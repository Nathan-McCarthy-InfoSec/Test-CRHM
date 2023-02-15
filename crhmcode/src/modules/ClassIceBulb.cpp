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

#include "ClassIceBulb.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;

ClassIceBulb* ClassIceBulb::klone(string name) const{
  return new ClassIceBulb(name);
}

void ClassIceBulb::decl(void) {

  Description = "'Estimates ice bulb temperature.'";

  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);
  declgetvar("*", "hru_rh", "(%)", &hru_rh);
  declgetvar("*", "hru_p", "(mm/int)", &hru_p);

  declvar("hru_icebulb", TDim::NHRU, "Estimates ice bulb temperature", "(" + string(DEGREE_CELSIUS) + ")", &hru_icebulb);

  declvar("hru_rainI", TDim::NHRU, "rain", "(mm/int)", &hru_rainI);

  declstatdiag("cumhru_rainI", TDim::NHRU, "cumulative HRU rain", "(mm)", &cumhru_rainI);

  declvar("hru_snowI", TDim::NHRU, "snow", "(mm/int)", &hru_snowI);

  declstatdiag("cumhru_snowI", TDim::NHRU, "cumulative HRU snow", "(mm)", &cumhru_snowI);

  declstatdiag("cumhru_pI", TDim::NHRU, "cumulative HRU snow", "(mm)", &cumhru_pI);

  decllocal("Pa", TDim::NHRU, "Atmospheric pressure", "(kPa)", &Pa);


  declparam("hru_elev", TDim::NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

  decldiagparam("tmaxI_allrain", TDim::NHRU, "[1.0]", "-10", "10", "precip all rain if HRU ice bulb temperature above or equal to this value",
      "(" + string(DEGREE_CELSIUS) + ")", &tmaxI_allrain);

  decldiagparam("tmaxI_allsnow", TDim::NHRU, "[-1.0]", "-10", "10", "precip all snow if HRUice bulb  temperature below this value",
      "(" + string(DEGREE_CELSIUS) + ")", &tmaxI_allsnow);

}

void ClassIceBulb::init(void) {

  nhru = getdim(TDim::NHRU);
  for (hh = 0; hh < nhru; ++hh) {
    Pa[hh] = 101.3f*pow((293.0f-0.0065f*hru_elev[hh])/293.0f, 5.26f);  // kPa
    cumhru_rainI[hh] = 0.0;
    cumhru_snowI[hh] = 0.0;
    cumhru_pI[hh] = 0.0;
  }
}

void ClassIceBulb::run(void) {

  long nstep = getstep() % Global::Freq;

  for (hh = 0; chkStruct(); ++hh){
    double Tk = hru_t[hh] + CRHM_constants::Tm;
    double D = 0.0000206*pow(Tk/CRHM_constants::Tm, 1.75);
    double RHO = Pa[hh]*1000.0/(CRHM_constants::Rgas*Tk);

    double qt = CRHM_constants::em/(Pa[hh]*1000.0)*611.213*exp(22.4422*hru_t[hh]/(CRHM_constants::Tm + hru_t[hh]));

    double lamda = 0.000076843*Tk + 0.003130762;

    double L;
    if(hru_t[hh] > 0.0)
      L = CRHM_constants::Lv;
    else
      L = CRHM_constants::Ls;

    double delta = CRHM_constants::em*L*qt/(CRHM_constants::Rgas*sqr(Tk));

    hru_icebulb[hh] = hru_t[hh] - L*(1.0 - hru_rh[hh]/100.0)*qt/(CRHM_constants::Cp + L*delta) *(RHO*CRHM_constants::Cp*D/lamda);

    hru_snowI[hh] = 0.0;
    hru_rainI[hh] = 0.0;

    if(hru_p[hh] > 0.0) { //rain or snow determined by temperature
      if(hru_icebulb[hh] >= tmaxI_allrain[hh]) { // all rain
        hru_rainI[hh] = hru_p[hh];
      }
      else if(hru_icebulb[hh] <= tmaxI_allsnow[hh]) { // all snow
        hru_snowI[hh] = hru_p[hh];
      }
      else { // mixed
        hru_rainI[hh] = hru_p[hh]*(tmaxI_allrain[hh] - hru_icebulb[hh])/(tmaxI_allrain[hh] - tmaxI_allsnow[hh]);
        hru_snowI[hh] = hru_p[hh] - hru_rainI[hh];
      }
    } // end if

    cumhru_rainI[hh] += hru_rainI[hh];
    cumhru_snowI[hh] += hru_snowI[hh];
    cumhru_pI[hh] = cumhru_pI[hh] + hru_snowI[hh] + hru_rainI[hh];
  }
}
