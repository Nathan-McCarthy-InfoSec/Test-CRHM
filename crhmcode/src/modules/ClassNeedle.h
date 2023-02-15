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

class ClassNeedle : public ClassModule {

    public:

    ClassNeedle(string Name, string Version = "undefined", LMODULE Lvl = LMODULE::PROTO) : ClassModule(Name, Version, Lvl, 1000, " , QliVt_Var, QsiS_Var, QsiS_Var, QsiA_Var") {};

    double Qli_ {0.0};

    double Qsi_ {0.0};

// declared observations

    double *Ts{ NULL };

    double *Qnsn{ NULL };

    double *Qsisn{ NULL };

    double *Qlisn{ NULL };

    double *Qlosn{ NULL };

// declared observation variables

    const double *Qsi{ NULL };

    const double *Qli{ NULL };

    const double *QsiA_Var{ NULL };

    const double *QsiS_Var{ NULL };

    const double *QliVt_Var{ NULL };

// declared variables

   double *Pa{ NULL };

   double *k{ NULL };

   double *Tauc{ NULL };

   double *ra{ NULL };

   double *Qnsn_Var{ NULL };

// declared parameters

   const double *LAI{ NULL };

   const double *Ht{ NULL };

   const double *Zwind{ NULL };

   const double *Zref{ NULL };

   const double *hru_elev{ NULL };

   const double *Z0snow{ NULL }; // snow roughness length (m)


// variable inputs

    const double *beta{ NULL };

    const double *SWE{ NULL };

    const double *Albedo{ NULL };

    const double *hru_t{ NULL };

    const double *hru_u{ NULL };

    const double *hru_ea{ NULL };

    const double *hru_rh{ NULL };


    void decl(void);

    void init(void);

    void run(void);

ClassNeedle* klone(string name) const;
};
