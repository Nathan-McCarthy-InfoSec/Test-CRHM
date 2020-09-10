//created by Manishankar Mondal

#include "ClassSnobalBase.h"

class ClassSnobalCRHM : public ClassSnobalBase {

    public:

    ClassSnobalCRHM(string Name, string Version = "undefined", CRHM::LMODULE Lvl = CRHM::PROTO) : ClassSnobalBase(Name, Version, Lvl) {};

    ClassSnobalCRHM* klone(string name) const;

    float Qsi_;
    float Qli_;

// Observations

    const float *Qsi; // incoming solar radiation (W/m^2)
    const float *Qli; // incoming longwave (thermal) rad (W/m^2) long
    const float *T_g_Obs; // ground temperature at depth
    const float *F_g_Obs; // ground flux at depth

// variable climate-data inputs

    const float  *T_a_X;      // air temp (C) hru_t
    const float  *T_pp_X;       // precip temp (C) hru_t
    const float  *e_a_X;      // vapor pressure (Pa) hru_ea
    const float  *u_X;        // wind speed (m/sec)  hru_u
    const float  *Albedo;     // albedo ()
    const float  *Qsisn_Var;  // short wave at snow surface
    const float  *QsiS_Var;  // short wave at snow surface from Slope_Qsi
    const float  *Qlisn_Var;  // long wave at snow surface - through canopy
    const float  *QliVt_Var;  // long wave at snow surface - no canopy

// variable precipitation inputs

    const float  *m_precip_X;	// specific mass of total precip     (kg/m^2) net_p
    const float  *m_snow_X;	// specific mass in snow in precip   (kg/m^2) net_snow
    const float  *m_drift_X;	// specific mass in snow drift       (kg/m^2) Drift
    const float  *m_subl_X;	// specific mass of snow sublimation (kg/m^2) Subl

// put variable precipitation inputs

    float  *m_rain_X;	// specific mass of rain in precip   (kg/m^2) net_rain

// parameters

    const float  *rho_snow_X;       // density of snowfall               (kg/m^3)
    const float  *T_g_X;            // soil temp at depth z_g (C)
    const float  *F_g_X;            // soil flux at depth z_g (C)
    const long   *rain_soil_snow;  //
    float *snow_store; // accumulates snow till > 1+mm

    void decl(void);

    void init(void);

    void run(void);

    void finish(bool good); // delete local storage used
};