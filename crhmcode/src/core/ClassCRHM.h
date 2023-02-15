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
// 11/15/17
//---------------------------------------------------------------------------
#ifndef ClassCRHMH
#define ClassCRHMH
//---------------------------------------------------------------------------

#include <string>
#include <iostream>
#include <map>
#include <typeinfo>

#include "Common.h"
#include "GlobalCommon.h"
#include "ClassData.h"
#include "ClassVar.h"
#include "ClassPar.h"
#include "Classfilter.h"
#include "MacroClass.h"
#include "ClassModel.h"
#include "Tresult.h"
#include "Unit_Info.h"
#include "Multiplier_Info.h"
#include "Convert.h"

using namespace std;

enum types { DELIMITER = 1, NUMBER };

//class Classmacro; removed forward declaration - jhs507
//class parser; removed forward declaration - jhs507
//class ClassModule; removed forward declaration - jhs507

typedef unsigned long Word;
typedef int INT;

void   LogError(CRHMException Except);
void   LogError(string S, TExcept Kind);

void   LogMessage(const char *S, double V, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, double V, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, long V, TExtra Opt = TExtra::BLANK);
void   LogMessage(const char *S, TExtra Opt = TExtra::BLANK);

void   LogMessage(long hh, const char *S, double V, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, long V, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, TExtra Opt = TExtra::BLANK);

void   LogMessage(long hh, const char *S, double V1, double V2, TExtra Opt = TExtra::BLANK);
void   LogMessage(long hh, const char *S, double V1, double V2, double V3, TExtra Opt = TExtra::BLANK);

void   LogMessageA(long hh, const char *S, double V1, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double HRU_area, const double Basin_area, const char *S2, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, TExtra Opt = TExtra::BLANK);
void   LogMessageA(long hh, const char *S, double V1, const double Basin_area, const char *S2, TExtra Opt = TExtra::BLANK);

void   LogDebug(long h, char *Text, double v);
void   LogDebug(char *S);
void   LogDebugD(char *S);
void   LogDebugT(string S);

void   Update_Main_Status(string S);

void   Update_Main_DIM(TDim Dim, long dim);

void   Update_Main_Dirty(void);

long getdim(TDim dimen);

long getstep(void);

bool laststep(void);

void setdim(TDim dimen, long dim);

void setdim(string name, long dim);

void ModVarRemove(MapVar & MapVars);

long julian(string when);

//  long julian(TDateTime DT);
//
//  long julian(TDateTime DT);
//
//  long MonthDaysCnt(TDateTime DT);

double Julian(string when);

bool last_timestep(void);

void dattim(string type, long *itime);

void dattim(double DT, long *itime);

ClassVar *declread(string module, string name, long cnt, long offset,
	ClassData * FileData, string Comment);

long ClassParFindParBld(ClassPar *thisPar);

ClassVar *ClassVarFind(string name);

ClassPar *ClassParFindShared(string name); // where name is concatenation of MODULE and NAME

ClassPar *ClassParFind(string name); // where name is concatenation of MODULE and NAME

ClassPar *ClassParFindPar(string name); // where name is parameter

ClassPar *ClassParFind(string module, string param); // routine concatenates MODULE and NAME

ClassPar *ClassParFindRev(string module, string param);

void ClassParSet(ClassPar *p);

//double sqr(double x);

string extract_units(string& Comment);

void   LogDebug(const char *S);
void   LogDebug(const string S);

#endif
