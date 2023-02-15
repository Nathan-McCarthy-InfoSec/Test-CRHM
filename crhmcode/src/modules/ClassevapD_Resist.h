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

#include "../core/ClassModule.h"

class ClassevapD_Resist : public ClassModule {
public:

ClassevapD_Resist(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long QsiCnt {0};
long TsCnt {0};

// declared variables
double *hru_actet { NULL };
double *hru_cum_actet { NULL };
double *evapD { NULL };
double *cum_evap { NULL };
double *rc { NULL };

// local allocated arrays
double *Pa { NULL };

// declared parameters
const double *basin_area { NULL };   // [BASIN]
const double *hru_area { NULL };
const double *Ht { NULL };
const double *Htmax { NULL };
const double *Zwind { NULL };
const double *hru_elev { NULL };
const double *F_Qg { NULL };
const double *rcs { NULL };
const double *LAImax { NULL };
const double *LAImin { NULL };
const double *soil_Depth { NULL };

const long *evap_type { NULL };
const long *inhibit_evap { NULL };
const long *soil_type { NULL };
const double *s { NULL };
const long *PM_method { NULL };

// variable inputs
const double *RnD { NULL };
const double *hru_tmean { NULL };
const double *hru_umean { NULL };
const double *hru_eamean { NULL };
const double *soil_moist { NULL };

// declared observations variable
const double *Qsi{ NULL };
const double *Ts{ NULL };

// declared observation functions
double *Qsi_mean { NULL };
double *Tsmean { NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassevapD_Resist* klone(string name) const;

double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double fdaily(double u, double Ht);        // Drying power f(u) - interval
};
