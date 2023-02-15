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
#include "Defdeclstatvar.h"

Defdeclstatvar::Defdeclstatvar(ClassMacro* Macro_) : DefCRHM(Macro_) {
	name = DefStringList->at(1);
	Dim = getTDim(DefStringList->at(2));
	Description = DefStringList->at(3);
	Units = DefStringList->at(4);

	if (DefCRHM::DefStringList->size() > 5 && DefStringList->at(5) == "Int")
	{
		Int = true;
	}
	else
	{
		Int = false;
	}
}

void Defdeclstatvar::CallDecl() {

	if (Int)
		Macro->declstatvar(name, Dim, Description, Units, &fix_long);
	else
		Macro->declstatvar(name, Dim, Description, Units, &fix);

	FP = Macro->vars.find(name);
	if (FP == Macro->vars.end()) {
		Macro->vars.insert(make_pair(name, VarCHRM()));
		FP = Macro->vars.find(name);
	}

	FP->second.name = name;
	FP->second.Ihh = 0;
	FP->second.Ill = 0;
	FP->second.IndexMax = Global::nhru - 1;
	FP->second.IndexMaxLay = Macro->nhru - 1; // FIX *******
	FP->second.Me = Macro;

	if (Int) {
		FP->second.kind = TV::CRHMint;
		FP->second.ivalue = const_cast<long*> (fix_long);
	}
	else if (Dim == TDim::NDEF || Dim == TDim::NDEFN) {
		FP->second.value2 = fix2;
		FP->second.kind = TV::CRHM2;
	}
	else {
		FP->second.kind = TV::CRHM;
		FP->second.value = fix;
	}
}


void Defdeclstatvar::CallInit(long nhru, long nlay) {
	FP->second.IndexMax = nhru - 1;
	for (int hh = 0; hh <= FP->second.IndexMax; ++hh) {
		FP->second.Ihh = hh;
		FP->second.put(0.0);
	}
}