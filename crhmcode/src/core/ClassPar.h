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
#pragma once

#ifndef CLASSPAR
#define CLASSPAR

#include "ClassCRHM.h"

using namespace std;

class parser;

class ClassPar {
public:
	string module;
	string param;
	string basemodule;
	string help;
	string units;

	TVar varType;
	TDim dimen{ TDim::NDEFNZ };

	long dim;
	long lay{ 0 };
	long variation_set{ 0 };

	double* values;
	long* ivalues;

	double** layvalues;
	long** ilayvalues;

	string valstr;
	double minVal{ 0.0 };
	double maxVal{ 0.0 };

	std::vector<std::string> * Strings{ NULL };
	std::vector<std::string> * StringsBkup{ NULL };

	TVISIBLE visibility{ TVISIBLE::USUAL };

	long Inhibit_share; // 0 - shared, 1 - linked to declparam, 2 - declputparam unlinked

						// backup storage

	double** layvaluesBkup{ NULL };
	long** ilayvaluesBkup{ NULL };

	ClassPar* Identical;

	

	ClassPar(string module = "none", string param = "none") : 
		module(module), 
		param(param), 
		dim(0), 
		visibility(TVISIBLE::USUAL), 
		variation_set(0), 
		varType(TVar::none),
		values(NULL), 
		ivalues(NULL), 
		layvalues(NULL), 
		ilayvalues(NULL), 
		Identical(NULL), 
		Inhibit_share(0) 
	{};

	ClassPar(string module, string param, TDim dimen, string CommaText, string help, TVar varType, int Grpdim);

	ClassPar(
		string module, 
		string param, 
		TDim dimen, 
		string valstr, 
		double minVal, 
		double maxVal,
		string help, 
		string units, 
		TVar varType, 
		int defdim = 0, 
		int GrpN = 0
	);

	ClassPar(ClassPar& p);  // copy constructor

	double& operator[](int ii) { return values[ii]; }

	virtual  ~ClassPar();

	bool Same(ClassPar& p);  // compares parameter data

	void Change(ClassPar& p);  // changes this values to p

	virtual string UserName(void) { return module + ' ' + param; };

	friend class ::parser;

	void ExpandShrink(long new_dim);

	void BackUp(void);

	void Restore(void);

	long GetUnit(void);

	/**
	* Checks if two parameters are consolidation candidates 
	* 
	* Parameters are consolidation candidates if they have the following properties
	*    they have the same name, 
	*    they have the same dimensions, 
	*    they have the same type, 
	*    they DO NOT have the same values. 
	* 
	* @param leftParameter - ClassPar* pointer to a parameter
	* @param rightParameter - ClassPar* pointer to a parameter
	* @return bool - true if leftParameter and rightPrameter are consolidation candidates
	*/
	static bool ConsolidationCandidates(ClassPar * leftParameter, ClassPar * rightParameter);

};

#endif // !CLASSPAR
