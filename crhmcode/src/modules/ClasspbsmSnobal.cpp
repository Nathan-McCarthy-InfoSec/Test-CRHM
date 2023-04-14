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

#include "ClasspbsmSnobal.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;


ClasspbsmSnobal* ClasspbsmSnobal::klone(string name) const{
  return new ClasspbsmSnobal(name);
}

void ClasspbsmSnobal::decl(void) {

  Description = "'Special \"pbsm\" module compatible with \"snobal\".' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

  variation_set = VARIATION_0 + VARIATION_2;

  declgetvar("*", "hru_u", "(m/s)", &hru_u);


  variation_set = VARIATION_1 + VARIATION_3;

  declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


  variation_set = VARIATION_2 + VARIATION_3;

  declparam("u_D", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

  declparam("Drift_offset", TDim::NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

  declparam("Drift_slope", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

  declparam("Subl_offset", TDim::NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

  declparam("Subl_slope", TDim::NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


  variation_set = VARIATION_ORG;

  declstatvar("SWE_max", TDim::NHRU, "snow water equivalent seasonal maximum", "(mm)", &SWE_max);

  declvar("hru_subl", TDim::NHRU, "interval sublimation", "(mm/int)", &Subl);

  declvar("hru_drift", TDim::NHRU, "interval composite transport", "(mm/int)", &Drift);

  decldiag("DriftH", TDim::NHRU, "interval transport", "(mm/int)", &DriftH);

  decldiag("SublH", TDim::NHRU, "interval sublimation", "(mm/int)", &SublH);

  declvar("Drift_out", TDim::NHRU, "interval transport out", "(mm/int)", &Drift_out);

  declvar("Drift_in", TDim::NHRU, "interval transport in", "(mm/int)", &Drift_in);

  declvar("BasinSnowLoss", TDim::BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

  declstatdiag("cumSubl", TDim::NHRU, "cumulative sublimation", "(mm)", &cumSubl);

  declstatdiag("cumDrift", TDim::NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

  declstatdiag("cumBasinSnowLoss", TDim::BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

  declstatdiag("cumBasinSnowGain", TDim::BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

  declstatdiag("cumDriftIn", TDim::NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

  decllocal("hru_basin", TDim::NHRU, "conversion factor", "()", &hru_basin);

  decldiag("DrySnow", TDim::NHRU, "DrySnow", "()", &DrySnow);

  declstatdiag("SnowAge", TDim::NHRU, "SnowAge", "()", &SnowAge);

  decldiag("Prob", TDim::NHRU, "Probability", "()", &Prob);

  decldiag("snowdepth", TDim::NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

/* parameters */

  declparam("fetch", TDim::NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

  declparam("Ht", TDim::NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

  declparam("distrib", TDim::NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

  decldiagparam("N_S", TDim::NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

  decldiagparam("A_S", TDim::NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

  declparam("basin_area", TDim::BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

  declparam("hru_area", TDim::NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

  decldiagparam("inhibit_evap", TDim::NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

  declparam("inhibit_bs", TDim::NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

  decldiagparam("inhibit_subl", TDim::NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

  declputvar("*", "SWE", "(kg/m^2)", &SWE);
  declputvar("*", "z_s", "(m)", &z_s);
  declputvar("*", "rho", "(kg/m^3)", &rho);

    declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
    declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
    declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClasspbsmSnobal::init(void) {

  nhru = getdim(TDim::NHRU);

  cumBasinSnowLoss[0] = 0.0;
  cumBasinSnowGain[0] = 0.0;

  for (hh = 0; hh < nhru; ++hh) {
    SWE[hh] = 0.0;
    cumDrift[hh] = 0.0;
    cumDriftIn[hh] = 0.0;
    cumSubl[hh] = 0.0;
    SnowAge[hh] = 0.0;
    DrySnow[hh] = 0;
    snowdepth[hh] = 0.0;

    if((hh > 0) && (Ht[hh] < Ht[hh-1]) && distrib[hh-1] > 0){
      CRHMException TExcept(string("'" + Name + " (pbsmSnobal)' vegetation heights not in ascending order.").c_str(), TExcept::WARNING);
      LogError(TExcept);
    }
  }

  for (hh = 0; hh < nhru; ++hh)
    hru_basin[hh] = hru_area[hh]/basin_area[0];
}

void ClasspbsmSnobal::run(void) {

  double Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
  double SumDrift, total, transport;

  for (hh = 0; chkStruct(); ++hh) {

   if(variation == VARIATION_ORG || variation == VARIATION_2)
     hru_u_ = hru_u[hh];
   else
     hru_u_ = hru_Uadjust[hh];

   if(variation == VARIATION_2 || variation == VARIATION_3)
     hru_u_ = u_D[hh]*hru_u_;

   Drift_out[hh] = 0.0;
   Drift_in[hh] = 0.0;
   Drift[hh] = 0.0;

   Subl[hh] = 0.0;
   Prob[hh] = 0.0;

   if(SWE[hh] > 0.0 && !inhibit_bs[hh]) {

     E_StubHt = Ht[hh] - z_s[hh];                      // depths(m)
     if(E_StubHt < 0.0001) E_StubHt = 0.0001;

     Ustar = 0.02264*pow(hru_u_, 1.295f);            // Eq. 6.2 rev.,  Ustar over fallow

     if (E_StubHt > 0.01) {
       Znod = (sqr(Ustar)/163.3f)+0.5*N_S[hh]*E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
       Lambda = N_S[hh]*A_S[hh]*E_StubHt;                      // Raupach Eq. 1

       Ustn  = Ustar*sqrt((PBSM_constants::Beta*Lambda)/(1.0+PBSM_constants::Beta*Lambda));

       Uten_Prob = (log(10.0/Znod))/PBSM_constants::KARMAN *sqrt(Ustar-Ustn);
     }
     else
     {
       Uten_Prob = hru_u_;
     } // end if

     bool newsnow = net_snow[hh];

     ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, newsnow, SnowAge[hh], DrySnow[hh]);  // (mm)

     if (Prob[hh] > 0.001) {
       Ut = Ut * 0.8;

       double RH = hru_ea[hh]/Common::estar(hru_t[hh]); // Snobal uses Pascals

       Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, RH, fetch[hh], N_S[hh], A_S[hh]);

       if(variation == VARIATION_2 || variation == VARIATION_3){
         DriftH[hh] = Drift_offset[hh] + DriftH[hh]*Drift_slope[hh];
         SublH[hh] = Subl_offset[hh] + SublH[hh]*Subl_slope[hh];
       }

       Drift_out[hh] = DriftH[hh]*Prob[hh]/fetch[hh];

       if(!inhibit_subl[hh])
         Subl[hh] = SublH[hh]*Prob[hh];

// handle insufficient snow pack

       if(Drift_out[hh] + Subl[hh] > SWE[hh]){
         if(Drift_out[hh] >= SWE[hh]){
           Drift_out[hh] = SWE[hh];
           Subl[hh] = 0.0;
         }
         else
           Subl[hh] = SWE[hh] - Drift_out[hh];
       }

       cumDrift[hh] += Drift_out[hh];
       cumSubl[hh] += Subl[hh];
     }
   } // end if
 } // end for (hh)

 // distribute drift

  if(distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
    double Drft = Drift_out[0]*distrib[0];
    SWE[0] += Drft;
    cumDriftIn[0] += Drft;
    cumBasinSnowGain[0] += Drft*hru_basin[0];  // **** hru_basin = hru_area/basin_area ****
  }

  BasinSnowLoss[0] = 0.0;
  long LastN = 0;

  if(!inhibit_bs[0]&& nhru == 1){
    BasinSnowLoss[0] = Drift_out[0];
    cumBasinSnowLoss[0] += BasinSnowLoss[0];
  }

  for (long nn = LastN; chkStruct(nn); ++nn) {
    if(distrib[nn] >= 0.0 && nn+1 < nhru) // skip till last HRU or -ve distribution
      continue;

    SumDrift = 0.0;
    for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) // sum drift over range
        SumDrift += Drift_out[hhh]*hru_basin[hhh];

    if(SumDrift > 0.0){ // drift has occurred!
      for (long hh = LastN + 1; chkStruct(hh, nn+1); ++hh) {

        if(Ht[hh] > z_s[hh])
          SWE_max[hh] = SWE[hh] + rho[hh]*(Ht[hh]-z_s[hh]); // not filled
        else
          SWE_max[hh] = SWE[hh]; // filled or over filled. Wait for snow transport

        if(SWE_max[hh] <= 0.0)
           SWE_max[hh] = Ht[hh];

        if(hh == nn) { // handle last HRU
          if(distrib[nn] > 0){
            double In = SumDrift/hru_basin[hh]; // remaining drift
            if(SWE_max[hh] > SWE[hh] + In){ // fill snowpack, remainder leaves basin
              Drift_in[hh] = In; // can handle all
              cumDriftIn[hh] += Drift_in[hh];
              transport = 0.0;
            }
            else if(SWE_max[hh] > SWE[hh]){ // cannot handle all
              Drift_in[hh] = SWE_max[hh] - SWE[hh];
              cumDriftIn[hh] += Drift_in[hh];
              transport -= (In -(SWE_max[hh] - SWE[hh]))*hru_basin[hh];
            }
            else // zero or -ve - happens during melt??
              transport = SumDrift;
          }
          else if(distrib[nn] < 0){ // all drift deposited
              Drift_in[hh] = SumDrift/hru_basin[hh]; // can handle all
              cumDriftIn[hh] += Drift_in[hh];
              transport = 0.0;
          }
          else // distrib[nn] == 0 -> all excess drift leaves basin
              transport = SumDrift;

          BasinSnowLoss[0] += (transport + Drift_out[hh]*hru_basin[hh]);
          cumBasinSnowLoss[0] += (transport + Drift_out[hh]*hru_basin[hh]);
        }
        else if(SWE_max[hh] > SWE[hh] &&  distrib[hh] > 0.0) {
// handle intermediate HRUs with available storage and distrib > 0
          total = 0.0;
          for (long jj = hh; chkStruct(jj, nn+1); jj++) // calculate denominator
            total += fabs(distrib[jj]);
// determine contribution and scale
          transport = SumDrift*fabs(distrib[hh])/total/hru_basin[hh];
          if(SWE_max[hh] > SWE[hh] + transport) // sufficient capacity
            Drift_in[hh] += transport;
          else if(SWE_max[hh] > SWE[hh]){
            transport = SWE_max[hh] - SWE[hh];  // insufficient capacity
            Drift_in[hh] += transport;
          }
          else
            transport = 0.0;

          SumDrift -= transport*hru_basin[hh]; // remove drift used from total available
          cumDriftIn[hh] += transport;
        } // end if
      } // end for (hh)
      LastN = nn+1;
    } // end if
  } // end for (nn)

  for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation
    Drift[hh] = Drift_in[hh] - Drift_out[hh];
    if(SWE[hh] > 0.0){
      const_cast<long*> (inhibit_evap)[hh] = 1;
      snowdepth[hh] = Common::DepthofSnow(SWE[hh]);
    }
    else{
      const_cast<long*> (inhibit_evap)[hh] = 0;
      snowdepth[hh] = 0.0;
    }
  } // end for (hh)
}

void ClasspbsmSnobal::finish(bool good) {

  for(hh = 0; chkStruct(); ++hh) {
    LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
    LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
    LogDebug(" ");
  }

  LogMessage("'pbsmSnobal' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]); //
  LogMessage("'pbsmSnobal' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]); //
  LogDebug(" ");
}
