//created by Manishankar Mondal

#include "Classcalcsun.h"
#include "GlobalDll.h"
#include <algorithm>
#include "ClassCRHM.h"

#include "SnobalDefines.h"
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

using namespace CRHM;

Classcalcsun* Classcalcsun::klone(string name) const{
  return new Classcalcsun(name);
}

void Classcalcsun::decl(void) {

  Description = "'Calculates sunshine hours to replace field data', \
                 'Use actual sunshine hours or estimate from Qsi(W/m^2) when sunshine hours not available', \
                 'Use input Qsi (W/m^2) to estimate sunshine hours,' \
                 'Use input daily short-wave radiation observation(QsiD_Obs (W/m^2)), ' \
                 'Use input daily short-wave radiation variable (QsiD_Var (W/m^2)).'";

  variation_set = VARIATION_0;

  declreadobs("SunAct", NHRU, "sunshine hours", "(h)", &SunAct, HRU_OBS_Q, true); // must check for NULL


  variation_set = VARIATION_0 + VARIATION_1;

  declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, true); // must check for NULL

  declobsfunc("Qsi", "Qsitot", &Qsitot, DTOT, NULL, true); // must check for NULL

  variation_set = VARIATION_2;

  declreadobs("QsiD_Obs", NHRU, "daily short-wave", "(W/m^2)", &QsiD_Obs, HRU_OBS_Q);


  variation_set = VARIATION_3;

  declgetvar("*", "QsiD_Var", "(W/m^2)", &QsiD_Var);


  variation_set = VARIATION_ORG;

  declgetvar("*", "QdflatD", "(MJ/m^2*d)", &QdflatD);
  declgetvar("*", "QdfoD",   "(MJ/m^2*d)", &QdfoD);
  declgetvar("*", "SunMax",  "(h)", &SunMax);

  declvar("hru_SunAct", NHRU, "Actual Sunshine", "(h)", &hru_SunAct);
}

void Classcalcsun::init(void) {
  nhru = getdim(NHRU);

      switch(variation) {

      case VARIATION_ORG:
        if(SunAct == NULL){
          CRHMException TExcept(string("'" + Name + " (calcsun)' sunshine hours observation missing. Using Qsi instead.").c_str(), WARNING);
          LogError(TExcept);

          if(Qsi == NULL || Qsitot == NULL){
            CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TERMINATE);
            LogError(TExcept);
          }
        }
      break;

      case VARIATION_1:
        if(Qsi == NULL || Qsitot == NULL) {
          CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TERMINATE);
          LogError(TExcept);
        }
      break;

      case VARIATION_2:
        if(QsiD_Obs == NULL) {
          CRHMException TExcept(string("'" + Name + " (calcsun)' QsiD_Obs daily observation missing.").c_str(), TERMINATE);
          LogError(TExcept);
        }
  } // switch
}

void Classcalcsun::run(void) {
double Temp, Ratio;

  long nstep = getstep() % Global::Freq;

  if(nstep == 1 || Global::Freq == 1) { // beginning of every day

    for (hh = 0; chkStruct(); ++hh) {

      switch(variation) {

      case VARIATION_ORG:
        if(SunAct){
          hru_SunAct[hh] = SunAct[hh];
          Temp = -9999;
          break;
        }
// fall through
      case VARIATION_1:
        Temp =  Qsitot[hh]*WtoMJ_D/Global::Freq - QdfoD[hh]; // observed direct incoming  - QdfoD[hh]
        break;

      case VARIATION_2:
        Temp =  QsiD_Obs[hh]*WtoMJ_D - QdfoD[hh]; // observed daily direct incoming  - QdfoD[hh]
        break;

      case VARIATION_3:
        Temp =  QsiD_Var[hh]*WtoMJ_D - QdfoD[hh]; // variable daily direct incoming  - QdfoD[hh]
        break;

      default :
        CRHMException TExcept(string("'" + Name + " (variation)' 'variation not defined.").c_str(), TERMINATE);
        LogError(TExcept);
      } // switch

      if(Temp != -9999){
        if(Temp <= 0.0 || QdflatD[hh] - QdfoD[hh] <= 0.0)
          Ratio = 0.0;
        else{
          Ratio = Temp/(QdflatD[hh] - QdfoD[hh]); // incoming clear sky direct only
          if(Ratio > 1.0)
            Ratio = 1.0;
        }
        hru_SunAct[hh] = Ratio*SunMax[hh];
      }
    } // for
  } // beginning of every day
}