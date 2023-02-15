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

class ClassSoilX : public ClassModule {
public:

ClassSoilX(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv{0};
long meltrunoffDiv{0};
long runoffDiv{0};
long evapDiv{0};
long depths_size{0}; // handles recharge and lower layers

// declared observation variables

// declared variables
double *Sd{ NULL };
double *gw{ NULL };
double *soil_rechr{ NULL };
double *soil_moist{ NULL };
double *soil_gw{ NULL };
double *gw_flow{ NULL };
double *soil_ssr{ NULL };
double *rechr_ssr{ NULL };
double *soil_runoff{ NULL };
double *cum_soil_ssr{ NULL };
double *cum_rechr_ssr{ NULL };
double *cum_soil_runoff{ NULL };
double *cum_runoff_to_Sd{ NULL };
double *cum_redirected_residual{ NULL };
double *soil_gw_D{ NULL };
double *soil_ssr_D{ NULL };
double *gw_flow_D{ NULL };
double *soil_runoff_D{ NULL };
double *HK_V{ NULL };
double *HK_A{ NULL };
double *culvert_Q{ NULL };
double *culvert_water_H{ NULL };
double *culvert_water_A{ NULL };
double *culvert_water_V{ NULL };
double *culvert_over_Q{ NULL };
double *culvert_evap{ NULL };
double *cum_culvert{ NULL };
double *cum_culvert_over{ NULL };
double *HD{ NULL };
double *redirected_residual{ NULL };
double *infil_act{ NULL };
double *cum_infil_act{ NULL };
double *infil_act_D{ NULL };

// local variables
double *cum_soil_gw{ NULL };
double *cum_gw_flow{ NULL };
double *cum_hru_condense{ NULL };
double *soil_moist_Init{ NULL };
double *soil_rechr_Init{ NULL };
double *Sd_Init{ NULL };
double *gw_Init{ NULL };
double *SWE_Init{ NULL };
double *Dts_runoff_K{ NULL }; // from Dts_snow_runoff_K or Dts_organic_runoff_K

double *snowinfil_buf{ NULL };
double *runoff_buf{ NULL };
double *meltrunoff_buf{ NULL };
double *hru_evap_buf{ NULL };

double *thaw_layers{ NULL };
double **thaw_layers_lay{ NULL };
double *depth_layers{ NULL };
double **depth_layers_lay{ NULL };
double *thaw_all{ NULL };

// declared parameters
const double *Sdmax{ NULL };
const double *Sdinit{ NULL };
const double *gw_max{ NULL };
const double *gw_init{ NULL };
const double *gw_K{ NULL };
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *soil_rechr_max{ NULL };
const double *soil_rechr_init{ NULL };
const double *soil_moist_max{ NULL };
const double *soil_moist_init{ NULL };
const double *soil_gw_K{ NULL };
const double *rechr_ssr_K{ NULL };
const double *lower_ssr_K{ NULL };
const double *Sd_ssr_K{ NULL };
const double *Sd_gw_K{ NULL };
const double *channel_slope{ NULL };
const double *side_slope{ NULL };
const double *culvert_diam{ NULL };
const double *culvert_water_Dmax{ NULL };
const double *number_culverts{ NULL };
const double *porosity_upper{ NULL };
const double *porosity_lower{ NULL };
const double *evap_from_runoff{ NULL };
const double *Dts_snow_max{ NULL };
const double *Dts_organic_max{ NULL };
const double *Dts_snow_init{ NULL };
const double *Dts_snow_runoff_K{ NULL };
const double *Dts_organic_runoff_K{ NULL };
const double *Dts_organic_init{ NULL };
const long *soil_withdrawal{ NULL };
const long **soil_withdrawal_Tables{ NULL };

const long *culvert_type{ NULL };
const long *cov_type{ NULL };
const long *transp_limited{ NULL };
const long *soil_ssr_runoff{ NULL };
const long *NO_Freeze{ NULL };
const long *inhibit_evap{ NULL };

// variable inputs
const double *infil{ NULL };
const double *snowinfil{ NULL };
const double *meltrunoff{ NULL }; // frozen melt runoff
const double *runoff{ NULL };     // liquid runoff
const double *hru_evap{ NULL };
const double *Zdt{ NULL };
const double *Zdf{ NULL };
const double *Zd_front{ NULL };
const double **Zd_front_array{ NULL };

double *Dts{ NULL };
double *Dts_max{ NULL };

// variable put inputs
double *hru_actet{ NULL };      // [nhru]
double *hru_cum_actet{ NULL };


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSoilX* klone(string name) const;
};
