#include "../../core/ClassModule.h"
#include "WQ_CRHM.h"

#ifndef CLASSSED_SOILX
#define CLASSSED_SOILX

class ClassSed_SoilX : public ClassModule {
public:

ClassSed_SoilX(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long snowinfilDiv{0};
long meltrunoffDiv{0};
long runoffDiv{0};
long evapDiv{0};

// Added for XG
long depths_size{0}; // handles recharge and lower layers

// declared observation variables

// declared variables
long *current_getstep{ NULL };

/* Added for snow cover fraction */
double* scf{ NULL };

double *Sd{ NULL };
double* Sd_conc{ NULL };
double** Sd_conc_lay{ NULL };

double *gw{ NULL };
double* gw_conc{ NULL };
double** gw_conc_lay{ NULL };

double *soil_rechr{ NULL };
double* soil_rechr_conc{ NULL };
double** soil_rechr_conc_lay{ NULL };
double* conc_soil_rechr{ NULL };
double** conc_soil_rechr_lay{ NULL };

double *soil_moist{ NULL };
double* soil_moist_conc{ NULL };
double** soil_moist_conc_lay{ NULL };
double* conc_soil_moist{ NULL };
double** conc_soil_moist_lay{ NULL };

double* soil_lower{ NULL };
double* soil_lower_conc{ NULL };
double** soil_lower_conc_lay{ NULL };
double* conc_soil_lower{ NULL };
double** conc_soil_lower_lay{ NULL };

double *soil_gw{ NULL };
double* soil_gw_conc{ NULL };
double** soil_gw_conc_lay{ NULL };

double *Sd_gw{ NULL };
double *gw_flow{ NULL };

double *soil_ssr{ NULL };
double* soil_ssr_conc{ NULL };
double** soil_ssr_conc_lay{ NULL };

double *rechr_ssr{ NULL };
double* rechr_ssr_conc{ NULL };
double** rechr_ssr_conc_lay{ NULL };

double *soil_runoff{ NULL };
double* soil_runoff_cWQ{ NULL };
double** soil_runoff_cWQ_lay{ NULL };

double *cum_soil_ssr{ NULL };
double *cum_rechr_ssr{ NULL };
double *cum_soil_runoff{ NULL };
double *cum_runoff_to_Sd{ NULL };
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
double* redirected_residual_conc{ NULL };
double** redirected_residual_conc_lay{ NULL };
double *cum_redirected_residual{ NULL };

double *infil_act{ NULL };
double *cum_infil_act{ NULL };
double *infil_act_D{ NULL };

double *soil_runoff_stream{ NULL };
double *weir_outflow{ NULL };
double *weir_outflow_m3s{ NULL };
double *weir_water_A{ NULL };
double *weir_water_V{ NULL };
double *weir_water_h{ NULL };
double *weir_evap{ NULL };
double *cum_weir_over_m3{ NULL };
double *weir_crest_volume{ NULL };
double *stream{ NULL };
double *stream_to_Sd{ NULL };
double *cum_stream{ NULL };
double *stream_Grp_in{ NULL };
double *stream_Grp_loss{ NULL };
double *cum_stream_Grp_loss{ NULL };

// local variables
double *cum_soil_gw{ NULL };
double *cum_Sd_gw{ NULL };
double *cum_gw_flow{ NULL };
double *cum_hru_condense{ NULL };
double *cum_Sd_evap{ NULL };
double *soil_moist_Init{ NULL };
double *soil_rechr_Init{ NULL };
double *Sd_Init{ NULL };
double *gw_Init{ NULL };
double *SWE_Init{ NULL };

double *snowinfil_buf{ NULL };
double *runoff_buf{ NULL };
double *meltrunoff_buf{ NULL };
double *hru_evap_buf{ NULL };

// vvvvvvvvvv  Added for XG

double *thaw_layers{ NULL };
double **thaw_layers_lay{ NULL };
double *depth_layers{ NULL };
double **depth_layers_lay{ NULL };
double *thaw_all{ NULL };

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

/* Added for snow cover fraction */
const double* CV_SWE{ NULL };

const double *side_slope{ NULL };
const double *culvert_diam{ NULL };
const double *culvert_water_Dmax{ NULL };
const double *number_culverts{ NULL };

// vvvvvvvvvv  Added for XG

	const double *porosity_upper{ NULL };
	const double *porosity_lower{ NULL };
	const double *evap_from_runoff{ NULL };

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

const double *weir_crest{ NULL };
const double *weir_coefficient{ NULL };
const double *weir_mult{ NULL };
const double *weir_b{ NULL };
const double *lake_mult{ NULL };
const double *lake_power{ NULL };
const double *lake_p{ NULL };
const double *lake_S{ NULL };
const double *runoff_stream{ NULL };
const double *stream_runoff{ NULL };
const double *stream_Sd{ NULL };
const double *Wetlands_scaling_factor{ NULL };    // temporary modification

const long *culvert_type{ NULL };
const long *cov_type{ NULL };
const long *transp_limited{ NULL };
const long *soil_ssr_runoff{ NULL };

// vvvvvvvvvv  Added for XG

	const long *NO_Freeze{ NULL };

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

const long *inhibit_evap{ NULL };
const long *soil_withdrawal{ NULL };
const long **soil_withdrawal_Tables{ NULL };

// variable inputs
const double *infil{ NULL };
const double *snowinfil{ NULL };
const double *meltrunoff{ NULL }; // frozen melt runoff
const double *runoff{ NULL };     // liquid runoff
const double *hru_evap{ NULL };

// vvvvvvvvvv  Added for XG

const double *Zdt{ NULL };
const double *Zdf{ NULL };
const double *Zd_front{ NULL };
const double **Zd_front_array{ NULL };

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/* Added for snow cover fraction */
const double* SWE{ NULL };
const double* SWE_max{ NULL };

const double *SD{ NULL };

// variable put inputs
double *hru_actet{ NULL };      // [nhru]
double *hru_cum_actet{ NULL };


// local allocated arrays

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassSed_SoilX* klone(string name) const;
};

#endif