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

/* 
 * This modules implements the representative elementary watershed channel connection
 * with water quality metrics.
 */

#include "WQ_CRHM.h"

class ClassWQ_REWroute : public ClassModule {
public:

ClassWQ_REWroute(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 9999) {};

long inflowCnt{0};
long inflowConcCnt{0};
long gwCnt{0};

// declared variables
double *rew{ NULL };
double *rew_conc{ NULL };
double *gwrew{ NULL };

double **inflow_All{ NULL };
double **inflow_conc_All{ NULL };
double **gw_All{ NULL };

double *inflow{ NULL };        // [nhru]
double *inflow_mWQ{ NULL };       // [ndefn]
double **inflow_mWQ_lay{ NULL };       // [ndefn]
double *cuminflow{ NULL };     // [nhru]
double *outflow{ NULL };       // [nhru]
double *outflow_mWQ{ NULL };       // [ndefn]
double **outflow_mWQ_lay{ NULL };       // [ndefn]
double *outflow_cWQ{ NULL };       // [ndefn]
double **outflow_cWQ_lay{ NULL };       // [ndefn]
double *cumoutflow{ NULL };    // [nhru]

double *gwinflow{ NULL };        // [nhru]
double *cumgwinflow{ NULL };     // [nhru]
double *gwoutflow{ NULL };       // [nhru]
double *cumgwoutflow{ NULL };    // [nhru]

double *flow{ NULL };     // [BASIN] all HRUs
double *flow_s{ NULL };   // [BASIN] all HRUs
double *cumflow{ NULL };  // [BASIN] all HRUs

double *gwflow{ NULL };     // [BASIN] all HRUs
double *gwflow_s{ NULL };   // [BASIN] all HRUs
double *cumgwflow{ NULL };  // [BASIN] all HRUs

double *WS_Ktravel_var{ NULL };         // [nhru]
double *WS_gwKtravel_var{ NULL };         // [nhru]

double *culvert_Q{ NULL };
double *culvert_water_H{ NULL };
double *culvert_water_A{ NULL };
double *culvert_water_V{ NULL };
double *culvert_water_O{ NULL };
double *culvert_evap{ NULL };
double *cum_culvert{ NULL };
double *cum_culvert_over{ NULL };
double *HD{ NULL };

ClassMuskingum *inflowDelay{ NULL };
ClassMuskingum *gwDelay{ NULL };

ClassMuskingum **inflowDelay_mWQ{ NULL };
ClassMuskingum **gwDelay_mWQ{ NULL };

ClassClark *Clark_inflowDelay{ NULL };
ClassClark *Clark_gwDelay{ NULL };

ClassClark **Clark_inflowDelay_mWQ{ NULL };
ClassClark **Clark_gwDelay_mWQ{ NULL };

// declared parameters

const double *WS_route_n{ NULL };         // [nhru]
const double *WS_route_R{ NULL };         // [nhru]
const double *WS_route_S0{ NULL };        // [nhru]
const double *WS_route_L{ NULL };         // [nhru]
const long  *WS_Channel_shp{ NULL };      // [nhru]

const double *WS_Lag{ NULL };             // [nhru]
const double *WS_route_X_M{ NULL };       // [nhru]
const long  *WS_whereto{ NULL };         // [nhru]
const long  *WS_order{ NULL };           // [nhru]

const double *WS_gwLag{ NULL };           // [nhru]
const double *WS_gwroute_X_M{ NULL };     // [nhru]
const long  *WS_gwwhereto{ NULL };       // [nhru]
const long  *WS_gworder{ NULL };         // [nhru]

const double *WS_Kstorage{ NULL };     // [nhru]
const double *WS_gwKstorage{ NULL };   // [nhru]

const double *WS_channel_slope{ NULL };
const double *WS_side_slope{ NULL };
const double *WS_culvert_diam{ NULL };
const double *WS_culvert_water_Dmax{ NULL };
const double *WS_number_culverts{ NULL };

const long *WS_culvert_type{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);
void Culvert(long hh);

void Reset_WQ(long hru, double* var, double** var_conc_lay);

ClassWQ_REWroute* klone(string name) const;
};
