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
#include <stdio.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <math.h>
#include <cmath>

#include "ClassPar.h"
#include "ClassCRHM.h"
#include "../modules/newmodules/NewModules.h"
#include "stddef.h"
#include "GlobalDll.h"

using namespace std;


ClassPar::ClassPar(string module, string param, TDim dimen,
	string CommaText, string help, TVar varType, int Grpdim)
	: module(module), basemodule(""), param(param), varType(varType), dimen(dimen), help(help),
	units(""), valstr(""), minVal(0), maxVal(0), Inhibit_share(0),
	values(NULL), ivalues(NULL), layvalues(NULL), ilayvalues(NULL), Identical(NULL),
	layvaluesBkup(NULL), ilayvaluesBkup(NULL), lay(1) {

	if (Grpdim == 0 && dimen >= TDim::NHRU)
		Grpdim = Global::nhru;

	if (dimen < TDim::NHRU)
		dim = getdim(dimen); // handle cases of 'ONE, TWO, ...
	else
		dim = Grpdim;

	Strings = new std::vector<std::string>();
	//Strings->QuoteChar = '\'';
	Common::tokenizeString(CommaText, Strings);

	if (Strings->size() == 0) // handle case of newly added string parameter. Only handles 'BASIN'
	{
		Strings->push_back("");
	}

	if (dimen == TDim::NHRU)
	{
		for (size_t ii = Strings->size(); ii < (size_t) dim; ++ii)
		{
			Strings->push_back(Strings->at(0) + std::to_string(ii + 1));
		}
	}

}

//---------------------------------------------------------------------------
void ClassPar::ExpandShrink(long new_dim)
{

	// backup current string

	if (varType == TVar::Txt)
	{
		StringsBkup = new std::vector<std::string>(*Strings);
	}
	else if (varType == TVar::Float)
	{
		layvaluesBkup = new double* [lay];
		for (int ii = 0; ii < lay; ii++)
			layvaluesBkup[ii] = new double[dim];

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == TVar::Int)
	{
		ilayvaluesBkup = new long* [lay];
		for (int ii = 0; ii < lay; ii++)
			ilayvaluesBkup[ii] = new long[dim];

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
	}

	// delete current arrays

	if (varType == TVar::Float) {
		for (int ii = 0; ii < lay; ++ii) delete[] layvalues[ii];

		delete[] layvalues;  //Array [nhru] [lay]
		values = NULL;
	}
	else if (varType == TVar::Int) {
		for (int ii = 0; ii < lay; ++ii) delete[] ilayvalues[ii];

		delete[] ilayvalues; //Array [nhru] [lay]
		ilayvalues = NULL;
		ivalues = NULL;
	}
	else if (varType == TVar::Txt)
	{
		Strings->clear();
	}

	// allocate new memory

	long lay0 = lay;
	long dim0 = dim;

	dim = new_dim;

	if (dimen == TDim::NDEFN) // NDEFN stays the same
		lay = new_dim;

	if (varType == TVar::Float) {
		if (lay > 0) {
			layvalues = new double* [lay];
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new double[dim];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					layvalues[jj][kk] = 0.0;
		}

		values = new double[dim];
		for (int kk = 0; kk < dim; ++kk)
			values[kk] = 0.0;
	}
	else if (varType == TVar::Int) {
		if (lay > 0) {
			ilayvalues = new long* [lay];
			for (int ii = 0; ii < lay; ii++)
				ilayvalues[ii] = new long[dim];

			for (int jj = 0; jj < lay; ++jj)
				for (int kk = 0; kk < dim; ++kk)
					ilayvalues[jj][kk] = (int)0.0;
		}

		ivalues = new long[dim];
		for (int kk = 0; kk < dim; ++kk)
			ivalues[kk] = 0;
	}
	else if (varType == TVar::Txt)
	{
		Strings->clear();
	}

	// copy data into expanded/shrunk array

	if (varType == TVar::Txt)
	{
		if (StringsBkup->size() > 0)
		{
			for (int kk = 0; kk < dim; ++kk)
			{
				Strings->push_back(StringsBkup->at(min<int>(kk, dim0 - 1)) + "");
			}
			delete StringsBkup;
		}
		StringsBkup = NULL;
	}
	else if (varType == TVar::Float)
	{
		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				layvalues[jj][ii] = layvaluesBkup[min<int>(jj, lay0 - 1)][min<int>(ii, dim0 - 1)];

		for (int ii = 0; ii < lay0; ++ii)
			delete[] layvaluesBkup[ii];
		delete[] layvaluesBkup;  //Array [nhru] [lay]
		layvaluesBkup = NULL;
	}
	else if (varType == TVar::Int) {

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				ilayvalues[jj][ii] = ilayvaluesBkup[min<int>(jj, lay0 - 1)][min<int>(ii, dim0 - 1)];

		for (int ii = 0; ii < lay0; ++ii)
			delete[] ilayvaluesBkup[ii];
		delete[] ilayvaluesBkup; //Array [nhru] [lay]
		ilayvaluesBkup = NULL;
	}
}

//---------------------------------------------------------------------------
void ClassPar::BackUp() {

	if (varType == TVar::Txt)
	{
		StringsBkup = new std::vector<std::string>(*Strings);
	}
	else if (varType == TVar::Float)
	{
		layvaluesBkup = new double* [lay];
		for (int ii = 0; ii < lay; ii++)
			layvaluesBkup[ii] = new double[dim];

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				layvaluesBkup[jj][ii] = layvalues[jj][ii];
	}
	else if (varType == TVar::Int)
	{
		ilayvaluesBkup = new long* [lay];
		for (int ii = 0; ii < lay; ii++)
			ilayvaluesBkup[ii] = new long[dim];

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				ilayvaluesBkup[jj][ii] = ilayvalues[jj][ii];
	}
}

//---------------------------------------------------------------------------
void ClassPar::Restore()
{

	if (varType == TVar::Txt)
	{
		Strings = NULL;
		Strings = new std::vector<std::string>(*StringsBkup);
		delete StringsBkup;
		StringsBkup = NULL;
	}
	else if (varType == TVar::Float)
	{

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				layvalues[jj][ii] = layvaluesBkup[jj][ii];

		for (int ii = 0; ii < lay; ++ii)
			delete[] layvaluesBkup[ii];
		delete[] layvaluesBkup;  //Array [nhru] [lay]
		layvaluesBkup = NULL;
	}
	else if (varType == TVar::Int)
	{

		for (int jj = 0; jj < lay; jj++)
			for (int ii = 0; ii < dim; ii++)
				ilayvalues[jj][ii] = ilayvaluesBkup[jj][ii];

		for (int ii = 0; ii < lay; ++ii)
			delete[] ilayvaluesBkup[ii];
		delete[] ilayvaluesBkup; //Array [nhru] [lay]
		ilayvaluesBkup = NULL;
	}
}

//---------------------------------------------------------------------------
ClassPar::ClassPar(string module, string param, TDim dimen,
	string valstr, double minVal, double maxVal,
	string help, string units, TVar varType, int defdim, int Grpdim)
	: module(module), basemodule(""), param(param), varType(varType), dimen(dimen),
	valstr(valstr), minVal(minVal), maxVal(maxVal), Inhibit_share(0),
	help(help), units(units),
	values(NULL), ivalues(NULL),
	layvalues(NULL), ilayvalues(NULL), Strings(NULL),
	layvaluesBkup(NULL), ilayvaluesBkup(NULL), Identical(NULL), StringsBkup(NULL), lay(1) {

	if (Grpdim == 0 && dimen >= TDim::NHRU)
		Grpdim = Global::nhru;

	if (dimen == TDim::NLAY) {
		lay = Global::nlay;
		dim = Grpdim;
	}
	else if (dimen == TDim::NDEF) {
		lay = defdim;
		dim = 1; //
	}
	else if (dimen == TDim::NDEFNZ) {
		lay = defdim;
		dim = 1; // array 1 * n;
	}
	else if (dimen == TDim::NDEFN) {
		lay = defdim;
		dim = Grpdim; // Global::nhru;
	}
	else if (dimen < TDim::NHRU) {
		dim = getdim(dimen); // handle cases of 'ONE, TWO, ...
		lay = 1;
	}
	else {
		dim = Grpdim;
		lay = 1;
	}

	try {
		if (varType == TVar::Float) {
			layvalues = new double* [lay];
			for (int ii = 0; ii < lay; ii++)
				layvalues[ii] = new double[dim];
			values = layvalues[0];
		}
		else if (varType == TVar::Int) {
			ilayvalues = new long* [lay];
			for (int ii = 0; ii < lay; ii++)
				ilayvalues[ii] = new long[dim];
			ivalues = ilayvalues[0];
		}
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in ClassPar.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}
}

//---------------------------------------------------------------------------
ClassPar::ClassPar(ClassPar& p) {  // copy constructor

	module = string(p.module);
	basemodule = string(p.basemodule);
	param = string(p.param);
	units = string(p.units);
	help = string(p.help);

	varType = p.varType;
	dimen = p.dimen;

	dim = p.dim;
	lay = p.lay;
	variation_set = p.variation_set;
	visibility = p.visibility;
	Inhibit_share = p.Inhibit_share;

	valstr = string(p.valstr);
	minVal = p.minVal;
	maxVal = p.maxVal;

	layvaluesBkup = NULL;
	ilayvaluesBkup = NULL;

	Strings = NULL;
	ivalues = NULL;
	values = NULL;
	ilayvalues = NULL;
	layvalues = NULL;
	Identical = NULL;

	try
	{
		if (varType == TVar::Float)
		{
			layvalues = new double* [lay];

			for (int ii = 0; ii < lay; ii++)
			{
				layvalues[ii] = new double[dim];
			}

			values = layvalues[0];
		}
		else if (varType == TVar::Int)
		{
			ilayvalues = new long* [lay];

			for (int ii = 0; ii < lay; ii++)
			{
				ilayvalues[ii] = new long[dim];
			}

			ivalues = ilayvalues[0];
		}
		else if (varType == TVar::Txt)
		{
			Strings = new std::vector<std::string>();
		}
	}
	catch (std::bad_alloc)
	{
		CRHMException Except("Could not allocate in ClassPar.", TExcept::TERMINATE);
		LogError(Except);
		throw CRHMException(Except);
	}

	if (varType == TVar::Float)
	{
		for (int jj = 0; jj < lay; jj++)
		{
			for (int ii = 0; ii < dim; ii++)
			{
				layvalues[jj][ii] = p.layvalues[jj][ii];
			}
		}
	}
	else if (varType == TVar::Int)
	{

		if (ilayvalues != NULL)
		{
			for (int jj = 0; jj < lay; jj++)
			{
				for (int ii = 0; ii < dim; ii++)
				{
					ilayvalues[jj][ii] = p.ilayvalues[jj][ii];
				}
			}
		}
		else {
			CRHMException Except("ilayvalues array is null allocation must have failed.", TExcept::TERMINATE);
			LogError(Except);
			throw CRHMException(Except);
		}


	}
	else if (varType == TVar::Txt)
	{
		Strings = new std::vector<std::string>(*p.Strings);
	}

}

//---------------------------------------------------------------------------
bool ClassPar::Same(ClassPar& p) {  // compares parameter data

	if (varType == p.varType && dim == p.dim && param == p.param) {
		if (Inhibit_share != 0 || p.Inhibit_share != 0) // declputparam
		{
			if (Global::GroupCntTrk)
			{
				return(false);  // never share group declputparam
			}
			else
			{
				return(true); // always share simple project declputparam parameters
			}
		}
		if (dim == p.dim) {
			if (varType == TVar::Txt)
			{

				if (!Strings && !p.Strings)
				{
					return true;
				}

				if (Strings != NULL && (Strings->size() != p.Strings->size()))
				{
					return(false);
				}

				if (Strings == NULL) {
					return false;
				}
				else {
					for (size_t ii = 0; ii < Strings->size(); ++ii)
					{

						if (Strings->at(ii) != p.Strings->at(ii))
						{
							return(false);
						}

					}
				}


			}
			else
			{
				for (int jj = 0; jj < lay; ++jj)
					for (int ii = 0; ii < dim; ++ii)
						if (varType == TVar::Float) {
							if (layvalues[jj][ii] != p.layvalues[jj][ii]) return(false);
						}
						else if (varType == TVar::Int) {
							if (ilayvalues[jj][ii] != p.ilayvalues[jj][ii]) return(false);
						}
			}
			return(true);
		}
	}
	return(false);
}

//---------------------------------------------------------------------------
void ClassPar::Change(ClassPar& p) {  // changes parameter data to 'p'

	if (this == &p) return;

	if (varType == TVar::Txt)
	{
		Strings = new std::vector<std::string>(*p.Strings);

		// duplicate last field when # of HRUs increased
		while (Strings->size() < (size_t) dim && Strings->size() > 0)
		{
			Strings->push_back(Strings->at(Strings->size() - 1) + "");
		}
	}
	else
	{
		bool Bang = valstr.find("!") != string::npos;
		for (int jj = 0; jj < lay; ++jj) {
			long jj0 = min<long>(jj, p.lay - 1);
			for (int ii = 0; ii < dim; ++ii) {
				long ii0 = min<long>(ii, p.dim - 1);
				if (Bang && ii0 < ii) {
					if (varType == TVar::Float)
					{
						layvalues[jj][ii] = layvalues[jj][ii - 1] + 1;
					}
					else if (varType == TVar::Int)
					{
						ilayvalues[jj][ii] = ilayvalues[jj][ii - 1] + 1;
					}
				}
				else {
					if (varType == TVar::Float)
					{
						layvalues[jj][ii] = p.layvalues[jj0][ii0];
					}
					else if (varType == TVar::Int)
					{
						ilayvalues[jj][ii] = p.ilayvalues[jj0][ii0];
					}
				}
			}
		}
	}
}

long GetSharedUnitPar(string units) {
	const string delims("()/* \t,.-_");
	string::size_type begIdx, endIdx;
	begIdx = units.find_first_not_of(delims);

	while (begIdx != string::npos) {
		endIdx = units.find_first_of(delims, begIdx);
		if (endIdx == string::npos)
			endIdx = units.length();

		string name(units.substr(begIdx, endIdx - begIdx));

		if (name == "d")
			return Global::Freq;
		else if (name == "int")
			return 1;

		begIdx = units.find_first_not_of(delims, endIdx);
	}
	return 0; // was -1!!!!!!
}

long ClassPar::GetUnit(void) {
	return GetSharedUnitPar(units);
}

//---------------------------------------------------------------------------
ClassPar::~ClassPar()
{

	if (varType == TVar::Float)
	{
		for (int ii = 0; ii < lay; ++ii)
			delete[] layvalues[ii];

		delete[] layvalues; // Array [nhru] [lay]
		values = NULL;
	}
	else if (varType == TVar::Int)
	{
		for (int ii = 0; ii < lay; ++ii)
			delete[] ilayvalues[ii];

		delete[] ilayvalues; // Array [nhru] [lay]
		ilayvalues = NULL;
		ivalues = NULL;
	}
	else if (varType == TVar::Txt)
	{
//		for (string s : Strings)
//			delete s;
		Strings->clear();
		delete Strings;
	}
	varType = TVar::none;
}

//---------------------------------------------------------------------------
ClassPar::~ClassPar()
{

	if (varType == TVar::Float)
	{
		for (int ii = 0; ii < lay; ++ii)
			delete[] layvalues[ii];

		delete[] layvalues; // Array [nhru] [lay]
		values = NULL;
	}
	else if (varType == TVar::Int)
	{
		for (int ii = 0; ii < lay; ++ii)
			delete[] ilayvalues[ii];

		delete[] ilayvalues; // Array [nhru] [lay]
		ilayvalues = NULL;
		ivalues = NULL;
	}
	else if (varType == TVar::Txt)
	{
//		for (string s : Strings)
//			delete s;
		Strings->clear();
		delete Strings;
	}
	varType = TVar::none;
}


bool ClassPar::ConsolidationCandidates(ClassPar* leftParameter, ClassPar* rightParameter)
{

	if (leftParameter == rightParameter)
	{
		return false;
	}

	if (leftParameter->param != rightParameter->param)
	{
		return false;
	}

	if (leftParameter->dim != rightParameter->dim)
	{
		return false;
	}

	if (leftParameter->lay != rightParameter->lay)
	{
		return false;
	}

	if (leftParameter->varType != rightParameter->varType)
	{
		return false;
	}

	bool sameValues = true;

	for (long i = 0; i < leftParameter->lay; i++)
	{
		for (long j = 0; j < leftParameter->dim; j++)
		{
			if (leftParameter->varType == TVar::Float)
			{
				double leftCompare = leftParameter->layvalues[i][j];
				double rightCompare = rightParameter->layvalues[i][j];

				if (std::abs(leftCompare - rightCompare) > std::numeric_limits<double>::epsilon())
				{
					sameValues = false;
					break;
				}

			}
			else if (leftParameter->varType == TVar::Int)
			{
				long leftCompare = leftParameter->ilayvalues[i][j];
				long rightCompare = rightParameter->ilayvalues[i][j];

				if (leftCompare != rightCompare)
				{
					sameValues = false;
					break;
				}
			}
			else if (leftParameter->varType == TVar::Txt)
			{
				std::string leftCompare = leftParameter->Strings->at(i);
				std::string rightCompare = rightParameter->Strings->at(i);

				if (leftCompare != rightCompare)
				{
					sameValues = false;
					break;
				}
			}

			if (!sameValues)
			{
				break;
			}
		}
	}

	return !sameValues;
}