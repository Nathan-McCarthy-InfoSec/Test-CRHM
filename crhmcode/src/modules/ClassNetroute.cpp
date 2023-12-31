/**
* Copyright 2022, CRHMcode's Authors or Contributors
* This file is part of CRHMcode.
* 
* CRHMcode is free software: you can redistribute it and/or modify it under 
* the terms of the GNU General Public License as published by the Free Software 
* Foundation, either version 3 of the License, or (at your option) any later 
* version.
* 
* CRHMcode is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty 
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License along with 
* CRHMcode. If not, see <https://www.gnu.org/licenses/>.
* 
**/
//created by Manishankar Mondal

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm>

#include "ClassNetroute.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;


ClassNetroute* ClassNetroute::klone(string name) const{
  return new ClassNetroute(name);
}

double ClassNetroute::Function1(double *I, long hh) {
  return runDelay->ChangeLag(I, hh);
}

double ClassNetroute::Function2(double *X, long hh) {
  return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute::decl(void) {

  Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'";

  declvar("inflow", TDim::NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

  declstatdiag("cuminflow", TDim::NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

  declvar("outflow", TDim::NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

  declstatdiag("cumoutflow", TDim::NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

  decldiag("outflow_diverted", TDim::NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

  declstatdiag("cumoutflow_diverted", TDim::NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2)", &cumoutflow_diverted);

  declstatdiag("cum_to_Sd", TDim::NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

  declstatdiag("cum_to_soil_rechr", TDim::NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

  declvar("gwinflow", TDim::NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

  declstatdiag("gwcuminflow", TDim::NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

  declvar("gwoutflow", TDim::NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

  declstatdiag("gwcumoutflow", TDim::NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

  decldiag("gwoutflow_diverted", TDim::NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

  declstatdiag("gwcumoutflow_diverted", TDim::NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2)", &gwcumoutflow_diverted);

  declvar("ssrinflow", TDim::NHRU, "subsurface inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

  declstatdiag("ssrcuminflow", TDim::NHRU, "cumulative subsurface inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

  declvar("ssroutflow", TDim::NHRU, "HRU subsurface outflow", "(mm*km^2/int)", &ssroutflow);

  declstatdiag("ssrcumoutflow", TDim::NHRU, "cumulative HRU subsurface outflow", "(mm*km^2)", &ssrcumoutflow);

  declstatdiag("HRU_cumbasinflow", TDim::NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

  declvar("runinflow", TDim::NHRU, "overland inflow (sum of meltrunoff and runoff) from other HRUs", "(mm*km^2/int)", &runinflow);

  declstatdiag("runcuminflow", TDim::NHRU, "cumulative overland inflow (sum of meltrunoff and runoff) from other HRUs", "(mm*km^2)", &runcuminflow);

  declvar("runoutflow", TDim::NHRU, "HRU overland outflow", "(mm*km^2/int)", &runoutflow);

  declstatdiag("runcumoutflow", TDim::NHRU, "cumulative HRU overland outflow", "(mm*km^2)", &runcumoutflow);

  declstatdiag("cum_preferential_flow_to_gw", TDim::NHRU, "cumulative other HRU's runoff to gw of this HRU via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

  declparam("preferential_flow", TDim::NHRU, "[0]", "0", "1","0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


  declvar("basinflow", TDim::BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

  decldiag("basinflow_s", TDim::BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

  declstatdiag("cumbasinflow", TDim::BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

  declvar("basingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

  decldiag("basingw_s", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

  declstatdiag("cumbasingw", TDim::BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

  decllocal("soil_ssr_Buf", TDim::NHRU, "buffer subsurface runoff from soil, i.e. soil_ssr_Buf is from soil_ssr", "(mm/int)", &soil_ssr_Buf);

  decllocal("soil_runoff_Buf", TDim::NHRU, "buffer overland runoff from soil, i.e. soil_runoff_Buf is from soil_runoff", "(mm/int)", &soil_runoff_Buf);

  decllocal("soil_gw_Buf", TDim::NHRU, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf);


  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

  declparam("Kstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "aggregated storage constant", "(d)", &Kstorage);

  declparam("Lag", TDim::NHRU, "[0.0]", "0.0","1.0E4.0", "aggregated lag delay", "(h)", &Lag);

  declparam("ssrKstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

  declparam("ssrLag", TDim::NHRU, "[0.0]", "0.0","1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

  declparam("runKstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "runoff storage constant", "(d)", &runKstorage);

  declparam("runLag", TDim::NHRU, "[0.0]", "0.0","1.0E4", "runoff lag delay", "(h)", &runLag);

  declparam("gwKstorage", TDim::NHRU, "[0.0]", "0.0","200.0", "gw storage constant", "(d)", &gwKstorage);

  declparam("gwLag", TDim::NHRU, "[0.0]", "0.0","1.0E4", "gw lag delay", "(h)", &gwLag);

  declparam("whereto", TDim::NHRU, "[0]", "0", "1000", "send to; 0 - basin outflow, or HRU input", "()", &whereto);

  declparam("order", TDim::NHRU, "[1,2,3,4,5!]", "1","1000", "HRU routing process order", "()", &order);

  declparam("gwwhereto", TDim::NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

  declparam("Sdmax", TDim::NHRU, "[0]", "0.0", "1000.0","Maximum depression storage", "(mm)", &Sdmax);

  declparam("soil_rechr_max", TDim::NHRU, "[60.0]", "0.0", "350.0",
      "Maximum available water holding capacity for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "
      "and transpiration). Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

  decldiagparam("Sd_ByPass", TDim::NHRU, "[0]", "0", "1","0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

  decldiagparam("soil_rechr_ByPass", TDim::NHRU, "[1]", "0", "1","0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);


  soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

  soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

  soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


  declputvar("*", "Sd", "(mm)", &Sd);

  declputvar("*", "soil_moist", "(mm)", &soil_moist);

  declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

  declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

  declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute::init(void) {

  nhru = getdim(TDim::NHRU);

  if(soil_ssrDiv > 1){
    string S = "Netroute:  \"soil_ssr\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  if(soil_runoffDiv > 1){
    string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  if(soil_gwDiv > 1){
    string S = "Netroute:  \"gw_flow\". Converting to mm/int";
    CRHMException TExcept(S.c_str(), TExcept::WARNING);
    LogError(TExcept);
  }

  hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);
  ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
  runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
  gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

  basinflow[0] = 0.0;
  basinflow_s[0] = 0.0;
  cumbasinflow[0] = 0.0;
  basingw[0] = 0.0;
  basingw_s[0] = 0.0;
  cumbasingw[0] = 0.0;

  for(hh = 0; hh < nhru; ++hh) {
    inflow[hh] = 0.0;
    cuminflow[hh] = 0.0;
    outflow[hh] = 0.0;
    outflow_diverted[hh] = 0.0;
    cumoutflow_diverted[hh] = 0.0;
    cumoutflow[hh] = 0.0;
    cum_to_Sd[hh] = 0.0;
    cum_to_soil_rechr[hh] = 0.0;
    cum_preferential_flow_to_gw[hh] = 0.0;


    gwinflow[hh] = 0.0;
    gwcuminflow[hh] = 0.0;
    gwcumoutflow[hh] = 0.0;
    gwcumoutflow_diverted[hh] = 0.0;
    HRU_cumbasinflow[hh] = 0.0;

    ssrinflow[hh] = 0.0;
    ssrcuminflow[hh] = 0.0;
    ssroutflow[hh] = 0.0;
    ssrcumoutflow[hh] = 0.0;

    runinflow[hh] = 0.0;
    runcuminflow[hh] = 0.0;
    runoutflow[hh] = 0.0;
    runcumoutflow[hh] = 0.0;

    soil_ssr_Buf[hh] = 0.0;
    soil_runoff_Buf[hh] = 0.0;
    soil_gw_Buf[hh] = 0.0;

    bool OK = false;
    for(long jj = 0; chkStruct(jj); ++jj)
      if(order[jj] - 1 == hh){
        OK = true;
        break;
      }

    if(!OK){
        string SS = string("'" + Name + " (Netroute)' the 'order' parameter does not have a unique value for each HRU");
        CRHMException Except(SS.c_str() , TExcept::ERR);
        LogError(Except);
        throw Except;
    }
  }
}

void ClassNetroute::run(void) {

  long step = getstep();
  long nstep = step% Global::Freq;

  basinflow[0] = 0.0;
  basingw[0] = 0.0;

  for(long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

    for(hh = 0; chkStruct(hh); ++hh)
      if(order[hh] - 1 == jj)
        break;

    if(soil_gwDiv == 1) // interval value
       soil_gw_Buf[hh] = soil_gw[hh];

    gwinflow[hh] = soil_gw_Buf[hh]*hru_area[hh];

    gwoutflow_diverted[hh] = 0.0;

    double gw_amount = 0.0;

    for(long hhh = 0; chkStruct(hhh); ++hhh){
      if(gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh])-1 == hh || abs(gwwhereto[hhh]) > nhru)){ // handles "gwwhereto" <> 0
        gwoutflow_diverted[hhh] = gwoutflow[hhh];
        gw_amount = gwoutflow_diverted[hhh]; // units (mm*km^2/int)
        gwoutflow[hhh] = 0.0;
        gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

        if(abs(gwwhereto[hhh]) <= nhru){
          if(gwwhereto[hhh] > 0){ // direct to HRU surface
            double free = soil_rechr_max[hh] - soil_rechr[hh];
            if(free > 0.0 && !soil_rechr_ByPass[hh]){
              if(free > gw_amount/hru_area[hh]){ // units (mm*km^2/int)
                soil_rechr[hh] += gw_amount/hru_area[hh];
                soil_moist[hh] += gw_amount/hru_area[hh];
                cum_to_soil_rechr[hh] += gw_amount/hru_area[hh];
                gw_amount = 0.0;
              }
              else {
                gw_amount = (gw_amount/hru_area[hh] - free)*hru_area[hh];
                cum_to_soil_rechr[hh] += free;
                soil_moist[hh] += free;
                soil_rechr[hh] = soil_rechr_max[hh];
              }
            }

            free = Sdmax[hh] - Sd[hh];
            if(free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]){
              if(free > gw_amount/hru_area[hh]){ // units (mm*km^2/int)
                Sd[hh] += gw_amount/hru_area[hh];
                cum_to_Sd[hh] += gw_amount/hru_area[hh];
                gw_amount = 0.0;
              }
              else {
                gw_amount = (gw_amount/hru_area[hh] - free)*hru_area[hh];
                cum_to_Sd[hh] += free;
                Sd[hh] = Sdmax[hh];
              }
            }
          } // hh > 0
          else{ // hh < 0
            gw[hh] +=  gw_amount/hru_area[hh];
            gw_amount = 0.0;
          }
        } // <= HRU
        else{ // > nhru then put in basinflow
          basinflow[0] += gw_amount*1000; // (m3)
          HRU_cumbasinflow[hh] = gw_amount;
          cumoutflow[hh] += gw_amount;
          gw_amount = 0.0;
        }
      } // handles "gwwhereto" <> 0
    } // for hhh

    gwcuminflow[hh] += gwinflow[hh];

    if(soil_ssrDiv == 1) // interval value
       soil_ssr_Buf[hh] = soil_ssr[hh];

    if(soil_runoffDiv == 1) // interval value
       soil_runoff_Buf[hh] = soil_runoff[hh];

    runinflow[hh] = soil_runoff_Buf[hh]*hru_area[hh]; // includes melt and rain runoff
    runcuminflow[hh] += runinflow[hh];

    ssrinflow[hh] = soil_ssr_Buf[hh]*hru_area[hh]; // subsurface runoff
    ssrcuminflow[hh] += ssrinflow[hh];

    ssrcumoutflow[hh] += ssroutflow[hh];
    runcumoutflow[hh] += runoutflow[hh];

    inflow[hh] = (runoutflow[hh] + ssroutflow[hh] + gw_amount); // add this HRU runoff and subsurface flow

    cuminflow[hh] += inflow[hh];

    for(long hhh = 0; chkStruct(hhh); ++hhh) {
      if(whereto[hhh]-1 == hh && outflow[hhh] > 0.0){
        if(preferential_flow[hhh]) {
          gw[hh] += outflow[hhh]/hru_area[hh];
          cum_preferential_flow_to_gw[hh] += outflow[hhh]/hru_area[hh];
          outflow[hhh] = 0.0;
        }
        else {
          outflow_diverted[hhh] = outflow[hhh];
          cumoutflow_diverted[hhh] += outflow_diverted[hhh];
          double free = soil_rechr_max[hh] - soil_rechr[hh];
          if(free > 0.0 && !soil_rechr_ByPass[hh]){
            if(free > outflow[hhh]/hru_area[hh]){ // units (mm*km^2/int)
              soil_rechr[hh] += outflow[hhh]/hru_area[hh];
              soil_moist[hh] += outflow[hhh]/hru_area[hh];
              cum_to_soil_rechr[hh] += outflow[hhh]/hru_area[hh];
              outflow[hhh] = 0.0;
            }
            else {
              outflow[hhh] = (outflow[hhh]/hru_area[hh] - free)*hru_area[hh];
              cum_to_soil_rechr[hh] += free;
              soil_moist[hh] += free;
              soil_rechr[hh] = soil_rechr_max[hh];
            }
          }

          free = Sdmax[hh] - Sd[hh];
          if(free > 0.0 && !Sd_ByPass[hh] && outflow[hhh] > 0.0){
            if(free > outflow[hhh]/hru_area[hh]){ // units (mm*km^2/int)
              Sd[hh] += outflow[hhh]/hru_area[hh];
              cum_to_Sd[hh] += outflow[hhh]/hru_area[hh];
              outflow[hhh] = 0.0;
            }
            else {
              outflow[hhh] = (outflow[hhh]/hru_area[hh] - free)*hru_area[hh];
              cum_to_Sd[hh] += free;
              Sd[hh] = Sdmax[hh];
            } // if
          } // if
        } // else

        if(outflow[hhh] > 0.0) // handle excess
          redirected_residual[hh] +=  outflow[hhh]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

        outflow[hhh] = 0.0;
      } // if
    } // for hhh

    hruDelay->DoClark(hh); // need to update for later HRUs

    if(whereto[hh] == 0 && outflow[hh] > 0.0) { // move to basinflow
      basinflow[0] += outflow[hh]*1000; // (m3)
      HRU_cumbasinflow[hh] += outflow[hh];
      cumoutflow[hh] += outflow[hh];
    }
    if(gwwhereto[hh] == 0) { // move to basin gw
      basingw[0] += gwoutflow[hh]*1000; // (m3) end of every day
      gwcumoutflow[hh] += gwoutflow[hh];
    }

    if(nstep == 0){ // end of every day
      if(soil_ssrDiv > 1) // daily value - ready for next day
         soil_ssr_Buf[hh] = soil_ssr[hh]/soil_ssrDiv;

      if(soil_runoffDiv > 1) // daily value - ready for next day
         soil_runoff_Buf[hh] = soil_runoff[hh]/soil_runoffDiv;

      if(soil_gwDiv > 1) // daily value - ready for next day
         soil_gw_Buf[hh] = soil_gw[hh]/soil_gwDiv;
    } // end if

  } // for jj accessing hh

  runDelay->DoClark();
  ssrDelay->DoClark();
  gwDelay->DoClark();

  basinflow_s[0] = basinflow[0]*Global::Freq/86400.0;
  basingw_s[0] = basingw[0]*Global::Freq/86400.0;

  cumbasinflow[0] += basinflow[0];
  cumbasingw[0] += basingw[0];
}

void ClassNetroute::finish(bool good) {

  double Allcuminflow = 0.0;
  double Allcumoutflow = 0.0;
  double Allcumoutflowdiverted = 0.0;

  double Allgwcuminflow = 0.0;
  double Allgwcumoutflow = 0.0;
  double Allgwcumoutflowdiverted = 0.0;

  double Allssrcuminflow = 0.0;
  double Allssrcumoutflow = 0.0;
  double Allruncuminflow = 0.0;
  double Allruncumoutflow = 0.0;

  double AllSdcuminflow = 0.0;
  double Allrechrcuminflow = 0.0;

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (Netroute)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (Netroute)' gwDelay_in_storage     (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh)/hru_area[hh], hru_area[hh], basin_area[0]);

    LogMessageA(hh, string("'" + Name + " (Netroute)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
    LogMessageA(hh, string("'" + Name + " (Netroute)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
    LogMessageA(hh, string("'" + Name + " (Netroute)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh]/hru_area[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");

    Allcuminflow += cuminflow[hh];
    Allcumoutflow += cumoutflow[hh];
    Allcumoutflowdiverted += cumoutflow_diverted[hh];

    Allgwcuminflow += gwcuminflow[hh];
    Allgwcumoutflow += gwcumoutflow[hh];
    Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

    Allssrcumoutflow += ssrcumoutflow[hh];
    Allssrcuminflow += ssrcuminflow[hh];
    Allruncuminflow += runcuminflow[hh];
    Allruncumoutflow += runcumoutflow[hh];

    AllSdcuminflow += cum_to_Sd[hh];
    Allrechrcuminflow += cum_to_soil_rechr[hh];
  }

  LogMessage(string("'" + Name + " (Netroute)' cumbasinflow (m^3): ").c_str(), cumbasinflow[0]);
  LogMessage(string("'" + Name + " (Netroute)' cumbasingw   (m^3): ").c_str(), cumbasingw[0]);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute)' Allgwcuminflow (mm*basin): ").c_str(), Allgwcuminflow);
  LogMessage(string("'" + Name + " (Netroute)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
  LogMessage(string("'" + Name + " (Netroute)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute)' Allcuminflow (mm*basin): ").c_str(), Allcuminflow);
  LogMessage(string("'" + Name + " (Netroute)' Allcumoutflow (mm*basin): ").c_str(), Allcumoutflow);
  LogMessage(string("'" + Name + " (Netroute)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute)' Allssrcuminflow (mm*basin): ").c_str(), Allssrcuminflow);
  LogMessage(string("'" + Name + " (Netroute)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute)' Allruncuminflow (mm*basin): ").c_str(), Allruncuminflow);
  LogMessage(string("'" + Name + " (Netroute)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
  LogDebug(" ");

  LogMessage(string("'" + Name + " (Netroute)' AllSdcuminflow (mm*basin): ").c_str(), AllSdcuminflow);
  LogMessage(string("'" + Name + " (Netroute)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
  LogDebug(" ");

  delete hruDelay;
  delete ssrDelay;
  delete runDelay;
  delete gwDelay;
}
