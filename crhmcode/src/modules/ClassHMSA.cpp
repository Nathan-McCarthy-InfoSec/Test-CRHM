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

#include "ClassHMSA.h"
#include "../core/GlobalDll.h"
#include "../core/ClassCRHM.h"
#include "newmodules/SnobalDefines.h"


using namespace CRHM;







ClassHMSA* ClassHMSA::klone(string name) const{
  return new ClassHMSA(name);
}

void ClassHMSA::decl(void) {

  Description = "'Estimation of frost table (Masaki Hayashi 2007).' \
                 'ebsm using variable hru_t ("+string(DEGREE_CELSIUS)+"),' \
                 'ebsm using observation Tsurf_obs ("+string(DEGREE_CELSIUS)+").'";

  MaxFrontCnt = 10;

  variation_set = VARIATION_ORG;

// Variables:
  declstatvar("Cum_Thaw", TDim::NHRU, "Cumulative thaw depth", "(m)", &Cum_Thaw);
  declstatvar("Cum_Frozen", TDim::NHRU, "Cumulative frozen depth", "(m)", &Cum_Frozen);
  declvar("Lamda_b", TDim::NHRU, "Thermal conductivity", "()", &Lamda_b); // (W/m.DEGREE_CELCIUS)
  declvar("Thaw_D", TDim::NHRU, "thaw table depth below surface", "(m)", &Thaw_D);
  declvar("Frozen_D", TDim::NHRU, "frost table depth below surface", "(m)", &Frozen_D);
  declvar("C_K0", TDim::NHRU, "Conductivity", "()", &C_K0);
  declvar("Last_Tsurf", TDim::NHRU, "last surface temperature", "(" + string(DEGREE_CELSIUS) + ")", &Last_Tsurf);

  declvar("f", TDim::NHRU, "Vol fraction of ice (or water)", "(m^3/m^3)", &f);
  declvar("Soil_Ice", TDim::NLAY, "Ice fraction in soil", "()", &Soil_Ice, &Soil_Ice_lay);
  declvar("Soil_Water", TDim::NLAY, "Liquid water fraction in soil", "()", &Soil_Water, &Soil_Water_lay);
  declvar("Total_Moisture", TDim::NLAY, "layer moisture fraction", "()", &Total_Moisture, &Total_Moisture_lay);
  declstatvar("Cum_d", TDim::NLAY, "cumulative layer depths", "(m)", &Cum_d, &Cum_d_lay);
  declstatvar("Frozen_ID", TDim::NLAY, "cumulative layer depths", "(m)", &Frozen_ID, &Frozen_ID_lay);

  declvar("FrntDepth", TDim::NDEFN, "Front depth", "(m)", &FrntDepth, &FrntDepth_array, MaxFrontCnt);
  declstatvar("FreezeCum", TDim::NDEFN, "Front depth", "(m)", &FreezeCum, &FreezeCum_array, MaxFrontCnt);
  declvar("ThawCum", TDim::NDEFN, "Front depth", "(m)", &ThawCum, &ThawCum_array, MaxFrontCnt);
  declvar("FrntDepthType", TDim::NDEFN, "Front depth type > 0 thaw, < 0 freeze", "()", &FrntDepthType, &FrntDepthType_array, MaxFrontCnt);
  declvar("FrontCnt", TDim::NHRU, "number of fronts", "()", &FrontCnt);

// local variables
  decllocal("Tsurface", TDim::NHRU, "soil surface temperature used in module", "()", &Tsurface);

// Parameters (some are already defined in 'CRHMQuinton'):
  declparam("Alpha_ID", TDim::NHRU, "1", "0", "1", "For ID=0 input Alpha values used, for ID=1 Alpha calculated in model", "()", &Alpha_ID);
  declparam("Alpha_T", TDim::NHRU, "0.000118", "0.0", "1e2", "Thaw layer migration constant", "()", &Alpha_T); // (J^-1/2/m^3/2)
  declparam("Alpha_F", TDim::NHRU, "0.000118", "0.0", "1e2", "Freeze layer migration constant", "()", &Alpha_F); //(J^-1/2/m^3/2)

  declparam("Soil_depths_lay", TDim::NLAY, "[0.15] , [0.1], [0.1] ,[0.1]", "0.0", "100.0", "layer depths", "(m)", &Soil_Depths, &Soil_depths_lay);
  declparam("Organic", TDim::NLAY, "0.10, 0.17, 0.24, 0.25, 0.25, 0.25", "0.0", "1.0", "Volume ratio of organic matter", "(m^3/m^3)", &Organic, &Organic_lay);
  declparam("Porosity", TDim::NLAY, "0.90, 0.83, 0.76, 0.75, 0.75, 0.75", "0.0", "1.0", "Layer Porosity", "(m^3/m^3)", &Porosity, &Porosity_lay); // "Pors" in CRHMQuinton
  declparam("Bulkdensity", TDim::NLAY, "90.0, 144.3, 200.0, 248.0, 248.0, 248.0", "0.0", "1e3", "Bulk density of layer", "(kg/m^3)", &BulkDensity, &BulkDensity_lay);
  declparam("Soil_ID", TDim::NLAY, "0, 1, 2, 3, 3, 3", "0", "4", "Soil_ID", "(kg/m^3)", &Soil_ID, &Soil_ID_lay);

  declparam("InitThaw_D", TDim::NHRU, "0.7", "0.0", "1e2", "Initial thaw table depth below surface", "(m)", &InitThaw_D);
  declparam("InitFrozen_D", TDim::NHRU, "0.0", "0.0", "1e2", "Initial frost table depth below surface", "(m)", &InitFrozen_D);
  declparam("Soil_Layers", TDim::NHRU, "6", "0.0", "100.0", "No. of soil layers", "()", &Soil_Layers);
  declparam("D_Top", TDim::NHRU, "0.02", "0.0", "1e2", "Pos of upper bndry temp rel to grd surface", "(m)", &D_Top);
  declparam("Method_ID", TDim::NHRU, "1", "1", "5", "SoilHeat method, 1/2/3/4/5 - Johansen Complete/Johansen  common/ De Vries as Hayashi/ De Vries as Farouki/ Chad", "()", &Method_ID);

  declparam("TMPB_W", TDim::NDEF, "0.15, 0.18, 0.19, 0.19, 0.06", "0", "1.0", "Liquid water fraction in soil", "()", &TMPB_W, &TMPB_W_NDEF, 5);

  variation_set = VARIATION_0;

// driving variable:
  declgetvar("*", "hru_t", "(" + string(DEGREE_CELSIUS) + ")", &hru_t);

  variation_set = VARIATION_1;

  Liqcnt = declreadobs("LiqWat", TDim::NOBS, "liquid water at depth observation", "()", &LiqWat, HRU_OBS_misc); // # layers
  Totcnt = declreadobs("TotMoist", TDim::NOBS, "total moisture at depth observation", "()", &TotMoist, HRU_OBS_misc); // # layers
  declreadobs("Tsurf_obs", TDim::NHRU, "soil surface temperature observation", "(" + string(DEGREE_CELSIUS) + ")", &Tsurf_obs, HRU_OBS_misc);

  variation_set = VARIATION_ORG;
}

void ClassHMSA::init(void) {

  nhru = getdim(TDim::NHRU);
  nlay = getdim(TDim::NLAY);

//[Max_Layers]
//double Alpha; variable is unreferenced commenting out for now - jhs507
//double I_Avg; variable is unreferenced commenting out for now - jhs507
//double I_Dummy; variable is unreferenced commenting out for now - jhs507
//double F_Dummy; variable is unreferenced commenting out for now - jhs507

  for(hh = 0; chkStruct(); ++hh) {
    if(Soil_Layers[hh] > nlay){
      CRHMException TExcept("In module 'HMSA' Soil_Layers parameter must be <= number of layers (nlay)!", TExcept::TERMINATE);
      LogError(TExcept);
    }

    Thaw_D[hh] = InitThaw_D[hh];
    Frozen_D[hh] = InitFrozen_D[hh];
    FrontCnt[hh] = 0;

    for(long nn = 0; nn < MaxFrontCnt; ++nn){
      FrntDepthType_array[nn][hh] = 0;
      FrntDepth_array[nn][hh] = 0.0;
      FreezeCum_array[nn][hh] = 0.0;
      ThawCum_array[nn][hh] = 0.0;
    }
  } // for
}

void ClassHMSA::run(void) {

  long I_Avg;
  double Alpha;

  for(hh = 0; chkStruct(); ++hh) {

    switch (variation) {
      case VARIATION_ORG :
        Tsurface[hh] = hru_t[hh]; // variable
      break;
      case VARIATION_1 :
        Tsurface[hh] = Tsurf_obs[hh]; // variable
      break;
    } // switch

        // Calculate accumulative depth of each layers
      Cum_d_lay[0][hh] = Soil_depths_lay[0][hh];
      for (long nn = 1; nn < Soil_Layers[hh]; ++nn)
          Cum_d_lay[nn][hh] = Cum_d_lay[nn-1][hh] + Soil_depths_lay[nn][hh];

    if (Thaw_D[hh] > 0.0) { //  Frozen_ID = 0 = thaw, = 1 = frozen
        for (long nn = 0; nn < Soil_Layers[hh]; ++nn)
          Frozen_ID_lay[nn][hh] = 1; // sets frozen
        for (long nn = 0; nn < Soil_Layers[hh]; ++nn)   {
            Frozen_ID_lay[nn][hh] = 0; // sets unfrozen
            if( Thaw_D[hh] < Cum_d_lay[nn][hh]) break;
        }
    }
    else  {
        for (long nn = 0; nn < Soil_Layers[hh]; ++nn)
          Frozen_ID_lay[nn][hh] = 0; // sets unfrozen
        for (long nn = 0; nn < Soil_Layers[hh]; ++nn)   {
            Frozen_ID_lay[nn][hh] = 1; // sets frozen
            if( Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
        }
    }

    for(long nn = 0; nn < Soil_Layers[hh]; ++nn) {

      if(variation == VARIATION_1){
        Soil_Water_lay[nn][hh] = LiqWat[min<long>(nn, Liqcnt)];
        Total_Moisture_lay[nn][hh] = TotMoist[min<long>(nn, Totcnt)];
      }
      else if(getstep() == 1){ // fix
        Soil_Water_lay[nn][hh] = 0.0;
        Total_Moisture_lay[nn][hh] = 0.5;
      }

     if(Frozen_ID_lay[nn][hh] == 1)
          Soil_Water_lay[nn][hh] = TMPB_W[Soil_ID[hh]];
     else
         Soil_Water_lay[nn][hh] = Total_Moisture_lay[nn][hh];

// Mass conservation checks:
      if (Total_Moisture_lay[nn][hh] > Porosity_lay[nn][hh])
        Total_Moisture_lay[nn][hh] = Porosity_lay[nn][hh];
      if (Soil_Water_lay[nn][hh] > Total_Moisture_lay[nn][hh])
        Soil_Water_lay[nn][hh] = Total_Moisture_lay[nn][hh];
      Soil_Ice_lay[nn][hh] = Total_Moisture_lay[nn][hh] - Soil_Water_lay[nn][hh];
      if (Soil_Ice_lay[nn][hh] < 0.0)
        Soil_Ice_lay[nn][hh] = 0.0;
    } // for nn

// Start Hayashi's algorithm
// For the 1st time step, calculate the initial values of Cum_Thaw & Cum_Frozen from initial Thaw_D & Frozen_D
        if (getstep() == 1) { // first CRHM timestep
            if (Thaw_D[hh] > 0.0) {
                 f[hh] = 0.0;
                 I_Avg = 0;
                 for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
                    ++I_Avg;
                    f[hh] += Soil_Water_lay[nn][hh]*Soil_depths_lay[nn][hh];
                    if(Thaw_D[hh] < Cum_d_lay[nn][hh]) break;

                 }
                 f[hh] /= Cum_d_lay[I_Avg-1][hh];
                 if (Alpha_ID[hh] >0)
                   Cum_Thaw[hh] = Thaw_D[hh]*Thaw_D[hh]*Rho_Ice*f[hh]*Water_Ice /(2.0*86400.0); // reverse of Eq. 4 (and 86400 is for daily totals - needs changing for timestep)
                 else
                   Cum_Thaw[hh] = Thaw_D[hh]*Thaw_D[hh]/(Alpha_T[hh]*Alpha_T[hh]*86400.0); // reverse of Eq. (4) //daily value

                 Cum_Frozen[hh] = 0.0;
                 Frozen_D[hh] = 0.0;

                 FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
                 ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];
                 FrntDepthType_array[FrontCnt[hh]][hh] = 1;
            }
            else{ // i.e. Frozen_D[hh] > 0.0
                 f[hh] = 0.0;
                 I_Avg = 0;
                 for (long nn=0 ;nn < Soil_Layers[hh]; ++nn) {
                    I_Avg ++   ;
                    f[hh] += Soil_Ice_lay[nn][hh];
                    if(Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
                 }
                 f[hh] /= I_Avg;
                 if (Alpha_ID[hh] >0)
                   Cum_Frozen[hh] = Frozen_D[hh]*Frozen_D[hh]*Rho_Water*f[hh]*Water_Ice/(2.0*86400.0); // reverse of Eq. (4)
                 else
                   Cum_Frozen[hh] = Frozen_D[hh]*Frozen_D[hh]/(Alpha_F[hh]*Alpha_F[hh]*86400.0); // reverse of Eq. (4) //daily value

                 Cum_Thaw[hh] = 0.0;
                 Thaw_D[hh] = 0.0;

                 FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
                 FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
                 FrntDepthType_array[FrontCnt[hh]][hh] = -1;
            }
            ++FrontCnt[hh];  // no need to check
         } // end of first time step
         else {      // other time steps
            if (Tsurface[hh] > 0.0 )    {  // surface thaw condition
                if(Last_Tsurf[hh] < 0.0){ // save frozen front
                  FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
                  FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
                  FrntDepthType_array[FrontCnt[hh]][hh] = -1;
                  if(FrontCnt[hh] < MaxFrontCnt-1)
                    ++FrontCnt[hh];
                  else{
                    CRHMException TExcept("Maximum # of fronts exceeded ", TExcept::TERMINATE);
                    LogError(TExcept);
                    throw TExcept;
                  }
                  FrntDepthType_array[FrontCnt[hh]][hh] = 1;
                }
                Frozen_D[hh] = 0.0;
                Cum_Frozen[hh] = 0.0;
                Lamda_b[hh] = 0.0;
                f[hh] = 0.0;
                I_Avg = 0;
            // calculate the thaw penetration
                for (long nn = 0; nn < Soil_Layers[hh]; ++nn)    {
                    f[hh] +=  Total_Moisture_lay[nn][hh]*Soil_depths_lay[nn][hh];
                    ++I_Avg;
                    Get_Heat_Param_Soil(1.0, nn);
                    Lamda_b[hh] += (Soil_depths_lay[nn][hh]/C_K0[hh]);
                    if(Thaw_D[hh] < Cum_d_lay[nn][hh]) break;
                }
                f[hh] /= Cum_d_lay[I_Avg-1][hh];
                Lamda_b[hh] = Cum_d_lay[I_Avg-1][hh]/Lamda_b[hh];
                if (Alpha_ID[hh] >0)
                  Alpha = sqrt(2.0/(Rho_Ice*f[hh]*Water_Ice));
                else
                  Alpha = Alpha_T[hh];
                Cum_Thaw[hh] += Lamda_b[hh]*Tsurface[hh];

                Thaw_D[hh] = Alpha*sqrt(86400.0*Cum_Thaw[hh]); //daily value

                FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
                ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];

                if(FrontCnt[hh] > 1 && FrntDepth_array[FrontCnt[hh]][hh] >= FrntDepth_array[FrontCnt[hh]-1][hh]){ // caught up ?
                  FrntDepth_array[FrontCnt[hh]-1][hh] = 0.0;
                  FrontCnt[hh] -= 2; // go back to earlier thaw front
                  Cum_Thaw[hh] = sqr(FrntDepth_array[FrontCnt[hh]][hh]/Alpha)/86400.0;
                }
            } // end of surface thaw condition
            else                 {   // surface frozen condition
                  if(Last_Tsurf[hh] > 0.0){ // save thaw front
                    FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
                    ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];
                    FrntDepthType_array[FrontCnt[hh]][hh] = 1;
                    if(FrontCnt[hh] < MaxFrontCnt-1)
                      ++FrontCnt[hh];
                    else{
                      CRHMException TExcept("Maximum # of fronts exceeded ", TExcept::TERMINATE);
                      LogError(TExcept);
                      throw TExcept;
                    }
                    FrntDepthType_array[FrontCnt[hh]][hh] = -1;
                  }
                  Thaw_D[hh] = 0.0;
                  Cum_Thaw[hh] = 0.0;
                Lamda_b[hh] = 0.0;
                f[hh] = 0.0;
                I_Avg = 0;
            // calculate the frost penetration
                for (long nn = 0; nn < Soil_Layers[hh]; ++nn)    {
                    f[hh] +=  Total_Moisture_lay[nn][hh]*Soil_depths_lay[nn][hh];
                    if(Soil_Ice_lay[nn][hh] < 0.0)
                      Soil_Ice_lay[nn][hh] = 0.0;
                    Get_Heat_Param_Soil(-1.0, nn);
                    Lamda_b[hh] += (Soil_depths_lay[nn][hh]/C_K0[hh]);
                    I_Avg ++;
                    if(Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
                }
                f[hh] /= Cum_d_lay[I_Avg-1][hh];
                Lamda_b[hh] = Cum_d_lay[I_Avg-1][hh]/Lamda_b[hh];
                if (Alpha_ID[hh] >0)
                  Alpha = sqrt(2.0/(Rho_Water*f[hh]*Water_Ice));
                else
                  Alpha = Alpha_F[hh];

                Cum_Frozen[hh] += -1.0* Lamda_b[hh]*Tsurface[hh];
                Frozen_D[hh] = Alpha*sqrt(86400.0*Cum_Frozen[hh]); //daily value

                FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
                FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];

                if(FrontCnt[hh] > 1 && FrntDepth_array[FrontCnt[hh]][hh] >= FrntDepth_array[FrontCnt[hh]-1][hh]){ // caught up ?
                  FrntDepth_array[FrontCnt[hh]-1][hh] = 0.0;
                  FrontCnt[hh] -= 2; // go back to earlier freeze front
                  Cum_Frozen[hh] = sqr(FrntDepth_array[FrontCnt[hh]][hh]/Alpha)/86400.0;
                }
            } // end of surface frozen condition
         } //end of other time step
         Last_Tsurf[hh] = Tsurface[hh];

        if(laststep()){
            if(Tsurface[hh] > 0){
              FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
              ThawCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
              FrntDepthType_array[FrontCnt[hh]][hh] = 1;
            }
            else{
              FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
              FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
              FrntDepthType_array[FrontCnt[hh]][hh] = -1;
            }
            ++FrontCnt[hh]; // no need to check
        }
  } // for hh

}

void ClassHMSA::Get_Heat_Chad(long nn){

   double Minerals = 1.0 - Porosity_lay[nn][hh] - Organic_lay[nn][hh];

   double x_a = K_Air;
   double x_w = Soil_Water_lay[nn][hh];
   double x_s = 1.0-Porosity_lay[nn][hh] + Soil_Ice_lay[nn][hh];
   double lam_s;

   if (Minerals < 0.1)     // Organic Soil
     lam_s = K_Organic;
   else if (Organic_lay[nn][hh] < 0.1 ) // Mineral Soil
     lam_s = K_Minerals;
   else   //mixed
     lam_s = (Minerals*K_Minerals + Organic_lay[nn][hh]*K_Organic)/x_s;

   double n = Porosity_lay[nn][hh];

   double g_a;
   if(x_w >= 0.09)
     g_a = 0.333-x_a/n*(0.333-0.035);
   else
     g_a = 0.013 + 0.944*x_w;

   double g_c = 1.0 - 2.0*g_a;

   //double Fs = 1.0/3.0*(2.0/(1 + (ks_s[soil_type_lay[nn][hh]]/lam_w-1.0)*0.125)
   //             + (1.0/((1 + (ks_s[soil_type_lay[nn][hh]]/lam_w-1.0)*0.75))));

   //double Fa = 1.0/3.0*(2.0/(1 + (lam_a/lam_w-1.0)*ga) + (1.0/((1 + (lam_a/lam_w-1.0)*gc))));

   double F_a = 1.0/3.0*(2.0/(1.0+(lam_a/lam_w-1.0)*g_a) + 1.0/(1.0+(lam_a/lam_w-1.0)*g_c));
   double F_s = 1.0/3.0*(2.0/(1.0+(lam_s/lam_w-1.0)*g_a) + 1.0/(1.0+(lam_s/lam_w-1.0)*g_c));

   //double a = Farouki_a(por_s[soil_type_lay[nn][hh]]);
   double a = Farouki_a(Porosity_lay[nn][hh]);

 // Calculate thermal cond. (W/m/K) of each layer depending on thermal & saturation condition (C_K0 in HMSA):
 // if layer is saturated & frozen:
       C_K0[hh]  = lam_i*a*a + lam_s*sqr(1.0-a)            // lamis_lay[nn][hh]
                            + lam_s*lam_i*(2*a-2*sqr(a))
                            /(lam_s*a+lam_i*(1.0-a));
 // if layer is satureated & UNfrozen:
       C_K0[hh]  = lam_w*a*a + lam_s*sqr(1.0-a)
                            + lam_s*lam_w*(2*a-2*sqr(a))   // lamws_lay[nn][hh]
                            /(lam_s*a+lam_w*(1.0-a));
 // if layer is UNsaturated & UNfrozen:
       C_K0[hh] = (x_w*lam_w + F_a*x_a*lam_a +F_s*x_s*lam_s) // lamwsa_lay[nn][hh]
                             /(x_w + F_a*x_a + F_s*x_s);
}

void ClassHMSA::Get_Heat_Param_Soil(double Soil_Temp, long nn) {

// Subroutine to calculate soil heat parameters (method to be chosen by user)
// uses: int Method_ID, double bulkdensity, Porosity, Organic, Soil_Water, Soil_Ice.
// parameters: Soil_Temp, layer.
// returns: C_K0 = conductivity; C_K1 = specific  heat capacity

double Air, Minerals; //repsective volumetric fractions of soil air and minerals
double KersNumber, SoilDryCond, SoilSatCond; // for method 2
double Sr, g_a, g_c, F_a, F_s, x_a, x_w, x_s, lam_a, lam_w, lam_s; //for method 3
//double Solid; varible is unreferenced commenting out for now - jhs507
//double x_i; varible is unreferenced commenting out for now - jhs507
//double F_i; varible is unreferenced commenting out for now - jhs507
//double lam_i; varible is unreferenced commenting out for now - jhs507

    Minerals = 1.0 - Porosity_lay[nn][hh] - Organic_lay[nn][hh];
    if (Minerals < 0.0) Minerals = 0.0;
    Air = Porosity_lay[nn][hh] - Soil_Water_lay[nn][hh] - Soil_Ice_lay[nn][hh];
    if(Air < 0.0) Air = 0.0;
//    Rho_Soil = BulkDensity_lay[nn][hh] / (1.0 - Porosity_lay[nn][hh]);
    Sr = (Soil_Water_lay[nn][hh] + Soil_Ice_lay[nn][hh])/Porosity_lay[nn][hh];

	switch(Method_ID[hh]) {
        case 1:               //Johansen Complete
            if(Soil_Temp < -0.5)    // frozen soil
                KersNumber = Sr;
            else if(Organic_lay[nn][hh] > Minerals)
                KersNumber = Sr*Sr;
            else
                KersNumber = 0.7*log10(Sr)+1.0; //coarse mineral soil
//              KersNumber = 1.0*log10(Sr)+1.0; //fine mineral soil

            SoilSatCond = pow(K_Organic, Organic_lay[nn][hh])*pow(K_Minerals, Minerals)*pow(K_Ice, Soil_Ice_lay[nn][hh])
                *pow(K_Water,(Soil_Water_lay[nn][hh] + Air));
            if(Organic_lay[nn][hh] > Minerals) {
                if(Soil_Temp > -0.5)
                 SoilDryCond = 0.05;
                else
                 SoilDryCond = 0.55;
                }
            else
                 SoilDryCond = (0.135*BulkDensity_lay[nn][hh] + 64.7)/(2700.0 - 0.947*BulkDensity_lay[nn][hh]);

            if(Soil_Temp < -0.5 && Organic_lay[nn][hh] > Minerals)
                C_K0[hh] = SoilDryCond*pow((SoilSatCond/SoilDryCond), KersNumber);
            else
                C_K0[hh] = KersNumber*(SoilSatCond - SoilDryCond) + SoilDryCond;
        break;
        case 2:   //Johansen  common
            KersNumber = Sr; //TDSA
            SoilSatCond = pow(K_Organic, Organic_lay[nn][hh]) * pow(K_Minerals, Minerals)*pow(K_Ice, Soil_Ice_lay[nn][hh])
                *pow(K_Water,(Soil_Water_lay[nn][hh] + Air));
            SoilDryCond = (0.135*BulkDensity_lay[nn][hh] + 64.7)/(2700.-0.947*BulkDensity_lay[nn][hh]);
            C_K0[hh] = KersNumber*(SoilSatCond - SoilDryCond)  + SoilDryCond;
        break;
        case 3:   //De Vries as Hayashi,2007
            if(Soil_Ice_lay[nn][hh] < 0.01)   {  // Ice free
                lam_a =  K_Air;
                x_a = Air;
                x_w = Soil_Water_lay[nn][hh] + Soil_Ice_lay[nn][hh];
            }
            else {      // Mostly Ice
                lam_a =  K_Ice;
                x_a = Soil_Ice_lay[nn][hh];
                x_w = Soil_Water_lay[nn][hh];
            }
            lam_w =  K_Water;
            x_s = 1.0 - Porosity_lay[nn][hh];
            if (Minerals < 0.1)     //Organic Soil
                lam_s = K_Organic;
            else if (Organic_lay[nn][hh] < 0.1 ) //Minreal Soil
                lam_s = K_Minerals;
            else   //mixed
                lam_s = (Minerals*K_Minerals + Organic_lay[nn][hh]*K_Organic)/x_s;

            g_a = 0.333 - x_a/Porosity[hh]*(0.333-0.035);
            g_c = 1.0 - 2.0 * g_a;
            F_a = 1.0/3.0*(2.0/(1.0+(lam_a/lam_w-1.0)*g_a) + 1.0/(1.0+(lam_a/lam_w-1.0)*g_c));
            F_s = 1.0/3.0*(2.0/(1.0+(lam_s/lam_w-1.0)*g_a) + 1.0/(1.0+(lam_s/lam_w-1.0)*g_c));
            C_K0[hh] = (x_w*lam_w+F_a*x_a*lam_a+F_s*x_s*lam_s) /(x_w+F_a*x_a+F_s*x_s);
            break;
          case 4:   //De Vries as Farouki, 1986_three soil materials used: Air, water and soild

            x_a = Air;
            x_w = Soil_Water_lay[nn][hh];
            x_s = 1.0-Porosity_lay[nn][hh] + Soil_Ice_lay[nn][hh];

            lam_w =  K_Water;
            if (x_w > 0.09)
                 lam_a =  K_Air + 0.0238*exp(0.0536*Soil_Temp); //estimated from fig. 91 in Farouki 1986.
            else
                 lam_a = (0.0615+1.96*x_w)*0.418; //from Farouki 1986 pp110.
            lam_s = pow(K_Organic, Organic_lay[nn][hh]/x_s) * pow(K_Minerals, Minerals/x_s)*pow(K_Ice, Soil_Ice_lay[nn][hh]/x_s);
            if(x_w > 0.09)
                g_a = 0.333- x_a/Porosity[hh]*(0.333-0.035);
            else
                g_a = 0.013+0.944*x_w;

            g_c = 1.0 - 2.0 * g_a;
            F_a = 1.0/3.0*(2.0/(1.0+(lam_a/lam_w-1.0)*g_a) + 1.0/(1.0+(lam_a/lam_w-1.0)*g_c));
            F_s = 1.0/3.0*(2.0/(1.0+(lam_s/lam_w-1.0)*0.125) + 1.0/(1.0+(lam_s/lam_w-1.0)*0.75));
            C_K0[hh] = (x_w*lam_w+F_a*x_a*lam_a+F_s*x_s*lam_s) /(x_w+F_a*x_a+F_s*x_s);
            break;
          case 5:   //Chad

            Get_Heat_Chad(nn);
        }
}
