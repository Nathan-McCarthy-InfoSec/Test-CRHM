//created by Manishankar Mondal

#include "../../core/ClassModule/ClassModule.h"

class ClassShutWallD : public ClassModule {
public:

ClassShutWallD(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl) {};

long Qn_Cnt{0};
long Qg_Cnt{0};

// declared variables
double *hru_actet{ NULL };
double *hru_cum_actet{ NULL };
double *evapD{ NULL };
double *cum_evap{ NULL };
double *Cc{ NULL };
double *Cs{ NULL };
double *Ra{ NULL };
double *Rc{ NULL };
double *Rs{ NULL };
double *ETc{ NULL };
double *ETs{ NULL };
double *raa{ NULL };
double *rca{ NULL };
double *rcs{ NULL };
double *rsa{ NULL };
double *rss{ NULL };

// declared parameters
const double *basin_area{ NULL };   // [BASIN]
const double *hru_area{ NULL };
const double *rs{ NULL };
const double *hru_elev{ NULL };
const double *Cr{ NULL };
const double *LAI{ NULL };
const double *Ht{ NULL };
const double *Zwind{ NULL };
const double *w{ NULL };
const double *rst{ NULL };
const double *z0g{ NULL };
const double *gammab{ NULL };

const long *inhibit_evap{ NULL };

// declared observations
const double *hru_umean{ NULL };
const double *hru_tmean{ NULL };
const double *hru_eamean{ NULL };
const double *Qn{ NULL };
const double *Qg{ NULL };

// declared observation functions
double *Qnmean{ NULL };
double *Qgmean{ NULL };

// variable inputs

// local allocated arrays
double *Pa{ NULL };

void decl(void);
void init(void);
void run(void);
void finish(bool good);

ClassShutWallD* klone(string name) const;

double RHOa(double t, double ea, double Pa); // atmospheric density (kg/m^3)
double gamma(double Pa, double t);         // Psychrometric constant
double lambda(double t);                   // Latent heat of vaporization
double delta(double t);                   // Slope of sat vap p vs t, kPa/DEGREE_CELSIUS
};