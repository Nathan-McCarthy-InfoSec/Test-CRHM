// 01/25/18
//---------------------------------------------------------------------------


//#include "stdafx.h"
#include <stdio.h>
//#include <tchar.h>



//#include <vcl.h>
#pragma hdrstop

#include "NewModules.h"
#include "GlobalDll.h"
//#include "ClassModule.h"
#include <algorithm>

//#include <values.h>
#include <limits.h>

#include "SnobalDefines.h"

//#include <math.hpp>
#include <math.h>
//#include <cmath>

#include <assert.h>
#include <iostream>
#include <fstream>
#include <bitset>

#include "Hype_CRHM.h"
#include "Hype_routines.h"
#include "Hype_river.h"
#include "Hype_lake.h"
#include "Common.h"

#include <errno.h>
#include <stdexcept>
#include <float.h>
#include <iostream>
#include <fstream>
#include <ctime>
//#include <atltime.h>
#include <sstream>

std::string Convert(float number) {
	std::ostringstream buff;
	buff << number;
	return buff.str();
}

#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

//---------------------------------------------------------------------------

//#pragma package(smart_init)
#pragma init_seg

using namespace std;
using namespace CRHM;

/*
const long i_in = 0; // inorganic nitrogen
const long i_on = 1; // organic nitrogen
const long i_sp = 2; // soluble (reactive) phosphorus, i.e. phosphate
const long i_pp = 3; // particulate phosphorus
const long i_oc = 4; // (dissolved) organic carbon
*/

//extern double xLimit;
//extern long lLimit;

Administer DLLModules("08/25/08", "Modules_New");
bool RELEASE = false;

/*
string getTimeGG() {
	CTime t1 = CTime::GetCurrentTime();
	CTime t2 = t1 + CTimeSpan(0, 1, 0, 0);
	CString cs = t1.Format(_T("%A, %B %d, %Y"));

	CT2A ct(cs);
 string strr(ct);
	return (strr);
};
*/

void MoveModulesToGlobal(string DLLName) {

	DLLModules.AddModule(new Classshared("Shared", "10/25/10", CRHM::CUSTOM)); // essential for parameter screen
	DLLModules.AddModule(new ClassNOP("NOP", "05/20/16", CRHM::ADVANCE)); // essential for parameter screen
	DLLModules.AddModule(new Classbasin("basin", "02/24/12", CRHM::BASIC));
	DLLModules.AddModule(new Classglobal("global", "04/19/13", CRHM::BASIC));

	//testing making modules from macros of SmithCreek project. //written by Manishankar. uncommenting the following lines will enable the classes for the macros.

	//DLLModules.AddModule(new ClassGrow_Crop("Grow_Crop", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new Classdisplay("Display", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassSWE_peak("SWE_peak", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassAlbedo_Change("Albedo_Change", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassCalc_tmean("Calc_tmean", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassConvert_Qnsn_QnD("Convert_Qnsn_QnD", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new Classea_RH("ea_RH", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassHt_Change("Ht_Change", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassJulian_Test("Julian_Test", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassNo_Display_Macro("No_Display_Macro", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassSicartLong("SicartLong", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassSlope_Qsi2("Slope_Qsi2", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassCalc_t("Calc_t", "04/19/13", CRHM::BASIC)); //written by Manishankar
	//DLLModules.AddModule(new ClassHt_Change_Julian("Ht_Change_Julian", "04/19/13", CRHM::BASIC)); //written by Manishankar			
	//DLLModules.AddModule(new Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA("SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA", "04/19/13", CRHM::BASIC)); //written by Manishankar
	
	
	DLLModules.AddModule(new Classobs("obs", "11/28/17", CRHM::BASIC));
	DLLModules.AddModule(new Classintcp("intcp", "02/24/15", CRHM::BASIC));
	
	DLLModules.AddModule(new Classcalcsun("calcsun", "10/01/13", CRHM::BASIC));

	DLLModules.AddModule(new ClassNO_pbsm("NO_pbsm", "11/15/06", CRHM::ADVANCE));
	DLLModules.AddModule(new Classpbsm("pbsm", "11/20/17", CRHM::BASIC));
	DLLModules.AddModule(new Classsbsm("sbsm", "10/21/09", CRHM::ADVANCE));

	DLLModules.AddModule(new ClassAnnan("Annandale", "07/14/11", CRHM::ADVANCE));

	DLLModules.AddModule(new Classebsm("ebsm", "01/18/16", CRHM::BASIC));

	DLLModules.AddModule(new ClassLongVt("longVt", "02/10/16", CRHM::ADVANCE));

	DLLModules.AddModule(new ClassSlope_Qsi("Slope_Qsi", "07/14/11", CRHM::ADVANCE));

	DLLModules.AddModule(new Classalbedo("albedo", "08/11/11", CRHM::BASIC));
	DLLModules.AddModule(new Classnetall("netall", "03/22/16", CRHM::BASIC));
	DLLModules.AddModule(new Classevap("evap", "09/26/13", CRHM::BASIC));
	DLLModules.AddModule(new ClassevapD("evapD", "11/04/09", CRHM::ADVANCE));
	DLLModules.AddModule(new Classevap_Resist("evap_Resist", "11/21/16", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassevapD_Resist("evapD_Resist", "09/08/09", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassShutWall("ShuttleWallace", "10/05/06", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassShutWallD("ShuttleWallaceD", "10/05/06", CRHM::ADVANCE));

	DLLModules.AddModule(new Classcrack("crack", "09/03/08", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassPrairieInfil("PrairieInfiltration", "03/22/13", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassAyers("Ayers", "01/11/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassGreencrack("Greencrack", "03/22/13", CRHM::BASIC));
	DLLModules.AddModule(new ClassGreenAmpt("GreenAmpt", "03/29/10", CRHM::ADVANCE));
	DLLModules.AddModule(new Classfrozen("frozen", "08/03/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassfrozenAyers("frozenAyers", "08/02/16", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassSoil("Soil", "11/28/17", CRHM::BASIC));
	DLLModules.AddModule(new ClassevapX("evapX", "12/18/12", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassSoilX("SoilX", "11/28/17", CRHM::ADVANCE)); // nlay >= 2 check added
	DLLModules.AddModule(new ClassSoilDS("SoilDetention", "11/28/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassSoilPrairie("SoilPrairie", "11/28/17", CRHM::PROTO)); // prototype wetlands
	DLLModules.AddModule(new Classglacier("glacier", "11/15/17", CRHM::ADVANCE)); // removed commented lines
	DLLModules.AddModule(new ClassSWEslope("SWESlope", "11/01/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassICEflow("ICEflow", "01/25/17", CRHM::PROTO));

	DLLModules.AddModule(new ClassNetroute("Netroute", "04/24/17", CRHM::BASIC));
	DLLModules.AddModule(new ClassNetroute_D("Netroute_D", "04/24/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassNetroute_M("Netroute_M", "04/24/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassNetroute_M_D("Netroute_M_D", "04/24/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassREWroute("REW_route", "11/14/13", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassREWroute2("REW_route2", "01/31/15", CRHM::ADVANCE));

	DLLModules.AddModule(new ClassSnobalCRHM("SnobalCRHM", "11/21/16", CRHM::ADVANCE));
	DLLModules.AddModule(new ClasspbsmSnobal("pbsmSnobal", "01/05/17", CRHM::ADVANCE));

	DLLModules.AddModule(new ClassCRHMCanopy("Canopy", "06/14/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassCRHMCanopyClearing("CanopyClearing", "6/13/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassCRHMCanopyClearingGap("CanopyClearingGap", "6/13/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassNeedle("NeedleLeaf", "07/19/11", CRHM::ADVANCE));
	DLLModules.AddModule(new Classwalmsley_wind("walmsley_wind", "07/30/08", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassXG("XG", "10/03/17", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassXGAyers("XGAyers", "05/19/17", CRHM::PROTO));

	DLLModules.AddModule(new ClassSetSoil("SetSoil", "10/21/09", CRHM::ADVANCE));
	DLLModules.AddModule(new ClassVolumetric("Volumetric", "04/11/16", CRHM::ADVANCE));
	DLLModules.AddModule(new Classtsurface("tsurface", "12/14/16", CRHM::PROTO));

	DLLModules.AddModule(new Classalbedoparam("albedo_param", "11/22/05", CRHM::SUPPORT));
	DLLModules.AddModule(new Classalbedoobs("albedo_obs", "11/22/05", CRHM::SUPPORT));
	DLLModules.AddModule(new ClassalbedoRichard("albedo_Richard", "03/19/15", CRHM::SUPPORT));
	DLLModules.AddModule(new ClassalbedoBaker("albedo_Baker", "03/19/15", CRHM::SUPPORT));
	DLLModules.AddModule(new ClassalbedoWinstral("albedo_Winstral", "03/19/15", CRHM::SUPPORT));
	DLLModules.AddModule(new ClassHtobs("Ht_obs", "12/02/09", CRHM::SUPPORT));
	DLLModules.AddModule(new ClassObstoPar("obs_par", "07/19/10", CRHM::SUPPORT));

	DLLModules.AddModule(new Classfrostdepth("frostdepth", "08/11/11", CRHM::CUSTOM));

	DLLModules.AddModule(new Classqmelt("Qmelt", "03/31/16", CRHM::CUSTOM));
	DLLModules.AddModule(new Classquinton("Quinton", "03/31/16", CRHM::CUSTOM));
	DLLModules.AddModule(new Classqdrift("Qdrift", "03/31/16", CRHM::CUSTOM));

	DLLModules.AddModule(new ClassSimpleRichard("SimpleSnow", "03/24/06", CRHM::CUSTOM));
	DLLModules.AddModule(new ClassKevin("Kevin", "08/11/11", CRHM::OBSOL));
	DLLModules.AddModule(new ClassTs("Tsnow", "01/15/13", CRHM::CUSTOM));
	DLLModules.AddModule(new ClassK_Estimate("K_Estimate", "01/16/18", CRHM::ADVANCE)); // fixed 'put' descriptions

	DLLModules.AddModule(new ClassSnobalX("Snobal", "02/03/16", CRHM::OBSOL));
	DLLModules.AddModule(new Classinterception("interception", "11/03/06", CRHM::OBSOL));
	DLLModules.AddModule(new Classlake("lake_evap", "07/04/12", CRHM::ADVANCE));

	if (!RELEASE) {
		DLLModules.AddModule(new ClassHMSA("HMSA", "01/16/13", CRHM::PROTO));
		DLLModules.AddModule(new ClassHeating("FHM", "10/02/09", CRHM::PROTO));
		DLLModules.AddModule(new ClassIceBulb("IceBulb", "11/20/17", CRHM::PROTO));
		DLLModules.AddModule(new Class3D_param("3D_param", "03/18/13", CRHM::PROTO));
		DLLModules.AddModule(new ClassMeltRunoff_Lag("MeltRunoff_Lag", "09/03/13", CRHM::PROTO));
		DLLModules.AddModule(new ClassMeltRunoff_Kstorage("MeltRunoff_Kstorage", "09/03/13", CRHM::PROTO));
		DLLModules.AddModule(new ClassFlowInSnow("FlowInSnow", "08/19/14", CRHM::PROTO));
		DLLModules.AddModule(new ClassMod_Exec("Exec", "02/26/14", CRHM::PROTO));
		DLLModules.AddModule(new Classcontribution("contribution", "01/29/14", CRHM::PROTO));
		DLLModules.AddModule(new Classalbedoobs2("albedo_obs2", "11/18/14", CRHM::PROTO));
		DLLModules.AddModule(new Classwinter_meltflag("winter_meltflag", "02/12/15", CRHM::PROTO));
		DLLModules.AddModule(new Class_z_s_rho("z_s_and_rho", "04/09/15", CRHM::PROTO));
		//DLLModules.AddModule(new ClassWQ_Snow("WQ_Snow", "12/04/17", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_Soil("WQ_Soil", "01/24/18", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_ion("WQ_ion", "10/30/16", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_Netroute("WQ_Netroute", "12/18/17", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_Netroute_M_D("WQ_Netroute_M_D", "06/26/17", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_pbsm("WQ_pbsm", "12/04/17", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_Hype("WQ_Hype", "12/18/17", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_Lake("WQ_Lake", "01/23/18", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_River("WQ_River", "01/23/18", CRHM::PROTO));
		DLLModules.AddModule(new ClassWQ_REWroute("WQ_REW_route", "01/23/18", CRHM::ADVANCE));
	}

	DLLModules.AddModel("Prairie using sunshine hours or Qsi generated sunshine hours", "basin, global, obs, calcsun, intcp, pbsm, albedo, netall, ebsm, evap, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Prairie slope using Qsi generated sunshine hours", "basin, global, obs, Slope_Qsi#3, intcp, calcsun#1, netall, pbsm, albedo, ebsm, evap, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Prairie Annandale", "basin, global, obs, Annandale#1, intcp, netall, pbsm, albedo, ebsm, evap, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Canopy/Clearing using Qsi", "basin, global, obs, calcsun, longVt, netall, evap, CanopyClearing#1, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
	DLLModules.AddModel("Canopy/Clearing slope using Qsi", "basin, global, obs, Slope_Qsi#1, longVt, calcsun#3, netall, evap, CanopyClearing#3, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
	DLLModules.AddModel("Canopy/Clearing using Annandale(Slope)", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#3, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
	DLLModules.AddModel("Canopy/Clearing using Annandale(horizontal)", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#4, pbsm, albedo, ebsm#1, frozenAyers, Soil, Netroute");
	DLLModules.AddModel("NeedleLeaf with walmsley_wind", "basin, global, obs, calcsun, intcp, walmsley_wind, longVt, netall, albedo, pbsm#1, NeedleLeaf#1, evap, ebsm#1, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Prairie using Qsi and Snobal", "basin, global, obs, calcsun, intcp, longVt, netall, pbsmSnobal, albedo, evap, SnobalCRHM#2, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Prairie using Annandale and Snobal", "basin, global, obs, Annandale#1, intcp, longVt, netall, pbsmSnobal, albedo, evap, SnobalCRHM#2, PrairieInfiltration, Soil, Netroute");
	DLLModules.AddModel("Canopy/Clearing using Annandale(Slope) and Snobal", "basin, global, obs, Annandale#1, longVt#2, netall, evap, CanopyClearing#3, pbsmSnobal, albedo, SnobalCRHM#2, frozenAyers, Soil, Netroute");

	DLLModules.LoadCRHM(DLLName);

}
// All these at 0% saturation from Chow pg 115 except fcap
// Wilt = Chow's por-eff por, fcap from Floods in Canada
// Soil curves of form K = Ks / (A*Psi^3 + 1 )
// data from Clapp and Hornberger (1978). Original table appears In Dingman (2002)
// porosity/air entry tension/pore size distribution
// AVAIL ->     1 - Sand, at pcts < 0.25, limited to 0.25*pcts*avail_evap.
//              2 - loam, at pcts < 0.5,  limited to 0.5*pcts*avail_evap.
//              3 - clay, at pcts < 0.67 && pcts > 0.33, limited to pcts*avail_evap and
//                        at pcts < 0.33 limited to 0.5*pcts*avail_evap
//              4 organic, unlimted availability
//              where pcts = (soil moist)/(soil moist max)
// psi, k(mm/h), wilt, fcap,  porG, porE, air entry, pore size ?? b, AVAIL
// {PSI,  KSAT,  WILT,  FCAP, PORG,   PORE,     AIRENT, PORESZ ?? b, AVAIL}
//  mm    mm/h
float soilproperties[][9] = {
	{ 0.0,  999.9, 0.000, 0.00, 1.100,  1.000,	0.000,	0.0,  4 },  //      0  water
{ 49.5, 117.8, 0.020, 0.10, 0.437,  0.395,	0.121,	4.05, 1 },  //    � 1  sand
{ 61.3,  29.9, 0.036, 0.16, 0.437,  0.41 ,	0.09,	4.38, 4 },  //    � 2  loamsand
{ 110.1,  10.9, 0.041, 0.23, 0.453,  0.435,	0.218,	4.9,  2 },  //     �3  sandloam
{ 88.9,   3.4, 0.029, 0.26, 0.463,  0.451,	0.478,	5.39, 2 },  //    � 4  loam
{ 166.8,   6.5, 0.045, 0.38, 0.501,  0.485,	0.786,	5.3,  2 },  //    � 5  siltloam
{ 218.5,   1.5, 0.068, 0.38, 0.398,  0.420,	0.299,	7.12, 3 },  //    � 6  saclloam
{ 208.8,   1.0, 0.155, 0.39, 0.464,  0.476,	0.63,	8.52, 2 },  //    � 7  clayloam
{ 273.3,   1.0, 0.039, 0.40, 0.471,  0.477,	0.356,	7.75, 2 },  //    � 8  siclloam
{ 239.0,   0.6, 0.110, 0.41, 0.430,  0.426,	0.153,	10.4, 3 },  //    � 9  sandclay
{ 292.2,   0.5, 0.056, 0.43, 0.479,  0.492,	0.49,	10.4, 3 },  //    � 10 siltclay
{ 316.3,   0.3, 0.090, 0.46, 0.475,  0.482,	0.405,	11.4, 3 },  //    � 11 clay
{ 0.0,   0.0, 0.000, 0.00, 0.000,  0.000,	0.0,	 0.0, 4 }   //    � 12 pavement. Values not used
};

float SetSoilproperties[][4] = {
	//  avail       wilt    field   pore
	{ 1000.0,	  0.0, 1000.0,  1000.0 },          //      0  water
{ 84.0,	 40.0,	124.0,  395.0 },	  //      1  sand
{ 80.0,	 60.0,	140.0,  410.0 },	  //      2  loamsand
{ 130.0,	100.0,	230.0,  435.0 },	  //      3  sandloam
{ 157.0,	110.0,	267.0,  451.0 },	  //      4  loam
{ 162.0,	130.0,	292.0,  485.0 },	  //      5  siltloam
{ 170.0,	140.0,	310.0,  420.0 },	  //      6  saclloam
{ 167.0,	150.0,	317.0,  476.0 },	  //      7  clayloam
{ 150.0,	190.0,	340.0,  477.0 },	  //      8  siclloam
{ 150.0,	200.0,	350.0,  426.0 },	  //      9  sandclay
{ 150.0,	210.0,	360.0,  492.0 },	  //      10 siltclay
{ 145.0,	215.0,	360.0,  482.0 }, 	  //      11 clay
{ 0.0,     1000.0, 1000.0,    0.0 }           //      12 pavement
};

Classshared* Classshared::klone(string name) const {
	return new Classshared(name);
}

void Classshared::decl(void) {

	Description = "'System module only. NEVER use!'";

}

void Classshared::init(void) {

}

ClassNOP* ClassNOP::klone(string name) const {
	return new ClassNOP(name);
}

void ClassNOP::decl(void) {

	Description = "'NO operation module. Use only in macro declstruct as filler.'";

}

void ClassNOP::init(void) {

}

void ClassNOP::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessage(hh, string("'" + Name + " (NOP)'").c_str(), BLANK);
	}
	LogDebug(" ");
}

Classbasin* Classbasin::klone(string name) const {
	return new Classbasin(name);
}

void Classbasin::decl(void) {

	Description = "'Holds commonly used physical and control parameters.'";

	decldiagparam("RUN_ID", BASIN, "1", "-1E8", "+1E8", "run identification. If RUN_ID > 0 then the log file default name 'CRHM_output' with extensions .sum, .log OR .txt is expanded to 'CRHM_output_ID'.", "()", &RUN_ID);

	decldiagparam("RUN_START", BASIN, "0", "0", "+1E5", "run start time (Automation)", "(d)", &RUN_START);

	decldiagparam("RUN_END", BASIN, "0", "0", "+1E5", "run end time (Automation)", "(d)", &RUN_END);

	INIT_STATE = decldiagparam("INIT_STATE", BASIN, "", "Initial state file (Automation)", INIT_STATE);


	declvar("run_ID", BASIN, "run identification", "()", &run_ID);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("hru_ASL", NHRU, "0.0", "0.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(�)", &hru_ASL);


	hru_names = declparam("hru_names", NHRU, "'HRU'", "HRU names", hru_names);

	basin_name = declparam("basin_name", BASIN, "Basin", "Basin name", basin_name);

	RapidAdvance_to = decldiagparam("RapidAdvance_to", ONE, "' ', ' ', ' '", "Rapid advance to this date formatted as 'mm/dd/yyyy'", RapidAdvance_to);

	Loop_to = decldiagparam("Loop_to", TWO, "' ', ' '", "loop to this date formatted as 'mm/dd/yyyy', 0 - # loops", Loop_to);

	StateVars_to_Update = decldiagparam("StateVars_to_Update", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "run up these state variables.", StateVars_to_Update);

	TraceVars = decldiagparam("TraceVars", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop during run up.", TraceVars);
}

void Classbasin::init(void) {

	run_ID[0] = RUN_ID[0];  // transfer run identification

	float totarea = 0;
	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh)
		totarea += hru_area[hh];

	if (fabs((totarea - basin_area[0]) / basin_area[0]) > 1e-3) {
		const_cast<float *>  (basin_area)[0] = totarea;

		CRHMException TExcept("Sum of HRU's area <> Basin area, Basin area made = " + Convert(totarea), WARNING);
		LogError(TExcept);
	}



	//  TDateTime class (need to remove comment from GlobalDll.h file)

	/*Global::RapidAdvanceTo = 0;
	Global::LoopTo = 0;
	Global::LoopCnt = 0;

	try {
	if (!RapidAdvance_to->strings[0].IsEmpty()) {
	RapidAdvance_to->strings[0] = RapidAdvance_to->strings[0].Trim();
	if (!RapidAdvance_to->strings[0].IsEmpty())
	Global::RapidAdvanceTo = StrToDate(RapidAdvance_to->strings[0]);
	}
	if (!Loop_to->strings[0].IsEmpty()) {
	Loop_to->strings[0] = Loop_to->strings[0].Trim();
	Loop_to->strings[1] = Loop_to->strings[1].Trim();
	if (!Loop_to->strings[0].IsEmpty())
	Global::LoopTo = StrToDate(Loop_to->strings[0]);
	if (!Loop_to->strings[1].IsEmpty())
	Global::LoopCnt = StrToInt(Loop_to->strings[1]);
	}
	}

	catch (Sysutils::Exception &E) {
	CRHMException TExcept("Error in 'RapidAdvance_to' or 'Loop_to' parameters", TERMINATE);
	LogError(TExcept);
	Global::RapidAdvanceTo = 0;
	Global::LoopTo = 0;
	Global::LoopCnt = 0;
	}*/



}

Classglobal* Classglobal::klone(string name) const {
	return new Classglobal(name);
}


void Classglobal::decl(void) {

	Description = "'Calculate theoretical short_wave radiation using method proposed by Garnier and Ohmura (1970).'";

	declvar("QdroD", NHRU, "daily clear-sky direct", "(MJ/m^2*d)", &QdroD);

	declvar("QdroDext", NHRU, "daily ExtraTerrestrial direct", "(MJ/m^2*d)", &QdroDext);

	declvar("QdfoD", NHRU, "daily average clear-sky diffuse", "(MJ/m^2*d)", &QdfoD);

	declvar("Qdro", NHRU, "clear-sky direct", "(W/m^2)", &Qdro);

	declvar("Qdfo", NHRU, "clear-sky diffuse", "(W/m^2)", &Qdfo);

	declvar("Qdflat", NHRU, "clear-sky 'Qdro + Qdfo' on horizontal surface", "(W/m^2)", &Qdflat);

	declvar("QdflatE", NHRU, "'Qdro' on horizontal surface, no atmosheric attenuation", "(W/m^2)", &QdflatE);

	declvar("QdflatD", NHRU, "daily clear-sky Qdro (with diffuse) on horizontal surface", "(MJ/m^2*d)", &QdflatD);

	declvar("SolAng", NHRU, "Solar Angle", "(r)", &SolAng);

	declvar("SunMax", NHRU, "maximum sunshine hours", "(h)", &SunMax);

	declvar("cosxs", NHRU, "cosine of the angle of incidence on the slope", "()", &cosxs);

	declvar("cosxsflat", NHRU, "cosine of the angle of incidence on the horizontal", "()", &cosxsflat);

	declvar("pQdro", NFREQ, "clear-sky direct", "(MJ/m^2*int)", &pQdro, &pQdro_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pQdfo", NFREQ, "clear-sky diffuse", "(MJ/m^2*int)", &pQdfo, &pQdfo_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pQdflat", NFREQ, "Qdro + Qdfo on horizontal surface", "(MJ/m^2*int)", &pQdflat, &pQdflat_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pQdflatE", NFREQ, "Qdro on horizontal surface with no atmospheric attenuation", "(MJ/m^2*int)", &pQdflatE, &pQdflatE_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pSol", NFREQ, "Solar Angle", "(r)", &pSol, &pSol_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pCosxs", NFREQ, "Cos(x^s)", "(r)", &pCosxs, &pCosxs_FREQ, 0, true, false, CRHM::PRIVATE);

	declvar("pCosxs0", NFREQ, "Cos(x^s) on the horizontal", "(r)", &pCosxs0, &pCosxs0_FREQ, 0, true, false, CRHM::PRIVATE);

	// parameters

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("hru_GSL", NHRU, "0.0", "-90.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("hru_ASL", NHRU, "0.0", "-360.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(�)", &hru_ASL);

	declparam("Time_Offset", NHRU, "0.0", "-12.0", "12.0", "solar time offset from local time", "(h)", &Time_Offset);

}

const float DEGtoRAD = M_PI / 180.0;
const float DEGtoRAD365 = 2 * M_PI / 365.0;
const long CalcFreq = 288;
const float RADxxMIN = 2.0*M_PI / CalcFreq;
const float MINS_int = 24.0*60.0 / CalcFreq;

void Classglobal::init(void) {

	nhru = getdim(NHRU);

	int Integer = CalcFreq / Global::Freq;

	int Remainder = CalcFreq % Global::Freq;

	if (Remainder != 0 || Integer < 1) {
		CRHMException TExcept("\"288/(first observation frequency)\" must be an integer > one!", TERMINATE);
		LogError(TExcept);
	}

}

void Classglobal::air_mass(const float czen, float &oam) {

	float diff;

	float Z = acos(czen);
	oam = fabs(1.0f / (czen + 0.50572f*pow(96.07995f - Z, -1.6364f)));       // oam by cosecant approx.

	if (oam < 2.9)                          // zenith < 70 deg
		return;
	else if (oam < 16.38) {                 // zenith < 86.5 deg
		diff = pow(10.0f, 2.247f*log10(oam) - 2.104f);
		oam = oam - diff;
		return;
	}
	else if (oam <= 114.6) {                 // zenith < 89.5 deg
		diff = pow(10.0f, 1.576f*log10(oam) - 1.279f);
		oam = oam - diff;
		return;
	}

	oam = 30.0;                             // computed oam >114.6
}

void Classglobal::run(void) {

	/*   calculate daily incoming short wave radiation

	calculate direct and diffuse solar radiation on a slope in mj/m^2*d
	for a surface at given slope and azimuth
	for any given day and transmissivity
	account cloud cover empirically

	written by Pat Landine
	Division of Hydrology
	University of Sask.

	ref. B.J. Garnier and Atsuma Ohmura
	A method of calculating the direct shortwave
	radiation income of slopes
	Jour. of Applied Meteorology vol.7 1968

	incident shortwave radiation

	id = (sol/rad_vec**2)*integral{(trans**oam)*cos(x^s)*dh}

	sol      = solar constant
	rad_vec  = radius vector of the earth'S orbit
	trans    = mean transmissivity of the atmosphere
	oam      = optical air mass
	cos(x^s) = cosine of the angle of incidence  of the
	sun'S rays on the slope (x is a unit normal
	vector pointing away from the surface and
	s is the unit vector expressing the sun'S
	position.
	h        = hour angle measured from solar noon.
	(15 deg./hour or pi/12 rad/hour)

	integration is performed as an addition of a series of
	MINS_int minute intervals

	diffuse clear sky radiation

	Qdfo = 0.5*[(1 - aw - ao)*it - id]*(cos(gslope/2))**2

	aw     = radiation absorbed by water vapour (assumed = 7%
	aw     = radiation absorbed by ozone (assumed = 2%)
	gslope = gradient of slope

	it = (sol/rad_vec**2)*integral{czen*dh}

	czen = cosine of the sun'S zenith angle

	cloud cover adjustment

	ig = (id + Qdfo)

	variable description

	aslope = azimuth of the slope
	dec    = declination of the sun above or below the equator
	day = day of the calendar year

	use phys_constants
	*/

	long Period, Day;

	float Trans, Dec, Rad_vec, Sol, Clat, Slat, Cdec, Sdec, Hr_Ang;
	float Czen, t1, t2, x, y, z, Oam;
	float cosxsL, cosxs0, t10, t20;
	float It, Id, diffuse, Sum_Id, Sum_Diff, Sum_Sol, Sum_cosxs, Sum_cosxs0, Sum_Ext, Sum_Flatd, Sum_Flatf;

	Period = (getstep() - 1) % Global::Freq;

	if (Period == 0 || getstep() == 1) {

		for (hh = 0; hh < nhru; ++hh) {

			Day = julian("now");
			if (Global::Freq <= 1) --Day;  // if daily 00:00 is the next day

			Trans = 0.818;

			Dec = sin((Day - 81) * DEGtoRAD365) * 0.40928;     // Declination

			Rad_vec = .01676*cos(M_PI - 0.017262*(Day - 3)) + 1.0;   // radius vector
			Sol = 0.0819 / (Rad_vec*Rad_vec);                    // solar constant  mj/m**2*min or 117.936 mj/m**2*day

																 // calculate sines and cosines

			Clat = cos(hru_lat[hh] * DEGtoRAD);
			Slat = sin(hru_lat[hh] * DEGtoRAD);
			Cdec = cos(Dec);
			Sdec = sin(Dec);

			// set constants and initial values

			SunMax[hh] = 0.0;                 // no. of sunshine hours in 10ths.
			QdroD[hh] = 0.0;
			QdroDext[hh] = 0.0;
			QdfoD[hh] = 0.0;
			QdflatD[hh] = 0.0;
			Sum_Id = 0.0;
			Sum_Diff = 0.0;
			Sum_Sol = 0.0;
			Sum_cosxs = 0.0;
			Sum_cosxs0 = 0.0;
			Sum_Ext = 0.0;
			Sum_Flatd = 0.0;
			Sum_Flatf = 0.0;

			/*     cos(x^s) = [(Slat * cos(Hr_Ang) * (-cos(ASL) * sin(GSL))
			- sin(Hr_Ang) * (sin(ASL) * sin(GSL))
			+ (Clat * cos(Hr_Ang)) * cos(GSL)] * Cdec
			+ [Clat * (cos(ASL) * sin(GSL))
			+ Slat * cos(GSL)] * Sdec */

			x = -cos(hru_ASL[hh] * DEGtoRAD) * sin(hru_GSL[hh] * DEGtoRAD);
			y = sin(hru_ASL[hh] * DEGtoRAD) * sin(hru_GSL[hh] * DEGtoRAD);   //  compute constant
			z = cos(hru_GSL[hh] * DEGtoRAD);                               //  components of cos(x^s)
			t1 = (x*Slat + z * Clat)* Cdec;
			t2 = (-x * Clat + z * Slat)* Sdec;

			t10 = Clat * Cdec;
			t20 = Slat * Sdec;

			Hr_Ang = -M_PI * (1.0 + Time_Offset[hh] / 12.0);

			for (long jj = 0; jj < CalcFreq; ++jj, Hr_Ang += RADxxMIN) { // CalcFreq periods/day

				Czen = Cdec * Clat*cos(Hr_Ang) + Sdec * Slat;  // cos of zenith angle
				diffuse = 0.0;

				if (Czen > 0.0) {
					Sum_Sol = Sum_Sol + M_PI / 2.0f - acos(Czen);

					SunMax[hh] = SunMax[hh] + MINS_int; // sum sunshine minutes
					It = MINS_int * Sol*Czen;           // extra-ter. rad for MINS_int minute interval

					cosxs0 = t10 * cos(Hr_Ang);
					cosxs0 = cosxs0 + t20;
					// horzontal
					if (cosxs0 > 0.0) {      // not in shadow
						Sum_cosxs0 += cosxs0;

						air_mass(Czen, Oam); // get optical air mass
						Oam = Oam * pow((288.0f - 0.0065f*hru_elev[hh]) / 288.0f, 5.256f);  // correction

						Id = MINS_int * Sol*cosxs0; // direct rad. for MINS_int minute interval
						Sum_Ext += Id;

						Id = Id * pow(Trans, Oam); // direct rad. for MINS_int minute interval

												   // List (1968) diffuse = 0.5((1-aw-ac)Qa - Id) where
												   // aw = radiation absorbed by water vapour (7%)
												   // ac = radiation absorbed by ozone (2%)

						diffuse = 0.5f*(0.91f*It - Id);      // Diffuse radiation on horizontal
						Sum_Flatf += diffuse;
						Sum_Flatd += Id;
					}

					cosxsL = -y * sin(Hr_Ang)*Cdec + t1 * cos(Hr_Ang);
					cosxsL = cosxsL + t2;

					if (cosxsL > 0.0) {       // slope not in shadow
						Sum_cosxs += cosxsL;

						air_mass(Czen, Oam); // get optical air mass
						Oam = Oam * pow((288.0f - 0.0065f*hru_elev[hh]) / 288.0f, 5.256f);  // correction

						Id = MINS_int * Sol*cosxsL;     // direct rad. for MINS_int minute interval
						Id = Id * pow(Trans, Oam);

						Sum_Id += Id;
					}

					diffuse = diffuse * sqr(cos(hru_GSL[hh] / 2.0)); // on slope

					Sum_Diff += diffuse;

				} // end if

				if (!((jj + 1) % (CalcFreq / Global::Freq))) {

					int kk = jj / (CalcFreq / Global::Freq);
					pQdro_FREQ[kk][hh] = Sum_Id;     // direct radiation
					pQdfo_FREQ[kk][hh] = Sum_Diff;   // diffuse radiation
					pQdflat_FREQ[kk][hh] = (Sum_Flatd + Sum_Flatf); // level direct + diffuse radiation
					pQdflatE_FREQ[kk][hh] = Sum_Ext; // level direct no atmospheric attenuation
					pSol_FREQ[kk][hh] = Sum_Sol / (CalcFreq / Global::Freq);  // solar angle
					pCosxs_FREQ[kk][hh] = Sum_cosxs / (CalcFreq / Global::Freq);  // solar angle
					pCosxs0_FREQ[kk][hh] = Sum_cosxs0 / (CalcFreq / Global::Freq);  // solar angle

					QdroD[hh] += Sum_Id;   // direct radiation
					QdroDext[hh] += Sum_Ext;  // ExtraTerrestrial radiation
					QdfoD[hh] += Sum_Diff; // diffuse radiation
					QdflatD[hh] += Sum_Flatd + Sum_Flatf; // level direct

					Sum_Id = 0.0;
					Sum_Diff = 0.0;
					Sum_Sol = 0.0;
					Sum_cosxs = 0.0;
					Sum_cosxs0 = 0.0;
					Sum_Ext = 0.0;
					Sum_Flatd = 0.0;
					Sum_Flatf = 0.0;
				}

			} // end for
			SunMax[hh] = SunMax[hh] / 60.0;        // convert to hours*10

			Hr_Ang = 0.0;
		} // end for hh
	} // end if - Entire day calculated

	for (hh = 0; hh < nhru; ++hh) {
		Qdro[hh] = pQdro_FREQ[Period][hh] * 1E6 / 86400 * Global::Freq; // MJ/m^2.int to W/m^2
		Qdfo[hh] = pQdfo_FREQ[Period][hh] * 1E6 / 86400 * Global::Freq; // MJ/m^2.int to W/m^2
		Qdflat[hh] = pQdflat_FREQ[Period][hh] * 1E6 / 86400 * Global::Freq; // MJ/m^2.int to W/m^2
		QdflatE[hh] = pQdflatE_FREQ[Period][hh] * 1E6 / 86400 * Global::Freq; // MJ/m^2.int to W/m^2
		SolAng[hh] = pSol_FREQ[Period][hh];
		cosxs[hh] = pCosxs_FREQ[Period][hh];
		cosxsflat[hh] = pCosxs0_FREQ[Period][hh];
	} // end if
}

Classobs* Classobs::klone(string name) const {
	return new Classobs(name, "07/05/06");
}

void Classobs::decl(void) {

	Description = "'Converts measurement observations to HRU variables with corrections,' \
                 'original interval version,' \
                 'daily interval version for Annandale (additional inputs are observations t_min and t_max),' \
                 'inputs rain and snow observations (p and ppt not used)).'";

	variation_set = VARIATION_ORG;

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	decldiagparam("HRU_OBS", NDEFN, "[1, 2, 3!]", "1", "100", "observation indirection table ([1] - t, rh and ea, [2] - p and ppt, [3] - u, [4] - Q, [5] - misc)", "()", &HRU_OBS, &HRU_OBS_Tables, 5);

	declparam("obs_elev", NDEFN, "[0]", "0.0", "100000.0", "observation measurement altitude table ([1] - t, rh and ea, [2] - p and ppt", "(m)", &obs_elev, &obs_elev_Tables, 2);

	declparam("hru_elev", NHRU, "[0]", "0.0", "100000.0", "HRU altitude", "(m)", &hru_elev);

	declparam("lapse_rate", NHRU, "[0.75]", "0", "2", "temperature lapse rate", "(�C/100m)", &lapse_rate);

	decldiagparam("precip_elev_adj", NHRU, "[0.0]", "-1.0", "1.0", "precipitation height adjustment {adjusted p(or ppt) = p(or ppt)*(1.0 + precip_elev_adj*elev_difference/100)}", "(1/100m)", &precip_elev_adj);

	decldiagparam("ElevChng_flag", NHRU, "[0]", "0", "1", "Elevation change control; 0 - maintain RH, 1 - keep Vp within Vsat maximum", "()", &ElevChng_flag);

	decldiagparam("ClimChng_flag", NHRU, "[0]", "0", "1", "Climate change control; 0 - maintain RH, 1 - keep Vp within Vsat maximum", "()", &ClimChng_flag);

	decldiagparam("ClimChng_t", NHRU, "[0]", "-50", "+50", "Climate change additive temperature change.", "(�C)", &ClimChng_t);

	decldiagparam("ClimChng_precip", NHRU, "[1]", "0.0", "10", "Climate change multiplative p/ppt change.", "()", &ClimChng_precip);

	
	Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables);

	Global::Warming_t = const_cast<float *> (this->ClimChng_t); // must be here to load do_t_day etc.

	Global::Warming_p = const_cast<float *> (this->ClimChng_precip); // must be here to load do_p etc.


	declreadobs("u", NHRU, "wind velocity", "(m/s)", &u, HRU_OBS_u);

	declreadobs("ppt", NHRU, "daily precipitation", "(mm/d)", &ppt, HRU_OBS_p_ppt, true);

	declreadobs("p", NHRU, "interval precipitation", "(mm/int)", &p, HRU_OBS_p_ppt, true);


	decldiag("t_obs", NFREQ, "observation temperature before modification by lapse rate and global warning", "(�C)", &t_obs, &t_obs_lay);


	declvar("hru_t", NHRU, "temperature", "(�C)", &hru_t);

	declvar("hru_rh", NHRU, "relative humidity", "(%)", &hru_rh);

	declvar("hru_ea", NHRU, "HRU vapour pressure", "(kPa)", &hru_ea);

	declvar("hru_u", NHRU, "wind velocity", "(m/s)", &hru_u);

	declvar("hru_p", NHRU, "total precip (includes snow catch adjustment", "(mm/int)", &hru_p);

	declvar("hru_rain", NHRU, "rain", "(mm/int)", &hru_rain);

	declvar("Pa", NHRU, "average surface pressure", "(kPa)", &Pa);

	decllocal("DTindx", ONE, "main loop Index", "()", &DTindx);

	decllocal("DTnow", ONE, "main loop Time", "()", &DTnow);

	declstatdiag("cumhru_rain", NHRU, "cumulative HRU rain", "(mm)", &cumhru_rain);

	declvar("hru_snow", NHRU, "snow", "(mm/int)", &hru_snow);

	declstatdiag("cumhru_snow", NHRU, "cumulative HRU snow", "(mm)", &cumhru_snow);

	declstatdiag("cumhru_snow_meas", NHRU, "cumulative HRU snow catch adjustment", "(mm)", &cumhru_snow_meas);

	declvar("hru_tmax", NHRU, "max daily temp", "(�C)", &hru_tmax);

	declvar("hru_tmin", NHRU, "min daily temp", "(�C)", &hru_tmin);

	declvar("hru_tmean", NHRU, "mean daily temp", "(�C)", &hru_tmean);

	declvar("hru_eamean", NHRU, "mean daily vapour pressure", "(kPa)", &hru_eamean);

	declvar("hru_umean", NHRU, "mean daily wind", "(m/s)", &hru_umean);

	declvar("hru_rhmean", NHRU, "daily mean relative humidity", "(%)", &hru_rhmean);

	declvar("hru_newsnow", NHRU, "new snow on HRU - 0=no, 1=yes", "()", &hru_newsnow);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	Global::RH_EA_obs = -1;

	decldiag("Tday", NFREQ, "observation t unavailable", "(�C)", &NotUsed, &tday_intvls);
	Exist = declobsfunc("t", "Tday", &NotUsed, INTVL, &tday_intvls);

	decldiag("RHday", NFREQ, "observation rh unavailable", "(kPa)", &NotUsed, &rhday_intvls);
	Exist = declobsfunc("rh", "RHday", &NotUsed, INTVL, &rhday_intvls, true);

	if (Exist >= 0)
		Global::RH_EA_obs = 0;

	decldiag("EAday", NFREQ, "observation ea unavailable", "(kPa)", &NotUsed, &eaday_intvls);
	Exist = declobsfunc("ea", "EAday", &NotUsed, INTVL, &eaday_intvls, true);

	if (Exist >= 0)
		if (Global::RH_EA_obs < 0)
			Global::RH_EA_obs = 1;

	declobsfunc("u", "Umean", &umean, AVG);

	declobsfunc("ppt", "pptD", &pptD, FIRST, NULL, true);

	auto var = const_cast<float *> (p);
	declobsfunc("p", "p", &var, FOBS, NULL, true);

	variation_set = VARIATION_0 + VARIATION_1;

	declparam("catchadjust", NHRU, "[0]", "0", "3", "none - 0/Nipher - 1/MacDonald-Alter - 2 (not recommended)/Smith-Alter - 3", "()", &catchadjust);

	decldiagparam("ppt_daily_distrib", NHRU, "[1]", "0", "1", "0 - daily precip in first interval, 1 - equally divided over the day", "()", &ppt_daily_distrib);

	declparam("snow_rain_determination", NHRU, "[0]", "0", "2", "snow/rain determination: 0 - air temperature, 1 - ice bulb temperature, 2 - Harder", "()", &snow_rain_determination);

	decldiagparam("tmax_allrain", NHRU, "[4.0]", "-10", "10", "precip all rain if HRU air/ice bulb temperature above or equal to this value. Not used in Harder method.",
		"(�C)", &tmax_allrain);

	decldiagparam("tmax_allsnow", NHRU, "[0.0]", "-10", "10", "precip all snow if HRU air/ice bulb temperature below this value. Not used in Harder method",
		"(�C)", &tmax_allsnow);


	variation_set = VARIATION_1;

	declreadobs("t_max", NHRU, " daily maximum temperature", "(�C)", &t_max, HRU_OBS_t_rh_ea);

	declreadobs("t_min", NHRU, " daily minimumn temperature", "(�C)", &t_min, HRU_OBS_t_rh_ea);


	variation_set = VARIATION_2;

	declreadobs("obs_snow", NHRU, "snow observation", "(mm)", &obs_snow, HRU_OBS_Q);

	declreadobs("obs_rain", NHRU, "rain observation", "(mm)", &obs_rain, HRU_OBS_Q);


	variation_set = VARIATION_ORG;
}

void Classobs::init(void) {

	if (this->GroupCnt < 2) { // display for simple project and first group

		if (ppt == NULL && p == NULL && variation != VARIATION_2) {
			CRHMException TExcept("No precipitation data.  Both p and ppt not available!", TERMINATE);
			LogError(TExcept);
		}

		if (ppt) {
			CRHMException TExcept("using daily precipitation (ppt) observation.", WARNING);
			LogError(TExcept);
		}

		if (p) {
			CRHMException TExcept("using interval precipitation (p) observation.", WARNING);
			LogError(TExcept);
		}

		if (variation == VARIATION_1 && Global::Freq != 1) {
			CRHMException TExcept("obs#1 (using daily maximun/minimum temperatures) only works with daily data", TERMINATE);
			LogError(TExcept);
		}

		if (Global::RH_EA_obs == -1) {
			//CRHMException TExcept("No psychrometric data.  Both relative humidity (rh) and vapour pressure (ea) observations not available.", TERMINATE);
			CRHMException TExcept("No psychrometric data.  Both relative humidity (rh) and vapour pressure (ea) observations not available.", WARNING);
			LogError(TExcept);
		}
		else if (Global::RH_EA_obs == 1) {
			CRHMException TExcept("using vapour pressure (ea) observation.", WARNING);
			LogError(TExcept);
		}
		else if (Global::RH_EA_obs == 0) {
			CRHMException TExcept("using relative humidity (rh) observation.", WARNING);
			LogError(TExcept);
		}
	}

	nhru = getdim(NHRU);
	nobs = getdim(NOBS);

	for (hh = 0; hh < nhru; ++hh) {
		cumhru_rain[hh] = 0.0;
		cumhru_snow[hh] = 0.0;
		cumhru_snow_meas[hh] = 0.0;

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa

		DTnow[0] = 0.0;
		DTindx[0] = 0;
	}

	Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables);

}

void Classobs::pre_run(void) {

	Global::HRU_OBS = const_cast<long **> (HRU_OBS_Tables); 

	Global::OBS_ELEV = const_cast<float **> (obs_elev_Tables);

	Global::obs_t = const_cast<float **> (this->tday_intvls);

	Global::obs_ea = const_cast<float **> (this->eaday_intvls);

	Global::obs_rh = const_cast<float **> (this->rhday_intvls);

	Global::obs_t_obs = this->t_obs_lay;


	Global::Warming_t = const_cast<float *> (this->ClimChng_t); // must be here to switch for groups.

	Global::Warming_p = const_cast<float *> (this->ClimChng_precip); // must be here to switch for groups.

	Global::hru_elev = const_cast<float *> (this->hru_elev);

	Global::lapse_rate = const_cast<float *> (this->lapse_rate);

	Global::ppt_adj = const_cast<float *> (this->precip_elev_adj);

	Global::RH_VP_flag = const_cast<long *> (this->ElevChng_flag);

	Global::RH_VP_flag2 = const_cast<long *> (this->ClimChng_flag);



	//Global::RH_EA_obs = const_cast<long > (Global::RH_EA_obs);
	//long &test = Global::RH_EA_obs;
	//Global::RH_EA_obs = const_cast<long *> (test);



}

void Classobs::run(void) {

	float catchratio;
	float Tmean, Tmax, Tmin, RHmean, EAmean;

	long  nstep = getstep() % Global::Freq;
	long tt = Global::DTindx%Global::Freq;

	//DTnow[0] = std::stod(getTimeGG());
	//DTnow[0] = Common::DateTimeDt();
	DTnow[0] = (double) Global::DTnow; //added by Manishankar to solve the output difference problem.
	DTindx[0] = Global::DTindx;

	for (hh = 0; chkStruct(); ++hh) {

		hru_t[hh] = tday_intvls[tt][hh];

		hru_rh[hh] = rhday_intvls[tt][hh];


		//added by Manishankar. Possibly, needs to be removed. eaday_intvls[tt][hh] was not being assigned the appropriate value. It was having the default value which is a negative and very big.
		//eaday_intvls[tt][hh] = Common::estar(hru_t[hh])*hru_rh[hh] / 100.0;



		hru_ea[hh] = eaday_intvls[tt][hh];

		hru_u[hh] = max<float>(u[hh], 5.0e-2);

		if (nstep == 1 || Global::Freq == 1) {
			
			//umean[hh] = 3.05;

			//look at this.
			if (umean != NULL)
			{
				hru_umean[hh] = umean[hh];		
			}


			switch (variation) {
			case VARIATION_ORG:
			case VARIATION_2:
				Tmean = 0.0;
				Tmax = -999.0;
				Tmin = 999.0;
				RHmean = 0.0;
				EAmean = 0.0;
				for (long tt = 0; tt < Global::Freq; ++tt) {
					Tmean += tday_intvls[tt][hh];
					if (tday_intvls[tt][hh] > Tmax)
						Tmax = tday_intvls[tt][hh];
					if (tday_intvls[tt][hh] < Tmin)
						Tmin = tday_intvls[tt][hh];
					RHmean += rhday_intvls[tt][hh];
					EAmean += eaday_intvls[tt][hh];
				}

				hru_tmean[hh] = Tmean / Global::Freq;
				hru_tmax[hh] = Tmax;
				hru_tmin[hh] = Tmin;
				hru_eamean[hh] = EAmean / Global::Freq;
				hru_rhmean[hh] = RHmean / Global::Freq;

				break;
			case VARIATION_1:
				hru_tmax[hh] = t_max[hh]; // To get same results in different compilers
				hru_tmin[hh] = t_min[hh]; // To get same results in different compilers
				hru_tmean[hh] = (hru_tmax[hh] + hru_tmin[hh]) / 2.0;
				hru_eamean[hh] = hru_ea[hh]; // daily - only one value
				hru_rhmean[hh] = hru_rh[hh]; // daily - only one value
				break;
			} // switch
		}

		float umean = hru_umean[hh];
		if (umean > 8.0) umean = 8;

		if (variation != VARIATION_2) {

			switch (catchadjust[hh]) {  //


			case 1:  // Nipher
				catchratio = 0.01*(-0.387*sqr(umean) - 2.022*umean + 100.0);
				if (catchratio < 0.3) catchratio = 0.3;

				break;

			case 2:  // MacDonald-Alter (not correct, use Smith-Alter)
				catchratio = 1.01*exp(-0.09*umean);

				if (catchratio > 1.0) catchratio = 1.0;

				break;

			case 3:  // Smith-Alter
				if (p != NULL)
					catchratio = 1.18*exp(-0.18*hru_u[hh]);  // for hourly observed wind and precipitation
				if (ppt != NULL)
					catchratio = exp(-0.2*umean);  // for daily observed wind and precipitation

				if (catchratio > 1.0) catchratio = 1.0;

				break;

			default: // none

				catchratio = 1.0;

			} // end switch

			if (p != NULL) // insert p
				hru_p[hh] = p[hh];
			else
				hru_p[hh] = 0.0;

			if (ppt != NULL) { // merge ppt
				if (!ppt_daily_distrib[hh] && tmax_allsnow[hh] >= hru_tmax[hh]) {
					if (getstep() % Global::Freq == 1) // only for snow and option to add all first interval
						hru_p[hh] += pptD[hh];
					else
						hru_p[hh] += 0.0;
				}
				else // distribute over day
				{
					if (pptD != NULL) //look at this.
					{
						hru_p[hh] += pptD[hh] / Global::Freq;
					}
				}
			}

			hru_snow[hh] = 0.0;
			hru_rain[hh] = 0.0;
			hru_newsnow[hh] = 0;

			if (snow_rain_determination[hh] == 2) { // Harder
				Harder();
				if (hru_snow[hh] > 0.0) {
					cumhru_snow_meas[hh] += hru_snow[hh];
					hru_snow[hh] /= catchratio;
					hru_newsnow[hh] = 1;

					if (hru_rain[hh] > 0.0)
						hru_p[hh] = hru_rain[hh] + hru_snow[hh];
					else
						hru_p[hh] = hru_snow[hh];
				}
			}
			else {
				float Use;
				if (snow_rain_determination[hh])
					Use = Common::Ice_Bulb(hru_t[hh], hru_rh[hh], Pa[hh]);
				else
					Use = hru_t[hh];

				if (hru_p[hh] > 0.0) { //rain or snow determined by temperature
					if (Use >= tmax_allrain[hh]) { // all rain
						hru_rain[hh] = hru_p[hh];
					}
					else if (Use <= tmax_allsnow[hh]) { // all snow
						cumhru_snow_meas[hh] += hru_p[hh];
						hru_snow[hh] = hru_p[hh] / catchratio;
						hru_p[hh] = hru_snow[hh];
						hru_newsnow[hh] = 1;
					}
					else { // mixed
						hru_rain[hh] = hru_p[hh] * (tmax_allrain[hh] - Use) / (tmax_allrain[hh] - tmax_allsnow[hh]);
						cumhru_snow_meas[hh] += (hru_p[hh] - hru_rain[hh]);
						hru_snow[hh] = (hru_p[hh] - hru_rain[hh]) / catchratio;
						hru_p[hh] = hru_rain[hh] + hru_snow[hh];
						hru_newsnow[hh] = 1;
					}
				}
			} // end if
		}
		else {
			hru_rain[hh] = obs_rain[hh];
			hru_snow[hh] = obs_snow[hh];
			hru_p[hh] = hru_rain[hh] + hru_snow[hh];
			if (hru_snow[hh] > 0.0)
				hru_newsnow[hh] = 1;
			else
				hru_newsnow[hh] = 0;

			cumhru_snow_meas[hh] += hru_snow[hh];
		}

		cumhru_rain[hh] += hru_rain[hh];
		cumhru_snow[hh] += hru_snow[hh];
	}
}

void Classobs::Harder(void) {

	float Tk, D, lamda, pta, L, Ti1, Ti2, crit, crit1, T1, T2, a, b, c, ratio, hru_icebulb;

	Tk = hru_t[hh] + CRHM_constants::Tm;

	D = 0.0000206*pow(Tk / CRHM_constants::Tm, 1.75);

	lamda = 0.000063*Tk + 0.00673;

	pta = 18.01528*((hru_rh[hh] / 100.0)*0.611*exp((17.3*hru_t[hh]) / (237.3 + hru_t[hh]))) / (0.00831441*(hru_t[hh] + CRHM_constants::Tm)) / 1000.0;

	if (hru_t[hh] > 0.0)

		L = 1000 * (2501.0 - (2.361*hru_t[hh]));

	else

		L = 1000.0*(2834.1 - 0.29*hru_t[hh] - 0.004*hru_t[hh] * hru_t[hh]);

	Ti1 = 250.0;

	crit = 9999.0;

	while (crit > 0.0001) { //Iteration solution optimised by using the newton-raphston method

		T1 = Ti1 + 0.001*Ti1;

		T2 = Ti1 - 0.001*Ti1;

		a = (-Ti1 + Tk + (L*D / lamda)*(pta - (18.01528*(0.611*exp((17.3*(Ti1 - CRHM_constants::Tm)) / (237.3 + (Ti1 - CRHM_constants::Tm)))) / (0.00831441*Ti1) / 1000)));

		b = (-T1 + Tk + (L*D / lamda)*(pta - (18.01528*(0.611*exp((17.3*(T1 - CRHM_constants::Tm)) / (237.3 + (T1 - CRHM_constants::Tm)))) / (0.00831441*T1) / 1000)));

		c = (-T2 + Tk + (L*D / lamda)*(pta - (18.01528*(0.611*exp((17.3*(T2 - CRHM_constants::Tm)) / (237.3 + (T2 - CRHM_constants::Tm)))) / (0.00831441*T2) / 1000)));

		Ti2 = Ti1 - (a / ((b - c) / (0.002*Ti1)));

		crit1 = Ti1 - Ti2;

		if (crit1 < 0.0)

			crit = -crit1;

		else

			crit = crit1;

		Ti1 = Ti2;

	} // end while

	hru_icebulb = Ti1 - CRHM_constants::Tm;

	if (hru_icebulb < -10.0) //Eoverflow if ratio calculated with icebulb < -39C

		ratio = 0.0;

	else

		ratio = 1.0 / (1.0 + 2.50286*pow(0.125006, hru_icebulb));

	hru_snow[hh] = 0.0;

	hru_rain[hh] = 0.0;

	if (hru_p[hh] > 0.0) //rain or snow determined by ice bulb ratio

		hru_rain[hh] = hru_p[hh] * ratio;

	hru_snow[hh] = hru_p[hh] * (1.0 - ratio);
}

void Classobs::finish(bool good) {

	float Allcumhru_rain = 0.0;
	float Allcumhru_snow = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_rain      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_rain[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_snow (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_snow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (obs)'  cumhru_snow_meas (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumhru_snow_meas[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcumhru_rain += cumhru_rain[hh] * hru_area[hh];
		Allcumhru_snow += cumhru_snow[hh] * hru_area[hh];
		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (obs)' Allcumhru_rain (mm*basin): ").c_str(), Allcumhru_rain);
	LogMessage(string("'" + Name + " (obs)' Allcumhru_snow (mm*basin): ").c_str(), Allcumhru_snow, "*** adjusted snowfall");
	LogMessage(string("'" + Name + " (obs)' Allcumhru_ppt  (mm*basin): ").c_str(), Allcumhru_rain + Allcumhru_snow, "*** rainfall + adjusted snowfall");
	LogDebug(" ");
}

Classintcp* Classintcp::klone(string name) const {
	return new Classintcp(name);
}

void Classintcp::decl(void) {

	Description = "'Substitutes for canopy in open environment - implements variable name change. hru_snow --> net_snow, hru_rain --> net_rain.'";

	declvar("net_rain", NHRU, "hru_rain minus interception", "(mm/int)", &net_rain);

	declstatdiag("cumnet_rain", NHRU, "cumulative hru_rain minus interception", "(mm)", &cumnet_rain);

	declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

	declstatdiag("cumnet_snow", NHRU, "cumulative hru_snow minus interception", "(mm)", &cumnet_snow);

	declvar("net_p", NHRU, "hru_precipitation (rain and/or snow) less interception", "(mm/int)", &net_p);

	declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);
	declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);
	declgetvar("*", "hru_p", "(mm/int)", &hru_p);

}

void Classintcp::init(void) {

	nhru = getdim(NHRU);
	for (hh = 0; hh < nhru; ++hh) {
		cumnet_rain[hh] = 0.0;
		cumnet_snow[hh] = 0.0;
	}
}

void Classintcp::run(void) {

	for (hh = 0; chkStruct(); ++hh) {

		if (net_p != NULL && hru_p != NULL)
		net_p[hh] = hru_p[hh];

		if (net_snow != NULL && hru_snow != NULL)
		net_snow[hh] = hru_snow[hh];

		if (net_rain != NULL && hru_rain != NULL)
		net_rain[hh] = hru_rain[hh];

		if (cumnet_rain != NULL && net_rain != NULL)
		cumnet_rain[hh] += net_rain[hh];

		if (cumnet_snow != NULL && net_snow != NULL)
		cumnet_snow[hh] += net_snow[hh];

		if (intcp_evap != NULL)
		intcp_evap[hh] = 0.0;
	}
}

void Classintcp::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetrain  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (intcp)'  cumnetsnow  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumnet_snow[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
	LogDebug(" ");
}

Classpbsm* Classpbsm::klone(string name) const {
	return new Classpbsm(name);
}

void Classpbsm::decl(void) {

	Description = "'calculates snow transport and sublimation (Pomeroy and Li, 1999).' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

	variation_set = VARIATION_0 + VARIATION_2;

	declgetvar("*", "hru_u", "(m/s)", &hru_u);


	variation_set = VARIATION_1 + VARIATION_3;

	declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


	variation_set = VARIATION_2 + VARIATION_3;

	declparam("u_D", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

	declparam("Drift_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

	declparam("Drift_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

	declparam("Subl_offset", NHRU, "[0.0]", "0.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

	declparam("Subl_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


	variation_set = VARIATION_ORG;


	declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

	declvar("Subl", NHRU, "interval sublimation", "(mm/int)", &Subl);

	declvar("Drift", NHRU, "interval transport", "(mm/int)", &Drift);

	decldiag("DriftH", NHRU, "interval transport", "(mm/int)", &DriftH);

	decldiag("SublH", NHRU, "interval sublimation", "(mm/int)", &SublH);

	decldiag("BasinSnowLoss", BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

	declstatdiag("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

	declstatdiag("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

	declstatdiag("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

	declstatdiag("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

	declstatdiag("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

	decllocal("hru_basin", NHRU, "conversion factor", "()", &hru_basin);

	decldiag("DrySnow", NHRU, "DrySnow", "()", &DrySnow);

	declstatdiag("SnowAge", NHRU, "SnowAge", "()", &SnowAge);

	declstatdiag("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

	declvar("Prob", NHRU, "Probability", "()", &Prob);

	declvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

	decllocal("SWE_Init", NHRU, "initial SWE", "(mm)", &SWE_Init);

	/* parameters */

	declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	declparam("distrib", NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

	decldiagparam("N_S", NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

	decldiagparam("A_S", NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("inhibit_bs", NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

	decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_rh", "(%)", &hru_rh);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void Classpbsm::init(void) {

	nhru = getdim(NHRU);

	cumBasinSnowLoss[0] = 0.0;
	cumBasinSnowGain[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		SWE[hh] = 0.0;
		cumDrift[hh] = 0.0;
		cumDriftIn[hh] = 0.0;
		cumSubl[hh] = 0.0;
		cumSno[hh] = 0.0;
		SnowAge[hh] = 0.0;
		DrySnow[hh] = 0;
		snowdepth[hh] = 0.0;

		if ((hh > 0) && (Ht[hh] < Ht[hh - 1]) && distrib[hh - 1] > 0) {
			CRHMException TExcept(string("'" + Name + " (pbsm)' vegetation heights not in ascending order.").c_str(), WARNING);
			LogError(TExcept);
		}
	}

	for (hh = 0; hh < nhru; ++hh)
		hru_basin[hh] = hru_area[hh] / basin_area[0];
}

/*****************************
PBSMrun - PBSM module run function
10/28/99 (tb) 06/11/99

******************************/

float DepthofSnow(float SWE) {

	// 3/5/98 Calculates Snow Depth(m) from SWE(mm)
	float Snow_Depth;

	if (SWE > 2.05) {
		if (SWE <= 145.45) // SWE 145.45 mm equivalent to 60 cm
			Snow_Depth = (SWE - 2.05) / 2.39;
		else
			Snow_Depth = (SWE + 128.06) / 4.5608;
	}
	else
		Snow_Depth = 0;

	return Snow_Depth / 100.0;
} // DepthofSnow

float SWEfromDepth(float Snow_Depth) { // 3/5/98 Calculates SWE(mm) from Snow Depth(m)

	float SWE;

	if (Snow_Depth > 0.6)
		SWE = 4.5608*Snow_Depth*100.0 - 128.06;
	else if (Snow_Depth > 0.0205)
		SWE = 2.39*Snow_Depth*100.0 + 2.05;
	else
		SWE = Snow_Depth;

	return SWE;
} // SWEfromDepth

void ProbabilityThresholdNew(float SWE, float t, float Uten_Prob, float & Probability, float & Threshold,
	long Snow, float & SnowAge, long & DrySnow) {

	//Probability of blowing snow occurrence and threshold wind speeds determined by ambient air temperature and snow age

	float Wind, Mean, Variance, c;

	Wind = 0.0;
	Probability = 0.0;

	if (SWE <= 0.0) {   //no snow available
		DrySnow = false;
		SnowAge = 0.0;
		Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
	}

	else if ((Snow == true) && (t < 0.0))
	{
		// with concurrent snowfall: new dry snow
		DrySnow = true;
		SnowAge = 24.0 / Global::Freq;

		Mean = 0.365 * t + 0.00706 * sqr(t)
			+ 0.91 * log((float)SnowAge) + 11.0;
		Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

		while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
			// Wind < 3 m/s too weak for dry snow transport

			Wind = Wind + 0.1;

			c = (-sqr(Wind - Mean)) / (2.0*sqr(Variance));

			Probability = Probability + (1.0 / (Variance * 2.5055)) * (exp(c)) * 0.1;
		} // {while do}
		Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); // (m/s)
	} // {if}

	else if ((t < 0.0) && DrySnow)
	{
		// {without concurrent snowfall: old dry snow}
		SnowAge = SnowAge + 24.0 / Global::Freq;

		Mean = 0.365 * t + 0.00706 * sqr(t)
			+ 0.91 * log((float)SnowAge) + 11.0;
		Variance = 0.145 * t + 0.00196 * sqr(t) + 4.23;

		while ((Wind <= Uten_Prob) && (Uten_Prob >= 3.0)) {
			// Wind < 3 m/s too weak for dry snow transport
			Wind = Wind + 0.1;

			c = (-sqr(Wind - Mean)) / (2.0*sqr(Variance));

			Probability = Probability + (1.0 / (Variance * 2.5055)) * (exp(c)) * 0.1;
		} // while do

		Threshold = 9.43 + 0.18 * t + 0.0033 * sqr(t); //(m/s)
	} // if
	else if ((t >= 0.0) || !DrySnow)
	{
		DrySnow = false;             // or wet snow remains on the ground
		SnowAge = 0.0;
		Mean = 21.0;
		Variance = 7.0;

		while ((Wind <= Uten_Prob) && (Uten_Prob >7.0)) {    // loop to calculate P.
															 // wind < 7 m/s too weak for wet snow transport
			Wind = Wind + 0.1;
			c = (-sqr(Wind - Mean)) / (2.0*sqr(Variance));
			Probability = Probability + (1.0 / (Variance * 2.5055)) * (exp(c)) * 0.1;
		} // while do
		Threshold = 9.9;     // (m/s)
	} //if

} // Probability_threshold procedure

void Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH) {

	// total sublimation

	if ((SBsum + SBsalt) >= 0.0)
		SublH = 0.0;
	else
		SublH = (SBsum + SBsalt)*(-1E+3); // -mgmm2s to mg/m^2/s to g/m^2/s

	DriftH = (TQsalt + TQsusp); // kg/m-width/s
								// Convert to interval values

	SublH = SublH * Global::Interval * 3600 * 24 / 1000.0; // g/m^2/s to mm/m^2/interval
	DriftH = DriftH * Global::Interval * 3600 * 24;      // kg/m-width/s to kg/m-width/interval

} // sum procedure

void Pbsm(float E_StubHt, float Uthr, float & DriftH, float & SublH,
	float t, float u, float rh, float Fetch, long N_S, float A_S)
{

	/*   Modified Calculations for Mean Particle Mass in this version
	program to calculate blowing snow horizontal flux, sublimation rate
	and latent heat flux due to snow sublimation for a variety of windspeeds,
	boundary layers and surface conditions.

	All variable and constants entered into the programme are in SI and
	use Canadian Atmospheric Environement Service Meteorological data
	format.  Snow transport is in kg per square meter per half hour
	from the surface to 5 metres height.  Sublimation is totaled to the top
	of the boundary layer for diffusion, based on the meteorological
	Fetch and is expressed in millimeters of blowing snow lost over
	a square meter of snow surface per half hour  */

	float   A, Alpha, B, Bd, Bound, C,
		Diff, DmDt, Es, H,
		Htran, Hsalt, Inc, Lamb, Lambda, Lb,
		Mpm, Mpr, Nh, Nsalt,
		Nz, Nuss, Omega, TQsalt,
		TQsum, Qz, RauTerm, Temp,
		Reyn, SBsalt, Sbz, SBsum,
		SigmaZ, Sigma2, SvDens, Usthr, Ustar,
		UstarZ, Uz, Vs, Vsalt, Sigma,
		Vsusp, Z, Zr, Zstb;

	//Compute stubble coefficients

	Zstb = 0.005*N_S*A_S*E_StubHt*100.0;      // Lettau, used for susp Z0''
	Lambda = N_S * A_S*E_StubHt;         // Raupach Eq. 1
	Sigma = (M_PI*A_S) / (4.0*E_StubHt); // Raupach Eq. 4

										 // Calculate the flux for interval
	TQsalt = 0.0;                      // Total saltation flux
	TQsum = 0.0;                       // Total Suspension
	SBsalt = 0.0;
	SBsum = 0.0;
	DriftH = 0.0;
	SublH = 0.0;

	Temp = t + 273.0;                 // Convert to Deg. K

									  // Check for data errors    Fluxes set to zero for the interval
	if ((Temp < 0.0) || (u < 1.0) || (rh < 0.01)) { return; }

	if (rh >= 1.0) rh = rh / 100.0;       // handle %rh

	Lamb = 0.000076843*Temp + 0.003130762;   // therm. cond. of atm. (J/(msK))
	Diff = 2.06e-5f*pow(Temp / 273.0f, 1.75f); // diffus. of w.vap. atmos. (m^2/s
	B = PBSM_constants::LATH * PBSM_constants::M / (PBSM_constants::R * Temp) - 1.0;

	// find undersaturation of w. vapour at 2 metres
	Es = 611.15f * exp(22.452f*(Temp - 273.0f) / Temp);  //{sat pressure}
	SvDens = (Es*PBSM_constants::M) / (PBSM_constants::R*Temp);                       //{sat density}
	Sigma2 = rh - 1.0;                              //{undersaturation at 2 m}

	if (u > Uthr) {

		// define saltation parameters and calculate saltation
		//    rate using 10/1987 MODEL OF BLOWING SNOW EQUATIONS

		Usthr = 0.03697f*Uthr;                                  //{Eq. 6.3}
		Ustar = 0.02264f*pow(u, 1.295f);
		if (E_StubHt > 0.0001)                         //{Eq. 6.2 rev}
			RauTerm = 1.0 / ((1.0 - Sigma * Lambda)*(1.0 + PBSM_constants::Beta*Lambda)); //{Raupach}
		else
			RauTerm = 1.0;

		Hsalt = PBSM_constants::C2 / (2.0f*PBSM_constants::g)*sqr(Ustar);                         //{Eq. 4.13}
		Nsalt = 2.0*PBSM_constants::rho / (PBSM_constants::C2*PBSM_constants::C3*Ustar)*(RauTerm - sqr(Usthr) / sqr(Ustar)); //{Eq. 4.14 updated}

		if (Nsalt <= 0.0) {
			Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
			return;
		}

		TQsalt = PBSM_constants::C1*PBSM_constants::rho*Usthr / (PBSM_constants::g*PBSM_constants::C3*Ustar)*(sqr(Ustar)*RauTerm - sqr(Usthr)); // Eq. 4.20

																																				// calculate sublimation rate in the saltation layer

		Mpr = 100E-6;
		Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
		Alpha = 5.0;

		SigmaZ = Sigma2 * (1.019 + 0.027 * log(Hsalt)); // Eq. 6.20, Revised in May. 1997
		if (SigmaZ > -0.01) { SigmaZ = -0.01; }
		Vsalt = 0.6325 * Ustar + 2.3 * Usthr;          // Eq. 6.25
		Reyn = (2.0 * Mpr * Vsalt) / 1.88E-5;            // Eq. 6.22
		Nuss = 1.79 + 0.606 * sqrt(Reyn);              // Eq. 6.21
		A = Lamb * Temp * Nuss;
		C = 1.0 / (Diff * SvDens * Nuss);
		DmDt = ((2.0 * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants::LATH * B / A) + C);

		//{Eq. 6.16} {Gamma Dist. Corr.}
		Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Mpr*sqr(Mpr) *(1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

		Vs = DmDt / Mpm;                // Sublimation rate coefficient Eq. 6.13
		SBsalt = Vs * Nsalt * Hsalt;  // Eq. 6.11

									  // calculate mass flux in the suspended layers and the sublimation
									  //     rate for layers of height Inc from height r to b

		Zr = 0.05628 * Ustar;         // Eq. 5.27
		Alpha = 15.0;
		Inc = 0.0001;

		// Loop to find the first suspended drift density level, r
		//     from the reference level Zr
		//     To preserve continuity with saltation the first suspended
		//     level drift density is less than or equal to Nsalt.

		TQsum = 0;
		SBsum = 0;

		Z = Zr + Inc;
		while (Z <= 0.15) {
			Nz = 0.8 * exp(-1.55*(pow(0.05628f*Ustar, -0.544f) - pow(Z, -0.544f)));

			// Eq. 5.26, Revised in Dec. 1995
			if (Nz <= Nsalt) { goto Ten; }
			Z = Z + Inc;
		} //while
	Ten:  Lb = Z + Inc;
		Z = Lb;
		Inc = 0.001;

		// find height of fully-developed boundary layer for turbulent
		//     diffusion using a form of Pasquills plume dispersion eq.
		//     iterate towards Bound

		Bd = 1.0;
		Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
			sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));          // Eq. 6.9
		while (fabs(Bound - Bd) > 0.001) {
			Bd = Bound;
			Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
				sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));      // Eq. 6.9
		} //while


		  // Loop to calculate the suspended mass flux up to 5 metres
		  //     and the total sublimation rate to the top of the boundary layer
		  //   at increments of 1 mm to 50cm & increments of 10 cm to  b

	Twenty: H = Z + Inc;
		while (H <= Bound) {
			Nh = 0.8 * exp(-1.55f*(pow(0.05628f*Ustar, -0.544f) - pow(H, -0.544f)));
			Nz = Nh;
			UstarZ = Ustar * pow(1.2f / (1.2f + Nz), 0.5f);                  // Eq. 5.17a
			Uz = (UstarZ / PBSM_constants::KARMAN) *log(H / ((0.00613f *sqr(Ustar)) + Zstb));// Eq. 4.17r
			if (Uz > 0) {
				Mpr = 4.6e-5 * pow(H, -0.258f);                            // Eq. 6.15
				if (H >= 5.0) { Mpr = 30E-6f; }

				Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
				Alpha = 4.08 + 12.6 * H;                                  // Eq. 6.14
				if (H >= 1.5) { Alpha = 25.0; }

				SigmaZ = Sigma2 * (1.019 + 0.027 * log(H));  // Eq. 6.20, Revised in May. 1997
				if (SigmaZ > -0.01) { SigmaZ = -0.01; }
				Omega = 1.1e7f * pow(Mpr, 1.8f);               // Eq. 5.18
				Vsusp = Omega + 0.0106f * pow(Uz, 1.36f);
				Reyn = (2.0f * Mpr * Vsusp) / 1.88e-5f;          // Eq. 6.22
				Nuss = 1.79f + 0.606f * sqrt(Reyn);            // Eq. 6.21
				A = Lamb * Temp * Nuss;
				C = 1.0 / (Diff * SvDens * Nuss);
				DmDt = ((2.0f*M_PI * Mpr * SigmaZ) - (Htran*B / A)) / ((PBSM_constants::LATH*B / A) + C);
				Mpm = 1.333f * M_PI * PBSM_constants::DICE * sqr(Mpr)*Mpr *   // Eq. 6.16
					(1.0f + 3.0f / Alpha + 2.0f / sqr(Alpha));       // Gamma Dist. Corr.
				Vs = DmDt / Mpm;                               // Eq. 6.13
				Sbz = Vs * Nz * Inc;                         // mg
				SBsum = SBsum + Sbz;                         // Eq. 6.12
				Qz = Nz * Uz * Inc;                          // Eq. 5.4
				if (H >= 5.0) { Qz = 0.0; }
				TQsum = TQsum + Qz;                          // Eq. 5.5
				if (Nz >= 1e-5) {
					if (((H - Inc) >= 0.5) && (H < 0.6)) {
						Inc = 0.1;
						Z = 0.5;
						goto Twenty;                            // re start the loop
					} //{if}
				}
				else {
					Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
					return;
				} // if
			}
			else {
				TQsalt = 0.0;
				TQsum = 0.0;
				SBsalt = 0.0;
				SBsum = 0.0;
				Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
				return;
			} // if
			H = H + Inc;
		} // while
	} // if
	Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
} //PBSM procedure}

void Classpbsm::run(void) {

	float Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
	float SumDrift, total, SWE_Max, transport=0.0;

	if (getstep() == 1)
		for (hh = 0; chkStruct(); ++hh)
			SWE_Init[hh] = SWE[hh];

	for (hh = 0; chkStruct(); ++hh) {

		if (net_snow[hh] > 0.0) {
			SWE[hh] = SWE[hh] + net_snow[hh];
			cumSno[hh] = cumSno[hh] + net_snow[hh];
		}

		if (variation == VARIATION_ORG || variation == VARIATION_2)
			hru_u_ = hru_u[hh];
		else
			hru_u_ = hru_Uadjust[hh];

		if (variation == VARIATION_2 || variation == VARIATION_3)
			hru_u_ = u_D[hh] * hru_u_;

		Drift[hh] = 0.0;
		Subl[hh] = 0.0;
		DriftH[hh] = 0.0;
		SublH[hh] = 0.0;
		Prob[hh] = 0.0;

		if (SWE[hh] > 0.0 && !inhibit_bs[hh]) {

			E_StubHt = Ht[hh] - DepthofSnow(SWE[hh]); // depths(m) SWE(mm)
			if (E_StubHt < 0.0001) E_StubHt = 0.0001;

			Ustar = 0.02264*pow(hru_u_, 1.295f); // Eq. 6.2 rev.,  Ustar over fallow

			if (E_StubHt > 0.01) {
				Znod = (sqr(Ustar) / 163.3f) + 0.5*N_S[hh] * E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
				Lambda = N_S[hh] * A_S[hh] * E_StubHt;  // Raupach Eq. 1

				Ustn = Ustar * sqrt((PBSM_constants::Beta*Lambda) / (1.0 + PBSM_constants::Beta*Lambda));

				Uten_Prob = (log(10.0 / Znod)) / PBSM_constants::KARMAN *min <float>(0.0, Ustar - Ustn);
			}
			else
			{
				Uten_Prob = hru_u_;
			} // end if


			ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, hru_newsnow[hh], SnowAge[hh], DrySnow[hh]);

			if (Prob[hh] > 0.001) {
				Ut = Ut * 0.8;

				Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, hru_rh[hh], fetch[hh], N_S[hh], A_S[hh]);

				if (variation == VARIATION_2 || variation == VARIATION_3) {
					DriftH[hh] = Drift_offset[hh] + DriftH[hh] * Drift_slope[hh];
					SublH[hh] = Subl_offset[hh] + SublH[hh] * Subl_slope[hh];
				}

				Drift[hh] = DriftH[hh] * Prob[hh] / fetch[hh];
				if (!inhibit_subl[hh])
					Subl[hh] = SublH[hh] * Prob[hh];

				// handle insufficient snow pack

				if (Drift[hh] + Subl[hh] > SWE[hh]) {
					Subl[hh] = SWE[hh] * Subl[hh] / (Subl[hh] + Drift[hh]);
					Drift[hh] = SWE[hh] - Subl[hh];
				} // end if

				cumDrift[hh] = cumDrift[hh] + Drift[hh];
				cumSubl[hh] = cumSubl[hh] + Subl[hh];

				SWE[hh] = SWE[hh] - Subl[hh] - Drift[hh];
			}
		} // end if
	} // end for (hh)

	  // distribute drift

	if (distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
		float Drft = Drift[0] * distrib[0];
		SWE[0] += Drft;
		cumDriftIn[0] += Drft;
		cumBasinSnowGain[0] += Drft * hru_basin[0];  // **** hru_basin = hru_area/basin_area ****
	}

	BasinSnowLoss[0] = 0.0;
	long LastN = 0;

	if (!inhibit_bs[0] && nhru == 1) {
		BasinSnowLoss[0] = Drift[0];
		cumBasinSnowLoss[0] += BasinSnowLoss[0];
	}

	for (long nn = LastN; chkStruct(nn); ++nn) {
		if (distrib[nn] >= 0.0 && nn + 1 < nhru) // skip till last HRU or -ve distribution
			continue;

		SumDrift = 0.0;
		for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) // sum drift over range
			SumDrift += Drift[hhh] * hru_basin[hhh];

		if (SumDrift > 0.0) { // drift has occurred!
			for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {
				SWE_Max = SWEfromDepth(Ht[hh]);

				if (hh == nn) { // handle last HRU
					if (distrib[nn] > 0) {
						float In = SumDrift / hru_basin[hh]; // remaining drift
						if (SWE_Max > SWE[hh] + In) { // fill snowpack, remainder leaves basin
							SWE[hh] += In; // can handle all
							cumDriftIn[hh] += In;
							transport = 0.0;
						}
						else if (SWE_Max > SWE[hh]) { // cannot handle all
							cumDriftIn[hh] += (SWE_Max - SWE[hh]);
							transport -= (In - (SWE_Max - SWE[hh]))*hru_basin[hh];
							SWE[hh] += SWE_Max - SWE[hh]; //  has to come last
						}
						else // zero or -ve - happens during melt??
							transport = SumDrift;
					}
					else if (distrib[nn] < 0) { // all drift deposited
						SWE[hh] += SumDrift / hru_basin[hh]; // can handle all
						cumDriftIn[hh] += SumDrift / hru_basin[hh];
						transport = 0.0;
					}
					else // distrib[nn] == 0 -> all excess drift leaves basin
						transport = SumDrift;

					BasinSnowLoss[0] += (transport + Drift[hh] * hru_basin[hh]);
					cumBasinSnowLoss[0] += (transport + Drift[hh] * hru_basin[hh]);
				}
				else if (SWE_Max > SWE[hh] && distrib[hh] > 0.0) {
					// handle intermediate HRUs with available storage and distrib > 0
					total = 0.0;
					for (long jj = hh; chkStruct(jj, nn + 1); jj++) // calculate denominator        !!!! nn+1
						total += fabs(distrib[jj]);
					// determine contribution and scale
					transport = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];
					if (SWE_Max > SWE[hh] + transport) // sufficient capacity
						SWE[hh] += transport;
					else {
						transport = SWE_Max - SWE[hh];  // insufficient capacity
						SWE[hh] = SWE_Max;
					}
					SumDrift -= transport * hru_basin[hh]; // remove drift used from total available
					cumDriftIn[hh] += transport;
				} // end if
			} // end for (hh)
		} // end if
		LastN = nn + 1;
	} // end for (nn)

	for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation

		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0.0;
		}
	} // end for (hh)
}

void Classpbsm::finish(bool good) {

	if (!good) return;

	float AllcumSubl = 0.0;
	float AllcumCover = cumBasinSnowGain[0] - cumBasinSnowLoss[0];

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh] + cumDriftIn[hh] - cumDrift[hh] - cumSubl[hh], hru_area[hh], basin_area[0], "*** SWE just before melt");
		LogMessageA(hh, string("'" + Name + " (pbsm)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm)' SWE_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh] - SWE_Init[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		AllcumSubl += cumSubl[hh] * hru_area[hh];
		AllcumCover += (cumSno[hh] + cumDriftIn[hh] - cumDrift[hh] - cumSubl[hh])*hru_area[hh];
	}

	LogMessage(string("'" + Name + " (pbsm)' AllcumSubl  (mm*basin): ").c_str(), AllcumSubl, "*** cumulative sum of all HRUs cumSubl");
	LogMessage(string("'" + Name + " (pbsm)' AllcumCover (mm*basin): ").c_str(), AllcumCover, "*** SWE just before melt cumulative sum of all HRUs cumCover");
	LogDebug(" ");
	LogMessage("'pbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
	LogMessage("'pbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);
	LogDebug(" ");

}

ClassNO_pbsm* ClassNO_pbsm::klone(string name) const {
	return new ClassNO_pbsm(name);
}

void ClassNO_pbsm::decl(void) {

	Description = "'Substitute for pbsm when there is no transport and sublimation.  Alternatve is \"pbsm\" with parameter \"inhibit_bs\" = 1.'";

	declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

	declstatdiag("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

	declvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);


	/* parameters */

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClassNO_pbsm::init(void) {

	nhru = getdim(NHRU);

	hru_basin = new float[nhru];

	for (hh = 0; hh < nhru; ++hh) {
		SWE[hh] = 0.0;
		cumSno[hh] = 0.0;
		hru_basin[hh] = hru_area[hh] / basin_area[0];
		snowdepth[hh] = 0.0;
	}
}

void ClassNO_pbsm::run(void) {

	for (hh = 0; chkStruct(); ++hh) {

		if (net_snow[hh] > 0.0) {
			SWE[hh] = SWE[hh] + net_snow[hh];
			cumSno[hh] = cumSno[hh] + net_snow[hh];
		}

		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0;
		}
	}
}

void ClassNO_pbsm::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (NO_pbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
	}
	LogDebug(" ");
}

Classalbedo* Classalbedo::klone(string name) const {
	return new Classalbedo(name);
}

void Classalbedo::decl(void) {

	Description = "'Estimates the snow albedo during the winter and the melt period. Use with \"ebsm\".'";

	declstatvar("Albedo", NHRU, "Albedo()", "()", &Albedo);

	declvar("meltflag", NHRU, "meltflag = 1 - melt true", "()", &meltflag);

	declvar("winter", NHRU, "winter = 1 - true", "()", &winter);

	declvar("net_snowD", NHRU, "daily snow fall", "(mm/d)", &net_snowD);

	declvar("newsnowcnt", NHRU, "snow age count", "()", &newsnowcnt);


	decldiagparam("Albedo_bare", NHRU, "[0.17]", "0.0", "1.0", "albedo for bare ground", "()", &Albedo_bare); // pseudo
	decldiagparam("Albedo_snow", NHRU, "[0.85]", "0.0", "1.0", "albedo for fresh snow covered ground", "()", &Albedo_snow); // pseudo

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void Classalbedo::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		if (SWE[hh] > 5.0) {
			Albedo[hh] = Albedo_snow[hh];
			winter[hh] = 1;
		}
		else {
			Albedo[hh] = Albedo_bare[hh];
			winter[hh] = 0;
		}
		net_snowD[hh] = 0.0;
		meltflag[hh] = 0;
		newsnowcnt[hh] = 0;
	}
}

void Classalbedo::run(void) {

	long nstep, jday;

	nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // calculate daily snow accumulation

		if (net_snow != NULL)
		{
			if (nstep == 1 || Global::Freq == 1) // beginning of every day
				net_snowD[hh] = net_snow[hh];
			else
				net_snowD[hh] += net_snow[hh];
		}
	}

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		jday = julian("now");

		for (hh = 0; chkStruct(); ++hh) {
			float hemisphere = (hru_lat[hh] < 0.0);
			if ((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
				winter[hh] = 1;
				Albedo[hh] = Albedo_snow[hh];
			}
			continue;
		}

		for (hh = 0; chkStruct(); ++hh) {
			meltflag[hh] = 0;
			if (hru_newsnow[hh] > 0)
				newsnowcnt[hh] = 0;
			else
				newsnowcnt[hh] = newsnowcnt[hh] + 1;

			if (SWE[hh] <= 0.0) {
				Albedo[hh] = Albedo_bare[hh];
				winter[hh] = 0;
				meltflag[hh] = 0;
			}
			else { // SWE[hh] > 0.0
				float DR = 0.071;

				if (SWE[hh] > 60.0 && Albedo[hh] > 0.65)
					DR = 0.015;

				if (SWE[hh] > 60.0 && Albedo[hh] < 0.65)
					DR = 0.001;

				if (net_snowD[hh] > 0.25) { // SF = SWE*2 if density 0.005 (0.5cm)
					Albedo[hh] = Albedo[hh] + net_snowD[hh] * 0.1*2.0; // daily value
					if (Albedo[hh] > Albedo_snow[hh])
						Albedo[hh] = Albedo_snow[hh];
					continue;
				}

				float Qnc = -0.371 + 5.22*QdroD[hh] * (1 - Albedo[hh]);

				if (hru_tmax[hh] < -6.0 && Qnc < 1.0)
					winter[hh] = 1;

				if (Albedo[hh] <= Albedo_bare[hh])
					winter[hh] = 0;

				if (winter[hh] == 1) {
					if (newsnowcnt[hh] < 3) {
						Albedo[hh] = Albedo[hh] - 0.05;
						continue;
					}
					float MT = -0.064*jday + 6.69;

					if (hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 ||
						hru_tmax[hh] > MT && Qnc > -0.5) {
						Albedo[hh] = Albedo[hh] - DR;

						if (Albedo[hh] < Albedo_bare[hh])
							Albedo[hh] = Albedo_bare[hh];

						meltflag[hh] = 1;
					}
					else
						if (Albedo[hh] > 0.65)
							Albedo[hh] = Albedo[hh] - 0.006;
				}
				else {
					Albedo[hh] = Albedo[hh] - 0.02;
					if (Albedo[hh] < Albedo_bare[hh])
						Albedo[hh] = Albedo_bare[hh];
					meltflag[hh] = 1;
				}

			} // SWE > 0.0
		} // for HRU
	} //end of every day
}

Classnetall* Classnetall::klone(string name) const {
	return new Classnetall(name);
}

void Classnetall::decl(void) {

	Description = "'Models net all-wave radiation (Rn, RnD and RnD_POS) from sunshine hours, temperature and humidity using Brunt.'";

	declvar("net", NHRU, "all-wave net", "(MJ/m^2*int)", &net);

	decldiag("Rn", NHRU, "all-wave net", "(mm/m^2*int)", &Rn);

	declvar("netD", NHRU, "all-wave net", "(MJ/m^2*d)", &netD);

	declvar("RnD", NHRU, "all-wave net", "(mm/m^2*d)", &RnD);

	decldiag("RnD_POS", NHRU, "Sum of Positive all-wave net", "(mm/m^2*d)", &RnD_POS);

	declstatdiag("cum_net", NHRU, "cumulative all-wave net", "(MJ/m^2)", &cum_net);


	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
	declgetvar("*", "hru_SunAct", "(h)", &hru_SunAct);

	declgetvar("*", "Tday", "(�C)", &NotUsed, &tday_intvls); // from obs
	declgetvar("*", "EAday", "(kPa)", &NotUsed, &eaday_intvls); // from obs

	declgetvar("*", "SunMax", "(h)", &SunMax);
	declgetvar("*", "Qdro", "(W/m^2)", &Qdro); // clear-sky direct (W/m^2)
	declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo); // clear-sky diffuse (W/m^2)
	declgetvar("*", "Albedo", "()", &Albedo);

	declgetvar("*", "pQdro", "(MJ/m^2*int)", &pQdro, &pQdro_FREQ); // clear-sky direct (MJ/m^2/int)
	declgetvar("*", "pQdfo", "(MJ/m^2*int)", &pQdfo, &pQdfo_FREQ); // clear-sky diffuse (MJ/m^2/int)
}

void Classnetall::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh)
		cum_net[hh] = 0.0;
}

void Classnetall::run(void) {

	float netlong, shortw;

	long nstep = getstep() % Global::Freq;

	if (hru_SunAct == NULL) { return; }

	if (nstep == 1 || Global::Freq == 1) { // beginning of every day

		for (hh = 0; chkStruct(); ++hh) {
			netD[hh] = 0.0;
			RnD[hh] = 0.0;
			RnD_POS[hh] = 0.0;			

			for (int ff = 0; ff < Global::Freq; ++ff) {
				if (SunMax[hh] > 0.0)
					netlong = -0.85 + 0.97*CRHM_constants::SB*pow(tday_intvls[ff][hh] + 273.0f, 4)*(-0.39f + 0.093f*sqrt(eaday_intvls[ff][hh]))*
					(0.26f + 0.81f*(hru_SunAct[hh] / SunMax[hh]));
				else
					netlong = -0.85;

				if (hru_SunAct[hh] > 0.0 && SunMax[hh] > 0.0)
					shortw = (0.024f + 0.974f*pow(hru_SunAct[hh] / SunMax[hh], 1.35f))*pQdro_FREQ[ff][hh] +
					(2.68f + 2.2f*(hru_SunAct[hh] / SunMax[hh]) - 3.85f*sqr(hru_SunAct[hh] / SunMax[hh]))*pQdfo_FREQ[ff][hh];
				else
					shortw = (0.024f*pQdro_FREQ[ff][hh] + 2.68f*pQdfo_FREQ[ff][hh]);

				float Net = (shortw*(1.0f - Albedo[hh]) + netlong / Global::Freq); // MJ/interval
				netD[hh] += Net;

				Net = Net / (2.501f - 0.002361f*tday_intvls[ff][hh]); // MJ/m^2 to mm/m^2

				RnD[hh] += Net;
				if (Net > 0.0) RnD_POS[hh] += Net;

			} // Interval loop
		} // HRU loop
	} // if first interval

	for (hh = 0; chkStruct(); ++hh) {

		// t Kelvin degrees, ea bar

		if (SunMax[hh] > 0.0)
			netlong = -0.85f + 0.97*CRHM_constants::SB*pow(hru_t[hh] + 273.0f, 4.0f)*(-0.39f + 0.093f*sqrt(hru_ea[hh]))*
			(0.26f + 0.81f*(hru_SunAct[hh] / SunMax[hh]));
		else
			netlong = -0.85;

		if (hru_SunAct[hh] > 0.0 && SunMax[hh] > 0.0)
			shortw = (0.024f + 0.974f*pow(hru_SunAct[hh] / SunMax[hh], 1.35f))*Qdro[hh] * WtoMJ_D +
			(2.68f + 2.2f*(hru_SunAct[hh] / SunMax[hh]) - 3.85f*sqr(hru_SunAct[hh] / SunMax[hh]))*Qdfo[hh] * WtoMJ_D;
		else
			shortw = (0.024f*Qdro[hh] + 2.68f*Qdfo[hh])*WtoMJ_D;

		net[hh] = (shortw*(1.0f - Albedo[hh]) + netlong) / Global::Freq; // MJ/day to MJ/interval
		Rn[hh] = net[hh] / (2.501f - 0.002361f*hru_t[hh]); // MJ/interval to mm/interval

		cum_net[hh] += net[hh]; // mm/interval

	} // HRU loop
}

Classebsm* Classebsm::klone(string name) const {
	return new Classebsm(name);
}

void Classebsm::decl(void) {

	Description = "'Energy-budget snowmelt model for the Canadian Prairies', \
                 'ebsm using Brunt et al', \
                 'ebsm using input variable Qnsn_Var (W/m^2*int) from CanopyClearing etc.', \
                 'ebsm using input observation Qnsn (W/m^2*int)', \
                 'ebsm using input observation QnD (MJ/m^2*d)'";

	variation_set = VARIATION_ORG;

	declvar("snowmeltD", NHRU, "daily snowmelt", "(mm/d)", &snowmeltD);

	declvar("cumsnowmelt", NHRU, "cumulative melt", "(mm)", &cumsnowmelt);

	declstatvar("LW_ebsm", NHRU, "liquid water in snowpack", "(mm)", &LW_ebsm, NULL, 1, false, CRHM::PRIVATE);

	declstatvar("u_ebsm", NHRU, "snowpack energy deficit", "(MJ)", &u_ebsm, NULL, 1, false, CRHM::PRIVATE);

	declvar("Qmelt", NHRU, "Qmelt = Qn+Qh+Qe+Qp", "(MJ/d)", &Qmelt);

	decldiag("Qn_ebsm", NHRU, "net radiation", "(MJ/d)", &Qn_ebsm);

	decldiag("Qh_ebsm", NHRU, "sensible heat", "(MJ/d)", &Qh_ebsm);

	decldiag("Qe_ebsm", NHRU, "latent heat", "(MJ/d)", &Qe_ebsm);

	decldiag("Qe_subl", NHRU, "latent heat sublimation", "(mm/d)", &Qe_subl);

	decldiag("cumQe_subl", NHRU, "cumulative latent heat sublimation", "(mm)", &cumQe_subl);

	decldiag("Qp_ebsm", NHRU, "input from rainfall", "(MJ/d)", &Qp_ebsm);


	decldiag("LWmax", NHRU, "maximum liquid water in snowpack", "(mm)", &LWmax);

	declvar("net_rainD", NHRU, "daily net rain", "(mm/d)", &net_rainD);


	decldiagparam("delay_melt", NHRU, "[0]", "0", "366", "inhibit melt until this Julian date. Default incorrect for the Southern Hemisphere", "()", &delay_melt);

	decldiagparam("Qe_subl_from_SWE", NHRU, "[0]", "0", "1", "0 - add to 'Qmelt' (original version), 1 - take Qe_subl from SWE ", "()", &Qe_subl_from_SWE);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);


	declgetvar("*", "SunMax", "(h)", &sunmax);
	declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
	declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
	declgetvar("*", "hru_tmean", "(�C)", &tmean);
	declgetvar("*", "hru_tmax", "(�C)", &tmax);
	declgetvar("*", "hru_tmin", "(�C)", &tmin);
	declgetvar("*", "hru_umean", "(m/s)", &umean);
	declgetvar("*", "hru_rhmean", "(%)", &rhmean);
	declgetvar("*", "hru_SunAct", "(h)", &sunact);
	declgetvar("*", "meltflag", "()", &meltflag);
	declgetvar("*", "Albedo", "()", &Albedo);
	declputvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "net_rain", "(mm/int)", &net_rain);


	variation_set = VARIATION_0;

	decldiagparam("tfactor", NHRU, "[0.0]", "0.0", "10.0", "degree day melt factor", "(mm/d*�C)", &tfactor);

	decldiagparam("nfactor", NHRU, "[0.0]", "0.0", "10.0", "net radiation factor (typical value 3.0(mm*m^2/MJ))", "(mm*m^2/MJ)", &nfactor);

	decldiagparam("Use_QnD", NHRU, "[0]", "0", "1", "1 - Use QnD if available", "()", &Use_QnD);


	variation_set = VARIATION_0 + VARIATION_3;

	declreadobs("QnD", NHRU, "net radiation", "(MJ/m^2*d)", &QnD, HRU_OBS_Q, true); // must check for NULL


	variation_set = VARIATION_1 + VARIATION_2;

	declstatvar("Qnsn_Acc", NHRU, "accumulator for Qnsn_Var/Qnsn", "(W/m^2)", &Qnsn_Acc); // daily value


	variation_set = VARIATION_1;

	declgetvar("*", "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var); // interval value

	variation_set = VARIATION_2;


	declreadobs("Qnsn", NHRU, "net radiation", "(W/m^2*int)", &Qnsn, HRU_OBS_Q);

	variation_set = VARIATION_ORG;
}

void Classebsm::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		snowmeltD[hh] = 0.0;
		cumsnowmelt[hh] = 0.0;
		LW_ebsm[hh] = 0.0;
		u_ebsm[hh] = 0.0;
		Qmelt[hh] = 0.0;
		Qn_ebsm[hh] = 0.0;
		Qh_ebsm[hh] = 0.0;
		Qe_ebsm[hh] = 0.0;
		Qe_subl[hh] = 0.0;
		cumQe_subl[hh] = 0.0;
		Qp_ebsm[hh] = 0.0;

		if (variation == VARIATION_ORG)
			if (nfactor[hh] != 0.0 && QnD == NULL) {
				CRHMException TExcept("ebsm: nfactor > 0.0 with observation 'QnD' not defined!", TERMINATE);
				LogError(TExcept);
			}
	}
}

void Classebsm::run(void) {

	float umin, ref, melt;

	long  nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {
		if (nstep == 1 || Global::Freq == 1) { // beginning of every day
			net_rainD[hh] = net_rain[hh];
			if (variation == VARIATION_1)
				Qnsn_Acc[hh] = Qnsn_Var[hh];
			else if (variation == VARIATION_2)
				Qnsn_Acc[hh] = Qnsn[hh];
		}
		else {
			net_rainD[hh] += net_rain[hh];
			if (variation == VARIATION_1)
				Qnsn_Acc[hh] += Qnsn_Var[hh];
			else if (variation == VARIATION_2)
				Qnsn_Acc[hh] += Qnsn[hh];
		}
	}

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		for (hh = 0; chkStruct(); ++hh) {

			snowmeltD[hh] = 0.0;
			Qmelt[hh] = 0.0;
			Qn_ebsm[hh] = 0.0;
			Qh_ebsm[hh] = 0.0;
			Qe_ebsm[hh] = 0.0;
			Qe_subl[hh] = 0.0;
			Qp_ebsm[hh] = 0.0;

			if (SWE[hh] <= 0.0) { // bare ground
				LW_ebsm[hh] = 0.0;
				u_ebsm[hh] = 0.0;
			}
			else if (variation == VARIATION_ORG && (tfactor[hh] > 0.0 || nfactor[hh] > 0.0) && meltflag[hh] == 1) {
				if (delay_melt[hh] <= julian("now")) {

					if (QnD) { // observation available (MJ/m^2*d)
						if (QnD[hh] > 0.0)
							Qn_ebsm[hh] = QnD[hh] * nfactor[hh];
					}

					Qh_ebsm[hh] = tmax[hh] * tfactor[hh];

					Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh];
					snowmeltD[hh] = Qmelt[hh];
					if (snowmeltD[hh] <= 0.0)
						snowmeltD[hh] = 0.0;
					else {
						if (SWE[hh] > snowmeltD[hh])
							SWE[hh] = SWE[hh] - snowmeltD[hh];
						else {
							snowmeltD[hh] = SWE[hh];
							SWE[hh] = 0.0;
						}
						cumsnowmelt[hh] = cumsnowmelt[hh] + snowmeltD[hh];
					}
				}
			}
			else if (meltflag[hh] == 1 && delay_melt[hh] <= julian("now")) {
				float eamean = Common::estar(tmean[hh])*rhmean[hh] / 100.0; \
					switch (variation) {

					case VARIATION_ORG:
						if (QnD != NULL && Use_QnD[hh]) { // observation available (MJ/m^2*d)
							if (QnD[hh] > 0.0)
								Qn_ebsm[hh] = QnD[hh];
						}
						else
						{
							//Manishankar. Need to uncomment the following line.

							Qn_ebsm[hh] = -0.53 + 0.47*(QdroD[hh] + QdfoD[hh])*(0.52 + 0.52*sunact[hh] / sunmax[hh])*(1.0 - Albedo[hh]);
							
						}

						break;
					case VARIATION_1:
						Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
						break;
					case VARIATION_2:
						Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
						break;
					case VARIATION_3:
						Qn_ebsm[hh] = QnD[hh]; // already in (MJ/m^2*d)
						break;
					} // switch

				Qh_ebsm[hh] = -0.92 + 0.076*umean[hh] + 0.19*tmax[hh];
				Qe_ebsm[hh] = 0.08*(0.18 + 0.098*umean[hh])*(6.11 - eamean * 10.0);

				Qe_subl[hh] = Qe_ebsm[hh] / 2.83; // Lv = 2.83 mJ/Kg

				if (Qe_subl_from_SWE[hh]) {
					if (Qe_subl[hh] > SWE[hh])
						Qe_subl[hh] = SWE[hh];
					cumQe_subl[hh] += Qe_subl[hh];
					SWE[hh] = SWE[hh] - Qe_subl[hh];
				}

				if (net_rainD[hh] > 0.0)
					Qp_ebsm[hh] = net_rainD[hh] * tmean[hh] * 4.2 / 1000.0;
				else
					Qp_ebsm[hh] = 0.0;

				if (Qe_subl_from_SWE[hh])
					Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qp_ebsm[hh]; // Qe_ebsm already taken from SWE
				else
					Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qe_ebsm[hh] + Qp_ebsm[hh];

				u_ebsm[hh] = u_ebsm[hh] + Qmelt[hh];

				LWmax[hh] = SWE[hh] * 0.05;

				float t_minus = tmin[hh];
				if (t_minus > 0.0)
					t_minus = 0.0;

				umin = SWE[hh] * (2.115 + 0.00779*t_minus)*t_minus / 1000.0;

				if (umin > u_ebsm[hh])
					u_ebsm[hh] = umin;

				if (u_ebsm[hh] > 0.0) {
					melt = u_ebsm[hh] / 316.8*1000.0; // thermal quality B=0.95. 316.8 = 333.5*0.95 (kJ/kg)
					if (melt + LW_ebsm[hh] > LWmax[hh]) {
						snowmeltD[hh] = melt - (LWmax[hh] - LW_ebsm[hh]);
						if (snowmeltD[hh] > SWE[hh]) {
							snowmeltD[hh] = SWE[hh] + LW_ebsm[hh];
							SWE[hh] = 0.0;
							LW_ebsm[hh] = 0.0;
						}
						else if (SWE[hh] > melt) {
							SWE[hh] = SWE[hh] - melt;
							LW_ebsm[hh] = LWmax[hh];
						}
						else {
							snowmeltD[hh] = SWE[hh] + LW_ebsm[hh];
							SWE[hh] = 0.0;
							LW_ebsm[hh] = 0.0;
						}
						cumsnowmelt[hh] = cumsnowmelt[hh] + snowmeltD[hh];
					}
					else { // melt retained in snowpack
						LW_ebsm[hh] = LW_ebsm[hh] + melt;
						SWE[hh] = SWE[hh] - melt;
						snowmeltD[hh] = 0.0;
					}
					u_ebsm[hh] = 0.0;
				}
				else { // no melt - convert liquid water to ice - reduce u_ebsm accordingly
					Qmelt[hh] = 0.0;
					snowmeltD[hh] = 0.0;

					if (u_ebsm[hh] < 0.0) {
						ref = -u_ebsm[hh] / 333.5*1000.0;
						if (LW_ebsm[hh] > ref) {
							u_ebsm[hh] = 0.0;
							SWE[hh] = SWE[hh] + ref;
							LW_ebsm[hh] = LW_ebsm[hh] - ref;
						}
						else {
							u_ebsm[hh] = u_ebsm[hh] + LW_ebsm[hh] * 333.5 / 1000.0;
							SWE[hh] = SWE[hh] + LW_ebsm[hh];
							LW_ebsm[hh] = 0.0;
						}
					}
				} // no melt
			} // if
			else { // meltflag[hh] == 0. TB addition 02/02/06
				if (tmin[hh] < 0.0)
					u_ebsm[hh] = SWE[hh] * (2.115 + 0.00779*tmin[hh])*tmin[hh] / 1000.0;
				if (LW_ebsm[hh] > 0.0) {
					u_ebsm[hh] = u_ebsm[hh] + LW_ebsm[hh] * 333.5 / 1000.0;
					SWE[hh] = SWE[hh] + LW_ebsm[hh];
				}
				LW_ebsm[hh] = 0.0;
			}
		} // end for HRUs
	} // end if (end of day)
}

void Classebsm::finish(bool good) {

	if (!good) return;

	float Allcumsnowmelt = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (ebsm)' cumQe_subl   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumQe_subl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (ebsm)' cumsnowmelt   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmelt[hh], hru_area[hh], basin_area[0]);

		Allcumsnowmelt += cumsnowmelt[hh] * hru_area[hh];
	}
	LogDebug(" ");
	LogMessage(string("'" + Name + " (ebsm)' Allcumsnowmelt (mm*basin): ").c_str(), Allcumsnowmelt);
	LogDebug(" ");
}

ClassTs* ClassTs::klone(string name) const {
	return new ClassTs(name);
}

void ClassTs::decl(void) {

	Description = "'Estimates snow surface temperature from HRU inputs.' \
                 'Tsnow using variable QliVt_Var (W/m^2),' \
                 'Tsnow using observation Qli (W/m^2).'";

	variation_set = VARIATION_ORG;

	declvar("hru_Ts", NHRU, "snow surface temperature", "(�C)", &hru_Ts);


	declobs("Ts", NHRU, "snow surface temperature", "(�C)", &Ts);


	decllocal("Pa", NHRU, "average surface pressure", "(kPa)", &Pa);

	decllocal("ra", NHRU, "", "(s/m)", &ra);

	decllocal("Qli_", NHRU, "", "(W/m^2)", &Qli_);


	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	decldiagparam("Zref", NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_rh", "()", &hru_rh);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	variation_set = VARIATION_0;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

	variation_set = VARIATION_1;

	declreadobs("Qli", NHRU, "incident long-wave for a flat horizon with vt = 0", "(W/m^2)", &Qli, HRU_OBS_Q);


}

void ClassTs::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRUs to module

	for (hh = 0; hh < nhru; ++hh) {
		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
	}

}

void ClassTs::run(void) { // executed every interval

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Qli_[hh] = QliVt_Var[hh];
			break;
		case VARIATION_1:
			Qli_[hh] = Qli[hh];
			break;
		} // switch

		float T1 = hru_t[hh] + CRHM_constants::Tm;

		float rho = Pa[hh] * 1000 / (CRHM_constants::Rgas*T1);

		float U1 = max<float>(hru_u[hh], 1.0e-3); // Wind speed (m/s)

		ra[hh] = (log(Zref[hh] / Z0snow[hh])*log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

		float delta = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas*sqr(T1));

		float q = (hru_rh[hh] / 100)*Common::Qs(Pa[hh], T1);

		Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_[hh] - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho / ra[hh]) /
			(4.0f*CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*delta)*rho / ra[hh]);

		Ts[hh] -= CRHM_constants::Tm;

		if (Ts[hh] > 0.0) Ts[hh] = 0.0;

		hru_Ts[hh] = Ts[hh];
	} // HRU loop
}

ClassNeedle* ClassNeedle::klone(string name) const {
	return new ClassNeedle(name);
}

void ClassNeedle::decl(void) {

	Description = "'Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), '\
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2), '";

	variation_set = VARIATION_0 + VARIATION_1;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);


	variation_set = VARIATION_0 + VARIATION_2;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


	variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);


	variation_set = VARIATION_2 + VARIATION_3;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);


	variation_set = VARIATION_4;

	declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


	variation_set = VARIATION_ORG;

	declobs("Ts", NHRU, "snow surface temperature", "(�C)", &Ts);

	declobs("Qnsn", NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn);

	declobs("Qsisn", NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn);

	declobs("Qlisn", NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn);

	declobs("Qlosn", NHRU, "reflected long-wave at surface", "(W/m^2)", &Qlosn);


	decldiag("k", NHRU, "extinction coefficient", "()", &k);

	decldiag("Tauc", NHRU, "short-wave transmissivity", "(W/m^2)", &Tauc);

	decllocal("Pa", NHRU, "Average surface pressure", "(kPa)", &Pa);

	declvar("ra", NHRU, "", "(s/m)", &ra);

	declvar("Qnsn_Var", NHRU, "net all-wave at snow surface", "(W/m^2*int)", &Qnsn_Var);


	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "Canopy height(m)", "(m)", &Ht);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	declparam("Zref", NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_rh", "()", &hru_rh);

	declgetvar("*", "SolAng", "(r)", &beta);

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "Albedo", "()", &Albedo);
}

void ClassNeedle::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRU's to module

	for (hh = 0; hh < nhru; ++hh) {
		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa

		if (Ht[hh] > Zwind[hh]) {
			CRHMException TExcept("Vegetation height greater than Intrument reference height or wind reference height, i.e. (Ht > Zref or Ht > Zwind)!", WARNING);
			LogError(TExcept);
		}
	}
}

void ClassNeedle::run(void) { // executed every interval

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Qsi_ = Qsi[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_1:
			Qsi_ = Qsi[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_2:
			Qsi_ = QsiS_Var[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_3:
			Qsi_ = QsiS_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_4:
			Qsi_ = QsiA_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		} // switch

		if (SWE[hh] <= 0.0) { // Do nothing!
			Ts[hh] = 0.0;
			Qnsn[hh] = 0.0;
			Qnsn_Var[hh] = 0.0;

			Qsisn[hh] = 0.0;
			Qlisn[hh] = 0.0;
			Qlosn[hh] = 0.0;

			continue;
		}

		float Exposure = Ht[hh] - DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
		if (Exposure < 0.0) Exposure = 0.0;

		float LAI_ = LAI[hh] * Exposure / Ht[hh];

		float Vf = 0.45 - 0.29*log(LAI[hh]);

		float Vf_ = Vf + (1.0 - Vf)*sin((Ht[hh] - Exposure) / Ht[hh] * M_PI_2);

		float T1 = hru_t[hh] + CRHM_constants::Tm;

		if (beta[hh] > 0.001) {
			k[hh] = 1.081*beta[hh] * cos(beta[hh]) / sin(beta[hh]);

			Tauc[hh] = exp(-k[hh] * LAI_);
		}
		else {
			k[hh] = 0.0;
			Tauc[hh] = 0.0;
		}

		if (SWE[hh] <= 0.0) { // Do nothing!
			Ts[hh] = 0.0;
			continue;
		}

		Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f);

		Qsisn[hh] = Qsi_ * Tauc[hh];


		float rho = Pa[hh] * 1000 / (CRHM_constants::Rgas*T1);

		float U1 = hru_u[hh]; // Wind speed (m/s)

		ra[hh] = (log(Zref[hh] / Z0snow[hh])*log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

		float delta = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas*sqr(T1));

		float q = (hru_rh[hh] / 100)*Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)


		Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_ - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho / ra[hh]) /
			(4 * CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*delta)*rho / ra[hh]);

		Ts[hh] -= CRHM_constants::Tm;

		if (Ts[hh] > 0.0) Ts[hh] = 0.0;

		Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

		// Canopy temperature is approximated by the air temperature.

		Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1 - Albedo[hh]);
		Qnsn_Var[hh] = Qnsn[hh];
	}
}

ClassSimpleRichard* ClassSimpleRichard::klone(string name) const {
	return new ClassSimpleRichard(name);
}

void ClassSimpleRichard::decl(void) {

	Description = "'A simple snow melt model (R. Essery).'";

	declvar("alb", NHRU, "Snow albedo", "()", &alb);

	declvar("snowmelt", NHRU, "snow melt", "(kg/m^2)", &snowmelt);

	declvar("sursubl", NHRU, "Surface sublimation", "(kg/m^2)", &sursubl);

	declvar("meltclark", NHRU, "snow melt delayed", "(kg/m^2)", &meltclark);

	declvar("T0", NHRU, "Surface temperature", "(�C)", &T0);


	declvar("LE", NHRU, "Latent heat flux", "(W/m^2)", &LE);

	declvar("H", NHRU, "Sensible heat flux", "(W/m^2)", &H);

	declvar("Hsm", NHRU, "Snowmelt heat flux", "(W/m^2)", &Hsm);

	declvar("LWn", NHRU, "Net longwave radiation", "(W/m^2)", &LWn);

	declvar("SWn", NHRU, "Net shortwave radiation", "(W/m^2)", &SWn);



	declreadobs("Qsi", NHRU, "short-wave incoming", "W/m^2", &Qsi, HRU_OBS_Q);

	declreadobs("Qli", NHRU, "long-wave incoming", "W/m^2", &Qli, HRU_OBS_Q);

	declreadobs("snow", NHRU, "snowfall rate", "mm/int", &snow, HRU_OBS_misc);

	declreadobs("t", NHRU, "air temperature", "(�C)", &t, HRU_OBS_t_rh_ea);

	declreadobs("u", NHRU, "windspeed", "m/s", &u, HRU_OBS_u);

	declreadobs("rh", NHRU, "relative humidity", "rh", &rh, HRU_OBS_t_rh_ea);


	decldiagparam("a1", NHRU, "[1.08e7]", "0.0", "1.0e8", "Albedo decay time constant for cold snow", "(s)", &a1);

	decldiagparam("a2", NHRU, "[7.2e5]", "0.0", "1.0e8", "Albedo decay time constant for melting snow", "(s)", &a2);

	decldiagparam("amin", NHRU, "[0.5]", "0.0", "1.0", "Minimum albedo for aged snow", "()", &amin);

	decldiagparam("amax", NHRU, "[0.84]", "0.0", "1.0", "Maximum albedo for fresh snow", "()", &amax);

	decldiagparam("smin", NHRU, "[10]", "0.0", "20", "Minimum snowfall to refresh snow albedo", "(mm)", &smin);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	declparam("Zref", NHRU, "[2]", "0.0", "100.0", "Reference height", "(m)", &Zref);

	decldiagparam("Pa", NHRU, "[84]", "10", "1e3", "Average surface pressure", "(KPa)", &Pa);

	decldiagparam("Kstorage", NHRU, "[0.0]", "0.0", "200.0", "storage constant", "(d)", &Kstorage);

	decldiagparam("Lag", NHRU, "[0.0]", "0.0", "960.0", "lag delay", "(h)", &Lag);


	declputvar("*", "SWE", "(mm)", &SWE);


}

void ClassSimpleRichard::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRU's to module

	Delays = new ClassClark(snowmelt, meltclark, Kstorage, Lag, nhru);

	dt = 3600 * 24 / Global::Freq;

	for (hh = 0; hh < nhru; ++hh) {
		T0[hh] = 0.0;
		SWE[hh] = 0.0;
		alb[hh] = 0.84;

		LE[hh] = 0.0;
		H[hh] = 0.0;
		Hsm[hh] = 0.0;
		LWn[hh] = 0.0;
		SWn[hh] = 0.0;
	}
}

void ClassSimpleRichard::run(void) { // executed every interval

	for (hh = 0; chkStruct(); ++hh) {
		float Q1 = (rh[hh] / 100.)*Common::Qs(Pa[hh], t[hh]); // Specific humidity (kg/kg)
		float U1 = max<float>(u[hh], 1.0e-3);    // Wind speed (m/s)
		SURF(hh, Q1, U1);
		U1 = 0;
	}
	Delays->DoClark();
}

// Calculate surface exchange coefficient, Richardson number formulation

void ClassSimpleRichard::EXCH(long hh, float Q1, float U1, float &CH) {

	// Q1         ! Specific humidity (kg/kg)
	// T0         ! Surface temperature (C)
	// t          ! Air temperature (C)
	// U          ! Windspeed (m/s)
	// Z0snow     ! Roughness length (m)
	// Zref       ! Reference height (m)

	// Arguments OUT
	// CH         ! Scalar exchange coefficient
	// Local variables

	float CHn        // Neutral exchange coefficient
		, RiB        // Bulk Richardson number
		, fh         // Stability function
		, fz         // Stability function
		, dT         // Temperature difference (K)
		, dQ;        // Humidity difference

	CHn = sqr(0.4) / (log(Zref[hh] / Z0snow[hh])*log(Zref[hh] / Z0snow[hh]));
	dT = t[hh] - T0[hh];
	dQ = Q1 - Common::Qs(Pa[hh], T0[hh]);
	RiB = 9.81*Zref[hh] * (dT / (t[hh] + CRHM_constants::Tm) + 0.61*dQ) / sqr(U1);
	//  fh = 1.0;

	if (RiB >= 0.0)
		fh = 1.0 / (1.0 + 10.0*RiB);
	else {
		fz = sqrt(Z0snow[hh] / (Zref[hh] + Z0snow[hh])) / 4.0;
		fh = 1.0 - 1.0*RiB / (1.0 + 10.0*CHn*sqrt(-RiB) / fz);
	}

	CH = CHn * fh;
}

// Snow albedo

void ClassSimpleRichard::ALBEDO(long hh) {

	// Arguments IN snow: Snowfall (kg/m**2/int) ,T0 Surface temperature (C) ,dt Timestep (s)


	if (T0[hh] < 0) // cold snow
		alb[hh] = alb[hh] - dt / a1[hh];
	else             // melting snow
		alb[hh] = (alb[hh] - amin[hh])*exp(-dt / a2[hh]) + amin[hh];

	alb[hh] = alb[hh] + (amax[hh] - alb[hh])*snow[hh] / smin[hh];

	if (alb[hh] < amin[hh]) alb[hh] = amin[hh];
	if (alb[hh] > amax[hh]) alb[hh] = amax[hh];
}

// Surface energy balance and temperature

void ClassSimpleRichard::SURF(long hh, float Q1, float U1) {
	// Arguments IN
	// LW         ! Longwave radiation (W/m^2)
	// Pa         ! Surface pressure (KPa)
	// Q1         ! Specific humidity (kg/kg)
	// SNOW       ! Snowfall (kg/m**2/Int)
	// SW         ! Shortwave radiation (W/m^2)
	// t          ! Air temperature (C)
	// U          ! Windspeed (m/s)
	// Zref         ! Reference height (m)
	// dt         ! Timestep (s)

	// Arguments OUT
	// LE         ! Latent heat flux (W/m^2)
	// H          ! Sensible heat flux (W/m^2)
	// Hsm        ! Snowmelt heat flux (W/m^2)
	// LWn        ! Net longwave radiation (W/m^2)
	// SWn        ! Net shortwave radiation (W/m^2)

	// Arguments INOUT
	// alb        ! Albedo
	// swe        ! Snowmass (kg/m^2)
	// T0         ! Surface temperature (C)

	// Local variables
	float A1;         // Penman-Monteith radiative term
	float Ch;         // Surface exchange coefficient
	float dQ1;        // Air humidity deficit
	float D;          // dQs/dT
	float R1;         // Net radiation for T0=t
	float rho;        // Air density (kg/m^3)
	float rKh;        // rho*Ch*U1
	float rKPM;       // Penman-Monteith exchange term

	EXCH(hh, Q1, U1, Ch);

	A1 = 4 * CRHM_constants::sbc*pow(t[hh] + CRHM_constants::Tm, 3.0f);
	dQ1 = Common::Qs(Pa[hh], t[hh]) - Q1;
	D = 0.62*CRHM_constants::Ls*Common::Qs(Pa[hh], t[hh]) / (CRHM_constants::Rgas*sqr(t[hh] + CRHM_constants::Tm));
	R1 = (1.0f - alb[hh])*Qsi[hh] + Qli[hh] - CRHM_constants::sbc*pow(t[hh] + CRHM_constants::Tm, 4.0f);
	rho = Pa[hh] * 1000.0f / (CRHM_constants::Rgas*CRHM_constants::Tm);
	rKh = rho * Ch*U1;
	rKPM = rKh / ((CRHM_constants::Cp + CRHM_constants::Ls*D)*rKh + A1);

	// Surface fluxes and temperature for non-melting snow
	LE[hh] = CRHM_constants::Ls*rKPM*(D*R1 + (CRHM_constants::Cp*rKh + A1)*dQ1);
	H[hh] = CRHM_constants::Cp*rKPM*(R1 - CRHM_constants::Ls*rKh*dQ1);
	SWn[hh] = (1.0 - alb[hh])*Qsi[hh];
	LWn[hh] = H[hh] + LE[hh] - SWn[hh];
	T0[hh] = t[hh] + (R1 - H[hh] - LE[hh]) / A1;
	Hsm[hh] = 0.0;

	// Adjust surface fluxes if snow is melting
	if (T0[hh] > 0 && SWE[hh] > 0.0) {
		T0[hh] = 0.0;
		LE[hh] = CRHM_constants::Ls*rKh*(dQ1 + D * (T0[hh] - t[hh]));
		H[hh] = CRHM_constants::Cp*rKh*(T0[hh] - t[hh]);
		SWn[hh] = (1.0 - alb[hh])*Qsi[hh];
		LWn[hh] = Qli[hh] - CRHM_constants::sbc*pow(t[hh] + CRHM_constants::Tm, 4.0f) + A1 * (t[hh] - T0[hh]);
		Hsm[hh] = SWn[hh] + LWn[hh] - LE[hh] - H[hh];
	}

	// Update SWE and albedo
	SWE[hh] = SWE[hh] + snow[hh];

	snowmelt[hh] = Hsm[hh] / CRHM_constants::Lf*dt;
	sursubl[hh] = -LE[hh] / CRHM_constants::Ls*dt;

	if (snowmelt[hh] + sursubl[hh] > SWE[hh]) {
		snowmelt[hh] = SWE[hh] - sursubl[hh];
		if (snowmelt[hh] < 0.0) {
			snowmelt[hh] = 0.0;
			sursubl[hh] = SWE[hh];
		}
	}

	SWE[hh] -= (snowmelt[hh] + sursubl[hh]);

	SWE[hh] = max<float>(SWE[hh], 0.0);

	ALBEDO(hh);
}

void ClassSimpleRichard::finish(bool good) {

	delete Delays;
}

string Evap_names[] = { "Granger", "Priestley-Taylor", "Penman-Monteith", "Dalton Bulk transfer" };

Classevap* Classevap::klone(string name) const {
	return new Classevap(name);
}

void Classevap::decl(void) {

	Description = "'Calculates interval evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor/Penman-Monteith.'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet); // , NULL, false, CRHM::DIAGNOSTIC

	declvar("hru_evap", NHRU, "interval evaporation", "(mm/int)", &evap);

	declvar("hru_evap_PT", NHRU, "Priestley-Taylor interval evaporation", "(mm/int)", &hru_evap_PT);

	declvar("hru_evapD", NHRU, "daily sum of interval evaporation", "(mm/d)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

	declvar("evapGrangerD", NHRU, "daily Granger evaporation", "(mm/d)", &evapGrangerD);

	decllocal("evap_G", NHRU, "relative evaporation", "()", &G);

	decllocal("evap_D", NHRU, "drying power", "()", &D);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	declparam("evap_type", NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor, 2 = Penman-Monteith.",
		"()", &evap_type);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

	decldiagparam("rs", NHRU, "[0.0]", "0.0", "0.01", "stomatal resistance (Penman-Monteith); water 0.0, crops - 0.000579, short grass - 0.00081, forest - 0.002315", "(d/m)", &rs);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height (Penman-Monteith)", "(m)", &Zwind);

	declgetvar("*", "Rn", "(mm/m^2*int)", &Rn);
	declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
	declgetvar("*", "RnD_POS", "(mm/m^2*d)", &RnD_POS);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_eamean", "kPa", &hru_eamean);
}

void Classevap::init(void) {

	for (hh = 0; chkStruct(); ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cum_evap[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
		D[hh] = 0.0;
		G[hh] = 0.0;
	}
}

void Classevap::run(void) {

	float Q;

	long nstep = getstep() % Global::Freq;


	for (hh = 0; chkStruct(); ++hh) {

		evap[hh] = 0.0;
		hru_evap_PT[hh] = 0.0;
		hru_actet[hh] = 0.0;

		if (inhibit_evap[hh]) {
			evapD[hh] = 0.0;
			evapGrangerD[hh] = 0.0;
			continue;
		}

		if (nstep == 1 || Global::Freq == 1) { // beginning of every day

			evapD[hh] = 0.0;
			evapGrangerD[hh] = 0.0;

			Q = RnD[hh] * (1.0 - F_Qg[hh]); // daily value (mm/d)

			if (Q > 0.0) {
				double Eal = fdaily(hru_umean[hh], Ht[hh])*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]);
				if (Eal > 0.0) {
					D[hh] = Eal / (Eal + Q);
					if (D[hh] > 1.0)
						D[hh] = 1.0;
				}
				else // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
					D[hh] = 0.0;

				G[hh] = 1.0 / (0.793 + 0.2*exp(4.902*D[hh])) + 0.006 * D[hh];
				evapGrangerD[hh] = (delta(hru_tmean[hh]) * G[hh] * Q + gamma(Pa[hh], hru_tmean[hh]) *
					G[hh] * Eal) / (delta(hru_tmean[hh]) * G[hh] + gamma(Pa[hh], hru_tmean[hh]));
			}
		}

		// calculated every interval

		Q = Rn[hh] * (1.0 - F_Qg[hh]); // (mm/d)

		switch (evap_type[hh]) {

		case 0: // Granger
			if (Q > 0.0 && evapGrangerD[hh] > 0.0 && RnD_POS[hh] > 0.0)
				evap[hh] = Q / RnD_POS[hh] / (1.0 - F_Qg[hh])*evapGrangerD[hh];
			else
				evap[hh] = 0.0;
			break;

		case 1: // Priestley-Taylor
			if (Q > 0.0)
				evap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
			else
				evap[hh] = 0.0;

			break;

		case 2: // Penman-Monteith
			if (Q > 0.0) {

				float Z0 = Ht[hh] / 7.6;
				float d = Ht[hh] * 0.67;
				float ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*hru_u[hh]);
				float RHOa = 1E3*Pa[hh] / (CRHM_constants::Rgas*(hru_t[hh] + CRHM_constants::Tm))*(1.0 - 0.379*hru_ea[hh] / Pa[hh]);
				float Cp = 1.005; // (kJ/kg/K)

				evap[hh] = (delta(hru_t[hh])*Q*Global::Freq + (RHOa*Cp /
					(lambda(hru_t[hh])*1e3)*(Common::estar(hru_t[hh]) - hru_ea[hh]) / (ra / 86400))) /
					(delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + rs[hh] / ra)) /
					Global::Freq;
			}
			else
				evap[hh] = 0.0;

			break;

		} // switch

		if (Q > 0.0) // Priestley-Taylor always calculated
			hru_evap_PT[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));

		cum_evap[hh] += evap[hh];
		evapD[hh] += evap[hh];
	} // for
}

void Classevap::finish(bool good) {

	float Allcum_evap = 0.0;
	float Allcum_actet = 0.0;

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "**** " + Evap_names[evap_type[hh]] + " ****";
		LogMessageA(hh, string("'" + Name + " (evap)' hru_cum_evap    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0], s.c_str());
		LogMessageA(hh, string("'" + Name + " (evap)' hru_cum_actet   (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcum_evap += cum_evap[hh] * hru_area[hh];
		Allcum_actet += hru_cum_actet[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (evap)' Allcum_evap  (mm*basin): ").c_str(), Allcum_evap, "*** potential evaporation");
	LogMessage(string("'" + Name + " (evap)' Allcum_actet (mm*basin): ").c_str(), Allcum_actet, "*** actual evaporation");
	LogDebug(" ");

}

double Classevap::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float Classevap::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double Classevap::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

double Classevap::fdaily(float u, float Ht) { // Drying power f(u) (mm/d/kPa)

	float Z0 = Ht * 100.0 / 7.6;
	float a = 8.19 + 0.22*Z0;
	float b = 1.16 + 0.08*Z0;
	return a + b * u;
}

ClassevapD* ClassevapD::klone(string name) const {
	return new ClassevapD(name);
}

void ClassevapD::decl(void) {

	Description = "'Calculates daily evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor.'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	declvar("hru_evapD", NHRU, "daily evaporation", "(mm/d)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

	declvar("evap_G", NHRU, "relative evaporation", "()", &G);

	declvar("evap_D", NHRU, "drying power", "()", &D);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("evap_type", NHRU, "0", "0", "1", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor", "()", &evap_type);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

	declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);

	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_eamean", "(kPa)", &hru_eamean);
}

void ClassevapD::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		evapD[hh] = 0.0;
		cum_evap[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
		D[hh] = 0.0;
		G[hh] = 0.0;
	}
}

void ClassevapD::run(void) {

	float Q;

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (inhibit_evap[hh] && nstep == 1) {
			evapD[hh] = 0.0;
			hru_actet[hh] = 0.0;
			continue;
		}

		if (nstep == 1 || Global::Freq == 1) { // beginning of day

			hru_actet[hh] = 0.0;

			Q = RnD[hh] * (1.0 - F_Qg[hh]); // daily value (mm/d)

			switch (evap_type[hh]) {
			case 0: // Granger
				if (Q > 0.0) {
					double Eal = fdaily(hru_umean[hh], Ht[hh])*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]);
					if (Eal > 0.0) {
						D[hh] = Eal / (Eal + Q);
						if (D[hh] > 1.0)
							D[hh] = 1.0;
					}
					else // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
						D[hh] = 0.0;

					G[hh] = 1.0 / (0.793 + 0.2*exp(4.902*D[hh])) + 0.006 * D[hh];
					evapD[hh] = (delta(hru_tmean[hh]) * G[hh] * Q + gamma(Pa[hh], hru_tmean[hh]) *
						G[hh] * Eal) / (delta(hru_tmean[hh]) * G[hh] + gamma(Pa[hh], hru_tmean[hh]));
				}
				else
					evapD[hh] = 0.0;

				break;

			case 1: // Priestley-Taylor
				if (Q > 0.0)
					evapD[hh] = 1.26*delta(hru_tmean[hh])*Q / (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]));
				else
					evapD[hh] = 0.0;

				break;
			} // switch

			cum_evap[hh] += evapD[hh];
		}
	} // for
}

void ClassevapD::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "**** " + Evap_names[evap_type[hh]] + " ****";
		LogMessageA(hh, string("'" + Name + " (evapD)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0], s.c_str());
		LogMessageA(hh, string("'" + Name + " (evapD)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassevapD::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}


float ClassevapD::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassevapD::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

double ClassevapD::fdaily(float u, float Ht) { // Drying power f(u) (mm/d/kPa)

	float Z0 = Ht * 100.0 / 7.6;
	float a = 8.19 + 0.22*Z0;
	float b = 1.16 + 0.08*Z0;
	return a + b * u;
}

Classsbsm* Classsbsm::klone(string name) const {
	return new Classsbsm(name);
}

void Classsbsm::decl(void) {

	Description = "'Simplified blowing snow model (Richard Essery,  Long Li and John Pomeroy, 1999).'";

	declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

	declvar("wet_snow", NHRU, "wet snow (T was above zero)", "(mm)", &wet_snow);

	declvar("Subl", NHRU, "interval sublimation", "(mm /int)", &Subl);

	declvar("Drift", NHRU, "interval transport", "(mm /int)", &Drift);

	declvar("BasinSnowLoss", BASIN, "transport out of basin", "(mm /int)", &BasinSnowLoss);

	declstatdiag("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

	declstatdiag("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

	declstatdiag("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

	declstatdiag("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

	decllocal("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

	decllocal("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

	decllocal("Prob", NHRU, "Probability", "()", &Prob);

	decllocal("snow_age", NHRU, "snow age", "(h)", &snow_age);

	declvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);



	/* parameters */

	declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

	declparam("basin_area", BASIN, "3.0", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	declparam("zr", NHRU, "[ 0.1,   0.1,   0.05,  0.05,  0.05,  0.05,  0.08 ]", "0.001", "100.0", "Ratio of aerodynamic roughness length to vegetation height", "()", &zr);

	declparam("distrib", NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - do not have to sum to 1", "()", &distrib);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_rh", "(%)", &hru_rh);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void Classsbsm::init(void) {

	nhru = getdim(NHRU);

	hru_basin = new float[nhru];

	dt = 3600 * 24 / Global::Freq;

	cumBasinSnowLoss[0] = 0.0;
	cumBasinSnowGain[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		SWE[hh] = 0.0;
		wet_snow[hh] = 0.0;
		cumSno[hh] = 0.0;
		Drift[hh] = 0.0;
		cumDrift[hh] = 0.0;
		cumDriftIn[hh] = 0.0;
		Subl[hh] = 0.0;
		cumSubl[hh] = 0.0;
		Prob[hh] = 0.0;
		snow_age[hh] = 0.0;
		hru_basin[hh] = hru_area[hh] / basin_area[0];
		snowdepth[hh] = 0.0;
	}
}

void Classsbsm::run(void) {

	float SumDrift, total, SWE_Max, trans;

	for (hh = 0; chkStruct(); ++hh) {

		if (net_snow[hh] > 0.0) {
			SWE[hh] = SWE[hh] + net_snow[hh];
			cumSno[hh] = cumSno[hh] + net_snow[hh];
			snow_age[hh] = 1.0;
		}
		else
			snow_age[hh] += dt / 3600;


		if (hru_t[hh] >= 0.0)
			wet_snow[hh] = SWE[hh];
		else
			wet_snow[hh] = min<float>(SWE[hh], wet_snow[hh]);

		Drift[hh] = 0.0;
		Subl[hh] = 0.0;

		if (hru_u[hh] > 3.0 && SWE[hh] > 0.0) {

			prob();

			if (Prob[hh] > 0.0) {
				float RH = hru_rh[hh];
				if (RH > 1.01)
					RH /= 100.0;
				Drift[hh] = Prob[hh] * transport()*dt / fetch[hh];
				if (!inhibit_subl[hh])
					Subl[hh] = Prob[hh] * ((1.0 - RH) / scale())* sublimation()*dt;

				// handle insufficient snow pack

				if (Drift[hh] + Subl[hh] > SWE[hh]) {
					Subl[hh] = SWE[hh] * Subl[hh] / (Subl[hh] + Drift[hh]);
					Drift[hh] = SWE[hh] - Subl[hh];
				} // end if

				cumDrift[hh] += Drift[hh];
				cumSubl[hh] += Subl[hh];

				SWE[hh] = SWE[hh] - Subl[hh] - Drift[hh];
			}
		}
	} // for

	  // distribute drift


	if (distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
		float Drft = Drift[0] * distrib[0];
		SWE[0] += Drft;
		cumDriftIn[0] += Drft;
		cumBasinSnowGain[0] += Drft * hru_basin[0];
	}

	BasinSnowLoss[0] = 0.0;
	long LastN = 0;

	for (long nn = 0; chkStruct(nn); ++nn) {
		if (distrib[nn] >= 0.0 && nn + 1 < nhru)
			continue;

		SumDrift = 0.0;
		for (long hh = LastN; chkStruct(hh, nn + 1); ++hh)
			if (distrib[nn] != 0.0)
				SumDrift += Drift[hh] * hru_basin[hh];

		if (SumDrift > 0.0) {
			for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {
				SWE_Max = SWEfromDepth(Ht[hh]);

				if (hh == nn) {
					SWE[hh] += SumDrift / hru_basin[hh];
					cumDriftIn[hh] += SumDrift / hru_basin[hh];
					if (SWE[hh] > SWE_Max) {
						if (SWE[hh] - SWE_Max >= Drift[hh]) {
							SWE[hh] -= Drift[hh];
							BasinSnowLoss[0] = Drift[hh];
						}
						else {
							SWE[hh] = SWE_Max;
							BasinSnowLoss[0] = SWE[hh] - SWE_Max;
						}
						BasinSnowLoss[0] *= hru_basin[hh];
						cumBasinSnowLoss[0] += BasinSnowLoss[0];
					}

				}
				else if (SWE_Max > SWE[hh] && distrib[hh] > 0.0) {

					total = 0.0;
					for (long jj = hh; chkStruct(jj, nn); jj++)
						total = total + fabs(distrib[jj]);

					trans = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];

					if (SWE_Max > SWE[hh] + trans) {
						SWE[hh] += trans;
					}
					else {
						trans = SWE_Max - SWE[hh];
						SWE[hh] = SWE_Max;
					}
					SumDrift -= trans * hru_basin[hh];
					cumDriftIn[hh] += trans;
				}
			} // end for (hh)
		} // end if
		LastN = nn + 1;
	} // end for (nn)

	for (hh = 0; chkStruct(); ++hh) {
		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0;
		}
	} // for
}

void Classsbsm::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (sbsm)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (sbsm)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (sbsm)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (sbsm)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (sbsm)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}

	LogMessage("'sbsm' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]);
	LogMessage("'sbsm' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]);
	LogDebug(" ");

	delete[] hru_basin;
	hru_basin = NULL;
}

//=======================================================================
float Classsbsm::transport(void) {
	//=======================================================================
	return ((0.00096f*sqr(hru_t[hh]) + 0.5298f*hru_t[hh] + 666.82f)*pow(hru_u[hh] / 25.0f, 4.0f)) / 1000.0f;
}

//=======================================================================
float Classsbsm::sublimation(void) {
	//=======================================================================
	return  137.6f*pow(hru_u[hh] / 25.0f, 5.0f) / 1000.0f;
}

//=======================================================================
float Classsbsm::scale(void) {
	//=======================================================================
	float
		cond,       // Thermal conductivity of air (W/m/K)
		diff,       // Diffusivity of water vapour in air (m^2/s)
		rsat,       // Saturation density of water vapour (kg/m3)
		tk;         // Temperature (K)

	float const ls = 2.838e6; // Latent heat of sublimation (J/kg)
	float const m = 18.01;    // Molecular weight of water (kg/kmole)
	float const r = 8313.0;   // Universal gas constant (J/kmole/K)

	tk = hru_t[hh] + 273.0f;
	diff = 2.06e-5f*pow(tk / 273.0f, 1.75f);
	rsat = m * 611.15f*exp(22.45*hru_t[hh] / tk) / (r*tk);
	cond = 0.000076843*tk + 0.003130762;
	return ((ls*m / (r*tk)) - 1.0f) / (cond*(hru_t[hh] + 273.0f)) + 1.0f / (ls*diff*rsat);
}

//=======================================================================
void Classsbsm::prob(void) {
	//=======================================================================

	float
		mean        // Mean of cumulative normal distribution
		, var         // Standard deviation
		, rho         // Snow density (kg/m3)
		, sd          // Snow depth (m)
		, us;

	//  float const ht[] = { 0.01,  0.01,  0.08,  0.08,  1.0,   1.0,   3.   };// Vegetation height (m)
	//  float const zr[] = { 0.1,   0.1,   0.05,  0.05,  0.05,  0.05,  0.08 };// Ratio of aerodynamic roughness length to vegetation height
	//     1 - water      2 - soil      3 - open tundra
	//     4 - sparse shrub tundra      5 - shrub tundra
	//     6 - dense shrub tundra       7 - sparse forest

	bool dry_snow = hru_t[hh] < 0.0;

	mean = 0.365*hru_t[hh] + 0.00706*sqr(hru_t[hh]) + 0.91*log(snow_age[hh]) + 11.0;
	var = 0.145*hru_t[hh] + 0.00196*sqr(hru_t[hh]) + 4.23;

	if (!dry_snow) {
		mean = 21.0;
		var = 7.0;
	}

	rho = 240.;
	if (SWE[hh] > 145.45)
		rho = 69.856*log(SWE[hh]) - 74.732;
	sd = SWE[hh] / rho;
	us = hru_u[hh];
	if (sd < Ht[hh])
		us = us / sqrt(1. + PBSM_constants::Beta * 2 * zr[hh] * (Ht[hh] - sd));

	Prob[hh] = 1.0 / (1.0 + exp(1.7*(mean - us) / var));

	if (SWE[hh] <= wet_snow[hh]) {
		Prob[hh] = 1 / (1. + exp(1.7*(21.0 - us) / 7.0));
		if (us <= 7.0) Prob[hh] = 0.0;
	}

	if (sd <= 0.01) Prob[hh] = 0.0;

	if (dry_snow) {
		if (us <= 3.0)
			Prob[hh] = 0.0;
	}
	else {
		if (us <= 7.0)
			Prob[hh] = 0.0;
	}
}

Classcrack* Classcrack::klone(string name) const {
	return new Classcrack(name);
}

void Classcrack::decl(void) {

	Description = "'Handles frozen soil infiltration using Granger et al. 1984; Gray et al., 1986.'";

	declvar("snowinfil", NHRU, "infiltration", "(mm/d)", &snowinfil);

	declstatdiag("cumsnowinfil", NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/d)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

	declvar("infil", NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	declstatvar("crackstat", NHRU, "infiltration status", "()", &crackstat);

	declstatdiag("RainOnSnow", NHRU, "cumulative rain on snow", "(mm)", &RainOnSnow);

	declstatvar("crackon", NHRU, "crack cycle enabled", "()", &crackon);


	decllocal("RainOnSnowA", NHRU, "accumulated rain on snow", "(mm)", &RainOnSnowA);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("fallstat", NHRU, "[50.0]", "-1.0", "100.0",
		"fall status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", &fallstat);

	decldiagparam("Major", NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", &Major);

	decldiagparam("PriorInfiltration", NHRU, "[1]", "0", "1", "allow limited melt to infiltrate prior to first major melt", "(mm/d)", &PriorInfiltration);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "snowmeltD", "(mm/d)", &snowmelt);
	declgetvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "net_rain", "(mm/int)", &net_rain);
}

void Classcrack::init(void) {

	nhru = getdim(NHRU);

	try {

		Xinfil = new float*[3];   // Data [3] [nhru]
		for (int jj = 0; jj < 3; ++jj)
			Xinfil[jj] = new float[nhru];

		timer = new long[nhru];
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in module CRACK.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	for (hh = 0; hh < nhru; ++hh) {
		infil[hh] = 0.0;
		cuminfil[hh] = 0.0;
		snowinfil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		runoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		meltrunoff[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;

		RainOnSnow[hh] = 0.0;
		RainOnSnowA[hh] = 0.0;

		crackon[hh] = false;
		crackstat[hh] = 0;

		timer[hh] = 0;
		Xinfil[0][hh] = 0.0;
		Xinfil[1][hh] = 0.0;
		Xinfil[2][hh] = 0.0;
	}
}

void infil_index(float Theta, float SWE, float & Index, float & Pot) {

	Pot = 5 * (1 - Theta)*pow(SWE, 0.584f);
	Index = Pot / SWE;
	if (Index > 1.0) Index = 1;
	Pot = Pot / 6;
}

void Classcrack::run(void) {

	long nstep;

	nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // every interval
		infil[hh] = 0.0;
		if (net_rain[hh] > 0.0) {
			if (crackon[hh])
				RainOnSnowA[hh] += net_rain[hh];
			else {
				infil[hh] = net_rain[hh];
				cuminfil[hh] += net_rain[hh];
			}
		}
	}

	if (nstep == 0) // end of every day
		for (hh = 0; chkStruct(); ++hh) {

			if (SWE[hh] > 25.0 && !crackon[hh]) {
				crackstat[hh] = 0;
				crackon[hh] = true; // initialise for current year
				timer[hh] = 0;
				Xinfil[0][hh] = 0.0;
				Xinfil[1][hh] = 0.0;
				Xinfil[2][hh] = 0.0;
			}

			snowinfil[hh] = 0.0;
			meltrunoff[hh] = 0.0;

			if (crackon[hh] && snowmelt[hh] > 0.0) {

				if (timer[hh] > 0 && crackstat[hh] > 0)

					// ice lens forms, if next day below -10 limited

					if (fallstat[hh] > 0.0 && hru_tmax[0] < -10.0) crackstat[hh] = 10;

				// unlimited - (fallstat[hh].eq.0.0)

				if (fallstat[hh] <= 0.0) {

					snowinfil[hh] = snowmelt[hh];
					crackstat[hh] = 1;
				}

				// limited - (0.0 < fallstat[hh] < 100.0)

				else if (fallstat[hh] < 100.0) {
					if (snowmelt[hh] >= Major[hh] || crackstat[hh] >= 1) {
						if (SWE[hh] > Xinfil[2][hh] && snowmelt[hh] >= Major[hh]) {
							infil_index(fallstat[hh] / 100.0, SWE[hh], Xinfil[0][hh], Xinfil[1][hh]);
							Xinfil[2][hh] = SWE[hh];
						}
						if (snowmelt[hh] >= Major[hh]) {
							if (crackstat[hh] <= 0)
								crackstat[hh] = 1;
							else
								crackstat[hh] = crackstat[hh] + 1;

							timer[hh] = 1;
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];
							if (snowinfil[hh] > Xinfil[1][hh]) snowinfil[hh] = Xinfil[1][hh];
						}
						else
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];

						if (crackstat[hh] > 6)
							snowinfil[hh] = 0;
					}
					else
						if (PriorInfiltration[hh])
							snowinfil[hh] = snowmelt[hh]; // zero by default
				}

				// restricted - (fallstat[hh].ge.100.0)

				else if (fallstat[hh] >= 100.0) {
					snowinfil[hh] = 0.0;
					crackstat[hh] = 1;
				}

				meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

				if (snowinfil[hh] > 0.0)
					snowinfil[hh] += RainOnSnowA[hh];
				else
					meltrunoff[hh] += RainOnSnowA[hh];

				cumsnowinfil[hh] += snowinfil[hh];
				cummeltrunoff[hh] += meltrunoff[hh];

				RainOnSnow[hh] += RainOnSnowA[hh];
				RainOnSnowA[hh] = 0.0;

			} // end if
			else if (snowmelt[hh] > 0.0) {
				snowinfil[hh] = snowmelt[hh];
				cumsnowinfil[hh] += snowinfil[hh];
			}

			if (crackstat[hh] > 0 && SWE[hh] <= 0.0) {
				crackon[hh] = false;
				crackstat[hh] = 0;
			}
		}   // end for
}

void Classcrack::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (crack)' cumsnowinfil    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (crack)' cummeltrunoff   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (crack)' cuminfil(rain)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (crack)' cumrunoff(rain) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (crack)' RainOnSnow      (mm) (mm*hru) (mm*hru/basin): ").c_str(), RainOnSnow[hh], hru_area[hh], basin_area[0], "information only - amount of rain handled as snow");
		LogDebug(" ");
	}

	if (Xinfil != NULL) {
		for (int ii = 0; ii < 3; ii++)
			delete[] Xinfil[ii];  //Array [3] [nhru]

		delete[] Xinfil;
		Xinfil = NULL;
	}

	delete[] timer;
	timer = NULL;
}

ClassKevin* ClassKevin::klone(string name) const {
	return new ClassKevin(name);
}

void ClassKevin::decl(void) {

	Description = "'Melt model loosely based on thesis (K. Shook).'";

	declvar("winter", NHRU, "winter = 1 - true", "()", &winter);

	declvar("SnowStat", NHRU, "EARLY/MATURE/HOLD 0/1/2", "()", &SnowStat);

	declvar("sca", NHRU, "snow covered area", "()", &sca);

	declvar("snowmelt", NHRU, "snow melt", "(mm/int)", &snowmelt);

	declvar("netLong", NHRU, "net long-wave", "(mm/int)", &netLong);

	declvar("netShort", NHRU, "net long-wave", "(mm/int)", &netShort);

	declvar("snowmeltD", NHRU, "daily snow melt", "(mm/d)", &snowmeltD);

	declvar("cumsnowmelt", NHRU, "cumulative snow melt", "(mm)", &cumsnowmelt);

	decldiag("albedo", NHRU, "areal albedo()", "()", &albedo);


	decldiagparam("Asnow1", NHRU, "0.8", "0", "1", "early snow albedo", "()", &Asnow1);

	decldiagparam("Asnow2", NHRU, "0.6", "0", "1", "mature snow albedo", "()", &Asnow2);

	decldiagparam("Asoil", NHRU, "0.2", "0.1", "1", "soil albedo", "()", &Asoil);

	declparam("cv", NHRU, "0.33", "0.2", "0.7", "coefficient of variation", "()", &cv);

	declparam("tfactor", NHRU, "0.1", "0.0", "10.0", "degree interval melt factor", "(mm/d*�C)", &tfactor);

	declparam("nfactor", NHRU, "0.0", "0.0", "10.0", "net radiation factor (typical value 3.0 (mm/MJ*m^2*d))", "(mm/MJ*m^2*d)", &nfactor);

	declparam("meltthresh", NHRU, "1.0", "0.0", "10.0", "melt threshold to become mature pack", "(mm/d)", &meltthresh);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declputvar("*", "SWE", "(mm)", &SWE);

	declreadobs("hru_Qn", NHRU, "net radiation", "(W/m^2)", &hru_Qn, 0, true);


	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_eamean", "(kPa)", &hru_eamean);
	declgetvar("*", "hru_SunAct", "(h)", &hru_SunAct);
	declgetvar("*", "SunMax", "(h)", &SunMax);
	declgetvar("*", "Qdro", "(W/m^2)", &Qdro);
	declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);
}

void ClassKevin::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh)
		if (nfactor[hh] != 0.0 && hru_Qn == NULL) {
			CRHMException TExcept("Kevin: nfactor > 0.0 with observation 'hru_Qn' not defined!", TERMINATE);
			LogError(TExcept);
		}

	SWEpeak = new float[nhru];
	SWElast = new float[nhru];

	for (hh = 0; hh < nhru; ++hh) {
		snowmelt[hh] = 0.0;
		cumsnowmelt[hh] = 0.0;
		netLong[hh] = 0.0;
		netShort[hh] = 0.0;
		if (SWE[0] > 50.0) // use hru #1
			for (long hh = 0; hh < nhru; ++hh) {
				winter[hh] = 1;
				albedo[hh] = Asnow1[hh];
				sca[hh] = 1.0;
			}
		else {
			winter[hh] = 0;
			albedo[hh] = Asoil[hh];
			sca[hh] = 0.0;
		}

		SnowStat[hh] = EARLY;
		SWEpeak[hh] = SWE[hh];
		SWElast[hh] = SWE[hh];
	} // for HRU
}

void ClassKevin::run(void) {

	float melt, netlong, shortw, net;

	long nstep = getstep() % Global::Freq;

	long jday = julian("now");
	float hemisphere = (hru_lat[0] < 0.0); // use hru #1
	if ((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[0] > 5.0 && nstep == 1) // use hru #1
		for (hh = 0; chkStruct(); ++hh) {
			winter[hh] = 1;
			albedo[hh] = Asnow1[hh];
			sca[hh] = 1.0;
		}

	for (hh = 0; chkStruct(); ++hh) {

		snowmelt[hh] = 0.0;
		if (nstep == 1) // beginning of every day
			snowmeltD[hh] = 0.0;

		if (SWE[hh] <= 0.0) {
			albedo[hh] = Asoil[hh];
			sca[hh] = 0.0;
			SnowStat[hh] = EARLY;
			continue;
		}

		// snow accounting handled in PBSM

		if ((tfactor[hh] > 0.0) || (nfactor[hh] > 0.0)) {
			melt = 0.0;
			if (hru_t[hh] > 0.0)
				melt += hru_t[hh] * tfactor[hh] / Global::Freq;
			if (hru_Qn) { // observation available
				if (hru_Qn[hh] > 0.0)
					melt += hru_Qn[hh] * nfactor[hh] * WtoMJ_D / Global::Freq;
			}
		}
		else {

			// t Kelvin degrees, ea bar

			netlong = -0.85 + 0.97*CRHM_constants::SB*pow(hru_tmean[hh] + 273.0f, 4.0f)*(-0.39f + 0.093f*sqrt(hru_eamean[hh]))*
				(0.26f + 0.81f*(hru_SunAct[hh] / SunMax[hh]));
			netLong[hh] = netlong;

			if (hru_SunAct[hh] > 0.0)
				shortw = (0.024f + 0.974f*pow(hru_SunAct[hh] / SunMax[hh], 1.35f))*Qdro[hh] * WtoMJ_D +
				(2.68f + 2.2f*(hru_SunAct[hh] / SunMax[hh]) - 3.85f*sqr(hru_SunAct[hh] / SunMax[hh]))*Qdfo[hh] * WtoMJ_D;
			else
				shortw = (0.024f*Qdro[hh] + 2.68f*Qdfo[hh])*WtoMJ_D;

			netShort[hh] = shortw;

			if (SnowStat[hh] == MATURE)
				net = (shortw*(1.0f - Asnow2[hh]) + netlong) / Global::Freq; // MJ/day to MJ/interval
			else
				net = (shortw*(1.0f - Asnow1[hh]) + netlong) / Global::Freq; // MJ/day to MJ/interval

			if (net > 0.0)
				melt = net / 0.3336f; // Latent heat of fusion, 0.3336 MJ/kg

			else
				melt = 0.0;
		}

		switch (SnowStat[hh]) {

		case EARLY:
			if (melt > 0.0) {
				if (melt > SWE[hh]) {
					melt = SWE[hh];
					SWE[hh] = 0.0;
					snowmelt[hh] = melt;
					sca[hh] = 0.0;
					albedo[hh] = Asoil[hh];
				}
				else {
					SWE[hh] -= melt;
					snowmelt[hh] = melt;
					sca[hh] = 1.0;
					albedo[hh] = Asnow1[hh];
				}
			}
			break;

		case MATURE:

			if (SWE[hh] > SWElast[hh]) { // additional snow - falling or drifting

				if (melt > 0.0) { // handle melt
					SWE[hh] -= melt;
					snowmelt[hh] = melt;
				}

				if (SWE[hh] > SWEpeak[hh]) { // snow fall exceeding last peak
					SWEpeak[hh] = SWE[hh];
					LogMessage(hh, " add to SWE peak ", SWEpeak[hh], DT);
				}
				else
					if (SWE[hh] > SWElast[hh]) SnowStat[hh] = HOLD;

				SWElast[hh] = SWE[hh];
				sca[hh] = 1.0;
				albedo[hh] = Asnow1[hh];

				break;
			}

			if (melt > 0.0) {
				sca[hh] = Common::SWE_prob(SWEpeak[hh], SWEpeak[hh] - SWElast[hh], cv[hh]);
				if (sca[hh] >= 0.01) {
					snowmelt[hh] = melt * sca[hh];
					if (snowmelt[hh] > SWE[hh]) snowmelt[hh] = SWE[hh];
					SWE[hh] -= snowmelt[hh];

					SWElast[hh] = SWE[hh];
					albedo[hh] = Asnow2[hh] * sca[hh] + Asoil[hh] * (1.0 - sca[hh]);
				}
				else {  // when SCA less than 0.01 - no snow!
					snowmelt[hh] = SWE[hh];
					SWE[hh] = 0.0;
					winter[hh] = 0;
					SnowStat[hh] = EARLY;
					sca[hh] = 0.0;
					albedo[hh] = Asoil[hh];
					LogMessage(hh, " going to 'EARLY' SWE ", SWE[hh], DT);
				}
			}
			break;

		case HOLD:
			sca[hh] = 1.0;
			albedo[hh] = Asnow1[hh];

			if (melt > 0.0) {
				if (melt > SWE[hh]) melt = SWE[hh];
				SWE[hh] -= melt;
				snowmelt[hh] += melt;
			}

			if (SWElast[hh] >= SWE[hh] || SWE[hh] >= SWEpeak[hh]) { // return to lognormal distribution
				SnowStat[hh] = MATURE;
				SWElast[hh] = SWE[hh];
			}
			break;
		} // switch

		snowmeltD[hh] += snowmelt[hh]; // accumulate daily melt
		cumsnowmelt[hh] += snowmelt[hh];

		if (nstep == 0) // end of every day
			if (snowmeltD[hh] >= meltthresh[hh] && SnowStat[hh] == EARLY && SWE[hh] > 5) {  // use today's melt // threshold for major melt event(5 mm/day)
				SnowStat[hh] = MATURE;   // switch to MATURE
				SWEpeak[hh] = SWE[hh];
				LogMessage(hh, "'Kevin' SWE peak ", SWEpeak[hh], DT);
				LogDebug(" ");
				SWElast[hh] = SWE[hh];
			}
	} // for HRU
}

void ClassKevin::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Kevin)' cumsnowmelt (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmelt[hh], hru_area[hh], basin_area[0]);
	}
	LogDebug(" ");

	delete[] SWEpeak;
	SWEpeak = NULL;
	delete[] SWElast;
	SWElast = NULL;
}

ClassGreencrack* ClassGreencrack::klone(string name) const {
	return new ClassGreencrack(name);
}

void ClassGreencrack::decl(void) {

	Description = "'Handles summer using Green Ampt and frozen soil infiltration using Granger et al. 1984; Gray et al., 1986.'";

	declvar("infil", NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

	declvar("snowinfil", NHRU, "infiltration", "(mm/int)", &snowinfil);

	declstatdiag("cumsnowinfil", NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

	declvar("crackstat", NHRU, "infiltration status", "()", &crackstat);

	declstatvar("RainOnSnow", NHRU, "cumulative rain on snow", "(mm)", &RainOnSnow);

	declstatvar("crackon", NHRU, "crack cycle enabled", "()", &crackon);


	decllocal("RainOnSnowA", NHRU, "accumulated rain on snow", "(mm)", &RainOnSnowA);

	decllocal("k", NHRU, "(mm/h)", "()", &k);

	decllocal("F0", NHRU, "last HRU cumulative infiltration", "(mm)", &F0);

	decllocal("f0", NHRU, "", "(mm/h)", &f0);

	decllocal("F1", NHRU, "HRU cumulative infiltration", "(mm)", &F1);

	decllocal("f1", NHRU, "", "(mm/h)", &f1);

	decllocal("dthbot", NHRU, "", "()", &dthbot);

	decllocal("psidthbot", NHRU, "", "(mm)", &psidthbot);

	decllocal("timer", NHRU, "", "(d)", &timer);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("fallstat", NHRU, "[50.0]", "-1.0", "100.0",
		"fall status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", &fallstat);

	decldiagparam("Major", NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", &Major);

	declparam("soil_type", NHRU, "[4]", "0", "12",
		"water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
		" 0 - 12", "()", &soil_type);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "2500.0",
		"Initial value of available water in soil profile", "(mm)", &soil_moist_init);

	decldiagparam("PriorInfiltration", NHRU, "[0]", "0", "1", "allow limited melt to infiltrate prior to major melt", "()", &PriorInfiltration);


	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);

	declgetvar("*", "snowmeltD", "(mm/d)", &snowmelt);

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_rain", "(mm/int)", &net_rain);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);


}

void ClassGreencrack::init(void) {

	nhru = getdim(NHRU);

	try {

		Xinfil = new float*[3];   // Data [3] [nhru]
		for (int jj = 0; jj < 3; ++jj)
			Xinfil[jj] = new float[nhru];
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in module CRACK.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	for (hh = 0; hh < nhru; ++hh) {
		infil[hh] = 0.0;
		cuminfil[hh] = 0.0;
		snowinfil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		runoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		meltrunoff[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;

		RainOnSnow[hh] = 0.0;
		RainOnSnowA[hh] = 0.0;

		crackstat[hh] = 0;
		crackon[hh] = false;

		timer[hh] = 0;
		Xinfil[0][hh] = 0.0;
		Xinfil[1][hh] = 0.0;
		Xinfil[2][hh] = 0.0;

		F1[hh] = soil_moist_max[hh];
		k[hh] = soilproperties[soil_type[hh]][KSAT];

		if (soil_moist_max[hh] > 0.0)  // handle zero
			dthbot[hh] = (1.0 - soil_moist_init[hh] / soil_moist_max[hh]);
		else {
			dthbot[hh] = 1.0;
			continue;
		}

		psidthbot[hh] = soilproperties[soil_type[hh]][PSI] * dthbot[hh];
		f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0;
	}
}

void ClassGreencrack::run(void) {

	long nstep;

	nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // every interval
		if (crackon[hh])
			RainOnSnowA[hh] += net_rain[hh];

		infil[hh] = 0.0;
		snowinfil[hh] = 0.0;
		runoff[hh] = 0.0;
		meltrunoff[hh] = 0.0;
	}

	if (nstep == 0) { // end of every day
		for (hh = 0; chkStruct(); ++hh) {

			if (SWE[hh] > 25.0 && !crackon[hh]) {
				crackstat[hh] = 0;
				crackon[hh] = true; // initialise for current year
				timer[hh] = 0;
				Xinfil[0][hh] = 0.0;
				Xinfil[1][hh] = 0.0;
				Xinfil[2][hh] = 0.0;
			}

			if (crackon[hh] && snowmelt[hh] > 0.0) {

				if (timer[hh] > 0 && crackstat[hh] > 0)

					// ice lens forms, if next day below -10 limited

					if (fallstat[hh] > 0.0 && hru_tmax[0] < -10.0) crackstat[hh] = 10;

				// unlimited - (fallstat[hh].eq.0.0)

				if (fallstat[hh] <= 0.0) {

					snowinfil[hh] = snowmelt[hh];
					crackstat[hh] = 1;
				}

				// limited - (0.0 < fallstat[hh] < 100.0)

				else if (fallstat[hh] < 100.0) {
					if (snowmelt[hh] >= Major[hh] || crackstat[hh] >= 1) {
						if (SWE[hh] > Xinfil[2][hh] && snowmelt[hh] >= Major[hh]) {
							infil_index(fallstat[hh] / 100.0, SWE[hh], Xinfil[0][hh], Xinfil[1][hh]);
							Xinfil[2][hh] = SWE[hh];
						}
						if (snowmelt[hh] >= Major[hh]) {
							if (crackstat[hh] <= 0)
								crackstat[hh] = 1;
							else
								crackstat[hh] = crackstat[hh] + 1;

							timer[hh] = 1;
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];
							if (snowinfil[hh] > Xinfil[1][hh]) snowinfil[hh] = Xinfil[1][hh];
						}
						else
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];

						if (crackstat[hh] > 6)
							snowinfil[hh] = 0;
					}
					else
						if (PriorInfiltration[hh])
							snowinfil[hh] = snowmelt[hh]; // zero by default
				}

				// restricted - (fallstat[hh].ge.100.0)

				else if (fallstat[hh] >= 100.0) {
					snowinfil[hh] = 0.0;
					crackstat[hh] = 1;
				}

				meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

				if (snowinfil[hh] > 0.0)
					snowinfil[hh] += RainOnSnowA[hh];
				else
					meltrunoff[hh] += RainOnSnowA[hh];

				cumsnowinfil[hh] += snowinfil[hh];
				cummeltrunoff[hh] += meltrunoff[hh];

				RainOnSnow[hh] += RainOnSnowA[hh];
				RainOnSnowA[hh] = 0.0;

			} // end if(crackon[hh] && snowmelt[hh])
			else if (snowmelt[hh] > 0.0) {
				snowinfil[hh] = snowmelt[hh];
				cumsnowinfil[hh] += snowinfil[hh];
			}

			if (crackstat[hh] > 0 && SWE[hh] <= 0.0) {
				crackon[hh] = false;
				crackstat[hh] = 0;
			}
		} // for
	} // end of every day

	  // greenampt routine

	for (hh = 0; chkStruct(); ++hh) {
		if (!crackon[hh] && net_rain[hh] > 0.0) {

			garain = net_rain[hh]; // precipitation/interval
			intensity = net_rain[hh] * Global::Freq / 24.0; // convert to mm/h

			if (garain > 0.0) {
				if (soil_type[hh] == 12) { // handle pavement separately
					runoff[hh] = garain;
				}
				else if (soil_type[hh] == 0 || soil_moist[hh] <= 0.0) { // handle water separately
					infil[hh] = garain;
					cuminfil[hh] += infil[hh];
				}
				else {
					F1[hh] = soil_moist[hh];
					dthbot[hh] = (1.0 - soil_moist[hh] / soil_moist_max[hh]);
					psidthbot[hh] = soilproperties[soil_type[hh]][PSI] * dthbot[hh];
					if (soil_type[hh] > 0) // not water!
						f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0; // infiltrate first interval rainfall (mm/h)

					infiltrate();

					infil[hh] = F1[hh] - F0[hh];
					cuminfil[hh] += infil[hh];

					if (pond > 0.0)
						runoff[hh] = pond;
				}
			}

			cumrunoff[hh] += runoff[hh];

		} // if(!crackon[hh] && net_rain[hh] > 0.0) greenampt routine
	} // for
}

void ClassGreencrack::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Greencrack)' cumsnowinfil  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Greencrack)' cummeltrunoff (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Greencrack)' cuminfil      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Greencrack)' cumrunoff     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Greencrack)' RainOnSnow    (mm) (mm*hru) (mm*hru/basin): ").c_str(), RainOnSnow[hh], hru_area[hh], basin_area[0], "information only - amount of rain handled as snow");
		LogDebug(" ");
	}

	if (Xinfil != NULL) {
		for (int ii = 0; ii < 3; ii++)
			delete[] Xinfil[ii];  // Array [3] [nhru]

		delete[] Xinfil;
		Xinfil = NULL;
	}
}

void ClassGreencrack::infiltrate(void) {

	F0[hh] = F1[hh]; // last interval final values become initial values
	f0[hh] = f1[hh]; // last interval final values become initial values

	if (soil_type[hh] == 0) { // water!
		pond += garain;
		return;
	}
	pond = 0.0;

	f0[hh] = calcf1(F0[hh], psidthbot[hh]); // (mm/h)

	if (intensity > f0[hh]) { // (mm/h). Greater than initial
		ponding(); // already ponding
		return;
	}

	F1[hh] = F0[hh] + garain;

	f1[hh] = calcf1(F1[hh], psidthbot[hh]); // (mm/h)

	if (intensity > f1[hh]) // (mm/h). Greater than end
		startponding(); // ponding begins during interval
}

void ClassGreencrack::ponding(void) {

	F1[hh] = F0[hh] + garain;

	howmuch(F0[hh], Global::Interval*24.0);

	pond = F0[hh] + garain - F1[hh];
}

void ClassGreencrack::startponding(void) { // ponding during interval

	float Fp = k[hh] * psidthbot[hh] / (intensity - k[hh]); // (mm/h)
	float dt = (Fp - F0[hh]) / intensity;

	howmuch(F0[hh], Global::Interval*24.0 - dt);

	pond = F0[hh] + garain - F1[hh];
}

void ClassGreencrack::howmuch(float F0, float dt) { // output is F1[hh]

	float LastF1;
	do {
		LastF1 = F1[hh];
		F1[hh] = F0 + k[hh] * dt + psidthbot[hh] * log((F1[hh] + psidthbot[hh]) / (F0 + psidthbot[hh]));
	} while (fabs(LastF1 - F1[hh]) > 0.01);
}

float ClassGreencrack::calcf1(float F, float psidth) { // calculates infitration rate

	return k[hh] * (psidth / F + 1.0); // (mm/h)
}

Classfrostdepth* Classfrostdepth::klone(string name) const {
	return new Classfrostdepth(name);
}

void Classfrostdepth::decl(void) {

	Description = "'Frost penetration (Van Wijk W. R., (1963) Physics of Plant Environment. North-Holland Publishing Company - Amsterdam, pp.166).'";

	declstatvar("frostdepth", NHRU, "frost penetration", "(m)", &frostdepth);

	declstatvar("Findex", NHRU, "freezing index", "(d* �C)", &Findex);

	declstatvar("Tfreeze", NHRU, "duration of freezing period in days", "(d)", &Tfreeze);

	declstatvar("Lacc", NHRU, "cumulative effective latent heat", "(MJ/m^3)", &Lacc);

	declstatvar("Cacc", NHRU, "cumulative effective heat capacity", "(MJ/(m^3*K))", &Cacc);

	declstatvar("Kacc", NHRU, "cumulative effective thermal conductivity", "(W/(m*K))", &Kacc);


	declparam("Ta", NHRU, "[10]", "-10.0", "50.0", "annual air temperature", "(�C)", &Ta);

	declparam("soil_type", NLAY, "[2]", "1", "4",
		"HRU soil type: 1= sand, 2= loam, 3= clay, 4 = organic", "()", &soil_type, &soil_type_lay);

	declparam("por", NLAY, "[0.5]", "0.0", "1.0", "porosity", "(m^3/m^3)", &por, &por_lay);

	declparam("theta", NLAY, "[0.5]", "0.0", "1.0", "degree of saturation", "(m^3/m^3)", &theta, &theta_lay);

	declparam("d", NLAY, "[2.0]", "0.0", "100.0", "layer depth", "(m)", &d, &d_lay);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);


	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "snowdepth", "(m)", &snowdepth);
}

const float ko = 0.21;  // W/(m K) organic material
const float km = 2.50;  // W/(m K) mineral
const float ka = 0.025; // W/(m K) air
const float ki = 2.24;  // W/(m K) ice
const float kw = 0.57;  // W/(m K) water
const float Cm = 2.000; // MJ/(m3.K) mineral
const float Cw = 4.185; // MJ/(m3.K) water
const float Ca = 0.001; // MJ/(m3.K) air
const float Co = 0.110; // MJ/(m3.K) organic
const float Ci = 1.950; // MJ/(m3.K) ice

void Classfrostdepth::init(void) {

	nlay = getdim(NLAY);
	nhru = getdim(NHRU);

	//  Lacc = new float[nhru];
	//  Cacc = new float[nhru];
	//  Kacc = new float[nhru];

	k_lay = new float*[nlay];   // Array  [nlay][nhru]
	L_lay = new float*[nlay];   // Array  [nlay][nhru]
	c_lay = new float*[nlay];   // Array  [nlay][nhru]

	for (int nn = 0; nn < nlay; ++nn) {
		k_lay[nn] = new float[nhru];
		L_lay[nn] = new float[nhru];
		c_lay[nn] = new float[nhru];
	}

	for (hh = 0; hh < nhru; ++hh) {
		Tfreeze[hh] = 0;
		Findex[hh] = 0.0;
		frostdepth[hh] = 0.0;
		Lacc[hh] = 0.0;
		Cacc[hh] = 0.0;
		Kacc[hh] = 0.0;

		for (long nn = 0; nn < nlay; ++nn) {
			L_lay[nn][hh] = theta_lay[nn][hh] * por_lay[nn][hh]; // water m3/m3
			if (soil_type_lay[nn][hh] != 4) {
				k_lay[nn][hh] = (1.0 - por_lay[nn][hh])*km + L_lay[nn][hh] * kw + (por_lay[nn][hh] - L_lay[nn][hh])*ka;
				c_lay[nn][hh] = (1.0 - por_lay[nn][hh])*Cm + L_lay[nn][hh] * Cw + (por_lay[nn][hh] - L_lay[nn][hh])*Ca;
			}
			else {
				k_lay[nn][hh] = (1.0 - por_lay[nn][hh])*ko + L_lay[nn][hh] * kw + (por_lay[nn][hh] - L_lay[nn][hh])*ka;
				c_lay[nn][hh] = (1.0 - por_lay[nn][hh])*Co + L_lay[nn][hh] * Cw + (por_lay[nn][hh] - L_lay[nn][hh])*Ca;
			}
			L_lay[nn][hh] *= 333.0; // MJ/m3
		}
	}
}

void Classfrostdepth::run(void) {

	const float csnow = 0.25*Ci;       // MJ/(m3.�C)
	const float ksnow = 0.25*ki + 0.75*ka; // J/(m.K.s)

	float FrozenD;     // depth frozen of next layer
	long  FrozenL;     // last fully frozen layer
	float dsum;        // soil and snow frozen depth
	float dsoil;       // soil frozen depth

	long nstep = getstep() % Global::Freq;

	if (nstep != 0) return; // not end of day

	long jday = julian("now");
	float hemisphere = (hru_lat[0] < 0.0); // use hru #1
	if ((!hemisphere && (jday < 300) || hemisphere && (jday < 117)) && Tfreeze[0] == 0) return; // use hru #1

	for (hh = 0; chkStruct(); ++hh) {

		if (hru_tmean[hh] > 0.0) {
			if (hru_tmean[hh] > 20.0) {
				frostdepth[hh] = 0.0;
				Tfreeze[0] = 0;
			}
			continue;
		}
		else {
			float Lastsnowdepth = snowdepth[hh];
			//      snowdepth[hh] = SWE[hh]/250.0;
			if (snowdepth[hh] > Lastsnowdepth && Lastsnowdepth > 0.05) {
				Findex[hh] = (Lacc[hh] + Cacc[hh] * Ta[hh] * 1.8) /
					(24.0 * 3600 * 1E-6*Kacc[hh] / sqr(frostdepth[hh] + snowdepth[hh]) - Cacc[hh] / (2.0*Tfreeze[hh]));
			}
			Tfreeze[hh]++;
			Findex[hh] += -hru_tmean[hh]; // /Global::Freq;
		}

		dsum = snowdepth[hh] + 0.001; // avoid divide by zero errors

		Lacc[hh] = 0.0;
		Cacc[hh] = dsum * csnow;
		Kacc[hh] = dsum / ksnow;

		dsoil = 0.0;
		FrozenL = 0;

		while (nlay - 1 > FrozenL) {
			if (frostdepth[hh] < dsoil + d_lay[FrozenL][hh]) break;
			dsoil += d_lay[FrozenL][hh];
			dsum += d_lay[FrozenL][hh];
			Lacc[hh] += L_lay[FrozenL][hh] * d_lay[FrozenL][hh];
			Cacc[hh] += c_lay[FrozenL][hh] * d_lay[FrozenL][hh];
			Kacc[hh] += d_lay[FrozenL][hh] / k_lay[FrozenL][hh];
			FrozenL++;
		}

		FrozenD = frostdepth[hh] - dsoil;

		dsum += FrozenD;
		Lacc[hh] += L_lay[FrozenL][hh] * FrozenD;
		Cacc[hh] += c_lay[FrozenL][hh] * FrozenD;
		Kacc[hh] += FrozenD / k_lay[FrozenL][hh];

		Lacc[hh] = Lacc[hh] / dsum;
		Cacc[hh] = Cacc[hh] / dsum;
		Kacc[hh] = dsum / Kacc[hh];

		frostdepth[hh] = sqrt((24.0 * 3600 * 1e-6*Kacc[hh] * Findex[hh]) /
			(Lacc[hh] + Cacc[hh] * (Ta[hh] * 1.8 + Findex[hh] / (2.0*Tfreeze[hh])))) - snowdepth[hh];

		if (frostdepth[hh] < 0.0) frostdepth[hh] = 0.0;
	}
}

void Classfrostdepth::finish(bool good) {

	if (k_lay != NULL)
		for (int nn = 0; nn < nlay; ++nn) {
			delete[] k_lay[nn];  // Array  [nlay][nhru]
			delete[] L_lay[nn];  // Array  [nlay][nhru]
			delete[] c_lay[nn];  // Array  [nlay][nhru]
		}
	else
		return;

	delete[] k_lay;
	k_lay = NULL;
	delete[] L_lay;
	L_lay = NULL;
	delete[] c_lay;
	c_lay = NULL;
}

Classfrozen* Classfrozen::klone(string name) const {
	return new Classfrozen(name);
}

void Classfrozen::decl(void) {

	Description = "'Frozen soil infiltration Zhao and Gray (1999).'";

	declvar("infil", NHRU, "Potential rain infiltration", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

	declvar("snowinfil", NHRU, "melt infiltration", "(mm/int)", &snowinfil);

	declstatvar("cumsnowinfil", NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	decllocal("t0_Var", NHRU, "t0 value used by module", "(h)", &t0_Var);

	decllocal("t0_Acc", NHRU, "opportunity time", "(h)", &t0_Acc); // to reset every loop

	decllocal("INF", NHRU, "parametric calculation", "(mm)", &INF);

	decllocal("Julian_window", ONE, "currently in Julian window handling frozen infiltration.", "()", &Julian_window);

	decllocal("Julian_lockout", ONE, "lockout next frozen cycle until after this Julian date when t0_Julian is not set (i.e. 0).", "()", &Julian_lockout);

	decllocal("infiltype", NHRU, "infiltration type. PREMELT/RESTRICTED/LIMITED/UNLIMITED/SATURATED - 0/1/2/3/4 respectively", "()", &infiltype);

	decllocal("snowmeltD_last", NHRU, "yesterday's snowmelt. Used to determine the formation of ice lens.", "(mm/d)", &snowmeltD_last);

	decllocal("SWEPk", NHRU, "peak snow water equivalent", "(mm)", &SWEPk);


	declparam("t0", NHRU, "[0.0]", "0.0", "1000.0", "< 0 - calculate opportunity time, == 0 - calculate t0 from '0.65*SWE-5.0',  > 0 - use as opportunity time", "(h)", &t0);

	decldiagparam("S0", NHRU, "[1.0]", "0.0", "1.0", "surface saturation", "(mm^3/mm^3)", &S0);

	declparam("Si", NHRU, "[0.5]", "0.0", "1.0", "initial soil saturation (0 - 0.4m)", "(mm^3/mm^3)", &Si);

	decldiagparam("C", NHRU, "[1.0]", "0.0", "3.0", "coefficient", "()", &C);

	declparam("hru_tsoil", NHRU, "[269.15]", "223.0", "273.15", "soil average temperature at start of infiltration (0 - 0.4m)", "(�K)", &hru_tsoil);

	decldiagparam("t_ice_lens", NHRU, "[-20]", "-50.0", "0.0", "overnight minimum to cause ice lens after major melt", "(�C)", &t_ice_lens);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone",
		"(mm)", &soil_moist_max);

	decldiagparam("t0_Julian", ONE, "[30]", "0", "366", "value > 0 - inhibit frozen algorithm till after this Julian date, 0 - enable frozen algorithm immediately when melt criteria is met.", "()", &t0_Julian);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_rain", "(mm/int)", &net_rain);

	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);


	declreadobs("t0_inhibit", NHRU, "opportunity time inhibit", "()", &t0_inhibit, 0, true);
}

void Classfrozen::init(void) {

	nhru = getdim(NHRU);

	if (t0[0] <= 0.0) { // going to calculate oportunity time
		if (t0_inhibit == NULL) {
			CRHMException TExcept("Frozen: calculating opportunity time using every melt (when applicable) interval!", WARNING);
			LogError(TExcept);
		}
		else {
			CRHMException TExcept("Frozen: calculating opportunity time using selected melt (when applicable) intervals!", WARNING);
			LogError(TExcept);
		}
	}

	for (hh = 0; hh < nhru; ++hh) {
		t0_Acc[hh] = 0.0;
		t0_Var[hh] = 0.0;
		cuminfil[hh] = 0.0;
		infil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;
		runoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		INF[hh] = 0.0;
		SWEPk[hh] = 0.0;

		infiltype[hh] = PREMELT;
	}

	SetOpportunityTime = false;
	Julian_window[0] = 0; // before Julian date
	Julian_lockout[0] = 0;
}

void Classfrozen::run(void) {

	bool SetOpportunity = false;
	bool ClrOpportunity = false;

	long nstep = getstep() % Global::Freq;

	float SWE_sum = 0.0;

	for (hh = 0; chkStruct(); ++hh)
		SWE_sum += SWE[hh]; // used to reset opportunity time

	for (hh = 0; chkStruct(); ++hh) {

		if (nstep == 0) { // end of day
			snowmeltD_last[hh] = snowmeltD[hh];
			if (SWE[hh] > SWEPk[hh])
				SWEPk[hh] = SWE[hh];
		}
		else if (nstep == 1 &&                  // beginning of day
			hru_tmin[hh] <= t_ice_lens[hh] &&
			infiltype[hh] == LIMITED &&
			snowmeltD_last[hh] > 5.0) {

			infiltype[hh] = RESTRICTED;

			LogMessage(hh, " ice lens formed at temperature of ", hru_tmin[hh], DT);
			LogDebug(" ");

			CRHMException TExcept("Ice lens formed in HRU " + std::to_string(hh + 1) + ", at minimum temperature of " + Convert(hru_tmin[hh]).c_str(), WARNING);
			LogError(TExcept);
		}

		infil[hh] = 0.0;

		if (net_rain[hh] > 0.0) {
			infil[hh] = net_rain[hh];
			cuminfil[hh] += net_rain[hh];
		}

		snowinfil[hh] = 0.0;
		meltrunoff[hh] = 0.0;

		if (Julian_lockout[0] == julian("now"))
			Julian_lockout[0] = 0;

		float snowmelt = snowmeltD[hh] / Global::Freq;

		if (nstep == 1 && hh == 0) {
			if (t0_Julian[0] == julian("now") || t0_Julian[0] == 0 && SWE_sum / nhru > 10 && snowmeltD[hh] > 2.0 && !Julian_lockout[0]) {
				Update_infil = true;
				if (t0[0] <= 0) {
					Julian_window[0] = 1;
					for (long hhh = 0; chkStruct(hhh); ++hhh) // reset
						t0_Acc[hhh] = t0[hhh];
				}
				else
					for (long hhh = 0; chkStruct(hhh); ++hhh) // save t0 values
						t0_Var[hhh] = t0[hhh];

				Julian_lockout[0] = (julian("now") + 183) % 365; // close after 6 months
			}
		}

		INF[hh] = 0.0;
		if (snowmelt > 0.0) { // snowmeltD[hh]/Global::Freq

			if (hh == (nhru - 1) && (SWE_sum / nhru <= 2.0 || last_timestep())) { // end of melt
				if (SetOpportunityTime) { // was calculating opportunity time
					--Global::CRHMControlSaveCnt; // restore state to backtrack. NO output this cycle
					ClrOpportunity = true;

					for (long hhh = 0; chkStruct(hhh); ++hhh) // save opportunity time values
						t0_Var[hhh] = t0_Acc[hhh];

					SetOpportunityTime = false;
				 string s = Name + " End save ";
					LogMessage(s.c_str(), DD);
					Julian_window[0] = 0;
				}
			}

			if (!SetOpportunityTime) { // normal operation
				float capacity;
				switch (infiltype[hh]) {
				case LIMITED:

					capacity = soil_moist_max[hh] - soil_moist[hh];
					if (capacity > 0.0 && (t0_Var[hh] || !t0[hh])) { // also handles divide by zero
						if (!t0[hh]) {
							t0_Var[hh] = 0.65*SWEPk[hh] - 5.0;
							if (t0_Var[hh] < 24.0)
								t0_Var[hh] = 24.0;
						}
						INF[hh] = C[hh] * pow(S0[hh], 2.92f)*pow(1.0f - Si[hh], 1.64f)*
							pow((273.15f - hru_tsoil[hh]) / 273.15f, -0.45f)*pow(t0_Var[hh], 0.44f); // (mm)

						float INF0 = INF[hh] / t0_Var[hh];

						if (snowmelt <= INF0 && snowmelt <= capacity) {
							snowinfil[hh] = snowmelt;
							meltrunoff[hh] = 0.0;
						}
						else if (snowmelt > INF0) {
							snowinfil[hh] = INF0;
							meltrunoff[hh] = snowmelt - INF0;
						}
						else {
							snowinfil[hh] = capacity;
							meltrunoff[hh] = snowmelt - capacity;
						}

						cumsnowinfil[hh] += snowinfil[hh];
						cummeltrunoff[hh] += meltrunoff[hh];

						if (cumsnowinfil[hh] > INF[hh]) {
							cummeltrunoff[hh] += (cumsnowinfil[hh] - INF[hh]);
							cumsnowinfil[hh] = INF[hh];
							infiltype[hh] = RESTRICTED;
						}
					}
					else {
						meltrunoff[hh] = snowmelt;
						cummeltrunoff[hh] += meltrunoff[hh];
					}

					break;

				case UNLIMITED:
					snowinfil[hh] = snowmelt;
					cumsnowinfil[hh] += snowinfil[hh];
					break;
				case RESTRICTED:
					meltrunoff[hh] = snowmelt;
					cummeltrunoff[hh] += meltrunoff[hh];
					break;
				default:
					if (Si[hh] < 1.0) {
						snowinfil[hh] = snowmelt;
						cumsnowinfil[hh] += snowinfil[hh];
					}
					else {
						meltrunoff[hh] = snowmelt;
						cummeltrunoff[hh] += meltrunoff[hh];
					}
					break;
				} // switch
			} // normal operation

			if (snowmeltD[hh] > 2.0) {
				if (Julian_window[0] == 1 && !SetOpportunityTime) { // run ahead?
					SetOpportunity = true;
					++Global::CRHMControlSaveCnt; // save state for backtrack. Inhibit output, including this interval
				 string s = Name + " Start save ";
					LogMessage(s.c_str(), DD);
				}

				if (Update_infil) {
					for (long hhh = 0; chkStruct(hhh); ++hhh) { // set infiltration

						SWEPk[hhh] = SWE[hhh];

						if (Si[hhh] >= 1.0)
							infiltype[hhh] = RESTRICTED;
						else if (Si[hhh] <= 0.0)
							infiltype[hhh] = UNLIMITED;
						else
							infiltype[hhh] = LIMITED;
					}

					Update_infil = false;
				}
			} // snowmeltD[hh] > 2.0

			if (SetOpportunityTime) { // accummulate opportunity time
				if (t0_inhibit == NULL)
					t0_Acc[hh] += 24.0 / Global::Freq;
				else if (t0_inhibit[hh] > 0)
					t0_Acc[hh] += 24.0 / Global::Freq;
			}
		} // if(snowmelt > 0.0)
	} // for

	if (SetOpportunity)
		SetOpportunityTime = true;
	if (ClrOpportunity)
		SetOpportunityTime = false;
}

void Classfrozen::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (frozen)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozen)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozen)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozen)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassNetroute* ClassNetroute::klone(string name) const {
	return new ClassNetroute(name);
}

float ClassNetroute::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassNetroute::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to gw of this HRU via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

	declparam("preferential_flow", NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer soil_gw(gw_flow) runoff", "(mm/d)", &soil_gw_Buf);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Kstorage", NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", &Kstorage);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", &Lag);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("whereto", NHRU, "[0]", "0", "1000", "send to; 0 - basin outflow, or HRU input", "()", &whereto);

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "Netroute:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "Netroute:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	basinflow[0] = 0.0;
	basinflow_s[0] = 0.0;
	cumbasinflow[0] = 0.0;
	basingw[0] = 0.0;
	basingw_s[0] = 0.0;
	cumbasingw[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		outflow_diverted[hh] = 0.0;
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		cum_to_Sd[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_preferential_flow_to_gw[hh] = 0.0;


		gwinflow[hh] = 0.0;
		gwcuminflow[hh] = 0.0;
		gwcumoutflow[hh] = 0.0;
		gwcumoutflow_diverted[hh] = 0.0;
		HRU_cumbasinflow[hh] = 0.0;

		ssrinflow[hh] = 0.0;
		ssrcuminflow[hh] = 0.0;
		ssroutflow[hh] = 0.0;
		ssrcumoutflow[hh] = 0.0;

		runinflow[hh] = 0.0;
		runcuminflow[hh] = 0.0;
		runoutflow[hh] = 0.0;
		runcumoutflow[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (Netroute)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassNetroute::run(void) {

	long step = getstep();
	long nstep = step % Global::Freq;

	basinflow[0] = 0.0;
	basingw[0] = 0.0;

	for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

		for (hh = 0; chkStruct(hh); ++hh)
			if (order[hh] - 1 == jj)
				break;

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];

		gwoutflow_diverted[hh] = 0.0;

		float gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0
				gwoutflow_diverted[hhh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hhh]; // units (mm*km^2/int)
				gwoutflow[hhh] = 0.0;
				gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // units (mm*km^2/int)
								soil_rechr[hh] += gw_amount / hru_area[hh];
								soil_moist[hh] += gw_amount / hru_area[hh];
								cum_to_soil_rechr[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								soil_moist[hh] += free;
								soil_rechr[hh] = soil_rechr_max[hh];
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // units (mm*km^2/int)
								Sd[hh] += gw_amount / hru_area[hh];
								cum_to_Sd[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_Sd[hh] += free;
								Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						gw[hh] += gw_amount / hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU
				else { // > nhru then put in basinflow
					basinflow[0] += gw_amount * 1000; // (m3)
					HRU_cumbasinflow[hh] = gw_amount;
					cumoutflow[hh] += gw_amount;
					gw_amount = 0.0;
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];

		ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		runcumoutflow[hh] += runoutflow[hh];

		inflow[hh] = (runoutflow[hh] + ssroutflow[hh] + gw_amount); // add this HRU runoff and subsurface flow

		cuminflow[hh] += inflow[hh];

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {
				if (preferential_flow[hhh]) {
					gw[hh] += outflow[hhh] / hru_area[hh];
					cum_preferential_flow_to_gw[hh] += outflow[hhh] / hru_area[hh];
					outflow[hhh] = 0.0;
				}
				else {
					outflow_diverted[hhh] = outflow[hhh];
					cumoutflow_diverted[hhh] += outflow_diverted[hhh];
					float free = soil_rechr_max[hh] - soil_rechr[hh];
					if (free > 0.0 && !soil_rechr_ByPass[hh]) {
						if (free > outflow[hhh] / hru_area[hh]) { // units (mm*km^2/int)
							soil_rechr[hh] += outflow[hhh] / hru_area[hh];
							soil_moist[hh] += outflow[hhh] / hru_area[hh];
							cum_to_soil_rechr[hh] += outflow[hhh] / hru_area[hh];
							outflow[hhh] = 0.0;
						}
						else {
							outflow[hhh] = (outflow[hhh] / hru_area[hh] - free)*hru_area[hh];
							cum_to_soil_rechr[hh] += free;
							soil_moist[hh] += free;
							soil_rechr[hh] = soil_rechr_max[hh];
						}
					}

					free = Sdmax[hh] - Sd[hh];
					if (free > 0.0 && !Sd_ByPass[hh] && outflow[hhh] > 0.0) {
						if (free > outflow[hhh] / hru_area[hh]) { // units (mm*km^2/int)
							Sd[hh] += outflow[hhh] / hru_area[hh];
							cum_to_Sd[hh] += outflow[hhh] / hru_area[hh];
							outflow[hhh] = 0.0;
						}
						else {
							outflow[hhh] = (outflow[hhh] / hru_area[hh] - free)*hru_area[hh];
							cum_to_Sd[hh] += free;
							Sd[hh] = Sdmax[hh];
						} // if
					} // if
				} // else

				if (outflow[hhh] > 0.0) // handle excess
					redirected_residual[hh] += outflow[hhh]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

				outflow[hhh] = 0.0;
			} // if
		} // for hhh

		hruDelay->DoClark(hh); // need to update for later HRUs

		if (whereto[hh] == 0) { // move to basinflow
			basinflow[0] += outflow[hh] * 1000; // (m3)
			HRU_cumbasinflow[hh] += outflow[hh];
			cumoutflow[hh] += outflow[hh];
		}
		if (gwwhereto[hh] == 0) { // move to basin gw
			basingw[0] += gwoutflow[hh] * 1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		} // end if

	} // for hh

	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasingw[0] += basingw[0];
}

void ClassNetroute::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Netroute)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute)' gwDelay_in_storage     (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh];
	}

	LogMessage(string("'" + Name + " (Netroute)' cumbasinflow (m^3): ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute)' cumbasingw   (m^3): ").c_str(), cumbasingw[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute)' Allgwcuminflow (mm*basin): ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute)' Allcuminflow (mm*basin): ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute)' Allcumoutflow (mm*basin): ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute)' Allssrcuminflow (mm*basin): ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute)' Allruncuminflow (mm*basin): ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute)' AllSdcuminflow (mm*basin): ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}


Classinterception* Classinterception::klone(string name) const {
	return new Classinterception(name);
}

void Classinterception::decl(void) {

	Description = "'Calculates canopy sublimation and unloading.'";

	declvar("SI_Lo", NHRU, "Canopy load", "(kg/m^2)", &SI_Lo);

	declvar("net_snow", NHRU, "Canopy unload ", "(kg/m^2)", &net_snow);

	decldiag("Cum_net_snow", NHRU, "Cumulative Canopy unload ", "(kg/m^2)", &Cum_net_snow);

	declvar("SI_Subl", NHRU, "Canopy sublimation", "(kg/m^2*int)", &SI_Subl);

	decldiag("Cum_Subl", NHRU, "Cumulative Canopy sublimation", "(kg/m^2)", &Cum_Subl);


	declvar("net_rain", NHRU, "hru_rain minus interception", "(mm/int)", &net_rain);

	decldiag("v", NHRU, "ventilation velocity", "(m/s)", &v);


	declparam("Sbar", NHRU, "[6.6]", "0.0", "100.0", "Maximum snow load", "(kg/m^2)", &Sbar);

	declparam("LAI", NHRU, "[2.2]", "0.0", "10.0", "Leaf are index", "(m^2/m^2)", &LAI);

	decldiagparam("k", NHRU, "[0.0113]", "0.0", "1.0", "Snow shape coefficient", "()", &k);

	declparam("Ht", NHRU, "[20]", "0.0", "100.0", "Canopy height", "(m)", &Ht);

	decldiagparam("WidthJ", NHRU, "[75]", "0.0", "100.0", "Canopy ", "(m)", &WidthJ);

	decldiagparam("velW", NHRU, "[0.75]", "0.0", "1.0", "Canopy wind coefficient", "(m)", &velw);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);


	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);
	declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);
	declgetvar("*", "hru_rh", "()", &hru_rh);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
}

void Classinterception::init(void) {

	nobs = getdim(NOBS);
	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		SI_Lo[hh] = 0.0;
		net_snow[hh] = 0.0;
		net_rain[hh] = 0.0;
		SI_Subl[hh] = 0.0;
		Cum_Subl[hh] = 0.0;
		Cum_net_snow[hh] = 0.0;
	}
}

void Classinterception::run(void) {

	const float Radius = 0.0005;     /* Ice sphere radius, metres */
	const float R = 8313.0;          /* Universal gas constant, J/(mole*K) */
	const float M = 18.01;           /* Molecular weight of water */
	const float RhoI = 900.0;        /* Density of ice, kg/m^3 */
									 //const float k1 = 0.0114;         /* Snow shape coefficient, Jackpine site */
	const float Fract = 0.4;         /* Fractal dimension */
									 //const float SnowAlb = 0.8;       /* Albedo for snow */
									 //const float CanAlb = 0.2;        /* Albedo for canopy */
	const float Hs = 2838000.0;      // Latent heat of sublimation, J/kg

	const float Cc = 0.82;
	const float Viscosity = 1.88E-5;
	const float Albedo = 0.8; // particle albedo

	float RhoSat, RhoT, Nr, Nu, Sstar, A, B, J, D, Vs, Ce;
	float I1, Unld, Istar, Cp, RhoS;

	for (hh = 0; chkStruct(); ++hh) {

		net_rain[hh] = hru_rain[hh];

		RhoS = 67.92 + 51.25*exp(hru_t[hh] / 2.59);
		Istar = Sbar[hh] * (0.27 + 46.0 / RhoS)*LAI[hh];

		net_snow[hh] = 0.0;

		if (SI_Lo[hh] > Istar) { // after increase in temperature
			net_snow[hh] = SI_Lo[hh] - Istar;
			Cum_net_snow[hh] += net_snow[hh];
			SI_Lo[hh] = Istar;
		}

		if (hru_snow[hh] > 0.0) { // add new snow
			Cp = Cc / (1.0 - (Cc*hru_u[hh] * Ht[hh]) / (velw[hh] * WidthJ[hh]));
			if (Cp <= 0.0 || Cp > 1.0) Cp = 1.0;

			I1 = (Istar - SI_Lo[hh])*(1 - exp(-Cp * hru_snow[hh] / Istar));

			SI_Lo[hh] = SI_Lo[hh] + I1; // add new snowfall

			net_snow[hh] += hru_snow[hh] - I1;
			Cum_net_snow[hh] += hru_snow[hh] - I1;
		}
		else if (SI_Lo[hh] <= 0.0) {
			SI_Lo[hh] = 0.0;
			continue; // exit if no snow in canopy
		}

		// calculate sublimation
		RhoSat = 1.324*exp(22.452*hru_t[hh] / (hru_t[hh] + 273.0)) / (hru_t[hh] + 273.0);  // saturation water vapour density
		RhoT = 0.00063*(hru_t[hh] + 273.0) + 0.0673; // thermal conductivity of atmosphere


		float n = 2.43*Cc + 2.97*(1.0 - Cc);
		float mx = 3.46*Cc + 3.2*(1.0 - Cc);
		float Is_CioncoA = n + mx * exp(-Ht[hh]);
		float For_vent = velw[hh] * Ht[hh];
		float Is_CioncoB = For_vent / Ht[hh] - 1.0;
		float Is_CioncoAB = Is_CioncoA * Is_CioncoB;
		v[hh] = hru_u[hh] * exp(Is_CioncoAB); // estimated windspeed z

		Nr = 2 * Radius*v[hh] / Viscosity;
		Nu = 1.79 + 0.606*sqrt(Nr);
		Sstar = M_PI * sqr(Radius)*(1.0 - Albedo)*Qsi[hh]; //Solar incident radiation
		A = RhoT * (hru_t[hh] + 273)*Nu;
		B = Hs * M / (R*(hru_t[hh] + 273.0)) - 1.0;
		J = B / A;
		D = 2.06E-5f*pow((hru_t[hh] + 273.0f) / 273.0f, 1.75f);   // diffusivity of water vapour
		Vs = (2.0*M_PI*Radius*(1.0 - hru_rh[hh]) + Sstar * J) /
			(Hs*J + (1.0f / (D*RhoSat*Nu)));  // NB reversed (Rh - 1.0)
		Vs = Vs / (4.0f / 3.0f*M_PI*pow(Radius, 3.0f)*RhoI);
		Ce = k[hh] * pow(SI_Lo[hh] / Istar, -Fract);

		SI_Subl[hh] = -SI_Lo[hh] * Vs*Ce*3600.0f*24.0f / Global::Freq / 1000.0f; // sublimation is positive!  Units???
		Cum_Subl[hh] += SI_Subl[hh];

		// take sublimation from canopy snow
		if (SI_Lo[hh] > SI_Subl[hh])
			SI_Lo[hh] = SI_Lo[hh] - SI_Subl[hh];
		else {
			SI_Subl[hh] = SI_Lo[hh];
			SI_Lo[hh] = 0.0;
			continue;
		}

		if (hru_snow[hh] > 0.0) {  // Unload canopy snow
			if (I1 > SI_Subl[hh]) {
				Unld = (I1 - SI_Subl[hh])*0.322;
				SI_Lo[hh] = SI_Lo[hh] - Unld;
				net_snow[hh] += Unld;
				Cum_net_snow[hh] += Unld;
			}
		}
	}
}

void Classinterception::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (interception)' Cumulative Canopy Unload      (mm) (mm*hru) (mm*hru/basin): ").c_str(), Cum_net_snow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (interception)' Cumulative Canopy sublimation (mm) (mm*hru) (mm*hru/basin): ").c_str(), Cum_Subl[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassGreenAmpt* ClassGreenAmpt::klone(string name) const {
	return new ClassGreenAmpt(name);
}

void ClassGreenAmpt::decl(void) {

	Description = "'Summer Green Ampt model.'";

	declvar("infil", NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	declvar("snowinfil", NHRU, "infiltration", "(mm/int)", &snowinfil);

	declstatdiag("cumsnowinfil", NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

	declstatvar("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm/int)", &cummeltrunoff);


	decllocal("k", NHRU, "(mm/h)", "()", &k);

	declstatdiag("F0", NHRU, "last HRU cumulative infiltration", "(mm)", &F0);

	decllocal("f0", NHRU, "", "(mm/h)", &f0);

	declstatdiag("F1", NHRU, "HRU cumulative infiltration", "(mm)", &F1);

	decllocal("f1", NHRU, "", "(mm/h)", &f1);

	decllocal("dthbot", NHRU, "", "()", &dthbot);

	decllocal("psidthbot", NHRU, "", "(mm)", &psidthbot);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("soil_type", NHRU, "[4]", "0", "12",
		"water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
		" 0 - 12", "()", &soil_type);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "2500.0",
		"Initial value of available water in soil profile", "(mm)", &soil_moist_init);


	declgetvar("*", "net_rain", "(mm/int)", &net_rain);

	declgetvar("*", "snowmeltD", "(mm/d)", &snowmelt);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);


}

void ClassGreenAmpt::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		cuminfil[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;

		F1[hh] = soil_moist_max[hh];
		k[hh] = soilproperties[soil_type[hh]][KSAT];
		dthbot[hh] = (1.0 - soil_moist_init[hh] / soil_moist_max[hh]);
		psidthbot[hh] = soilproperties[soil_type[hh]][PSI] * dthbot[hh];
		f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0;
	}
}

void ClassGreenAmpt::run(void) {

	// greenampt routine

	for (hh = 0; chkStruct(); ++hh) {

		infil[hh] = 0.0;
		runoff[hh] = 0.0;
		snowinfil[hh] = 0.0;
		meltrunoff[hh] = 0.0;

		float melt = snowmelt[hh] / Global::Freq;
		float All = net_rain[hh] + melt;

		if (All > 0.0) {

			garain = All; // precipitation/interval
			intensity = All * Global::Freq / 24.0; // convert to mm/h

			if (garain > 0.0) {
				if (soil_type[hh] == 12) { // handle pavement separately
					runoff[hh] = garain;
				}
				else if (soil_type[hh] == 0 || soil_moist[hh] <= 0.0) { // handle water separately
					infil[hh] = garain;
					//          cuminfil[hh] += infil[hh];
				}
				else {
					F1[hh] = soil_moist[hh];
					dthbot[hh] = (1.0 - soil_moist[hh] / soil_moist_max[hh]);
					psidthbot[hh] = soilproperties[soil_type[hh]][PSI] * dthbot[hh];
					if (soil_type[hh] > 0) // not water!
						f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0; // infiltrate first interval rainfall

					infiltrate();

					infil[hh] = F1[hh] - F0[hh];
					//          cuminfil[hh] += infil[hh];

					if (pond > 0.0) {

						runoff[hh] = pond;
					}
				}
			}

			if (melt >= infil[hh]) {
				snowinfil[hh] = melt;
				infil[hh] = 0.0;
			}
			else if (melt > 0.0) {
				snowinfil[hh] = melt;
				infil[hh] -= snowinfil[hh];
			}
			else
				snowinfil[hh] = 0.0;

			if (melt - snowinfil[hh] >= pond) {
				meltrunoff[hh] = melt - snowinfil[hh];
				runoff[hh] = 0.0;
			}
			else if (melt - snowinfil[hh] > 0.0) {
				meltrunoff[hh] = melt - snowinfil[hh];
				runoff[hh] = pond - meltrunoff[hh];
			}
			else {
				meltrunoff[hh] = 0.0;
				runoff[hh] = pond;
			}

			cuminfil[hh] += infil[hh];
			cumrunoff[hh] += runoff[hh];

			cumsnowinfil[hh] += snowinfil[hh];
			cummeltrunoff[hh] += meltrunoff[hh];

		} // if(net_rain[hh] + net_snow[hh] > 0.0) greenampt routine
	} // for
}

void ClassGreenAmpt::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cuminfil(rain)      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cumrunoff(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cumsnowinfil(snow)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (GreenAmpt)' cummeltrunoff(snow) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

void ClassGreenAmpt::infiltrate(void) {

	F0[hh] = F1[hh];
	f0[hh] = f1[hh];

	if (soil_type[hh] == 0) { // water!
		pond += garain;
		return;
	}
	pond = 0.0;

	f0[hh] = calcf1(F0[hh], psidthbot[hh])*Global::Interval*24.0;

	if (intensity > f0[hh]) {
		ponding();
		return;
	}

	F1[hh] = F0[hh] + garain;

	f1[hh] = calcf1(F1[hh], psidthbot[hh])*Global::Interval*24.0;

	if (intensity > f1[hh])
		startponding();
}

void ClassGreenAmpt::ponding(void) {

	F1[hh] = F0[hh] + garain;

	howmuch(F0[hh], Global::Interval*24.0);

	pond += garain - (F1[hh] - F0[hh]);

	howmuch(F0[hh], Global::Interval*24.0);

}

void ClassGreenAmpt::startponding(void) {

	float Fp = k[hh] * psidthbot[hh] / (intensity - k[hh]);
	float dt = (Fp - F0[hh]) / intensity;

	howmuch(Fp, Global::Interval*24.0 - dt);

	pond += garain - (F1[hh] - F0[hh]);

}

void ClassGreenAmpt::howmuch(float F0, float dt) {

	float LastF1;

	do {
		LastF1 = F1[hh];
		F1[hh] = F0 + k[hh] * dt + psidthbot[hh] * log((F1[hh] + psidthbot[hh]) / (F0 + psidthbot[hh]));
	} while (fabs(LastF1 - F1[hh]) > 0.001);
}

float ClassGreenAmpt::calcf1(float F, float psidth) {

	return k[hh] * (psidth / F + 1.0);
}

Classalbedoparam* Classalbedoparam::klone(string name) const {
	return new Classalbedoparam(name);
}

void Classalbedoparam::decl(void) {

	Description = "'Initialises the variable \"Albedo\" from the parameter \"Albedo_Value\".'";

	declvar("Albedo", NHRU, "Albedo", "()", &Albedo);

	declparam("Albedo_Value", NHRU, "[0.17]", "0.0", "1.0", "Albedo", "()", &Albedo_Value);

}

void Classalbedoparam::init(void) {
	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		Albedo[hh] = Albedo_Value[hh];
	}
}

void Classalbedoparam::run(void) {
}

Classalbedoobs* Classalbedoobs::klone(string name) const {
	return new Classalbedoobs(name);
}

void Classalbedoobs::decl(void) {

	Description = "'Every interval sets the variable \"Albedo\" to the value of the observation \"Albedo_obs\".'";

	declvar("Albedo", NHRU, "Albedo", "()", &Albedo);

	decldiagparam("Albedo_Value", NHRU, "[0.17]", "0.0", "1.0", "Albedo", "()", &Albedo_Value);

	declreadobs("Albedo_obs", NHRU, "albedo observation", "()", &Albedo_obs, HRU_OBS_Q, true);

}

void Classalbedoobs::init(void) {
	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		Albedo[hh] = Albedo_Value[hh];
	}

	if (Albedo_obs == NULL) {
		CRHMException TExcept("\"albedo_obs\". No observation albedo data!  Using constant parameter value instead.", WARNING);
		LogError(TExcept);
	}
}

void Classalbedoobs::run(void) {
	if (Albedo_obs != NULL)
		for (hh = 0; chkStruct(); ++hh)
			Albedo[hh] = Albedo_obs[hh];
}

ClassHtobs* ClassHtobs::klone(string name) const {
	return new ClassHtobs(name);
}

void ClassHtobs::decl(void) {

	Description = "'Every interval sets the variable \"Ht_var\" to the value of the observation \"Ht_obs\".'";

	declvar("Ht_var", NHRU, "vegetation height", "(m)", &Ht_var);

	declputparam("*", "Ht", "(m)", &Ht);


	declreadobs("Ht_obs", NHRU, "height observation", "(m)", &Ht_obs, HRU_OBS_misc, true);

}

void ClassHtobs::init(void) {
	nhru = getdim(NHRU);

	if (Ht_obs == NULL) {
		CRHMException TExcept("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {
		Ht_var[hh] = Ht[hh];
	}
}

void ClassHtobs::run(void) {
	if (Ht_obs != NULL)
		for (hh = 0; chkStruct(); ++hh) {
			float H = Ht_obs[hh];
			if (H < 0.001)
				H = 0.001;
			//      const_cast<float *> (Ht) [hh] = H;
			Ht[hh] = H;
			Ht_var[hh] = Ht[hh];
		}
}

ClassSnobalX* ClassSnobalX::klone(string name) const {
	return new ClassSnobalX(name);
}

void ClassSnobalX::decl(void) {

	Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Non standard module.'";

	declstatvar("layer_count", NHRU, "number of layers in snowcover: 0, 1, or 2", "()", &layer_count);
	declstatvar("isothermal", NHRU, "melting: 0/1", "()", &isothermal);
	declstatvar("snowcover", NHRU, "snow on gnd at start of current timestep: 0/1", "()", &snowcover);

	declvar("R_n", NHRU, "net allwave radiation", "(W/m^2)", &R_n);
	declvar("H", NHRU, "sensible heat xfr", "(W/m^2)", &H);
	declvar("L_v_E", NHRU, "latent heat xfr", "(W/m^2)", &L_v_E);
	declvar("G", NHRU, "heat xfr by conduction & diffusion from soil to snowcover", "(W/m^2)", &G);
	declvar("M", NHRU, "advected heat from precip", "(W/m^2)", &M);
	declvar("delta_Q", NHRU, "change in snowcover's energy", "(W/m^2)", &delta_Q);
	declvar("G_0", NHRU, "heat xfr by conduction & diffusion from soil or lower layer to active layer", "(W/m^2)", &G_0);
	declvar("delta_Q_0", NHRU, "change in active layer's energy", "(W/m^2)", &delta_Q_0);

	declstatvar("cc_s_0", NHRU, "active layer cold content", "(J/m^2)", &cc_s_0);
	declstatvar("cc_s_l", NHRU, "lower layer cold content", "(J/m^2)", &cc_s_l);
	declstatvar("cc_s", NHRU, "snowcover's cold content", "(J/m^2)", &cc_s);
	declstatvar("h2o", NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o);

	decllocal("E_s", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2)", &E_s);
	decllocal("E", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &E);
	decllocal("E_s_0", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0);
	decllocal("E_s_l", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l);
	decllocal("melt", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &melt);
	declvar("ro_predict", NHRU, "predicted specific runoff", "(m/s)", &ro_predict);
	declvar("h2o_total", NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total);

	decldiag("E_s_int", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &E_s_int);
	decldiag("E_int", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &E_int);
	decldiag("E_s_0_int", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0_int);
	decldiag("E_s_l_int", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l_int);
	declvar("melt_direct_int", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &melt_direct_int);
	declstatvar("sum", NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
	declvar("snowmelt_int", NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
	declvar("snowmeltD", NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
	declvar("cumsnowmelt", NHRU, "cumulative melt", "(mm)", &cumsnowmelt);

	declstatvar("z_s_0", NHRU, "active layer depth", "(m)", &z_s_0);
	declstatvar("z_s_l", NHRU, "lower layer depth", "(m)", &z_s_l);
	declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

	declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

	declstatvar("m_s_0", NHRU, "active layer specific mass", "(kg/m^2)", &m_s_0);
	declstatvar("m_s_l", NHRU, "lower layer specific mass", "(kg/m^2)", &m_s_l);
	declstatvar("SWE", NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s);

	declstatvar("T_s_0", NHRU, "active snow layer temp", "(�C)", &T_s_0);
	declstatvar("T_s_l", NHRU, "lower layer temp", "(�C)", &T_s_l);
	declstatvar("T_s", NHRU, "average snowcover temp", "(�C)", &T_s);

	declvar("h2o_sat", NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
	declvar("h2o_vol", NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol);
	declvar("h2o_max", NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max);

	declvar("z_snow", NHRU, "depth of snow in precip", "(m)", &z_snow);
	declvar("h2o_sat_snow", NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_snow);

	declvar("precip_now", NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now);
	declvar("T_rain", NHRU, "rain's temp", "(�C)", &T_rain);
	declvar("T_snow", NHRU, "snowfall's temp", "(�C)", &T_snow);

	decllocal("S_n_L", NHRU, "net solar radiation", "(W/m^2)", &S_n);
	decllocal("I_lw_L", NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
	decllocal("T_a_L", NHRU, "air temp", "(�C)", &T_a);
	decllocal("e_a_L", NHRU, "vapor pressure", "(Pa)", &e_a);
	decllocal("u_L", NHRU, "wind speed", "(m/s)", &u);
	decllocal("T_g_L", NHRU, "soil temp at depth z_g", "(�C)", &T_g); // should be K but causes unit fault

	decllocal("m_precip_L", NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
	decllocal("m_rain_L", NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
	decllocal("m_snow_L", NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
	decllocal("m_drift_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_drift);
	decllocal("m_subl_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
	decllocal("rho_snow_L", NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
	decllocal("T_pp_L", NHRU, "precip temp", "(�C)", &T_pp);

	decllocal("P_a", NHRU, "air pressure", "(Pa)", &P_a);

	decllocal("m_precip_cum", NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
	decllocal("m_rain_cum", NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
	decllocal("m_snow_cum", NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
	decllocal("m_drift_cum", NHRU, "cumulative specific mass of total drifting snow", "(kg/m^2)", &m_drift_cum);
	decllocal("m_subl_cum", NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
	decllocal("E_s_cum", NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
	decllocal("melt_direct_cum", NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

	decllocal("stop_no_snow", NHRU, "snow flag", "()", &stop_no_snow);

	decldiagparam("relative_hts", NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

	declparam("z_g", NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
	declparam("z_u", NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
	declparam("z_T", NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
	declparam("z_0", NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

	declparam("max_z_s_0", NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
	declparam("max_h2o_vol", NHRU, "[0.0001]", "0.0", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("KT_sand", NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

	declgetvar("*", "hru_S_n", "(W/m^2)", &S_n_X);
	declgetvar("*", "hru_I_lw", "(W/m^2)", &I_lw_X);
	declgetvar("*", "hru_t", "(�C)", &T_a_X);
	declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
	declgetvar("*", "hru_u", "(m/s)", &u_X);
	declgetvar("*", "hru_T_g", "(�C)", &T_g_X);

	declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
	declgetvar("*", "net_rain", "(kg/m^2)", &m_rain_X);
	declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
	declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
	declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
	declgetvar("*", "hru_rho_snow", "(kg/m^3)", &rho_snow_X);
	declgetvar("*", "hru_T_pp", "(�C)", &T_pp_X);
}

void ClassSnobalBase::init(void) {

	input_rec1 = new INPUT_REC[nhru]; // input data for start of data timestep [nhru]
	input_rec2 = new INPUT_REC[nhru]; // input data for start of data timestep [nhru]
	time_step = new long[nhru];	     // length current timestep (sec)
	current_time = new long[nhru];    // start time of current time step (sec)

	computed = new int*[nhru];		// array of flags for each timestep;
	input_deltas = new INPUT_REC*[nhru]; // deltas for climate-input parameters for each timestep
	precip_info = new PRECIP_REC*[nhru]; // array of precip info adjusted for each timestep
	tstep_info = new TSTEP_REC*[nhru]; 	// array of info for each timestep:

	for (long ii = 0; ii < nhru; ++ii) {
		computed[ii] = new int[4];           // [nhru] [4]
		input_deltas[ii] = new INPUT_REC[4]; // [nhru] [4]
		precip_info[ii] = new PRECIP_REC[4]; // [nhru] [4]
		tstep_info[ii] = new TSTEP_REC[4];   // [nhru] [4]
	}

	for (hh = 0; chkStruct(); ++hh) {
		P_a[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f)*1000.0f;  // Pa

		T_s[hh] = -75.0; // temperatures inside Snobal model are �K
		T_s_0[hh] = -75.0;
		T_s_l[hh] = -75.0;

		rho[hh] = 218.0; // change 10/18/16
		h2o_sat[hh] = 0.0;

		z_s[hh] = 0.0;
		z_s_0[hh] = 0.0;
		z_s_l[hh] = 0.0;

		m_s[hh] = 0.0;
		m_s_0[hh] = 0.0;
		m_s_l[hh] = 0.0;

		cc_s[hh] = 0.0;
		cc_s_0[hh] = 0.0;
		cc_s_l[hh] = 0.0;

		h2o[hh] = 0.0;
		h2o_max[hh] = 0.0;
		h2o_total[hh] = 0.0;
		melt[hh] = 0.0;
		z_snow[hh] = 0.0;
		ro_predict[hh] = 0.0;
		T_snow[hh] = 0.0;
		T_rain[hh] = 0.0;

		layer_count[hh] = 0;
		isothermal[hh] = 0;
		snowcover[hh] = 0;
		stop_no_snow[hh] = 0;
		current_time[hh] = 0;

		melt_direct_cum[hh] = 0.0;
		E_s_cum[hh] = 0.0;

		m_precip_cum[hh] = 0.0;
		m_rain_cum[hh] = 0.0;
		m_snow_cum[hh] = 0.0;
		m_drift_cum[hh] = 0.0;
		m_subl_cum[hh] = 0.0;
		cumsnowmelt[hh] = 0.0;

		L_v_E[hh] = 0.0;
		E[hh] = 0.0;
		H[hh] = 0.0;
		G[hh] = 0.0;
		M[hh] = 0.0;
		R_n[hh] = 0.0;
		delta_Q[hh] = 0.0;
		delta_Q_0[hh] = 0.0;

		tstep_info[hh][DATA_TSTEP].level = DATA_TSTEP;
		tstep_info[hh][DATA_TSTEP].time_step = 24 * 3600 / Global::Freq;
		tstep_info[hh][DATA_TSTEP].intervals = 0;
		tstep_info[hh][DATA_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD;

		tstep_info[hh][NORMAL_TSTEP].level = NORMAL_TSTEP;
		tstep_info[hh][NORMAL_TSTEP].time_step = 24 * 3600 / Global::Freq;
		tstep_info[hh][NORMAL_TSTEP].intervals = 1;
		tstep_info[hh][NORMAL_TSTEP].threshold = DEFAULT_NORMAL_THRESHOLD; // 60

		tstep_info[hh][MEDIUM_TSTEP].level = MEDIUM_TSTEP;
		tstep_info[hh][MEDIUM_TSTEP].time_step = 24 * 3600 / Global::Freq / 4;
		tstep_info[hh][MEDIUM_TSTEP].intervals = 4;
		tstep_info[hh][MEDIUM_TSTEP].threshold = DEFAULT_MEDIUM_THRESHOLD; // 10

		tstep_info[hh][SMALL_TSTEP].level = SMALL_TSTEP;
		tstep_info[hh][SMALL_TSTEP].time_step = 24 * 3600 / Global::Freq / 60;
		tstep_info[hh][SMALL_TSTEP].intervals = 15;
		tstep_info[hh][SMALL_TSTEP].threshold = DEFAULT_SMALL_THRESHOLD;  // 1
	}
}

void ClassSnobalX::init(void) {
	ClassSnobalBase::init();
}

void ClassSnobalX::run(void) { // executed every interval

	if (getstep() == 1) { // beginning of model run. Handle initial state file problems
		for (hh = 0; chkStruct(); ++hh) {
			if (m_s[hh] <= 0)
				layer_count[hh] = 0;
			else {
				rho[hh] = m_s[hh] / z_s[hh];
				if (layer_count[hh] <= 0)
					layer_count[hh] = 1;
			}
		}
	}

	for (hh = 0; chkStruct(); ++hh) {

		T_s[hh] += CRHM_constants::Tm; // temperatures inside Snobal model are �K
		T_s_0[hh] += CRHM_constants::Tm;
		T_s_l[hh] += CRHM_constants::Tm;

		T_snow[hh] += CRHM_constants::Tm;
		T_rain[hh] += CRHM_constants::Tm;

		input_rec2[hh].S_n = S_n_X[hh];
		input_rec2[hh].I_lw = I_lw_X[hh];
		input_rec2[hh].T_a = T_a_X[hh] + CRHM_constants::Tm;
		input_rec2[hh].e_a = e_a_X[hh] * 1000;
		input_rec2[hh].u = u_X[hh];
		input_rec2[hh].T_g = T_g_X[hh] + CRHM_constants::Tm;

		m_precip[hh] = m_precip_X[hh];
		m_snow[hh] = m_snow_X[hh];
		m_drift[hh] = m_drift_X[hh];
		m_subl[hh] = m_subl_X[hh];
		m_rain[hh] = m_rain_X[hh];
		rho_snow[hh] = rho_snow_X[hh];

		m_precip_cum[hh] += m_precip[hh];
		m_rain_cum[hh] += m_rain[hh];
		m_snow_cum[hh] += m_snow[hh];
		m_drift_cum[hh] += m_drift[hh];
		m_subl_cum[hh] += m_subl[hh];

		if (m_snow[hh] > 0.0) {
			if (rho_snow[hh] <= 0.0) {
				CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TERMINATE);
				LogError(TExcept);
			}
			z_snow[hh] = m_snow[hh] / rho_snow[hh];
		}
		else
			z_snow[hh] = 0.0;

		T_pp[hh] = T_pp_X[hh] + CRHM_constants::Tm;

		// clear interval values

		snowmelt_int[hh] = 0.0;
		melt_direct_int[hh] = 0.0;
		sum[hh] = 0.0;
		E_s_int[hh] = 0.0;
		E_int[hh] = 0.0;
		E_s_0_int[hh] = 0.0;
		E_s_l_int[hh] = 0.0;
		ro_predict[hh] = 0.0;

		long Step = getstep();
		if (getstep() > 1) { // Not first step

			if (m_precip[hh] > 0.0) {
				stop_no_snow[hh] = 0;
				precip_now[hh] = true;
			}
			else {
				if (layer_count[hh] == 0)
					stop_no_snow[hh] = 1;
				precip_now[hh] = false;
			}

			// process blowing snow event
			_drift();

			do_data_tstep(); // executes Snobal code
		}
		else if (m_precip[hh] > 0.0) {
			CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", WARNING);
			LogError(TExcept);
		}

		if (Step % Global::Freq == 1)
			snowmeltD[hh] = snowmelt_int[hh];
		else
			snowmeltD[hh] += snowmelt_int[hh];

		input_rec1[hh].S_n = input_rec2[hh].S_n;
		input_rec1[hh].I_lw = input_rec2[hh].I_lw;
		input_rec1[hh].T_a = input_rec2[hh].T_a;
		input_rec1[hh].e_a = input_rec2[hh].e_a;
		input_rec1[hh].u = input_rec2[hh].u;
		input_rec1[hh].T_g = input_rec2[hh].T_g;

		E_s_cum[hh] += E_s_int[hh];
		sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
		cumsnowmelt[hh] += snowmelt_int[hh];
		melt_direct_cum[hh] += melt_direct_int[hh];

		T_s[hh] -= CRHM_constants::Tm; // temperatures outside Snobal model are �C
		T_s_0[hh] -= CRHM_constants::Tm;
		T_s_l[hh] -= CRHM_constants::Tm;

		T_snow[hh] -= CRHM_constants::Tm;
		T_rain[hh] -= CRHM_constants::Tm;
	}
}

void ClassSnobalBase::finish(bool good) { // only required for local storage and final output

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Snobal)' m_precip_cum    (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_precip_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' m_rain_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_rain_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' m_snow_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_snow_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' m_drift_cum     (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_drift_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' m_subl_cum      (mm) (mm*hru) (mm*hru/basin): ").c_str(), -m_subl_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' SWE             (mm) (mm*hru) (mm*hru/basin): ").c_str(), m_s[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (Snobal)' E_s_cum         (mm) (mm*hru) (mm*hru/basin): ").c_str(), E_s_cum[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' cumsnowmelt     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmelt[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Snobal)' melt_direct_cum (mm) (mm*hru) (mm*hru/basin): ").c_str(), melt_direct_cum[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}

	delete[] input_rec1;   // [nhru]
	delete[] input_rec2;   // [nhru]
	delete[] time_step;    // [nhru]
	delete[] current_time; // [nhru]

	for (long ii = 0; ii < nhru; ++ii) {
		delete[] computed[ii];         // [nhru] [4]
		delete[] input_deltas[ii];     // [nhru] [4]
		delete[] precip_info[ii];      // [nhru] [4]
		delete[] tstep_info[ii];       // [nhru] [4]
	}

	delete[] computed;
	delete[] input_deltas;
	delete[] precip_info;
	delete[] tstep_info;
}

void ClassSnobalX::finish(bool good) { // only required for local storage and final output

	ClassSnobalBase::finish(good);
}

ClassSnobalCRHM* ClassSnobalCRHM::klone(string name) const {
	return new ClassSnobalCRHM(name);
}

void ClassSnobalCRHM::decl(void) {

	Description = "'A model using the energy balance to calculate snowmelt (Marks, et. al (1997)). Standard CRHM module.' \
                 'use Qsi (W/m^2) and Qli (W/m^2) observations,' \
                 'use variables Qsisn_Var (W/m^2) and Qlisn_Var (W/m^2) from module CanopyClearing.' \
                 'use observation Qsi (W/m^2) and QliVt_Var (W/m^2) from module longVt.' \
                 'use variables QsiS_Var (W/m^2) from Annandale and QliVt_Var (W/m^2) from module longVt.'";

	declstatvar("layer_count", NHRU, "number of layers in snowcover: 0, 1, or 2", "()", &layer_count);
	declstatvar("isothermal", NHRU, "melting: 0/1", "()", &isothermal);
	declstatvar("snowcover", NHRU, "snow on gnd at start of current timestep: 0/1", "()", &snowcover);

	declvar("R_n", NHRU, "net allwave radiation", "(W/m^2)", &R_n);
	declvar("H", NHRU, "sensible heat xfr", "(W/m^2)", &H);
	declvar("L_v_E", NHRU, "latent heat xfr", "(W/m^2)", &L_v_E);
	declvar("G", NHRU, "heat xfr by conduction & diffusion from soil to snowcover", "(W/m^2)", &G);
	declvar("M", NHRU, "advected heat from precip", "(W/m^2)", &M);
	declvar("delta_Q", NHRU, "change in snowcover's energy", "(W/m^2)", &delta_Q);
	declvar("G_0", NHRU, "heat xfr by conduction & diffusion from soil or lower layer to active layer", "(W/m^2)", &G_0);
	declvar("delta_Q_0", NHRU, "change in active layer's energy", "(W/m^2)", &delta_Q_0);

	declstatvar("cc_s_0", NHRU, "active layer cold content", "(J/m^2)", &cc_s_0);
	declstatvar("cc_s_l", NHRU, "lower layer cold content", "(J/m^2)", &cc_s_l);
	declstatvar("cc_s", NHRU, "snowcover's cold content", "(J/m^2)", &cc_s);
	declstatvar("h2o", NHRU, "liquid h2o content as specific mass", "(kg/m^2)", &h2o);

	decllocal("E_s", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2)", &E_s);
	decllocal("E", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*s)", &E);
	decllocal("E_s_0", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0);
	decllocal("E_s_l", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l);
	decllocal("melt", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2)", &melt);
	declvar("ro_predict", NHRU, "predicted specific runoff", "(m/s)", &ro_predict);
	declvar("h2o_total", NHRU, "total liquid h2o: includes h2o in snowcover, melt, and rainfall", "(kg/m^2)", &h2o_total);

	decldiag("E_s_int", NHRU, "mass of evap into air & soil from snowcover", "(kg/m^2*int)", &E_s_int);
	decldiag("E_int", NHRU, "mass flux by evap into air from active layer", "(kg/m^2*int)", &E_int);
	decldiag("E_s_0_int", NHRU, "mass of evaporation to air", "(kg/m^2*int)", &E_s_0_int);
	decldiag("E_s_l_int", NHRU, "mass of evaporation to soil", "(kg/m^2*int)", &E_s_l_int);
	declvar("melt_direct_int", NHRU, "specific melt (kg/m^2 or m)", "(kg/m^2*int)", &melt_direct_int);
	declvar("sum", NHRU, "sum of SWE, snowmelt, drift, subl", "(mm)", &sum);
	declvar("SWE_change", NHRU, "interval change in SWE", "(mm)", &SWE_change);
	declvar("snowmelt_int", NHRU, "snow melt", "(kg/m^2*int)", &snowmelt_int);
	declvar("snowmeltD", NHRU, "daily snow melt", "(mm/d)", &snowmeltD);
	decllocal("snowmeltD_acc", NHRU, "daily snow melt accumulator", "(mm/d)", &snowmeltD_acc);
	declvar("cumsnowmelt", NHRU, "cumulative melt", "(mm)", &cumsnowmelt);


	declstatvar("z_s_0", NHRU, "active layer depth", "(m)", &z_s_0);
	declstatvar("z_s_l", NHRU, "lower layer depth", "(m)", &z_s_l);
	declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

	declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

	declstatvar("m_s_0", NHRU, "active layer specific mass", "(kg/m^2)", &m_s_0);
	declstatvar("m_s_l", NHRU, "lower layer specific mass", "(kg/m^2)", &m_s_l);
	declstatvar("SWE", NHRU, "snowcover's specific mass", "(kg/m^2)", &m_s);

	declstatvar("T_s_0", NHRU, "active snow layer temp", "(�C)", &T_s_0);
	declstatvar("T_s_l", NHRU, "lower layer temp", "(�C)", &T_s_l);
	declstatvar("T_s", NHRU, "average snowcover temp", "(�C)", &T_s);

	declstatvar("h2o_sat", NHRU, "fraction of liquid H2O saturation (0 to 1.0)", "()", &h2o_sat);
	declvar("h2o_vol", NHRU, "liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &h2o_vol);
	declvar("h2o_max", NHRU, "max liquid h2o content as specific mass", "(kg/m^2)", &h2o_max);

	declvar("z_snow", NHRU, "depth of snow in precip", "(m)", &z_snow);
	declvar("h2o_sat_snow", NHRU, "snowfall's % of liquid H2O saturation", "()", &h2o_sat_snow);

	declvar("precip_now", NHRU, "precipitation occur for current timestep - 0/1", "()", &precip_now);
	declvar("T_rain", NHRU, "rain's temp", "(�C)", &T_rain);
	declvar("T_snow", NHRU, "snowfall's temp", "(�C)", &T_snow);

	decllocal("S_n_L", NHRU, "net solar radiation", "(W/m^2)", &S_n);
	decllocal("I_lw_L", NHRU, "incoming longwave (thermal) rad ", "(W/m^2)", &I_lw);
	decllocal("T_a_L", NHRU, "air temp", "(�C)", &T_a);
	decllocal("e_a_L", NHRU, "vapor pressure", "(Pa)", &e_a);
	decllocal("u_L", NHRU, "wind speed", "(m/s)", &u);
	decllocal("T_g_L", NHRU, "soil temp at depth z_g", "(�C)", &T_g);
	decllocal("F_g_L", NHRU, "soil flux at depth z_g", "(W/m^2)", &F_g);

	decllocal("m_precip_L", NHRU, "specific mass of total precip", "(kg/m^2)", &m_precip);
	declvar("rain_on_snow", NHRU, "specific mass of rain in precip", "(kg/m^2)", &m_rain);
	decllocal("m_snow_L", NHRU, "specific mass in snow in precip", "(kg/m^2)", &m_snow);
	decllocal("m_drift_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_drift);
	decllocal("m_subl_L", NHRU, "specific mass of drifting snow", "(kg/m^2)", &m_subl);
	decllocal("rho_snow_L", NHRU, "density of snowfall", "(kg/m^2)", &rho_snow);
	decllocal("T_pp_L", NHRU, "precip temp", "(�C)", &T_pp);

	decllocal("P_a", NHRU, "air pressure", "(Pa)", &P_a);

	decllocal("m_precip_cum", NHRU, "cumulative specific mass of total precip", "(kg/m^2)", &m_precip_cum);
	decllocal("m_rain_cum", NHRU, "cumulative specific mass of total rain", "(kg/m^2)", &m_rain_cum);
	decllocal("m_snow_cum", NHRU, "cumulative specific mass of total snow", "(kg/m^2)", &m_snow_cum);
	decllocal("m_drift_cum", NHRU, "cumulative specific mass of total drifting snow", "(kg/m^2)", &m_drift_cum);
	decllocal("m_subl_cum", NHRU, "cumulative specific mass of total sublimation", "(kg/m^2)", &m_subl_cum);
	decllocal("E_s_cum", NHRU, "cumulative mass flux by evap into air from active layer", "(kg/m^2)", &E_s_cum);
	decllocal("melt_direct_cum", NHRU, "cumulative melt when SWE < threshold melt", "(kg/m^2)", &melt_direct_cum);

	decllocal("stop_no_snow", NHRU, "snow flag", "()", &stop_no_snow);
	decllocal("snow_store", NHRU, "accumulates snow till significant", "()", &snow_store);

	decldiagparam("relative_hts", NHRU, "[0]", "0", "1", "1 - measurements heights, z_T and z_u, are relative to snow, i.e. 0 -> use (z_T), 1 -> use (z_T - z_s)", "()", &relative_hts);

	declparam("z_g", NHRU, "[0.01]", "0.1", "1.0", "depth of soil temp meas", "(m)", &z_g);
	declparam("z_u", NHRU, "[1.0]", "0.0", "10.0", "height of wind measurement", "(m)", &z_u);
	declparam("z_T", NHRU, "[1.0]", "0.0", "10.0", "height of air temp & vapor pressure measurement", "(m)", &z_T);
	declparam("z_0", NHRU, "[0.001]", "0.0001", "0.1", "roughness length", "(m)", &z_0);

	declparam("max_z_s_0", NHRU, "[0.1]", "0.0", "0.35", "maximum active layer thickness", "(m)", &max_z_s_0);
	declparam("max_h2o_vol", NHRU, "[0.0001]", "0.0001", "0.2", "max liquid h2o content as volume ratio: V_water/(V_snow - V_ice)", "()", &max_h2o_vol);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);
	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
	declparam("hru_rho_snow", NHRU, "[100]", "50", "1000", "rho of falling snow", "(kg/m^3)", &rho_snow_X);
	declparam("hru_T_g", NHRU, "[-4]", "-50", "50", "ground temperature used when observation T_g not available", "(�C)", &T_g_X);
	declparam("hru_F_g", NHRU, "[0]", "-50", "50", "ground flux used when observation F_g not available", "(W/m^2)", &F_g_X);
	declparam("T_g_or_G_flux", NHRU, "[0]", "0", "1", "0 - calculate ground flux from ground temperature, 1 - use ground flux value", "()", &T_g_or_G_flux);

	decldiagparam("rain_soil_snow", NHRU, "[0]", "0", "1", "0 - handle only snow (module Soil handles rain), 1 - handle snow and rain in this module (when SWE > 0.02mm).", "()", &rain_soil_snow);

	declparam("KT_sand", NHRU, "[0.08]", "0.01", "3.0", "thermal conductivity of wet sand (J/(m sec K)(from Oke, 1978, pg. 38)", "()", &KT_sand);

	declgetvar("*", "hru_t", "(�C)", &T_a_X);
	declgetvar("*", "hru_t", "(�C)", &T_pp_X); // default precipitation temperature to air
	declgetvar("*", "hru_ea", "(kPa)", &e_a_X);
	declgetvar("*", "hru_u", "(m/s)", &u_X);

	declgetvar("*", "net_p", "(kg/m^2)", &m_precip_X);
	declgetvar("*", "net_snow", "(kg/m^2)", &m_snow_X);
	declgetvar("*", "hru_drift", "(kg/m^2)", &m_drift_X);
	declgetvar("*", "hru_subl", "(kg/m^2)", &m_subl_X);
	declgetvar("*", "Albedo", "()", &Albedo);

	declputvar("*", "net_rain", "(kg/m^2)", &m_rain_X);

	declreadobs("T_g", NHRU, "ground temperature", "(�C)", &T_g_Obs, HRU_OBS_misc, true);

	declreadobs("F_g", NHRU, "ground flux", "(W/m^2)", &F_g_Obs, HRU_OBS_misc, true);

	variation_set = VARIATION_0 + VARIATION_2;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

	variation_set = VARIATION_0;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

	variation_set = VARIATION_1;

	declgetvar("*", "Qsisn_Var", "(W/m^2)", &Qsisn_Var);

	declgetvar("*", "Qlisn_Var", "(W/m^2)", &Qlisn_Var);

	variation_set = VARIATION_2 + VARIATION_3;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);

	variation_set = VARIATION_3;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

	variation_set = VARIATION_ORG;
}

void ClassSnobalCRHM::init(void) {

	ClassSnobalBase::init();
	if (!T_g_Obs) {
		CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground temperature T_g observation not available using parameter hru_T_g.").c_str(), WARNING);
		LogError(TExcept);
	}

	if (!F_g_Obs) {
		CRHMException TExcept(string("'" + Name + " (SnobalCRHM)' ground flux F_g observation not available using parameter hru_F_g.").c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; chkStruct(); ++hh) {
		snow_store[hh] = 0.0;
		snowmeltD[hh] = 0.0;
	}
}

void ClassSnobalCRHM::run(void) { // executed every interval

	long nstep = getstep() % Global::Freq;

	if (getstep() == 1) { // beginning of model run. Handle initial state file problems
		for (hh = 0; chkStruct(); ++hh) {
			if (m_s[hh] <= 0)
				layer_count[hh] = 0;
			else {
				rho[hh] = m_s[hh] / z_s[hh];
				if (layer_count[hh] <= 0)
					layer_count[hh] = 1;
			}
		}
	}

	for (hh = 0; chkStruct(); ++hh) {

		T_s[hh] += CRHM_constants::Tm; // temperatures inside Snobal model are �K
		T_s_0[hh] += CRHM_constants::Tm;
		T_s_l[hh] += CRHM_constants::Tm;

		T_snow[hh] += CRHM_constants::Tm;
		T_rain[hh] += CRHM_constants::Tm;

		SWE_change[hh] = -m_s[hh];

		switch (variation) {
		case VARIATION_ORG:
			input_rec2[hh].S_n = Qsi[hh] * (1.0 - Albedo[hh]);
			input_rec2[hh].I_lw = Qli[hh];
			break;
		case VARIATION_1:
			input_rec2[hh].S_n = Qsisn_Var[hh] * (1.0 - Albedo[hh]);
			input_rec2[hh].I_lw = Qlisn_Var[hh];
			break;
		case VARIATION_2:
			input_rec2[hh].S_n = Qsi[hh] * (1.0 - Albedo[hh]);
			input_rec2[hh].I_lw = QliVt_Var[hh];
			break;
		case VARIATION_3:
			input_rec2[hh].S_n = QsiS_Var[hh] * (1.0 - Albedo[hh]);
			input_rec2[hh].I_lw = QliVt_Var[hh];
			break;
		}


		input_rec2[hh].T_a = T_a_X[hh] + CRHM_constants::Tm;
		input_rec2[hh].e_a = e_a_X[hh] * 1000;
		input_rec2[hh].u = u_X[hh];

		if (F_g_Obs)
			input_rec2[hh].F_g = F_g_Obs[hh];
		else
			input_rec2[hh].F_g = F_g_X[hh];

		if (T_g_Obs) // only convert degrees not fluxes
			input_rec2[hh].T_g = T_g_Obs[hh] + CRHM_constants::Tm;
		else
			input_rec2[hh].T_g = T_g_X[hh] + CRHM_constants::Tm;

		if (m_snow_X[hh] == 0)
			m_snow[hh] = 0.0;

		if (snowcover[hh]) {
			m_snow[hh] = m_snow_X[hh];
		}
		else {
			if (m_snow_X[hh] > 0.0)
				snow_store[hh] += m_snow_X[hh];
			m_snow[hh] = 0.0;
		}

		if ((nstep == 1 && snow_store[hh] > 0.0) || snow_store[hh] > 1.0) {
			m_snow[hh] = snow_store[hh];
			snow_store[hh] = 0.0;
		}

		if (rain_soil_snow[hh] && snowcover[hh]) { // handle snow and rain over snow cover
			m_precip[hh] = m_precip_X[hh];
			m_rain[hh] = m_rain_X[hh];
			m_rain_X[hh] = 0.0;
		}
		else { // handle only snow. Infitration routine handles rain
			m_precip[hh] = m_snow_X[hh];
			m_rain[hh] = 0.0;
		}

		m_drift[hh] = m_drift_X[hh];
		m_subl[hh] = m_subl_X[hh];
		rho_snow[hh] = rho_snow_X[hh];

		m_precip_cum[hh] += m_precip[hh]; // change
		m_rain_cum[hh] += m_rain[hh];
		m_snow_cum[hh] += m_snow[hh];
		m_drift_cum[hh] += m_drift[hh];
		m_subl_cum[hh] += m_subl[hh];

		if (m_snow[hh] > 0.0) {
			if (rho_snow[hh] <= 0.0) {
				CRHMException TExcept("Snobal: rho_snow is <= 0.0 with snow > 0.0", TERMINATE);
				LogError(TExcept);
			}
			z_snow[hh] = m_snow[hh] / rho_snow[hh];
		}
		else
			z_snow[hh] = 0.0;

		T_pp[hh] = T_pp_X[hh] + CRHM_constants::Tm;

		// clear interval values

		snowmelt_int[hh] = 0.0;
		melt_direct_int[hh] = 0.0;
		sum[hh] = 0.0;
		E_s_int[hh] = 0.0;
		E_int[hh] = 0.0;
		E_s_0_int[hh] = 0.0;
		E_s_l_int[hh] = 0.0;
		ro_predict[hh] = 0.0;

		long Step = getstep();
		if (getstep() > 1) { // Not first step

			if (m_precip[hh] > 0.0) {
				stop_no_snow[hh] = 0;
				precip_now[hh] = true;
			}
			else {
				if (layer_count[hh] == 0)
					stop_no_snow[hh] = 1;
				precip_now[hh] = false;
			}

			// process blowing snow event
			_drift();

			do_data_tstep(); // executes Snobal code

		}
		else if (m_precip[hh] > 0.0) {
			CRHMException TExcept("Snobal - cannot handle precipitation during first day of model run", WARNING);
			LogError(TExcept);
		}

		Step = Step % Global::Freq;
		if (Step == 1)
			snowmeltD_acc[hh] = snowmelt_int[hh];
		else
			snowmeltD_acc[hh] += snowmelt_int[hh];

		if (Step == 0) {
			snowmeltD[hh] = snowmeltD_acc[hh];
			snowmeltD_acc[hh] = 0.0;
		}

		input_rec1[hh].S_n = input_rec2[hh].S_n;
		input_rec1[hh].I_lw = input_rec2[hh].I_lw;
		input_rec1[hh].T_a = input_rec2[hh].T_a;
		input_rec1[hh].e_a = input_rec2[hh].e_a;
		input_rec1[hh].u = input_rec2[hh].u;
		input_rec1[hh].T_g = input_rec2[hh].T_g;
		input_rec1[hh].F_g = input_rec2[hh].F_g;

		E_s_cum[hh] += E_s_int[hh];
		sum[hh] = m_s[hh] + m_drift_cum[hh] + m_subl_cum[hh] + cumsnowmelt[hh] + E_s_cum[hh];
		SWE_change[hh] += m_s[hh];
		cumsnowmelt[hh] += snowmelt_int[hh];
		melt_direct_cum[hh] += melt_direct_int[hh];

		T_s[hh] -= CRHM_constants::Tm; // temperatures outside Snobal model are �C
		T_s_0[hh] -= CRHM_constants::Tm;
		T_s_l[hh] -= CRHM_constants::Tm;

		T_snow[hh] -= CRHM_constants::Tm;
		T_rain[hh] -= CRHM_constants::Tm;
	}
}

void ClassSnobalCRHM::finish(bool good) { // only required for local storage and final output

	ClassSnobalBase::finish(good);
}

/*
** DESCRIPTION
**      This routine initializes the properties for the snowcover.  It
**	determines the number of layers, their individual properties,
**	the cold content for the snowcover and its layers, and the
**	snowcover's water content.  The following global variables
**	should be initialized before invoking this routine:
**
**		z_s	depth of snowcover (m)
**		rho	density of snowcover (kg/m^3)
**		T_s	average temperature of snowcover (K)
**		T_s_0	temperature of surface layer of snowcover (K)
**		T_s_l	temperature of lower layer of snowcover (K)
**		h2o_sat	% of liquid h2o saturation (0 to 1.0)
**
**		max_h2o_vol	maximum liquid h2o[hh] content as volume ratio:
**				    V_water/(V_snow - V_ice) (unitless)
**
** GLOBAL VARIABLES READ
**	h2o_sat
**	layer_count
**	m_s_0
**	m_s_l
**	max_h2o_vol
**	rho
**	T_s
**	T_s_0
**	T_s_l
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	cc_s
**	cc_s_0
**	cc_s_l
**	h2o
**	h2o_max
**	h2o_total
**	h2o_vol
**	m_s
**	m_s_0
**	m_s_l
**	rho
**	T_s
**	T_s_0
**	T_s_l
**	(and those variables modified by "_calc_layer", "_layer_mass" and cold_content)
*/

void ClassSnobalBase::init_snow(void)
{
	float	rho_dry;	// snow density without H2O

	m_s[hh] = rho[hh] * z_s[hh];

	_calc_layers();

	if (layer_count[hh] == 0) {

		// If mass > 0, then it must be below threshold. So turn this little bit of mass into water.

		if (m_s[hh] > 0.0) {
			h2o_total[hh] += m_s[hh];
			melt_direct_int[hh] += m_s[hh];
		}

		rho[hh] = 0.0;
		m_s[hh] = cc_s[hh] = 0.0;
		m_s_0[hh] = cc_s_0[hh] = 0.0;
		m_s_l[hh] = cc_s_l[hh] = 0.0;

		// Note: Snow temperatures are set to MIN_SNOW_TEMP (as degrees K) instead of 0 K to keep quantization range in output image smaller.

		T_s[hh] = T_s_0[hh] = T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
		h2o_vol[hh] = h2o[hh] = h2o_max[hh] = h2o_sat[hh] = 0.0;
	}
	else {

		// Compute specific mass for each layer.

		_layer_mass();

		cc_s_0[hh] = _cold_content(T_s_0[hh], m_s_0[hh]);

		if (layer_count[hh] == 2) {
			cc_s_l[hh] = _cold_content(T_s_l[hh], m_s_l[hh]);
		}
		else {
			T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
			cc_s_l[hh] = 0.0;
		}

		// Compute liquid water content as volume ratio, and snow density without water.

		h2o_vol[hh] = h2o_sat[hh] * max_h2o_vol[hh];
		rho_dry = DRY_SNO_RHO(rho[hh], h2o_vol[hh]);

		// Determine maximum liquid water content (as specific mass) and the actual liquid water content (as specific mass).

		h2o_max[hh] = H2O_LEFT(z_s[hh], rho_dry, max_h2o_vol[hh]);

		h2o[hh] = h2o_sat[hh] * h2o_max[hh];
		stop_no_snow[hh] = 0; //????
	}
}

/*
** NAME
**      void _calc_layers(void) -- determine # of layers in snowcover and their depths
**
** DESCRIPTION
**      This routine determines the # of layers in the snowcover based its
**	depth and mass.  Usually, there are are 2 layers: the surface (active)
**	and the lower layer.  The depth of the surface layer is set to the
**	maximum depth for the surface layer (variable "max_z_s_0").  The
**	remaining depth constitutes the lower layer.  The routine checks
**	to see if the mass of this lower layer is above the minium threshold
**	(i.e., the mass threshold for the small run timestep).  If not,
**	the surface layer is the whole snowcover, and there's no lower
**	layer.
**
** GLOBAL VARIABLES READ
**	m_s
**	max_z_s_0
**	rho[hh]
**	tstep_info
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	layer_count
**	z_s
**	z_s_0
**	z_s_l
*/

void ClassSnobalBase::_calc_layers(void)
{
	if (m_s[hh] <= tstep_info[hh][SMALL_TSTEP].threshold) {

		// Less than minimum layer mass, so treat as no snowcover.

		layer_count[hh] = 0;
		z_s[hh] = z_s_0[hh] = z_s_l[hh] = 0.0;
	}
	else if (z_s[hh] < max_z_s_0[hh]) {

		// Not enough depth for surface layer and the lower layer, so just 1 layer: surface layer.

		layer_count[hh] = 1;
		z_s_0[hh] = z_s[hh];
		z_s_l[hh] = 0.0;
	}
	else {

		// Enough depth for both layers.

		layer_count[hh] = 2;
		z_s_0[hh] = max_z_s_0[hh];
		z_s_l[hh] = z_s[hh] - z_s_0[hh];

		// However, make sure there's enough MASS for the lower layer.  If not, then there's only 1 layer.

		if (z_s_l[hh] * rho[hh] < tstep_info[hh][SMALL_TSTEP].threshold) {
			layer_count[hh] = 1;
			z_s_0[hh] = z_s[hh];
			z_s_l[hh] = 0.0;
		}
	}
}

/*
** NAME
**      void _layer_mass(void) -- calculate the specific mass for each snow layer
**
** DESCRIPTION
**      This routine computes the specific mass for each snow layer in
**	the snowcover.  A layer's mass is based its depth and the
**	average snowcover density.
**
** GLOBAL VARIABLES READ
**	layer_count
**	rho
**	z_s_0
**	z_s_l
**
** GLOBAL VARIABLES MODIFIED
**	m_s_0
**	m_s_l
*/

void ClassSnobalBase::_layer_mass(void)
{
	if (layer_count[hh] == 0) {
		m_s_0[hh] = 0.0;
		m_s_l[hh] = 0.0;
	}
	else {  // layer_count is 1 or 2
		m_s_0[hh] = rho[hh] * z_s_0[hh];
		if (layer_count[hh] == 2)
			m_s_l[hh] = rho[hh] * z_s_l[hh];
		else
			m_s_l[hh] = 0.0;
	}
}

/*
** NAME
**      _cold_content -- calculates cold content for a layer
**
**      float
**	_cold_content(
**	    float  temp,		|* temperature of layer *|
**	    float  mass)		|* specific mass of layer *|
**
** DESCRIPTION
**      This routine calculates the cold content for a layer (i.e., the
**	energy required to bring its temperature to freezing) from the
**	layer's temperature and specific mass.
**
** RETURN VALUE
**	The layer's cold content.
*/

float ClassSnobalBase::_cold_content(
	float	temp,		// temperature of layer
	float	mass)		// specific mass of layer
{
	if (temp < FREEZE)
		return heat_stor(CP_ICE(temp), mass, (temp - FREEZE));
	else
		return 0.0;
}

/*
** NAME
**      int do_data_tstep(void) -- run model for 1 data timestep between 2 input records
**
** DESCRIPTION
**	This routine performs the model's calculations for 1 data timestep
**	between 2 input-data records which are in 'input_rec1' and
**	'input_rec2'.
**
**	If there's precipitation during the data timestep, the flag
**	'precip_now' used be TRUE.  Furthermore, the routine requires
**	that the following precipitation variables have been initialized:
**
**		m_pp
**		percent_snow
**		rho_snow
**		T_pp
**
**	This routine divides the data timestep into the appropriate number
**	of normal run timesteps.  The input values for each normal timestep
**	are computed from the two input records by linear interpolation.
**
** RETURN VALUE
**
**	TRUE	The model's calculations were completed.
**
**	FALSE	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	e_a
**	I_lw
**	in_rec
**	layer_count
**	m_pp_data
**	m_rain_data
**	m_snow_data
**	more_pr_recs
**	precip_data
**	S_n
**	T_a
**	T_g
**	tstep_info
**	u
**	z_snow_data
**
** GLOBAL VARIABLES MODIFIED
**	precip_now
*/

void ClassSnobalBase::do_data_tstep(void) {

	int level; // loop index

			   //  Copy values from first input record into global variables.

	S_n[hh] = input_rec1[hh].S_n;
	I_lw[hh] = input_rec1[hh].I_lw;
	T_a[hh] = input_rec1[hh].T_a;
	e_a[hh] = input_rec1[hh].e_a;
	u[hh] = input_rec1[hh].u;
	T_g[hh] = input_rec1[hh].T_g;
	F_g[hh] = input_rec1[hh].F_g;

	// Compute deltas for the climate input parameters over the CRHM data timestep.

	input_deltas[hh][DATA_TSTEP].S_n = input_rec2[hh].S_n - input_rec1[hh].S_n;
	input_deltas[hh][DATA_TSTEP].I_lw = input_rec2[hh].I_lw - input_rec1[hh].I_lw;
	input_deltas[hh][DATA_TSTEP].T_a = input_rec2[hh].T_a - input_rec1[hh].T_a;
	input_deltas[hh][DATA_TSTEP].e_a = input_rec2[hh].e_a - input_rec1[hh].e_a;
	input_deltas[hh][DATA_TSTEP].u = input_rec2[hh].u - input_rec1[hh].u;
	input_deltas[hh][DATA_TSTEP].T_g = input_rec2[hh].T_g - input_rec1[hh].T_g;
	input_deltas[hh][DATA_TSTEP].F_g = input_rec2[hh].F_g - input_rec1[hh].F_g;

	// If there is precipitation, then compute the amount of rain & snow in it.

	precip_info[hh]->m_drift = m_drift[hh];
	precip_info[hh]->m_subl = m_subl[hh];

	if (precip_now[hh]) {
		precip_info[hh]->m_pp = m_precip[hh];
		precip_info[hh]->m_snow = m_snow[hh];
		precip_info[hh]->m_rain = m_rain[hh];

		if (precip_info[hh]->m_snow > 0.0)
			precip_info[hh]->z_snow = z_snow[hh];
		else
			precip_info[hh]->z_snow = 0.0;

		// Mixed snow and rain

		if ((precip_info[hh]->m_snow > 0.0) && (precip_info[hh]->m_rain > 0.0)) {
			T_snow[hh] = FREEZE;
			h2o_sat_snow[hh] = 1.0;
			T_rain[hh] = T_pp[hh];
		}

		// Snow only

		else if (precip_info[hh]->m_snow > 0.0) {
			if (T_pp[hh] < FREEZE) {	/* Cold snow */
				T_snow[hh] = T_pp[hh];
				h2o_sat_snow[hh] = 0.0;
			}
			else {				/* Warm snow */
				T_snow[hh] = FREEZE;
				h2o_sat_snow[hh] = 1.0;
			}
		}

		// Rain only

		else if (precip_info[hh]->m_rain > 0.0) {
			T_rain[hh] = T_pp[hh];
		}
	}
	else {
		precip_info[hh]->m_pp = 0.0;
		precip_info[hh]->m_snow = 0.0;
		precip_info[hh]->m_rain = 0.0;
		precip_info[hh]->z_snow = 0.0;
	}

	//  Clear the 'computed' flag at the other timestep levels.

	for (level = NORMAL_TSTEP; level <= SMALL_TSTEP; ++level)
		computed[hh][level] = 0;

	// Divide the data timestep into normal run timesteps.

	_divide_tstep(tstep_info[hh]);
}

/*
** NAME
**      int _divide_tstep( -- divide a timestep into smaller timesteps
**
**	int
**	_divide_tstep(
**	    TSTEP_REC *tstep;	|* record of timestep to be divided *|
**
** DESCRIPTION
**	This routine divides a timestep into smaller timesteps.  For
**	each of these smaller timestep, the routine either run the
**	model for that timestep, or further subdivides that timestep
**	into even smaller timesteps.
**
** RETURN VALUE
**
**	TRUE	The timestep was successfully divided into smaller timesteps.
**
**	FALSE	An error occured while running the model during one of the
**		smaller timesteps.  An message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	layer_count
**	precip_now
**	tstep_info
**
** GLOBAL VARIABLES MODIFIED
*/

int ClassSnobalBase::_divide_tstep(TSTEP_REC *tstep) {  // record of timestep to be divided

	TSTEP_REC  *next_lvl_tstep;	// info of next level of timestep
	INPUT_REC  *curr_lvl_deltas;	// -> input-deltas of current level
	INPUT_REC  *next_lvl_deltas;	// -> input-deltas of next level
	PRECIP_REC *curr_lvl_precip;	// -> precip data of current level
	PRECIP_REC *next_lvl_precip;	// -> precip data of next level
	int next_level;
	// Fetch the record for the timestep at the next level.

	next_level = tstep->level + 1;
	next_lvl_tstep = &tstep_info[hh][next_level];

	curr_lvl_deltas = &input_deltas[hh][tstep->level];
	next_lvl_deltas = &input_deltas[hh][next_level];

	curr_lvl_precip = &precip_info[hh][tstep->level];
	next_lvl_precip = &precip_info[hh][next_level];

	//  If this is the first time this new level has been used during
	//  the current data timestep, then calculate its input deltas and precipitation values.

	if (!computed[hh][next_level]) {
		next_lvl_deltas->S_n = curr_lvl_deltas->S_n / next_lvl_tstep->intervals;
		next_lvl_deltas->I_lw = curr_lvl_deltas->I_lw / next_lvl_tstep->intervals;
		next_lvl_deltas->T_a = curr_lvl_deltas->T_a / next_lvl_tstep->intervals;
		next_lvl_deltas->e_a = curr_lvl_deltas->e_a / next_lvl_tstep->intervals;
		next_lvl_deltas->u = curr_lvl_deltas->u / next_lvl_tstep->intervals;
		next_lvl_deltas->T_g = curr_lvl_deltas->T_g / next_lvl_tstep->intervals;
		next_lvl_deltas->F_g = curr_lvl_deltas->F_g / next_lvl_tstep->intervals;

		next_lvl_precip->m_pp = curr_lvl_precip->m_pp / next_lvl_tstep->intervals;
		next_lvl_precip->m_rain = curr_lvl_precip->m_rain / next_lvl_tstep->intervals;
		next_lvl_precip->m_snow = curr_lvl_precip->m_snow / next_lvl_tstep->intervals;
		next_lvl_precip->m_drift = curr_lvl_precip->m_drift / next_lvl_tstep->intervals;
		next_lvl_precip->m_subl = curr_lvl_precip->m_subl / next_lvl_tstep->intervals;
		next_lvl_precip->z_snow = curr_lvl_precip->z_snow / next_lvl_tstep->intervals;

		computed[hh][next_level] = 1;
	}

	// For each the new smaller timestep, either subdivide them if below their mass threshold, or run the model for them.

	for (int ii = 0; (ii < next_lvl_tstep->intervals) && !stop_no_snow[hh]; ++ii) { // execute every interval

		if ((next_level < SMALL_TSTEP) && _below_thold(next_lvl_tstep->threshold)) {
			if (!_divide_tstep(next_lvl_tstep)) // call self (this routine)
				return 0; // cannot get here unless _hl_e is coded to return error!
		}
		else {
			if (!_do_tstep(next_lvl_tstep)) // execute code
				return 0; // cannot get here unless _hl_e is coded to return error!
		}
	} // for

	return 1;
} // _divide_tstep

  /*
  ** NAME
  **      _below_thold -- is a layer's mass below a threshold ?
  **
  **      int
  **	_below_thold(
  **	    float  threshold)	|* current timestep's threshold for a
  **				   layer's mass *|
  **
  ** DESCRIPTION
  **      This routine determines if any individual layer's mass is below
  **	a given threshold for the current timestep.
  **
  ** RETURN VALUE
  **      	1	A layer's mass is less than the threshold.
  **
  **		0	All layers' masses are greater than the threshold.
  **
  ** GLOBAL VARIABLES READ
  **	layer_count
  **	m_s
  **	m_s_0
  **	m_s_l
  **
  ** GLOBAL VARIABLES MODIFIED
  */

int ClassSnobalBase::_below_thold(float	threshold) { // current timestep's threshold for a layer's mass

	if (layer_count[hh] == 0)
		return 0;

	if (layer_count[hh] == 1)
		return (m_s[hh] < threshold);
	else  /* layer_count == 2 */
		return ((m_s_0[hh] < threshold) || (m_s_l[hh] < threshold));
}

/*
** NAME
**      _do_tstep -- do model calculations for 1 timestep
**
**      int
**	_do_tstep(
**	    TSTEP_REC *tstep;  |* timestep's record *|
**
** DESCRIPTION
**      This routine performs the model's calculations for a single timestep.
**      It requires that these climate variables have been initialized:
**
**      	S_n
**      	I_lw
**      	T_a
**      	e_a
**      	u
**      	T_g
**
**	The routine also requires the precipitation data have been adjusted
**	for the timestep, and have been stored in the array:
**
**		precip_info
**
** RETURN VALUE
**
**	TRUE	The model's calculations were completed.
**
**	FALSE	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**	delta_Q
**	delta_Q_0
**	E_s
**	G
**	H
**	L_v_E
**	layer_count
**	M
**	melt
**	precip_now
**	R_n
**	ro_predict
**
** GLOBAL VARIABLES MODIFIED
**	current_time
**	curr_time_hrs
**	delta_Q_0_bar
**	delta_Q_bar
**	e_a
**	G_bar
**	H_bar
**	h2o_total
**	I_lw
**	L_v_E_bar
**	M_bar
**	m_precip
**	m_rain

**	m_snow
**	R_n_bar
**	S_n
**	snowcover
**	T_a
**	T_g
**	u
**	time_step
**	z_snow
*/

int ClassSnobalBase::_do_tstep(TSTEP_REC *tstep)  // timestep's record
{
	time_step[hh] = tstep->time_step;

	m_precip[hh] = precip_info[hh][tstep->level].m_pp;
	m_rain[hh] = precip_info[hh][tstep->level].m_rain;
	m_snow[hh] = precip_info[hh][tstep->level].m_snow;
	m_drift[hh] = precip_info[hh][tstep->level].m_drift;
	m_subl[hh] = precip_info[hh][tstep->level].m_subl;
	z_snow[hh] = precip_info[hh][tstep->level].z_snow;

	h2o_total[hh] = 0.0;
	melt[hh] = 0.0;

	// Is there a snowcover?

	snowcover[hh] = (layer_count[hh] > 0);

	// Calculate energy transfer terms

	if (!_e_bal())
		return 0;

	// Adjust mass and calculate runoff

	_mass_bal();

	//  Update the averages for the energy terms and the totals for mass changes since the last output.

	// increment time
	current_time[hh] += time_step[hh];

	//  update interval values

	snowmelt_int[hh] += ro_predict[hh];
	E_s_int[hh] += E_s[hh];
	E_int[hh] += E[hh];
	E_s_0_int[hh] += E_s_0[hh];
	E_s_l_int[hh] += E_s_l[hh];

	//  Update the model's input parameters

	S_n[hh] += input_deltas[hh][tstep->level].S_n;
	I_lw[hh] += input_deltas[hh][tstep->level].I_lw;
	T_a[hh] += input_deltas[hh][tstep->level].T_a;
	e_a[hh] += input_deltas[hh][tstep->level].e_a;
	u[hh] += input_deltas[hh][tstep->level].u;
	T_g[hh] += input_deltas[hh][tstep->level].T_g;
	F_g[hh] += input_deltas[hh][tstep->level].F_g;

	return 1;
}

/*
** NAME
**      int _e_bal(void) -- calculates point energy budget for 2-layer snowcover
**
** DESCRIPTION
**      Calculates point energy budget for 2-layer snowcover.
**
** RETURN VALUE
**
**	TRUE	The calculations were completed.
**
**	FALSE	An error occured, and a message explaining the error has
**		been stored with the 'usrerr' routine.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassSnobalBase::_e_bal(void) {

	if (snowcover[hh]) {

		// calculate energy xfer terms

		// calculate net radiation

		_net_rad();

		// calculate H & L_v_E  (and E as well)

		if (!_h_le())
			return 0;

		// calculate G & G_0(conduction/diffusion heat xfr)

		if (layer_count[hh] == 1) {

			if (T_g_or_G_flux[hh])
				G[hh] = F_g[hh]; // ground flux
			else
				G[hh] = g_soil(rho[hh], T_s_0[hh], T_g[hh], z_s_0[hh], z_g[hh], P_a[hh]);

			G_0[hh] = G[hh];
		}
		else {  //  layer_count[hh] == 2

			if (T_g_or_G_flux[hh])
				G[hh] = F_g[hh]; // ground flux
			else
				G[hh] = g_soil(rho[hh], T_s_l[hh], T_g[hh], z_s_l[hh], z_g[hh], P_a[hh]);

			G_0[hh] = g_snow(rho[hh], rho[hh], T_s_0[hh], T_s_l[hh], z_s_0[hh], z_s_l[hh], P_a[hh]);
		}

		// calculate advection

		_advec();

		// sum E.B. terms

		// surface energy budget

		delta_Q_0[hh] = R_n[hh] + H[hh] + L_v_E[hh] + G_0[hh] + M[hh];

		// total snowpack energy budget

		if (layer_count[hh] == 1)
			delta_Q[hh] = delta_Q_0[hh];
		else /* layer_count == 2 */
			delta_Q[hh] = delta_Q_0[hh] + G[hh] - G_0[hh];
	}
	else {
		R_n[hh] = 0.0;

		H[hh] = L_v_E[hh] = E[hh] = 0.0;

		G[hh] = G_0[hh] = 0.0;

		M[hh] = 0.0;

		delta_Q[hh] = delta_Q_0[hh] = 0.0;
	}

	return 1;
}

/*
** NAME
**      void _net_rad(void) -- calculates net allwave radiation
**
** DESCRIPTION
**      Calculates net allwave radiation from the net solar radiation
**	incoming thermal/longwave radiation, and the snow surface
**	temperature.
**
** GLOBAL VARIABLES READ
**	I_lw
**	S_n
**	T_s_0
**
** GLOBAL VARIABLES MODIFIED
**	R_n
*/

void ClassSnobalBase::_net_rad(void)
{
	//	R_n[hh] = S_n[hh] + (SNOW_EMISSIVITY * (I_lw[hh] - STEF_BOLTZ * pow(T_s_0[hh], 4.0f)));
	R_n[hh] = S_n[hh] + (I_lw[hh] - SNOW_EMISSIVITY * STEF_BOLTZ * pow(T_s_0[hh], 4.0f)); // correction 07/17/14
}

/*
** NAME
**      int _h_le(void) -- calculates turbulent transfer at a point
**
** DESCRIPTION
**      Calculates point turbulent transfer (H and L_v_E) for a 2-layer
**	snowcover.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

int ClassSnobalBase::_h_le(void) {

	float e_s, e_a_fix;
	float sat_vp;
	float rel_z_T; // relative z_T (temperature measurement height) above snow surface
	float rel_z_u; // relative z_u (windspeed measurement height) above snow surface

				   // calculate saturation vapor pressure

	e_s = sati(T_s_0[hh]);

	//*** error check for bad vapor pressures ***

	sat_vp = sati(T_a[hh]);
	if (e_a[hh] > sat_vp)
		e_a_fix = sat_vp;
	//		const_cast<float*> (e_a)[hh] = sat_vp;
	else
		e_a_fix = e_a[hh];

	// determine relative measurement heights
	if (!relative_hts[hh]) {
		rel_z_T = z_T[hh];
		rel_z_u = z_u[hh];
	}
	else {
		rel_z_T = z_T[hh] - z_s[hh];
		if (rel_z_T < 1.0)
			rel_z_T = 1.0;
		rel_z_u = z_u[hh] - z_s[hh];
		if (rel_z_u < 1.0)
			rel_z_u = 1.0;
	}

	// calculate H & L_v_E

	if (hle1(P_a[hh], T_a[hh], T_s_0[hh], rel_z_T, e_a_fix, e_s, rel_z_T, u[hh], rel_z_u, z_0[hh], H[hh], L_v_E[hh], E[hh]))
		return 1; // !!!!!TB

	return 1;
}

float ClassSnobalBase::g_soil(
	float	rho,	// snow layer's density (kg/m^3)
	float	tsno,	// snow layer's temperature (K)
	float	tg,	// soil temperature (K)
	float	ds,	// snow layer's thickness (m)
	float	dg,	// dpeth of soil temperature measurement (m)
	float	pa)	// air pressure (Pa)
{
	float	k_g;
	float	kcs;
	float	k_s;
	float	g;

	// check tsno
	if (tsno > FREEZE) {
		// warn("g_soil: tsno = %8.2f; set to %8.2f\n", tsno, FREEZE);
		tsno = FREEZE;
	}

	// set effective soil conductivity
	k_g = efcon(KT_sand[hh], tg, pa);   // 10/26/10

										// calculate G
										// set snow conductivity
	kcs = KTS(rho);
	k_s = efcon(kcs, tsno, pa);

	g = ssxfr(k_s, k_g, tsno, tg, ds, dg);

	return (g);
}

float ClassSnobalBase::g_snow(
	float	rho1,	/* upper snow layer's density (kg/m^3)	*/
	float	rho2,	/* lower  "     "        "    (kg/m^3)	*/
	float	ts1,	/* upper snow layer's temperature (K)	*/
	float	ts2,	/* lower  "     "         "       (K)	*/
	float	ds1,	/* upper snow layer's thickness (m)	*/
	float	ds2,	/* lower  "     "         "     (m)	*/
	float	pa)	/* air pressure (Pa)			*/
{
	float	kcs1;
	float	kcs2;
	float	k_s1;
	float	k_s2;
	float	g;


	//	calculate G
	if (ts1 == ts2)
		g = 0.0;
	else {
		//	set snow conductivity
		kcs1 = KTS(rho1);
		kcs2 = KTS(rho2);
		k_s1 = efcon(kcs1, ts1, pa);
		k_s2 = efcon(kcs2, ts2, pa);

		//	calculate g
		g = ssxfr(k_s1, k_s2, ts1, ts2, ds1, ds2);
	}

	return (g);
}

/*
** NAME
**      void _advec(void) -- calculates advected energy at a point
**
** DESCRIPTION
**      This routine calculates the advected energy for a 2-layer snowcover
**	if there's precipitation for the current timestep.
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_snow
**	precip_now
**	T_rain
**	T_s_0
**	T_snow
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	M
*/

void ClassSnobalBase::_advec(void) {

	if (precip_now) {
		M[hh] = (heat_stor(CP_WATER(T_rain[hh]), m_rain[hh], (T_rain[hh] - T_s_0[hh])) +
			heat_stor(CP_ICE(T_snow[hh]), m_snow[hh], (T_snow[hh] - T_s_0[hh]))) / time_step[hh];
	}
	else
		M[hh] = 0.0;
}

/*
** NAME
**      void _mass_bal(void) -- calculates point mass budget of 2-layer snowcover
**
** DESCRIPTION
**      Calculates the point mass budget for 2-layer energy budget snowmelt
**	model.  It then solves for new snow temperatures.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
*/

void ClassSnobalBase::_mass_bal(void) {

	// process blowing snow event
	//  _drift();

	// adjust mass and calc. runoff

	// age snow by compacting snow due to time passing
	_time_compact();

	// process precipitation event
	_precip();

	// calculate melt or freezing and adjust cold content

	_snowmelt();

	// calculate evaporation and adjust snowpack

	_evap_cond();

	// compact snow due to H2O generated (melt & rain)
	_h2o_compact();

	// calculate runoff, and adjust snowcover */

	_runoff();

	// adjust layer temps if there was a snowcover at start of the
	//   timestep and there's still snow on the ground

	if (snowcover[hh]) {
		if (layer_count[hh] == 1) {
			T_s_0[hh] = new_tsno(m_s_0[hh], T_s_0[hh], cc_s_0[hh]);
			T_s[hh] = T_s_0[hh];
		}
		else if (layer_count[hh] == 2) {
			if (isothermal[hh])
				T_s[hh] = T_s_l[hh] = T_s_0[hh] = FREEZE;
			else {
				T_s_0[hh] = new_tsno(m_s_0[hh], T_s_0[hh], cc_s_0[hh]);
				T_s_l[hh] = new_tsno(m_s_l[hh], T_s_l[hh], cc_s_l[hh]);
				T_s[hh] = new_tsno(m_s[hh], T_s[hh], cc_s[hh]);
			}
		}
	}
}

/*
** NAME
**      void _time_compact(void) -- compact snowcover by gravity over time
**
** DESCRIPTION
**	This routine "ages" the snowcover by accounting for the compaction
**	or densification by gravity as time passes.  The snowcover's
**	density is increased using the following "half-saturation" function:
**
**		rho(time) = A / (1 + B/time)
**
**	A = "saturation-level" or asymtope which is the maximum density
**	    due to compaction by gravity (approximately 350 kg/m^2)
**	B = the point for half of the saturation level is reached (10 days)
**
**			^
**			|
**		 A: 350 + = = = = = = = = = = = = = = = = = =
**		  	|			*   *
**			|		   *
**	rho		|	       *
**	(kg/m^2)	|	    *
**			|	  *
**	       A/2: 175 + . . . *
**      		|     * .
**      		|   *   .
**      		|  * 	.
**      		| * 	.
**      		|*	.
**      	      0 +-------+----------------------------->
**      		0	B: 10 days		time
**
**
** GLOBAL VARIABLES READ
**	time_step
**
** GLOBAL VARIABLES MODIFIED
**	rho
**	(and those variables modified by "_new_density")
**
*/

//  Time when half "saturation", i.e., maximum density is reached * (seconds).
// *  (864000 = 10 days * 24 hours/day * 60 mins/hr * 60 secs/min)

void ClassSnobalBase::_time_compact(void)
{
	const float A = 350; // Maximum density due to compaction by gravity (kg/m^2).
	const float B = 86400;

	float	time;	/* point on time axis corresponding to current density */
					// If the snow is already at or above the maximum density due compaction by gravity, then just leave.

	if (!snowcover[hh] || rho[hh] > A || m_s[hh] <= 0.0)
		return;

	// Given the current density, determine where on the time axis we are (i.e., solve the function above for "time").

	if (rho[hh] > 349)
		rho[hh] = 349;

	time = B / (A / rho[hh] - 1);

	// Move along the time axis by the time step, and calculate the density at this new time.

	rho[hh] = A / (1 + B / (time + time_step[hh]));

	// Adjust the snowcover for this new density.

	_new_density();
}

/*
** NAME
**      void _precip(void) -- process a precipitation event
**
** DESCRIPTION
**      This routine processes a precipitation event, i.e., the current
**	precip record, if there's one for the current timestep.  It
**	determines if the precip is rain or snow which increases the
**	snowcover.
**
** GLOBAL VARIABLES READ
**	h2o_sat_snow
**	m_rain
**	m_precip
**	max_h2o_vol
**	precip_now
**	rho_snow
**	snowcover
**	T_snow
**	z_snow
**
** GLOBAL VARIABLES MODIFIED
**	h2o
**	h2o_sat
**	h2o_total
**	rho
**	T_s
**	T_s_0
**	z_s[hh]
**	(and those variables modified by "_adj_snow" and "_init_snow")
*/

void ClassSnobalBase::_precip(void)
{
	float	h2o_vol_snow;	// liquid water content of new snowfall as volume ratio

	if (precip_now[hh]) {
		if (snowcover[hh]) {

			// Adjust snowcover's depth and mass by snowfall's depth and the total precipitation mass.

			_adj_snow(z_snow[hh], m_precip[hh]);


			// Determine the additional liquid water that's in the snowfall,
			//   and then add its mass to liquid water in the whole snowcover.

			h2o_vol_snow = h2o_sat_snow[hh] * max_h2o_vol[hh];
			h2o[hh] += H2O_LEFT(z_snow[hh], rho_snow[hh], h2o_vol_snow);
		}
		else { // no snowcover

			   // Use snowfall, if any, to setup a new snowcover.

			if (m_snow[hh] > 0.0) {
				z_s[hh] = z_snow[hh];
				rho[hh] = rho_snow[hh];
				T_s[hh] = T_snow[hh];
				T_s_0[hh] = T_snow[hh];
				T_s_l[hh] = T_snow[hh];
				h2o_sat[hh] = h2o_sat_snow[hh];

				init_snow();
			}
		}

		// Add rainfall and water in the snowcover to total liquid water. ???? !!!!

		h2o_total[hh] += m_rain[hh];
		//    ro_predict[hh] += m_rain[hh];
	} // current precip

	  // Add water in the snowcover to total liquid water.
	else // no precip
		h2o_total[hh] += h2o[hh];
}

void ClassSnobalBase::_drift(void)
{
	if (m_drift[hh] - m_subl[hh] == 0.0 || layer_count[hh] == 0)
		return;

	else if (m_drift[hh] - m_subl[hh] > 0.0) { // drift in
		_adj_snow((m_drift[hh] - m_subl[hh]) / rho[hh], m_drift[hh] - m_subl[hh]);
	}
	else { // drift out or sublimation
		_adj_snow((m_drift[hh] - m_subl[hh]) / rho[hh], m_drift[hh] - m_subl[hh]);
	}
}

/*
** NAME
**      void _snowmelt(void) -- calculates melt or re-freezing at a point
**
** DESCRIPTION
**      Calculates melting or re-freezing for point 2-layer energy balance
**      snowmelt model.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**
**	(and those variables modified by "_adj_snow")
*/

void ClassSnobalBase::_snowmelt(void) {

	float  Q_0;            // energy available for surface melt
	float  Q_l;	       // energy available for lower layer melt
	float  Q_freeze;       // energy used for re-freezing
	float  Q_left;         // energy left after re_freezing
	float  h2o_refrozen;   // amount of liquid H2O that was refrozen

						   // If no snow on ground at start of timestep, then just exit.

	if (!snowcover[hh]) {
		melt[hh] = 0.0;
		return;
	}

	// calculate melt or freezing, and adjust cold content

	// calculate surface melt

	// energy for surface melt
	Q_0 = (delta_Q_0[hh] * time_step[hh]) + cc_s_0[hh];

	if (Q_0 > 0.0) {
		melt[hh] = MELT(Q_0);
		cc_s_0[hh] = 0.0;
	}
	else if (Q_0 == 0.0) {
		melt[hh] = 0.0;
		cc_s_0[hh] = 0.0;
	}
	else {
		melt[hh] = 0.0;
		cc_s_0[hh] = Q_0;

		if (m_s[hh] < 2.0) // addition TB 06/03/10
			cc_s_0[hh] = 0.0;
	}


	// calculate lower layer melt

	if (layer_count[hh] == 2) {
		// energy for layer melt
		Q_l = ((G[hh] - G_0[hh]) * time_step[hh]) + cc_s_l[hh];

		if (Q_l > 0.0) {
			melt[hh] += MELT(Q_l);
			cc_s_l[hh] = 0.0;
		}
		else if (Q_l == 0.0)
			cc_s_l[hh] = 0.0;
		else
			cc_s_l[hh] = Q_l;
	}
	else {  // layer_count == 1
		Q_l = 0.0;
	}

	h2o_total[hh] += melt[hh];

	// adjust layers for re-freezing

	// adjust surface layer

	h2o_refrozen = 0.0;

	if (cc_s_0[hh] < 0.0) {
		// if liquid h2o present, calc refreezing and adj cc_s_0
		if (h2o_total[hh] > 0.0) {
			Q_freeze = h2o_total[hh] * (z_s_0[hh] / z_s[hh]) * LH_FUS(FREEZE);
			Q_left = Q_0 + Q_freeze;

			if (Q_left <= 0.0) {
				h2o_refrozen = h2o_total[hh] * (z_s_0[hh] / z_s[hh]);
				cc_s_0[hh] = Q_left;
			}
			else {
				h2o_refrozen = (h2o_total[hh] * (z_s_0[hh] / z_s[hh])) - MELT(Q_left);
				cc_s_0[hh] = 0.0;
			}
		}
	}

	// adjust lower layer for re-freezing

	if ((layer_count[hh] == 2) && (cc_s_l[hh] < 0.0)) {
		// if liquid h2o, calc re-freezing and adj cc_s_l[hh]
		if (h2o_total[hh] > 0.0) {
			Q_freeze = h2o_total[hh] * (z_s_l[hh] / z_s[hh]) * LH_FUS(FREEZE);
			Q_left = Q_l + Q_freeze;

			if (Q_left <= 0.0) {
				h2o_refrozen += h2o_total[hh] * (z_s_l[hh] / z_s[hh]);
				cc_s_l[hh] = Q_left;
			}
			else {
				h2o_refrozen += ((h2o_total[hh] * (z_s_l[hh] / z_s[hh])) - MELT(Q_left));
				cc_s_l[hh] = 0.0;
			}
		}
	}

	// Note:  because of rounding errors, h2o_refrozen may not
	//   be exactly the same as h2o_total.  Check for this case, and if so, then just zero out h2o_total.

	if (fabs(h2o_total[hh] - h2o_refrozen) <= 1e-8) {
		h2o_total[hh] = 0.0;
	}
	else {
		h2o_total[hh] -= h2o_refrozen;
	}

	// determine if snowcover is isothermal

	if ((layer_count[hh] == 2) && (cc_s_0[hh] == 0.0) && (cc_s_l[hh] == 0.0))
		isothermal[hh] = 1;
	else if ((layer_count[hh] == 1) && (cc_s_0[hh] == 0.0))
		isothermal[hh] = 1;
	else
		isothermal[hh] = 0;

	// adjust depth and density for melt

	if (melt[hh] > 0.0) { // !!!
		if (rho[hh] <= 0.0)
			rho[hh] = 750; // Maximum snow density (kg/m^3)

		_adj_snow(-(melt[hh] / rho[hh]), 0.0);
	}

	// set total cold content
	if (layer_count[hh] == 2)
		cc_s[hh] = cc_s_0[hh] + cc_s_l[hh];
	else // (layer_count[hh] == 1)
		cc_s[hh] = cc_s_0[hh];
}

/*
** NAME
**      void _new_density(void) -- adjust the snowcover's depth and layers for new density
**
** DESCRIPTION
**      This routine adjusts the snowcover's depth for a new density.  The
**	layers are also adjusted accordingly.
**
** GLOBAL VARIABLES READ
**	m_s
**	rho
**
** GLOBAL VARIABLES MODIFIED
**	z_s
**
**	(and those variables modified by "_adj_layers")
*/

void ClassSnobalBase::_new_density(void) {

	z_s[hh] = m_s[hh] / rho[hh];

	_adj_layers();
}

/*
** NAME
**      _adj_snow -- adjust the snowcover with changes in depth and/or mass
**
**      void
**	_adj_snow(
**	    float delta_z_s,	|* change in snowcover's depth *|
**	    float delta_m_s)	|* change is snowcover's mass *|
**
** DESCRIPTION
**      This routine adjusts the snowcover for a change in its depth or
**	its mass or both.  The snowcover's density is updated.  If there
**	is a change in the snowcover's depth, the # of layers is recomputed.
**	If there's just a change in the snowcover's mass with no change in
**	its depth, then just the specific masses for the layers are updated.
**
**	The routine ensures that the snowcover's density does NOT exceed
**	a maximum density (currently 750 kg/m^3).  If the adjustments to
**	the snowcover, for some reason, lead to an excessive density, the
**	density is clipped at the maximum, and the depth re-adjusted
**	accordingly.
**
** GLOBAL VARIABLES READ
**
** GLOBAL VARIABLES MODIFIED
**	m_s
**	rho
**	z_s
**
**	(and those variables modified by "_adj_layers" and "_layer_mass")
*/

void ClassSnobalBase::_adj_snow(
	float	delta_z_s,	// change in snowcover's depth
	float	delta_m_s)	// change is snowcover's mass
{

	const float MAX_SNOW_DENSITY = 750; // Maximum snow density (kg/m^3)

										// Update depth, mass, and then recompute density.
	z_s[hh] += delta_z_s;
	m_s[hh] += delta_m_s;

	if (z_s[hh] > 0.0)
		rho[hh] = m_s[hh] / z_s[hh];
	else {
		z_s[hh] = 0.0;
		m_s[hh] = 0.0;
	}

	// Clip density at maxium density if necessary.
	if (rho[hh] > MAX_SNOW_DENSITY) {
		rho[hh] = MAX_SNOW_DENSITY;
		z_s[hh] = m_s[hh] / rho[hh];
		_adj_layers();
	}
	// If a change in depth, adjust the layers' depths and masses.
	else {
		if (delta_z_s != 0.0)
			_adj_layers();
		else
			// Just a change in the snowcover's mass, so update the layers' masses.
			_layer_mass();
	}
}

/*
** NAME
**      void _evap_cond(void) -- calculates evaporation/condensation at a point
**
** DESCRIPTION
**      Calculates mass lost or gained by evaporation/condensation
**      at a point for 2-layer energy balance snowmelt model snobal.c;
**      Also adjusts the liq h2o, mass and depth of the snow layer;
**      Assumes that liq h2o is favored in evap as the ratio of
**      vaporization to sublimation (0.882); Half the ice lost as evap
**      is assumed to be lost depth; the rest reduces the density;
**
** GLOBAL VARIABLES READ
**	E
**	layer_count
**	P_a
**	rho
**	T_g
**	T_s_l
**	T_s_0
**	time_step
**	z_g
**
** GLOBAL VARIABLES MODIFIED
**	E_s h2o_total
**
**	(and those variables modified by "_adj_snow")
*/

#define VAP_SUB (2.501 / 2.835) // ratio vaporization to sublimatin

void ClassSnobalBase::_evap_cond(void) {

	//        float  E_s_0;          // mass of evaporation to air (kg/m^2)
	//        float  E_s_l;          // mass of evaporation to soil (kg/m^2)
	float  E_l;	       // mass flux by evap/cond to soil (kg/m^2/s)
	float  e_g;            // soil vapor press
	float  e_s_l;          // lower snow layer's vapor press
	float  k;              // soil diffusion coef
	float  prev_h2o_tot;   // previous value of h2o_total variable
	float  q_delta;        // difference between snow & soil spec hum's
	float  q_g;            // soil spec hum
	float  q_s_l;          // lower snow layer's spec hum
	float  rho_air;        // air density
	float  T_bar;          // snow-soil mean temp

						   // calculate evaporation or condensation

						   // If no snow on ground at start of timestep, then just exit.

	if (!snowcover[hh]) {
		E_s[hh] = 0.0;
		return;
	}

	// Total mass change due to evap/cond at surface during timestep

	E_s_0[hh] = E[hh] * time_step[hh];

	//  Adjust total h2o for evaporative losses

	prev_h2o_tot = h2o_total[hh];

	if (h2o_total[hh] > 0.0) {
		h2o_total[hh] += (E_s_0[hh] * VAP_SUB);
		if (h2o_total[hh] <= 0.0)
			h2o_total[hh] = 0.0;
	}

	// Determine total mass change due to evap/cond at soil

	if (layer_count[hh] == 0)
		E_s_l[hh] = 0.0;
	else {
		if (layer_count[hh] == 2) {
			e_s_l = sati(T_s_l[hh]);
			T_bar = (T_g[hh] + T_s_l[hh]) / 2.0;
		}
		else {  /* layer_count == 1 */
			e_s_l = sati(T_s_0[hh]);
			T_bar = (T_g[hh] + T_s_0[hh]) / 2.0;
		}

		q_s_l = SPEC_HUM(e_s_l, P_a[hh]);
		e_g = sati(T_g[hh]);
		q_g = SPEC_HUM(e_g, P_a[hh]);
		q_delta = q_g - q_s_l;
		rho_air = GAS_DEN(P_a[hh], MOL_AIR, T_bar);
		k = DIFFUS(P_a[hh], T_bar);

		E_l = EVAP(rho_air, k, q_delta, z_g[hh]);

		/* total mass of evap/cond for time step */
		E_s_l[hh] = E_l * time_step[hh];

		/** adjust h2o_total for evaporative losses **/
		if (h2o_total[hh] > 0.0) {
			h2o_total[hh] += (E_s_l[hh] * VAP_SUB);
			if (h2o_total[hh] <= 0.0)
				h2o_total[hh] = 0.0;
		}
	}

	E_s[hh] = E_s_0[hh] + E_s_l[hh];

	//      adj mass and depth for evap/cond

	if (layer_count[hh] > 0)
		_adj_snow(((E_s[hh] + (prev_h2o_tot - h2o_total[hh])) / rho[hh]) / 2.0, E_s[hh]);
}

/*
** NAME
**      void _h2o_compact(void) -- compact snowcover due to liquid H2O that was added
**
** DESCRIPTION
**	This routine compacts or densifies the snowcover based on the
**	amount of liquid H2O that was added to the snowcover from melting
**	and rain.  The snowcover's density is increased using the
**	following "half-saturation" function:
**
**		delta_rho(h2o_added) = A / (1 + B/h2o_added)
**
**	A = "saturation-level" or asymtope which is the difference between
**	    the maximum density due to compaction by liquid H2O
**	    (approximately 550 kg/m^2) and the current density
**	B = the point for half of the saturation level is reached (5 %)
**	    (h2o_added = ratio of mass of liquid h2o added by melting and
**		         rain to the mass of the snowcover)
**
**			^
**			|
**		      A + = = = = = = = = = = = = = = = = = =
**	(550 - current  |			*   *
**	       density)	|		   *
**			|	       *
**	delta_rho	|	    *
**	(kg/m^2)	|	  *
**	            A/2 + . . . *
**      		|     * .
**      		|   *   .
**      		|  * 	.
**      		| * 	.
**      		|*	.
**      	      0 +-------+-----------------------------+	  h2o_added
**      		0	B: 5 %			     1.0
**
**
** GLOBAL VARIABLES READ
**	m_rain
**	m_s
**	melt
**
** GLOBAL VARIABLES MODIFIED
**	rho
**
**	(and those variables modified by "_new_density")
*/

#define	MAX_DENSITY  550
/*
*  Maximum density due to compaction by liquid H2O added (kg/m^2).
*/

#define	BB	0.4 // changed from 0.05

// ratio where half the difference between maximum density and
//   current density is reached (ratio from 0.0 to 1.0).

void ClassSnobalBase::_h2o_compact(void)
{

	float Alocal;         // difference between maximum & currentdensities

	float	h2o_added;	// ratio of mass of liquid H2O added from melting and rain to mass of snowcover

						// If the snow is already at or above the maximum density due compaction by liquid H2O, then just leave.

	if ((!snowcover[hh]) || (rho[hh] > MAX_DENSITY))
		return;

	Alocal = MAX_DENSITY - rho[hh];

	if (m_s[hh]) {  // !!! fudge
		if (precip_now[hh])
			h2o_added = (melt[hh] + m_rain[hh]) / m_s[hh];
		else
			h2o_added = melt[hh] / m_s[hh];

		if (h2o_added > 0.000001) {
			rho[hh] += Alocal / (1 + BB / h2o_added);
			_new_density(); // Adjust the snowcover for this new density.
		}
	}
}

void ClassSnobalBase::_adj_layers(void) {

	/*
	** NAME
	**      _adj_layers -- adjust the layers because of new snowcover depth
	**
	** SYNOPSIS
	**      #include "_snobal.h"
	**
	**      void
	**	_adj_layers(void);
	**
	** DESCRIPTION
	**      This routine adjusts the layers of the snowcover because the
	**	snowcover's depth has changed.  It is assumed that the snowcover's
	**	density has already been updated.  The # of layers are recomputed
	**	based on the overall snowcover depth.  Their depths and masses
	**	are updated as well.  If a layer has been created due to an
	**	increase in the snowcover's depth, its temperature and cold content
	**	are initialized.
	**
	** GLOBAL VARIABLES READ
	**	layer_count
	**
	** GLOBAL VARIABLES MODIFIED
	**	cc_s
	**	cc_s_0
	**	cc_s_l
	**	h2o
	**	h2o_max
	**	h2o_total
	**	h2o_vol
	**	m_s
	**	m_s_0
	**	m_s_l
	**	rho
	**	T_s
	**	T_s_0
	**	T_s_l
	**
	**	(and those variables modified by "_calc_layer" and "_layer_mass")
	*/

	/*
	*  Recompute then number of layers and see if there's been
	*  a change in the # of layers.  Note:  since this routine
	*  is called to adjust an existing snowcover, the current # of
	*  layers must be either 1 or 2 while the new # of layers may
	*  either be 0, 1 or 2.
	*
	*	current #	new #
	*	of layers	of layers
	*
	*	   1	   -->	   0
	*	   1	   -->	   1	(no change)
	*	   1	   -->	   2
	*	   2	   -->	   0
	*	   2	   -->	   1
	*	   2	   -->	   2	(no change)
	*/
	int prev_layer_count;	// previous # of layers, if change in depth
	prev_layer_count = layer_count[hh];  // must be > 0
	_calc_layers();

	if (layer_count[hh] == 0) {

		// 1 or 2 layers --> 0 layers

		rho[hh] = 218.0; // 10/18/16

						 // If mass > 0, then it must be below threshold. So turn this little bit of mass into water.

		if (m_s[hh] > 0.0) {
			snowmelt_int[hh] += m_s[hh];
			melt_direct_int[hh] += m_s[hh];
		}

		m_s[hh] = cc_s[hh] = 0.0;
		m_s_0[hh] = cc_s_0[hh] = 0.0;

		// Note: Snow temperatures are set to MIN_SNOW_TEMP (as degrees K) instead of 0 K to keep quantization range in output image smaller.

		T_s[hh] = T_s_0[hh] = MIN_SNOW_TEMP + FREEZE;

		if (prev_layer_count == 2) {
			m_s_l[hh] = cc_s_l[hh] = 0.0;
			T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
		}
		h2o_vol[hh] = h2o[hh] = h2o_max[hh] = h2o_sat[hh] = 0.0;
	}

	else {
		_layer_mass();

		if ((prev_layer_count == 1) && (layer_count[hh] == 2)) {

			// 1 layer --> 2 layers, add lower layer

			T_s_l[hh] = T_s[hh];
			cc_s_l[hh] = _cold_content(T_s_l[hh], m_s_l[hh]);
		}

		else if ((prev_layer_count == 2) && (layer_count[hh] == 1)) {

			// 2 layers --> 1 layer, remove lower layer

			T_s_l[hh] = MIN_SNOW_TEMP + FREEZE;
			cc_s_l[hh] = 0.0;
		}
	}
}

/*
** NAME
**      void _runoff(void) -- calculates runoff from snowcover
**
** DESCRIPTION
**      Calculates runoff for point energy budget 2-layer snowmelt model
**
** GLOBAL VARIABLES READ
**	h2o_total
**	layer_count
**	snowcover
**	max_h2o_vol
**	z_s
**
** GLOBAL VARIABLES MODIFIED
**	h2o
**	h2o_max
**	h2o_sat
**	h2o_vol
**	rho
**	ro_predict
*/

void ClassSnobalBase::_runoff(void) {

	float	m_s_dry;	/* snowcover's mass without liquid H2O */
	float	rho_dry;	/* snow density without liquid H2O */

						// calculate runoff

						// If no snow on ground at start of timestep or no layers currently, then all water (e.g., rain) is runoff.

	if ((!snowcover[hh]) || (layer_count[hh] == 0)) {
		ro_predict[hh] = h2o_total[hh];
		return;
	}

	//  Determine the snow density without any water, and the maximum liquid water the snow can hold.

	m_s_dry = m_s[hh] - h2o_total[hh];
	rho_dry = m_s_dry / z_s[hh];
	h2o_max[hh] = H2O_LEFT(z_s[hh], rho_dry, max_h2o_vol[hh]);

	// Determine runoff, and water left in the snow

	if (h2o_total[hh] > h2o_max[hh]) {
		ro_predict[hh] = h2o_total[hh] - h2o_max[hh];
		h2o[hh] = h2o_max[hh];
		h2o_sat[hh] = 1.0;
		h2o_vol[hh] = max_h2o_vol[hh];

		//  Update the snowcover's mass for the loss of runoff.

		_adj_snow(0.0, -ro_predict[hh]);
	}
	else {
		ro_predict[hh] = 0.0;
		h2o[hh] = h2o_total[hh];
		h2o_sat[hh] = h2o[hh] / h2o_max[hh];
		h2o_vol[hh] = h2o_sat[hh] * max_h2o_vol[hh];
	}
}
/* ----------------------------------------------------------------------- */

float satw(
	float  tk) {		/* air temperature (K)		*/

	double  x;
	double  l10;

	if (tk <= 0.) {
		CRHMException TExcept("satw temperature <= 0.0", TERMINATE);
		LogError(TExcept);
	}

	errno = 0;
	l10 = log(1.e1);

	x = -7.90298*(BOIL / tk - 1.0f) + 5.02808f*log(BOIL / tk) / l10 -
		1.3816e-7*(pow(1.0e1, 1.1344e1f*(1.0 - tk / BOIL)) - 1.0f) +
		8.1328e-3*(pow(1.0e1, -3.49149f*(BOIL / tk - 1.0f)) - 1.0f) +
		log(SEA_LEVEL) / l10;

	x = pow(1.0e1f, x);

	if (errno) {
		CRHMException TExcept("satw: bad return from log or pow", TERMINATE);
		LogError(TExcept);
	}

	return(x);
}
/* ----------------------------------------------------------------------- */

float ClassSnobalBase::sati(float  tk) { //* air temperature (K)

	double  l10;
	double  x;

	if (tk <= 0.0) {
		CRHMException TExcept("sati temperature <= 0.0", TERMINATE);
		LogError(TExcept);
		//            tk = FREEZE + 0.01;
	}

	if (tk > FREEZE) {
		x = satw(tk);
		return(x);
	}

	errno = 0;
	l10 = log(1.e1);

	x = pow(1.e1, -9.09718*((FREEZE / tk) - 1.0) - 3.56654*log(FREEZE / tk) / l10 +
		8.76793e-1*(1.0 - (tk / FREEZE)) + log(6.1071) / l10);

	if (errno) {
		CRHMException TExcept("sati: bad return from log or pow", TERMINATE);
		LogError(TExcept);
	}

	return(x*1.e2);
}
/* ----------------------------------------------------------------------- */

float ClassSnobalBase::ssxfr(
	float	k1,	/* layer 1's thermal conductivity (J / (m K sec))  */
	float	k2,	/* layer 2's    "         "                        */
	float	t1,	/* layer 1's average layer temperature (K)	   */
	float	t2,	/* layer 2's    "      "        "         	   */
	float	d1,     /* layer 1's thickness (m)			   */
	float	d2)     /* layer 2's    "       "			   */
{
	float	xfr;

	xfr = 2.0 * (k1 * k2 * (t2 - t1)) / ((k2 * d1) + (k1 * d2));

	return (xfr);
}
/* ----------------------------------------------------------------------- */

float ClassSnobalBase::heat_stor(
	float	cp,	/* specific heat of layer (J/kg K) */
	float	spm,	/* layer specific mass (kg/m^2)    */
	float	tdif)	/* temperature change (K)          */
{
	float	stor;

	stor = cp * spm * tdif;

	return (stor);
}
/* ----------------------------------------------------------------------- */

float ClassSnobalBase::new_tsno(
	float	spm,	/* layer's specific mass (kg/m^2) 	 */
	float	t0,	/* layer's last temperature (K) 	 */
	float	ccon)	/* layer's adjusted cold content (J/m^2) */
{
	float	tsno;
	float	cp;
	float	tdif;

	cp = CP_ICE(t0);

	tdif = ccon / (spm * cp);
	tsno = tdif + FREEZE;

	if (tsno < MIN_SNOW_TEMP + FREEZE)
		tsno = MIN_SNOW_TEMP + FREEZE;
	else {
		if (tsno > CRHM_constants::Tm)
			tsno = CRHM_constants::Tm;
	}

	return (tsno);
}
/* ----------------------------------------------------------------------- */

float ClassSnobalBase::efcon(
	float	k,	/* layer thermal conductivity (J/(m K sec)) */
	float	t,	/* layer temperature (K)		    */
	float	p)	/* air pressure (Pa)  			    */
{
	double	etc;
	double	de;
	double	lh;
	double	e;
	double	q;

	// calculate effective layer diffusion(see Anderson, 1976, pg. 32)
	de = DIFFUS(p, t);

	// set latent heat from layer temp.
	if (t > FREEZE)
		lh = LH_VAP(t);
	else if (t == FREEZE)
		lh = (LH_VAP(t) + LH_SUB(t)) / 2.0;
	else
		lh = LH_SUB(t);

	// set mixing ratio from layer temp.
	e = sati(t);
	q = MIX_RATIO(e, p);

	//	calculate effective layer conductivity
	etc = k + (lh * de * q);

	return (etc);
}
// -----------------------------------------------------------------------

#define AH		1.0	// ratio sensible/momentum phi func
#define AV		1.0	// ratio latent/momentum phi func
#define ITMAX		50	// max # iterations allowed
#define PAESCHKE	7.35	// Paeschke's const (eq. 5.3)
#define THRESH		1.e-5	// convergence threshold

#define SM		0
#define SH		1
#define SV		2
#define BETA_S		5.2
#define BETA_U		16

// psi-functions
//	code =	SM	momentum
//		SH	sensible heat flux
//		SV	latent heat flux

static double
psi(double zeta,		// z/lo
	int	code)		// which psi function? (see above)
{
	double	x;		// height function variable
	double	result;

	if (zeta > 0) {		// stable
		if (zeta > 1)
			zeta = 1;
		result = -BETA_S * zeta;
	}
	else if (zeta < 0) {	// unstable
		x = sqrt(sqrt(1.0 - BETA_U * zeta));

		switch (code) {
		case SM:
			result = 2.0 * log((1.0 + x) / 2.0) + log((1.0 + x * x) / 2.0) -
				2.0 * atan(x) + M_PI_2;
			break;

		case SH:
		case SV:
			result = 2.0 * log((1.0 + x * x) / 2.0);
			break;

		default: // shouldn't reach
			CRHMException TExcept("psi-function code not of these: SM, SH, SV", TERMINATE);
			LogError(TExcept);
		}
	}

	else {			/* neutral */
		result = 0;
	}

	return (result);
}
/* ----------------------------------------------------------------------- */

int ClassSnobalBase::hle1(
	float	press,	// aiFr pressure (Pa)
	float	ta,	// air temperature (K) at height za
	float	ts,	// surface temperature (K)
	float	za,	// height of air temp measurement (m)
	float	ea,	// vapor pressure (Pa) at height zq
	float	es,	// vapor pressure (Pa) at surface
	float	zq,	// height of spec hum measurement (m)
	float	u,	// wind speed (m/s) at height zu
	float	zu,	// height of wind speed measurement (m)
	float	z0,	// roughness length (m)

				// output variables

	float &CRHM_h,	// sens heat flux (+ to surf) (W/m^2)
	float &CRHM_le,	// latent heat flux (+ to surf) (W/m^2)
	float &CRHM_e)	// mass flux (+ to surf) (kg/m^2/s)
{
	double h = 0.00;	// sens heat flux (+ to surf) (W/m^2)
	double e = 0.00;	// mass flux (+ to surf) (kg/m^2/s)

	double	ah = AH;
	double	av = AV;
	double	cp = CP_AIR;
	double	d0;	// displacement height (eq. 5.3)
	double	dens;	// air density
	double	diff;	// difference between guesses
	double	factor;
	double	g = GRAVITY;
	double	k = VON_KARMAN;
	double	last;	// last guess at lo
	double	lo;	// Obukhov stability length (eq. 4.25)
	double	ltsh;	// log ((za-d0)/z0)
	double	ltsm;	// log ((zu-d0)/z0)
	double	ltsv;	// log ((zq-d0)/z0)
	double	qa;	// specific humidity at height zq
	double	qs;	// specific humidity at surface
	double  	ustar;	// friction velocity (eq. 4.34')
	double	xlh = 0.00;	// latent heat of vap/subl
	int	ier = 0;	// return error code
	int	iter = 0;	// iteration counter

					/*static TDateTime LastDTnow;*/

					// check for bad input

					// heights must be positive
	if (z0 <= 0 || zq <= z0 || zu <= z0 || za <= z0) {
	 string D = getTimeGG() + "hle1: height not positive ";
	 string SS = D + "hru " + std::to_string(hh + 1);			//use Convert() function for "hh + 1" ???
		SS = SS + "  ta: " + Convert(ta - CRHM_constants::Tm) +
			", z0: " + Convert(z0) +
			", zq: " + Convert(zq) +
			", zu: " + Convert(zu) +
			", za: " + Convert(za);

		CRHMException TExcept(SS.c_str(), WARNING);
		LogError(TExcept);
		ier = -2;
		return (ier);
	}

	// temperatures are Kelvin
	if (ta <= 0 || ts <= 0) {
		CRHMException TExcept("temps not K", TERMINATE);
		LogError(TExcept);
		ier = -2;
		return (ier);
	}

	// pressures must be positive
	if (ea <= 0 || es <= 0 || press <= 0 || ea >= press || es >= press) {

	 string D = getTimeGG();
	 string SS = D + "hh " + Convert(hh) + " 'hle1' " + ". H: " + Convert(h) + " le: " + Convert(xlh * e);
		SS = SS + " ta: " + Convert(ta - CRHM_constants::Tm) +
			", ts: " + Convert(ts - CRHM_constants::Tm) +
			", ea: " + Convert(ea) +
			", es: " + Convert(es) +
			", u:  " + Convert(u) +
			", m_s:  " + Convert(m_s[hh]);

		CRHM_le = 0.0; // addition TB 09/23/14
		CRHM_h = 0.0;
		CRHM_e = 0.0;

		CRHMException TExcept2(SS.c_str(), WARNING);
		LogError(TExcept2);

		CRHMException TExcept("hle1: pressures must be positive", TERMINATE);
		LogError(TExcept);

		ier = -2;
		return (ier);
	}

	// vapor pressures can't exceed saturation if way off stop
	if ((es - 25.0) > sati(ts) || (ea - 25.0) > satw(ta)) {
		CRHMException TExcept("hle1: vapor pressures can't exceed saturation", TERMINATE);
		LogError(TExcept);
		ier = -2;
		return (ier);
	}
	// else fix them up
	if (es > sati(ts)) {
		es = sati(ts);
	}
	if (ea > satw(ta)) {
		ea = satw(ta);
	}

	if (u < 0.5)
		u = 0.5;
	else if (u > 15)
		u = 15;
	// displacement plane height, eq. 5.3 & 5.4

	d0 = 2.0 * PAESCHKE * z0 / 3.0;

	// constant log expressions

	ltsm = log((zu - d0) / z0);
	ltsh = log((za - d0) / z0);
	ltsv = log((zq - d0) / z0);

	// convert vapor pressures to specific humidities

	qa = SPEC_HUM(ea, press);
	qs = SPEC_HUM(es, press);

	// convert temperature to potential temperature

	ta += DALR * za;

	// air density at press, virtual temp of geometric mean of air and surface

	dens = GAS_DEN(press, MOL_AIR, VIR_TEMP(sqrt(ta*ts), sqrt(ea*es), press));

	// starting value, assume neutral stability, so psi-functions are all zero

	ustar = k * u / ltsm;
	factor = k * ustar * dens;
	e = (qa - qs) * factor * av / ltsv;
	h = (ta - ts) * factor * cp * ah / ltsh;

	// if not neutral stability, iterate on Obukhov stability length to find solution

	if (ta != ts) {
		lo = HUGE_VAL;

		do {
			last = lo;

			// Eq 4.25, but no minus sign as we define positive H as toward surface

			// There was an error in the old version of this line that omitted the cubic power of ustar. Now, this error has been fixed.

			lo = ustar * ustar * ustar * dens / (k * g * (h / (ta*cp) + 0.61 * e));

			// friction velocity, eq. 4.34'

			ustar = k * u / (ltsm - psi(zu / lo, SM));

			// evaporative flux, eq. 4.33'

			factor = k * ustar * dens;
			e = (qa - qs) * factor * av / (ltsv - psi(zq / lo, SV));

			// sensible heat flux, eq. 4.35' with sign reversed

			h = (ta - ts) * factor * ah * cp / (ltsh - psi(za / lo, SH));

			diff = last - lo;

		} while (fabs(diff) > THRESH && fabs(diff / lo) > THRESH && ++iter < ITMAX);
	}

	xlh = LH_VAP(ts);
	if (ts <= FREEZE)
		xlh += LH_FUS(ts);

	// latent heat flux (- away from surf)

	CRHM_le = xlh * e;
	CRHM_h = h;
	CRHM_e = e;


	if (iter >= ITMAX) {
		CRHM_le = 0.0; // addition TB 06/03/10
		CRHM_h = 0.0;
		CRHM_e = 0.0;

	 string Flag = "iters" + std::to_string(iter);
		/*LastDTnow = Global::DTnow;*/

	 string D = getTimeGG();
	 string SS = D + "hh " + Convert(hh) + " 'hle1' " + Flag + ". H: " + Convert(h) + " le: " + Convert(xlh * e);
		SS = SS + " ta: " + Convert(ta - CRHM_constants::Tm) +
			", ts: " + Convert(ts - CRHM_constants::Tm) +
			", ea: " + Convert(ea) +
			", es: " + Convert(es) +
			", u:  " + Convert(u) +
			", m_s:  " + Convert(m_s[hh]);
		CRHMException TExcept2(SS.c_str(), WARNING);
		LogError(TExcept2);

		ier = -1;
	}

	//  ier_array[ArrayCnt[hh]][hh] = ier;
	//  e_array[ArrayCnt[hh]][hh] = e;
	//  h_array[ArrayCnt[hh]][hh] = h;
	//  Length_array[ArrayCnt[hh]][hh] = lo;
	//  Ustar_array[ArrayCnt[hh]++][hh] = ustar;

	return (ier);
}
/* ----------------------------------------------------------------------- */

ClasspbsmSnobal* ClasspbsmSnobal::klone(string name) const {
	return new ClasspbsmSnobal(name);
}

void ClasspbsmSnobal::decl(void) {

	Description = "'Special \"pbsm\" module compatible with \"snobal\".' \
                 'original version using hru_u,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u,' \
                 'using hru_u and a regression to use daily windspeed,' \
                 'uses hru_Uadjust from walmsley_wind instead of hru_u and a regression to use daily windspeed.'";

	variation_set = VARIATION_0 + VARIATION_2;

	declgetvar("*", "hru_u", "(m/s)", &hru_u);


	variation_set = VARIATION_1 + VARIATION_3;

	declgetvar("*", "hru_Uadjust", "(m/s)", &hru_Uadjust);


	variation_set = VARIATION_2 + VARIATION_3;

	declparam("u_D", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed correction", "()", &u_D);

	declparam("Drift_offset", NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed drift offset correction", "()", &Drift_offset);

	declparam("Drift_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed drift slope correction", "()", &Drift_slope);

	declparam("Subl_offset", NHRU, "[0.0]", "-100.0", "100.0", "Daily windspeed sublimation offset correction", "()", &Subl_offset);

	declparam("Subl_slope", NHRU, "[1.0]", "0.5", "2.0", "Daily windspeed sublimation slope correction", "()", &Subl_slope);


	variation_set = VARIATION_ORG;

	declvar("hru_subl", NHRU, "interval sublimation", "(mm/int)", &Subl);

	declvar("hru_drift", NHRU, "interval composite transport", "(mm/int)", &Drift);

	decldiag("DriftH", NHRU, "interval transport", "(mm/int)", &DriftH);

	decldiag("SublH", NHRU, "interval sublimation", "(mm/int)", &SublH);

	declvar("Drift_out", NHRU, "interval transport out", "(mm/int)", &Drift_out);

	declvar("Drift_in", NHRU, "interval transport in", "(mm/int)", &Drift_in);

	declvar("BasinSnowLoss", BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

	declstatdiag("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

	declstatdiag("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

	declstatdiag("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

	declstatdiag("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

	declstatdiag("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

	decllocal("hru_basin", NHRU, "conversion factor", "()", &hru_basin);

	decldiag("DrySnow", NHRU, "DrySnow", "()", &DrySnow);

	declstatdiag("SnowAge", NHRU, "SnowAge", "()", &SnowAge);

	decldiag("Prob", NHRU, "Probability", "()", &Prob);

	decldiag("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

	/* parameters */

	declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	declparam("distrib", NHRU, "[0.0, 1.0]", "-10.0", "10.0", "distribution fractions - can sum to 1", "()", &distrib);

	decldiagparam("N_S", NHRU, "[320]", "1", "500", "vegetation number density", "(1/m^2)", &N_S);

	decldiagparam("A_S", NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("inhibit_bs", NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

	decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

	declputvar("*", "SWE", "(kg/m^2)", &SWE);
	declputvar("*", "z_s", "(m)", &z_s);
	declputvar("*", "rho", "(kg/m^3)", &rho);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void ClasspbsmSnobal::init(void) {

	nhru = getdim(NHRU);

	cumBasinSnowLoss[0] = 0.0;
	cumBasinSnowGain[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		SWE[hh] = 0.0;
		cumDrift[hh] = 0.0;
		cumDriftIn[hh] = 0.0;
		cumSubl[hh] = 0.0;
		SnowAge[hh] = 0.0;
		DrySnow[hh] = 0;
		snowdepth[hh] = 0.0;

		if ((hh > 0) && (Ht[hh] < Ht[hh - 1]) && distrib[hh - 1] > 0) {
			CRHMException TExcept(string("'" + Name + " (pbsmSnobal)' vegetation heights not in ascending order.").c_str(), WARNING);
			LogError(TExcept);
		}
	}

	for (hh = 0; hh < nhru; ++hh)
		hru_basin[hh] = hru_area[hh] / basin_area[0];
}

void ClasspbsmSnobal::run(void) {

	float Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
	float SumDrift, total, SWE_Max, transport;

	for (hh = 0; chkStruct(); ++hh) {

		if (variation == VARIATION_ORG || variation == VARIATION_2)
			hru_u_ = hru_u[hh];
		else
			hru_u_ = hru_Uadjust[hh];

		if (variation == VARIATION_2 || variation == VARIATION_3)
			hru_u_ = u_D[hh] * hru_u_;

		Drift_out[hh] = 0.0;
		Drift_in[hh] = 0.0;
		Drift[hh] = 0.0;

		Subl[hh] = 0.0;
		Prob[hh] = 0.0;

		if (SWE[hh] > 0.0 && !inhibit_bs[hh]) {

			E_StubHt = Ht[hh] - z_s[hh];                      // depths(m)
			if (E_StubHt < 0.0001) E_StubHt = 0.0001;

			Ustar = 0.02264*pow(hru_u_, 1.295f);            // Eq. 6.2 rev.,  Ustar over fallow

			if (E_StubHt > 0.01) {
				Znod = (sqr(Ustar) / 163.3f) + 0.5*N_S[hh] * E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
				Lambda = N_S[hh] * A_S[hh] * E_StubHt;                      // Raupach Eq. 1

				Ustn = Ustar * sqrt((PBSM_constants::Beta*Lambda) / (1.0 + PBSM_constants::Beta*Lambda));

				Uten_Prob = (log(10.0 / Znod)) / PBSM_constants::KARMAN *sqrt(Ustar - Ustn);
			}
			else
			{
				Uten_Prob = hru_u_;
			} // end if

			bool newsnow = net_snow[hh];

			ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, newsnow, SnowAge[hh], DrySnow[hh]);  // (mm)

			if (Prob[hh] > 0.001) {
				Ut = Ut * 0.8;

				float RH = hru_ea[hh] / Common::estar(hru_t[hh]); // Snobal uses Pascals

				Pbsm(E_StubHt, Ut, DriftH[hh], SublH[hh], hru_t[hh], hru_u_, RH, fetch[hh], N_S[hh], A_S[hh]);

				if (variation == VARIATION_2 || variation == VARIATION_3) {
					DriftH[hh] = Drift_offset[hh] + DriftH[hh] * Drift_slope[hh];
					SublH[hh] = Subl_offset[hh] + SublH[hh] * Subl_slope[hh];
				}

				Drift_out[hh] = DriftH[hh] * Prob[hh] / fetch[hh];

				if (!inhibit_subl[hh])
					Subl[hh] = SublH[hh] * Prob[hh];

				// handle insufficient snow pack

				if (Drift_out[hh] + Subl[hh] > SWE[hh]) {
					if (Drift_out[hh] >= SWE[hh]) {
						Drift_out[hh] = SWE[hh];
						Subl[hh] = 0.0;
					}
					else
						Subl[hh] = SWE[hh] - Drift_out[hh];
				}

				cumDrift[hh] += Drift_out[hh];
				cumSubl[hh] += Subl[hh];
			}
		} // end if
	} // end for (hh)

	  // distribute drift

	if (distrib[0] > 0.0) { // simulate transport entering basin using HRU 1
		float Drft = Drift_out[0] * distrib[0];
		SWE[0] += Drft;
		cumDriftIn[0] += Drft;
		cumBasinSnowGain[0] += Drft * hru_basin[0];  // **** hru_basin = hru_area/basin_area ****
	}

	BasinSnowLoss[0] = 0.0;
	long LastN = 0;

	if (!inhibit_bs[0] && nhru == 1) {
		BasinSnowLoss[0] = Drift_out[0];
		cumBasinSnowLoss[0] += BasinSnowLoss[0];
	}

	for (long nn = LastN; chkStruct(nn); ++nn) {
		if (distrib[nn] >= 0.0 && nn + 1 < nhru) // skip till last HRU or -ve distribution
			continue;

		SumDrift = 0.0;
		for (long hhh = LastN; chkStruct(hhh, nn); ++hhh) // sum drift over range
			SumDrift += Drift_out[hhh] * hru_basin[hhh];

		if (SumDrift > 0.0) { // drift has occurred!
			for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {

				if (Ht[hh] > z_s[hh])
					SWE_Max = SWE[hh] + rho[hh] * (Ht[hh] - z_s[hh]); // not filled
				else
					SWE_Max = SWE[hh]; // filled or over filled. Wait for snow transport

				if (SWE_Max <= 0.0)
					SWE_Max = Ht[hh];

				if (hh == nn) { // handle last HRU
					if (distrib[nn] > 0) {
						float In = SumDrift / hru_basin[hh]; // remaining drift
						if (SWE_Max > SWE[hh] + In) { // fill snowpack, remainder leaves basin
							Drift_in[hh] = In; // can handle all
							cumDriftIn[hh] += Drift_in[hh];
							transport = 0.0;
						}
						else if (SWE_Max > SWE[hh]) { // cannot handle all
							Drift_in[hh] = SWE_Max - SWE[hh];
							cumDriftIn[hh] += Drift_in[hh];
							transport -= (In - (SWE_Max - SWE[hh]))*hru_basin[hh];
						}
						else // zero or -ve - happens during melt??
							transport = SumDrift;
					}
					else if (distrib[nn] < 0) { // all drift deposited
						Drift_in[hh] = SumDrift / hru_basin[hh]; // can handle all
						cumDriftIn[hh] += Drift_in[hh];
						transport = 0.0;
					}
					else // distrib[nn] == 0 -> all excess drift leaves basin
						transport = SumDrift;

					BasinSnowLoss[0] += (transport + Drift_out[hh] * hru_basin[hh]);
					cumBasinSnowLoss[0] += (transport + Drift_out[hh] * hru_basin[hh]);
				}
				else if (SWE_Max > SWE[hh] && distrib[hh] > 0.0) {
					// handle intermediate HRUs with available storage and distrib > 0
					total = 0.0;
					for (long jj = hh; chkStruct(jj, nn + 1); jj++) // calculate denominator
						total += fabs(distrib[jj]);
					// determine contribution and scale
					transport = SumDrift * fabs(distrib[hh]) / total / hru_basin[hh];
					if (SWE_Max > SWE[hh] + transport) // sufficient capacity
						Drift_in[hh] += transport;
					else if (SWE_Max > SWE[hh]) {
						transport = SWE_Max - SWE[hh];  // insufficient capacity
						Drift_in[hh] += transport;
					}
					else
						transport = 0.0;

					SumDrift -= transport * hru_basin[hh]; // remove drift used from total available
					cumDriftIn[hh] += transport;
				} // end if
			} // end for (hh)
			LastN = nn + 1;
		} // end if
	} // end for (nn)

	for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation
		Drift[hh] = Drift_in[hh] - Drift_out[hh];
		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0.0;
		}
	} // end for (hh)
}

void ClasspbsmSnobal::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsmSnobal)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}

	LogMessage("'pbsmSnobal' cumBasinSnowLoss (mm): ", cumBasinSnowLoss[0]); //
	LogMessage("'pbsmSnobal' cumBasinSnowGain (mm): ", cumBasinSnowGain[0]); //
	LogDebug(" ");
}
//==============================================================================

ClassalbedoRichard* ClassalbedoRichard::klone(string name) const {
	return new ClassalbedoRichard(name);
}

void ClassalbedoRichard::decl(void) {

	Description = "'Calculates snow cover albedo from a method proposed by R.Essery.'";

	declstatvar("Albedo", NHRU, "Albedo", "()", &Albedo);

	decldiagparam("Albedo_Snow", NHRU, "[0.85]", "0.0", "1.0", "Initial albedo for snow cover", "()", &Albedo_Snow);

	decldiagparam("Albedo_Bare", NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", &Albedo_Bare);

	decldiagparam("a1", NHRU, "[1.08e7]", "0.0", "1.0e8", "Albedo decay time constant for cold snow", "(s)", &a1);

	decldiagparam("a2", NHRU, "[7.2e5]", "0.0", "1.0e8", "Albedo decay time constant for melting snow", "(s)", &a2);

	decldiagparam("amin", NHRU, "[0.5]", "0.0", "1.0", "Minimum albedo for aged snow", "()", &amin);

	decldiagparam("amax", NHRU, "[0.84]", "0.0", "1.0", "Maximum albedo for fresh snow", "()", &amax);

	decldiagparam("smin", NHRU, "[10]", "0.0", "20", "Minimum snowfall to refresh snow albedo", "(mm/int)", &smin);

	declgetvar("*", "hru_tmean", "(�C)", &T0);

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoRichard::init(void) {

	dt = 3600 * 24 / Global::Freq;

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh)
		if (SWE[hh] > 1.0)
			Albedo[hh] = Albedo_Snow[hh];
		else
			Albedo[hh] = Albedo_Bare[hh];

}

void ClassalbedoRichard::run(void) {

	for (hh = 0; chkStruct(); ++hh) {
		if (SWE[hh] > 1.0) {

			if (T0[hh] < 0) // cold snow
				Albedo[hh] = Albedo[hh] - dt / a1[hh];
			else            // melting snow
				Albedo[hh] = (Albedo[hh] - amin[hh])*exp(-dt / a2[hh]) + amin[hh];

			Albedo[hh] = Albedo[hh] + (amax[hh] - Albedo[hh])*net_snow[hh] / smin[hh];

			if (Albedo[hh] < amin[hh]) Albedo[hh] = amin[hh];
			if (Albedo[hh] > amax[hh]) Albedo[hh] = amax[hh];
		}
		else
			Albedo[hh] = Albedo_Bare[hh];
	}
}

ClassalbedoBaker* ClassalbedoBaker::klone(string name) const {
	return new ClassalbedoBaker(name);
}

void ClassalbedoBaker::decl(void) {

	Description = "'Calculates snowcover albedo from a method proposed by Baker.'";

	declstatvar("Albedo", NHRU, "Albedo", "()", &Albedo);

	decllocal("Ab_t", NHRU, "timesteps since albedo refresh", "()", &Ab_t);

	decldiagparam("Albedo_Snow", NHRU, "[0.85]", "0.0", "1.0", "Initial albedo for snow cover", "()", &Albedo_Snow);

	decldiagparam("Albedo_Bare", NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", &Albedo_Bare);

	decldiagparam("refresh", NHRU, "[3.0]", "0.0", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", &refresh);


	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoBaker::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		if (SWE[hh] > 1.0)
			Albedo[hh] = Albedo_Snow[hh];
		else
			Albedo[hh] = Albedo_Bare[hh];

		Ab_t[hh] = 0.0;
	}
}

void ClassalbedoBaker::run(void) {

	for (hh = 0; chkStruct(); ++hh) {
		if (SWE[hh] > 1.0) {

			// albedo routine:

			if (net_snow[hh] >= refresh[hh])
				Ab_t[hh] = 0;
			else
				Ab_t[hh] = Ab_t[hh] + 1;

			// albedo decay formulation after (Baker et al., 1990):

			Albedo[hh] = 0.9 - 0.0473 * pow(Ab_t[hh] / Global::Freq, 0.1f);

			// Baker, D.G., Ruschy, D.L., Wall, D.B., 1990.
			//   The albedo decay of prairie snows. J. Appl. Meteor. 29 _2, 179-187

			// if albedo < Albedo_Bare or no snow albedo == Albedo_Bare

			if (Albedo[hh] < Albedo_Bare[hh] || SWE[hh] <= 1.0)
				Albedo[hh] = Albedo_Bare[hh];
		}
		else
			Albedo[hh] = Albedo_Bare[hh];
	}
}

//#define MINALB  0.50    /* minimum possible albedo; Aguado, 1985 */
//#define MAXALB  0.88    /* maximum snow albedo */
//#define ALBINC  0.004   /* albedo decay increment (Coughlan Diss.) */
//#define HEATINC 30.0    /* heat increment parameter (Coughlan Diss). */

#define Hf  334.4E3    // Latent heat of fusion, J/kg
#define major 5.0      // threshold for major melt event(5 mm/d)

float Farouki_a(float fract_por) {

	float a = 0.0;
	float nnew = 0.0;

	while (fabs(fract_por - nnew) > 0.001) {
		a += (fract_por - nnew)*0.25;
		nnew = 3 * a*a - 2 * a*a*a;
	}
	return a;
}

//---------------------------------------------------------------------------

ClassNetroute_M* ClassNetroute_M::klone(string name) const {
	return new ClassNetroute_M(name);
}

float ClassNetroute_M::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassNetroute_M::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute_M::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route and Muskingum method for \"outflow\".'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to gw of this HRU via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

	declparam("preferential_flow", NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

	decllocal("Ktravel", NHRU, "travel time", "(d)", &Ktravel);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &Lag);

	declparam("route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &route_n);

	declparam("route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "(m)", &route_R);

	declparam("route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &route_S0);

	declparam("route_L", NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

	declparam("route_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &route_X_M);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("whereto", NHRU, "[0]", "0", "1000", "send to; 0 - basin outflow, or HRU input", "()", &whereto);

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);

	declparam("Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute_M::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "Netroute_M:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "Netroute_M:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "Netroute_M:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	const float Vw[3] = { 1.67, 1.22, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

	for (hh = 0; hh < nhru; ++hh) {
		float Vavg = (1.0 / route_n[hh])*pow(route_R[hh], 2.0 / 3.0)*pow(route_S0[hh], 0.5f); // (m/s)
		Ktravel[hh] = route_L[hh] / (Vw[route_Cshp[hh]] * Vavg) / 86400.0; // (d)
	}

	hruDelay = new ClassMuskingum(inflow, outflow, Ktravel, route_X_M, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	for (hh = 0; hh < nhru; ++hh) {
		if (Ktravel[hh] >= (Global::Interval / (2.0*route_X_M[hh]))) {
		 string S = string("'" + Name + " (Netroute_M) Muskingum coefficient negative in HRU ").c_str() + std::to_string(hh + 1);
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
		}

		if (Ktravel[hh] < (Global::Interval / (2.0*(1.0 - route_X_M[hh])))) { //    if(hruDelay->c0[hh] < 0.0)
			hruDelay->c0[hh] = 0.0;
			hruDelay->c1[hh] = 1.0;
			hruDelay->c2[hh] = 0.0;
		}
	}

	basinflow[0] = 0.0;
	basinflow_s[0] = 0.0;
	cumbasinflow[0] = 0.0;
	basingw[0] = 0.0;
	basingw_s[0] = 0.0;
	cumbasingw[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		outflow_diverted[hh] = 0.0;
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		cum_to_Sd[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_preferential_flow_to_gw[hh] = 0.0;

		gwinflow[hh] = 0.0;
		gwcuminflow[hh] = 0.0;
		gwcumoutflow[hh] = 0.0;
		gwcumoutflow_diverted[hh] = 0.0;
		HRU_cumbasinflow[hh] = 0.0;

		ssrinflow[hh] = 0.0;
		ssrcuminflow[hh] = 0.0;
		ssroutflow[hh] = 0.0;
		ssrcumoutflow[hh] = 0.0;

		runinflow[hh] = 0.0;
		runcuminflow[hh] = 0.0;
		runoutflow[hh] = 0.0;
		runcumoutflow[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (Netroute_M)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassNetroute_M::run(void) {

	long nstep = getstep() % Global::Freq;

	basinflow[0] = 0.0;
	basingw[0] = 0.0;

	for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

		for (hh = 0; chkStruct(hh); ++hh)
			if (order[hh] - 1 == jj)
				break;

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];

		gwoutflow_diverted[hh] = 0.0;

		float gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0
				gwoutflow_diverted[hhh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hhh];
				gwoutflow[hhh] = 0.0;
				gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // units (mm*km^2/int)
								soil_rechr[hh] += gw_amount / hru_area[hh];

								soil_moist[hh] += gw_amount / hru_area[hh];
								cum_to_soil_rechr[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								soil_moist[hh] += free;
								soil_rechr[hh] = soil_rechr_max[hh];
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // outflow (mm*km^2/int)
								Sd[hh] += gw_amount / hru_area[hh];
								cum_to_Sd[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_Sd[hh] += free;
								Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						gw[hh] += gw_amount / hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU
				else { // > nhru then put in basinflow
					basinflow[0] += gw_amount * 1000; // (m3)
					HRU_cumbasinflow[hh] = gw_amount;
					cumoutflow[hh] += gw_amount;
					gw_amount = 0.0;
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];

		ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		runcumoutflow[hh] += runoutflow[hh];

		inflow[hh] = (runoutflow[hh] + ssroutflow[hh] + gw_amount); // add this HRU runoff and subsurface flow

		cuminflow[hh] += inflow[hh];

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {
				if (preferential_flow[hhh]) {
					gw[hh] += outflow[hhh] / hru_area[hh];
					cum_preferential_flow_to_gw[hh] += outflow[hhh] / hru_area[hh];
					outflow[hhh] = 0.0;
				}
				else {
					outflow_diverted[hhh] = outflow[hhh];
					cumoutflow_diverted[hhh] += outflow_diverted[hhh];
					float free = soil_rechr_max[hh] - soil_rechr[hh];
					if (free > 0.0 && !soil_rechr_ByPass[hh]) {
						if (free > outflow[hhh] / hru_area[hh]) { // units (mm*km^2/int)
							soil_rechr[hh] += outflow[hhh] / hru_area[hh];
							soil_moist[hh] += outflow[hhh] / hru_area[hh];
							cum_to_soil_rechr[hh] += outflow[hhh] / hru_area[hh];
							outflow[hhh] = 0.0;
						}
						else {
							outflow[hhh] = (outflow[hhh] / hru_area[hh] - free)*hru_area[hh];
							cum_to_soil_rechr[hh] += free;
							soil_moist[hh] += free;
							soil_rechr[hh] = soil_rechr_max[hh];
						}
					}

					free = Sdmax[hh] - Sd[hh];
					if (free > 0.0 && !Sd_ByPass[hh] && outflow[hhh] > 0.0) {
						if (free > outflow[hhh] / hru_area[hh]) { // units (mm*km^2/int)
							Sd[hh] += outflow[hhh] / hru_area[hh];
							cum_to_Sd[hh] += outflow[hhh] / hru_area[hh];
							outflow[hhh] = 0.0;
						}
						else {
							outflow[hhh] = (outflow[hhh] / hru_area[hh] - free)*hru_area[hh];
							cum_to_Sd[hh] += free;
							Sd[hh] = Sdmax[hh];
						} // if
					} // if
				} // else

				if (outflow[hhh] > 0.0) // handle excess
					redirected_residual[hh] += outflow[hhh]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

				outflow[hhh] = 0.0;
			} // if
		} // for hhh

		hruDelay->DoMuskingum(hh); // need to update for later HRUs

		if (whereto[hh] == 0) { // move to basinflow
			basinflow[0] += outflow[hh] * 1000; // (m3)
			HRU_cumbasinflow[hh] += outflow[hh];
			cumoutflow[hh] += outflow[hh];
		}
		if (gwwhereto[hh] == 0) { // move to basin gw
			basingw[0] += gwoutflow[hh] * 1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		}  // end if


	} // for hh

	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasingw[0] += basingw[0];
}

void ClassNetroute_M::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' hruDelay->Left         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' gwDelay_in_storage     (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_M)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh] * hru_area[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (Netroute_M)' cumbasinflow (m^3): ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute_M)' cumbasingw   (m^3): ").c_str(), cumbasingw[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M)' Allgwcuminflow  (mm*basin): ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M)' Allcuminflow    (mm*basin): ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allcumoutflow   (mm*basin): ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M)' Allssrcuminflow  (mm*basin): ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M)' Allruncuminflow) (mm*basin): ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M)' AllSdcuminflow    (mm*basin): ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}

ClassREWroute2* ClassREWroute2::klone(string name) const {
	return new ClassREWroute2(name);
}

void ClassREWroute2::decl(void) {

	Description = "'Handles the routing of surface and subsurface runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.' \
                    'uses Muskingum and culverts,' \
                    'uses Clark and culverts.'";

	variation_set = VARIATION_ORG;

	inflowCnt = declgrpvar("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", &rew, &inflow_All);

	declvar("WS_inflow", NHRU, "inflow from each RB", "(m^3/int)", &inflow);

	declstatdiag("cum_WSinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cuminflow);

	declvar("WS_outflow", NHRU, "outflow of each RB", "(m^3/int)", &outflow);

	declstatdiag("cum_WSoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumoutflow);

	declvar("WS_flow", BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", &flow);

	declvar("WS_flow_s", BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", &flow_s);

	declstatdiag("cum_WSflow", BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", &cumflow);


	gwCnt = declgrpvar("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", &gwrew, &gw_All);

	declvar("WS_gwinflow", NHRU, "inflow from each RB", "(m^3/int)", &gwinflow);

	declstatdiag("cum_WSgwinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cumgwinflow);

	declvar("WS_gwoutflow", NHRU, "outflow of each RB", "(m^3/int)", &gwoutflow);

	declstatdiag("cum_WSgwoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumgwoutflow);

	declvar("WS_gwflow", BASIN, "watershed ground water outflow", "(m^3/int)", &gwflow);

	declvar("WS_gwflow_s", BASIN, "watershed ground water outflow", "(m^3/s)", &gwflow_s);

	declstatdiag("cum_WSgwflow", BASIN, "cumulative watershed ground water outflow", "(m^3)", &cumgwflow);


	declparam("watershed_area", BASIN, "3", "1e-6", "1e09", "Total watershed area", "(km^2)", &watershed_area);

	declparam("RB_area", NHRU, "[1]", "1e-6", "1e09", "RB area", "(km^2)", &RB_area);

	declparam("WS_whereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_whereto);

	declparam("WS_order", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_order);

	declparam("WS_gwwhereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_gwwhereto);

	declparam("WS_gworder", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_gworder);

	declparam("WS_Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_Lag);

	declparam("WS_gwLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_gwLag);


	variation_set = VARIATION_2 + VARIATION_3;

	declvar("WS_culvert_Q", NHRU, "flow in culvert", "(m^3/s)", &culvert_Q);

	declvar("WS_culvert_water_H", NHRU, "depth of pond at culvert inlet", "(m)", &culvert_water_H);

	declvar("WS_culvert_water_A", NHRU, "surface area of culvert pond", "(m^2)", &culvert_water_A);

	declvar("WS_culvert_water_V", NHRU, "volume of water in culvert pond", "(m^3)", &culvert_water_V);

	declvar("WS_culvert_over_Q", NHRU, "flow over the road", "(m^3/s)", &culvert_over_Q);

	declvar("WS_culvert_evap", NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

	declvar("WS_cum_culvert", NHRU, "Cumulative culvert HRU flow", "(m^3)", &cum_culvert);

	declvar("WS_cum_culvert_over", NHRU, "Cumulative culvert HRU overflow", "(m^3)", &cum_culvert_over);

	declstatdiag("WS_HD", NHRU, "ratio of depth of water at culvert/culvert diameter", "()", &HD);

	declparam("WS_channel_slope", NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert", "()", &WS_channel_slope);

	declparam("WS_side_slope", NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope", "()", &WS_side_slope);

	declparam("WS_culvert_diam", NHRU, "[0.5]", "0.1", "5.0", "culvert diameter", "(m)", &WS_culvert_diam);

	declparam("WS_culvert_water_Dmax", NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet", "(m)", &WS_culvert_water_Dmax);

	declparam("WS_number_culverts", NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert", "()", &WS_number_culverts);

	declparam("WS_culvert_type", NHRU, "[4]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet", "()", &WS_culvert_type);


	variation_set = VARIATION_0 + VARIATION_2;

	decldiag("WS_Ktravel_var", NHRU, "inflow storage constant", "(d)", &WS_Ktravel_var);

	decldiag("WS_gwKtravel_var", NHRU, "gw storage constant", "(d)", &WS_gwKtravel_var);

	declparam("WS_route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &WS_route_n);

	declparam("WS_route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "()", &WS_route_R);

	declparam("WS_route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &WS_route_S0);

	declparam("WS_route_L", NHRU, "[3.69]", "0.01", "1.0E10", "routing length", "(m)", &WS_route_L);

	declparam("WS_Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &WS_Channel_shp);

	declparam("WS_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_route_X_M);

	declparam("WS_gwX_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_gwroute_X_M);


	variation_set = VARIATION_1 + VARIATION_3;

	declparam("WS_Kstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_Kstorage);

	declparam("WS_gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_gwKstorage);


	variation_set = VARIATION_ORG;
}

void ClassREWroute2::init(void) {

	if (nhru < inflowCnt) {
		CRHMException Except("Module REW route # of HRUs must be >= # of groups.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	float totarea = 0;
	for (hh = 0; hh < nhru; ++hh)
		totarea += RB_area[hh];

	if (fabs((totarea - watershed_area[0]) / watershed_area[0]) > 1e-3) {
		const_cast<float *>  (watershed_area)[0] = totarea;
		CRHMException TExcept(string(string("Sum of RB's area <> Watershed area, Watershed area made = ") + Convert(totarea)).c_str(), WARNING);
		LogError(TExcept);
	}

	if (WS_whereto[WS_order[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'whereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (WS_gwwhereto[WS_gworder[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'gwwhereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (variation == VARIATION_ORG || variation == VARIATION_2) {
		const float Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

		for (hh = 0; hh < nhru; ++hh) {
			float Vavg = (1.0 / WS_route_n[hh])*pow(WS_route_R[hh], 2.0f / 3.0f)*pow(WS_route_S0[hh], 0.5f);

			WS_gwKtravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
			WS_Ktravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
		}

		inflowDelay = new ClassMuskingum(inflow, outflow, WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
		gwDelay = new ClassMuskingum(gwinflow, gwoutflow, WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);

		for (hh = 0; hh < nhru; ++hh) {
			if (WS_gwKtravel_var[hh] >= (Global::Interval / (2.0*WS_gwroute_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) GW Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (gwDelay->c0[hh] < 0.0) {
				gwDelay->c0[hh] = 0.0;
				gwDelay->c1[hh] = 1.0;
				gwDelay->c2[hh] = 0.0;
			}

			if (WS_Ktravel_var[hh] >= (Global::Interval / (2.0*WS_route_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) inflow Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (WS_Ktravel_var[hh] < (Global::Interval / (2.0*(1.0 - WS_route_X_M[hh])))) { //inflowDelay->c0[hh] < 0.0
				inflowDelay->c0[hh] = 0.0;
				inflowDelay->c1[hh] = 1.0;
				inflowDelay->c2[hh] = 0.0;
			}
		}
	}
	else if (variation == VARIATION_1 || variation == VARIATION_3) {
		Clark_inflowDelay = new ClassClark(inflow, outflow, WS_Kstorage, WS_Lag, nhru);
		Clark_gwDelay = new ClassClark(inflow, outflow, WS_gwKstorage, WS_gwLag, nhru);
	}

	flow[0] = 0.0;
	flow_s[0] = 0.0;
	cumflow[0] = 0.0;

	gwflow[0] = 0.0;
	gwflow_s[0] = 0.0;
	cumgwflow[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		gwinflow[hh] = 0.0;
		cumgwinflow[hh] = 0.0;
		gwoutflow[hh] = 0.0;
		cumgwoutflow[hh] = 0.0;

		if (variation == VARIATION_2 || variation == VARIATION_3) {
			culvert_water_V[hh] = 0.0;
			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			HD[hh] = 0.0;
			culvert_evap[hh] = 0.0;
			cum_culvert[hh] = 0.0;
			cum_culvert_over[hh] = 0.0;

			if (WS_number_culverts[hh] > 0.0) {
				if (WS_culvert_water_Dmax[hh] / WS_culvert_diam[hh] > 2.5) {
				 string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + std::to_string(hh + 1);
					CRHMException TExcept(S.c_str(), WARNING);
					LogError(TExcept);
				}
			}
		}
	}
}

void ClassREWroute2::run(void) {

	flow[0] = 0.0;
	gwflow[0] = 0.0;

	for (long jj = 0; jj < inflowCnt; ++jj) { // HRUs not in sequence

		int hh = WS_order[jj] - 1;

		if (rew[hh])
			inflow[hh] = inflow_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			inflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {
				if (outflow[hhh] > 0.0)
					inflow[hh] += outflow[hhh];
			}
		}

		cuminflow[hh] += inflow[hh];

		if (variation == VARIATION_2 || variation == VARIATION_3)
			Culvert(hh);

		if (variation == VARIATION_ORG || variation == VARIATION_2)
			inflowDelay->DoMuskingum(hh); // need to update for later HRUs
		else if (variation == VARIATION_1 || variation == VARIATION_3)
			Clark_inflowDelay->DoClark(hh); // need to update for later HRUs

		cumoutflow[hh] += outflow[hh];

		if (WS_whereto[hh] == 0) {
			flow[0] += outflow[hh]; // (already m^3)
			flow_s[0] = flow[0] * Global::Freq / 86400.0;
		}
	} //end for

	for (long jj = 0; jj < gwCnt; ++jj) { // HRUs not in sequence

		int hh = WS_gworder[jj] - 1;

		if (gwrew[hh])
			gwinflow[hh] = gw_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			gwinflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_gwwhereto[hhh] - 1 == hh && gwoutflow[hhh] > 0.0) {
				if (gwoutflow[hhh] > 0.0)
					gwinflow[hh] += gwoutflow[hhh];
			}
		}

		cumgwinflow[hh] += gwinflow[hh];

		if (variation == VARIATION_ORG || variation == VARIATION_2)
			gwDelay->DoMuskingum(hh); // need to update for later HRUs
		else if (variation == VARIATION_1 || variation == VARIATION_3)
			Clark_gwDelay->DoClark(hh); // need to update for later HRUs

		cumgwoutflow[hh] += gwoutflow[hh];

		if (WS_gwwhereto[hh] == 0) {
			gwflow[0] += gwoutflow[hh]; // (already m^3)
			gwflow_s[0] = gwflow[0] * Global::Freq / 86400.0;
		}
	} //end for

	cumflow[0] += flow[0];
	cumgwflow[0] += gwflow[0];
}

void ClassREWroute2::Culvert(long hh) {

	float culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

	culvert_water_A[hh] = 0.0;
	culvert_water_H[hh] = 0.0;
	culvert_over_Q[hh] = 0.0;
	culvert_Q[hh] = 0.0;
	HD[hh] = 0.0;
	culvert_evap[hh] = 0.0;

	if ((inflow[hh] > 0.0 || culvert_water_V[hh] > 0.0) && WS_number_culverts[hh] > 0.0) {
		culvert_water_V[hh] += inflow[hh]; // m3 where inflow(m^3/int)
		inflow[hh] = 0.0;

		culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * WS_channel_slope[hh] * WS_side_slope[hh], 1.0 / 3.0); // (m)

		if (culvert_water_H[hh] > 0.0) {

			// calculate overflow if culvert level exceeds Dmax

			culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * WS_channel_slope[hh] * WS_side_slope[hh], 1.0 / 3.0); // (m)

			if (culvert_water_H[hh] > WS_culvert_water_Dmax[hh]) { // (m) overflow over road
				culvert_water_H[hh] = WS_culvert_water_Dmax[hh]; // (m)
				float maxVol = pow(WS_culvert_water_Dmax[hh], 3.0) / (3.0*WS_channel_slope[hh] * WS_side_slope[hh]); // (m3)

				culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400 * Global::Freq; //  (m3) to (m3/int) - difference released over interval
				culvert_water_V[hh] = maxVol; // (m3)

				cum_culvert_over[hh] += culvert_over_Q[hh]; // (m3)
				cum_culvert[hh] += culvert_Q[hh] * 86400 / Global::Freq; // (m3/s) to (m3)

				inflow[hh] += culvert_over_Q[hh] * 86400 / Global::Freq; // (m3/int) to (m3)
			}

			// calculate flow through culvert

			HD[hh] = culvert_water_H[hh] / WS_culvert_diam[hh];

			if (HD[hh] <= 0.0)
				culvert_Q[hh] = 0.0;
			else if (HD[hh] < 1.5)
				culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
					+ 0.159413*HD[hh] + 0.00772254)*culvert_C[WS_culvert_type[hh]] * WS_number_culverts[hh] * pow(WS_culvert_diam[hh], 2.5), 0.0); // (m3/s)
			else
				culvert_Q[hh] = culvert_C[WS_culvert_type[hh]] * WS_number_culverts[hh] * 0.785*pow(WS_culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

			if (culvert_water_V[hh] > culvert_Q[hh] * 86400 / Global::Freq) // (m3/s) to (m3)
				culvert_water_V[hh] -= culvert_Q[hh] * 86400 / Global::Freq; // (m3/s) to (m3)
			else { // all runs away
				culvert_Q[hh] = culvert_water_V[hh] / 86400 * Global::Freq;  // (m3) to (m3/int) - difference released over interval
				culvert_water_V[hh] = 0.0;
			}

			inflow[hh] += culvert_Q[hh] * 86400 / Global::Freq; // (m3/int)
			cum_culvert[hh] += culvert_Q[hh] * 86400 / Global::Freq; // (m3/s) to (m3/int)

			culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (WS_channel_slope[hh] * WS_side_slope[hh]); // used for evaporation
		}
	}
}

void ClassREWroute2::finish(bool good) {
	for (hh = 0; hh < inflowCnt; ++hh) {
		LogMessageA(hh, string("'" + Name + " (REW_route2)' cuminflow          (m^3) (m^3): ").c_str(), cuminflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route2)' cumoutflow         (m^3) (m^3): ").c_str(), cumoutflow[hh], 1.0);
		if (variation == VARIATION_ORG || variation == VARIATION_2)
			LogMessageA(hh, string("'" + Name + " (REW_route2)' inflowDelay_in_storage (m^3) (m^3): ").c_str(), inflowDelay->Left(hh), 1.0);
		else if (variation == VARIATION_1 || variation == VARIATION_3)
			LogMessageA(hh, string("'" + Name + " (REW_route2)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str(), Clark_inflowDelay->Left(hh), 1.0);

		LogMessageA(hh, string("'" + Name + " (REW_route2)' cumgwinflow  (m^3) (m^3): ").c_str(), cumgwinflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route2)' cumgwoutflow (m^3) (m^3): ").c_str(), cumgwoutflow[hh], 1.0);
		if (variation == VARIATION_ORG || variation == VARIATION_2)
			LogMessageA(hh, string("'" + Name + " (REW_route2)' gwDelay_in_storage (m^3) (m^3): ").c_str(), gwDelay->Left(hh), 1.0);
		else if (variation == VARIATION_1 || variation == VARIATION_3)
			LogMessageA(hh, string("'" + Name + " (REW_route2)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str(), Clark_gwDelay->Left(hh), 1.0);

		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (REW_route2)' cumflow (m^3): ").c_str(), cumflow[0]);
	LogMessage(string("'" + Name + " (REW_route2)' cumgwflow (m^3): ").c_str(), cumgwflow[0]);
	LogDebug(" ");

	if (variation == VARIATION_ORG || variation == VARIATION_2) {
		delete inflowDelay;
		delete gwDelay;
	}
	else if (variation == VARIATION_1 || variation == VARIATION_3) {
		delete Clark_inflowDelay;
		delete Clark_gwDelay;
	}
}

// Walmsley_Wind module that adjusts the wind speed due to topographic feature

Classwalmsley_wind* Classwalmsley_wind::klone(string name) const {
	return new Classwalmsley_wind(name);
}

void Classwalmsley_wind::decl(void) {

	Description = "'A parametric version of the wind flow model (Mason and Sykes (1979)).'";

	declvar("hru_Uadjust", NHRU, "adjusted wind speed due to topography", "(m/s)", &hru_Uadjust);

	declvar("hru_Uchange", NHRU, "amount of change in wind speed due to topography", "(m/s)", &hru_Uchange);

	decldiag("WR", NHRU, "wind ratio between adjusted wind speed and reference wind speed", "()", &WR);

	declparam("Zwind", NHRU, "[10.0]", "0.0", "100.0", "wind instrument height", "(m)", &Zwind);

	declparam("A", NHRU, "0.0", "0.0", "4.4", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 2.5 = 2D escarpments, 3.0 = 2D hills, 3.5 = 2D rolling terrain, 4.0 = 3D hills, 4.4 = 3D rolling terrain",
		"()", &Ax);

	declparam("B", NHRU, "0.0", "0.0", "2.0", "coefficient for wind speed change due to topography, 0.0 = flat terrain, 0.8 = 2D escarpments, 1.1 = 3D rolling terrain, 1.55 = 2D rolling terrain, 1.6 = 3D hills, 2.0 = 2D hills",
		"()", &Bx);

	declparam("L", NHRU, "[1000.0]", "40.0", "1.0E6f", "upwind length at half height", "(m)", &L);

	declparam("Walmsley_Ht", NHRU, "[0]", "-1000.0", "1000.0", "Walmsley height", "(m)", &Walmsley_Ht);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

}

void Classwalmsley_wind::init(void) {
	nhru = getdim(NHRU);
}

void Classwalmsley_wind::run(void) {

	/*Walmsley, Talor and Salmon's simple guidelines for estimating wind speed variations
	due to topographic features*/

	for (int hh = 0; hh < nhru; ++hh) {
		double Smax = Bx[hh] * Walmsley_Ht[hh] / L[hh]; // maximum decay of fractional speed-up ratio
		double S = Smax * exp(-Ax[hh] * Zwind[hh] / L[hh]); // the decay of fractional speed-up ratio

		hru_Uchange[hh] = S * hru_u[hh];
		hru_Uadjust[hh] = hru_Uchange[hh] + hru_u[hh];
		WR[hh] = hru_Uadjust[hh] / hru_u[hh];
	}

}

// TSANDCLAY{LOAM1, LOAM2, LOAM3, SAND, CLAY}

const float rho_s[] = { 41.1, 75.2, 91.4, 1300.0, 1300.0 }; // (kg/m3) solids
const float c_s[] = { 1920.0, 1920.0, 1920.0, 890.0, 890.0 }; // (J/m3/K) solids
const float Cv_s[] = { 78912.0, 144384.0, 175392.0, 1157000.0, 1157000.0 }; // (J/m3/K) solids
const float lam_s[] = { 0.21, 0.21, 0.21, 2.50, 2.50 };  // (W/m/K) solids
const float ks_s[] = { 450.0, 154.0, 13.0, 5.0, 3.0 }; // (m/day)  solids
const float por_s[] = { 0.96, 0.9, 0.87, 0.43, 0.43 }; // ()  solids

													   //---------------------------------------------------------------------------

ClassLongVt* ClassLongVt::klone(string name) const {
	return new ClassLongVt(name);
}

void ClassLongVt::decl(void) {

	Description = "'LongVt: Calculates incoming long-wave radiation variable (QliVt_Var) (Sicart et al., 2005) using terrain view factor.' \
                 'using input Qsi (W/m^2) to calculate daily average,' \
                 'using input observation QsiDObs (W/m^2) for daily average,' \
                 'using input variable QsiD_Var (W/m^2) from module Annandale for daily average,' \
                 'using input observation Qli (W/m^2) for daily average.'";

	variation_set = VARIATION_ORG;

	declvar("tau", NHRU, "Atmospheric transmissivity = S/Sextra", "()", &tau);

	declvar("Qli_Var", NHRU, "calculated incoming long", "(W/m^2)", &Qli_Var);

	declvar("QliVt_Var", NHRU, "calculated incoming long in open environment", "(W/m^2)", &QliVt_Var);



	declgetvar("*", "QdroDext", "(MJ/m^2*d)", &QdroDext);

	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_rh", "()", &hru_rh);


	declparam("Vt", NHRU, "[0.3]", "0.0", "1.0", "terrain view factor (equivalent to 1-Vf)", "()", &Vt);

	decldiagparam("epsilon_s", NHRU, "[0.98]", "0.0", "1.0", "terrain emissivity", "()", &epsilon_s);


	variation_set = VARIATION_0;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

	declobsfunc("Qsi", "QsiDavg", &QsiDavg, AVG, NULL, true); // must check for NULL


	variation_set = VARIATION_1;

	declreadobs("QsiDObs", NHRU, "incident short-wave", "(W/m^2)", &QsiD, HRU_OBS_Q);


	variation_set = VARIATION_2;

	declgetvar("*", "QsiD_Var", "(W/m^2)", &QsiD_Var);


	variation_set = VARIATION_3;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


	variation_set = VARIATION_0 + VARIATION_1 + VARIATION_2;

	declobs("Qli", NHRU, "incoming calculated long-wave", "(W/m^2)", &Qli_out);


	variation_set = VARIATION_ORG;

}

void ClassLongVt::init(void) {
	nhru = getdim(NHRU);

	if (variation == VARIATION_ORG) {
		if (!QsiDavg) { // only exists if an actual file observation
			CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi observation to calculate tau. Qsi appears to be a declared obs instead of read from a file.").c_str(), TERMINATE);
			LogError(TExcept);
		}
		else {
			CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi observation to calculate tau.").c_str(), WARNING);
			LogError(TExcept);
		}
	}
	else if (variation == VARIATION_1) {
		CRHMException TExcept(string("'" + Name + " (LongVt)' using QsiDObs observation to calculate tau.").c_str(), WARNING);
		LogError(TExcept);
	}
	else if (variation == VARIATION_2) {
		CRHMException TExcept(string("'" + Name + " (LongVt)' using Qsi_Var variable to calculate tau.").c_str(), WARNING);
		LogError(TExcept);
	}
	else if (variation == VARIATION_3) {
		CRHMException TExcept(string("'" + Name + " (LongVt)' using Qli observation to convert to QliVT_Var.").c_str(), WARNING);
		LogError(TExcept);
	}
}

void ClassLongVt::run(void) {

	long hhmax;
	long nstep = getstep() % Global::Freq;


	for (hh = 0; chkStruct(); ++hh) {
		if (nstep == 1 || Global::Freq == 1) { // beginning of every day
			if (QdroDext[hh] >= 0.001) {    // 04/21/14
				switch (variation) {
				case VARIATION_ORG:
					tau[hh] = QsiDavg[hh] * 86400 / 1E6 / QdroDext[hh]; // 03/29/07
					break;
				case VARIATION_1:
					tau[hh] = QsiD[hh] * 86400 / 1E6 / QdroDext[hh]; // 03/29/07
					break;
				case VARIATION_2:
					tau[hh] = QsiD_Var[hh] * 86400 / 1E6 / QdroDext[hh]; // 03/29/07
					break;
				}
			}
			else
				tau[hh] = 0.8;     // 04/21/14
		}

		if (variation != VARIATION_3)
			Qli_Var[hh] = 1.24f*pow((hru_ea[hh] * 10.0f) / (hru_t[hh] + CRHM_constants::Tm), 1.0f / 7.0f)*(1.0f + 0.44f*hru_rh[hh] / 100.0f - 0.18f*tau[hh])*CRHM_constants::sbc*pow(hru_t[hh] + CRHM_constants::Tm, 4.0f);
		else
			Qli_Var[hh] = Qli[hh];

		QliVt_Var[hh] = (1.0f - Vt[hh])*Qli_Var[hh] + Vt[hh] * epsilon_s[hh] * CRHM_constants::sbc*pow(hru_t[hh] + CRHM_constants::Tm, 4.0f);

		if (variation != VARIATION_3)
			Qli_out[hh] = QliVt_Var[hh];
	}
}

Classpbsm_M* Classpbsm_M::klone(string name) const {
	return new Classpbsm_M(name);
}

void Classpbsm_M::decl(void) {

	Description = "'Calculates snow transport and sublimation (Pomeroy and Li, 1999). This module has enhanced transport distribution features.'";

	declstatvar("SWE", NHRU, "snow water equivalent", "(mm)", &SWE);

	declvar("Subl", NHRU, "interval sublimation", "(mm/int)", &Subl);

	declvar("Drift", NHRU, "interval transport", "(mm/int)", &Drift);

	declvar("BasinSnowLoss", BASIN, "transport out of basin", "(mm/int)", &BasinSnowLoss);

	declstatvar("cumSubl", NHRU, "cumulative sublimation", "(mm)", &cumSubl);

	declstatvar("cumDrift", NHRU, "cumulative transport from HRU", "(mm)", &cumDrift);

	declstatvar("cumBasinSnowLoss", BASIN, "cumulative transport out of basin", "(mm)", &cumBasinSnowLoss);

	declstatvar("cumBasinSnowGain", BASIN, "cumulative transport to basin estimated from HRU 1", "(mm)", &cumBasinSnowGain);

	decllocal("cumDriftIn", NHRU, "cumulative transport to HRU", "(mm)", &cumDriftIn);

	decllocal("DrySnow", NHRU, "DrySnow", "()", &DrySnow);

	decllocal("SnowAge", NHRU, "SnowAge", "()", &SnowAge);

	decllocal("this_distrib", NHRU, "current step distribution", "()", &this_distrib);

	declstatvar("cumSno", NHRU, "cumulative snow", "(mm)", &cumSno);

	declvar("Prob", NHRU, "Probability", "()", &Prob);

	declstatvar("snowdepth", NHRU, "depth of snow using Gray/Pomeroy", "(m)", &snowdepth);

	declvar("Q_leeslope", NHRU, "leeslope transport from HRU", "(mm)", &Q_leeslope);

	declvar("Q_valley", NHRU, "valley transport from HRU", "(mm)", &Q_valley);

	declvar("Results", NDEFN, "calulated distributions", "()", &Results, &Results_lay, nhru);

	/* parameters */

	declparam("fetch", NHRU, "[1000.0]", "300.0", "10000.0", "fetch distance", "(m)", &fetch);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	declparam("distrib", NDEFN, "[0.0, 1.0, 1.0, 1.0]", "0.0", "99.0", "distribution array", "()", &distrib, &distrib_hru, nhru);

	decldiagparam("N_S", NHRU, "[320]", "0.1", "500", "vegetation number density", "(1/m^2)", &N_S);

	decldiagparam("A_S", NHRU, "[0.003]", "0.0", "2.0", "stalk diameter", "(m)", &A_S);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("inhibit_bs", NHRU, "[0]", "0", "1", "inhibit blowing snow, 1 -> inhibit", "()", &inhibit_bs);

	decldiagparam("inhibit_subl", NHRU, "[0]", "0", "1", "inhibit sublimation, 1 -> inhibit", "()", &inhibit_subl);

	declparam("eq_prof", NHRU, "[0]", "0", "1", "0: use vegetation height, 1: use equilibrium profile depth as SWE_Max", "()", &eq_prof);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

	decldiagparam("Beta_M", NHRU, "[170.0]", "32.0", "170.0", "ratio of element to surface drag for vegetation; 170 for stalks, 320 for shrubs", "()", &Beta_M);

	declparam("hru_Ht", NHRU, "[0.0]", "0.0", "1000.0", "HRU feature height(m)", "(m)", &hru_Ht);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_rh", "(%)", &hru_rh);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);

}

void Classpbsm_M::init(void) {

	nhru = getdim(NHRU);

	cumBasinSnowLoss[0] = 0.0;
	cumBasinSnowGain[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		SWE[hh] = 0.0;
		cumDrift[hh] = 0.0;
		cumDriftIn[hh] = 0.0;
		cumSubl[hh] = 0.0;
		cumSno[hh] = 0.0;
		SnowAge[hh] = 0.0;
		DrySnow[hh] = 0;
		snowdepth[hh] = 0.0;

		if ((hh > 0) && (Ht[hh] < Ht[hh - 1]) && distrib[hh - 1] > 0) {
			CRHMException TExcept("PBSM - vegetation heights not in ascending order", WARNING);
			LogError(TExcept);
			//         throw TExcept;
		}
	}

	hru_basin = new float[nhru];

	for (hh = 0; hh < nhru; ++hh)
		hru_basin[hh] = hru_area[hh] / basin_area[0];
}

void Classpbsm_M::run(void) {

	float Znod, Ustar, Ustn, E_StubHt, Lambda, Ut, Uten_Prob;
	float DriftH, SublH, CurrentDrift, total, SWE_Max, transport;
	float VB_distrib;

	for (hh = 0; chkStruct(); ++hh) {

		if (net_snow[hh] > 0.0) {
			SWE[hh] = SWE[hh] + net_snow[hh];
			cumSno[hh] = cumSno[hh] + net_snow[hh];
		}

		Drift[hh] = 0.0;
		Subl[hh] = 0.0;
		Prob[hh] = 0.0;
		Q_leeslope[hh] = 0.0;
		Q_valley[hh] = 0.0;

		if (SWE[hh] > 0.0 && !inhibit_bs[hh]) {

			E_StubHt = Ht[hh] - DepthofSnow(SWE[hh]); // depths(m) SWE(mm)
			if (E_StubHt < 0.0001)
				E_StubHt = 0.0001;

			float d = 2.0 / 3.0*E_StubHt;

			float Z = 0.123*E_StubHt;

			float Wind = hru_u[hh] * log((10.0 - d) / Z) / log((Zwind[hh] - d) / Z);

			Ustar = 0.02264*pow(Wind, 1.295f); // Eq. 6.2 rev.,  Ustar over fallow

			if (E_StubHt > 0.01) {
				Znod = (sqr(Ustar) / 163.3f) + 0.5*N_S[hh] * E_StubHt*A_S[hh]; // Eq. 29, Snowcover Book
				Lambda = N_S[hh] * A_S[hh] * E_StubHt;  // Raupach Eq. 1

				Ustn = Ustar * sqrt((Beta_M[hh] * Lambda) / (1.0 + Beta_M[hh] * Lambda));

				Uten_Prob = (log(10.0 / Znod)) / PBSM_constants::KARMAN *sqrt(Ustar - Ustn);
			}
			else {
				Uten_Prob = Wind;
			} // end if

			ProbabilityThresholdNew(SWE[hh], hru_t[hh], Uten_Prob, Prob[hh], Ut, hru_newsnow[hh], SnowAge[hh], DrySnow[hh]);

			if (Prob[hh] > 0.001) {
				Ut = Ut * 0.8;

				Pbsm(E_StubHt, Ut, DriftH, SublH, hru_t[hh], Wind, hru_rh[hh], fetch[hh], N_S[hh], A_S[hh],
					hru_GSL[hh], hru_Ht[hh], Beta_M[hh], Q_leeslope[hh], Q_valley[hh]);

				Drift[hh] = DriftH * Prob[hh] / fetch[hh];
				if (!inhibit_subl[hh])
					Subl[hh] = SublH * Prob[hh];

				// handle insufficient snow pack

				if (Drift[hh] + Subl[hh] > SWE[hh]) {
					Subl[hh] = SWE[hh] * Subl[hh] / (Subl[hh] + Drift[hh]);
					Drift[hh] = SWE[hh] - Subl[hh];
				} // end if

				cumDrift[hh] = cumDrift[hh] + Drift[hh];
				cumSubl[hh] = cumSubl[hh] + Subl[hh];

				SWE[hh] = SWE[hh] - Subl[hh] - Drift[hh];
			}
		} // end if
	} // end for (hh)

	  // distribute drift

	for (long hh = 0; chkStruct(hh); ++hh) {
		if (distrib_hru[hh][0] > 0.0) { // simulate transport entering basin using HRU 1
			float Drft = Drift[hh] * distrib_hru[hh][0];
			SWE[hh] += Drft;
			cumDriftIn[hh] += Drft;
			cumBasinSnowGain[0] += Drft * hru_basin[hh];  // **** hru_basin = hru_area/basin_area ****
		}
	}

	BasinSnowLoss[0] = 0.0;
	long LastN = 0;

	for (long nn = LastN; chkStruct(nn); ++nn) {
		if (distrib[nn] >= 0.0 && nn + 1 < nhru) // skip till last HRU or -ve distribution
			continue;

		for (long cc = LastN; chkStruct(cc, hh - 1); ++cc) { // handle drift over range
			CurrentDrift = Drift[cc] * hru_basin[cc];

			if (CurrentDrift > 0.0) { // drift has occurred!
				for (long hh = LastN + 1; chkStruct(hh, nn + 1); ++hh) {
					if (!eq_prof[hh]) { //use veg height to calculate SWE_Max
						SWE_Max = SWEfromDepth(Ht[hh]);
					}
					else {
						float tanEqSlope = (0.1818 * 100 * tan(hru_GSL[cc] * DEGtoRAD) + 0.4309 * 100 * tan(hru_GSL[hh] * DEGtoRAD) - 7.2887) / 100;
						float EqProfDepth = hru_Ht[hh] / 2 * (1 - (tan(hru_GSL[hh] * DEGtoRAD) - tanEqSlope) / (tan(hru_GSL[hh] * DEGtoRAD)*(1 + tan(hru_GSL[hh] * DEGtoRAD)*tanEqSlope)));
						SWE_Max = SWEfromDepth(EqProfDepth);
					}

					if (hh == nn) { // handle last HRU
						if (fabs(distrib_hru[cc][hh]) + distrib_hru[nhru - 1][hh] > 0.0)
							BasinSnowLoss[0] = CurrentDrift * distrib_hru[nhru - 1][hh] / (fabs(distrib_hru[cc][hh]) + distrib_hru[nhru - 1][hh]); // drift directly to basin loss
						else
							BasinSnowLoss[0] = 0;

						CurrentDrift -= BasinSnowLoss[0];

						SWE[hh] += CurrentDrift / hru_basin[hh];
						cumDriftIn[hh] += CurrentDrift / hru_basin[hh];
						if (SWE[hh] > SWE_Max) { // over filled!
							if (SWE[hh] - SWE_Max >= Drift[hh]) { // drift less than excess
								SWE[hh] -= Drift[hh];
								BasinSnowLoss[0] += Drift[hh];
							}
							else { // drift more than excess
								BasinSnowLoss[0] += SWE[hh] - SWE_Max;
								SWE[hh] = SWE_Max;
							}
							BasinSnowLoss[0] *= hru_basin[hh];
							cumBasinSnowLoss[0] += BasinSnowLoss[0];
						}
					}
					else if (SWE_Max > SWE[hh] && distrib_hru[cc][hh] > 0.0) {
						// handle intermediate HRUs with available storage and distrib > 0

						float sum = distrib_hru[nhru - 1][cc]; // always the very last HRU
						for (long jj = hh; chkStruct(jj, nn + 1); jj++) { // calculate denominator
							Results_lay[cc][jj] = 0.0;
							if (distrib_hru[cc][jj] != 88 && distrib_hru[cc][jj] != 99) {
								sum += fabs(distrib_hru[cc][jj]);
							}
						}
						if (distrib_hru[cc][hh] == 88 && Q_leeslope[hh] >= 0.0) { // leeward slope
							if (Q_leeslope[hh] > 0.0)
								this_distrib[hh] = (1 - sum)*Q_leeslope[hh] / (Q_leeslope[hh] + Q_valley[hh]);
							else
								this_distrib[hh] = 0.0;

							Results_lay[cc][hh] = this_distrib[hh];
							//              sum += this_distrib[hh];
							for (long kk = hh + 1; chkStruct(kk, nn + 1); kk++) {
								if (distrib_hru[cc][kk] == 99 && Q_valley[hh] >= 0.0) {
									if (Q_valley[hh] > 0.0)
										VB_distrib = (1 - sum)*Q_valley[hh] / (Q_leeslope[hh] + Q_valley[hh]);
									else
										VB_distrib = 0.0;
								} // if
							} // for kk
						}
						else if (distrib_hru[cc][hh] == 99) { //&& Q_valley[hh] >= 0.0) { // valley bottom
															  //              if(Q_valley[hh] > 0.0)
															  //				this_distrib[hh] = (1 - sum)*Q_valley[hh]/(Q_leeslope[hh] + Q_valley[hh]);
															  //              else
															  //                this_distrib[hh] = 0.0;
							this_distrib[hh] = VB_distrib;

							Results_lay[cc][hh] = this_distrib[hh];
							//              sum += this_distrib[hh];
						}
						else {
							this_distrib[hh] = distrib_hru[cc][hh];
						}

						// determine contribution and scale
						transport = CurrentDrift * fabs(this_distrib[hh]) / hru_basin[hh] / 1;
						if (SWE_Max > SWE[hh] + transport) // sufficient capacity
							SWE[hh] += transport;
						else {
							transport = SWE_Max - SWE[hh];  // insufficient capacity
							SWE[hh] = SWE_Max;
						}
						CurrentDrift -= transport * hru_basin[hh]; // remove drift used from total available
						cumDriftIn[hh] += transport;
					} // end if
				} // end for (hh)
			} // end if
		} // end for
		LastN = nn + 1;
	} // end for (nn)

	for (hh = 0; chkStruct(); ++hh) { // snow cover inhibits evaporation

		if (SWE[hh] > 0.0) {
			const_cast<long*> (inhibit_evap)[hh] = 1;
			snowdepth[hh] = DepthofSnow(SWE[hh]);
		}
		else {
			const_cast<long*> (inhibit_evap)[hh] = 0;
			snowdepth[hh] = 0.0;
		}
	} // end for (hh)
}

void Classpbsm_M::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumSno     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumDrift   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDrift[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumDriftIn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumDriftIn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumSubl    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSubl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' cumCover   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSno[hh] + cumDriftIn[hh] - cumDrift[hh] - cumSubl[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (pbsm_M)' SWE        (mm) (mm*hru) (mm*hru/basin): ").c_str(), SWE[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}

	LogMessage("'pbsm_M' cumulative basin snow loss (mm): ", cumBasinSnowLoss[0]); //
	LogMessage("'pbsm_M' cumulative basin snow gain (mm): ", cumBasinSnowGain[0]); //
	LogDebug(" ");

	delete[] hru_basin;
	hru_basin = NULL;
}

void Classpbsm_M::Sum(float TQsalt, float TQsusp, float SBsum, float SBsalt, float & DriftH, float & SublH)
{

	// total sublimation

	if ((SBsum + SBsalt) >= 0.0)
		SublH = 0.0;
	else
		SublH = (SBsum + SBsalt)*(-1E+3); // -mgmm2s to mg/m^2/s to g/m^2/s

	DriftH = (TQsalt + TQsusp); // kg/m-width/s
								// Convert to interval values

	SublH = SublH * Global::Interval * 3600 * 24 / 1000.0; // g/m^2/s to mm/m^2/interval
	DriftH = DriftH * Global::Interval * 3600 * 24;      // kg/m-width/s to kg/m-width/interval

} // sum procedure

void Classpbsm_M::Pbsm(float E_StubHt, float Uthr, float & DriftH, float & SublH,
	float t, float u, float rh, float Fetch,
	long N_S, float A_S, float GSL, float height, float Beta_M, float & Qdist_leeslope, float & Qdist_valley)
{

	/*   Modified Calculations for Mean Particle Mass in this version
	program to calculate blowing snow horizontal flux, sublimation rate
	and latent heat flux due to snow sublimation for a variety of windspeeds,
	boundary layers and surface conditions.

	All variable and constants entered into the programme are in SI and
	use Canadian Atmospheric Environement Service Meteorological data
	format.  Snow transport is in kg per square meter per half hour
	from the surface to 5 metres height.  Sublimation is totaled to the top
	of the boundary layer for diffusion, based on the meteorological
	Fetch and is expressed in millimeters of blowing snow lost over
	a square meter of snow surface per half hour  */

	float   A, Alpha, B, Bd, Bound, C,
		Diff, DmDt, Es, H,
		Htran, Hsalt, Inc, Lamb, Lambda, Lb,
		Mpm, Mpr, Nh, Nsalt,
		Nz, Nuss, Omega, TQsalt,
		TQsum, Qz, RauTerm, Temp,
		Reyn, SBsalt, Sbz, SBsum,
		SigmaZ, Sigma2, SvDens, Usthr, Ustar,
		UstarZ, Uz, Vs, Vsalt, Sigma,
		Vsusp, Z, Zr, Zstb,
		tX, tH, Qdist;

	//Compute stubble coefficients

	Zstb = 0.005*N_S*A_S*E_StubHt*100.0;      // Lettau, used for susp Z0''
	Lambda = N_S * A_S*E_StubHt;         // Raupach Eq. 1
	Sigma = (M_PI*A_S) / (4.0*E_StubHt); // Raupach Eq. 4

										 // Calculate the flux for interval
	TQsalt = 0.0;                      // Total saltation flux
	TQsum = 0.0;                       // Total Suspension
	SBsalt = 0.0;
	SBsum = 0.0;
	DriftH = 0.0;
	SublH = 0.0;

	Temp = t + 273.0;                 // Convert to Deg. K

									  // Check for data errors    Fluxes set to zero for the interval
	if ((Temp < 0.0) || (u < 1.0) || (rh < 0.01)) { return; }

	if (rh >= 1.0) rh = rh / 100.0;       // handle %rh

	Lamb = 0.000076843*Temp + 0.003130762;   // therm. cond. of atm. (J/(msK))
	Diff = 2.06e-5f*pow(Temp / 273.0f, 1.75f); // diffus. of w.vap. atmos. (m^2/s
	B = PBSM_constants::LATH * PBSM_constants::M / (PBSM_constants::R * Temp) - 1.0;

	// find undersaturation of w. vapour at 2 metres
	Es = 611.15f * exp(22.452f*(Temp - 273.0f) / Temp);  //{sat pressure}
	SvDens = (Es*PBSM_constants::M) / (PBSM_constants::R*Temp);                       //{sat density}
	Sigma2 = rh - 1.0;                              //{undersaturation at 2 m}

	if (u > Uthr) {

		// define saltation parameters and calculate saltation
		//    rate using 10/1987 MODEL OF BLOWING SNOW EQUATIONS

		Usthr = 0.03697f*Uthr;                                  //{Eq. 6.3}
		Ustar = 0.02264f*pow(u, 1.295f);                         //{Eq. 6.2 rev}
		if (E_StubHt > 0.0001)                         //{Eq. 6.2 rev}
			RauTerm = 1.0 / ((1.0 - Sigma * Lambda)*(1.0 + Beta_M * Lambda)); //{Raupach}
		else
			RauTerm = 1.0;

		Hsalt = PBSM_constants::C2 / (2.0f*PBSM_constants::g)*sqr(Ustar);                         //{Eq. 4.13}
		Nsalt = 2.0*PBSM_constants::rho / (PBSM_constants::C2*PBSM_constants::C3*Ustar)*(RauTerm - sqr(Usthr) / sqr(Ustar)); //{Eq. 4.14 updated}

		if (Nsalt <= 0.0) {
			Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
			return;
		}

		TQsalt = PBSM_constants::C1*PBSM_constants::rho*Usthr / (PBSM_constants::g*PBSM_constants::C3*Ustar)*(sqr(Ustar)*RauTerm - sqr(Usthr)); // Eq. 4.20

																																				// calculate sublimation rate in the saltation layer

		Mpr = 100E-6;
		Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
		Alpha = 5.0;

		SigmaZ = Sigma2 * (1.019 + 0.027 * log(Hsalt)); // Eq. 6.20, Revised in May. 1997
		if (SigmaZ > -0.01) { SigmaZ = -0.01; }
		Vsalt = 0.6325 * Ustar + 2.3 * Usthr;          // Eq. 6.25
		Reyn = (2.0 * Mpr * Vsalt) / 1.88E-5;            // Eq. 6.22
		Nuss = 1.79 + 0.606 * sqrt(Reyn);              // Eq. 6.21
		A = Lamb * Temp * Nuss;
		C = 1.0 / (Diff * SvDens * Nuss);
		DmDt = ((2.0 * M_PI * Mpr * SigmaZ) - (Htran * B / A)) / ((PBSM_constants::LATH * B / A) + C);

		//{Eq. 6.16} {Gamma Dist. Corr.}
		Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Mpr*sqr(Mpr) *(1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

		Vs = DmDt / Mpm;                // Sublimation rate coefficient Eq. 6.13
		SBsalt = Vs * Nsalt * Hsalt;  // Eq. 6.11

									  // calculate mass flux in the suspended layers and the sublimation
									  //     rate for layers of height Inc from height r to b

		Zr = 0.05628 * Ustar;         // Eq. 5.27
		Alpha = 15.0;
		Inc = 0.0001;

		// Loop to find the first suspended drift density level, r
		//     from the reference level Zr
		//     To preserve continuity with saltation the first suspended
		//     level drift density is less than or equal to Nsalt.

		TQsum = 0;
		SBsum = 0;

		Z = Zr + Inc;
		while (Z <= 0.15) {
			Nz = 0.8 * exp(-1.55*(pow(0.05628f*Ustar, -0.544f) - pow(Z, -0.544f)));

			// Eq. 5.26, Revised in Dec. 1995
			if (Nz <= Nsalt) { goto Ten; }
			Z = Z + Inc;
		} //while
	Ten:  Lb = Z + Inc;
		Z = Lb;
		Inc = 0.001;

		// find height of fully-developed boundary layer for turbulent
		//     diffusion using a form of Pasquills plume dispersion eq.
		//     iterate towards Bound

		Bd = 1.0;
		Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
			sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));          // Eq. 6.9
		while (fabs(Bound - Bd) > 0.001) {
			Bd = Bound;
			Bound = PBSM_constants::ZD + (PBSM_constants::KARMAN2 * (Fetch - PBSM_constants::XD) * pow(log(Bd * 162.926f /
				sqr(Ustar)) * log(PBSM_constants::ZD * 162.926f / sqr(Ustar)), -0.5f));      // Eq. 6.9
		} //while


		  // Loop to calculate the suspended mass flux up to 5 metres
		  //     and the total sublimation rate to the top of the boundary layer
		  //   at increments of 1 mm to 50cm & increments of 10 cm to  b

		Qdist_leeslope = 0;
		Qdist_valley = 0;

	Twenty: H = Z + Inc;
		while (H <= Bound) {
			Nh = 0.8 * exp(-1.55f*(pow(0.05628f*Ustar, -0.544f) - pow(H, -0.544f)));
			Nz = Nh;
			UstarZ = Ustar * pow(1.2f / (1.2f + Nz), 0.5f);                  // Eq. 5.17a
			Uz = (UstarZ / PBSM_constants::KARMAN) *log(H / ((0.00613f *sqr(Ustar)) + Zstb));// Eq. 4.17r
			if (Uz > 0) {
				if (height <= 0)
					tX = 0;
				else
					tX = height / (Uz*tan(GSL*DEGtoRAD));

				Mpr = 4.6e-5 * pow(H, -0.258f);                            // Eq. 6.15
				if (H >= 5.0) { Mpr = 30E-6f; }

				Htran = 0.9 * M_PI * sqr(Mpr) * PBSM_constants::Qstar;
				Alpha = 4.08 + 12.6 * H;                                  // Eq. 6.14
				if (H >= 1.5) { Alpha = 25.0; }

				SigmaZ = Sigma2 * (1.019 + 0.027 * log(H));  // Eq. 6.20, Revised in May. 1997
				if (SigmaZ > -0.01) { SigmaZ = -0.01; }
				Omega = 1.1e7f * pow(Mpr, 1.8f);               // Eq. 5.18
				tH = (height + H) / Omega;
				Vsusp = Omega + 0.0106f * pow(Uz, 1.36f);
				Reyn = (2.0f * Mpr * Vsusp) / 1.88e-5f;          // Eq. 6.22
				Nuss = 1.79f + 0.606f * sqrt(Reyn);            // Eq. 6.21
				A = Lamb * Temp * Nuss;
				C = 1.0 / (Diff * SvDens * Nuss);
				DmDt = ((2.0f*M_PI * Mpr * SigmaZ) - (Htran*B / A)) / ((PBSM_constants::LATH*B / A) + C);
				Mpm = 1.333f * M_PI * PBSM_constants::DICE * sqr(Mpr)*Mpr *   // Eq. 6.16
					(1.0f + 3.0f / Alpha + 2.0f / sqr(Alpha));       // Gamma Dist. Corr.
				Vs = DmDt / Mpm;                               // Eq. 6.13
				Sbz = Vs * Nz * Inc;                         // mg
				SBsum = SBsum + Sbz;                         // Eq. 6.12
				Qz = Nz * Uz * Inc;

				if (tH < tX)
					Qdist_leeslope += Qz;
				else
					Qdist_valley += Qz;
				// Eq. 5.4
				if (H >= 5.0) { Qz = 0.0; }
				TQsum = TQsum + Qz;                          // Eq. 5.5
				if (Nz >= 1e-5) {
					if (((H - Inc) >= 0.5) && (H < 0.6)) {
						Inc = 0.1;
						Z = 0.5;
						goto Twenty;                            // re start the loop
					} //{if}
				}
				else {
					Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
					return;
				} // if
			}
			else {
				TQsalt = 0.0;
				TQsum = 0.0;
				SBsalt = 0.0;
				SBsum = 0.0;
				Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
				return;
			} // if
			H = H + Inc;
		} // while
	} // if

	Sum(TQsalt, TQsum, SBsum, SBsalt, DriftH, SublH);
} //PBSM procedure}

ClassNetroute_D* ClassNetroute_D::klone(string name) const {
	return new ClassNetroute_D(name);
}

float ClassNetroute_D::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassNetroute_D::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute_D::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method. Distributed flow.'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to this HRU's gw via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

	declparam("preferential_flow", NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);


	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("cumscaling_boost", NHRU, "cumulative amout inflow boosted", "(mm*km^2)", &cumscaling_boost);

	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

	decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Kstorage", NHRU, "[0.0]", "0.0", "200.0", "aggregated storage constant", "(d)", &Kstorage);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", &Lag);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

	declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);

	decldiagparam("scaling_factor", NHRU, "[1.0]", "0.0", "1.0E6", "multiplies the input to Muskingum by this scaling factor.", "()", &scaling_factor); // temporary

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute_D::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "Netroute_D:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "Netroute_D:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "Netroute:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	hruDelay = new ClassClark(inflow, outflow, Kstorage, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	basinflow[0] = 0.0;
	basinflow_s[0] = 0.0;
	cumbasinflow[0] = 0.0;
	basingw[0] = 0.0;
	basingw_s[0] = 0.0;
	cumbasingw[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		outflow_diverted[hh] = 0.0;
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		cumscaling_boost[hh] = 0.0;
		cum_to_Sd[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_preferential_flow_to_gw[hh] = 0.0;

		gwinflow[hh] = 0.0;
		gwcuminflow[hh] = 0.0;
		gwcumoutflow[hh] = 0.0;
		gwcumoutflow_diverted[hh] = 0.0;
		HRU_cumbasinflow[hh] = 0.0;

		ssrinflow[hh] = 0.0;
		ssrcuminflow[hh] = 0.0;
		ssroutflow[hh] = 0.0;
		ssrcumoutflow[hh] = 0.0;

		runinflow[hh] = 0.0;
		runcuminflow[hh] = 0.0;
		runoutflow[hh] = 0.0;
		runcumoutflow[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (Netroute_D)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassNetroute_D::run(void) {

	long nstep = getstep() % Global::Freq;

	basinflow[0] = 0.0;
	basingw[0] = 0.0;

	if (getstep() == 1) {
		for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
			distrib_sum[hh] = 0.0;

			for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
				if (distrib_hru[hh][hhh] < 0.0)
					const_cast<float **> (distrib_hru)[hh][hhh] = -distrib_hru[hh][hhh] * hru_area[hh];
				distrib_sum[hh] += distrib_hru[hh][hhh];
			}

			if (distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0) {
				const_cast<float *> (distrib_Basin)[hh] = 1;
			}

			distrib_sum[hh] += distrib_Basin[hh];
		}
	}

	float gw_amount;

	for (long jj = 0; chkStruct(jj); ++jj) { // do HRUs in sequence

		for (hh = 0; chkStruct(hh); ++hh) {
			if (order[hh] - 1 == jj)
				break;
		}

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];

		gwoutflow_diverted[hh] = 0.0;

		gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0
				gwoutflow_diverted[hhh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hhh];
				gwoutflow[hhh] = 0.0;
				gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // outflow (mm*km^2/int)
								soil_rechr[hh] += gw_amount / hru_area[hh];
								soil_moist[hh] += gw_amount / hru_area[hh];
								cum_to_soil_rechr[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								soil_moist[hh] += free;
								soil_rechr[hh] = soil_rechr_max[hh];
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // outflow (mm*km^2/int)
								Sd[hh] += gw_amount / hru_area[hh];
								cum_to_Sd[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_Sd[hh] += free;
								Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						gw[hh] += gw_amount / hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU
				else { // > nhru then put in basinflow
					basinflow[0] += gw_amount * 1000; // (m3)
					HRU_cumbasinflow[hh] = gw_amount;
					cumoutflow[hh] += gw_amount;
					gw_amount = 0.0;
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];

		inflow[hh] = gw_amount;
		outflow_diverted[hh] = 0.0;
	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];

		ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		runcumoutflow[hh] += runoutflow[hh];

		inflow[hh] += scaling_factor[hh] * (runoutflow[hh] + ssroutflow[hh]); // add this HRU runoff and subsurface flow temporary change 10/07/11

		if (outflow[hh] > 0.0) {

			float Used = outflow[hh] * distrib_Basin[hh] / distrib_sum[hh];
			if (distrib_Basin[hh] > 0.0) { // direct to basin

				basinflow[0] += Used * 1000; // (m3)
				HRU_cumbasinflow[hh] += Used;
				cumoutflow[hh] += Used;
			}

			for (long To = 0; chkStruct(To); ++To) { // distribute outflow of HRUs

				if (hh != To && distrib_hru[hh][To] > 0.0) {
					float Amount = (outflow[hh] - Used) / hru_area[To] * distrib_hru[hh][To] / (distrib_sum[hh] - distrib_Basin[hh]); // outflow (mm*km^2/int)

					if (preferential_flow[hh]) {
						gw[To] += Amount;
						cum_preferential_flow_to_gw[To] += Amount;
						Amount = 0.0;
					}
					else {
						float free = soil_rechr_max[To] - soil_rechr[To];
						if (free > 0.0 && !soil_rechr_ByPass[To]) {
							if (free > Amount) { // outflow (mm*km^2/int)
								soil_rechr[To] += Amount;
								soil_moist[To] += Amount;
								cum_to_soil_rechr[To] += Amount;
								Amount = 0.0;
							}
							else {
								Amount -= free;
								cum_to_soil_rechr[To] += free;
								soil_moist[To] += free;
								soil_rechr[To] = soil_rechr_max[To];
							}
						} // if

						free = Sdmax[To] - Sd[To];
						if (free > 0.0 && !Sd_ByPass[To] && Amount > 0.0) {
							if (free > Amount) { // outflow (mm*km^2/int)
								Sd[To] += Amount;
								cum_to_Sd[To] += Amount;
								Amount = 0.0;
							}
							else {
								Amount -= free;
								cum_to_Sd[To] += free;
								Sd[To] = Sdmax[To];
							}
						} // if
					} // else

					if (Amount > 0.0)
						redirected_residual[To] += Amount * hru_area[To]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

				} // contribute to this HRU
			} // distribute outflow over HRUs
		} // outflow > 0.0

		if (gwwhereto[hh] == 0) { // move to basin gw
			basingw[0] += gwoutflow[hh] * 1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		} // end if

	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) {
		cuminflow[hh] += inflow[hh];
		cumscaling_boost[hh] += inflow[hh] * (scaling_factor[hh] - 1.0);

		outflow_diverted[hh] = 0.0;
		if (distrib_sum[hh] > 0.0) { // does not apply to last HRU
			for (long hhh = 0; chkStruct(hhh); ++hhh) {
				outflow_diverted[hh] += outflow[hh] * distrib_hru[hh][hhh] / distrib_sum[hh];
			}
		}
		cumoutflow_diverted[hh] += outflow_diverted[hh];
	} //end for

	hruDelay->DoClark();
	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasingw[0] += basingw[0];
}

void ClassNetroute_D::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	for (hh = 0; chkStruct(); ++hh) {

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' scaling_boost          (mm) (mm*km^2) (mm*basin): ").c_str(), cumscaling_boost[hh] / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' gwDelay_in_storage           (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_D)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_D)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh] * hru_area[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (Netroute_D)' cumbasinflow (m^3): ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute_D)' cumbasingw  (m^3): ").c_str(), cumbasingw[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_D)' Allgwcuminflow (mm*basin): ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_D)' Allcuminflow (mm*basin): ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allcumoutflow (mm*basin): ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_D)' Allssrcuminflow (mm*basin): ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_D)' Allruncuminflow (mm*basin): ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_D)' AllSdcuminflow (mm*basin): ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute_D)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}

ClassNetroute_M_D* ClassNetroute_M_D::klone(string name) const {
	return new ClassNetroute_M_D(name);
}

float ClassNetroute_M_D::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassNetroute_M_D::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassNetroute_M_D::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route and Muskingum method for \"outflow\". Distributed flow.'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU recycled tosoil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to this HRU's gw via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

	declparam("preferential_flow", NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);

	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("cumscaling_boost", NHRU, "cumulative amout inflow boosted", "(mm*km^2)", &cumscaling_boost);

	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

	decllocal("Ktravel", NHRU, "travel time", "(d)", &Ktravel);

	decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &Lag);

	declparam("route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &route_n);

	declparam("route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "(m)", &route_R);

	declparam("route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &route_S0);

	declparam("route_L", NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

	declparam("route_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &route_X_M);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

	declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);

	declparam("Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);

	decldiagparam("scaling_factor", NHRU, "[1.0]", "0.0", "1.0E6", "multiplies the input to Muskingum by this scaling factor.", "()", &scaling_factor); // temporary

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "gw", "(mm)", &gw);
}

void ClassNetroute_M_D::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "Netroute_M_D:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "Netroute_M_D:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "Netroute_M_D:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	const float Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

	for (hh = 0; hh < nhru; ++hh) {
		float Vavg = (1.0 / route_n[hh])*pow(route_R[hh], 2.0 / 3.0)*pow(route_S0[hh], 0.5f); // (m/s)
		Ktravel[hh] = route_L[hh] / (Vw[route_Cshp[hh]] * Vavg) / 86400.0; // (d)
	}

	hruDelay = new ClassMuskingum(inflow, outflow, Ktravel, route_X_M, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	for (hh = 0; hh < nhru; ++hh) {
		if (Ktravel[hh] >= (Global::Interval / (2.0*route_X_M[hh]))) {
		 string S = string("'" + Name + " (Netroute_M_D) Muskingum coefficient negative in HRU ").c_str() + std::to_string(hh + 1);
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
		}

		if (Ktravel[hh] < (Global::Interval / (2.0*(1.0 - route_X_M[hh])))) { //    if(hruDelay->c0[hh] < 0.0)
			hruDelay->c0[hh] = 0.0;
			hruDelay->c1[hh] = 1.0;
			hruDelay->c2[hh] = 0.0;
		}
	}

	basinflow[0] = 0.0;
	basinflow_s[0] = 0.0;
	cumbasinflow[0] = 0.0;
	basingw[0] = 0.0;
	basingw_s[0] = 0.0;
	cumbasingw[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		outflow_diverted[hh] = 0.0;
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		cumscaling_boost[hh] = 0.0;
		cum_to_Sd[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_preferential_flow_to_gw[hh] = 0.0;

		gwinflow[hh] = 0.0;
		gwcuminflow[hh] = 0.0;
		gwcumoutflow[hh] = 0.0;
		gwcumoutflow_diverted[hh] = 0.0;
		HRU_cumbasinflow[hh] = 0.0;

		ssrinflow[hh] = 0.0;
		ssrcuminflow[hh] = 0.0;
		ssroutflow[hh] = 0.0;
		ssrcumoutflow[hh] = 0.0;

		runinflow[hh] = 0.0;
		runcuminflow[hh] = 0.0;
		runoutflow[hh] = 0.0;
		runcumoutflow[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (Netroute_M_D)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassNetroute_M_D::run(void) {

	long nstep = getstep() % Global::Freq;

	basinflow[0] = 0.0;
	basingw[0] = 0.0;

	if (getstep() == 1) {
		for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
			distrib_sum[hh] = 0.0;

			for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
				if (distrib_hru[hh][hhh] < 0.0)
					const_cast<float **> (distrib_hru)[hh][hhh] = -distrib_hru[hh][hhh] * hru_area[hh];
				distrib_sum[hh] += distrib_hru[hh][hhh];
			}

			if (distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0) {
				const_cast<float *> (distrib_Basin)[hh] = 1;
			}

			distrib_sum[hh] += distrib_Basin[hh];
		}
	}

	float gw_amount;

	for (long jj = 0; chkStruct(jj); ++jj) { // do HRUs in sequence

		for (hh = 0; chkStruct(hh); ++hh) {
			if (order[hh] - 1 == jj)
				break;
		}

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];

		gwoutflow_diverted[hh] = 0.0;

		gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0
				gwoutflow_diverted[hhh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hhh];
				gwoutflow[hhh] = 0.0;
				gwcumoutflow_diverted[hhh] += gwoutflow_diverted[hhh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // outflow (mm*km^2/int)
								soil_rechr[hh] += gw_amount / hru_area[hh];
								soil_moist[hh] += gw_amount / hru_area[hh];
								cum_to_soil_rechr[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								soil_moist[hh] += free;
								soil_rechr[hh] = soil_rechr_max[hh];
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount / hru_area[hh]) { // outflow (mm*km^2/int)
								Sd[hh] += gw_amount / hru_area[hh];
								cum_to_Sd[hh] += gw_amount / hru_area[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount / hru_area[hh] - free)*hru_area[hh];
								cum_to_Sd[hh] += free;
								Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						gw[hh] += gw_amount / hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU
				else { // > nhru then put in basinflow
					basinflow[0] += gw_amount * 1000; // (m3)
					HRU_cumbasinflow[hh] = gw_amount;
					cumoutflow[hh] += gw_amount;
					gw_amount = 0.0;
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];

		inflow[hh] = gw_amount;
		outflow_diverted[hh] = 0.0;
	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		runinflow[hh] = soil_runoff_Buf[hh] * hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];

		ssrinflow[hh] = soil_ssr_Buf[hh] * hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		runcumoutflow[hh] += runoutflow[hh];

		inflow[hh] += scaling_factor[hh] * (runoutflow[hh] + ssroutflow[hh]); // add this HRU runoff and subsurface flow temporary change 10/07/11

		if (outflow[hh] > 0.0) {

			float Used = outflow[hh] * distrib_Basin[hh] / distrib_sum[hh];
			if (distrib_Basin[hh] > 0.0) { // direct to basin

				basinflow[0] += Used * 1000; // (m3)
				HRU_cumbasinflow[hh] += Used;
				cumoutflow[hh] += Used;
			}

			for (long To = 0; chkStruct(To); ++To) { // distribute outflow of HRUs

				if (hh != To && distrib_hru[hh][To] > 0.0) {
					float Amount = (outflow[hh] - Used) / hru_area[To] * distrib_hru[hh][To] / (distrib_sum[hh] - distrib_Basin[hh]); // outflow (mm*km^2/int)

					if (preferential_flow[hh]) {
						gw[To] += Amount;
						cum_preferential_flow_to_gw[To] += Amount;
						Amount = 0.0;
					}
					else {
						float free = soil_rechr_max[To] - soil_rechr[To];
						if (free > 0.0 && !soil_rechr_ByPass[To]) {
							if (free > Amount) { // outflow (mm*km^2/int)
								soil_rechr[To] += Amount;
								soil_moist[To] += Amount;
								cum_to_soil_rechr[To] += Amount;
								Amount = 0.0;
							}
							else {
								Amount -= free;
								cum_to_soil_rechr[To] += free;
								soil_moist[To] += free;
								soil_rechr[To] = soil_rechr_max[To];
							}
						} // if

						free = Sdmax[To] - Sd[To];
						if (free > 0.0 && !Sd_ByPass[To] && Amount > 0.0) {
							if (free > Amount) { // outflow (mm*km^2/int)
								Sd[To] += Amount;
								cum_to_Sd[To] += Amount;
								Amount = 0.0;
							}
							else {
								Amount -= free;
								cum_to_Sd[To] += free;
								Sd[To] = Sdmax[To];
							}
						} // if
					} // else

					if (Amount > 0.0)
						redirected_residual[To] += Amount * hru_area[To]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

				} // contribute to this HRU
			} // distribute outflow over HRUs
		} // outflow > 0.0

		if (gwwhereto[hh] == 0) { // move to basin gw
			basingw[0] += gwoutflow[hh] * 1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		} // end if

	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) {
		cuminflow[hh] += inflow[hh];
		cumscaling_boost[hh] += inflow[hh] * (scaling_factor[hh] - 1.0);

		outflow_diverted[hh] = 0.0;
		if (distrib_sum[hh] > 0.0) { // does not apply to last HRU
			for (long hhh = 0; chkStruct(hhh); ++hhh) {
				outflow_diverted[hh] += outflow[hh] * distrib_hru[hh][hhh] / distrib_sum[hh];
			}
		}
		cumoutflow_diverted[hh] += outflow_diverted[hh];
	} //end for

	hruDelay->DoMuskingum();
	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasingw[0] += basingw[0];
}

void ClassNetroute_M_D::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	for (hh = 0; chkStruct(); ++hh) {

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cuminflow              (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cumoutflow             (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cumoutflow_diverted    (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' hruDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' scaling_boost          (mm) (mm*km^2) (mm*basin): ").c_str(), cumscaling_boost[hh] / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrcuminflow           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrcumoutflow          (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' ssrDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runoffcuminflow        (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runoffcumoutflow       (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' runDelay_in_storage    (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcuminflow            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcumoutflow           (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwcumdiverted          (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' gwDelay_in_storage     (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cum_to_Sd              (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' cum_to_soil_rechr      (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D)' HRU_cumbasinflow       (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh] * hru_area[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (Netroute_M_D)' cumulative surface & subsurface basinflow(m^3): ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute_M_D)' cumulative basingw  (m^3): ").c_str(), cumbasingw[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcuminflow (mm*basin): ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcumoutflow (mm*basin): ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allgwcumoutflowdiverted (mm*basin): ").c_str(), Allgwcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D)' Allcuminflow (mm*basin): ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allcumoutflow (mm*basin): ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allcumoutflowdiverted (mm*basin): ").c_str(), Allcumoutflowdiverted);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D)' Allssrcuminflow (mm*basin): ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allssrcumoutflow (mm*basin): ").c_str(), Allssrcumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D)' Allruncuminflow (mm*basin): ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allruncumoutflow (mm*basin): ").c_str(), Allruncumoutflow);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D)' AllSdcuminflow (mm*basin): ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D)' Allrechrcuminflow (mm*basin): ").c_str(), Allrechrcuminflow);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}

ClassSetSoil* ClassSetSoil::klone(string name) const {
	return new ClassSetSoil(name);
}

void ClassSetSoil::decl(void) {

	Description = "'Initialises module \"soil\", soil moisture variables from \"Vol_h2o_content\" and depth parameters.'";

	declparam("RUN_ID", BASIN, "1", "-1E8", "+1E8", "run identification. If RUN_ID > 0 then the log file default name 'CRHM_output' with extensions .sum, .log OR .txt is expanded to 'CRHM_output_ID'.", "()", &RUN_ID);

	declparam("RUN_START", BASIN, "0", "0", "+1E5", "run start time (Automation)", "(d)", &RUN_START);

	declparam("RUN_END", BASIN, "0", "0", "+1E5", "run end time (Automation)", "(d)", &RUN_END);

	INIT_STATE = declparam("INIT_STATE", BASIN, "", "Initial state file (Automation)", INIT_STATE);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("hru_ASL", NHRU, "0.0", "0.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(�)", &hru_ASL);

	hru_names = declparam("hru_names", NHRU, "'HRU'", "HRU names", hru_names);

	basin_name = declparam("basin_name", BASIN, "Basin", "Basin name", basin_name);

	RapidAdvance_to = decldiagparam("RapidAdvance_to", ONE, "' ', ' ', ' '", "Rapid advance to this date formatted as 'mm/dd/yyyy'", RapidAdvance_to);

	Loop_to = decldiagparam("Loop_to", TWO, "' ', ' '", "loop to this date formatted as 'mm/dd/yyyy', 0 - # loops", Loop_to);

	StateVars_to_Update = decldiagparam("StateVars_to_Update", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "run up these state variables.", StateVars_to_Update);

	TraceVars = decldiagparam("TraceVars", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop during run up.", TraceVars);

	// parameters for setsoil

	declparam("soil_Depth_rechr", NHRU, "[0.25]", "0.0", "10.0", "depth of top soil layer", "(m)", &soil_Depth_rechr);

	declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

	declparam("Vol_h2o_content", NHRU, "[0.5]", "0.01", "0.7", "initial volumetric water content", "()", &Vol_h2o_content);

	declparam("soil_type_rechr", NHRU, "[4]", "0", "12",
		"water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
		" 0 - 12", "()", &soiltype_rechr);

	declparam("soil_type", NHRU, "[4]", "0", "12",
		"water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
		" 0 - 12", "()", &soil_type);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion"//
		" of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to "//
		"soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0",
		"Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.",
		"(mm)", &soil_rechr_init);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.",
		"(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "2500.0",
		"Initial value of available water in soil profile.",
		"(mm)", &soil_moist_init);
}

void ClassSetSoil::init(void) {

	float totarea = 0;
	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh)
		totarea += hru_area[hh];

	if (fabs((totarea - basin_area[0]) / basin_area[0]) > 1e-3) {
		const_cast<float *>  (basin_area)[0] = totarea;
		CRHMException TExcept(string("Sum of HRU's area <> Basin area, Basin area made = ") + Convert(totarea).c_str(), WARNING);
		LogError(TExcept);
	}

	//Global::RapidAdvanceTo = 0;
	//Global::LoopTo = 0;
	//Global::LoopCnt = 0;

	//RapidAdvance_to->strings[0] = RapidAdvance_to->strings[0].Trim();
	//if (Loop_to->Count >= 1)
	//	Loop_to->strings[0] = Loop_to->strings[0].Trim();
	//if (Loop_to->Count == 2)
	//	Loop_to->strings[1] = Loop_to->strings[1].Trim();

	//if (!(RapidAdvance_to->strings[0].IsEmpty()))
	//	try {
	//	Global::RapidAdvanceTo = StrToDate(RapidAdvance_to->strings[0]);
	//	if (Loop_to->Count >= 1) {
	//		Global::LoopTo = StrToDate(Loop_to->strings[0]);
	//		if (Loop_to->Count == 2)
	//			Global::LoopCnt = StrToInt(Loop_to->strings[1]);
	//	}

	//}
	//catch (Sysutils::Exception &E) {
	//	CRHMException TExcept("Error in 'RapidAdvance_to' or 'Loop_to' parameters", TERMINATE);
	//	LogError(TExcept);
	//	Global::RapidAdvanceTo = 0;
	//	Global::LoopTo = 0;
	//	Global::LoopCnt = 0;
	//}

	for (hh = 0; chkStruct(); ++hh) {
		float Fract = (Vol_h2o_content[hh] * 1000 - SetSoilproperties[soiltype_rechr[hh]][1]) / SetSoilproperties[soiltype_rechr[hh]][0];
		if (Fract > 1.0)
			Fract = 1.0;
		if (Fract < 0.0)
			Fract = 0.0;

		const_cast<float *> (soil_rechr_init)[hh] = soil_Depth_rechr[hh] * Fract*SetSoilproperties[soiltype_rechr[hh]][0];

		const_cast<float *> (soil_rechr_max)[hh] = soil_Depth_rechr[hh] * SetSoilproperties[soiltype_rechr[hh]][0];

		float Fract2 = (Vol_h2o_content[hh] * 1000 - SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][0];
		if (Fract2 > 1.0)
			Fract2 = 1.0;
		if (Fract2 < 0.0)
			Fract2 = 0.0;

		const_cast<float *> (soil_moist_init)[hh] = soil_Depth[hh] * Fract2*SetSoilproperties[soil_type[hh]][0];

		const_cast<float *> (soil_moist_max)[hh] = soil_Depth[hh] * SetSoilproperties[soil_type[hh]][0];

		if (soil_rechr_init[hh] > soil_moist_init[hh]) // handles approximations
			const_cast<float *> (soil_rechr_init)[hh] = soil_moist_init[hh];

		if (soil_rechr_max[hh] > soil_moist_max[hh]) // handles approximations
			const_cast<float *> (soil_rechr_max)[hh] = soil_moist_max[hh];
	}
}

ClassVolumetric* ClassVolumetric::klone(string name) const {
	return new ClassVolumetric(name);
}

void ClassVolumetric::decl(void) {

	Description = "'Converts soil moisture to volumetric equivalent and determines fall status.'";

	declvar("Volumetric", NHRU, "volumetric soil moisture", "()", &Volumetric);

	declvar("fallstat_V", NHRU, "fallstat_V copy of parameter fallstat", "()", &fallstat_V);

	declvar("Si_V", NHRU, "Si_V copy of parameter Si", "()", &Si_V);

	declparam("soil_type", NHRU, "[4]", "0", "12",
		"water/sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay/pavement" //
		" 0 - 12", "()", &soil_type);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone",
		"(mm)", &soil_moist_max);

	declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

	declparam("Si_correction", NHRU, "[0.0]", "0.0", "1.0", "Si correction number", "()", &Si_correction);

	declparam("set_fallstat", NHRU, "[305]", "0", "366", "set fallstat on this Julian date", "()", &set_fallstat);

	declputparam("*", "Si", "(mm^3/mm^3)", &Si);

	declputparam("*", "fallstat", "(%)", &fallstat);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

}

void ClassVolumetric::init(void) {

	for (hh = 0; chkStruct(); ++hh)
		fallstat_V[hh] = 0.0;
}

void ClassVolumetric::run(void) {

	long nstep = getstep() % Global::Freq;
	long Julian = julian("now"); // same as "decday"

	for (hh = 0; chkStruct(); ++hh) {

		Volumetric[hh] = (soil_moist[hh] / soil_Depth[hh] + SetSoilproperties[soil_type[hh]][1]) / 1000.0;

		if (nstep == 0 && set_fallstat[hh] == Julian || (getstep() == 1 && Julian > set_fallstat[hh])) {
			if (Si) {
				float X = 1.0;
				if (SetSoilproperties[soil_type[hh]][3] > 0.0) {
					X = Volumetric[hh] / SetSoilproperties[soil_type[hh]][3] * 1000.0;
					X = X - Si_correction[hh];
				}
				if (X < 0.0)
					X = 0.0;
				else if (X > 1.0) {
					X = 1.0;
					Si[hh] = X;
					Si_V[hh] = Si[hh];
				}
			}

			if (fallstat) {
				if (SetSoilproperties[soil_type[hh]][3] > 0.0)
					fallstat[hh] = Volumetric[hh] / SetSoilproperties[soil_type[hh]][3] * 100000.0; // ie 100*1000
				else
					fallstat[hh] = 1.0;

				fallstat_V[hh] = fallstat[hh];
			}
		}
	}
}

ClassAnnan* ClassAnnan::klone(string name) const {
	return new ClassAnnan(name);
}

void ClassAnnan::decl(void) {

	Description = "'Estimates incoming short wave radiation from daily minimum and maximum temperatures (Annandale et al. (2001)).' \
                 'outputs observations(QsiA, QsiD and QsiS) with sunshine hours variable (hru_SunAct),' \
                 'outputs variables (QsiA_Var, QsiD_Var and QsiS_Var) with sunshine hours variable (hru_SunAct).'";

	variation_set = VARIATION_ORG;

	declparam("krs", NHRU, "[0.16]", "0.15", "0.2", "location index, interior = 0.16/coastal = 0.19", "()", &krs);
	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);

	declgetvar("*", "QdroDext", "(MJ/m^2*d)", &QdroDext);
	declgetvar("*", "QdflatD", "(MJ/m^2*d)", &QdflatD);
	declgetvar("*", "QdflatE", "(W/m^2)", &QdflatE);
	declgetvar("*", "Qdro", "(W/m^2)", &Qdro);
	declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);
	declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
	declgetvar("*", "SunMax", "(h)", &SunMax);

	declvar("hru_SunAct", NHRU, "Actual Sunshine", "(h)", &hru_SunAct);

	variation_set = VARIATION_0;

	declobs("QsiA", NHRU, "interval synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiA);
	declobs("QsiD", NHRU, "daily synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiD);
	declobs("QsiS", NHRU, "interval synthesized short-wave on slope derived from global and Annandale method", "(W/m^2)", &QsiS);

	variation_set = VARIATION_1;

	declvar("QsiA_Var", NHRU, "interval synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiA_Var);
	declvar("QsiD_Var", NHRU, "daily synthesized short-wave derived from Annandale method", "(W/m^2)", &QsiD_Var);
	declvar("QsiS_Var", NHRU, "synthesized short-wave on slope derived from global and Annandale method", "(W/m^2)", &QsiS_Var);

	variation_set = VARIATION_ORG;
}

void ClassAnnan::init(void) {

	nhru = getdim(NHRU);
}

void ClassAnnan::run(void) {

	float QsiAT, QsiST;

	for (hh = 0; chkStruct(); ++hh) {
		long nstep = getstep() % Global::Freq;

		if (nstep == 1 || Global::Freq == 1) { // beginning of every day

			if (hru_tmax[hh] - hru_tmin[hh] < 0.00001)
				TauAT = 0.0;
			else
				TauAT = krs[hh] * (1.0 + 2.7E-5*hru_elev[hh])*pow(hru_tmax[hh] - hru_tmin[hh], 0.5f);

			QsiDT = QdroDext[hh] * TauAT*MJ_DtoW;

		} // if

		if (variation == VARIATION_ORG || variation == VARIATION_1) {
			if (QdflatE[hh] > 1.0) {
				QsiAT = QdflatE[hh] * TauAT;
				QsiST = (Qdro[hh] + Qdfo[hh])*QsiDT / (MJ_DtoW) / QdflatD[hh]; // on slope simplified
			}
			else {
				QsiAT = 0.0;
				QsiST = 0.0;
			}
		}

		float Ratio;
		float Temp = QsiDT * WtoMJ_D - QdfoD[hh]; // observed direct incoming  - QdfoD[hh]
		if (Temp <= 0.0 || QdflatD[hh] - QdfoD[hh] <= 0.0)
			Ratio = 0.0;
		else {
			Ratio = Temp / (QdflatD[hh] - QdfoD[hh]); // incoming clear sky direct only
			if (Ratio > 1.0)
				Ratio = 1.0;
		}
		hru_SunAct[hh] = Ratio * SunMax[hh];

		switch (variation) {
		case VARIATION_ORG:
			QsiA[hh] = QsiAT;
			QsiS[hh] = QsiST;
			QsiD[hh] = QsiDT;
			break;

		case VARIATION_1:
			QsiA_Var[hh] = QsiAT;
			QsiS_Var[hh] = QsiST;
			QsiD_Var[hh] = QsiDT;
		} // switch
	} // for
}

ClassHeating* ClassHeating::klone(string name) const {
	return new ClassHeating(name);
}

void ClassHeating::decl(void) {

	Description = "'Branch and trunk temperatures in forest (Ellis).'";

	declobs("QLin", NHRU, "incoming calculated long-wave", "(W/m^2)", &QLin);

	declparam("hru_lat", NHRU, "[51.0]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("hru_GSL", NHRU, "[0.0]", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("hru_ASL", NHRU, "[0.0]", "0.0", "360.0", "aspect, 0/90/180/270 - north/east/south/west facing for positive GSL.", "(�)", &hru_ASL);

	declparam("snow_alb", NHRU, "[0.8]", "0.0", "1.0", "snow albedo", "()", &snow_alb);

	declparam("forest_alb", NHRU, "[0.15]", "0.0", "1.0", "forest albedo", "()", &forest_alb);

	declparam("hd1", NHRU, "[1e-5]", "0.0", "1.0", "depth of upper wood heating layer", "(m)", &hd1);

	declparam("hd2", NHRU, "[1e-3]", "0.0", "1.0", "depth of inner wood heating layer", "(m)", &hd2);

	declparam("qt", NHRU, "[0.2]", "0.0", "1.0", "trunk fraction of forest height", "()", &qt);

	declparam("w", NHRU, "[0.8]", "0.0", "1.0", "trunk fraction of forest height", "()", &w);

	declparam("L_B", NHRU, "[0.4]", "0.0", "10.0", "representative branch diameter", "(m)", &L_B);

	declparam("L_T", NHRU, "[0.3]", "0.0", "10.0", "representative trunk diameter", "(m)", &L_T);

	declparam("LAI", NHRU, "[0.3]", "0.0", "10.0", "effective leaf area index", "(m^2/m^2)", &LAI);


	declvar("Qnet_branch", NHRU, "energy balance of branch", "(W/m^2)", &Qnet_branch);

	declvar("Qnet_trunk", NHRU, "energy balance of trunk", "(W/m^2)", &Qnet_trunk);

	declvar("Lnet_branch", NHRU, "longwave cooling of branch", "(W/m^2)", &Lnet_branch);

	declvar("Lnet_trunk", NHRU, "longwave cooling of ", "(W/m^2)", &Lnet_trunk);

	declvar("Hnet_branch", NHRU, "temperature after cooling of branch", "(�C)", &Hnet_branch);

	declvar("Hnet_trunk", NHRU, "temperature after cooling of trunk", "(�C)", &Hnet_trunk);

	declvar("Wnet_branch", NHRU, "energy exchange from heat conduction", "(W/m^2)", &Wnet_branch);

	declvar("Wnet_trunk", NHRU, "energy exchange from heat conduction", "(W/m^2)", &Wnet_trunk);

	decldiag("T1_branch", NHRU, "temperature of branch", "(�C)", &T1_branch);

	decldiag("T1_trunk", NHRU, "temperature of trunk", "(�C)", &T1_trunk);

	decldiag("T2_branch", NHRU, "temperature of branch", "(�C)", &T2_branch);

	decldiag("T2_trunk", NHRU, "temperature of trunk", "(�C)", &T2_trunk);

	decldiag("T3_branch", NHRU, "temperature of branch", "(�C)", &T3_branch);

	decldiag("T3_trunk", NHRU, "temperature of trunk", "(�C)", &T3_trunk);

	declvar("Temp_branch", NHRU, "temperature", "(�C)", &Temp_branch);

	declvar("Temp_trunk", NHRU, "temperature", "(�C)", &Temp_trunk);

	declvar("Temp_forest", NHRU, "temperature", "(�C)", &Temp_forest);

	decldiag("H2_temp_branch", NHRU, "temperature", "(�C)", &H2_temp_branch);

	decldiag("H2_temp_trunk", NHRU, "temperature", "(�C)", &H2_temp_trunk);

	decldiag("H2_temp_trans_branch", NHRU, "temperature of layer h2", "(�C)", &H2_temp_trans_branch);

	decldiag("H2_temp_trans_trunk", NHRU, "temperature of layer h2", "(�C)", &H2_temp_trans_trunk);

	decldiag("Loops", NHRU, "iterative loop count", "()", &Loops);

	declvar("dec", NHRU, "declination", "()", &dec);

	declvar("SElev", NHRU, "sun - level angle", "()", &SElev);

	decldiag("kt", NHRU, "atmosphere transmissivity", "()", &kt);

	decldiag("gcf", NHRU, "geometric correction factor", "()", &gcf);

	declvar("Kd_slope", NHRU, "diffuse shortwave (slope)", "(W/m^2)", &Kd_slope);

	declvar("Kb_slope", NHRU, "beam shortwave (slope)", "(W/m^2)", &Kb_slope);

	declvar("Ko_slope", NHRU, "shortwave (slope)", "(W/m^2)", &Ko_slope);

	decldiag("opl_eff_slope", NHRU, "forest path length", "()", &opl_eff_slope);

	declvar("Ksc_slope", NHRU, "sub-canopy shortwave", "(W/m^2)", &Ksc_slope);

	declvar("Knet_slope", NHRU, "net sub-canopy shortwave", "(W/m^2)", &Knet_slope);

	decldiag("Nu_branch", NHRU, "branch Nusselt number", "()", &Nu_branch);

	decldiag("Nu_trunk", NHRU, "trunk Nusselt number", "()", &Nu_trunk);

	declvar("BranchT_eff", NHRU, "branch temperature", "(�C)", &BranchT_eff);

	declvar("TrunkT_eff", NHRU, "branch temperature", "(�C)", &TrunkT_eff);

	declvar("ForestT_eff", NHRU, "Forest temperature", "(�C)", &ForestT_eff);

	declvar("Lin", NHRU, "long-wave radiance", "(W/m^2)", &Lin);

	declvar("Lin_air", NHRU, "long-wave radiance (forest T = air T)", "(W/m^2)", &Lin_air);

	declvar("Lnet", NHRU, "long-wave radiation", "(W/m^2)", &Lnet);

	declvar("Rnet", NHRU, "all-wave radiation", "(W/m^2)", &Rnet);

	declvar("v", NHRU, "sky view factor", "()", &v);


	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

	declgetvar("*", "hru_Ts", "(�C)", &Ts);
}

void ClassHeating::init(void) {

	for (hh = 0; chkStruct(); ++hh) {
		Lnet_branch[hh] = 0.0;
		Lnet_trunk[hh] = 0.0;
		Hnet_branch[hh] = 0.0;
		Hnet_trunk[hh] = 0.0;
		Wnet_branch[hh] = 0.0;
		Wnet_trunk[hh] = 0.0;
		QLin[hh] = 0.0;
	}
}

void ClassHeating::run(void) {

	for (hh = 0; chkStruct(); ++hh) {
		if (getstep() == 1) { //Here, for the first timestep
			T3_branch[hh] = hru_t[hh];
			T3_trunk[hh] = hru_t[hh];
		}
	}

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {
		// Start calculations-------------------------------------------:

		// compute sky view factor from effective leaf area index (L):
		for (int kk = 1; kk <= 90; ++kk)
			v[hh] += exp(-LAI[hh] / sin((kk*CHAD_constants::DTOR)));

		v[hh] = v[hh] / 90.0; // calculate mean

							  // compute daily hour angle (h):
		float h = 15.0*((((float)nstep / Global::Freq) * 24) - 12)*M_PI / 360;

		// compute solar declination (dec):
		dec[hh] = -23.44*cos((360.0*(Julian("now") + 10.0) / 365.0)*CHAD_constants::DTOR)*CHAD_constants::DTOR;

		// compute sun-slope geometry (for horizontal surface):
		float Hasp = 0;
		float Hslo = 0;

		float Hc1 = -sin(Hasp)*sin(Hslo)*cos(dec[hh]);
		float Hc2 = cos(dec[hh])*(cos(hru_lat[hh] * CHAD_constants::DTOR)*cos(Hslo) - sin(hru_lat[hh] * CHAD_constants::DTOR)*cos(Hasp)*sin(Hslo));
		float Hc3 = sin(dec[hh])*(sin(hru_lat[hh] * CHAD_constants::DTOR)*cos(Hslo) + cos(hru_lat[hh] * CHAD_constants::DTOR)*cos(Hasp)*sin(Hslo));

		// compute cosine b/t sun and normal angle to horizon:
		SElev[hh] = Hc1 * sin(h) + Hc2 * cos(h) + Hc3;

		// the following is a conditional statement restricting variable �SElev� to a minimum of 0.:
		if (SElev[hh] < 0.0) SElev[hh] = 0.0;

		// compute exo-atmospheric shortwave irradiance to level surface [W m-2]:
		float HKex = SElev[hh] * CHAD_constants::solarconst;

		// conditional statement:
		if (HKex < 0.0) HKex = 0.0;

		// compute atmosphere transmissivity:

		kt[hh] = 0.0;
		if (HKex > 0.0)
			kt[hh] = Qsi[hh] / HKex;

		// conditional statement:

		if (kt[hh] > 1.0) kt[hh] = 1.0;
		if (kt[hh] < 0.0) kt[hh] = 0.0;
		if (HKex <= 0.0)  kt[hh] = 0.0;

		// compute diffuse and beam sw irradiance:
		float Kd = Qsi[hh] * (1 - kt[hh]);   	//diffuse sw
		float Kb = Qsi[hh] - Kd;   	//beam sw

									// compute sun-slope geometry to sloped surface:
		float SFasp = hru_ASL[hh] * CHAD_constants::DTOR;
		float SFslo = hru_GSL[hh] * CHAD_constants::DTOR;

		float SF1 = -sin(SFasp)*sin(SFslo)*cos(dec[hh]);
		float SF2 = cos(dec[hh])*(cos(hru_lat[hh] * CHAD_constants::DTOR)*cos(SFslo) - sin(hru_lat[hh] * CHAD_constants::DTOR)*cos(SFasp)*sin(SFslo));
		float SF3 = sin(dec[hh])*(sin(hru_lat[hh] * CHAD_constants::DTOR)*cos(SFslo) + cos(hru_lat[hh] * CHAD_constants::DTOR)*cos(SFasp)*sin(SFslo));

		// compute cosine b/t sun and normal angle to slope:
		float SF4 = SF1 * sin(h) + SF2 * cos(h) + SF3;

		if (SF4 <= 0.0) SF4 = 0.0;

		//compute geometric correction factor for slope (w.r.t. level surface):
		if (SElev[hh] > 0.0)
			gcf[hh] = SF4 / SElev[hh];
		else
			gcf[hh] = 5.0;

		//conditional statement:
		if (SElev[hh] <= 0.0) gcf[hh] = 0.0;
		if (gcf[hh] <= 0.0) gcf[hh] = 0.01;
		if (gcf[hh] > 5.0) gcf[hh] = 5.0;  // set gcf max to 5.

										   // compute above-canopy beam and diffuse SW to slope---:
										   // compute fraction of diffuse sw (Kd) lost to self-shading by slope:
		float slope_shade = 1.0 - hru_GSL[hh] / 180;

		// compute diffuse sw irradiance to slope [W m-2]:
		Kd_slope[hh] = Kd * slope_shade;

		// compute beam sw irradiance to slope [W m-2]:
		Kb_slope[hh] = gcf[hh] * Kb;

		// compute total sw irradiance to slope [W m-2]:
		Ko_slope[hh] = Kd_slope[hh] + Kb_slope[hh];

		// conditional statement:
		if (Ko_slope[hh] < 0.0) Ko_slope[hh] = 0;

		//----------Sub-canopy shortwave transmission calculations-----------
		// compute optical pathlength (opl) for beam irradiance for level and sloped forests:
		float opl_beam_level = LAI[hh] / sin(SElev[hh] + 1e-10);  		//level forest
		float opl_beam_slope = opl_beam_level / gcf[hh];  			//sloped forest

																	// compute optical pathlength (opl) (relative to 1L):
		float opl_diffuse = -log(v[hh]) / LAI[hh];

		// compute the effective (eff) optical pathlength for total sw irradiance (relative to 'L') [ ]:
		opl_eff_slope[hh] = (1 - kt[hh])*opl_diffuse + kt[hh] * opl_beam_slope;
		if (opl_eff_slope[hh] > 50)
			opl_eff_slope[hh] = 50;

		// compute sub-canopy shortwave irradiance for 1 pass through forest [W m-2]:
		Ksc_slope[hh] = Ko_slope[hh] * exp(-LAI[hh] * opl_eff_slope[hh]);

		// compute the proportion of multiple sw reflections [ ]:
		float mult_refl = 1 / (1 - snow_alb[hh] * forest_alb[hh] * (1 - v[hh]));

		// compute net sub-canopy shortwave radiation (w/ enhancement from multiple forest reflections) [W m-2]:
		Knet_slope[hh] = Ksc_slope[hh] * mult_refl*(1 - snow_alb[hh]);

		// compute Reynolds number of within-canopy air flow:
		float Re = CHAD_constants::pa*hru_u[hh] * L_T[hh] / CHAD_constants::dv;            	 	//Reynolds number (trunk)
		float Re_branch = CHAD_constants::pa*hru_u[hh] * L_B[hh] / CHAD_constants::dv;      	//Reynolds number (branch);
		float Pr = (CHAD_constants::kv / CHAD_constants::dh);                		//Prandtl number
		float Pe = Re * Pr;                 		//Peclet number

													// compute Nusselt number to index convective-to-conductive heat transfer:
													// Churchill-Bernstein equation for flow across cylinders:
		Nu_trunk[hh] = 0.3 + (0.62*pow(Re, 0.5)*pow(Pr, 0.33)) / (pow(1 + pow(0.4 / Pr, 0.66), 0.25)*pow(1 + pow(Re / 282000, 0.625), 0.8));

		// Michaetz and Johnson (2006) equation for P. contorta branch:
		Nu_branch[hh] = 0.044*pow(Re_branch, 0.714);

		// Here, for the first timestep�
		Temp_branch[hh] = hru_t[hh];
		Temp_trunk[hh] = hru_t[hh];

		H2_temp_branch[hh] = hru_t[hh];
		H2_temp_trunk[hh] = hru_t[hh];

		float Last_Temp_branch;
		float Last_Temp_trunk;
		Loops[hh] = 0;

		// --------- Beginning of iterative loop (calculate the following in a loop for every second of each
		do {
			Last_Temp_branch = Temp_branch[hh];
			Last_Temp_trunk = Temp_trunk[hh];

			// compute the energy balance of branch and trunk components:
			Qnet_branch[hh] = Qsi[hh] * (1 - forest_alb[hh]);
			Qnet_trunk[hh] = Qsi[hh] * (1 - forest_alb[hh]);

			// calculate the heating from energy to layer h1:
			T1_branch[hh] = Last_Temp_branch + Qnet_branch[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);
			T1_trunk[hh] = Last_Temp_trunk + Qnet_trunk[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);

			// compute the longwave cooling of h1:
			Lnet_branch[hh] = 4 * CHAD_constants::emm*CHAD_constants::sbc*pow(hru_t[hh] + 273.15, 3)*(T1_branch[hh] - hru_t[hh]);
			Lnet_trunk[hh] = 4 * CHAD_constants::emm*CHAD_constants::sbc*pow(hru_t[hh] + 273.15, 3)*(T1_trunk[hh] - hru_t[hh]);

			// compute temperature after longwave cooling:
			T2_branch[hh] = T1_branch[hh] - Lnet_branch[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);
			T2_trunk[hh] = T1_trunk[hh] - Lnet_trunk[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);

			// compute cooling from sensible heat loss:
			Hnet_branch[hh] = CHAD_constants::tca*Nu_branch[hh] * (T2_branch[hh] - hru_t[hh]);
			Hnet_trunk[hh] = CHAD_constants::tca*Nu_trunk[hh] * (T2_trunk[hh] - hru_t[hh]);

			// compute temperature after cooling from sensible heat loss:
			T3_branch[hh] = T2_branch[hh] - Hnet_branch[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);
			T3_trunk[hh] = T2_trunk[hh] - Hnet_trunk[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);

			// compute energy exchange from heat conduction b/t h1 and h2:
			Wnet_branch[hh] = (T3_branch[hh] - H2_temp_branch[hh]) / (0.5*hd1[hh] + 0.5*hd2[hh])*CHAD_constants::kf; // (from previous timestep))

			Wnet_trunk[hh] = (T3_trunk[hh] - H2_temp_trunk[hh]) / (0.5*hd1[hh] + 0.5*hd2[hh])*CHAD_constants::kf; // (from previous timestep))

																												  //compute temperature after cooling from heat conduction to h1:
			Temp_branch[hh] = T3_branch[hh] - Wnet_branch[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);
			Temp_trunk[hh] = T3_trunk[hh] - Wnet_trunk[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd1[hh]);

			// compute temperature transfer b/t h1 and h2:
			H2_temp_trans_branch[hh] = Wnet_branch[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd2[hh]);
			H2_temp_trans_trunk[hh] = Wnet_trunk[hh] / (CHAD_constants::cf * CHAD_constants::pf * hd2[hh]);

			// compute the temperature of layer h2:
			H2_temp_branch[hh] = H2_temp_branch[hh] + H2_temp_trans_branch[hh]; // (from previous timestep)
			H2_temp_trunk[hh] = H2_temp_trunk[hh] + H2_temp_trans_trunk[hh]; // (from previous timestep)

			if (Loops[hh] % 20 == 1) LogMessage(Loops[hh], "", Last_Temp_branch, Temp_branch[hh], Wnet_branch[hh], TT); // ---------- End of iterative loop
		} while (++Loops[hh] < 900 || (fabs(Last_Temp_branch - Temp_branch[hh]) > 0.0001 || fabs(Last_Temp_trunk - Temp_trunk[hh]) > 0.0001) && ++Loops[hh] < 1000);

		float Prob_forest = exp(-(LAI[hh] + (opl_eff_slope[hh] * LAI[hh] - LAI[hh])));
		float Prob_branch = w[hh] * exp(-(LAI[hh] + (opl_eff_slope[hh] * LAI[hh] - LAI[hh])*(1 - qt[hh])));
		float Prob_trunk = Prob_forest - Prob_branch * (1 - qt[hh]);

		BranchT_eff[hh] = hru_t[hh] + (Temp_branch[hh] * Prob_branch);
		TrunkT_eff[hh] = hru_t[hh] + (Temp_trunk[hh] * Prob_trunk);

		ForestT_eff[hh] = (BranchT_eff[hh] + TrunkT_eff[hh]) / 2;

		Lin[hh] = Qli[hh] * v[hh] + (1 - v[hh])*CHAD_constants::emm*CHAD_constants::sbc*pow(ForestT_eff[hh] + 273.15, 4);

		QLin[hh] = Lin[hh];

		Lin_air[hh] = Qli[hh] * v[hh] + (1 - v[hh])*CHAD_constants::emm*CHAD_constants::sbc*pow(hru_t[hh] + 273.15, 4);

		Lnet[hh] = Lin[hh] - CHAD_constants::emm*CHAD_constants::sbc*pow(Ts[hh] + 273.15, 4);

		Rnet[hh] = Knet_slope[hh] + Lnet[hh];
	}
}

Classcalcsun* Classcalcsun::klone(string name) const {
	return new Classcalcsun(name);
}

void Classcalcsun::decl(void) {

	Description = "'Calculates sunshine hours to replace field data', \
                 'Use actual sunshine hours or estimate from Qsi(W/m^2) when sunshine hours not available', \
                 'Use input Qsi (W/m^2) to estimate sunshine hours,' \
                 'Use input daily short-wave radiation observation(QsiD_Obs (W/m^2)), ' \
                 'Use input daily short-wave radiation variable (QsiD_Var (W/m^2)).'";

	variation_set = VARIATION_0;

	declreadobs("SunAct", NHRU, "sunshine hours", "(h)", &SunAct, HRU_OBS_Q, true); // must check for NULL


	variation_set = VARIATION_0 + VARIATION_1;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, true); // must check for NULL

	declobsfunc("Qsi", "Qsitot", &Qsitot, DTOT, NULL, true); // must check for NULL

	variation_set = VARIATION_2;

	declreadobs("QsiD_Obs", NHRU, "daily short-wave", "(W/m^2)", &QsiD_Obs, HRU_OBS_Q);


	variation_set = VARIATION_3;

	declgetvar("*", "QsiD_Var", "(W/m^2)", &QsiD_Var);


	variation_set = VARIATION_ORG;

	declgetvar("*", "QdflatD", "(MJ/m^2*d)", &QdflatD);
	declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
	declgetvar("*", "SunMax", "(h)", &SunMax);

	declvar("hru_SunAct", NHRU, "Actual Sunshine", "(h)", &hru_SunAct);
}

void Classcalcsun::init(void) {
	nhru = getdim(NHRU);

	switch (variation) {

	case VARIATION_ORG:
		if (SunAct == NULL) {
			CRHMException TExcept(string("'" + Name + " (calcsun)' sunshine hours observation missing. Using Qsi instead.").c_str(), WARNING);
			LogError(TExcept);

			if (Qsi == NULL || Qsitot == NULL) {
				CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TERMINATE);
				LogError(TExcept);
			}
		}
		break;

	case VARIATION_1:
		if (Qsi == NULL || Qsitot == NULL) {
			CRHMException TExcept(string("'" + Name + " (calcsun)' Qsi interval observation missing.").c_str(), TERMINATE);
			LogError(TExcept);
		}
		break;

	case VARIATION_2:
		if (QsiD_Obs == NULL) {
			CRHMException TExcept(string("'" + Name + " (calcsun)' QsiD_Obs daily observation missing.").c_str(), TERMINATE);
			LogError(TExcept);
		}
	} // switch
}

void Classcalcsun::run(void) {

	try
	{
		float Temp = 0, Ratio = 0;

		long nstep = getstep() % Global::Freq;

		if (nstep == 1 || Global::Freq == 1) { // beginning of every day

			for (hh = 0; chkStruct(); ++hh) {

				switch (variation) {

				case VARIATION_ORG:
					if (SunAct) {
						hru_SunAct[hh] = SunAct[hh];
						Temp = -9999;
						break;
					}
					// fall through
				case VARIATION_1:
					try
					{
						if (Qsitot != NULL && QdfoD != NULL) // added by Manishankar Mondal
						Temp = Qsitot[hh] * WtoMJ_D / Global::Freq - QdfoD[hh]; // observed direct incoming  - QdfoD[hh]
					}
					catch (...) {}
					break;

				case VARIATION_2:
					if (QsiD_Obs != NULL && QdfoD != NULL) // added by Manishankar Mondal
					Temp = QsiD_Obs[hh] * WtoMJ_D - QdfoD[hh]; // observed daily direct incoming  - QdfoD[hh]
					break;

				case VARIATION_3:
					if (QsiD_Var != NULL && QdfoD != NULL) // added by Manishankar Mondal
					Temp = QsiD_Var[hh] * WtoMJ_D - QdfoD[hh]; // variable daily direct incoming  - QdfoD[hh]
					break;

				default:
					CRHMException TExcept(string("'" + Name + " (variation)' 'variation not defined.").c_str(), TERMINATE);
					LogError(TExcept);
				} // switch

				if (Temp != -9999) {
					if (Temp <= 0.0 || QdflatD[hh] - QdfoD[hh] <= 0.0)
						Ratio = 0.0;
					else {
						Ratio = Temp / (QdflatD[hh] - QdfoD[hh]); // incoming clear sky direct only
						if (Ratio > 1.0)
							Ratio = 1.0;
					}

					if (hru_SunAct != NULL && SunMax != NULL)
					hru_SunAct[hh] = Ratio * SunMax[hh];
				}
			} // for
		} // beginning of every day
	}
	catch (exception &E)
	{
		//---------------------
	}
}
//==============================================================================


ClassObstoPar* ClassObstoPar::klone(string name) const {
	return new ClassObstoPar(name);
}

void ClassObstoPar::decl(void) {

	Description = "'Every interval sets the parameter specified in parameter \"par_name\"to the value of the observation specified in parameter \"obs_name\".'";

	obs_name = declparam("obs_name", BASIN, "default_obs", "observation name", obs_name);

	par_name = declparam("par_name", BASIN, "default_par", "parameter name", par_name);

	/*if (par_name)
	declputparam("*", (par_name->strings[0]).c_str(), "(m)", &Ht);


	if (obs_name)
	declreadobs((obs_name->strings[0]).c_str(), NHRU, "height observation", "(m)", &Ht_obs);
	*/
	decldiag("Ht_var", NHRU, "variable name", "()", &Ht_var);
}

void ClassObstoPar::init(void) {
	nhru = getdim(NHRU);

	if (Ht_obs == NULL) {
		CRHMException TExcept("\"Ht_obs\". No observation vegetation height data!  Using constant parameter value instead.", WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {
		Ht_var[hh] = Ht[hh];
	}
}

void ClassObstoPar::run(void) {
	if (Ht_obs != NULL)
		for (hh = 0; chkStruct(); ++hh) {
			float H = Ht_obs[hh];
			if (H < 0.001)
				H = 0.001;
			//      const_cast<float *> (Ht) [hh] = H;
			Ht[hh] = H;
			Ht_var[hh] = Ht[hh];
		}
}

void ClassObstoPar::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "'" + Name + " (Ht_obs)' ";
		LogMessage(hh, s.c_str());
		LogDebug(" ");
	}
}

ClassPrairieInfil* ClassPrairieInfil::klone(string name) const {
	return new ClassPrairieInfil(name);
}

void ClassPrairieInfil::decl(void) {

	Description = "'Handles frozen soil infiltration using Granger et al. 1984; Gray et al., 1986 and Ayers, 1959 for unfrozen soil.'";

	declvar("snowinfil", NHRU, "infiltration", "(mm/d)", &snowinfil);

	declstatdiag("cumsnowinfil", NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/d)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

	declvar("infil", NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	declstatvar("crackstat", NHRU, "infiltration status", "()", &crackstat);

	declstatdiag("RainOnSnow", NHRU, "cumulative rain on snow", "(mm)", &RainOnSnow);

	declstatvar("crackon", NHRU, "crack cycle enabled", "()", &crackon);


	declstatdiag("RainOnSnowA", NHRU, "accumulated rain on snow", "(mm)", &RainOnSnowA);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("fallstat", NHRU, "[50.0]", "-1.0", "100.0",
		"fall status 0.0 - unlimited/ 100.0 - restricted/ other - limited", "(%)", &fallstat);

	declparam("Major", NHRU, "[5]", "1", "100", "threshold for major melt", "(mm/d)", &Major);

	declparam("PriorInfiltration", NHRU, "[1]", "0", "1", "allow limited melt to infiltrate prior to first major melt", "(mm/d)", &PriorInfiltration);

	declparam("texture", NHRU, "[1]", "1", "4",
		"texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

	declparam("groundcover", NHRU, "[1]", "1", "6",
		"groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "snowmeltD", "(mm/d)", &snowmelt);
	declgetvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "net_rain", "(mm/int)", &net_rain);
}

void ClassPrairieInfil::init(void) {

	nhru = getdim(NHRU);

	try {

		Xinfil = new float*[3];   // Data [3] [nhru]
		for (int jj = 0; jj < 3; ++jj)
			Xinfil[jj] = new float[nhru];

		timer = new long[nhru];
	}
	catch (std::bad_alloc) {
		CRHMException Except("Could not allocate in module CRACK.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	for (hh = 0; chkStruct(); ++hh) { // every interval
		infil[hh] = 0.0;
		cuminfil[hh] = 0.0;
		snowinfil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		runoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		meltrunoff[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;

		RainOnSnow[hh] = 0.0;
		RainOnSnowA[hh] = 0.0;

		crackon[hh] = false;
		crackstat[hh] = 0;

		timer[hh] = 0;
		Xinfil[0][hh] = 0.0;
		Xinfil[1][hh] = 0.0;
		Xinfil[2][hh] = 0.0;
	}
}

float textureproperties[][6] = { // mm/hour
	{ 7.6, 12.7, 15.2, 17.8, 25.4, 76.2 },  // coarse over coarse
{ 2.5,  5.1,  7.6, 10.2, 12.7,  15.2 }, // medium over medium
{ 1.3,  1.8,  2.5,  3.8,  5.1,  6.4 },  // medium/fine over fine
{ 0.5,  0.5,  0.5,  0.5,  0.5,  0.5 }   // soil over shallow bedrock
};

void ClassPrairieInfil::run(void) {

	long nstep;

	nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // every interval
		infil[hh] = 0.0;
		runoff[hh] = 0.0;

		if (net_rain[hh] > 0.0) {
			if (crackon[hh])
				RainOnSnowA[hh] += net_rain[hh];
			else {
				float maxinfil = textureproperties[texture[hh] - 1][groundcover[hh] - 1] * 24.0 / Global::Freq; // mm/int
				if (maxinfil > net_rain[hh])
					infil[hh] = net_rain[hh];
				else {
					infil[hh] = maxinfil;
					runoff[hh] = net_rain[hh] - maxinfil;
				}

				cuminfil[hh] += infil[hh];
				cumrunoff[hh] += runoff[hh];
			}
		}
	}

	if (nstep == 0) // end of every day
		for (hh = 0; chkStruct(); ++hh) {

			if (SWE[hh] > 25.0 && !crackon[hh]) {
				crackstat[hh] = 0;
				crackon[hh] = true; // initialise for current year
				timer[hh] = 0;
				Xinfil[0][hh] = 0.0;
				Xinfil[1][hh] = 0.0;
				Xinfil[2][hh] = 0.0;
			}

			snowinfil[hh] = 0.0;
			meltrunoff[hh] = 0.0;

			if (crackon[hh] && snowmelt[hh] > 0.0) {

				if (timer[hh] > 0 && crackstat[hh] > 0)

					// ice lens forms, if next day below -10 limited

					if (fallstat[hh] > 0.0 && hru_tmax[0] < -10.0) crackstat[hh] = 10;

				// unlimited - (fallstat[hh].eq.0.0)

				if (fallstat[hh] <= 0.0) {

					snowinfil[hh] = snowmelt[hh];
					crackstat[hh] = 1;
				}

				// limited - (0.0 < fallstat[hh] < 100.0)

				else if (fallstat[hh] < 100.0) {
					if (snowmelt[hh] >= Major[hh] || crackstat[hh] >= 1) {
						if (SWE[hh] > Xinfil[2][hh] && snowmelt[hh] >= Major[hh]) {
							infil_index(fallstat[hh] / 100.0, SWE[hh], Xinfil[0][hh], Xinfil[1][hh]);
							Xinfil[2][hh] = SWE[hh];
						}
						if (snowmelt[hh] >= Major[hh]) {
							if (crackstat[hh] <= 0)
								crackstat[hh] = 1;
							else
								crackstat[hh] = crackstat[hh] + 1;

							timer[hh] = 1;
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];
							if (snowinfil[hh] > Xinfil[1][hh]) snowinfil[hh] = Xinfil[1][hh];
						}
						else
							snowinfil[hh] = snowmelt[hh] * Xinfil[0][hh];

						if (crackstat[hh] > 6)
							snowinfil[hh] = 0;
					}
					else
						if (PriorInfiltration[hh])
							snowinfil[hh] = snowmelt[hh]; // zero by default
				}

				// restricted - (fallstat[hh].ge.100.0)

				else if (fallstat[hh] >= 100.0) {
					snowinfil[hh] = 0.0;
					crackstat[hh] = 1;
				}

				meltrunoff[hh] = snowmelt[hh] - snowinfil[hh];

				if (snowinfil[hh] > 0.0)
					snowinfil[hh] += RainOnSnowA[hh];
				else
					meltrunoff[hh] += RainOnSnowA[hh];

				cumsnowinfil[hh] += snowinfil[hh];
				cummeltrunoff[hh] += meltrunoff[hh];

				RainOnSnow[hh] += RainOnSnowA[hh];
				RainOnSnowA[hh] = 0.0;

			} // end if
			else if (snowmelt[hh] > 0.0) {
				snowinfil[hh] = snowmelt[hh];
				cumsnowinfil[hh] += snowinfil[hh];
			}

			if (crackstat[hh] > 0 && SWE[hh] <= 0.0) {
				crackon[hh] = false;
				crackstat[hh] = 0;
			}
		}   // end for
}

void ClassPrairieInfil::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cumsnowinfil    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cummeltrunoff   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cuminfil(rain)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' cumrunoff(rain) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (PrairieInfiltration)' RainOnSnow      (mm) (mm*hru) (mm*hru/basin): ").c_str(), RainOnSnow[hh], hru_area[hh], basin_area[0], "** information only - amount of rain handled as snow.");
		LogDebug(" ");
	}

	if (Xinfil != NULL) {
		for (int ii = 0; ii < 3; ii++)
			delete[] Xinfil[ii];  //Array [3] [nhru]

		delete[] Xinfil;
		Xinfil = NULL;
	}

	delete[] timer;
	timer = NULL;
}

//==============================================================================

ClassCRHMCanopy* ClassCRHMCanopy::klone(string name) const {
	return new ClassCRHMCanopy(name);
}

void ClassCRHMCanopy::decl(void) {

	Description = "'Prototype all season canopy module. Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), '\
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2), '";

	// Observations

	variation_set = VARIATION_0 + VARIATION_1;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);


	variation_set = VARIATION_0 + VARIATION_2;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


	variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);


	variation_set = VARIATION_2 + VARIATION_3;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);


	variation_set = VARIATION_4;

	declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


	variation_set = VARIATION_ORG;

	// get variables:

	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	declgetvar("*", "hru_rh", "()", &hru_rh);

	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

	declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

	declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

	declgetvar("*", "SolAng", "(r)", &SolAng);

	declgetvar("*", "Albedo", "(r)", &Albedo);

	declputvar("*", "SWE", "(mm)", &SWE);

	// declared observations

	declobs("Ts", NHRU, "snow surface temperature", "(�C)", &Ts);

	declobs("Qnsn", NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn);

	declvar("Qnsn_Var", NHRU, "net all-wave at snow surface", "(W/m^2*int)", &Qnsn_Var);

	declobs("Qsisn", NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn);

	declobs("Qlisn", NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn);

	declobs("Qlosn", NHRU, "reflected long-wave at surface", "(W/m^2)", &Qlosn);

	// declared variables

	decldiag("k", NHRU, "extinction coefficient", "()", &k);

	decldiag("Tauc", NHRU, "short-wave transmissivity", "(W/m^2)", &Tauc);

	decllocal("Pa", NHRU, "Average surface pressure", "(kPa)", &Pa);

	declvar("ra", NHRU, "", "(s/m)", &ra);

	declvar("drip_cpy", NHRU, "canopy drip", "(mm/int)", &drip_Cpy);

	declvar("direct_rain", NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

	declvar("net_rain", NHRU, " direct_rain + drip", "(mm/int)", &net_rain);

	declstatdiag("cum_net_rain", NHRU, " direct_rain + drip", "(mm)", &cum_net_rain);

	declvar("Subl_Cpy", NHRU, "canopy snow sublimation", "(mm/int)", &Subl_Cpy);

	declstatdiag("cum_Subl_Cpy", NHRU, "canopy snow sublimation", "(mm)", &cum_Subl_Cpy);

	decldiag("Pevap", NHRU, "used when ground is snow covered to calculate canopy evaporation (Priestley-Taylor)", "(mm)", &Pevap);

	declstatvar("rain_load", NHRU, "canopy rain load", "(mm)", &rain_load);

	declstatvar("Snow_load", NHRU, "canopy snow load (timetep start)", "(mm)", &Snow_load);

	declvar("direct_snow", NHRU, "snow 'direct' Thru", "(mm/int)", &direct_snow);

	declvar("SUnload", NHRU, "unloaded canopy snow", "(mm)", &SUnload);

	declvar("SUnload_H2O", NHRU, "unloaded canopy snow as water", "(mm)", &SUnload_H2O);

	declstatdiag("cum_SUnload_H2O", NHRU, "Cumulative unloaded canopy snow as water", "(mm)", &cum_SUnload_H2O);

	declstatdiag("cum_SUnload", NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", &cum_SUnload);

	declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

	declstatdiag("cum_net_snow", NHRU, "Cumulative Canopy unload ", "(mm)", &cum_net_snow);

	declvar("net_p", NHRU, "total precipitation after interception", "(mm/int)", &net_p);

	decldiag("u_FHt", NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

	decldiag("Cc", NHRU, "Canopy coverage", "()", &Cc);

	declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);

	declstatdiag("cum_intcp_evap", NHRU, "HRU Evaporation from interception", "(mm)", &cum_intcp_evap);

	declvar("Qsisn_Var", NHRU, "incident short-wave at surface", "(W/m^2*int)", &Qsisn_Var);

	declvar("Qlisn_Var", NHRU, "incident long-wave at surface", "(W/m^2*int)", &Qlisn_Var);


	// parameters:

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "forest/vegetation height", "(m)", &Ht);

	declparam("Zref", NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	declparam("LAI", NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

	declparam("Sbar", NHRU, "[6.6]", "0.0", "100.0", "maximum canopy snow interception load", "(kg/m^2)", &Sbar);

	declparam("Zvent", NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

	declparam("unload_t", NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(�C)", &unload_t);

	declparam("unload_t_water", NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(�C)", &unload_t_water);

	decldiagparam("Alpha_c", NHRU, "[0.1]", "0.05", "0.2", "canopy albedo", "()", &Alpha_c);

	decldiagparam("B_canopy", NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter. Suggestions are Colorado - 0.23 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopy::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRU's to module

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa

		rain_load[hh] = 0.0;
		Snow_load[hh] = 0.0;

		cum_net_snow[hh] = 0.0;
		cum_net_rain[hh] = 0.0;
		cum_Subl_Cpy[hh] = 0.0;
		cum_intcp_evap[hh] = 0.0;
		cum_SUnload_H2O[hh] = 0.0;

		if (Ht[hh] > Zwind[hh]) {
			CRHMException TExcept(string("'" + Name + " (Canopy)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), WARNING);
			LogError(TExcept);
		}
	}
}

void ClassCRHMCanopy::run(void) {

	float Kstar_H;

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Qsi_ = Qsi[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_1:
			Qsi_ = Qsi[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_2:
			Qsi_ = QsiS_Var[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_3:
			Qsi_ = QsiS_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_4:
			Qsi_ = QsiA_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		} // switch

		net_rain[hh] = 0.0;
		direct_rain[hh] = 0.0;
		drip_Cpy[hh] = 0.0;
		intcp_evap[hh] = 0.0;

		net_snow[hh] = 0.0;
		direct_snow[hh] = 0.0;
		SUnload[hh] = 0.0;
		SUnload_H2O[hh] = 0.0;
		Subl_Cpy[hh] = 0.0;

		// Canopy temperature is approximated by the air temperature.

		float T1 = hru_t[hh] + CRHM_constants::Tm;

		float Exposure = Ht[hh] - DepthofSnow(SWE[hh]); // depths(m) SWE(mm) 
		if (Exposure < 0.0)
			Exposure = 0.0;

		float LAI_ = LAI[hh] * Exposure / Ht[hh];

		float Vf = 0.45 - 0.29*log(LAI[hh]);

		float Vf_ = Vf + (1.0 - Vf)*sin((Ht[hh] - Exposure) / Ht[hh] * M_PI_2);

		if (SolAng[hh] > 0.001) {
			k[hh] = 1.081*SolAng[hh] * cos(SolAng[hh]) / sin(SolAng[hh]);
			Tauc[hh] = exp(-k[hh] * LAI_);
		}
		else {
			k[hh] = 0.0;
			Tauc[hh] = 0.0;
		}


		Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh]));

		Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f) + B_canopy[hh] * Kstar_H;

		Qlisn_Var[hh] = Qlisn[hh];

		Qsisn[hh] = Qsi_ * Tauc[hh];

		Qsisn_Var[hh] = Qsisn[hh];


		float rho = Pa[hh] * 1000 / (CRHM_constants::Rgas*T1);

		float U1 = hru_u[hh]; // Wind speed (m/s)

		ra[hh] = (log(Zref[hh] / Z0snow[hh])*log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

		float deltaX = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas*sqr(T1));

		float q = (hru_rh[hh] / 100)*Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)


		Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_ - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho / ra[hh]) /
			(4 * CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*deltaX)*rho / ra[hh]);

		Ts[hh] -= CRHM_constants::Tm;

		if (Ts[hh] > 0.0 || SWE[hh] <= 0.0)
			Ts[hh] = 0.0;

		Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

		Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

		Qnsn_Var[hh] = Qnsn[hh];

		//==============================================================================
		// coupled forest snow interception and sublimation routine:
		// after Hedstom & Pomeroy / Parviainen & Pomeroy:
		// calculate maximum canopy snow load (L*):

		if (Snow_load[hh] > 0.0 || hru_snow[hh] > 0.0) { // handle snow
			float RhoS = 67.92 + 51.25* exp(hru_t[hh] / 2.59);
			float LStar = Sbar[hh] * (0.27 + 46.0 / RhoS)* LAI[hh];

			if (Snow_load[hh] > LStar) { // after increase in temperature
				direct_snow[hh] = Snow_load[hh] - LStar;
				Snow_load[hh] = LStar;
			}

			// calculate intercepted snowload

			if (Ht[hh] - 2.0 / 3.0*Zwind[hh] > 1.0)
				u_FHt[hh] = hru_u[hh] * log((Ht[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]);
			else
				u_FHt[hh] = 0.0;

			double I1 = 0.0;

			if (hru_snow[hh] > 0.0) {
				if (fabs(hru_snow[hh] / LStar) < 50.0) {
					if (u_FHt[hh] <= 1.0)  // if wind speed at canopy top > 1 m/s
						I1 = (LStar - Snow_load[hh])*(1.0 - exp(-Cc[hh] * hru_snow[hh] / LStar));
					else
						I1 = (LStar - Snow_load[hh])*(1.0 - exp(-hru_snow[hh] / LStar));

					if (I1 <= 0)
						I1 = 0;

					Snow_load[hh] += I1;
				}

				// calculate canopy snow throughfall before unloading:

				direct_snow[hh] += (hru_snow[hh] - I1);
			}

			// calculate snow ventilation windspeed:

			const float gamma = 1.15;
			float xi2 = 1 - Zvent[hh];
			float windExt2 = (gamma * LAI[hh] * xi2);

			float uVent = u_FHt[hh] * exp(-1 * windExt2);

			//=============================================================================
			const float AlbedoIce = 0.8;       // albedo of ideal ice sphere
			const float Radius = 5.0e-4;       // radii of single 'ideal' ice sphere in, m)
			const float KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
			const float ks = 0.0114;           // snow shape coefficient for jack pine
			const float Fract = 0.37;          // fractal dimension of intercepted snow
			const float ci = 2.102e-3;         // heat capacity of ice (MJ/kg/K)
			const float Hs = 2.838e6;          // heat of sublimation (MJ/kg)
											   //==============================================================================

											   // calculate sublimation of intercepted snow from ideal intercepted ice sphere (500 microns diameter):

			float Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;

			float Es = 611.15f * exp(22.452f*hru_t[hh] / (hru_t[hh] + 273.0f));  // {sat pressure}

			float SvDens = Es * PBSM_constants::M / (PBSM_constants::R*(hru_t[hh] + 273.0f)); // {sat density}

			Lamb = 6.3e-4*(hru_t[hh] + 273.0) + 0.0673;  // thermal conductivity of atmosphere
			Nr = 2.0 * Radius * uVent / KinVisc;  // Reynolds number
			Nu = 1.79 + 0.606 * sqrt((float)Nr); // Nusselt number
			SStar = M_PI * sqr(Radius) * (1.0f - AlbedoIce) * Qsi_;  // SW to snow particle !!!! changed
			A1 = Lamb * (hru_t[hh] + 273) * Nu;
			B1 = Hs * PBSM_constants::M / (PBSM_constants::R * (hru_t[hh] + 273.0f)) - 1.0;
			J = B1 / A1;
			Sigma2 = hru_rh[hh] / 100 - 1;
			D = 2.06e-5* pow((hru_t[hh] + 273.0f) / 273.0f, -1.75f); // diffusivity of water vapour
			C1 = 1.0 / (D*SvDens*Nu);

			Alpha = 5.0;
			Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Radius*Radius*Radius *(1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

			// sublimation rate of single 'ideal' ice sphere:

			float Vs = (2.0* M_PI* Radius*Sigma2 - SStar * J) / (Hs* J + C1) / Mpm;

			// snow exposure coefficient (Ce):

			float Ce;
			if ((Snow_load[hh] / LStar) <= 0.0)
				Ce = 0.07;
			else
				Ce = ks * pow((Snow_load[hh] / LStar), -Fract);

			// calculate 'potential' canopy sublimation:

			float Vi = Vs * Ce;

			// limit sublimation to canopy snow available and take sublimated snow away from canopy snow at timestep start

			Subl_Cpy[hh] = -Snow_load[hh] * Vi*Global::Interval * 24 * 3600; // make W/m2
			if (Subl_Cpy[hh] > Snow_load[hh]) {
				Subl_Cpy[hh] = Snow_load[hh];
				Snow_load[hh] = 0.0;
			}
			else {
				Snow_load[hh] -= Subl_Cpy[hh];
				if (Snow_load[hh] < 0.0)
					Snow_load[hh] = 0.0;
			}

			// calculate 'ice-bulb' temperature of intercepted snow:

			float IceBulbT = hru_t[hh] - (Vi* Hs / 1e6 / ci);
			float Six_Hour_Divisor = Global::Freq / 4.0; // used to unload over 6 hours

			const float c = 0.678 / (24 * 7 * 24 / Global::Freq); // weekly dimensionless unloading coefficient -> to CRHM time interval

																  // determine whether canopy snow is unloaded:

			if (IceBulbT >= unload_t_water[hh]) {
				drip_Cpy[hh] = Snow_load[hh] / Six_Hour_Divisor;
				SUnload_H2O[hh] = drip_Cpy[hh];
				Snow_load[hh] -= SUnload_H2O[hh];
				cum_SUnload_H2O[hh] += SUnload_H2O[hh];
			}
			else if (IceBulbT >= unload_t[hh]) {
				SUnload[hh] = Snow_load[hh] / Six_Hour_Divisor;
				Snow_load[hh] -= SUnload[hh];
				cum_SUnload[hh] += SUnload[hh];
			}
			else if (IceBulbT < unload_t[hh]) { // has to be at least one interval. Trip on half step
				SUnload[hh] = Snow_load[hh] * c; // the dimensionless unloading coefficient already /interval
				if (SUnload[hh] > Snow_load[hh]) {
					SUnload[hh] = Snow_load[hh];
					Snow_load[hh] = 0.0;
				}
				else
					Snow_load[hh] -= SUnload[hh];

				cum_SUnload[hh] += SUnload[hh];
			}

			// calculate total sub-canopy snow:

			net_snow[hh] = direct_snow[hh] + SUnload[hh];

		} // handle snow

		  // calculate horizontal canopy-coverage (Cc):

		Cc[hh] = 0.29 * log(LAI[hh]) + 0.55;
		if (Cc[hh] <= 0.0)
			Cc[hh] = 0.0;

		float smax = Cc[hh] * LAI[hh] * 0.2;

		//  Forest rain interception and evaporation model
		// 'sparse' Rutter interception model (i.e. Valente 1997):

		// calculate direct throughfall:

		if (hru_rain[hh] > 0.0) {

			direct_rain[hh] = hru_rain[hh] * (1 - Cc[hh]);

			// calculate rain accumulation on canopy before evap loss:

			if (rain_load[hh] + hru_rain[hh] * Cc[hh] > smax) {
				drip_Cpy[hh] += (rain_load[hh] + hru_rain[hh] * Cc[hh] - smax);
				rain_load[hh] = smax;
			}
			else
				rain_load[hh] += hru_rain[hh] * Cc[hh];

		}

		// calculate 'actual evap' of water from canopy and canopy storage after evaporation::

		if (rain_load[hh] > 0.0) {
			if (inhibit_evap[hh] == 0) { // use Granger when no snowcover
				if (rain_load[hh] >= hru_evap[hh] * Cc[hh]) { // (evaporation in mm)
					intcp_evap[hh] = hru_evap[hh] * Cc[hh];  //
					rain_load[hh] -= hru_evap[hh] * Cc[hh];
				}
				else {
					intcp_evap[hh] = rain_load[hh];
					rain_load[hh] = 0.0;
				}
			}
			else { // use Priestley-Taylor when snowcover
				float Q = Qsi_ * 86400 / Global::Freq / 1e6 / lambda(hru_t[hh]); // convert w/m2 to mm/m^2/int

				if (Qsi_ > 0.0)
					Pevap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
				else
					Pevap[hh] = 0.0;

				if (rain_load[hh] >= Pevap[hh] * Cc[hh]) {  // (evaporation in mm)
					intcp_evap[hh] = Pevap[hh] * Cc[hh];  // check
					rain_load[hh] -= Pevap[hh] * Cc[hh];
				}
				else {
					intcp_evap[hh] = rain_load[hh]; // check
					rain_load[hh] = 0.0;
				}
			}
		} // if rain_load[hh] > 0.0

		  // cumulative amounts....

		net_rain[hh] = direct_rain[hh] + drip_Cpy[hh];
		net_p[hh] = net_rain[hh] + net_snow[hh];

		cum_net_rain[hh] += net_rain[hh];
		cum_net_snow[hh] += net_snow[hh];
		cum_intcp_evap[hh] += intcp_evap[hh];
		cum_Subl_Cpy[hh] += Subl_Cpy[hh];

	} // end for
}

void ClassCRHMCanopy::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (canopy)'  cum_net_snow    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_snow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (canopy)'  cum_net_rain    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_rain[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (canopy)'  cum_Subl_Cpy    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Subl_Cpy[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (canopy)'  cum_intcp_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (canopy)'  cum_SUnload_H2O (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_SUnload_H2O[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassCRHMCanopy::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

float ClassCRHMCanopy::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassCRHMCanopy::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float ClassCRHMCanopy::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R = 2870;
	return (1E4*Pa / (R*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

ClassPSPnew* ClassPSPnew::klone(string name) const {
	return new ClassPSPnew(name);
}

void ClassPSPnew::decl(void) {

	declvar("Qsubl", NHRU, "Canopy sublimation", "(mm/int)", &Qsubl);

	declvar("SnowLoad", NHRU, "Canopy snow load", "(kg/m^2)", &Load);

	declvar("Thru", NHRU, "Canopy fall through", "(kg/m^2)", &Thru);

	declvar("TCanSnow", NHRU, "snow Canopy temperature", "(�C)", &TCanSnow);

	declvar("Tbiomass", NHRU, "biomass temperature", "(�C)", &Tbiomass);


	declparam("InitN", NHRU, "0", "0", "200", "Number of periods before calculating sublimation", "()", &InitN);

	declparam("Sbar", NHRU, "6.6", "0.0", "20.0", "Uncorrected snow capacity", "(kg/m^2)", &Sbar);

	declparam("LAI", NHRU, "2.2", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

	declparam("Zcan", NHRU, "16", "0.0", "30.0", "Mid-canopy wind modelling height", "(m)", &Zcan);

	declparam("Zref", NHRU, "27", "0.0", "40.0", "Reference height", "(m)", &Zref);

	declparam("Ht", NHRU, "[20.0]", "0.001", "100.0", "Canopy height", "(m)", &Ht);

	declparam("Biomass", NHRU, "30.0", "0.0", "100.0", "Biomass", "(kg/m^2)", &Biomass);

	declparam("k", NHRU, "0.0113", "0.0", "1.0", "Snow shape coefficient", "()", &k);

	declparam("HeightH", NHRU, "20", "0.0", "100.0", "Canopy height", "(m)", &HeightH);

	declparam("WidthJ", NHRU, "75", "0.0", "100.0", "Canopy ", "(m)", &WidthJ);

	declgetvar("obs", "hru_u", "(m/s)", &hru_u);
	declgetvar("obs", "hru_t", "(�C)", &TAref);
	declgetvar("obs", "hru_rh", "(%)", &RHref);
	declgetvar("obs", "hru_p", "(mm/int)", &hru_p);
	declgetvar("*", "SolAng", "(r)", &SolarAng);

	declreadobs("TsnowG", NHRU, "snow temperature", "(�C)", &TsnowG, HRU_OBS_misc);
	declreadobs("Lnot", NHRU, "tree weight", "(kg/m^2)", &Lnot, HRU_OBS_misc);
	declreadobs("Qsi", NHRU, "Qsi", "(W/m^2)", &QsIn, HRU_OBS_Q);
	declreadobs("Qso", NHRU, "Qso", "(W/m^2)", &QsOut, HRU_OBS_Q);

}

void ClassPSPnew::init(void) {

	nhru = getdim(NHRU);

	T0CanSnow = new float[nhru];
	T0biomass = new float[nhru];

	for (long hh = 0; hh < nhru; hh++) {
		Qsubl[hh] = 0.0;
		Load[hh] = 0.0;
		Thru[hh] = 0.0;
	}
}

float SatVP(float Temp) /* outputs sat. vapor pressure, Pa */
{
	if (Temp > 0.0)  return 611.0*exp(17.27*Temp / (Temp + 237.3));
	else return 611.0*exp(21.88*Temp / (Temp + 265.5));
}

void ClassPSPnew::run(void) {

	const float GapFrac = 0.16;      /* Canopy gap fraction */
	const float UpperGF = 0.58;      /* Mid-canopy level gap fraction */
	const float Radius = 0.0005;    /* Ice sphere radius, metres */
	const float KinVisc = 1.88E-5;   /* Kinematic viscosity of air (Sask. avg. value) */
	const float R = 8313.0;          /* Universal gas constant, J/(mole*K) */
	const float M = 18.01;           /* Molecular weight of water */
	const float RhoI = 900.0;        /* Density of ice, kg/m^3 */
	const float k1 = 0.0114;         /* Snow shape coefficient, Jackpine site */
	const float Fract = 0.4;         /* Fractal dimension */
	const float SnowAlb = 0.8;       /* Albedo for snow */
	const float CanAlb = 0.2;        /* Albedo for canopy */
	const float KARMAN = 0.4;        /* Von Karman"s constant */
	const float g = 9.8;             /* Gravitational acceleration, m/s^2 */
	const float SBC = 5.67E-8;       /* Stephan-Boltzmann constant W/m2*/
	const float SpHtAir = 1013.0;    /* Specific heat of air, J/(kg*K) */
	const float SpHtIce = 2090.0;    /* Specific heat of ice, J/(kg*K) */
	const float SpHtCan = 2700.0;    /* Specific heat of canopy (CLASS value), J/(kg*K) */
	const float Hs = 2838000.0;      // Latent heat of sublimation, J/kg

	long   TItNum, RHItNum, TItNum2;       // Used in iteration loops
	bool   Tup, RHup, Tup2;
	float I1, Cp, wtsubl, Unld;

	double StepT, StepRH, StepT2;
	double DblRHcan, DblTbarCan, DblTCanSnow;

	float RhoS, Lstar; // Hedstrom-Pomeroy, for L/L*

	float SVDensC, SVDensS, LambdaT, CanVent, A, Nr, NuSh, D,
		Vs, Vhr, Ce, Vi; // Pomeroy-Schmidt components

	float QTrans50, QTrUp50, CanSnowFrac; /* Radiation model components */

	float RhoAir, SVDensA, VPref, Ustar, Uh, Ra, Ri,
		Stabil, Qe, Qh, dUdt; // CLASS components

	static long N;
	static float Z0m, Z0h, Disp, CdragH, CdragE;

	const float Cc = 0.82;
	const float Velw = 0.75;

	for (long hh = 0; hh < nhru; hh++) {

		if (getstep() == 1) {
			Tbiomass[hh] = TAref[hh];
			TCanSnow[hh] = TAref[hh];
			T0CanSnow[hh] = TCanSnow[hh];
			T0biomass[hh] = Tbiomass[hh];
			N = 0;
			Z0m = Ht[hh] / 10.0;            // One-time calc. of sfc. characteristics
			Z0h = Z0m / 2.0;
			Disp = Ht[hh] * 0.7;
			CdragH = (KARMAN / (log((Zref[hh] - Disp) / Z0h)))*(KARMAN / (log((Zref[hh] - Disp) / Z0m)));
			CdragE = sqr(KARMAN / (log(Zref[hh] / Ht[hh])));
		}

		Thru[hh] = 0.0;
		Qsubl[hh] = 0.0;

		if (N <= InitN[hh]) {// Starts depletion after Tcanopy is initialized
			Load[hh] = Lnot[0];
			if (N < InitN[hh]) break;
		}

		RhoS = 67.92 + 51.25*exp(TAref[hh] / 2.59);
		Lstar = Sbar[hh] * (0.27 + 46.0 / RhoS)*LAI[hh];

		if (Load[hh] > Lstar) { // after increase in temperature
			Thru[hh] = Load[hh] - Lstar;
			Load[hh] = Lstar;
		}

		if (hru_p[hh] > 0.0) {
			Cp = Cc / (1.0 - (Cc*hru_u[hh] * HeightH[hh]) / (Velw*WidthJ[hh]));
			if (Cp <= 0.0 || Cp > 1.0) Cp = 1.0;

			I1 = (Lstar - Load[hh])*(1 - exp(-Cp * hru_p[hh] / Lstar));

			Load[hh] = Load[hh] + I1; // add new snowfall
			Thru[hh] = Thru[hh] + (hru_p[hh] - I1); // remainder falls thru
		}

		if (Load[hh] <= 0.0) {
			Load[hh] = 0.0;
			break;
		}

		float RHrefhh;
		if (RHref[hh] > 1.5)
			RHrefhh = RHref[hh] / 100.0;
		else
			RHrefhh = RHref[hh];

		DblTbarCan = TAref[hh]; //TAref[hh]; // fix for precision problem

		DblRHcan = RHrefhh; // RHref[hh]; // fix for precision problem
		DblTCanSnow = TCanSnow[hh];

		CanSnowFrac = pow(Load[hh] / Lstar, 0.8);

		VPref = RHrefhh * Common::estar(TAref[hh]);
		SVDensA = Common::SVDens(TAref[hh]);
		RhoAir = 10000.0*94.97 / (2870.0*(TAref[hh] + 273.15))*(1.0 - 0.379*VPref / 94.97);

		Ustar = hru_u[hh] * KARMAN / (log((Zref[hh] - Disp) / Z0m));
		Uh = Ustar * (log((Ht[hh] - Disp) / Z0m)) / KARMAN;
		Ra = 1.0 / (CdragH*(hru_u[hh] + 0.1));

		A = 2.4338 + 3.45753*exp(-Uh);                 /* Modified Cionco wind model */
		CanVent = Uh * exp(A*((Zcan[hh] - 10) / (Ht[hh] - 10) - 1.0));  /* calculates canopy windspd  */

		Nr = 2 * Radius*CanVent / KinVisc;
		NuSh = 1.79 + 0.606*sqrt(Nr);

		if (SolarAng[hh] > 0.001) {
			float Mu = LAI[hh] / (Ht[hh] - 10)*(0.781*SolarAng[hh] * cos(SolarAng[hh]) + 0.0591);
			QTrans50 = QsIn[hh] * exp(-Mu * (Ht[hh] - 10) / 2 / sin(SolarAng[hh]));
			float QTrans100 = QsIn[hh] * exp(-Mu * (Ht[hh] - 10) / sin(SolarAng[hh]));
			QTrUp50 = (1.0 - SnowAlb)*QTrans100*exp(LAI[hh] / (Ht[hh] - 10)*0.0591*(Ht[hh] - 10) / 2);
		}
		else {
			QTrans50 = 0;
			QTrUp50 = 0;
		}

		TItNum = 0;
		StepT = 0.1;
		do { /* Canopy T iteration loop */
			TItNum = TItNum + 1;
			if (TItNum > 1)  DblTbarCan += StepT;
			SVDensC = Common::SVDens(DblTbarCan);
			Ri = g / ((TAref[hh] + DblTbarCan) / 2.0 + 273.15)*(TAref[hh] - DblTbarCan) / (Zref[hh] - Ht[hh])
				/ (sqr((hru_u[hh] - Uh) / (Zref[hh] - Ht[hh])));
			if (Ri < 0.0)  Stabil = pow((1.0 - 16.0*Ri), 0.75);
			else Stabil = sqr(1.0 - 5.0*Ri);

			RHItNum = 0;
			StepRH = 0.01;
			do { /* Canopy RH iteration loop */
				RHItNum = RHItNum + 1;
				if (RHItNum > 1)  DblRHcan += StepRH;
				LambdaT = 0.00063*(DblTbarCan + 273.15) + 0.0673;
				D = 2.06E-5*pow((DblTbarCan + 273.15) / 273.15, 1.75);

				TItNum2 = 0;
				StepT2 = 0.01;
				do { /* Canopy Snow and Biomass[hh] T iteration loop */
					TItNum2 = TItNum2 + 1;
					if (TItNum2 > 1) {
						DblTCanSnow += StepT2;
						Tbiomass[hh] = DblTbarCan + ((DblTbarCan - DblTCanSnow)*Load[hh] * SpHtIce)
							/ (Biomass[hh] * SpHtCan);
					}
					/* Solve for longwave */
					float QlwOut = SBC * (GapFrac*pow(TsnowG[0] + 273.15, 4.0) +
						(1.0 - GapFrac)*((1.0 - CanSnowFrac)*pow(Tbiomass[hh] + 273.15, 4.0)
							+ CanSnowFrac * pow(DblTCanSnow + 273.15, 4.0)));
					//         float QlwIn = Qn[hh]-QsIn[hh]+QsOut[hh]+QlwOut;
					float QlwIn = QsIn[hh] + QsOut[hh] + QlwOut;

					/* Solve for particle net radiation*/
					float QsDnStar = M_PI * Radius*Radius*QTrans50*(1.0 - SnowAlb);
					float QsUpStar = M_PI * Radius*Radius*QTrUp50*(1.0 - CanAlb);
					float QlwUpStar = M_PI * Radius*Radius*QlwOut;
					float QlwDnStar = M_PI * Radius*Radius*(QlwIn*UpperGF + SBC * (1.0 - UpperGF)*
						((1.0 - CanSnowFrac)*pow(Tbiomass[hh] + 273.15, 4.0)
							+ (CanSnowFrac*pow(DblTCanSnow + 273.15, 4.0))));
					float QradStar = 2 * M_PI*Radius*Radius*SBC*pow(DblTCanSnow + 273.15, 4.0);
					float QnetStar = QsDnStar + QsUpStar + QlwDnStar + QlwUpStar - QradStar;

					SVDensS = Common::SVDens(DblTCanSnow);
					Vs = (2.0*M_PI*D*Radius*(SVDensC*DblRHcan - SVDensS)*NuSh)*Hs;
					Vhr = (2.0*M_PI*LambdaT*Radius*(DblTCanSnow - DblTbarCan)*NuSh - QnetStar);

					if ((Vs - Vhr) < 0.0) {
						if (TItNum2 == 1) {
							Tup2 = false;
							StepT2 = -StepT2;
						}
						else {
							if (Tup2)  StepT2 = -StepT2 / 10.0;
							Tup2 = false;
						}
					}
					else {
						if (TItNum2 == 1)  Tup2 = true;
						else {
							if (!Tup2)  StepT2 = -StepT2 / 10.0;
							Tup2 = true;
						}
					}
				} while (fabs(Vs - Vhr) >= 0.000001);

				Vs = Vs / (4.0 / 3.0*M_PI*pow(Radius, 3.0)*RhoI) / Hs;
				Ce = k1 * pow(Load[hh] / Lstar, -Fract);
				Vi = Vs * Ce;
				Qsubl[hh] = Load[hh] * Vi*Hs;
				Qe = Hs * CdragE*(hru_u[hh] - Uh)*(SVDensA*RHrefhh - SVDensC * DblRHcan)*Stabil;

				if (Qe - Qsubl[hh] < 0.0) {
					if (RHItNum == 1) {
						RHup = false;
						StepRH = -StepRH;
					}
					else {
						if (RHup)  StepRH = -StepRH / 10.0;
						RHup = false;
					}
				}
				else {
					if (RHItNum == 1)  RHup = true;
					else {
						if (!RHup)  StepRH = -StepRH / 10.0;
						RHup = true;
					}
				}
			} while (fabs(Qsubl[hh] - Qe) >= 0.01);

			Qh = RhoAir * SpHtAir / Ra * (TAref[hh] - DblTbarCan)*Stabil;
			dUdt = ((Tbiomass[hh] - T0biomass[hh])*Biomass[hh] * SpHtCan
				+ (DblTCanSnow - T0CanSnow[hh])*Load[hh] * SpHtIce) / (Global::Interval * 24 * 3600.0);

			//     if (Qn[hh]+Qh+Qe-dUdt < 0.0)  {
			if (Qh + Qe - dUdt < 0.0) {
				if (TItNum == 1) {
					Tup = false;
					StepT = -StepT;
				}
				else {
					if (Tup)  StepT = -StepT / 10.0;
					Tup = false;
				}
			}
			else {
				if (TItNum == 1)  Tup = true;
				else {
					if (!Tup)  StepT = -StepT / 10.0;
					Tup = true;
				}
			}
			//   } while (fabs(Qn[hh]+Qe+Qh-dUdt) >= 0.01);
		} while (fabs(Qe + Qh - dUdt) >= 0.01);

		TCanSnow[hh] = DblTCanSnow;
		T0CanSnow[hh] = DblTCanSnow;
		T0biomass[hh] = Tbiomass[hh];

		wtsubl = -Qsubl[hh] * Global::Interval * 24 * 3600.0 / Hs; // make positive

		if (wtsubl > Load[hh]) {
			Qsubl[hh] = -Load[hh] / (Global::Interval * 24 * 3600.0 / Hs); // make W/m2
			wtsubl = Load[hh];
			Load[hh] = 0.0;
		}
		else
			Load[hh] = Load[hh] - wtsubl;

		if (hru_p[hh] > 0.0)
			if (I1 > wtsubl) {
				Unld = (I1 - wtsubl)*0.322;
				Load[hh] = Load[hh] - Unld;
				Thru[hh] = Thru[hh] + Unld;
			}
	}  // {for loop}
	N++;
}

void ClassPSPnew::finish(bool good) {

	delete[] T0CanSnow;
	T0CanSnow = NULL;
	delete[] T0biomass;
	T0biomass = NULL;
}

Classbrushintcp* Classbrushintcp::klone(string name) const {
	return new Classbrushintcp(name);
}

void Classbrushintcp::decl(void) {

	declvar("SnowLoad", NHRU, "Canopy snow load", "(kg/m^2)", &Load);

	declvar("Thru", NHRU, "Canopy fall through", "(kg/m^2)", &Thru);

	declstatvar("cumThru", NHRU, "Cumulative canopy fall through", "(mm)", &cumThru);

	declvar("brushsubl", NHRU, "Canopy snow sublimation", "(mm/int)", &brushsubl);

	declstatvar("cumbrushsubl", NHRU, "Cumulative canopy snow sublimation", "(mm)", &cumbrushsubl);

	declvar("spherecoeff", NHRU, "pan to sphere coefficient", "(mm/g)", &spherecoeff);

	declvar("net_rain", NHRU, "hru_rain minus interception", "(mm/int)", &net_rain);

	declstatdiag("cum_net_rain", NHRU, "cumulative hru_rain minus interception", "(mm)", &cum_net_rain);

	declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

	declvar("net_p", NHRU, "hru_precipitation (rain and/or snow) less interception", "(mm/int)", &net_p);

	declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);


	declparam("Ht", NHRU, "[20.0]", "0.001", "100.0", "Canopy height", "(m)", &Ht);

	declparam("Zcan", NHRU, "10.0", "0.0", "100.0", "Mid-canopy wind modelling height", "(m)", &Zcan);

	declparam("Zref", NHRU, "[20.0]", "0.0", "100.0", "Reference height. Set <= 0.0 to disable this module for this HRU", "(m)", &Zref);

	declparam("Sbar", NHRU, "6.6", "0.0", "20.0", "Uncorrected snow capacity", "(kg/m^2)", &Sbar);

	declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

	declparam("WidthJ", NHRU, "[75]", "0.0", "100.0", "Canopy forested downwind distance", "(m)", &WidthJ);

	declparam("brushAtten", NHRU, "[1.0]", "0.2", "10.0", "Brush attenuation coefficient", "()", &brushAtten);

	declparam("Tunload", NHRU, "0.0", "-5.0", "5.0", "Canopy unload at daily mean temperature", "(�C)", &Tunload);

	declparam("basin_area", ONE, "3", "0.01", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "0.01", "1e+09", "hru area", "(km^2)", &hru_area);

	declgetvar("obs", "hru_t", "(�C)", &hru_t);
	declgetvar("obs", "hru_tmean", ", (�C)", &hru_tmean);
	declgetvar("obs", "hru_rh", "()", &hru_rh);
	declgetvar("obs", "hru_u", "(m/s)", &hru_u);
	declgetvar("obs", "hru_rain", "(mm)", &hru_rain);
	declgetvar("obs", "hru_snow", "(mm)", &hru_snow);
	declgetvar("obs", "hru_p", "(mm)", &hru_p);

	declputvar("pbsm", "cumSubl", "(mm)", &cumSubl);
}

void Classbrushintcp::init(void) {
	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		net_p[hh] = 0.0;
		net_rain[hh] = 0.0;
		net_snow[hh] = 0.0;
		brushsubl[hh] = 0.0;
		cumbrushsubl[hh] = 0.0;
		Thru[hh] = 0.0;
		cumThru[hh] = 0.0;
		Load[hh] = 0.0;
		intcp_evap[hh] = 0.0;
		spherecoeff[hh] = 0.0;
		cum_net_rain[hh] = 0.0;
	}
}

void Classbrushintcp::run(void) {

	const float LATH = 2.838E6; // latent heat of sublimation (J/kg) List 1949
	const float Qstar = 120;    // Solar Radiation Input
	const float Mpr = 0.5E-3;
	const float Cc = 0.82;
	const float Velw = 0.75;
	const float KARMAN = 0.4;
	const float KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
	const float M = 18.01;      //{molecular weight of water (kg/kmole)}
	const float R = 8313;       //{universal gas constant (J/(kmole K))}


	for (hh = 0; chkStruct(); ++hh) {

		if (Zref[hh] > 0.0) {

			Thru[hh] = 0.0;

			if (hru_tmean[hh] > Tunload[hh]) {
				Thru[hh] = Load[hh] + hru_snow[hh];
				Load[hh] = 0.0;
			}
			else {

				float RhoS = 67.92 + 51.25*exp(hru_t[hh] / 2.59);
				float Lstar = Sbar[hh] * (0.27 + 46.0 / RhoS)*LAI[hh];

				if (Load[hh] > Lstar) { // after increase in temperature
					Thru[hh] = Load[hh] - Lstar;
					Load[hh] = Lstar;
				}

				if (hru_snow[hh] > 0.0) {
					float Cp = Cc / (1.0 - (Cc*hru_u[hh] * Ht[hh]) / (Velw*WidthJ[hh]));
					if (Cp <= 0.0 || Cp > 1.0) Cp = 1.0;

					float I1 = (Lstar - Load[hh])*(1 - exp(-Cp * hru_snow[hh] / Lstar));

					Load[hh] = Load[hh] + I1; // add new snowfall
					Thru[hh] = Thru[hh] + (hru_snow[hh] - I1); // remainder falls thru

				}

				if (Load[hh] > 0.0) {

					float Z0m = Ht[hh] / 10.0;
					float Disp = Ht[hh] * 0.7;
					float Ustar = hru_u[hh] * KARMAN / (log((Zref[hh] - Disp) / Z0m));
					float Uh = Ustar * (log((Ht[hh] - Disp) / Z0m)) / KARMAN;

					float CanVent = Uh * exp(brushAtten[hh] * (Zcan[hh] / Ht[hh] - 1.0));  /* calculates canopy windspd  */

					float Reyn = 2 * Mpr*CanVent / KinVisc;
					float Nuss = 1.79 + 0.606*sqrt(Reyn);

					float Temp = hru_t[hh] + 273.15;
					float Lamb = 0.00063*Temp + 0.0673;                // therm. cond. of atm. (J/(msK))
					float Diff = 2.06E-5*pow(Temp / 273.0, 1.75);        // diffus. of w.vap. atmos. (m2/s)
					float Sigma2 = hru_rh[hh] / 100.0 - 1.0;             // undersaturation at 2 m
					float Htran = 0.9 * M_PI * sqr(Mpr) * Qstar;

					float SigmaZ = Sigma2 * (1.019 + 0.027 * log(Zcan[hh]));  // Eq. 6.20, Revised in May. 1997
					if (SigmaZ > -0.01) { SigmaZ = -0.01; }

					float A = Lamb * Temp * Nuss;
					float B = LATH * M / (R * Temp) - 1.0;
					float C = 1.0 / (Diff * Common::SVDens(hru_t[hh]) * Nuss);
					float DmDt = -((2.0*M_PI * Mpr * SigmaZ) - (Htran*B / A)) / ((LATH*B / A) + C);
					DmDt *= 24.0*3600.0 / Global::Freq; // convert to interval

					spherecoeff[hh] = 17.6*pow(cumbrushsubl[hh] + 0.001, -0.086);

					brushsubl[hh] = DmDt * spherecoeff[hh] * 1000.0; //convert kg to gm

					if (brushsubl[hh] > Load[hh]) {
						brushsubl[hh] = Load[hh];
						Load[hh] = 0.0;
					}
					else
						Load[hh] -= brushsubl[hh];

					cumbrushsubl[hh] += brushsubl[hh];
					cumSubl[hh] += brushsubl[hh];
				}
			}

			net_snow[hh] = Thru[hh];
			cumThru[hh] += Thru[hh];

			net_rain[hh] = hru_rain[hh];
			net_p[hh] = hru_p[hh];
		}
		else {
			net_p[hh] = hru_p[hh];
			net_snow[hh] = hru_snow[hh];
			net_rain[hh] = hru_rain[hh];
		}
		cum_net_rain[hh] += net_rain[hh];
	}
}

void Classbrushintcp::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		if (Zref[hh] > 0.0) {
			LogMessageA(hh, "'brushintcp' cumThru     (mm) (mm*hru) (mm*hru/basin): ", cumThru[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, "'brushintcp' cumbrushsubl(mm) (mm*hru) (mm*hru/basin): ", cumbrushsubl[hh], hru_area[hh], basin_area[0]);
		}
		LogMessageA(hh, "'brushintcp' cumnetrain    (mm) (mm*hru) (mm*hru/basin): ", cum_net_rain[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassAyers* ClassAyers::klone(string name) const {
	return new ClassAyers(name);
}

void ClassAyers::decl(void) {

	Description = "'Uses Ayers, 1959 for unfrozen soil. Snow is assumed to melt immediately on contact with the ground.'";

	declvar("infil", NHRU, "Potential amount of water infiltrating the soil on each HRU", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential infiltration on each HRU", "(mm)", &cuminfil);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	declvar("snowinfil", NHRU, "infiltration", "(mm/int)", &snowinfil);

	declstatdiag("cumsnowinfil", NHRU, "cumulative infiltration", "(mm)", &cumsnowinfil);

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "melt runoff", "(mm)", &cummeltrunoff);

	decllocal("melt_int", NHRU, "interval melt from snowmelD", "(mm/int)", &melt_int);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("texture", NHRU, "[1]", "1", "4",
		"texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

	declparam("groundcover", NHRU, "[1]", "1", "6",
		"groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

	declgetvar("*", "net_rain", "(mm/int)", &net_rain);

	declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD);
}

void ClassAyers::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		cuminfil[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;
	}
}

void ClassAyers::run(void) {

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // every interval
		infil[hh] = 0.0;
		runoff[hh] = 0.0;
		snowinfil[hh] = 0.0;
		meltrunoff[hh] = 0.0;

		if (nstep == 0)
			melt_int[hh] = snowmeltD[hh] / Global::Freq;

		float maxinfil = textureproperties[texture[hh] - 1][groundcover[hh] - 1] * 24.0 / Global::Freq; // mm/int

		if (melt_int[hh] > 0.0) {
			if (maxinfil > melt_int[hh])
				snowinfil[hh] = melt_int[hh];
			else {
				snowinfil[hh] = maxinfil;
				meltrunoff[hh] = melt_int[hh] - maxinfil;
			}
			maxinfil -= snowinfil[hh];

			cumsnowinfil[hh] += snowinfil[hh];
			cummeltrunoff[hh] += meltrunoff[hh];
		}

		if (net_rain[hh] > 0.0) {
			if (maxinfil > 0.0) {
				if (maxinfil > net_rain[hh])
					infil[hh] = net_rain[hh];
				else {
					infil[hh] = maxinfil;
					runoff[hh] = net_rain[hh] - maxinfil;
				}
			}
			else
				runoff[hh] = net_rain[hh];

			cuminfil[hh] += infil[hh];
			cumrunoff[hh] += runoff[hh];
		}
	}
}

void ClassAyers::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Ayers)' cuminfil(rain)      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Ayers)' cumrunoff(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Ayers)' cumsnowinfil(snow)  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Ayers)' cummeltrunoff(snow) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassSlope_Qsi* ClassSlope_Qsi::klone(string name) const {
	return new ClassSlope_Qsi(name);
}

void ClassSlope_Qsi::decl(void) {

	Description = "'Estimates interval short-wave on a slope from measured horizontal Qsi and theoretical values on the slope.',  \
                 ' Output as observations, QsiS (W/m^2) and QsiD_Obs (W/m^2),' \
                 ' Output as variables, QsiS_Var (W/m^2) and QsiD_Var (W/m^2).'";

	variation_set = VARIATION_ORG;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);

	declobsfunc("Qsi", "QsiD_Obs", &QsiD, AVG);

	declgetvar("*", "Qdro", "(W/m^2)", &Qdro);
	declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);
	declgetvar("*", "Qdflat", "(W/m^2)", &Qdflat);


	variation_set = VARIATION_0;

	declobs("QsiS", NHRU, "generated interval short-wave", "(W/m^2)", &QsiS);

	declobs("QsiD_Obs", NHRU, "average measured (Qsi) short-wave on horizontal", "(W/m^2)", &QsiD_Obs);


	variation_set = VARIATION_1;

	declvar("QsiS_Var", NHRU, "corrected short-wave on slope", "(W/m^2)", &QsiS_Var);

	declvar("QsiD_Var", NHRU, "average short-wave on horizontal", "(W/m^2)", &QsiD_Var);

	variation_set = VARIATION_ORG;
}

void ClassSlope_Qsi::init(void) {

	nhru = getdim(NHRU);
}

void ClassSlope_Qsi::run(void) {

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {
		float Short = Qdro[hh] + Qdfo[hh];
		float ShortC = 0.0;
		if (Qdflat[hh] > 1.0)
			ShortC = Qsi[hh] / Qdflat[hh] * Short;

		switch (variation) {
		case VARIATION_ORG:
			QsiS[hh] = ShortC;
			if (nstep == 1)
				QsiD_Obs[hh] = QsiD[hh]; // move mean from variable to declared observation
			break;
		case VARIATION_1:
			QsiS_Var[hh] = ShortC;
			if (nstep == 1)
				QsiD_Var[hh] = QsiD[hh]; // move mean from variable to declared observation
			break;
		} // switch

	}
}

ClassalbedoWinstral* ClassalbedoWinstral::klone(string name) const {
	return new ClassalbedoWinstral(name);
}

void ClassalbedoWinstral::decl(void) {

	Description = "'Incomplete code to calculate snowcover albedo from a method proposed by Winstral.'";

	declstatvar("Albedo", NHRU, "Albedo", "()", &Albedo);

	declstatdiag("Ab_t", NHRU, "steps since albedo refresh", "()", &Ab_t);

	decllocal("irdalb", NHRU, "ir_diffuse decay", "()", &irdalb);

	decllocal("vddalb", NHRU, "visible_diffuse decay", "()", &vdalb);

	decldiagparam("maxdecay", NHRU, "[0.25]", "0.1", "0.5", "maximum decay", "()", &maxdecay);

	decldiagparam("power", NHRU, "[1.4]", "-2.0", "2.0", "power function", "()", &power);

	decldiagparam("decay_period", NHRU, "[5000]", "100", "20000", "time over albedo decays", "()", &decay_period);

	decldiagparam("refresh", NHRU, "[1.0]", "0.5", "50.0", "minimum sub-canopy snowfall to refresh albedo", "(mm)", &refresh);

	decldiagparam("Albedo_Bare", NHRU, "[0.17]", "0.0", "1.0", "Initial albedo for bare ground", "()", &Albedo_Bare);


	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void ClassalbedoWinstral::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		Ab_t[hh] = 0;
		irdalb[hh] = 0.24;
		vdalb[hh] = 0.02;
		//    balbx[hh] = 0.0;
	}
}

void ClassalbedoWinstral::run(void) {

	// albedo routine:

	for (hh = 0; chkStruct(); ++hh) {
		if (SWE[hh] > refresh[hh]) {

			if (net_snow[hh] >= refresh[hh])
				Ab_t[hh] = 0;
			else
				Ab_t[hh] = Ab_t[hh] + 24.0 / Global::Freq;

			irdalb[hh] = 0.24 + pow(Ab_t[hh] / decay_period[hh], power[hh]) * maxdecay[hh];

			vdalb[hh] = 0.02 + pow(Ab_t[hh] / decay_period[hh], power[hh]) * maxdecay[hh];

			Albedo[hh] = (1.0 - vdalb[hh])*0.48 + (1.0 - irdalb[hh])*0.52;
		}
		else
			Albedo[hh] = Albedo_Bare[hh];
	}
}

void ClassalbedoWinstral::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "'" + Name + " (albedo_Winstral)' ";
		LogMessage(hh, s.c_str());
	}
	LogDebug(" ");
}

ClassfrozenAyers* ClassfrozenAyers::klone(string name) const {
	return new ClassfrozenAyers(name);
}

void ClassfrozenAyers::decl(void) {

	Description = "'Frozen soil infiltration Zhao and Gray (1999) and Ayers, (1959) for unfrozen soil.'";

	declvar("infil", NHRU, "Potential rain infiltration", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

	declvar("snowinfil", NHRU, "melt infiltration", "(mm/int)", &snowinfil);

	declstatvar("cumsnowinfil", NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

	declvar("cumsnowinfil_0", NHRU, "cumulative melt infiltration at beginning of frozen cycle", "(mm)", &cumsnowinfil_0); // for looping

	declvar("meltrunoff", NHRU, "melt runoff", "(mm/int)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff", "(mm)", &cummeltrunoff);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);

	decllocal("t0_Var", NHRU, "t0 value used by module", "(h)", &t0_Var);

	decllocal("t0_Acc", NHRU, "opportunity time", "(h)", &t0_Acc); // to reset every loop

	decllocal("INF", NHRU, "parametric calculation", "(mm)", &INF);

	decllocal("Julian_window", ONE, "currently in Julian window handling frozen infiltration.", "()", &Julian_window);

	decllocal("Julian_lockout", ONE, "lockout next frozen cycle until after this Julian date when t0_Julian is not set (i.e. 0).", "()", &Julian_lockout);

	decllocal("infiltype", NHRU, "infiltration type. PREMELT/RESTRICTED/LIMITED/UNLIMITED/SATURATED - 0/1/2/3/4 respectively", "()", &infiltype);

	decllocal("snowmeltD_last", NHRU, "yesterday's snowmelt. Used to determine the formation of ice lens.", "(mm/d)", &snowmeltD_last);

	decllocal("SWEPk", NHRU, "peak snow water equivalent", "(mm)", &SWEPk);


	declparam("t0", NHRU, "[0.0]", "0.0", "1000.0", "< 0 - calculate opportunity time, == 0 - calculate t0 from '0.65*SWE-5.0',  > 0 - use as opportunity time", "(h)", &t0);

	decldiagparam("S0", NHRU, "[1.0]", "0.0", "1.0", "surface saturation", "(mm^3/mm^3)", &S0);

	declparam("Si", NHRU, "[0.5]", "0.0", "1.0", "initial soil saturation (0 - 0.4m)", "(mm^3/mm^3)", &Si);

	decldiagparam("C", NHRU, "[1.0]", "0.0", "3.0", "coefficient", "()", &C);

	declparam("hru_tsoil", NHRU, "[269.15]", "223.0", "273.15", "soil average temperature at start of infiltration (0 - 0.4m)", "(�K)", &hru_tsoil);

	decldiagparam("t_ice_lens", NHRU, "[-20]", "-50.0", "0.0", "overnight minimum to cause ice lens after major melt", "(�C)", &t_ice_lens);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0",
		"Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone",
		"(mm)", &soil_moist_max);

	declparam("texture", NHRU, "[1]", "1", "4",
		"texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

	declparam("groundcover", NHRU, "[1]", "1", "6",
		"groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

	decldiagparam("t0_Julian", ONE, "[30]", "0", "366", "value > 0 - inhibit frozen algorithm till after this Julian date, 0 - enable frozen algorithm immediately when melt criteria is met", "()", &t0_Julian);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

	declgetvar("*", "SWE", "(mm)", &SWE);

	declgetvar("*", "net_rain", "(mm/int)", &net_rain);

	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);


	declreadobs("t0_inhibit", NHRU, "opportunity time inhibit", "()", &t0_inhibit, 0, true);
}

void ClassfrozenAyers::init(void) {

	nhru = getdim(NHRU);

	if (t0[0] <= 0.0) { // going to calculate oportunity time
		if (t0_inhibit == NULL) {
			CRHMException TExcept(string("'" + Name + " (FrozenAyers)' calculating opportunity time using every melt interval!").c_str(), WARNING);
			LogError(TExcept);
		}
		else {
			CRHMException TExcept(string("'" + Name + " (FrozenAyers)' calculating opportunity time using selected intervals!").c_str(), WARNING);
			LogError(TExcept);
		}
	}

	for (hh = 0; hh < nhru; ++hh) {
		t0_Acc[hh] = 0.0;
		t0_Var[hh] = 0.0;
		cuminfil[hh] = 0.0;
		infil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		cumsnowinfil_0[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;
		runoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		INF[hh] = 0.0;
		SWEPk[hh] = 0.0;

		infiltype[hh] = PREMELT;
	}

	SetOpportunityTime = false;
	Julian_window[0] = 0; // before Julian date
	Julian_lockout[0] = 0;
}

void ClassfrozenAyers::run(void) {

	bool SetOpportunity = false;
	bool ClrOpportunity = false;

	long nstep = getstep() % Global::Freq;

	float SWE_sum = 0.0;

	for (hh = 0; chkStruct(); ++hh)
		SWE_sum += SWE[hh]; // used to reset opportunity time

	for (hh = 0; chkStruct(); ++hh) {

		if (nstep == 0) { // end of day
			snowmeltD_last[hh] = snowmeltD[hh];
			if (SWE[hh] > SWEPk[hh])
				SWEPk[hh] = SWE[hh];
		}
		else if (nstep == 1 &&                  // beginning of day
			hru_tmin[hh] <= t_ice_lens[hh] &&
			infiltype[hh] == LIMITED &&
			snowmeltD_last[hh] > 5.0) {

			infiltype[hh] = RESTRICTED;

			LogMessage(hh, " ice lens formed at temperature of ", hru_tmin[hh], DT);
			LogDebug(" ");

			CRHMException TExcept(string(string("Ice lens formed in HRU ") + std::to_string(hh + 1) + ", at minimum temperature of " + Convert(hru_tmin[hh])).c_str(), WARNING);
			LogError(TExcept);
		}

		infil[hh] = 0.0;
		runoff[hh] = 0.0;

		if (net_rain[hh] > 0.0) {
			float maxinfil = textureproperties[texture[hh] - 1][groundcover[hh] - 1] * 24.0 / Global::Freq; // mm/int
			if (maxinfil > net_rain[hh])
				infil[hh] = net_rain[hh];
			else {
				infil[hh] = maxinfil;
				runoff[hh] = net_rain[hh] - maxinfil;
			}

			cuminfil[hh] += infil[hh];
			cumrunoff[hh] += runoff[hh];
		}

		snowinfil[hh] = 0.0;
		meltrunoff[hh] = 0.0;

		if (Julian_lockout[0] == julian("now"))
			Julian_lockout[0] = 0;

		float snowmelt = snowmeltD[hh] / Global::Freq;

		if (nstep == 1 && hh == 0) {
			if (t0_Julian[0] == julian("now") || t0_Julian[0] == 0 && SWE_sum / nhru > 10 && snowmeltD[hh] > 2.0 && !Julian_lockout[0]) {
				Update_infil = true;
				if (t0[0] < 0) {
					Julian_window[0] = 1;
					for (long hhh = 0; chkStruct(hhh); ++hhh) // reset
						t0_Acc[hhh] = t0[hhh];
				}
				else
					for (long hhh = 0; chkStruct(hhh); ++hhh) // save t0 values
						t0_Var[hhh] = t0[hhh];

				Julian_lockout[0] = (julian("now") + 183) % 365; // close after 6 months
			}
		}

		INF[hh] = 0.0;
		if (snowmelt > 0.0) { // snowmeltD[hh]/Global::Freq

			if (hh == (nhru - 1) && (SWE_sum / nhru <= 2.0 || last_timestep())) { // end of melt
				if (SetOpportunityTime) { // was calculating opportunity time
					--Global::CRHMControlSaveCnt; // restore state to backtrack. NO output this cycle
					ClrOpportunity = true;

					for (long hhh = 0; chkStruct(hhh); ++hhh) // save opportunity time values
						t0_Var[hhh] = t0_Acc[hhh];

					SetOpportunityTime = false;
				 string s = Name + " End save ";
					LogMessage(s.c_str(), DD);
					Julian_window[0] = 0;
				}
			}

			if (!SetOpportunityTime) { // normal operation
				float capacity;
				switch (infiltype[hh]) {
				case LIMITED:

					capacity = soil_moist_max[hh] - soil_moist[hh];
					if (capacity > 0.0 && (t0_Var[hh] || !t0[hh])) { // also handles divide by zero
						if (!t0[hh]) {
							t0_Var[hh] = 0.65*SWEPk[hh] - 5.0;
							if (t0_Var[hh] < 24.0)
								t0_Var[hh] = 24.0;
						}
						INF[hh] = C[hh] * pow(S0[hh], 2.92f)*pow(1.0f - Si[hh], 1.64f)*
							pow((273.15f - hru_tsoil[hh]) / 273.15f, -0.45f)*pow(t0_Var[hh], 0.44f); // (mm)

						float INF0 = INF[hh] / t0_Var[hh];

						if (snowmelt <= INF0 && snowmelt <= capacity) {
							snowinfil[hh] = snowmelt;
							meltrunoff[hh] = 0.0;
						}
						else if (snowmelt > INF0) {
							snowinfil[hh] = INF0;
							meltrunoff[hh] = snowmelt - INF0;
						}
						else {
							snowinfil[hh] = capacity;
							meltrunoff[hh] = snowmelt - capacity;
						}

						cumsnowinfil[hh] += snowinfil[hh];
						cummeltrunoff[hh] += meltrunoff[hh];

						if (cumsnowinfil[hh] - cumsnowinfil_0[hh] > INF[hh]) {
							cummeltrunoff[hh] += (cumsnowinfil[hh] - cumsnowinfil_0[hh] - INF[hh]);
							cumsnowinfil[hh] += INF[hh];
							infiltype[hh] = RESTRICTED;
						}
					}
					else {
						meltrunoff[hh] = snowmelt;
						cummeltrunoff[hh] += meltrunoff[hh];
					}

					break;

				case UNLIMITED:
					snowinfil[hh] = snowmelt;
					cumsnowinfil[hh] += snowinfil[hh];
					break;
				case RESTRICTED:
					meltrunoff[hh] = snowmelt;
					cummeltrunoff[hh] += meltrunoff[hh];
					break;
				default:
					if (Si[hh] < 1.0) {
						snowinfil[hh] = snowmelt;
						cumsnowinfil[hh] += snowinfil[hh];
					}
					else {
						meltrunoff[hh] = snowmelt;
						cummeltrunoff[hh] += meltrunoff[hh];
					}
					break;
				} // switch
			} // normal operation

			if (snowmeltD[hh] > 2.0) {
				if (Julian_window[0] == 1 && !SetOpportunityTime) { // run ahead?
					SetOpportunity = true;
					++Global::CRHMControlSaveCnt; // save state for backtrack. Inhibit output, including this interval
				 string s = Name + " Start save ";
					LogMessage(s.c_str(), DD);
				}

				if (Update_infil) {
					for (long hhh = 0; chkStruct(hhh); ++hhh) { // set infiltration

						SWEPk[hhh] = SWE[hhh];

						if (Si[hhh] >= 1.0)
							infiltype[hhh] = RESTRICTED;
						else if (Si[hhh] <= 0.0)
							infiltype[hhh] = UNLIMITED;
						else
							infiltype[hhh] = LIMITED;
					}
					cumsnowinfil_0[hh] = cumsnowinfil[hh];

					Update_infil = false;
				}
			} // snowmeltD[hh] > 2.0

			if (SetOpportunityTime) { // accummulate opportunity time
				if (t0_inhibit == NULL)
					t0_Acc[hh] += 24.0 / Global::Freq;
				else if (t0_inhibit[hh] > 0)
					t0_Acc[hh] += 24.0 / Global::Freq;
			}
		} // if(snowmelt > 0.0)
	} // for

	if (SetOpportunity)
		SetOpportunityTime = true;
	if (ClrOpportunity)
		SetOpportunityTime = false;
}

void ClassfrozenAyers::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

//Define HMSA constants:

const float rho_a = 1.2; // (kg/m3) air
const float rho_i = 920.0; // (kg/m3) ice

const float c_a = 1010.0; // (J/kg/K) air
const float c_i = 2120.0; // (J/kg/K) ice

const float Cv_a = 1212.0; // (J/m3/K) air
const float Cv_i = 1950400.0; // (J/m3/K) ice
const float Cv_w = 4185000.0; // (J/m3/K) water

const float lam_a = 0.025; // (W/m/K) air
const float lam_i = 2.24;  // (W/m/K) ice
const float lam_w = 0.57;  // (W/m/K) water

const float Rho_Organic = 1300.0; // (kg m-3)
const float Rho_Minerals = 2650.0; // (kg m-3)
const float Rho_Water = 1000.0; // (kg m-3)
const float Rho_Ice = 920.0; // (note: 890.0 on Hayashi's paper) (kg m-3)
const float Rho_Snow = 200.0; // (kg m-3)
const float Rho_Air = 1.2;  // (kg m-3)

							//K_x: heat conductivity
const float K_Organic = 0.21;  // W/(m K)  //0.25
const float K_Minerals = 2.50;  // W/(m K)  //2.9
const float K_Air = 0.025; // W/(m K)
const float K_Ice = 2.24;  // W/(m K)
const float K_Water = 0.57;  // W/(m K)

							 //HC_x: specific heat capacity
const float HC_Minerals = 890.0; //745.1 // J/(kg.K)
const float HC_Water = 4185.0; // J/(kg.K)
const float HC_Air = 1010.0; // J/(kg.K)
const float HC_Organic = 1920.0; // J/(kg.K)
const float HC_Ice = 2120.0; // J/(kg.K)
const float Water_Ice = 334.0e3; // latent heat for fusion of water (J kg-1)
const float Max_Layers = 20;  // maximum layers allowed

ClassHMSA* ClassHMSA::klone(string name) const {
	return new ClassHMSA(name);
}

void ClassHMSA::decl(void) {

	Description = "'Estimation of frost table (Masaki Hayashi 2007).' \
                 'ebsm using variable hru_t (�C),' \
                 'ebsm using observation Tsurf_obs (�C).'";

	MaxFrontCnt = 10;

	variation_set = VARIATION_ORG;

	// Variables:
	declstatvar("Cum_Thaw", NHRU, "Cumulative thaw depth", "(m)", &Cum_Thaw);
	declstatvar("Cum_Frozen", NHRU, "Cumulative frozen depth", "(m)", &Cum_Frozen);
	declvar("Lamda_b", NHRU, "Thermal conductivity", "()", &Lamda_b); // (W/m.�C)
	declvar("Thaw_D", NHRU, "thaw table depth below surface", "(m)", &Thaw_D);
	declvar("Frozen_D", NHRU, "frost table depth below surface", "(m)", &Frozen_D);
	declvar("C_K0", NHRU, "Conductivity", "()", &C_K0);
	declvar("Last_Tsurf", NHRU, "last surface temperature", "(�C)", &Last_Tsurf);

	declvar("f", NHRU, "Vol fraction of ice (or water)", "(m^3/m^3)", &f);
	declvar("Soil_Ice", NLAY, "Ice fraction in soil", "()", &Soil_Ice, &Soil_Ice_lay);
	declvar("Soil_Water", NLAY, "Liquid water fraction in soil", "()", &Soil_Water, &Soil_Water_lay);
	declvar("Total_Moisture", NLAY, "layer moisture fraction", "()", &Total_Moisture, &Total_Moisture_lay);
	declstatvar("Cum_d", NLAY, "cumulative layer depths", "(m)", &Cum_d, &Cum_d_lay);
	declstatvar("Frozen_ID", NLAY, "cumulative layer depths", "(m)", &Frozen_ID, &Frozen_ID_lay);

	declvar("FrntDepth", NDEFN, "Front depth", "(m)", &FrntDepth, &FrntDepth_array, MaxFrontCnt);
	declstatvar("FreezeCum", NDEFN, "Front depth", "(m)", &FreezeCum, &FreezeCum_array, MaxFrontCnt);
	declvar("ThawCum", NDEFN, "Front depth", "(m)", &ThawCum, &ThawCum_array, MaxFrontCnt);
	declvar("FrntDepthType", NDEFN, "Front depth type > 0 thaw, < 0 freeze", "()", &FrntDepthType, &FrntDepthType_array, MaxFrontCnt);
	declvar("FrontCnt", NHRU, "number of fronts", "()", &FrontCnt);

	// local variables
	decllocal("Tsurface", NHRU, "soil surface temperature used in module", "()", &Tsurface);

	// Parameters (some are already defined in 'CRHMQuinton'):
	declparam("Alpha_ID", NHRU, "1", "0", "1", "For ID=0 input Alpha values used, for ID=1 Alpha calculated in model", "()", &Alpha_ID);
	declparam("Alpha_T", NHRU, "0.000118", "0.0", "1e2", "Thaw layer migration constant", "()", &Alpha_T); // (J^-1/2/m^3/2)
	declparam("Alpha_F", NHRU, "0.000118", "0.0", "1e2", "Freeze layer migration constant", "()", &Alpha_F); //(J^-1/2/m^3/2)

	declparam("Soil_depths_lay", NLAY, "[0.15] , [0.1], [0.1] ,[0.1]", "0.0", "100.0", "layer depths", "(m)", &Soil_Depths, &Soil_depths_lay);
	declparam("Organic", NLAY, "0.10, 0.17, 0.24, 0.25, 0.25, 0.25", "0.0", "1.0", "Volume ratio of organic matter", "(m^3/m^3)", &Organic, &Organic_lay);
	declparam("Porosity", NLAY, "0.90, 0.83, 0.76, 0.75, 0.75, 0.75", "0.0", "1.0", "Layer Porosity", "(m^3/m^3)", &Porosity, &Porosity_lay); // "Pors" in CRHMQuinton
	declparam("Bulkdensity", NLAY, "90.0, 144.3, 200.0, 248.0, 248.0, 248.0", "0.0", "1e3", "Bulk density of layer", "(kg/m^3)", &BulkDensity, &BulkDensity_lay);
	declparam("Soil_ID", NLAY, "0, 1, 2, 3, 3, 3", "0", "4", "Soil_ID", "(kg/m^3)", &Soil_ID, &Soil_ID_lay);

	declparam("InitThaw_D", NHRU, "0.7", "0.0", "1e2", "Initial thaw table depth below surface", "(m)", &InitThaw_D);
	declparam("InitFrozen_D", NHRU, "0.0", "0.0", "1e2", "Initial frost table depth below surface", "(m)", &InitFrozen_D);
	declparam("Soil_Layers", NHRU, "6", "0.0", "100.0", "No. of soil layers", "()", &Soil_Layers);
	declparam("D_Top", NHRU, "0.02", "0.0", "1e2", "Pos of upper bndry temp rel to grd surface", "(m)", &D_Top);
	declparam("Method_ID", NHRU, "1", "1", "5", "SoilHeat method, 1/2/3/4/5 - Johansen Complete/Johansen  common/ De Vries as Hayashi/ De Vries as Farouki/ Chad", "()", &Method_ID);

	declparam("TMPB_W", NDEF, "0.15, 0.18, 0.19, 0.19, 0.06", "0", "1.0", "Liquid water fraction in soil", "()", &TMPB_W, &TMPB_W_NDEF, 5);

	variation_set = VARIATION_0;

	// driving variable:
	declgetvar("*", "hru_t", "(�C)", &hru_t);

	variation_set = VARIATION_1;

	Liqcnt = declreadobs("LiqWat", NOBS, "liquid water at depth observation", "()", &LiqWat, HRU_OBS_misc); // # layers
	Totcnt = declreadobs("TotMoist", NOBS, "total moisture at depth observation", "()", &TotMoist, HRU_OBS_misc); // # layers
	declreadobs("Tsurf_obs", NHRU, "soil surface temperature observation", "(�C)", &Tsurf_obs, HRU_OBS_misc);

	variation_set = VARIATION_ORG;
}

void ClassHMSA::init(void) {

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);

	float F_Dummy, Alpha, I_Avg, I_Dummy; // [Max_Layers]

	for (hh = 0; chkStruct(); ++hh) {
		if (Soil_Layers[hh] > nlay) {
			CRHMException TExcept("In module 'HMSA' Soil_Layers parameter must be <= number of layers (nlay)!", TERMINATE);
			LogError(TExcept);
		}

		Thaw_D[hh] = InitThaw_D[hh];
		Frozen_D[hh] = InitFrozen_D[hh];
		FrontCnt[hh] = 0;

		for (long nn = 0; nn < MaxFrontCnt; ++nn) {
			FrntDepthType_array[nn][hh] = 0;
			FrntDepth_array[nn][hh] = 0.0;
			FreezeCum_array[nn][hh] = 0.0;
			ThawCum_array[nn][hh] = 0.0;
		}
	} // for
}

void ClassHMSA::run(void) {

	long I_Avg;
	float Alpha;

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Tsurface[hh] = hru_t[hh]; // variable
			break;
		case VARIATION_1:
			Tsurface[hh] = Tsurf_obs[hh]; // variable
			break;
		} // switch

		  // Calculate accumulative depth of each layers
		Cum_d_lay[0][hh] = Soil_depths_lay[0][hh];
		for (long nn = 1; nn < Soil_Layers[hh]; ++nn)
			Cum_d_lay[nn][hh] = Cum_d_lay[nn - 1][hh] + Soil_depths_lay[nn][hh];

		if (Thaw_D[hh] > 0.0) { //  Frozen_ID = 0 = thaw, = 1 = frozen
			for (long nn = 0; nn < Soil_Layers[hh]; ++nn)
				Frozen_ID_lay[nn][hh] = 1; // sets frozen
			for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
				Frozen_ID_lay[nn][hh] = 0; // sets unfrozen
				if (Thaw_D[hh] < Cum_d_lay[nn][hh]) break;
			}
		}
		else {
			for (long nn = 0; nn < Soil_Layers[hh]; ++nn)
				Frozen_ID_lay[nn][hh] = 0; // sets unfrozen
			for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
				Frozen_ID_lay[nn][hh] = 1; // sets frozen
				if (Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
			}
		}

		for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {

			if (variation == VARIATION_1) {
				Soil_Water_lay[nn][hh] = LiqWat[min<long>(nn, Liqcnt)];
				Total_Moisture_lay[nn][hh] = TotMoist[min<long>(nn, Totcnt)];
			}
			else if (getstep() == 1) { // fix
				Soil_Water_lay[nn][hh] = 0.0;
				Total_Moisture_lay[nn][hh] = 0.5;
			}

			if (Frozen_ID_lay[nn][hh] == 1)
				Soil_Water_lay[nn][hh] = TMPB_W[Soil_ID[hh]];
			else
				Soil_Water_lay[nn][hh] = Total_Moisture_lay[nn][hh];

			// Mass conservation checks:
			if (Total_Moisture_lay[nn][hh] > Porosity_lay[nn][hh])
				Total_Moisture_lay[nn][hh] = Porosity_lay[nn][hh];
			if (Soil_Water_lay[nn][hh] > Total_Moisture_lay[nn][hh])
				Soil_Water_lay[nn][hh] = Total_Moisture_lay[nn][hh];
			Soil_Ice_lay[nn][hh] = Total_Moisture_lay[nn][hh] - Soil_Water_lay[nn][hh];
			if (Soil_Ice_lay[nn][hh] < 0.0)
				Soil_Ice_lay[nn][hh] = 0.0;
		} // for nn

		  // Start Hayashi's algorithm
		  // For the 1st time step, calculate the initial values of Cum_Thaw & Cum_Frozen from initial Thaw_D & Frozen_D
		if (getstep() == 1) { // first CRHM timestep
			if (Thaw_D[hh] > 0.0) {
				f[hh] = 0.0;
				I_Avg = 0;
				for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
					++I_Avg;
					f[hh] += Soil_Water_lay[nn][hh] * Soil_depths_lay[nn][hh];
					if (Thaw_D[hh] < Cum_d_lay[nn][hh]) break;

				}
				f[hh] /= Cum_d_lay[I_Avg - 1][hh];
				if (Alpha_ID[hh] >0)
					Cum_Thaw[hh] = Thaw_D[hh] * Thaw_D[hh] * Rho_Ice*f[hh] * Water_Ice / (2.0*86400.0); // reverse of Eq. 4 (and 86400 is for daily totals - needs changing for timestep)
				else
					Cum_Thaw[hh] = Thaw_D[hh] * Thaw_D[hh] / (Alpha_T[hh] * Alpha_T[hh] * 86400.0); // reverse of Eq. (4) //daily value

				Cum_Frozen[hh] = 0.0;
				Frozen_D[hh] = 0.0;

				FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
				ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];
				FrntDepthType_array[FrontCnt[hh]][hh] = 1;
			}
			else { // i.e. Frozen_D[hh] > 0.0
				f[hh] = 0.0;
				I_Avg = 0;
				for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
					I_Avg++;
					f[hh] += Soil_Ice_lay[nn][hh];
					if (Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
				}
				f[hh] /= I_Avg;
				if (Alpha_ID[hh] >0)
					Cum_Frozen[hh] = Frozen_D[hh] * Frozen_D[hh] * Rho_Water*f[hh] * Water_Ice / (2.0*86400.0); // reverse of Eq. (4)
				else
					Cum_Frozen[hh] = Frozen_D[hh] * Frozen_D[hh] / (Alpha_F[hh] * Alpha_F[hh] * 86400.0); // reverse of Eq. (4) //daily value

				Cum_Thaw[hh] = 0.0;
				Thaw_D[hh] = 0.0;

				FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
				FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
				FrntDepthType_array[FrontCnt[hh]][hh] = -1;
			}
			++FrontCnt[hh];  // no need to check
		} // end of first time step
		else {      // other time steps
			if (Tsurface[hh] > 0.0) {  // surface thaw condition
				if (Last_Tsurf[hh] < 0.0) { // save frozen front
					FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
					FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
					FrntDepthType_array[FrontCnt[hh]][hh] = -1;
					if (FrontCnt[hh] < MaxFrontCnt - 1)
						++FrontCnt[hh];
					else {
						CRHMException TExcept("Maximum # of fronts exceeded ", TERMINATE);
						LogError(TExcept);
						throw TExcept;
					}
					FrntDepthType_array[FrontCnt[hh]][hh] = 1;
				}
				Frozen_D[hh] = 0.0;
				Cum_Frozen[hh] = 0.0;
				Lamda_b[hh] = 0.0;
				f[hh] = 0.0;
				I_Avg = 0;
				// calculate the thaw penetration
				for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
					f[hh] += Total_Moisture_lay[nn][hh] * Soil_depths_lay[nn][hh];
					++I_Avg;
					Get_Heat_Param_Soil(1.0, nn);
					Lamda_b[hh] += (Soil_depths_lay[nn][hh] / C_K0[hh]);
					if (Thaw_D[hh] < Cum_d_lay[nn][hh]) break;
				}
				f[hh] /= Cum_d_lay[I_Avg - 1][hh];
				Lamda_b[hh] = Cum_d_lay[I_Avg - 1][hh] / Lamda_b[hh];
				if (Alpha_ID[hh] >0)
					Alpha = sqrt(2.0 / (Rho_Ice*f[hh] * Water_Ice));
				else
					Alpha = Alpha_T[hh];
				Cum_Thaw[hh] += Lamda_b[hh] * Tsurface[hh];

				Thaw_D[hh] = Alpha * sqrt(86400.0*Cum_Thaw[hh]); //daily value

				FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
				ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];

				if (FrontCnt[hh] > 1 && FrntDepth_array[FrontCnt[hh]][hh] >= FrntDepth_array[FrontCnt[hh] - 1][hh]) { // caught up ?
					FrntDepth_array[FrontCnt[hh] - 1][hh] = 0.0;
					FrontCnt[hh] -= 2; // go back to earlier thaw front
					Cum_Thaw[hh] = sqr(FrntDepth_array[FrontCnt[hh]][hh] / Alpha) / 86400.0;
				}
			} // end of surface thaw condition
			else {   // surface frozen condition
				if (Last_Tsurf[hh] > 0.0) { // save thaw front
					FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
					ThawCum_array[FrontCnt[hh]][hh] = Cum_Thaw[hh];
					FrntDepthType_array[FrontCnt[hh]][hh] = 1;
					if (FrontCnt[hh] < MaxFrontCnt - 1)
						++FrontCnt[hh];
					else {
						CRHMException TExcept("Maximum # of fronts exceeded ", TERMINATE);
						LogError(TExcept);
						throw TExcept;
					}
					FrntDepthType_array[FrontCnt[hh]][hh] = -1;
				}
				Thaw_D[hh] = 0.0;
				Cum_Thaw[hh] = 0.0;
				Lamda_b[hh] = 0.0;
				f[hh] = 0.0;
				I_Avg = 0.0;
				// calculate the frost penetration
				for (long nn = 0; nn < Soil_Layers[hh]; ++nn) {
					f[hh] += Total_Moisture_lay[nn][hh] * Soil_depths_lay[nn][hh];
					if (Soil_Ice_lay[nn][hh] < 0.0)
						Soil_Ice_lay[nn][hh] = 0.0;
					Get_Heat_Param_Soil(-1.0, nn);
					Lamda_b[hh] += (Soil_depths_lay[nn][hh] / C_K0[hh]);
					I_Avg++;
					if (Frozen_D[hh] < Cum_d_lay[nn][hh]) break;
				}
				f[hh] /= Cum_d_lay[I_Avg - 1][hh];
				Lamda_b[hh] = Cum_d_lay[I_Avg - 1][hh] / Lamda_b[hh];
				if (Alpha_ID[hh] >0)
					Alpha = sqrt(2.0 / (Rho_Water*f[hh] * Water_Ice));
				else
					Alpha = Alpha_F[hh];

				Cum_Frozen[hh] += -1.0* Lamda_b[hh] * Tsurface[hh];
				Frozen_D[hh] = Alpha * sqrt(86400.0*Cum_Frozen[hh]); //daily value

				FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
				FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];

				if (FrontCnt[hh] > 1 && FrntDepth_array[FrontCnt[hh]][hh] >= FrntDepth_array[FrontCnt[hh] - 1][hh]) { // caught up ?
					FrntDepth_array[FrontCnt[hh] - 1][hh] = 0.0;
					FrontCnt[hh] -= 2; // go back to earlier freeze front
					Cum_Frozen[hh] = sqr(FrntDepth_array[FrontCnt[hh]][hh] / Alpha) / 86400.0;
				}
			} // end of surface frozen condition
		} //end of other time step
		Last_Tsurf[hh] = Tsurface[hh];

		if (laststep()) {
			if (Tsurface[hh] > 0) {
				FrntDepth_array[FrontCnt[hh]][hh] = Thaw_D[hh];
				ThawCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
				FrntDepthType_array[FrontCnt[hh]][hh] = 1;
			}
			else {
				FrntDepth_array[FrontCnt[hh]][hh] = Frozen_D[hh];
				FreezeCum_array[FrontCnt[hh]][hh] = Cum_Frozen[hh];
				FrntDepthType_array[FrontCnt[hh]][hh] = -1;
			}
			++FrontCnt[hh]; // no need to check
		}
	} // for hh

}

void ClassHMSA::Get_Heat_Chad(long nn) {

	float Minerals = 1.0 - Porosity_lay[nn][hh] - Organic_lay[nn][hh];

	float x_a = K_Air;
	float x_w = Soil_Water_lay[nn][hh];
	float x_s = 1.0 - Porosity_lay[nn][hh] + Soil_Ice_lay[nn][hh];
	float lam_s;

	if (Minerals < 0.1)     // Organic Soil
		lam_s = K_Organic;
	else if (Organic_lay[nn][hh] < 0.1) // Mineral Soil
		lam_s = K_Minerals;
	else   //mixed
		lam_s = (Minerals*K_Minerals + Organic_lay[nn][hh] * K_Organic) / x_s;

	float n = Porosity_lay[nn][hh];

	float g_a;
	if (x_w >= 0.09)
		g_a = 0.333 - x_a / n * (0.333 - 0.035);
	else
		g_a = 0.013 + 0.944*x_w;

	float g_c = 1.0 - 2.0*g_a;

	//float Fs = 1.0/3.0*(2.0/(1 + (ks_s[soil_type_lay[nn][hh]]/lam_w-1.0)*0.125)
	//             + (1.0/((1 + (ks_s[soil_type_lay[nn][hh]]/lam_w-1.0)*0.75))));

	//float Fa = 1.0/3.0*(2.0/(1 + (lam_a/lam_w-1.0)*ga) + (1.0/((1 + (lam_a/lam_w-1.0)*gc))));

	float F_a = 1.0 / 3.0*(2.0 / (1.0 + (lam_a / lam_w - 1.0)*g_a) + 1.0 / (1.0 + (lam_a / lam_w - 1.0)*g_c));
	float F_s = 1.0 / 3.0*(2.0 / (1.0 + (lam_s / lam_w - 1.0)*g_a) + 1.0 / (1.0 + (lam_s / lam_w - 1.0)*g_c));

	//float a = Farouki_a(por_s[soil_type_lay[nn][hh]]);
	float a = Farouki_a(Porosity_lay[nn][hh]);

	// Calculate thermal cond. (W/m/K) of each layer depending on thermal & saturation condition (C_K0 in HMSA):
	// if layer is saturated & frozen:
	C_K0[hh] = lam_i * a*a + lam_s * sqr(1.0 - a)            // lamis_lay[nn][hh]
		+ lam_s * lam_i*(2 * a - 2 * sqr(a))
		/ (lam_s*a + lam_i * (1.0 - a));
	// if layer is satureated & UNfrozen:
	C_K0[hh] = lam_w * a*a + lam_s * sqr(1.0 - a)
		+ lam_s * lam_w*(2 * a - 2 * sqr(a))   // lamws_lay[nn][hh]
		/ (lam_s*a + lam_w * (1.0 - a));
	// if layer is UNsaturated & UNfrozen:
	C_K0[hh] = (x_w*lam_w + F_a * x_a*lam_a + F_s * x_s*lam_s) // lamwsa_lay[nn][hh]
		/ (x_w + F_a * x_a + F_s * x_s);
}

void ClassHMSA::Get_Heat_Param_Soil(float Soil_Temp, long nn) {

	// Subroutine to calculate soil heat parameters (method to be chosen by user)
	// uses: int Method_ID, float bulkdensity, Porosity, Organic, Soil_Water, Soil_Ice.
	// parameters: Soil_Temp, layer.
	// returns: C_K0 = conductivity; C_K1 = specific  heat capacity

	float Air, Minerals; //repsective volumetric fractions of soil air and minerals
	float KersNumber, SoilDryCond, SoilSatCond; // for method 2
	float Sr, g_a, g_c, F_a, F_s, x_a, x_w, x_s, lam_a, lam_w, lam_s, F_i, x_i, lam_i, Solid; //for method 3

	Minerals = 1.0 - Porosity_lay[nn][hh] - Organic_lay[nn][hh];
	if (Minerals < 0.0) Minerals = 0.0;
	Air = Porosity_lay[nn][hh] - Soil_Water_lay[nn][hh] - Soil_Ice_lay[nn][hh];
	if (Air < 0.0) Air = 0.0;
	//    Rho_Soil = BulkDensity_lay[nn][hh] / (1.0 - Porosity_lay[nn][hh]);
	Sr = (Soil_Water_lay[nn][hh] + Soil_Ice_lay[nn][hh]) / Porosity_lay[nn][hh];

	switch (Method_ID[hh]) {
	case 1:               //Johansen Complete
		if (Soil_Temp < -0.5)    // frozen soil
			KersNumber = Sr;
		else if (Organic_lay[nn][hh] > Minerals)
			KersNumber = Sr * Sr;
		else
			KersNumber = 0.7*log10(Sr) + 1.0; //coarse mineral soil
											  //              KersNumber = 1.0*log10(Sr)+1.0; //fine mineral soil

		SoilSatCond = pow(K_Organic, Organic_lay[nn][hh])*pow(K_Minerals, Minerals)*pow(K_Ice, Soil_Ice_lay[nn][hh])
			*pow(K_Water, (Soil_Water_lay[nn][hh] + Air));
		if (Organic_lay[nn][hh] > Minerals) {
			if (Soil_Temp > -0.5)
				SoilDryCond = 0.05;
			else
				SoilDryCond = 0.55;
		}
		else
			SoilDryCond = (0.135*BulkDensity_lay[nn][hh] + 64.7) / (2700.0 - 0.947*BulkDensity_lay[nn][hh]);

		if (Soil_Temp < -0.5 && Organic_lay[nn][hh] > Minerals)
			C_K0[hh] = SoilDryCond * pow((SoilSatCond / SoilDryCond), KersNumber);
		else
			C_K0[hh] = KersNumber * (SoilSatCond - SoilDryCond) + SoilDryCond;
		break;
	case 2:   //Johansen  common
		KersNumber = Sr; //TDSA
		SoilSatCond = pow(K_Organic, Organic_lay[nn][hh]) * pow(K_Minerals, Minerals)*pow(K_Ice, Soil_Ice_lay[nn][hh])
			*pow(K_Water, (Soil_Water_lay[nn][hh] + Air));
		SoilDryCond = (0.135*BulkDensity_lay[nn][hh] + 64.7) / (2700. - 0.947*BulkDensity_lay[nn][hh]);
		C_K0[hh] = KersNumber * (SoilSatCond - SoilDryCond) + SoilDryCond;
		break;
	case 3:   //De Vries as Hayashi,2007
		if (Soil_Ice_lay[nn][hh] < 0.01) {  // Ice free
			lam_a = K_Air;
			x_a = Air;
			x_w = Soil_Water_lay[nn][hh] + Soil_Ice_lay[nn][hh];
		}
		else {      // Mostly Ice
			lam_a = K_Ice;
			x_a = Soil_Ice_lay[nn][hh];
			x_w = Soil_Water_lay[nn][hh];
		}
		lam_w = K_Water;
		x_s = 1.0 - Porosity_lay[nn][hh];
		if (Minerals < 0.1)     //Organic Soil
			lam_s = K_Organic;
		else if (Organic_lay[nn][hh] < 0.1) //Minreal Soil
			lam_s = K_Minerals;
		else   //mixed
			lam_s = (Minerals*K_Minerals + Organic_lay[nn][hh] * K_Organic) / x_s;

		g_a = 0.333 - x_a / Porosity[hh] * (0.333 - 0.035);
		g_c = 1.0 - 2.0 * g_a;
		F_a = 1.0 / 3.0*(2.0 / (1.0 + (lam_a / lam_w - 1.0)*g_a) + 1.0 / (1.0 + (lam_a / lam_w - 1.0)*g_c));
		F_s = 1.0 / 3.0*(2.0 / (1.0 + (lam_s / lam_w - 1.0)*g_a) + 1.0 / (1.0 + (lam_s / lam_w - 1.0)*g_c));
		C_K0[hh] = (x_w*lam_w + F_a * x_a*lam_a + F_s * x_s*lam_s) / (x_w + F_a * x_a + F_s * x_s);
		break;
	case 4:   //De Vries as Farouki, 1986_three soil materials used: Air, water and soild

		x_a = Air;
		x_w = Soil_Water_lay[nn][hh];
		x_s = 1.0 - Porosity_lay[nn][hh] + Soil_Ice_lay[nn][hh];

		lam_w = K_Water;
		if (x_w > 0.09)
			lam_a = K_Air + 0.0238*exp(0.0536*Soil_Temp); //estimated from fig. 91 in Farouki 1986.
		else
			lam_a = (0.0615 + 1.96*x_w)*0.418; //from Farouki 1986 pp110.
		lam_s = pow(K_Organic, Organic_lay[nn][hh] / x_s) * pow(K_Minerals, Minerals / x_s)*pow(K_Ice, Soil_Ice_lay[nn][hh] / x_s);
		if (x_w > 0.09)
			g_a = 0.333 - x_a / Porosity[hh] * (0.333 - 0.035);
		else
			g_a = 0.013 + 0.944*x_w;

		g_c = 1.0 - 2.0 * g_a;
		F_a = 1.0 / 3.0*(2.0 / (1.0 + (lam_a / lam_w - 1.0)*g_a) + 1.0 / (1.0 + (lam_a / lam_w - 1.0)*g_c));
		F_s = 1.0 / 3.0*(2.0 / (1.0 + (lam_s / lam_w - 1.0)*0.125) + 1.0 / (1.0 + (lam_s / lam_w - 1.0)*0.75));
		C_K0[hh] = (x_w*lam_w + F_a * x_a*lam_a + F_s * x_s*lam_s) / (x_w + F_a * x_a + F_s * x_s);
		break;
	case 5:   //Chad

		Get_Heat_Chad(nn);
	}
}

ClassSoil* ClassSoil::klone(string name) const {
	return new ClassSoil(name);
}

void ClassSoil::decl(void) {

	Description = "'Handles soil moisture throughout the year.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'";

	variation_set = VARIATION_1;

	declvar("culvert_Q", NHRU, "flow in culvert.", "(m^3/s)", &culvert_Q);

	declvar("culvert_water_H", NHRU, "depth of pond at culvert inlet.", "(m)", &culvert_water_H);

	declvar("culvert_water_A", NHRU, "surface area of culvert pond.", "(m^2)", &culvert_water_A);

	declvar("culvert_water_V", NHRU, "volume of water in culvert pond.", "(m^3)", &culvert_water_V);

	declvar("culvert_over_Q", NHRU, "flow over the road.", "(m^3/s)", &culvert_over_Q);

	declvar("culvert_evap", NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

	declstatdiag("cum_culvert", NHRU, "Cumulative culvert HRU flow.", "(m^3)", &cum_culvert);

	declstatdiag("cum_culvert_over", NHRU, "Cumulative culvert HRU overflow.", "(m^3)", &cum_culvert_over);

	decldiag("HD", NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", &HD);

	declparam("channel_slope", NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

	declparam("side_slope", NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

	declparam("culvert_diam", NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

	declparam("culvert_water_Dmax", NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

	declparam("number_culverts", NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

	declparam("culvert_type", NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


	variation_set = VARIATION_ORG;

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

	declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

	declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

	declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

	declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
		"portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

	declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

	decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

	decllocal("cum_Sd_evap", NHRU, "cumulative Sd evap over HRU.", "(mm)", &cum_Sd_evap);

	declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

	declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

	declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

	declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

	declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

	declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

	declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

	declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

	declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

	declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

	declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

	declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

	declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

	declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

	declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

	declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

	declstatdiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

	declstatdiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);


	decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

	decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

	decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

	decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

	decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

	decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

	decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

	decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

	declparam("Sdinit", NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
		"Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

	declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
		"that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

	declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

	declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

	declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

	declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

	declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

	declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

	declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

	declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
		"Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
		&soil_withdrawal, &soil_withdrawal_Tables, 2);

	declparam("cov_type", NHRU,
		"[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
		"0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

	declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

	declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit.", "()", &inhibit_evap);


	declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

	declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


	evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);


	declgetvar("*", "infil", "(mm/int)", &infil);

	snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

	runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

	meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);
}

void ClassSoil::init(void) {

	nhru = getdim(NHRU);

	if (snowinfilDiv > 1) {
	 string S = "Soil:  \"snowinfil\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (evapDiv > 1) {
	 string S = "Soil:  \"hru_evap\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (meltrunoffDiv > 1) {
	 string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (runoffDiv > 1) {
	 string S = "Netroute:  \"runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {

		if (soil_moist[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}

		if (soil_rechr[hh] > soil_rechr_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}

		if (soil_rechr_max[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
			throw TExcept;
		}

		if (Sdinit[hh] > Sdmax[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (gw_init[hh] > gw_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		soil_rechr[hh] = soil_rechr_init[hh];
		soil_moist[hh] = soil_moist_init[hh];

		redirected_residual[hh] = 0.0;
		cum_redirected_residual[hh] = 0.0;

		Sd[hh] = Sdinit[hh];

		gw[hh] = gw_init[hh];

		hru_cum_actet[hh] = 0.0;
		cum_hru_condense[hh] = 0.0;
		cum_Sd_evap[hh] = 0.0;
		cum_infil_act[hh] = 0.0;

		soil_runoff_D[hh] = 0.0;
		soil_ssr_D[hh] = 0.0;
		soil_gw_D[hh] = 0.0;
		gw_flow_D[hh] = 0.0;
		infil_act[hh] = 0.0;
		infil_act_D[hh] = 0.0;

		cum_soil_runoff[hh] = 0.0;
		cum_soil_ssr[hh] = 0.0;
		cum_rechr_ssr[hh] = 0.0;
		cum_soil_gw[hh] = 0.0;
		cum_gw_flow[hh] = 0.0;

		cum_runoff_to_Sd[hh] = 0.0;

		if (variation == VARIATION_1) {
			if (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) {
			 string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + std::to_string(hh + 1);
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}
			culvert_water_V[hh] = 0.0;
			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;
			cum_culvert[hh] = 0.0;
			cum_culvert_over[hh] = 0.0;
		}
	}
}

void ClassSoil::run(void) {

	float soil_lower, excs, condense;
	float et;

	long nstep = getstep();

	if (nstep == 1)
		for (hh = 0; chkStruct(); ++hh) {
			LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
			soil_moist_Init[hh] = soil_moist[hh];
			soil_rechr_Init[hh] = soil_rechr[hh];
			Sd_Init[hh] = Sd[hh];
			gw_Init[hh] = gw[hh];
		}

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (snowinfilDiv == 1) // interval value
			snowinfil_buf[hh] = snowinfil[hh];

		if (runoffDiv == 1) // interval value
			runoff_buf[hh] = runoff[hh];

		if (meltrunoffDiv == 1) // interval value
			meltrunoff_buf[hh] = meltrunoff[hh];

		if (evapDiv == 1) // interval value
			hru_evap_buf[hh] = hru_evap[hh];

		if (nstep == 1) { // beginning of every day
			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;
			infil_act_D[hh] = 0.0;
		}

		hru_actet[hh] = 0.0;
		infil_act[hh] = 0.0;
		soil_gw[hh] = 0.0;
		soil_ssr[hh] = 0.0;
		rechr_ssr[hh] = 0.0;

		if (hru_evap_buf[hh] < 0.0) {
			condense = -hru_evap_buf[hh];
			cum_hru_condense[hh] += condense;
			hru_evap_buf[hh] = 0.0;
		}
		else
			condense = 0.0;

		//******Add infiltration to soil and compute excess

		if (soil_moist_max[hh] > 0.0) {
			soil_lower = soil_moist[hh] - soil_rechr[hh];

			float potential = infil[hh] + snowinfil_buf[hh] + condense;

			soil_rechr[hh] = soil_rechr[hh] + potential;

			if (soil_rechr[hh] > soil_rechr_max[hh]) {
				excs = soil_rechr[hh] - soil_rechr_max[hh];
				soil_rechr[hh] = soil_rechr_max[hh];
				soil_lower = soil_lower + excs;
			}

			soil_moist[hh] = soil_lower + soil_rechr[hh];

			if (soil_moist[hh] > soil_moist_max[hh]) {
				excs = soil_moist[hh] - soil_moist_max[hh];
				soil_moist[hh] = soil_moist_max[hh];
			}
			else
				excs = 0.0;

			infil_act[hh] = potential - excs;
			cum_infil_act[hh] += infil_act[hh];
			infil_act_D[hh] += infil_act[hh];

			//  Handle subsurface runoff

			if (!inhibit_evap[hh]) { // only when no snowcover
				rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;
				if (rechr_ssr[hh] > soil_rechr[hh])
					rechr_ssr[hh] = soil_rechr[hh];

				soil_rechr[hh] -= rechr_ssr[hh];
				if (soil_rechr[hh] < 0.0)
					soil_rechr[hh] = 0.0;

				soil_moist[hh] -= rechr_ssr[hh];
				soil_ssr[hh] = rechr_ssr[hh];
				cum_rechr_ssr[hh] += rechr_ssr[hh];
			}

			float s2gw_k = soil_gw_K[hh] / Global::Freq;

			//  Handle excess to gw

			if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
				soil_gw[hh] = s2gw_k;
				excs -= s2gw_k;
			}
			else { // to gw
				soil_gw[hh] = excs;
				excs = 0.0;
			}

			//  Handle excess to interflow or runoff

			if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow
				soil_ssr[hh] += excs;
				excs = 0.0;
			}
		}
		else { // soil_moist_max <= 0.0, i.e. Pond
			excs = infil[hh] + snowinfil_buf[hh] + condense;
		}

		float runoff_to_Sd = 0.0;

		soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int)

		cum_redirected_residual[hh] += redirected_residual[hh];

		redirected_residual[hh] = 0;

		if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
			float Fix = -12.0;
			if (soil_runoff[hh] / Sdmax[hh] < 12.0)
				Fix = -soil_runoff[hh] / Sdmax[hh];
			float Ds = (Sdmax[hh] - Sd[hh])*(1 - exp(Fix));

			if (soil_moist_max[hh] <= 0.0) // handle pond
				Ds = Sdmax[hh] - Sd[hh];

			if (Ds > 0.0) {
				if (soil_runoff[hh] > Ds) {
					soil_runoff[hh] -= Ds;
					if (soil_runoff[hh] < 0.0)
						soil_runoff[hh] = 0.0;
					Sd[hh] += Ds;
					runoff_to_Sd += Ds;
				}
				else {
					Sd[hh] += soil_runoff[hh];
					runoff_to_Sd += soil_runoff[hh];
					soil_runoff[hh] = 0.0;
				}
			}
		}

		if (variation == VARIATION_1) {

			float culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;

			if ((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
				culvert_water_V[hh] += soil_runoff[hh] * (hru_area[hh] * 1000.0); // convert mm to m3
				soil_runoff[hh] = 0.0;

				culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

				if (culvert_water_H[hh] > 0.0) {

					// calculate overflow if culvert level exceeds Dmax

					culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

					if (culvert_water_H[hh] > culvert_water_Dmax[hh]) { // (m) overflow over road
						culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
						float maxVol = pow(culvert_water_Dmax[hh], 3.0) / (3.0*channel_slope[hh] * side_slope[hh]); // (m3)

						culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400.0*Global::Freq; // (m3) to (m3/int)
						culvert_water_V[hh] = maxVol; // (m3)

						cum_culvert_over[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
						soil_runoff[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
					}
					HD[hh] = culvert_water_H[hh] / culvert_diam[hh];

					// calculate flow through culvert

					if (HD[hh] <= 0.0)
						culvert_Q[hh] = 0.0;
					else if (HD[hh] < 1.5)
						culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
							+ 0.159413*HD[hh] + 0.00772254)*culvert_C[culvert_type[hh]] * number_culverts[hh] * pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
					else
						culvert_Q[hh] = culvert_C[culvert_type[hh]] * number_culverts[hh] * 0.785*pow(culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

					if (culvert_water_V[hh] > culvert_Q[hh] * 86400.0 / Global::Freq) // (m3/s) to (m3))
						culvert_water_V[hh] -= culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
					else {
						culvert_Q[hh] = culvert_water_V[hh] * Global::Freq / 86400.0;  // (m3) to (m3/s)
						culvert_water_V[hh] = 0.0;
					}

					cum_culvert[hh] += culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3/int)
					soil_runoff[hh] += culvert_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
				}
				culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (channel_slope[hh] * side_slope[hh]); // used for evaporation
			} // culvert addition
		}

		soil_runoff_D[hh] += soil_runoff[hh];
		cum_soil_runoff[hh] += soil_runoff[hh];
		cum_runoff_to_Sd[hh] += runoff_to_Sd;

		if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
			float Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
			if (Sd2gw_k > Sd[hh])
				Sd2gw_k = Sd[hh];
			soil_gw[hh] += Sd2gw_k;
			Sd[hh] -= Sd2gw_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		soil_gw_D[hh] += soil_gw[hh];
		cum_soil_gw[hh] += soil_gw[hh];

		gw[hh] += soil_gw[hh];
		gw_flow[hh] = 0.0;
		if (gw[hh] > gw_max[hh]) {
			gw_flow[hh] += (gw[hh] - gw_max[hh]);
			gw[hh] = gw_max[hh];
		}

		if (gw_max[hh] > 0.0) { // prevents divide by zero error
			float spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
			gw[hh] -= spill;
			gw_flow[hh] += spill;
		}

		gw_flow_D[hh] += gw_flow[hh];
		cum_gw_flow[hh] += gw_flow[hh];

		if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
			float Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
			if (Sd2ssr_k >= Sd[hh])
				Sd2ssr_k = Sd[hh];
			soil_ssr[hh] += Sd2ssr_k;
			Sd[hh] -= Sd2ssr_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		float s2ssr_k = lower_ssr_K[hh] / Global::Freq;
		if (s2ssr_k > 0.0) {
			float avail = soil_moist[hh] - soil_rechr[hh];
			if (s2ssr_k >= avail)
				s2ssr_k = avail;
			soil_moist[hh] -= s2ssr_k;
			soil_ssr[hh] += s2ssr_k;
		}

		cum_soil_ssr[hh] += soil_ssr[hh];
		soil_ssr_D[hh] += soil_ssr[hh];

		//******Compute actual evapotranspiration

		float culvert_pond = 0.0; // convert m3 to mm

		float culvert_evapL = 0;

		if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation
			culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
			culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

			if (culvert_evapL > culvert_pond) // limit to amount available
				culvert_evapL = culvert_pond;

			culvert_evap[hh] = culvert_evapL;
			hru_actet[hh] += culvert_evapL;
			culvert_water_V[hh] = (culvert_pond - culvert_evapL)*(hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
		}

		float avail_evap = hru_evap_buf[hh] - culvert_evapL;
		if (Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
			avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
		else
			avail_evap = 0.0;

		if (Sd[hh] > 0.0 && avail_evap > 0.0) {
			if (Sd[hh] >= avail_evap) {
				Sd[hh] -= avail_evap;
				if (Sd[hh] < 0.0)
					Sd[hh] = 0.0;
			}
			else {
				avail_evap = Sd[hh];
				Sd[hh] = 0.0;
			}
			cum_Sd_evap[hh] += avail_evap;
			hru_actet[hh] += avail_evap;
		}
		else
			avail_evap = 0.0;

		avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

		if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

			float pctl, pctr, etl, ets, etr;

			if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
				pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				pctl = 0.0;

			pctr = soil_rechr[hh] / soil_rechr_max[hh];

			etr = avail_evap; // default

			switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
			case 1: //******sandy soil
				if (pctr < 0.25)
					etr = 0.5*pctr*avail_evap;
				break;
			case 2: //******loam soil
				if (pctr < 0.5)
					etr = pctr * avail_evap;
				break;
			case 3: //******clay soil
				if (pctr <= 0.33)
					etr = 0.5*pctr*avail_evap;
				else if (pctr < 0.67)
					etr = pctr * avail_evap;
				break;
			case 4: //******organic soil
					//         use default above etr = avail_evap;
				break;
			} // recharge switch

			if (etr > avail_evap) {
				etl = 0.0; // default value
				etr = avail_evap;
			}
			else
				etl = avail_evap - etr; // default value

			switch (soil_withdrawal_Tables[1][hh]) {  // handle lower layer
			case 1: //******sandy soil
				if (pctl < 0.25)
					etl = 0.5*pctl*etl;
				break;
			case 2: //******loam soil
				if (pctl < 0.5)
					etl = pctl * etl;
				break;
			case 3: //******clay soil
				if (pctl <= 0.33)
					etl = 0.5*pctl*etl;
				else if (pctr < 0.67)
					etl = pctl * etl;
				break;
			case 4: //******organic soil
					//         use default above etl = avail_evap - etr;
				break;
			} // lower switch

			  //******Soil moisture accounting  Remember that soil_moist includes soil_rechr[hh][hh]

			long et_type = cov_type[hh];

			//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
			//****** et_type = 1 - recharge layer only, crops - cov_type = 1
			//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

			if (transp_limited[hh] == 1 && et_type == 2)
				et_type = 1;

			et = 0.0;

			switch (et_type) {  // handle evaporation
			case 0:   // avail_evap <= 0
				break;
			case -1:  // avail_evap <= 0
				break;
			case 1:
				if (etr > soil_rechr[hh]) {
					soil_rechr[hh] = 0.0;
					et = soil_rechr[hh];
				}
				else {
					soil_rechr[hh] = soil_rechr[hh] - etr;
					et = etr;
				}
				soil_moist[hh] = soil_moist[hh] - et;
				break;
			case 2:
				if (etr + etl >= soil_moist[hh]) {
					et = soil_moist[hh];
					soil_moist[hh] = 0.0;
					soil_rechr[hh] = 0.0;
				}
				else {
					et = etr + etl;
					soil_moist[hh] = soil_moist[hh] - et;

					if (etr > soil_rechr[hh]) {
						soil_rechr[hh] = 0.0;
					}
					else
						soil_rechr[hh] = soil_rechr[hh] - etr;
				}
				break;
			} // switch

			hru_actet[hh] += et;

		} // soil_moist[hh] > 0.0

		if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
			hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

		hru_cum_actet[hh] += hru_actet[hh];

		if (nstep == 0) { // end of every day
			if (snowinfilDiv > 1) // daily value - ready for next day
				snowinfil_buf[hh] = snowinfil[hh] / snowinfilDiv;

			if (runoffDiv > 1) // daily value - ready for next day
				runoff_buf[hh] = runoff[hh] / runoffDiv;

			if (meltrunoffDiv > 1) // daily value - ready for next day
				meltrunoff_buf[hh] = meltrunoff[hh] / meltrunoffDiv;

			if (evapDiv > 1) // daily value - ready for next day
				hru_evap_buf[hh] = hru_evap[hh] / evapDiv;
		}
	} // for
}

void ClassSoil::finish(bool good) {

	float Allcum_soil_runoff = 0.0;
	float Allcum_soil_ssr = 0.0;
	float Allcum_rechr_ssr = 0.0;
	float Allcum_soil_gw = 0.0;
	float Allcum_gw_flow = 0.0;
	float Allcum_infil_act = 0.0;
	float Allcum_soil_moist_change = 0.0;
	float Allcum_Sd_change = 0.0;
	float Allcum_gw_change = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_Sd_evap        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Sd_evap[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'hru_actet'.");
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogDebug(" ");

		if (variation == VARIATION_1) {
			LogMessageA(hh, string("'" + Name + " (Soil)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
		}

		Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
		Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
		Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
		Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
		Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
		Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
		Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
		Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
		Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];
	}

	LogMessage(string("'" + Name + " (Soil)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
	LogMessage(string("'" + Name + " (Soil)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
	LogMessage(string("'" + Name + " (Soil)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
	LogMessage(string("'" + Name + " (Soil)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
	LogMessage(string("'" + Name + " (Soil)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
	LogMessage(string("'" + Name + " (Soil)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
	LogMessage(string("'" + Name + " (Soil)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
	LogMessage(string("'" + Name + " (Soil)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
	LogMessage(string("'" + Name + " (Soil)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
	LogDebug(" ");
}

string Evap_Resist_names[] = { "Penman-Monteith", "Dalton Bulk transfer", "Priestley_Taylor" };

Classevap_Resist* Classevap_Resist::klone(string name) const {
	return new Classevap_Resist(name);
}

void Classevap_Resist::decl(void) {

	Description = "'Evaluation evaporation model using Penman-Monteith, Dalton Bulk transfer and Priestley-Taylor.' \
                 'Uses observation Qsi (W/m^2), ' \
                 'Uses variable QsiS_Var (W/m^2)(slope) from Annandale, '\
                 'Uses variable QsiA_Var (W/m^2)(horizontal) from Annandale, '";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	declvar("hru_evap", NHRU, "interval evaporation", "(mm/int)", &evap);

	declvar("hru_evapD", NHRU, "daily sum of interval evaporation", "(mm/d)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

	decldiag("rc", NHRU, "stomatal resistance (Penman-Monteith)", "(s/m)", &rc);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	decldiagparam("Zwind", NHRU, "[10.0]", "0.0", "100.0", "Wind instrument height", "(m)", &Zwind);

	declparam("evap_type", NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Penman-Monteith, 1 = Dalton bulk transfer, 2 = Priestley-Taylor",
		"()", &evap_type);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

	declparam("rcs", NHRU, "[25]", "25.0", "5000.0", "stomatal resistance", "(s/m)", &rcs);

	declparam("Htmax", NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (Penman-Monteith)", "(m)", &Htmax);

	declparam("LAImax", NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImax);

	declparam("LAImin", NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImin);

	declparam("s", NHRU, "[1]", "0", "1", "seasonal growth index (Penman-Monteith)", "()", &s);

	declparam("PMmethod", NHRU, "[0]", "0", "1", "Penman-Monteith method, 0 = RC min, 1 = LAI", "()", &PM_method);

	declparam("soil_type", NHRU, "[2]", "1", "12",
		"HRU soil type (1->11): sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay",
		"()", &soil_type);

	declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

	declgetvar("*", "Rn", "(mm/m^2*int)", &Rn);
	declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
	declgetvar("*", "RnD_POS", "(mm/m^2*d)", &RnD_POS);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_eamean", "(kPa)", &hru_eamean);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declreadobs("Ts", NHRU, "surface temperature", "(�C)", &Ts, HRU_OBS_misc, true);

	declreadobs("RnObs", NHRU, "all-wave", "(W/m^2)", &RnObs, HRU_OBS_Q, true);

	variation_set = VARIATION_0;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, false);

	variation_set = VARIATION_1;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);


	variation_set = VARIATION_2;

	declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


	variation_set = VARIATION_ORG;
}

void Classevap_Resist::init(void) {

	for (hh = 0; chkStruct(); ++hh) {

		if (evap_type[hh] == 1 && Ts == NULL) {
			CRHMException TExcept("'evap_Resist' Ts observation not available for Dalton bulk transfer!", TERMINATE);
			LogError(TExcept);
		}

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cum_evap[hh] = 0.0;
		evapD[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;

		if (Ht[hh] > Zwind[hh] / 0.67 && evap_type[hh] != 0) {
			CRHMException TExcept("Vegetation height greater than wind reference height, i.e. (Ht > Zwind/0.67)!", WARNING);
			LogError(TExcept);
		}
	}
	BeforeCorrectionRCS = rcs[0] < 0;

}

void Classevap_Resist::run(void) {

	float Q, rcstar, LAI, Z0, d, U, f1, f2, f3, f4, ra, ratio_rs_ra, p;

	const float Cp = 1.005; // (kJ/kg/K)

	if (getstep() == 1 && rcs[0] < 0)
		const_cast<float *> (rcs)[0] = -rcs[0];

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (nstep == 1 || Global::Freq == 1) // beginning of day
			evapD[hh] = 0.0;

		evap[hh] = 0.0;
		hru_actet[hh] = 0.0;

		if (inhibit_evap[hh])
			continue;

		switch (variation) {
		case VARIATION_ORG:
			Qsi_ = Qsi[hh];
			break;
		case VARIATION_1:
			Qsi_ = QsiS_Var[hh];
			break;
		case VARIATION_2:
			Qsi_ = QsiA_Var[hh];
			break;
		} // switch

		  // calculated every interval

		Q = Rn[hh] * (1.0 - F_Qg[hh]); // (mm/d)

		float Soil_Moist = (soil_moist[hh] / soil_Depth[hh] + SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][3];

		switch (evap_type[hh]) {

		case 0: // Penman-Monteith

			if (soil_moist[hh] > 0.0) { // else ignore

				Z0 = Ht[hh] / 7.6;
				d = Ht[hh] * 0.67;
				U = hru_u[hh]; // Wind speed (m/d)
				ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*U);

				rcstar = rcs[hh]; // rc min

				if (PM_method[hh] == 1) { // LAI
					LAI = Ht[hh] / Htmax[hh] * (LAImin[hh] + s[hh] * (LAImax[hh] - LAImin[hh]));
					rcstar = rcs[hh] * LAImax[hh] / LAI;
				}

				f1 = 1.0;
				if (Qsi_ > 0.0)
					f1 = max <float>(1.0, 500.0 / (Qsi_)-1.5);

				f2 = max <float>(1.0, 2.0*(Common::estar(hru_t[hh]) - hru_ea[hh]));

				p = soilproperties[soil_type[hh]][AIRENT] *
					pow(soilproperties[soil_type[hh]][PORE] / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]);

				f3 = max <float>(1.0, p / 40.0);

				f4 = 1.0;
				if (hru_t[hh] < 0.0 || hru_t[hh] > 40.0)
					f4 = 5000 / 50;

				if (RnObs != NULL && RnObs[hh] <= 0)
					rc[hh] = 5000.0;
				else if (Qsi_ <= 0)
					rc[hh] = 5000.0;
				else {
					rc[hh] = rcstar * f1*f2*f3*f4;
					if (rc[hh] > 5000.0 && !BeforeCorrectionRCS)
						rc[hh] = 5000.0;
				}

				ratio_rs_ra = rc[hh] / ra;

				evap[hh] = (delta(hru_t[hh])*Q*Global::Freq + (RHOa(hru_t[hh], hru_ea[hh], Pa[hh])
					*Cp / (lambda(hru_t[hh])*1e3)*(Common::estar(hru_t[hh]) - hru_ea[hh]) / (ra / 86400)))
					/ (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + ratio_rs_ra)) / Global::Freq;
			}

			break;

		case 1: // Dalton Bulk transfer

			if (soil_moist[hh] > 0.0) { // else ignore

				Z0 = Ht[hh] / 7.6;
				d = Ht[hh] * 0.67;
				U = hru_u[hh];
				ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*U);

				rcstar = rcs[hh]; // rc min

				f1 = 1.0;
				if (Qsi_ > 0.0)
					f1 = max <float>(1.0, 500.0 / (Qsi_)-1.5);

				f2 = max <float>(1.0, 2.0*(Common::estar(hru_t[hh]) - hru_ea[hh]));

				p = soilproperties[soil_type[hh]][AIRENT] *
					pow(soilproperties[soil_type[hh]][PORE] / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]);

				f3 = max <float>(1.0, p / 40.0);

				f4 = 1.0;
				if (hru_t[hh] < 5.0 || hru_t[hh] > 40.0)
					f4 = 5000 / 50;

				if (RnObs != NULL && RnObs[hh] <= 0)
					rc[hh] = 5000.0;
				else if (Qsi_ <= 0)
					rc[hh] = 5000.0;
				else {
					rc[hh] = rcstar * f1*f2*f3*f4;
					if (rc[hh] > 5000.0 && !BeforeCorrectionRCS)
						rc[hh] = 5000.0;
				}

				float qs = 0.622*Common::estar(Ts[hh]) / (Pa[hh] - Common::estar(Ts[hh])*0.378); // Specific humidity (kg/kg)
				float q = 0.622*hru_ea[hh] / (Pa[hh] - hru_ea[hh] * 0.378);

				evap[hh] = RHOa(hru_t[hh], hru_ea[hh], Pa[hh])*(qs - q) / ((ra + rc[hh]) / 86400) / Global::Freq;
			}
			break;

		case 2: // Priestley-Taylor
			if (Q > 0.0)
				evap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])); // restored amount to ground flux 11/21/16
			else
				evap[hh] = 0.0;
			break;

		} // switch

		if (evap[hh] < 0.0)
			evap[hh] = 0.0;

		cum_evap[hh] += evap[hh];
		evapD[hh] += evap[hh];
	} // for
}

void Classevap_Resist::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "'" + Name + " (evap_Resist)' " + Evap_Resist_names[evap_type[hh]] + " hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ";
		LogMessageA(hh, s.c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (evap_Resist)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double Classevap_Resist::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float Classevap_Resist::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double Classevap_Resist::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

float Classevap_Resist::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R0 = 2870;
	return (1E4*Pa / (R0*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

ClassevapD_Resist* ClassevapD_Resist::klone(string name) const {
	return new ClassevapD_Resist(name);
}

void ClassevapD_Resist::decl(void) {

	Description = "'Evaluation daily evaporation model using Penman-Monteith and Dalton Bulk transfer.'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	declvar("hru_evapD", NHRU, "daily evaporation", "(mm/d)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

	decldiag("rc", NHRU, "stomatal resistance (Penman-Monteith)", "(s/m)", &rc);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	decldiagparam("Zwind", NHRU, "[10.0]", "0.0", "100.0", "Wind instrument height", "(m)", &Zwind);

	declparam("evap_type", NHRU, "0", "0", "1", "Evaporation method for this HRU, 0 = Penman-Monteith, 1 = Dalton bulk transfer",
		"()", &evap_type);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

	declparam("rcs", NHRU, "[25]", "25.0", "5000.0", "stomatal resistance (Penman-Monteith/Dalton bulk transfer)", "(s/m)", &rcs);

	declparam("Htmax", NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (Penman-Monteith)", "(m)", &Htmax);

	declparam("LAImax", NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImax);

	declparam("LAImin", NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (Penman-Monteith)", "(m^2/m^2)", &LAImin);

	declparam("s", NHRU, "[1]", "0", "1", "seasonal growth index (Penman-Monteith)", "()", &s);

	declparam("PM_method", NHRU, "[0]", "0", "2", "Penman-Monteith method, 0 = RC min, 1 = LAI, 2 = bulk", "()", &PM_method);

	declparam("soil_type", NHRU, "[2]", " 1", "12",
		"HRU soil type (1->11): sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay", "()", &soil_type);

	declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column", "(m)", &soil_Depth);

	declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_eamean", "(kPa)", &hru_eamean);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, false);

	declobsfunc("Qsi", "Qsi_mean", &Qsi_mean, AVG, NULL, false);

	declreadobs("Ts", NHRU, "surface temperature", "(�C)", &Ts, HRU_OBS_misc, true);

	declobsfunc("Ts", "Tsmean", &Tsmean, AVG, NULL, true);
}

void ClassevapD_Resist::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {

		if (evap_type[hh] == 1 && Ts == NULL) {
			CRHMException TExcept("'evapD' Ts observation not available for Dalton bulk transport method!.", TERMINATE);
			LogError(TExcept);
		}

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		evapD[hh] = 0.0;
		cum_evap[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;

		if (Ht[hh] > Zwind[hh] / 0.67 && evap_type[hh] != 0) {
			CRHMException TExcept("Vegetation height greater than wind reference height, i.e. (Ht > Zwind/0.67)!", WARNING);
			LogError(TExcept);
		}
	}
}

void ClassevapD_Resist::run(void) {

	float Q, rcstar, LAI, Z0, d, U, f1, f2, f3, f4, p, ra, ratio_rs_ra;

	const float Cp = 1.005; // (kJ/kg/K)

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (inhibit_evap[hh] && nstep == 1) {
			evapD[hh] = 0.0;
			hru_actet[hh] = 0.0;
			continue;
		}

		if (nstep == 1 || Global::Freq == 1) { // beginning of day

			hru_actet[hh] = 0.0;

			Q = RnD[hh] * (1.0 - F_Qg[hh]); // daily value (mm/d)

			float Soil_Moist = (soil_moist[hh] / soil_Depth[hh] + SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][3];

			switch (evap_type[hh]) {

			case 0: // Penman-Monteith

				Z0 = Ht[hh] / 7.6;
				d = Ht[hh] * 0.67;
				U = max<float>(0.1, hru_umean[hh]);
				ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*U);

				rcstar = rcs[hh];

				if (PM_method[hh] == 1) {
					float LAI = Ht[hh] / Htmax[hh] * (LAImin[hh] + s[hh] * (LAImax[hh] - LAImin[hh]));
					rcstar = rcs[hh] * LAImax[hh] / LAI;
				}

				f1 = max <float>(1.0, 500.0 / (Qsi_mean[hh]) - 1.5);

				f2 = max <float>(1.0, 2.0*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]));
				if (f2 < 0.0) // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
					f2 = 0.0;

				p = soilproperties[soil_type[hh]][AIRENT] *
					pow(soilproperties[soil_type[hh]][PORE] / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]); // /100.0

				f3 = max <float>(1.0, p / 40.0);

				f4 = 1.0;
				if (hru_tmean[hh] < 0.0 || hru_tmean[hh] > 40.0)
					f4 = 5000 / 50;

				rc[hh] = rcstar * f1*f2*f3*f4;
				if (rc[hh] > 5000.0)
					rc[hh] = 5000.0;

				ratio_rs_ra = rc[hh] / ra;

				evapD[hh] = (delta(hru_tmean[hh])*Q + (RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh]) * Cp / (lambda(hru_tmean[hh])*1e3)
					*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]) / (ra / 86400)))
					/ (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh])*(1.0 + ratio_rs_ra));
				break;

			case 1: // Dalton Bulk transfer

				Z0 = Ht[hh] / 7.6;
				d = Ht[hh] * 0.67;
				U = max<float>(0.1, hru_umean[hh]);
				ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*U);

				rcstar = rcs[hh]; // rc min

				f1 = 1.0;
				if (Qsi_mean[hh] > 0.0)
					f1 = max <float>(1.0, 500.0 / (Qsi_mean[hh]) - 1.5);

				f2 = max <float>(1.0, 2.0*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]));
				if (f2 < 0.0) // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
					f2 = 0.0;

				p = soilproperties[soil_type[hh]][AIRENT] *
					pow(soilproperties[soil_type[hh]][PORE] / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]); // /100.0

				f3 = max <float>(1.0, p / 40.0);

				f4 = 1.0;
				if (hru_tmean[hh] < 5.0 || hru_tmean[hh] > 40.0)
					f4 = 5000 / 50;

				rc[hh] = rcstar * f1*f2*f3*f4;
				if (rc[hh] > 5000.0)
					rc[hh] = 5000.0;

				float qs = 0.622*Common::estar(Tsmean[hh]) / (Pa[hh] - Common::estar(Tsmean[hh])*0.378); // Specific humidity (kg/kg)
				float q = 0.622*hru_eamean[hh] / (Pa[hh] - hru_eamean[hh] * 0.378);

				evapD[hh] = RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh])*(qs - q) / ((ra + rc[hh]) / 86400);
				break;

			} // switch

			cum_evap[hh] += evapD[hh];
		}
	} // for
}

void ClassevapD_Resist::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "**** " + Evap_names[evap_type[hh] + 2] + " ****";
		LogMessageA(hh, string("'" + Name + " (evapD_Resist)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0], s.c_str());
		LogMessageA(hh, string("'" + Name + " (evapD_Resist)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassevapD_Resist::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}


float ClassevapD_Resist::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassevapD_Resist::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

float ClassevapD_Resist::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R0 = 2870;
	return (1E4*Pa / (R0*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

ClassShutWall* ClassShutWall::klone(string name) const {
	return new ClassShutWall(name);
}

void ClassShutWall::decl(void) {

	Description = "'Evaluation evaporation model (Shuttleworth - Wallace).'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	declvar("hru_evap", NHRU, "evaporation, interval calculation from daily", "(mm/int)", &evap);

	declvar("hru_evapD", NHRU, "daily evaporation", "(mm)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation from daily", "(mm)", &cum_evap);

	decldiag("Cc", NHRU, "canopy weighting coefficient", "()", &Cc);

	decldiag("Cs", NHRU, "substrate weighting coefficient", "()", &Cs);

	decldiag("Ra", NHRU, "", "()", &Ra);

	decldiag("Rc", NHRU, "", "()", &Rc);

	decldiag("Rs", NHRU, "", "()", &Rs);

	decldiag("ETc", NHRU, "", "(mm/d)", &ETc);

	decldiag("ETs", NHRU, "", "(mm/d)", &ETs);

	decldiag("raa", NHRU, "aerodynamic resistance from canopy to reference height", "(s/m)", &raa);

	decldiag("rca", NHRU, "boundary resistance", "(s/m)", &rca);

	decldiag("rcs", NHRU, "canopy stomatal resistance", "(s/m)", &rcs);

	decldiag("rsa", NHRU, "aerodynamic resistance from soil to canopy", "(s/m)", &rsa);

	decldiag("rss", NHRU, "soil surface resistance", "(s/m)", &rss);


	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("Cr", NHRU, "[0.7]", "0.3", "0.9", "extinction coefficient", "(s/m)", &Cr);

	declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

	declparam("w", NHRU, "[0.004]", "0.0", "1.0", "canopy characteristic leaf width", "(m)", &w);

	declparam("z0g", NHRU, "[0.01]", "0.0", "1.0", "ground roughness length", "(m)", &z0g);

	declparam("rs", NHRU, "[250]", "0.0", "1e3", "mean stomatal resistance", "(s/m)", &rst);

	decldiagparam("gammab", NHRU, "[0.5]", "0.0", "1.0", "shielding factor", "()", &gammab);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	decldiagparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_t", "(m/s)", &hru_t);
	declgetvar("*", "hru_ea", "kPa", &hru_ea);

	declreadobs("Qn", NHRU, "net all-wave", "(W/m^2)", &Qn, HRU_OBS_Q);
	declreadobs("Qg", NHRU, "ground flux", "(W/m^2)", &Qg, HRU_OBS_Q);

}

void ClassShutWall::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cum_evap[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
	}
}

void ClassShutWall::run(void) {

	const float Cp = 1.005; // (kj/kg/K)

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		evapD[hh] = 0.0;
		hru_actet[hh] = 0.0;

		if (inhibit_evap[hh])
			continue;

		if (nstep == 1) { // beginning of every day

			z0 = 0.13*Ht[hh];
			d = 0.63*Ht[hh];

			if (Ht[hh] < 1.0)
				n = 2.5;
			else if (Ht[hh] < 10.0)
				n = 2.306 + 0.194*Ht[hh];
			else
				n = 4.25;

		} //  beginning of every day

		float U = hru_u[hh];

		float Ustar = CRHM_constants::kappa*U / log((Zwind[hh] - d) / z0);

		float kh = CRHM_constants::kappa*Ustar*(Ht[hh] - d);

		float rb = 100 / n * sqrt(w[hh] / (0.1*U)) / (1.0 - exp(-n / 2.0));

		raa[hh] = 1.0 / (CRHM_constants::kappa*Ustar)*log((Zwind[hh] - d) / (Ht[hh] - d)) + Ht[hh] / (n*kh)*(exp(n*(1 - (z0 + d) / Ht[hh])) - 1.0);
		rca[hh] = rb * gammab[hh] / LAI[hh];
		rcs[hh] = rst[hh] / (2.0*LAI[hh]);
		rsa[hh] = (Ht[hh] * exp(n) / (n*kh))*(exp(-n * z0g[hh] / Ht[hh]) - exp(-n * (z0 + d) / Ht[hh]));
		rss[hh] = 4000;

		float Rn = Qn[hh] // Watts
			* 86400 / 1e3 / lambda(hru_t[hh]); // (mm/d)
		float G = Qg[hh] // Watts
			* 86400 / 1e3 / lambda(hru_t[hh]); // (mm/d)
		float Rsn = Rn * exp(-Cr[hh] * LAI[hh]);


		Ra[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*raa[hh];
		Rc[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*rca[hh] + gamma(Pa[hh], hru_t[hh])*rcs[hh];
		Rs[hh] = (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]))*rsa[hh] + gamma(Pa[hh], hru_t[hh])*rss[hh];

		Cc[hh] = 1.0 / (1.0 + Rc[hh] * Ra[hh] / (Rs[hh] * (Rc[hh] + Ra[hh])));
		Cs[hh] = 1.0 / (1.0 + Rs[hh] * Ra[hh] / (Rc[hh] * (Rs[hh] + Ra[hh])));

		ETc[hh] = (delta(hru_t[hh])*(Rn - G)
			+ ((RHOa(hru_t[hh], hru_ea[hh], Pa[hh])*Cp*(Common::estar(hru_t[hh]) - hru_ea[hh]))
				- (delta(hru_t[hh])*rca[hh] * (Rsn - G)) / (raa[hh] + rca[hh])))
			/ (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + rcs[hh] / (raa[hh] + rca[hh])));

		ETs[hh] = (delta(hru_t[hh])*(Rn - G)
			+ ((RHOa(hru_t[hh], hru_ea[hh], Pa[hh])*Cp*(Common::estar(hru_t[hh]) - hru_ea[hh]))
				- (delta(hru_t[hh])*rsa[hh] * (Rn - Rsn)) / (raa[hh] + rsa[hh])))
			/ (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + rss[hh] / (raa[hh] + rca[hh])));

		evap[hh] = (Cc[hh] * ETc[hh] + Cs[hh] * ETs[hh]) / Global::Freq;

		cum_evap[hh] += evap[hh];

		evapD[hh] += evap[hh];

	} // for
}

void ClassShutWall::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassShutWall::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(1.63 * Pa / lambda(t)); // lambda (kJ/(kg �C))
}

float ClassShutWall::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R = 2870;
	return (1E4*Pa / (R*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

float ClassShutWall::lambda(float t) // Latent heat of vaporization  (kJ/(kg �C))
{
	return(2501.0 - 2.361 * t);
}

double ClassShutWall::delta(float t)  // Slope of sat vap p vs t, (kPa/�C)
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

ClassShutWallD* ClassShutWallD::klone(string name) const {
	return new ClassShutWallD(name);
}

void ClassShutWallD::decl(void) {

	Description = "'Daily evaluation evaporation model (Shuttleworth - Wallace).'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	declvar("hru_evapD", NHRU, "daily evaporation", "(mm)", &evapD);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation from daily", "(mm)", &cum_evap);

	declvar("Cc", NHRU, "canopy weighting coefficient", "()", &Cc);

	declvar("Cs", NHRU, "substrate weighting coefficient", "()", &Cs);

	decldiag("Ra", NHRU, "", "()", &Ra);

	decldiag("Rc", NHRU, "", "()", &Rc);

	decldiag("Rs", NHRU, "", "()", &Rs);

	decldiag("ETc", NHRU, "", "(mm/d)", &ETc);

	decldiag("ETs", NHRU, "", "(mm/d)", &ETs);

	decldiag("raa", NHRU, "aerodynamic resistance from canopy to reference height", "(s/m)", &raa);

	decldiag("rca", NHRU, "boundary resistance", "(s/m)", &rca);

	decldiag("rcs", NHRU, "canopy stomatal resistance", "(s/m)", &rcs);

	decldiag("rsa", NHRU, "aerodynamic resistance from soil to canopy", "(s/m)", &rsa);

	decldiag("rss", NHRU, "soil surface resistance", "(s/m)", &rss);


	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "1", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evapatation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("Cr", NHRU, "[0.7]", "0.3", "0.9", "extinction coefficient", "()", &Cr);

	declparam("LAI", NHRU, "[2.2]", "0.0", "20.0", "Leaf area index", "(m^2/m^2)", &LAI);

	declparam("w", NHRU, "[0.004]", "0.0", "1.0", "canopy characteristic leaf width", "(m)", &w);

	declparam("z0g", NHRU, "[0.01]", "0.0", "1.0", "ground roughness length", "(m)", &z0g);

	declparam("rs", NHRU, "[250]", "0.0", "1e3", "mean stomatal resistance", "(s/m)", &rst);

	decldiagparam("gammab", NHRU, "[0.5]", "0.0", "1.0", "shielding factor", "()", &gammab);

	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height(m)", "(m)", &Ht);

	decldiagparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);


	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_tmean", "(m/s)", &hru_tmean);
	declgetvar("*", "hru_eamean", "kPa", &hru_eamean);

	declreadobs("Qn", NHRU, "net all-wave", "(W/m^2)", &Qn, HRU_OBS_Q);
	declreadobs("Qg", NHRU, "ground flux", "(W/m^2)", &Qg, HRU_OBS_misc);

	declobsfunc("Qn", "Qnmean", &Qnmean, AVG);
	declobsfunc("Qg", "Qgmean", &Qgmean, AVG);

}

void ClassShutWallD::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cum_evap[hh] = 0.0;
		evapD[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
	}
}

void ClassShutWallD::run(void) {

	const float Cp = 1.005; // (kj/kg/K)

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (inhibit_evap[hh])
			continue;

		if (nstep == 1) { // beginning of every day

			hru_actet[hh] = 0.0;

			float z0 = 0.13*Ht[hh];
			float d = 0.63*Ht[hh];

			float n;
			if (Ht[hh] < 1.0)
				n = 2.5;
			else if (Ht[hh] < 10.0)
				n = 2.306 + 0.194*Ht[hh];
			else
				n = 4.25;

			float U = max<float>(hru_umean[hh], 0.1);

			float Ustar = CRHM_constants::kappa*U / log((Zwind[hh] - d) / z0);

			float kh = CRHM_constants::kappa*Ustar*(Ht[hh] - d);

			float rb = 100 / n * sqrt(w[hh] / (0.1*U)) / (1.0 - exp(-n / 2.0));

			raa[hh] = 1.0 / (CRHM_constants::kappa*Ustar)*log((Zwind[hh] - d) / (Ht[hh] - d)) + Ht[hh] / (n*kh)*(exp(n*(1 - (z0 + d) / Ht[hh])) - 1.0);
			rca[hh] = rb * gammab[hh] / LAI[hh];
			rcs[hh] = rst[hh] / (2.0*LAI[hh]);
			rsa[hh] = (Ht[hh] * exp(n) / (n*kh))*(exp(-n * z0g[hh] / Ht[hh]) - exp(-n * (z0 + d) / Ht[hh]));
			rss[hh] = 4000;

			float Rn = Qnmean[hh] // Watts
				* 86400 / 1e3 / lambda(hru_tmean[hh]); // (mm/d)
			float G = Qgmean[hh] // Watts
				* 86400 / 1e3 / lambda(hru_tmean[hh]); // (mm/d)
			float Rsn = Rn * exp(-Cr[hh] * LAI[hh]);


			Ra[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*raa[hh];
			Rc[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*rca[hh] + gamma(Pa[hh], hru_tmean[hh])*rcs[hh];
			Rs[hh] = (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh]))*rsa[hh] + gamma(Pa[hh], hru_tmean[hh])*rss[hh];

			Cc[hh] = 1.0 / (1.0 + Rc[hh] * Ra[hh] / (Rs[hh] * (Rc[hh] + Ra[hh])));
			Cs[hh] = 1.0 / (1.0 + Rs[hh] * Ra[hh] / (Rc[hh] * (Rs[hh] + Ra[hh])));

			ETc[hh] = (delta(hru_tmean[hh])*(Rn - G)
				+ ((RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh])*Cp*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]))
					- (delta(hru_tmean[hh])*rca[hh] * (Rsn - G)) / (raa[hh] + rca[hh])))
				/ (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh])*(1.0 + rcs[hh] / (raa[hh] + rca[hh])));

			ETs[hh] = (delta(hru_tmean[hh])*(Rn - G)
				+ ((RHOa(hru_tmean[hh], hru_eamean[hh], Pa[hh])*Cp*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]))
					- (delta(hru_tmean[hh])*rsa[hh] * (Rn - Rsn)) / (raa[hh] + rsa[hh])))
				/ (delta(hru_tmean[hh]) + gamma(Pa[hh], hru_tmean[hh])*(1.0 + rss[hh] / (raa[hh] + rca[hh])));

			evapD[hh] = Cc[hh] * ETc[hh] + Cs[hh] * ETs[hh];

			cum_evap[hh] += evapD[hh];

		} //  beginning of every day
	} // for
}

void ClassShutWallD::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (ShuttleWallaceD)' hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_evap[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (ShuttleWallace)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassShutWallD::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(1.63 * Pa / lambda(t)); // lambda (kJ/(kg �C))
}

float ClassShutWallD::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R = 2870;
	return (1E4*Pa / (R*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

float ClassShutWallD::lambda(float t) // Latent heat of vaporization  (kJ/(kg �C))
{
	return(2501.0 - 2.361 * t);
}

double ClassShutWallD::delta(float t)  // Slope of sat vap p vs t, (kPa/�C)
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

ClassIceBulb* ClassIceBulb::klone(string name) const {
	return new ClassIceBulb(name);
}

void ClassIceBulb::decl(void) {

	Description = "'Estimates ice bulb temperature.'";

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_rh", "(%)", &hru_rh);
	declgetvar("*", "hru_p", "(mm/int)", &hru_p);

	declvar("hru_icebulb", NHRU, "Estimates ice bulb temperature", "(�C)", &hru_icebulb);

	declvar("hru_rainI", NHRU, "rain", "(mm/int)", &hru_rainI);

	declstatdiag("cumhru_rainI", NHRU, "cumulative HRU rain", "(mm)", &cumhru_rainI);

	declvar("hru_snowI", NHRU, "snow", "(mm/int)", &hru_snowI);

	declstatdiag("cumhru_snowI", NHRU, "cumulative HRU snow", "(mm)", &cumhru_snowI);

	declstatdiag("cumhru_pI", NHRU, "cumulative HRU snow", "(mm)", &cumhru_pI);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	decldiagparam("tmaxI_allrain", NHRU, "[1.0]", "-10", "10", "precip all rain if HRU ice bulb temperature above or equal to this value",
		"(�C)", &tmaxI_allrain);

	decldiagparam("tmaxI_allsnow", NHRU, "[-1.0]", "-10", "10", "precip all snow if HRUice bulb  temperature below this value",
		"(�C)", &tmaxI_allsnow);

}

void ClassIceBulb::init(void) {

	nhru = getdim(NHRU);
	for (hh = 0; hh < nhru; ++hh) {
		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cumhru_rainI[hh] = 0.0;
		cumhru_snowI[hh] = 0.0;
		cumhru_pI[hh] = 0.0;
	}
}

void ClassIceBulb::run(void) {

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {
		float Tk = hru_t[hh] + CRHM_constants::Tm;
		float D = 0.0000206*pow(Tk / CRHM_constants::Tm, 1.75);
		float RHO = Pa[hh] * 1000.0 / (CRHM_constants::Rgas*Tk);

		float qt = CRHM_constants::em / (Pa[hh] * 1000.0)*611.213*exp(22.4422*hru_t[hh] / (CRHM_constants::Tm + hru_t[hh]));

		float lamda = 0.000076843*Tk + 0.003130762;

		float L;
		if (hru_t[hh] > 0.0)
			L = CRHM_constants::Lv;
		else
			L = CRHM_constants::Ls;

		float delta = CRHM_constants::em*L*qt / (CRHM_constants::Rgas*sqr(Tk));

		hru_icebulb[hh] = hru_t[hh] - L * (1.0 - hru_rh[hh] / 100.0)*qt / (CRHM_constants::Cp + L * delta) *(RHO*CRHM_constants::Cp*D / lamda);

		hru_snowI[hh] = 0.0;
		hru_rainI[hh] = 0.0;

		if (hru_p[hh] > 0.0) { //rain or snow determined by temperature
			if (hru_icebulb[hh] >= tmaxI_allrain[hh]) { // all rain
				hru_rainI[hh] = hru_p[hh];
			}
			else if (hru_icebulb[hh] <= tmaxI_allsnow[hh]) { // all snow
				hru_snowI[hh] = hru_p[hh];
			}
			else { // mixed
				hru_rainI[hh] = hru_p[hh] * (tmaxI_allrain[hh] - hru_icebulb[hh]) / (tmaxI_allrain[hh] - tmaxI_allsnow[hh]);
				hru_snowI[hh] = hru_p[hh] - hru_rainI[hh];
			}
		} // end if

		cumhru_rainI[hh] += hru_rainI[hh];
		cumhru_snowI[hh] += hru_snowI[hh];
		cumhru_pI[hh] = cumhru_pI[hh] + hru_snowI[hh] + hru_rainI[hh];
	}
}

Classlake* Classlake::klone(string name) const {
	return new Classlake(name);
}

void Classlake::decl(void) {

	Description = "'Calculates lake evaporation from the Meyer formula.'";

	declvar("hru_evap", NHRU, "interval evaporation", "(mm/int)", &hru_evap);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &hru_cum_evap);

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet);

	decldiag("Va", NHRU, "water vapour pressure, Vw*rh (Meyer)", "(mm)", &Va);

	decldiag("Vw", NHRU, "air vapour pressure (Meyer)", "(mm)", &Vw);

	declvar("lake_evap_month", NHRU, "monthly evaporation from rh", "(mm)", &lake_evap_month); // ***cannot be a state variable***

	declvar("hru_t_Mmean", NHRU, "HRU temperature", "(�C)", &hru_t_Mmean);

	declvar("hru_rh_Mmean", NHRU, "HRU rh", "()", &hru_rh_Mmean);

	declvar("hru_u_Mmean", NHRU, "HRU wind speed", "(m/s)", &hru_u_Mmean);

	decllocal("hru_t_acc", NHRU, "HRU t accumulated", "(�C)", &hru_t_acc);

	decllocal("hru_rh_acc", NHRU, "HRU rh accumulated", "()", &hru_rh_acc);

	decllocal("hru_u_acc", NHRU, "HRU u accumulated", "(m)", &hru_u_acc);

	decllocal("start_open_day", NHRU, "TDate format start of open water", "()", &start_open_day);

	decllocal("end_open_day", NHRU, "TDate format end of open water", "()", &end_open_day);

	decldiagparam("Meyer_C", NHRU, "[10.5]", "5.0", "15.0", "Meyer coefficient. (Recommended range 10.1->11)", "()", &Meyer_C);

	declparam("start_open_water", NHRU, "[120]", "1", "366", "Start of lake evaporation (Julian day)", "()", &start_open_water);

	declparam("end_open_water", NHRU, "[240]", "1", "366", "End of lake evaporation (Julian day)", "()", &end_open_water);

	decldiagparam("Meyer_B", TWELVE, "[-0.3, -2.8, -1.4, 2.0, 7.3, 8.8, 10.0, 9.6, 7.1, 3.0, -1.2, -2.6]", "-10.0", "20.0", "Meyer monthly intercept coefficient", "()", &Meyer_B);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_rh", "()", &hru_rh);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
}

void Classlake::init(void) {

	for (hh = 0; chkStruct(); ++hh) {
		lake_evap_month[hh] = 0.0;
		hru_evap[hh] = 0.0;
		hru_cum_evap[hh] = 0.0;
		hru_actet[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
		hru_rh_acc[hh] = 0.0;
		hru_t_acc[hh] = 0.0;
		hru_t_Mmean[hh] = 0.0;
		hru_rh_Mmean[hh] = 0.0;
		hru_u_Mmean[hh] = 0.0;
		start_open_day[hh] = 0;
		end_open_day[hh] = 0;
	}

	N_intervals = 0;
	DoMean = false;
	Ahead = false;
}

void Classlake::run(void) {

	dattim("now", itime);

	long nstep = getstep() % Global::Freq;

	if ((nstep == 1 || Global::Freq == 1) && (getstep() == 1 || itime[2] == 1) && !Ahead) { // beginning of every day

		ThisMonth = itime[1];

		DoMean = false;
		Ahead = false; // differentiates read ahead month from processing month

		N_intervals = 0;

		for (hh = 0; chkStruct(); ++hh) {
			//if ((int)Global::DTnow >= end_open_day[hh]) { // convert Julian to TDate
			//	start_open_day[hh] = (double)TDate(itime[0] - 1, 12, 31) + start_open_water[hh];

			//	if (end_open_water[hh] > start_open_water[hh])
			//		end_open_day[hh] = (double)TDate(itime[0] - 1, 12, 31) + end_open_water[hh];
			//	else
			//		end_open_day[hh] = (double)TDate(itime[0], 12, 31) + end_open_water[hh];
			//}

			hru_t_Mmean[hh] = 0.0;
			hru_rh_Mmean[hh] = 0.0;
			hru_u_Mmean[hh] = 0.0;

			hru_t_acc[hh] = 0.0;
			hru_rh_acc[hh] = 0.0;
			hru_u_acc[hh] = 0.0;

			lake_evap_month[hh] = 0.0;
			Va[hh] = 0.0;
			Vw[hh] = 0.0;

			hru_actet[hh] = 0.0;
			hru_evap[hh] = 0.0;
		} // for

		for (hh = 0; chkStruct(); ++hh) {
			if (std::stod(getTimeGG()) + 0.01 >= start_open_day[hh] && (std::stod(getTimeGG()) - 0.01 <= end_open_day[hh])) {
				//DaysMonth = MonthDaysCnt(getTimeGG());
				DoMean = true;
				Ahead = true;
			}
			else // no evaporation this month
				return;
		} // for

		if (DoMean)
			++Global::CRHMControlSaveCnt; // save state for backtrack

	} // beginning of month

	if (DoMean) {
		if (--DaysMonth == 0 || last_timestep()) {
			add();
			process();
			--Global::CRHMControlSaveCnt; // restore state to backtrack
			DoMean = false;
		} // if
		else {
			add();
		}
	} // if DoMean
	else if (N_intervals) { // normal entry after monthly lake evaporation
		Ahead = false;
		for (hh = 0; chkStruct(); ++hh) {
			hru_actet[hh] = 0.0;
			hru_evap[hh] = 0.0;

			if (std::stod(getTimeGG()) + 0.01 >= start_open_day[hh] && std::stod(getTimeGG()) - 0.01 <= end_open_day[hh]) {
				hru_evap[hh] = lake_evap_month[hh] / N_intervals;
				hru_cum_evap[hh] += hru_evap[hh];
			} // if
		} // for
	}
}

void Classlake::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

		LogMessageA(hh, string("'" + Name + " (lake_evap)' hru_cum_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_evap[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (lake_evap)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

	}
}

void Classlake::add(void) {
	++N_intervals;
	for (hh = 0; chkStruct(); ++hh) {
		hru_t_acc[hh] += hru_t[hh];
		hru_rh_acc[hh] += hru_rh[hh];
		hru_u_acc[hh] += hru_u[hh];
	} // for
}

void Classlake::process(void) {

	for (hh = 0; chkStruct(); ++hh) {
		hru_t_Mmean[hh] = hru_t_acc[hh] / N_intervals;
		hru_rh_Mmean[hh] = hru_rh_acc[hh] / N_intervals;
		hru_u_Mmean[hh] = hru_u_acc[hh] / N_intervals;

		long Index = ThisMonth - 1;
		if (hru_lat[hh] < 0.0) // Southern Hemisphere 6 months offset
			Index = (Index + 6) % 12;

		float Tw = 0.6*hru_t_Mmean[hh] + Meyer_B[Index];

		Vw[hh] = pow(10, (-7.903*(373.16 / (Tw + 273.16) - 1) + (5.028*log10(373.16 / (Tw + 273.16)))
			- (0.0000001382*(pow(10, (11.34*(1 - (373.16 / (Tw + 273.16))))) - 1))
			+ (0.008133*pow(10, (-3.491*((373.16 / (Tw + 273.16)) - 1))))) + 3.006);

		Va[hh] = Vw[hh] * hru_rh_Mmean[hh] / 100.0;

		lake_evap_month[hh] = 0.75002*Meyer_C[hh] * (Vw[hh] - Va[hh])*(1 + 0.06214*hru_u_Mmean[hh])*(1.0 + 3.28084e-5*hru_elev[hh]);

		hru_t_acc[hh] = 0.0;
		hru_rh_acc[hh] = 0.0;
		hru_u_acc[hh] = 0.0;
	} // for
}

ClassK_Estimate* ClassK_Estimate::klone(string name) const {
	return new ClassK_Estimate(name);
}

void ClassK_Estimate::decl(void) {

	Description = "'K_Estimate.' \
                 'original interval version,' \
                 'estimates Dts_snow_runoff_K and Dts_organic_runoff_K for module SoilDS.'";

	variation_set = VARIATION_ORG;

	declvar("v_L_upper", NHRU, "Darcy's lateral flow velocity in upper soil column (ie. recharge layer)", "(m/s)", &v_L_upper);
	declvar("v_L_lower", NHRU, "Darcy's lateral flow velocity in lower soil column", "(m/s)", &v_L_lower);
	declvar("v_V_sd", NHRU, "Darcy's vertical flow velocity for sd (ie. depression)", "(m/s)", &v_V_sd);
	declvar("v_V_soil", NHRU, "Darcy's vertical flow velocity for soil column", "(m/s)", &v_V_soil);
	declvar("v_L_gw", NHRU, "Darcy's lateral flow velocity for groundwater reservoir", "(m/s)", &v_L_gw);

	declputparam("*", "rechr_ssr_K", "(mm/d)", &rechr_ssr_K);
	declputparam("*", "lower_ssr_K", "(mm/d)", &lower_ssr_K);
	declputparam("*", "Sd_ssr_K", "(mm/d)", &Sd_ssr_K);
	declputparam("*", "Sd_gw_K", "(mm/d)", &Sd_gw_K);
	declputparam("*", "soil_gw_K", "(mm/d)", &soil_gw_K);
	declputparam("*", "gw_K", "(mm/d)", &gw_K);

	declvar("rechr_ssr_K_V", NHRU, "ssr drainage factor from recharge", "(mm/d)", &rechr_ssr_K_V);
	declvar("lower_ssr_K_V", NHRU, "ssr drainage factor from soil column", "(mm/d)", &lower_ssr_K_V);
	declvar("Sd_ssr_K_V", NHRU, "depression storage ssr drainage factor", "(mm/d)", &Sd_ssr_K_V);
	declvar("Sd_gw_K_V", NHRU, "depression storage gw drainage factor", "(mm/d)", &Sd_gw_K_V);
	declvar("soil_gw_K_V", NHRU, "The maximum amount of the soil water excess for an HRU that is routed directly to the associated groundwater reservoir each day", "(mm/d)", &soil_gw_K_V);
	declvar("gw_K_V", NHRU, "ground water drainage factor from gw reservoir each day", "(m/s)", &gw_K_V);

	declparam("Inhibit_K_set", NHRU, "[0]", "0", "63", "Inhibit setting of rechr_ssr_K/lower_ssr_K/Sd_ssr_K/Sd_gw_K/soil_gw_K/gw_K parameters using 1/2/4/8/16/32", "()", &Inhibit_K_set);

	declparam("Ks_lower", NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for lower soil", "(m/s)", &Ks_lower);
	declparam("Ks_upper", NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for upper soil layer", "(m/s)", &Ks_upper);
	declparam("Ks_gw", NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for groundwater layer", "(m/s)", &Ks_gw);
	declparam("hru_GSL", NHRU, "[0.0]", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);
	declparam("PSD", NHRU, "[0.252]", "0.0", "10.0", "pore size distribution", "()", &PSD);
	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation and transpiration). Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);
	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile. Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declgetparam("*", "inhibit_evap", "()", &inhibit_evap); // used since no declgetparam defined

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);
	declputvar("*", "soil_moist", "(mm)", &soil_moist);
	declputvar("*", "gw", "(mm)", &gw);

	variation_set = VARIATION_1;

	declvar("Dts_organic_runoff_K_V", NHRU, "detention storage of organic layer runoff drainage factor", "(mm/d)", &Dts_organic_runoff_K_V);

	declvar("Dts_snow_runoff_K_V", NHRU, "detention storage of snow runoff drainage factor", "(mm/d)", &Dts_snow_runoff_K_V);

	declvar("Ks_snow", NHRU, "saturated hydraulic conductivity for snow slush layer", "(m/s)", &Ks_snow);

	declvar("v_L_organic", NHRU, "Darcy's lateral flow velocity in organic layer", "(m/s)", &v_L_organic);

	declvar("v_L_snow", NHRU, "Darcy's lateral flow velocity in snow slush layer", "(m/s)", &v_L_snow);


	declputparam("*", "Dts_organic_runoff_K", "(mm/d)", &Dts_organic_runoff_K);

	declputparam("*", "Dts_snow_runoff_K", "(mm/d)", &Dts_snow_runoff_K);


	declparam("d_g", NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

	declparam("Ks_organic", NHRU, "[6.9e-6]", "0", "100.0", "saturated hydraulic conductivity for organic layer", "(m/s)", &Ks_organic);

	declparam("PSD_org", NHRU, "[0.252]", "0.0", "10.0", "pore size distribution for organic layer", "()", &PSD_org);

	declparam("S_I", NHRU, "[3.3]", "1.0", "7.0", "soil index", "()", &S_I);


	declgetvar("*", "Dts", "(mm)", &Dts);

	declgetvar("*", "Dts_max", "(mm)", &Dts_max);

	declgetvar("*", "rho", "((kg/m^3))", &rho);

	variation_set = VARIATION_ORG;
}

void ClassK_Estimate::init(void) {

	nhru = getdim(NHRU);
	for (hh = 0; chkStruct(); ++hh) {
		v_L_upper[hh] = 0.0;
		v_L_lower[hh] = 0.0;
		v_V_sd[hh] = 0.0;
		v_V_soil[hh] = 0.0;
		v_L_gw[hh] = 0.0;

		rechr_ssr_K[hh] = 0.0;
		lower_ssr_K[hh] = 0.0;
		Sd_ssr_K[hh] = 0.0;
		Sd_gw_K[hh] = 0.0;
		soil_gw_K[hh] = 0.0;
		gw_K[hh] = 0.0;

		if (variation == VARIATION_1) {
			Dts_organic_runoff_K[hh] = 0.0;
			Dts_snow_runoff_K[hh] = 0.0;
			Dts_organic_runoff_K_V[hh] = 0.0;
			Dts_snow_runoff_K_V[hh] = 0.0;
			Ks_snow[hh] = 0.0;
			v_L_organic[hh] = 0.0;
			v_L_snow[hh] = 0.0;
		}
	}
}

void ClassK_Estimate::run(void) {

	const float  DEGtoRAD = M_PI / 180.0;
	const float den_water = 1000.0, acc_gravi = 9.8, dyna_visc_water = 0.001787;

	for (hh = 0; chkStruct(); ++hh) {
		if (soil_rechr[hh] <= 0.0000001)
			const_cast<float *>  (soil_rechr)[hh] = 0.0;

		if (soil_moist[hh] <= 0.0000001)
			const_cast<float *>  (soil_moist)[hh] = 0.0;

		if (gw[hh] <= 0.0000001)
			const_cast<float *>  (gw)[hh] = 0.0;

		if (soil_rechr[hh] > soil_moist[hh])
			const_cast<float *>  (soil_rechr)[hh] = soil_moist[hh];

		if (!(soil_rechr_max[hh] == 0.0 && soil_moist_max[hh] == 0.0)) {
			if (inhibit_evap[hh] == 1) {
				v_L_upper[hh] = 0.0;
				v_L_lower[hh] = Ks_lower[hh] * pow((soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]), 3.0 + 2.0 / PSD[hh])* tan(hru_GSL[hh] * DEGtoRAD);
				v_V_sd[hh] = 0.0;
				v_V_soil[hh] = Ks_lower[hh] * pow(soil_moist[hh] / soil_moist_max[hh], 3.0 + 2.0 / PSD[hh]);
				v_L_gw[hh] = Ks_gw[hh] * tan(hru_GSL[hh] * DEGtoRAD);
			}

			if (inhibit_evap[hh] == 0) {
				v_L_upper[hh] = Ks_upper[hh] * pow(soil_rechr[hh] / soil_rechr_max[hh], 3.0 + 2.0 / PSD[hh])*tan(hru_GSL[hh] * DEGtoRAD);
				v_L_lower[hh] = Ks_lower[hh] * pow((soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]), 3.0 + 2.0 / PSD[hh])*tan(hru_GSL[hh] * DEGtoRAD);
				v_V_sd[hh] = Ks_lower[hh] * pow(soil_moist[hh] / soil_moist_max[hh], 3.0 + 2.0 / PSD[hh]);
				v_V_soil[hh] = Ks_lower[hh] * pow(soil_moist[hh] / soil_moist_max[hh], 3.0 + 2.0 / PSD[hh]);
				v_L_gw[hh] = Ks_gw[hh] * tan(hru_GSL[hh] * DEGtoRAD);
			}
		}
		bitset<6> Inhibits(Inhibit_K_set[hh]); // Inhibit setting of rechr_ssr_K/lower_ssr_K/Sd_ssr_K/Sd_gw_K/soil_gw_K/gw_K parameters using 1/2/4/8/16/32

		if (!Inhibits[0])
			rechr_ssr_K[hh] = v_L_upper[hh] * soil_rechr_max[hh] * 86400;
		if (!Inhibits[1])
			lower_ssr_K[hh] = v_L_lower[hh] * (soil_moist_max[hh] - soil_rechr_max[hh]) * 86400;
		if (!Inhibits[2])
			Sd_ssr_K[hh] = v_L_lower[hh] * soil_moist_max[hh] * 86400;
		if (!Inhibits[3])
			Sd_gw_K[hh] = v_V_sd[hh] * 86400000;
		if (!Inhibits[4])
			soil_gw_K[hh] = v_V_soil[hh] * 86400000;
		if (!Inhibits[5])
			gw_K[hh] = v_L_gw[hh] * gw[hh] * 86400;

		// output as variables for tracking
		rechr_ssr_K_V[hh] = rechr_ssr_K[hh];
		lower_ssr_K_V[hh] = lower_ssr_K[hh];
		Sd_ssr_K_V[hh] = Sd_ssr_K[hh];
		Sd_gw_K_V[hh] = Sd_gw_K[hh];
		soil_gw_K_V[hh] = soil_gw_K[hh];
		gw_K_V[hh] = gw_K[hh];

		if (variation == VARIATION_1) {
			if (!(Dts_max[hh] == 0.0)) {
				if (inhibit_evap[hh] == 1 && rho[hh] > 100) { // when snowcover, use Shimizu (1970) to estimate sat. hydraulic conductivity of snow
					Ks_snow[hh] = (0.077*sqr((d_g[hh] / 1000))*exp(-7.8*(rho[hh] / 1000)))*(den_water*acc_gravi / dyna_visc_water);
					v_L_snow[hh] = Ks_snow[hh] * pow(Dts[hh] / Dts_max[hh], S_I[hh])*sin(hru_GSL[hh] * DEGtoRAD);  // Colbeck (1972) formulated Darcy's law for estimating downward flux which is used to calucate the lateral flux
					v_L_organic[hh] = 0.0;
				}

				if (inhibit_evap[hh] == 0 || rho[hh] <= 100) { // when no snowcover, use Brooks-Corey relationship (1964) to estimate hydraulic conductivity of organic layer and then compute lateral Darcy's flux
					v_L_organic[hh] = Ks_organic[hh] * pow(Dts[hh] / Dts_max[hh], 3.0 + 2.0 / PSD_org[hh])*tan(hru_GSL[hh] * DEGtoRAD);
					v_L_snow[hh] = 0.0;
				}
			}

			Dts_organic_runoff_K[hh] = v_L_organic[hh] * Dts_max[hh] * 86400;
			Dts_snow_runoff_K[hh] = v_L_snow[hh] * Dts_max[hh] * 86400;

			// output as variables for tracking
			Dts_organic_runoff_K_V[hh] = Dts_organic_runoff_K[hh];
			Dts_snow_runoff_K_V[hh] = Dts_snow_runoff_K[hh];
		}
	} //for
}

void ClassK_Estimate::finish(bool good) {

}

ClassevapX* ClassevapX::klone(string name) const {
	return new ClassevapX(name);
}

void ClassevapX::decl(void) {

	Description = "'Calculates interval evaporation. Parameter \"evap_type\" selects Granger/Priestley-Taylor/Penman-Monteith.'";

	declvar("hru_actet", NHRU, "actual evapotranspiration over HRU, limited by the amount of soil moisture available", "(mm/int)", &hru_actet);

	declstatdiag("hru_cum_actet", NHRU, "cumulative actual evapotranspiration over HRU", "(mm)", &hru_cum_actet); // , NULL, false, CRHM::DIAGNOSTIC

	declvar("hru_evap", NHRU, "interval evaporation", "(mm/int)", &evap);

	declvar("hru_evapD", NHRU, "daily sum of interval evaporation", "(mm/d)", &evap_D);

	declstatdiag("hru_cum_evap", NHRU, "cumulative interval evaporation", "(mm)", &cum_evap);

	decllocal("Granger_D", NHRU, "daily Granger evaporation", "(mm/d)", &Granger_D);

	decldiag("rc", NHRU, "stomatal resistance (used by Penman-Monteith and Dalton)", "(s/m)", &rc);

	decllocal("Pa", NHRU, "Atmospheric pressure", "(kPa)", &Pa);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	declparam("evap_type", NHRU, "0", "0", "2", "Evaporation method for this HRU, 0 = Granger, 1 = Priestley-Taylor, 2 = Penman-Monteith.",
		"()", &evap_type);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	decldiagparam("F_Qg", NHRU, "[0.1]", "0.0", "1.0", "fraction to ground flux, Qg = F_Qg*Rn", "()", &F_Qg);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height (used by Penman-Monteith).", "(m)", &Zwind);


	declparam("rcs", NHRU, "[25]", "25.0", "5000.0", "stomatal resistance (used by Penman-Monteith).", "(s/m)", &rcs);

	declparam("Htmax", NHRU, "[0.1]", "0.1", "100.0", "maximum vegetation height (used by Penman-Monteith).", "(m)", &Htmax);

	declparam("LAImax", NHRU, "[3.0]", "0.0", "20.0", "maximum leaf area index (used by Penman-Monteith).", "(m^2/m^2)", &LAImax);

	declparam("LAImin", NHRU, "[0.0]", "0.0", "20.0", "minimum leaf area index (used by Penman-Monteith).", "(m^2/m^2)", &LAImin);

	declparam("s", NHRU, "[1]", "0", "1", "seasonal growth index (used by Penman-Monteith).", "()", &s);

	declparam("PM_method", NHRU, "[0]", "0", "2", "Penman-Monteith method (used by Penman-Monteith), 0 = RC min, 1 = LAI, 2 = bulk.", "()", &PM_method);

	declparam("soil_type", NHRU, "[2]", " 1", "12",
		"HRU soil type (used by Penman-Monteith) [1->11]: sand/loamsand/sandloam/loam/siltloam/sasclloam/clayloam/siclloam/sandclay/siltclay/clay.", "()", &soil_type);

	declparam("soil_Depth", NHRU, "[1.0]", "0.0", "10.0", "depth of soil column (used by Penman-Monteith).", "(m)", &soil_Depth);

	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declgetvar("*", "Rn", "(mm/m^2*int)", &Rn);
	declgetvar("*", "RnD", "(mm/m^2*d)", &RnD);
	declgetvar("*", "RnD_POS", "(mm/m^2*d)", &RnD_POS);

	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_u", "(m/s)", &hru_u);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_tmean", "(�C)", &hru_tmean);
	declgetvar("*", "hru_umean", "(m/s)", &hru_umean);
	declgetvar("*", "hru_eamean", "kPa", &hru_eamean);

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q, false);

	declreadobs("RnObs", NHRU, "all-wave", "(W/m^2)", &RnObs, HRU_OBS_Q, true);
}

void ClassevapX::init(void) {

	for (hh = 0; chkStruct(); ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa
		cum_evap[hh] = 0.0;
		hru_cum_actet[hh] = 0.0;
		Granger_D[hh] = 0.0;
	} // for
}

void ClassevapX::run(void) {

	const float Cp = 1.005; // (kJ/kg/K)

	float Q, Z0, d, U, ra, f1, f2, f3, f4, Soil_Moist, p, rcstar, LAI, D, G;

	long nstep = getstep() % Global::Freq;


	for (hh = 0; chkStruct(); ++hh) {

		evap[hh] = 0.0;
		hru_actet[hh] = 0.0;

		if (inhibit_evap[hh]) {
			evap_D[hh] = 0.0;
			Granger_D[hh] = 0.0;
			continue;
		}

		if (nstep == 1 || Global::Freq == 1) { // beginning of every day

			evap_D[hh] = 0.0;
			Granger_D[hh] = 0.0;

			if (evap_type[hh] == 0) { // Granger

				Q = RnD[hh] * (1.0 - F_Qg[hh]); // daily value (mm/d)

				if (Q > 0.0) {
					double Eal = fdaily(hru_umean[hh], Ht[hh])*(Common::estar(hru_tmean[hh]) - hru_eamean[hh]);
					if (Eal > 0.0) {
						D = Eal / (Eal + Q);
						if (D > 1.0)
							D = 1.0;
					}
					else // happens when hru_eamean[hh] > hru_tmean[hh] because of lapse rate adjustment with increased height
						D = 0.0;

					G = 1.0 / (0.793 + 0.2*exp(4.902*D)) + 0.006 * D;
					Granger_D[hh] = (delta(hru_tmean[hh]) * G * Q + gamma(Pa[hh], hru_tmean[hh]) *
						G * Eal) / (delta(hru_tmean[hh]) * G + gamma(Pa[hh], hru_tmean[hh]));
				}


			} // Granger

		} // beginning of every day

		  // calculated every interval

		Q = Rn[hh] * (1.0 - F_Qg[hh]); // (mm/d)

		switch (evap_type[hh]) {

		case 0: // Granger

			if (Q > 0.0 && Granger_D[hh] > 0.0 && RnD_POS[hh] > 0.0)
				evap[hh] = Q / RnD_POS[hh] / (1.0 - F_Qg[hh])*Granger_D[hh];

			break;

		case 1: // Priestley-Taylor

			if (Q > 0.0)
				evap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));

			break;

		case 2: // Penman-Monteith

			if (soil_moist[hh] > 0.0) { // else ignore

				Z0 = Ht[hh] / 7.6;
				d = Ht[hh] * 0.67;
				U = hru_u[hh]; // Wind speed (m/d)
				ra = sqr(log((Zwind[hh] - d) / Z0)) / (sqr(CRHM_constants::kappa)*U);

				rcstar = rcs[hh]; // rc min

				if (PM_method[hh] == 1) { // LAI
					LAI = Ht[hh] / Htmax[hh] * (LAImin[hh] + s[hh] * (LAImax[hh] - LAImin[hh]));
					rcstar = rcs[hh] * LAImax[hh] / LAI;
				}

				f1 = 1.0;
				if (Qsi[hh] > 0.0)
					f1 = max <float>(1.0, 500.0 / (Qsi[hh]) - 1.5);

				f2 = max <float>(1.0, 2.0*(Common::estar(hru_t[hh]) - hru_ea[hh]));

				Soil_Moist = (soil_moist[hh] / soil_Depth[hh] +
					SetSoilproperties[soil_type[hh]][1]) / SetSoilproperties[soil_type[hh]][3];

				p = soilproperties[soil_type[hh]][AIRENT] *
					pow(soilproperties[soil_type[hh]][PORE] / Soil_Moist, soilproperties[soil_type[hh]][PORESZ]);

				f3 = max <float>(1.0, p / 40.0);

				f4 = 1.0;
				if (hru_t[hh] < 5.0 || hru_t[hh] > 40.0)
					f4 = 5000 / 50;

				if (RnObs && RnObs[hh] <= 0)
					rc[hh] = 5000.0;
				else if (Qsi[hh] <= 0)
					rc[hh] = 5000.0;
				else {
					rc[hh] = rcstar * f1*f2*f3*f4;
					if (rc[hh] > 5000.0)
						rc[hh] = 5000.0;
				}

				float ratio_rs_ra = rc[hh] / ra;

				evap[hh] = (delta(hru_t[hh])*Q*Global::Freq + (RHOa(hru_t[hh], hru_ea[hh], Pa[hh])
					*Cp / (lambda(hru_t[hh])*1e3)*(Common::estar(hru_t[hh]) - hru_ea[hh]) / (ra / 86400)))
					/ (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh])*(1.0 + ratio_rs_ra)) / Global::Freq;
			}

			break;

		} // switch

		cum_evap[hh] += evap[hh];
		evap_D[hh] += evap[hh];
	} // for
}

void ClassevapX::finish(bool good) {

	float Allcum_evap = 0.0;
	float Allcum_actet = 0.0;

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "**** " + Evap_names[evap_type[hh]] + " ****";
		LogMessageA(hh, string("'" + Name + " (evapX)' hru_cum_evap (mm) (mm*hru) (mm*hru/basin): ").c_str(), evap[hh], hru_area[hh], basin_area[0], s.c_str());
		LogMessageA(hh, string("'" + Name + " (evapX)' hru_cum_actet (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Allcum_evap += cum_evap[hh] * hru_area[hh];
		Allcum_actet += hru_cum_actet[hh] * hru_area[hh];
	}

	LogMessage(string("'" + Name + " (evapX)' Allcum_evap  (mm*basin): ").c_str(), Allcum_evap / basin_area[0]);
	LogMessage(string("'" + Name + " (evapX)' Allcum_actet (mm*basin): ").c_str(), Allcum_actet / basin_area[0]);
	LogDebug(" ");

}

double ClassevapX::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float ClassevapX::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassevapX::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

double ClassevapX::fdaily(float u, float Ht) { // Drying power f(u) (mm/d/kPa)

	float Z0 = Ht * 100.0 / 7.6;
	float a = 8.19 + 0.22*Z0;
	float b = 1.16 + 0.08*Z0;
	return a + b * u;
}

float ClassevapX::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R0 = 2870;
	return (1E4*Pa / (R0*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

Class3D_param* Class3D_param::klone(string name) const {
	return new Class3D_param(name);
}

void Class3D_param::decl(void) {

	Description = "'Initialises the variable \"Param_3D\" from the parameter \"Var_3D\".'";

	declvar("Var_3D", NHRU, "Var_3D", "()", &Var_3D);

	declparam("Param_3D", NHRU, "[0.17]", "0.0", "1.0", "Param_3D", "()", &Param_3D);

}

void Class3D_param::init(void) {
	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		Var_3D[hh] = Param_3D[hh];
	}
}

void Class3D_param::run(void) {
}

void Class3D_param::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

	 string s = "'" + Name + " (3D_param)' ";
		LogMessage(hh, s.c_str());
	}
	LogDebug(" ");
}

ClassMeltRunoff_Lag* ClassMeltRunoff_Lag::klone(string name) const {
	return new ClassMeltRunoff_Lag(name);
}

void ClassMeltRunoff_Lag::decl(void) {

	Description = "'Calculates Melt Runoff.'";

	declvar("Tf", NHRU, "time lag after water percolated snowcover", "()", &Tf);  // minutes

	decldiag("In_Lagstorage", NHRU, "melt runoff in Lag storage at the beginning of interval!", "(mm)", &In_Lagstorage);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("inhibit_MeltRunoff_Lag", NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Lag correction, 1 -> inhibit", "()", &inhibit_MeltRunoff_Lag);

	declputparam("*", "runLag", "(h)", &runLag);


	declgetvar("*", "snowmelt_int", "(mm)", &snowmelt_int);

}

void ClassMeltRunoff_Lag::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		Tf[hh] = 0.0;
		In_Lagstorage[hh] = 0.0;
	}

	Netroute_module = (ClassModule*)FindModule_from_parameter("*", "runKstorage");
}

void ClassMeltRunoff_Lag::run(void) {

	//  if(getstep()%Global::Freq != 0) return;

	for (hh = 0; chkStruct(); ++hh)
		if (!inhibit_MeltRunoff_Lag[hh]) {
			if (snowmelt_int[hh] > 0.0)
				Tf[hh] = 250.0*pow(hru_area[hh], 0.17)*pow(snowmelt_int[hh], -0.5) / 60.0;

			if (snowmelt_int[hh] <= 0.0)
				Tf[hh] = 0.0;

			In_Lagstorage[hh] = Netroute_module->Function1(Tf, hh);
		}
}

ClassMeltRunoff_Kstorage* ClassMeltRunoff_Kstorage::klone(string name) const {
	return new ClassMeltRunoff_Kstorage(name);
}

void ClassMeltRunoff_Kstorage::decl(void) {

	Description = "'Calculates Melt Runoff Kstorage.'";

	declvar("Ksat", NHRU, "saturated hydraulic conductivity of porous snow media", "(m/s)", &Ksat);

	declvar("Meltrunoff_K", NHRU, "melt runoff storage constant", "(d)", &Meltrunoff_K);

	decldiag("In_storage", NHRU, "melt runoff in storage at the beginning of interval!", "(mm)", &In_storage);


	declparam("d_g", NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("inhibit_MeltRunoff_Kstorage", NHRU, "[0]", "0", "1", "inhibit MeltRunoff_Kstorage correction, 1 -> inhibit", "()", &inhibit_MeltRunoff_Kstorage);

	declputparam("*", "runKstorage", "(d)", &runKstorage);


	declparam("route_L", NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);


	declgetvar("*", "rho", "((kg/m^3))", &rho);

}

void ClassMeltRunoff_Kstorage::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		Ksat[hh] = 0.0;
		Meltrunoff_K[hh] = 0.0;
		In_storage[hh] = 0.0;
	}

	Netroute_module = (ClassModule*)FindModule_from_parameter("*", "runKstorage");
}

void ClassMeltRunoff_Kstorage::run(void) {

	//  if(getstep()%Global::Freq != 0) return;

	for (hh = 0; chkStruct(); ++hh) {
		if (rho[hh] > 0 && !inhibit_MeltRunoff_Kstorage[hh]) {
			Ksat[hh] = 0.077*pow(((d_g[hh] / 2.0) / 1000), 2.0)*9.8 / 0.000001787*exp(-0.0078*rho[hh]);
			if ((hru_GSL[hh] * DEGtoRAD) > 0) {
				Meltrunoff_K[hh] = route_L[hh] / (Ksat[hh] * tan(hru_GSL[hh] * DEGtoRAD)) / (86400.0);
				runKstorage[hh] = route_L[hh] / (Ksat[hh] * tan(hru_GSL[hh] * DEGtoRAD)) / (86400.0);
			}
			else {
				Meltrunoff_K[hh] = route_L[hh] / Ksat[hh] / (86400.0);
				runKstorage[hh] = route_L[hh] / Ksat[hh] / (86400.0);
			}

			In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
		}
	}
}

ClassSoilPrairie* ClassSoilPrairie::klone(string name) const {
	return new ClassSoilPrairie(name);
}

void ClassSoilPrairie::decl(void) {

	Description = "'Handles soil moisture throughout the year.' \
                 'Parametric contibuting fraction model,' \
                 'Pothole Cascade Model of contributing fraction,' \
                 'PDMROF model of contributing fraction.'";

	variation_set = VARIATION_1;

	// local variables
	decllocal("total_slough_basin_area", NHRU, "total_basin_area", "(m^2)", &total_basin_area);
	decllocal("final_area", NHRU, "final_area", "(m^2)", &final_area);
	decllocal("max_slough_area", NHRU, "max_slough_area", "(m^2)", &max_slough_area);
	decllocal("outflow_volume", NHRU, "outflow_volume", "(m^3)", &outflow_volume);
	decllocal("delta_vol", NHRU, "delta_vol - change in volume", "(m^3)", &delta_vol);
	decllocal("final_vol", NHRU, "final_vol", "(m^3)", &final_vol);
	decllocal("max_slough_volume", NHRU, "max_slough_volume", "(m^3)", &max_slough_volume);
	decllocal("volfrac", NHRU, "volfrac", "()", &volfrac);
	decllocal("areafrac", NHRU, "areafrac", "()", &areafrac);
	decllocal("runofffrac", NHRU, "runofffrac", "()", &runofffrac);
	decllocal("total_slough_basin_area", NHRU, "total_slough_basin_area", "()", &total_slough_basin_area);
	decllocal("PCM_runoff_multiplier", NHRU, "PCM_runoff_multiplier", "()", &PCM_runoff_multiplier);
	decllocal("PCM_Sdmax", NHRU, "PCM_Sdmax", "(mm)", &PCM_Sdmax);
	decllocal("total_slough_volume", NHRU, "total_slough_volume", "(m^3)", &total_slough_volume);
	decllocal("PCM_outflow", NHRU, "PCM_outflow", "(m^3)", &PCM_outflow);

	// parameters
	declparam("max_water_frac", NHRU, "[0.24]", "0.0", "1.0", "Max. possible fraction of the HRU area covered by water.", "()", &max_water_frac);
	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);
	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);
	declparam("numSloughs", NHRU, "[1]", "1", "2000", "Number of sloughs", "()", &numSloughs);
	declparam("Max_V", NDEFN, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^3)", &Max_V, &Max_V_N, 736);
	declparam("Max_A", NDEFN, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^2)", &Max_A, &Max_A_N, 736);
	declparam("Init_V", NDEFN, "[1.0]", "1e-6", "1e+09", "Slough maximum volumes", "(m^3)", &Init_V, &Init_V_N, 736);
	declparam("Connect", NDEFN, "[1]", "0", "1000", "Slough maximum volumes", "()", &Connect, &Connect_N, 736);
	declparam("p1", NHRU, "[1.72]", "0.1", "5", "pond p1", "()", &p1);
	declparam("p2", NHRU, "[3.33]", "0.1", "5", "pond p2", "()", &p2);
	declparam("maxPondArea_p1", NHRU, "[10000]", "10", "100000", "Max area for p1", "(m^2)", &maxPondArea_p1);
	declparam("minPondBasinArea", NHRU, "[2893.887]", "10", "100000", "Min allowable pond basin area", "(m^2)", &minPondBasinArea);
	declparam("minPondArea", NHRU, "[10000]", "10", "100000", "Min pond area for basin calculation", "(m^2)", &minPondArea);
	declparam("basinarea_c1", NHRU, "[3.44329]", "0.01", "100", "Pond basin area constant c1", "()", &basinarea_c1);
	declparam("basinarea_c2", NHRU, "[0.738377]", "0.01", "100", "Pond basin area constant c2", "()", &basinarea_c2);




	variation_set = VARIATION_2;

	// local variables
	// decllocal("S", NHRU, "[1.1]", "0.01", "10", "Ponding storage", "(m)", &S);

	// parameters
	declparam("CMAX", NHRU, "[0.1]", "0.01", "100", "MAXIMUM POTHOLE PONDING CAPACITY", "(m)", &CMAX);
	declparam("CMIN", NHRU, "[0.1]", "0.01", "100", "MINIMUM POTHOLE PONDING CAPACITY", "(m)", &CMIN);
	declparam("B", NHRU, "[1.1]", "0.01", "10", "SHAPE FACTOR OF THE PARETO DISTRIBUTION FUNCTION", "(m)", &B);



	variation_set = VARIATION_ORG;

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

	declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

	declvar("direct_rain", NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

	declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

	declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

	declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
		"portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

	declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

	decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

	declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

	declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

	declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

	declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

	declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

	declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

	declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

	declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

	declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

	declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

	declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

	declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

	declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

	declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

	declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

	declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

	decldiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

	decldiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);

	declvar("Sd_water_frac", NHRU, "fraction of the maximum possible Sd HRU fraction that is under water.", "()", &Sd_water_frac);

	declvar("contrib_frac", NHRU, "Fraction of the wetlands contributing water.", "()", &contrib_frac);

	declvar("wetlands_evap", NHRU, "Depth of water evaporating from wetlands using Priestley-Taylor.", "(mm/int)", &wetlands_evap);

	declvar("total_evap", NHRU, "Control variable based on running sum of evap.", "(mm)", &total_evap);


	decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

	decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

	decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

	decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

	decllocal("hru_evap_PT_buf", NHRU, "Priestley-Taylor buffer evaporation", "(mm/d)", &hru_evap_PT_buf);

	decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

	decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

	decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

	decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

	declparam("Sdinit", NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
		"Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

	declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
		"that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

	declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

	declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

	declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

	declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

	declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

	declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

	declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

	declparam("Sd_water_frac_max", NHRU, "[0.24]", "0.0", "1.0", "Maximum fraction of the HRU area that can be water.", "()", &Sd_water_frac_max);

	//  declparam("Sd_water_frac_init", NHRU, "[0.0]", "0.0", "1.0", "Initial fraction of the maximum HRU area fraction under water.", "()", &Sd_water_frac_init);

	declparam("contrib_frac_init", NHRU, "[0.0]", "0.0", "1.0", "Fraction of the HRU area contributing water.", "()", &contrib_frac_init);

	declparam("evap_threshold", NHRU, "[10]", "0.0", "20.0", "Threshold evaporation necessary for setting the contribution fraction to zero.", "(mm)", &evap_threshold);

	declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
		"Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
		&soil_withdrawal, &soil_withdrawal_Tables, 2);

	declparam("cov_type", NHRU,
		"[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
		"0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

	declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

	declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit.", "()", &inhibit_evap);


	declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

	declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


	evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

	declgetvar("*", "hru_evap_PT", "(mm/int)", &hru_evap_PT);


	declgetvar("*", "infil", "(mm/int)", &infil);

	snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

	runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

	meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);
}

void ClassSoilPrairie::init(void) {

	nhru = getdim(NHRU);

	if (snowinfilDiv > 1) {
	 string S = "Soil:  \"snowinfil\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (evapDiv > 1) {
	 string S = "Soil:  \"hru_evap\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (meltrunoffDiv > 1) {
	 string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (runoffDiv > 1) {
	 string S = "Netroute:  \"runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {

		if (soil_moist[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}

		if (soil_rechr[hh] > soil_rechr_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}
		if (soil_rechr_max[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
			throw TExcept;
		}

		if (Sdinit[hh] > Sdmax[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (gw_init[hh] > gw_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		soil_rechr[hh] = soil_rechr_init[hh];
		soil_moist[hh] = soil_moist_init[hh];

		redirected_residual[hh] = 0.0;
		cum_redirected_residual[hh] = 0.0;

		Sd[hh] = Sdinit[hh];

		gw[hh] = gw_init[hh];

		hru_cum_actet[hh] = 0.0;
		cum_hru_condense[hh] = 0.0;
		cum_infil_act[hh] = 0.0;

		soil_runoff_D[hh] = 0.0;
		soil_ssr_D[hh] = 0.0;
		soil_gw_D[hh] = 0.0;
		gw_flow_D[hh] = 0.0;
		infil_act[hh] = 0.0;
		infil_act_D[hh] = 0.0;

		cum_soil_runoff[hh] = 0.0;
		cum_soil_ssr[hh] = 0.0;
		cum_rechr_ssr[hh] = 0.0;
		cum_soil_gw[hh] = 0.0;
		cum_gw_flow[hh] = 0.0;

		cum_runoff_to_Sd[hh] = 0.0;

		if (Sdmax[hh] > 0.0 && soil_moist_max[hh] > 0.0)
			Sd_water_frac[hh] = parametric_area_frac(Sd[hh] / Sdmax[hh]);
		else
			Sd_water_frac[hh] = 0.0;

		contrib_frac[hh] = contrib_frac_init[hh];
		if (Sdmax[hh] > 0.0  && soil_moist_max[hh] > 0.0)
			if (contrib_frac[hh] > Sd[hh] / Sdmax[hh])
				contrib_frac[hh] = Sd[hh] / Sdmax[hh];

		total_evap[hh] = 0.0;

		if (variation == VARIATION_1) {
			try {
				current_area = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]
				current_depth = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]
				current_volume = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]
				S_values = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]
				h_values = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]
				wetland_drainage = new float*[(int)numSloughs[hh]];   // Data [numSloughs] [nhru]


				for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
					current_area[jj] = new float[nhru];
					current_depth[jj] = new float[nhru];
					current_volume[jj] = new float[nhru];
					S_values[jj] = new float[nhru];
					h_values[jj] = new float[nhru];
					wetland_drainage[jj] = new float[nhru];
					PCM_calc_h_and_S(Max_V_N[jj][hh], Max_A_N[jj][hh], S_values[jj][hh], h_values[jj][hh]);
				}
			} // try

			catch (std::bad_alloc) {
				CRHMException Except("Could not allocate arrays in module PCM.", TERMINATE);
				LogError(Except);
				throw Except;
			}

			for (hh = 0; chkStruct(); ++hh) {
				max_slough_volume[hh] = 0.0;
				max_slough_area[hh] = 0.0;
				total_slough_basin_area[hh] = 0.0;
				for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
					current_volume[jj][hh] = Init_V_N[jj][hh];
					wetland_drainage[jj][hh] = PCM_wetland_drainage_area(Max_A_N[jj][hh]);
					max_slough_volume[hh] += Max_V_N[jj][hh];
					max_slough_area[hh] += Max_A_N[jj][hh];
					total_slough_basin_area[hh] += wetland_drainage[jj][hh];
				}
				// calculate PCM multiplication factor, based on total slough basin area and HRU area
				PCM_runoff_multiplier[hh] = hru_area[hh] / total_slough_basin_area[hh];

				// calculate Sdmax from total slough volume and hru areas
				PCM_Sdmax[hh] = (max_slough_volume[hh] / hru_area[hh]) * 1000.0;

			}
			// set initial contributing fraction
			contrib_frac[hh] = contrib_frac_init[hh];
			if (Sdmax[hh] > 0.0  && soil_moist_max[hh] > 0.0)
				if (contrib_frac[hh] > Sd[hh] / Sdmax[hh])
					contrib_frac[hh] = Sd[hh] / Sdmax[hh];

		}
		if (variation == VARIATION_2) {
			// nothing to set
		}

	}
}

void ClassSoilPrairie::run(void) {

	float soil_lower, excs, condense;
	float et;

	long nstep = getstep();

	if (nstep == 1)
		for (hh = 0; chkStruct(); ++hh) {
			LogMessageA(hh, string("'" + Name + " (Soil)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (Soil)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
			soil_moist_Init[hh] = soil_moist[hh];
			soil_rechr_Init[hh] = soil_rechr[hh];
			Sd_Init[hh] = Sd[hh];
			gw_Init[hh] = gw[hh];
		}

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (snowinfilDiv == 1) // interval value
			snowinfil_buf[hh] = snowinfil[hh];

		if (runoffDiv == 1) // interval value
			runoff_buf[hh] = runoff[hh];

		if (meltrunoffDiv == 1) // interval value
			meltrunoff_buf[hh] = meltrunoff[hh];

		if (evapDiv == 1) { // interval value
			hru_evap_buf[hh] = hru_evap[hh];
			hru_evap_PT_buf[hh] = hru_evap_PT[hh];
		}
		if (nstep == 1) { // beginning of every day
			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;
			infil_act_D[hh] = 0.0;
		}

		hru_actet[hh] = 0.0;
		infil_act[hh] = 0.0;
		soil_gw[hh] = 0.0;
		soil_ssr[hh] = 0.0;
		rechr_ssr[hh] = 0.0;

		if (hru_evap_buf[hh] < 0.0) {
			condense = -hru_evap_buf[hh];
			cum_hru_condense[hh] += condense;
			hru_evap_buf[hh] = 0.0;
		}
		else
			condense = 0.0;

		// do direct precipitation on water



		//******Add infiltration to soil and compute excess

		if (soil_moist_max[hh] > 0.0) {
			soil_lower = soil_moist[hh] - soil_rechr[hh];

			float potential = infil[hh] + snowinfil_buf[hh] + condense;

			soil_rechr[hh] = soil_rechr[hh] + potential;

			if (soil_rechr[hh] > soil_rechr_max[hh]) {
				excs = soil_rechr[hh] - soil_rechr_max[hh];
				soil_rechr[hh] = soil_rechr_max[hh];
				soil_lower = soil_lower + excs;
			}

			soil_moist[hh] = soil_lower + soil_rechr[hh];

			if (soil_moist[hh] > soil_moist_max[hh]) {
				excs = soil_moist[hh] - soil_moist_max[hh];
				soil_moist[hh] = soil_moist_max[hh];
			}
			else
				excs = 0.0;

			infil_act[hh] = potential - excs;
			cum_infil_act[hh] += infil_act[hh];
			infil_act_D[hh] += infil_act[hh];

			//  Handle subsurface runoff

			if (!inhibit_evap[hh]) { // only when no snowcover
				rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;
				if (rechr_ssr[hh] > soil_rechr[hh])
					rechr_ssr[hh] = soil_rechr[hh];

				soil_rechr[hh] -= rechr_ssr[hh];
				if (soil_rechr[hh] < 0.0)
					soil_rechr[hh] = 0.0;

				soil_moist[hh] -= rechr_ssr[hh];
				soil_ssr[hh] = rechr_ssr[hh];
				cum_rechr_ssr[hh] += rechr_ssr[hh];
			}

			float s2gw_k = soil_gw_K[hh] / Global::Freq;

			//  Handle excess to gw

			if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
				soil_gw[hh] = s2gw_k;
				excs -= s2gw_k;
			}
			else { // to gw
				soil_gw[hh] = excs;
				excs = 0.0;
			}

			//  Handle excess to interflow or runoff

			if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow
				soil_ssr[hh] += excs;
				excs = 0.0;
			}
		}
		else { // soil_moist_max <= 0.0, i.e. Pond
			excs = infil[hh] + snowinfil_buf[hh] + condense;
		}

		float runoff_to_Sd = 0.0;

		// use variable contributing areas for wetland HRUs
		if (Sdmax[hh] > 0.0 && soil_moist_max[hh] <= 0.0) {

			if (variation == VARIATION_ORG) {
				soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs;
				runoff_to_Sd = parametric_Sd_add(soil_runoff[hh]);
				soil_runoff[hh] -= runoff_to_Sd;

				runoff_to_Sd = parametric_Sd_add(redirected_residual[hh] / hru_area[hh]);
				soil_runoff[hh] -= runoff_to_Sd;
				cum_redirected_residual[hh] += (redirected_residual[hh] / hru_area[hh]) - runoff_to_Sd;

			}    // variation org

			if (variation == VARIATION_1) {
				// do local runoff
				soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs;
				PCM_runoff();
				soil_runoff[hh] = (redirected_residual[hh] / hru_area[hh]);
				cum_redirected_residual[hh] += (redirected_residual[hh] / hru_area[hh]);
				PCM_runoff();

				// adjust runoff by area ratio
				soil_runoff[hh] = soil_runoff[hh] * PCM_runoff_multiplier[hh];

			}    // variation 1

			if (variation == VARIATION_2) {
				// add local runoff
				PDMROF_add_subtract((meltrunoff_buf[hh] + runoff_buf[hh] + excs));

				// do redirected residual
				PDMROF_add_subtract(redirected_residual[hh] / hru_area[hh]);
				cum_redirected_residual[hh] += (redirected_residual[hh] / hru_area[hh]);
			}    // variation 2
		}
		else {
			// don't use variable contributing fraction
			soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + (redirected_residual[hh] / hru_area[hh]);
			cum_redirected_residual[hh] += redirected_residual[hh];
		}

		redirected_residual[hh] = 0;
		soil_runoff_D[hh] += soil_runoff[hh];
		cum_soil_runoff[hh] += soil_runoff[hh];
		cum_runoff_to_Sd[hh] += runoff_to_Sd;

		if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
			float Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
			if (Sd2gw_k > Sd[hh])
				Sd2gw_k = Sd[hh];
			soil_gw[hh] += Sd2gw_k;
			Sd[hh] -= Sd2gw_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		soil_gw_D[hh] += soil_gw[hh];
		cum_soil_gw[hh] += soil_gw[hh];

		gw[hh] += soil_gw[hh];
		gw_flow[hh] = 0.0;
		if (gw[hh] > gw_max[hh]) {
			gw_flow[hh] += (gw[hh] - gw_max[hh]);
			gw[hh] = gw_max[hh];
		}

		if (gw_max[hh] > 0.0) { // prevents divide by zero error
			float spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
			gw[hh] -= spill;
			gw_flow[hh] += spill;
		}

		gw_flow_D[hh] += gw_flow[hh];
		cum_gw_flow[hh] += gw_flow[hh];

		if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
			float Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq;
			if (Sd2ssr_k >= Sd[hh])
				Sd2ssr_k = Sd[hh];
			soil_ssr[hh] += Sd2ssr_k;
			Sd[hh] -= Sd2ssr_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		float s2ssr_k = lower_ssr_K[hh] / Global::Freq;
		if (s2ssr_k > 0.0) {
			float avail = soil_moist[hh] - soil_rechr[hh];
			if (s2ssr_k >= avail)
				s2ssr_k = avail;
			soil_moist[hh] -= s2ssr_k;
			soil_ssr[hh] += s2ssr_k;
		}

		cum_soil_ssr[hh] += soil_ssr[hh];
		soil_ssr_D[hh] += soil_ssr[hh];

		//******Compute actual evapotranspiration
		// update Sd and calculate contributing fraction
		if (Sd[hh] > 0.0 && soil_moist_max[hh] <= 0.0 && hru_evap_PT_buf[hh] > 0.0) {
			if (variation == VARIATION_ORG) {
				wetlands_evap[hh] = parametric_Sd_subtract(hru_evap_PT_buf[hh]);
				hru_actet[hh] += wetlands_evap[hh];
			}
			else if (variation == VARIATION_1) {
				PCM_evap(hru_evap_PT_buf[hh]);
				wetlands_evap[hh] = hru_evap_PT_buf[hh];
				hru_actet[hh] += wetlands_evap[hh];
			}
			else if (variation == VARIATION_2) {
				wetlands_evap[hh] = hru_evap_PT_buf[hh];
				hru_actet[hh] += wetlands_evap[hh];
				PDMROF_add_subtract(hru_evap_PT_buf[hh]);
			}
		}
		else
			wetlands_evap[hh] = 0.0;

		float avail_evap = hru_evap_buf[hh] * (1.0 - Sd_water_frac[hh] * Sd_water_frac_max[hh]);

		//    avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

		if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

			float pctl, pctr, etl, ets, etr;

			if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
				pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				pctl = 0.0;

			pctr = soil_rechr[hh] / soil_rechr_max[hh];

			etr = avail_evap; // default

			switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
			case 1: //******sandy soil
				if (pctr < 0.25)
					etr = 0.5*pctr*avail_evap;
				break;
			case 2: //******loam soil
				if (pctr < 0.5)
					etr = pctr * avail_evap;
				break;
			case 3: //******clay soil
				if (pctr <= 0.33)
					etr = 0.5*pctr*avail_evap;
				else if (pctr < 0.67)
					etr = pctr * avail_evap;
				break;
			case 4: //******organic soil
					//         use default above etr = avail_evap;
				break;
			} // recharge switch

			if (etr > avail_evap) {
				etl = 0.0; // default value
				etr = avail_evap;
			}
			else
				etl = avail_evap - etr; // default value

			switch (soil_withdrawal_Tables[1][hh]) {  // handle lower layer
			case 1: //******sandy soil
				if (pctl < 0.25)
					etl = 0.5*pctl*etl;
				break;
			case 2: //******loam soil
				if (pctl < 0.5)
					etl = pctl * etl;
				break;
			case 3: //******clay soil
				if (pctl <= 0.33)
					etl = 0.5*pctl*etl;
				else if (pctr < 0.67)
					etl = pctl * etl;
				break;
			case 4: //******organic soil
					//         use default above etl = avail_evap - etr;
				break;
			} // lower switch

			  //******Soil moisture accounting  Remember that soil_moist includes soil_rechr[hh][hh]

			long et_type = cov_type[hh];

			//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
			//****** et_type = 1 - recharge layer only, crops - cov_type = 1
			//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

			if (transp_limited[hh] == 1 && et_type == 2)
				et_type = 1;

			et = 0.0;

			switch (et_type) {  // handle evaporation
			case 0:   // avail_evap <= 0
				break;
			case -1:  // avail_evap <= 0
				break;
			case 1:
				if (etr > soil_rechr[hh]) {
					soil_rechr[hh] = 0.0;
					et = soil_rechr[hh];
				}
				else {
					soil_rechr[hh] = soil_rechr[hh] - etr;
					et = etr;
				}
				soil_moist[hh] = soil_moist[hh] - et;
				break;
			case 2:
				if (etr + etl >= soil_moist[hh]) {
					et = soil_moist[hh];
					soil_moist[hh] = 0.0;
					soil_rechr[hh] = 0.0;
				}
				else {
					et = etr + etl;
					soil_moist[hh] = soil_moist[hh] - et;

					if (etr > soil_rechr[hh]) {
						soil_rechr[hh] = 0.0;
					}
					else
						soil_rechr[hh] = soil_rechr[hh] - etr;
				}
				break;
			} // switch

			hru_actet[hh] += et;

		} // soil_moist[hh] > 0.0

		if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
			hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

		hru_cum_actet[hh] += hru_actet[hh];

		if (nstep == 0) { // end of every day
			if (snowinfilDiv > 1) // daily value - ready for next day
				snowinfil_buf[hh] = snowinfil[hh] / snowinfilDiv;

			if (runoffDiv > 1) // daily value - ready for next day
				runoff_buf[hh] = runoff[hh] / runoffDiv;

			if (meltrunoffDiv > 1) // daily value - ready for next day
				meltrunoff_buf[hh] = meltrunoff[hh] / meltrunoffDiv;

			if (evapDiv > 1) // daily value - ready for next day
				hru_evap_buf[hh] = hru_evap[hh] / evapDiv;
		}
	} // for
}

void ClassSoilPrairie::finish(bool good) {

	float Allcum_soil_runoff = 0.0;
	float Allcum_soil_ssr = 0.0;
	float Allcum_rechr_ssr = 0.0;
	float Allcum_soil_gw = 0.0;
	float Allcum_gw_flow = 0.0;
	float Allcum_infil_act = 0.0;
	float Allcum_soil_moist_change = 0.0;
	float Allcum_Sd_change = 0.0;
	float Allcum_gw_change = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_hru_condense   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (SoilPrairie)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogDebug(" ");

		if (variation == VARIATION_1) {
			LogDebug(" ");
		}

		Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
		Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
		Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
		Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
		Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
		Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
		Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
		Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
		Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];
	}

	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
	LogMessage(string("'" + Name + " (SoilPrairie)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
	LogDebug(" ");
}

//const float p1 = 1.72;
//const float p2 = 3.33;
const float maxerror = 0.00001;
const long maxiterations = 1000;
float ClassSoilPrairie::parametric_contrib_frac_add(const float contrib_frac_slice, const float delta_Sd) {

	//  Calculates contributing fraction after addition of water. Uses linear approximation of WDPM results.

	float vol_frac = Sd[hh] / Sdmax[hh];
	if (vol_frac >= 1.0)
		return 1.0;

	float vol_frac_delta = delta_Sd / Sdmax[hh];
	float slope = (1.0 - contrib_frac_slice) / (1.0 - vol_frac);
	slope = max <float>(slope, 0.0);
	float R = min <float>(contrib_frac_slice + vol_frac_delta * slope, 1.0); // contrib_frac_increase
	R = max <float>(R, 0.0);
	return R;
}

float ClassSoilPrairie::parametric_Sd_add(const float applied_depth) {

	// adds water to Sd in parametric hysteresis model

	float Sd_initial;
	float delta_Sd;
	float delta_volfrac;
	float tolerance = 0.01;
	float contrib_frac_mean;
	float contrib_frac_new;
	float contrib_frac_slice;
	float Sd_total;
	float contrib_frac_error;
	float depth_frac;
	int slices;

	Sd_initial = Sd[hh];
	delta_Sd = (1.0 - contrib_frac[hh]) * applied_depth;
	delta_volfrac = delta_Sd / Sdmax[hh];
	contrib_frac_new = parametric_contrib_frac_add(contrib_frac[hh], delta_Sd);

	if (contrib_frac[hh] > 0.0)
		contrib_frac_error = fabs((contrib_frac[hh] - contrib_frac_new) / contrib_frac[hh]);
	else
		contrib_frac_error = tolerance;

	// check to see if potential change in contrib_fraction warrants use of numerical integration

	if (contrib_frac_error < tolerance) {
		contrib_frac_mean = (contrib_frac[hh] + contrib_frac_new) / 2.0;
		Sd_total = Sd[hh] + applied_depth * (1.0 - contrib_frac_mean);
		contrib_frac[hh] = contrib_frac_new;
	}
	else { // Do numerical integration of depth applied to get Sd get number of slices to use

		slices = min <float>(max <float>(contrib_frac_error / tolerance, 2.0), 100);

		depth_frac = applied_depth / slices;
		Sd_total = Sd[hh];
		contrib_frac_slice = contrib_frac[hh];

		for (long ii = 0; ii < slices; ++ii) {
			delta_Sd = (1.0 - contrib_frac_slice) * depth_frac;
			Sd_total = Sd_total + delta_Sd;
			delta_volfrac = delta_Sd / Sdmax[hh];
			contrib_frac_slice = parametric_contrib_frac_add(contrib_frac_slice, delta_Sd);
		}
		contrib_frac[hh] = contrib_frac_slice;

		if (contrib_frac[hh] < 0.0001)
			contrib_frac[hh] = 0.0;
	}

	// update state variables

	delta_Sd = Sd_total - Sd[hh];

	Sd[hh] = Sd_total;
	total_evap[hh] = 0.0;
	Sd_water_frac[hh] = parametric_area_frac(Sd[hh] / Sdmax[hh]);

	return delta_Sd;
}

float ClassSoilPrairie::parametric_Sd_subtract(const float applied_depth) {

	//  subtracts depth of water from Sd in parametric hysteresis model

	float Sd_initial;
	float delta_Sd;
	float delta_areafrac;
	float tolerance = 0.01;
	float water_area_frac_mean;
	float water_area_frac_new;
	float water_area_frac_slice;
	float Sd_total;
	float volfrac;
	float water_area_frac_error;
	int slices;

	Sd_initial = Sd[hh];
	delta_Sd = Sd_water_frac_max[hh] * Sd_water_frac[hh] * applied_depth;
	water_area_frac_new = parametric_area_frac((Sd[hh] - delta_Sd) / Sdmax[hh]);
	water_area_frac_error = fabs((Sd_water_frac[hh] - water_area_frac_new) / Sd_water_frac[hh]);

	if (water_area_frac_error < tolerance) { //  check to see if potential change in contrib_fraction warrants use of numerical integration
		water_area_frac_mean = (Sd_water_frac[hh] + water_area_frac_new) / 2.0;
		Sd_total = Sd[hh] - applied_depth * Sd_water_frac_max[hh] * water_area_frac_mean;
	}
	else { // Do numerical integration of depth applied to get Sd

		slices = max <float>(water_area_frac_error / tolerance, 2.0); // get number of slices to use

		float depth_frac = applied_depth / slices;
		Sd_total = Sd_initial;
		water_area_frac_slice = Sd_water_frac[hh];

		for (long ii = 0; ii < slices; ++ii) {
			delta_Sd = Sd_water_frac_max[hh] * water_area_frac_slice * depth_frac;
			Sd_total = Sd_total + delta_Sd;
			volfrac = Sd_total / Sdmax[hh];
			water_area_frac_slice = parametric_area_frac(volfrac);
		}
	}
	// update state variables

	delta_Sd = Sd[hh] - Sd_total;

	Sd[hh] = Sd_total;
	total_evap[hh] += delta_Sd;
	Sd_water_frac[hh] = parametric_area_frac(Sd[hh] / Sdmax[hh]);
	contrib_frac[hh] = parametric_contrib_frac_subtract();

	if (contrib_frac[hh] < 0.0001)
		contrib_frac[hh] = 0.0;

	return delta_Sd;
}

float ClassSoilPrairie::parametric_area_frac(const float vol_frac) {

	// calculates maximum water area fraction from water volume fraction using simple scaling curve

	float c1 = -0.254337;
	float c2 = 1.22233;
	float c3 = 0.0261854;

	return c1 * sqr(vol_frac) + c2 * vol_frac + c3; // area_frac
}

float ClassSoilPrairie::parametric_contrib_frac_subtract(void) {

	//  sets contributing fraction to zero if total evaporation exceeds a threshold

	if (total_evap[hh] > evap_threshold[hh])
		return 0.0;
	else
		return max <float>(min <float>((1.0 - total_evap[hh] / evap_threshold[hh])*contrib_frac[hh], 1.0), 0.0);
}

float ClassSoilPrairie::PCM_area_frac(float maxarea, float volume, float S, float h) {

	float pval, areafrac;
	float currentdepth, currentarea;
	// set value of scaling parameter
	if (maxarea < maxPondArea_p1[hh])
		pval = p1[hh];
	else
		pval = p2[hh];

	// calculate current depth & area
	currentdepth = pow(volume*(1.0 + 2.0 / pval) / S, 1.0 / (1.0 + 2.0 / pval));
	currentdepth = min<float>(currentdepth, h);
	currentarea = S * pow(currentdepth, 2.0 / pval);
	areafrac = currentarea / maxarea;
	areafrac = min<float>(areafrac, 1.0);
	areafrac = max<float>(areafrac, 0.0);
	return areafrac;
} // end areafraction

void ClassSoilPrairie::PCM_calc_h_and_S(float maxvolume, float maxarea, float &S, float &h) {
	float est_area, area_error, pval;
	int iterations;
	bool done;
	// does iterative calculations to find h and S
	if (maxarea < maxPondArea_p1[hh])
		pval = p1[hh];
	else
		pval = p2[hh];

	h = 1.0;
	done = false;
	iterations = 0;
	while (!done) {
		S = maxarea / pow(h, 2.0 / pval);
		h = pow((maxvolume * (1.0 + 2.0 / pval)) / S, 1.0 / (1.0 + 2.0 / pval));
		est_area = S * pow(h, 2.0 / pval);
		area_error = fabs(est_area - maxarea) / maxarea;

		if ((area_error < maxerror) || (iterations > maxiterations))
			done = true;
		else
			iterations = iterations + 1;

	}
} // end  PCM_calc_h_and_S

float ClassSoilPrairie::PCM_wetland_drainage_area(float maxarea) { // based on scaling relationships

	if (maxarea > minPondArea[hh])
		return exp(basinarea_c1[hh]) * pow(maxarea, basinarea_c2[hh]);
	else
		return minPondBasinArea[hh];

} //end PCM_wetland_drainage_area

void ClassSoilPrairie::PCM_evap(float evap) {
	if (evap > 0.0) {                           // evaporate water 1 mm at a time
		outflow_volume[hh] = 0.0;
		long i_evap = int(-1.0 * evap);
		float evap_m = 1.0 / 1000.0;
		for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
			for (long pp = 0; pp < i_evap; ++pp) // assume area of willow ring = max area of water
				current_volume[jj][hh] = max <float>((current_volume[jj][hh] - (evap_m * Max_A_N[jj][hh])), 0.0);
		}
	}
	PCM_set_Sd();
}

void ClassSoilPrairie::PCM_set_Sd() {
	for (hh = 0; chkStruct(); ++hh) {
		total_slough_volume[hh] = 0.0;
		for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
			total_slough_volume[hh] += current_volume[jj][hh];
		}
		// calculate Sd from total slough volume and hru areas
		Sd[hh] = (total_slough_volume[hh] / hru_area[hh]) * 1000.0;
	}

}


void ClassSoilPrairie::PCM_rain() {
	// calculates addition of water to ponds from precip and snowmelt on water area
	bool done;
	for (hh = 0; chkStruct(); ++hh) {
		if (direct_rain[hh] > 0.0) {
			done = true;
			for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
				// apply rainfall // get current water area
				areafrac[hh] = PCM_area_frac(Max_A_N[jj][hh], current_volume[jj][hh], S_values[jj][hh], h_values[jj][hh]);

				// do direct Precip on water - see if any sloughs are full
				current_volume[jj][hh] = current_volume[jj][hh] + (direct_rain[hh] * Max_A_N[jj][hh] * areafrac[hh]) / 1000.0;

				if (current_volume[jj][hh] >= Max_V_N[jj][hh])
					done = false;

			} // adding precipitation

			if (!done) {
				// at least one pond is over-filled so route outflows
				PCM_outflow[hh] = PCM_outflow[hh] + PCM_route_excess();
			}
		}
	} // for
	  // set Sd
	PCM_set_Sd();
}

void ClassSoilPrairie::PCM_runoff() {
	// calculates addition of water to ponds from upland runoff
	bool done;
	for (hh = 0; chkStruct(); ++hh) {
		if (soil_runoff[hh] > 0.0) {
			done = true;
			for (long jj = 0; jj < (long)numSloughs[hh]; ++jj) {
				// apply runoff to sloughs and see if any are full
				current_volume[jj][hh] = current_volume[jj][hh] +
					(soil_runoff[hh] * wetland_drainage[jj][hh]) / 1000.0;

				if (current_volume[jj][hh] >= Max_V_N[jj][hh])
					done = false;
			} // loop through sloughs

			if (!done)
				PCM_outflow[hh] = PCM_route_excess(); // at least one pond is over-filled so route outflows

		}  // if soil_runoff
	}
	// set Sd
	PCM_set_Sd();
}

float ClassSoilPrairie::PCM_route_excess() {
	float largest_value, transferred_volume, initial_vol;
	bool done = false;
	const float tolerance = 0.1;
	long iter_count, destination;
	long const iter_max = 100;


	// route excess flows
	iter_count = 1;
	while (!done) {
		largest_value = 0.0;
		for (long jj = ((long)numSloughs[hh]) - 1; 0 < jj; --jj) {  // do j = numSloughs, 2, -1

			if (current_volume[jj][hh] > Max_V_N[jj][hh]) {
				transferred_volume = current_volume[jj][hh] - Max_V_N[jj][hh];
				current_volume[jj][hh] = Max_V_N[jj][hh];
				destination = Connect_N[jj][hh] - 1; // Index starts at 0 not 1
				current_volume[destination][hh] = current_volume[destination][hh] + transferred_volume;
			}
			else
				transferred_volume = 0.0;

			if (transferred_volume > largest_value)
				largest_value = transferred_volume;

		} // each slough

		if ((largest_value <= tolerance) || (iter_count > iter_max))
			done = true;
		else
			iter_count = iter_count + 1;

	} // done (all routing)
	  // now do slough #1
	outflow_volume[hh] = max<float>(current_volume[0][hh] - Max_V_N[0][hh], 0.0);
	current_volume[0][hh] = min<float>(current_volume[0][hh], Max_V_N[0][hh]);
	return(outflow_volume[hh]);
}


float ClassSoilPrairie::PDMROF_add_subtract(float deltaSd) {
	// applies PDMROF to calculate contributing fraction from volume fraction
	// and adds to Sd
	// variables and comments in uppercase are from original Fortran 90 code

	float BP1;        // B + 1
	float IBP1;       // 1 / BP1
	float SMXMCMN;
	float CMXMCMN;
	float SMAX;       // MAXIMUM TILE PONDING STORAGE  [M]
	float CSTR;       // CRITICAL PONDING DEPTH FOR A GIVEN STORAGE [M]
	float FSTR;       // DISTRIBUTION FUNCTION VALUE AT CRITICAL PONDING DEPTH [] THIS IS THE CONTRIBUTING AREA FRACTION
	float RNET;       // NET CHANGE IN THE DEPTH OF THE PONDED WATER
	float S;          // CURRENT TILE PONDING STORAGE  [M]
	float SPRE;       // PREVIOUS TILE PONDING STORAGE [M]
	float CMIN_local; // local version of CMIN
	float CMAX_local; // local version of CMAX
	float U;          // DIRECT RUNOFF BETWEEN TIME T AND T + DELTAT [M]

					  // AVOID UNREALISTIC SITUATION WHERE THE USER OR AN
					  // AUTOCALIBRATION ALGORITHM MAY SPECIFY
					  // A MAXIMUM STORAGE VALUE SMALLER THAN THE MINIMUM STORAGE

	CMIN_local = max <float>(0.0, CMIN[hh]);
	CMAX_local = max <float>(CMIN_local, CMAX[hh]);

	SPRE = Sd[hh] / 1000;    // convert to m

							 // calculate S by adding deltaSd (converted to m) to Sd
	S = SPRE + (deltaSd / 1000);

	// LIMIT THE MINIMUM STORAGE TO CMIN
	SPRE = max <float>(CMIN_local, SPRE);

	BP1 = B[hh] + 1.0;
	IBP1 = 1.0 / BP1;
	CMXMCMN = CMAX_local - CMIN_local;

	// MAXIMUM STORAGE
	SMAX = IBP1 * B[hh] * CMIN_local + CMAX_local;

	// CRITICAL POND DEPTH CORRESPONDING TO SPRE

	SMXMCMN = SMAX - CMIN_local;
	CSTR = CMIN[hh] + CMXMCMN * (1.0 - pow(((SMAX - SPRE) / SMXMCMN), IBP1));

	// CALCULATE THE NET CHANGE IN THE DEPTH OF THE PONDED
	// WATER WITHIN DELTAT (BETWEEN TIME T AND T + DELTAT)

	RNET = S - SPRE;   // i.e. deltaSd (in m)

					   // FOR A WET PERIOD AND IF THE PONDED WATER EXCEEDS THE
					   // MINIMUM STORAGE BELOW WHICH RUNOFF IS NOT POSSIBLE

	if ((RNET > 1.0E-06) && (S > CMIN_local)) {
		// CALCULATE THE CRITICAL POND DEPTH AT T + DELTAT AND
		// LIMIT IT TO THE MAXIMUM PONDING DEPTH

		CSTR = min <float>(CMAX_local, CSTR + RNET);

		// CALCULATE THE NEW DEPTH OF THE PONDED WATER, S AT
		// T + DELTAT. THIS TAKES INTO ACCOUNT THE LOSS DUE TO
		// DIRECT RUNOFF WITHIN DELTAT (T TO T + DELTAT).
		// NOTE THAT BECAUSE CSTR IS BOUND NOT TO EXCEED CMAX
		// S WILL NOT EXCEED SMAX.

		S = CMIN_local + SMXMCMN * (1.0 - pow(((CMAX_local - CSTR) / CMXMCMN), BP1));
		U = max <float>(0.0, RNET - (S - SPRE));

		// convert S and U to mm to set Sd and runoff
		// limit Sd to range between 0 and Sdmax

		Sd[hh] = min <float>(max <float>(0, S / 1000), Sdmax[hh]);
		soil_runoff[hh] += (U / 1000);
	}

	// add support for evaporation

	if (RNET < -1.0E-06) {
		CSTR = min <float>(CMAX_local, CSTR + RNET);
		S = SPRE + RNET;
		Sd[hh] = min <float>(max <float>(0, S / 1000), Sdmax[hh]);
	}

	// CONTRIBUTING AREA FRACTION
	FSTR = 1.0 - pow((1.0 - CSTR / CMAX_local), B[hh]);
	contrib_frac[hh] = FSTR;
	return FSTR;
}


ClassREWroute* ClassREWroute::klone(string name) const {
	return new ClassREWroute(name);
}

void ClassREWroute::decl(void) {

	Description = "'Handles the routing of surface and subsurface runoff from RBs (representative basins).' \
                    'uses Muskingum,' \
                    'uses Clark.'";

	variation_set = VARIATION_ORG;


	inflowCnt = declgrpvar("WS_ALL_inflow", "basinflow", "query variable = 'basinflow'", "(m^3/int)", &rew, &inflow_All);

	declvar("WS_inflow", NHRU, "inflow from each RB", "(m^3/int)", &inflow);

	declstatdiag("cum_WSinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cuminflow);

	declvar("WS_outflow", NHRU, "outflow of each RB", "(m^3/int)", &outflow);

	declstatdiag("cum_WSoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumoutflow);

	declvar("WS_flow", BASIN, "watershed surface and sub-surface outflow", "(m^3/int)", &flow);

	declvar("WS_flow_s", BASIN, "watershed surface and sub-surface outflow", "(m^3/s)", &flow_s);

	declstatdiag("cum_WSflow", BASIN, "cumulative watershed surface and sub-surface outflow", "(m^3)", &cumflow);


	gwCnt = declgrpvar("WS_ALL_gwflow", "basingw", "query variable = 'basingw'", "(m^3/int)", &gwrew, &gw_All);

	declvar("WS_gwinflow", NHRU, "inflow from each RB", "(m^3/int)", &gwinflow);

	declstatdiag("cum_WSgwinflow", NHRU, "cumulative inflow from each RB", "(m^3)", &cumgwinflow);

	declvar("WS_gwoutflow", NHRU, "outflow of each RB", "(m^3/int)", &gwoutflow);

	declstatdiag("cum_WSgwoutflow", NHRU, "cumulative outflow of each RB", "(m^3)", &cumgwoutflow);

	declvar("WS_gwflow", BASIN, "watershed ground water outflow", "(m^3/int)", &gwflow);

	declvar("WS_gwflow_s", BASIN, "watershed ground water outflow", "(m^3/s)", &gwflow_s);

	declstatdiag("cum_WSgwflow", BASIN, "cumulative watershed ground water outflow", "(m^3)", &cumgwflow);


	declparam("watershed_area", BASIN, "3", "1e-6", "1e09", "Total watershed area", "(km^2)", &watershed_area);

	declparam("RB_area", NHRU, "[1]", "1e-6", "1e09", "RB area", "(km^2)", &RB_area);

	declparam("WS_Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_Lag);

	declparam("WS_gwLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &WS_gwLag);

	declparam("WS_whereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_whereto);

	declparam("WS_order", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_order);

	declparam("WS_gwwhereto", NHRU, "[0]", "0", "1000", "0 - watershed outflow, or RB input", "()", &WS_gwwhereto);

	declparam("WS_gworder", NHRU, "1,2,3,4,5!", "1", "1000", "RB routing process order", "()", &WS_gworder);


	variation_set = VARIATION_0;

	decldiag("WS_Ktravel_var", NHRU, "inflow storage constant", "(d)", &WS_Ktravel_var);

	decldiag("WS_gwKtravel_var", NHRU, "gw storage constant", "(d)", &WS_gwKtravel_var);


	declparam("WS_route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &WS_route_n);

	declparam("WS_route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "()", &WS_route_R);

	declparam("WS_route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &WS_route_S0);

	declparam("WS_route_L", NHRU, "[3.69]", "0.01", "1.0E10", "routing length", "(m)", &WS_route_L);

	declparam("WS_Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &WS_Channel_shp);

	declparam("WS_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_route_X_M);

	declparam("WS_gwX_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &WS_gwroute_X_M);


	variation_set = VARIATION_1;

	declparam("WS_Kstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_Kstorage);

	declparam("WS_gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "Clark storage constant", "(d)", &WS_gwKstorage);


	variation_set = VARIATION_ORG;
}

void ClassREWroute::init(void) {

	if (nhru < inflowCnt) {
		CRHMException Except("Module REW route # of HRUs must be >= # of groups.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	float totarea = 0;
	for (hh = 0; hh < nhru; ++hh)
		totarea += RB_area[hh];

	if (fabs((totarea - watershed_area[0]) / watershed_area[0]) > 1e-3) {
		const_cast<float *>  (watershed_area)[0] = totarea;
		CRHMException TExcept(string(string("Sum of RB's area <> Watershed area, Watershed area made = ") + Convert(totarea)).c_str(), WARNING);
		LogError(TExcept);
	}

	if (WS_whereto[WS_order[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'whereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (WS_gwwhereto[WS_gworder[nhru - 1] - 1] != 0) {
		CRHMException Except("In module REW route 'gwwhereto' for last RB must be zero.", TERMINATE);
		LogError(Except);
		throw Except;
	}

	if (variation == VARIATION_ORG) {
		const float Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

		for (hh = 0; hh < nhru; ++hh) {
			float Vavg = (1.0 / WS_route_n[hh])*pow(WS_route_R[hh], 2.0f / 3.0f)*pow(WS_route_S0[hh], 0.5f);

			WS_gwKtravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
			WS_Ktravel_var[hh] = WS_route_L[hh] / (Vw[WS_Channel_shp[hh]] * Vavg) / 86400.0; // (d)
		}

		inflowDelay = new ClassMuskingum(inflow, outflow, WS_Ktravel_var, WS_route_X_M, WS_Lag, nhru);
		gwDelay = new ClassMuskingum(gwinflow, gwoutflow, WS_gwKtravel_var, WS_gwroute_X_M, WS_gwLag, nhru);

		for (hh = 0; hh < nhru; ++hh) {
			if (WS_gwKtravel_var[hh] >= (Global::Interval / (2.0*WS_gwroute_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) GW Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (gwDelay->c0[hh] < 0.0) {
				gwDelay->c0[hh] = 0.0;
				gwDelay->c1[hh] = 1.0;
				gwDelay->c2[hh] = 0.0;
			}

			if (WS_Ktravel_var[hh] >= (Global::Interval / (2.0*WS_route_X_M[hh]))) {
			 string S = string("'" + Name + " (REW_route) inflow Muskingum coefficient negative in HRU ").c_str();
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}

			if (WS_Ktravel_var[hh] < (Global::Interval / (2.0*(1.0 - WS_route_X_M[hh])))) { //inflowDelay->c0[hh] < 0.0
				inflowDelay->c0[hh] = 0.0;
				inflowDelay->c1[hh] = 1.0;
				inflowDelay->c2[hh] = 0.0;
			}
		}
	}
	else if (variation == VARIATION_1) {
		Clark_inflowDelay = new ClassClark(inflow, outflow, WS_Kstorage, WS_Lag, nhru);
		Clark_gwDelay = new ClassClark(inflow, outflow, WS_gwKstorage, WS_gwLag, nhru);
	}

	flow[0] = 0.0;
	flow_s[0] = 0.0;
	cumflow[0] = 0.0;

	gwflow[0] = 0.0;
	gwflow_s[0] = 0.0;
	cumgwflow[0] = 0.0;

	for (hh = 0; hh < nhru; ++hh) {
		inflow[hh] = 0.0;
		cuminflow[hh] = 0.0;
		outflow[hh] = 0.0;
		cumoutflow[hh] = 0.0;
		gwinflow[hh] = 0.0;
		cumgwinflow[hh] = 0.0;
		gwoutflow[hh] = 0.0;
		cumgwoutflow[hh] = 0.0;
	}
}

void ClassREWroute::run(void) {

	flow[0] = 0.0;
	gwflow[0] = 0.0;

	for (long jj = 0; jj < inflowCnt; ++jj) { // HRUs not in sequence

		int hh = WS_order[jj] - 1;

		if (rew[hh])
			inflow[hh] = inflow_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			inflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_whereto[hhh] - 1 == hh && outflow[hhh] > 0.0) {
				if (outflow[hhh] > 0.0)
					inflow[hh] += outflow[hhh];
			}
		}

		cuminflow[hh] += inflow[hh];

		if (variation == VARIATION_ORG)
			inflowDelay->DoMuskingum(hh); // need to update for later HRUs
		else
			Clark_inflowDelay->DoClark(hh); // need to update for later HRUs

		cumoutflow[hh] += outflow[hh];

		if (WS_whereto[hh] == 0) {
			flow[0] += outflow[hh]; // (already m^3)
			flow_s[0] = flow[0] * Global::Freq / 86400.0;
		}
	} //end for

	for (long jj = 0; jj < gwCnt; ++jj) { // HRUs not in sequence

		int hh = WS_gworder[jj] - 1;

		if (gwrew[hh])
			gwinflow[hh] = gw_All[hh][0]; // add this HRU runoff and subsurface flow
		else
			gwinflow[hh] = 0; // add this HRU runoff and subsurface flow

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (WS_gwwhereto[hhh] - 1 == hh && gwoutflow[hhh] > 0.0) {
				if (gwoutflow[hhh] > 0.0)
					gwinflow[hh] += gwoutflow[hhh];
			}
		}

		cumgwinflow[hh] += gwinflow[hh];

		if (variation == VARIATION_ORG)
			gwDelay->DoMuskingum(hh); // need to update for later HRUs
		else
			Clark_gwDelay->DoClark(hh); // need to update for later HRUs

		cumgwoutflow[hh] += gwoutflow[hh];

		if (WS_gwwhereto[hh] == 0) {
			gwflow[0] += gwoutflow[hh]; // (already m^3)
			gwflow_s[0] = gwflow[0] * Global::Freq / 86400.0;
		}
	} //end for

	cumflow[0] += flow[0];
	cumgwflow[0] += gwflow[0];
}

void ClassREWroute::finish(bool good) {
	for (hh = 0; hh < inflowCnt; ++hh) {
		LogMessageA(hh, string("'" + Name + " (REW_route)' cuminflow          (m^3) (m^3): ").c_str(), cuminflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route)' cumoutflow         (m^3) (m^3): ").c_str(), cumoutflow[hh], 1.0);
		if (variation == VARIATION_ORG)
			LogMessageA(hh, string("'" + Name + " (REW_route)' inflowDelay_in_storage (m^3) (m^3): ").c_str(), inflowDelay->Left(hh), 1.0);
		else
			LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_inflowDelay_in_storage (m^3) (m^3): ").c_str(), Clark_inflowDelay->Left(hh), 1.0);

		LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwinflow  (m^3) (m^3): ").c_str(), cumgwinflow[hh], 1.0);
		LogMessageA(hh, string("'" + Name + " (REW_route)' cumgwoutflow (m^3) (m^3): ").c_str(), cumgwoutflow[hh], 1.0);
		if (variation == VARIATION_ORG)
			LogMessageA(hh, string("'" + Name + " (REW_route)' gwDelay_in_storage (m^3) (m^3): ").c_str(), gwDelay->Left(hh), 1.0);
		else
			LogMessageA(hh, string("'" + Name + " (REW_route)' Clark_gwDelay_in_storage (m^3) (m^3): ").c_str(), Clark_gwDelay->Left(hh), 1.0);

		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (REW_route)' cumflow (m^3): ").c_str(), cumflow[0]);
	LogMessage(string("'" + Name + " (REW_route)' cumgwflow (m^3): ").c_str(), cumgwflow[0]);
	LogDebug(" ");

	if (variation == VARIATION_ORG) {
		delete inflowDelay;
		delete gwDelay;
	}
	else {
		delete Clark_inflowDelay;
		delete Clark_gwDelay;
	}
}

Classglacier* Classglacier::klone(string name) const {
	return new Classglacier(name);
}

void Classglacier::decl(void) {

	Description = "'Energy-budget glacier model', \
                 'glacier using Brunt et al', \
                 'glacier using input variable Qnsn_Var (W/m^2*int) from CanopyClearing etc.', \
                 'glacier using input observation Qnsn (W/m^2*int)', \
                 'glacier using input observation QnD (MJ/m^2*d)'";

	variation_set = VARIATION_ORG;

	declvar("SWEmelt", NHRU, "daily SWE snowmelt", "(mm/d)", &SWEmelt);

	declvar("SWEmelt_delayed", NHRU, "daily SWE snowmelt delayed", "(mm/d)", &SWEmelt_delayed);

	declstatdiag("cumSWEmelt", NHRU, "cumulative SWE snowmelt", "(mm)", &cumSWEmelt);

	declvar("firnmelt", NHRU, "daily firn melt", "(mm/d)", &firnmelt);

	declvar("firnmelt_delayed", NHRU, "daily firn melt delayed", "(mm/d)", &firnmelt_delayed);

	declstatdiag("cumfirnmelt", NHRU, "cumulative firn melt", "(mm)", &cumfirnmelt);

	declvar("icemelt", NHRU, "daily ice melt", "(mm/d)", &icemelt);

	declvar("icemelt_delayed", NHRU, "daily ice melt delayed", "(mm/d)", &icemelt_delayed);

	declstatdiag("cumicemelt", NHRU, "cumulative ice melt", "(mm)", &cumicemelt);

	declstatvar("firn_dens", NDEFN, "densities of snow densification layers", "(kg/m^3)", &firn_dens, &firn_dens_array, Global::nlay);

	declstatvar("firn_h", NDEFN, "depths of snow densification layers", "(m)", &firn_h, &firn_h_array, Global::nlay);

	declstatvar("firn_yr", NDEFN, "layer[1] - years to 'critical density] and layer[2, ...] age of firn", "(yr)", &firn_yr, &firn_yr_array, Global::nlay);

	decldiagparam("firn_dens_init", NDEFN, "[220.0]", "0.0", "1000.0", "initial densities of firn densification layers", "(kg/m^3)", &firn_dens_init, &firn_dens_array_init, Global::nlay);

	decldiagparam("firn_h_init", NDEFN, "[0.0]", "0.0", "100.0", "initial depths of firn densification layers", "(m)", &firn_h_init, &firn_h_array_init, Global::nlay);


	declstatvar("ice", NHRU, "water equivalent of ice", "(mm)", &ice);

	declstatvar("firn", NHRU, "water equivalent of all firn layers", "(mm)", &firn);

	declvar("glacier_h2o", NHRU, "water equivalent of SWE, firn layers and ice", "(mm)", &glacier_h2o);

	declvar("glacier_depth", NHRU, "depth of glacier", "(m)", &glacier_depth);

	declvar("glacier_Surf", NHRU, "surface elevation of glacier (SWE, firn layers, ice and optionally land elevation)", "(m)", &glacier_Surf);

	declstatvar("firn_depth", NHRU, "depth of all firn layers", "(m)", &firn_depth);

	declvar("firn_init", NHRU, "initial water equivalent of all firn layers", "(mm)", &firn_init);

	declstatvar("nfirn", NHRU, "num of layers used in firn consolidation array", "()", &nfirn);

	decllocal("topo_elev", NHRU, "topography elevations below glacier", "(m)", &topo_elev);

	decllocal("rho_snow", NHRU, "rho of snow moved to furn", "(kg/m^3)", &rho_snow);

	declvar("Gmelt", NHRU, "Qmelt = Qn+Qh+Qe+Qp", "(MJ/d)", &Qmelt);

	decllocal("cumGmelt", NHRU, "cumulative Qmelt = Qn+Qh+Qe+Qp", "(MJ/d)", &cumQmelt);

	decllocal("cumnet_rain_glacier", NHRU, "cumulative net_rain + firn and ice melt", "(mm)", &cumnet_rain_glacier);

	decllocal("cumsnowmeltD_glacier", NHRU, "cumulative snowmeltD + firn and ice melt", "(mm)", &cumsnowmeltD_glacier);

	decldiag("Gn_ebsm", NHRU, "net radiation", "(MJ/d)", &Qn_ebsm);

	decldiag("Gh_ebsm", NHRU, "sensible heat", "(MJ/d)", &Qh_ebsm);

	decldiag("Ge_ebsm", NHRU, "latent heat", "(MJ/d)", &Qe_ebsm);

	decldiag("Gp_ebsm", NHRU, "input from rainfall", "(MJ/d)", &Qp_ebsm);

	decldiag("GlacierMode", NHRU, "1 - glacier, 0 - tongue (no firn or ice", "()", &GlacierMode);


	decldiag("SWE_2firn", NHRU, "end of summer SWE transferred to firn", "(mm)", &SWE_2firn);

	decldiag("SWE_2firn_dens", NHRU, "end of summer density of SWE transferred to firn", "(kg/m^3)", &SWE_2firn_dens);

	declstatdiag("cumSWE_2firn", NHRU, "cumulative SWE added to firn", "(mm)", &cumSWE_2firn);

	decldiag("firn_2ice", NHRU, "end of summer firn transferred to ice", "(mm)", &firn_2ice);

	decldiag("firn_2ice_dens", NHRU, "end of summer density of firn transferred to ice.", "(kg/m^3)", &firn_2ice_dens);

	declstatdiag("cumfirn_2ice", NHRU, "cumulative firn added to ice", "(mm)", &cumfirn_2ice);

	declvar("Gnet_rainD", NHRU, "daily net rain", "(mm/d)", &Gnet_rainD);

	declvar("net_rain_org", NHRU, "value of 'net_rain' before addition of SWE, firn and ice melt", "(mm/int)", &net_rain_org);

	declvar("cumnet_rain_org", NHRU, "value of 'net_rain' before addition of SWE, firn and ice melt", "(mm)", &cumnet_rain_org);


	decldiagparam("delay_melt", NHRU, "[0]", "0", "366", "inhibit melt until this Julian date. Default incorrect for the Southern Hemisphere", "()", &delay_melt);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("ice_init", NHRU, "[1.0]", "0.0", "1.0E6", "Initial water equivalent of glacier ice", "(mm)", &ice_init);

	declparam("firn_Albedo", NHRU, "[187.0]", "0.2", "0.9", "Initial glacier firn albedo", "()", &firn_Albedo);

	declparam("ice_Albedo", NHRU, "[187.0]", "0.2", "0.9", "Initial glacier ice albedo", "()", &ice_Albedo);

	declparam("ice_dens", NHRU, "[1000.0]", "200.0", "1000.0", "density of glacier ice", "(kg/m^3)", &ice_dens);

	declparam("TKMA", NHRU, "[30]", "-50", "50", "Mean annual temperature of glacier", "(�C)", &TKMA);

	declparam("SWEAA", NHRU, "[0.3]", "0.1", "10.0", "Mean annual accumulation of glacier SWE", "(m/yr)", &SWEAA);

	declparam("SWEstorage", NHRU, "[0.0]", "0.0", "200.0", "snowmelt storage constant", "(d)", &SWEstorage);

	declparam("SWELag", NHRU, "[0.0]", "0.0", "1.0E4.0", "snowmelt  lag delay", "(h)", &SWELag);

	declparam("topo_elev_init", NHRU, "[0]", "0", "1000", "elevation used to initialise 'topo_elev' when 'Elev_Adj_glacier_surf equals 0.0'", "(m)", &topo_elev_init);

	declparam("Elev_Adj_glacier_surf", NHRU, "[0]", "0", "1", " 0 - glacier_Surf (m) = glacier depth, 1 - glacier_Surf = glacier depth + land elevation", "()", &Elev_Adj_glacier_surf);

	declparam("firnstorage", NHRU, "[0.1]", "0.0", "200.0", "firn storage constant", "(d)", &firnstorage);

	declparam("firnLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "firn  lag delay", "(h)", &firnLag);

	declparam("icestorage", NHRU, "[0.1]", "0.0", "200.0", "ice melt storage constant", "(d)", &icestorage);

	declparam("iceLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "ice melt lag delay", "(h)", &iceLag);

	declparam("SWE_to_firn_Julian", NHRU, "[244]", "0", "366", "convert any SWE to firn on Julian day. 0 - inhibit transfer", "()", &SWE_to_firn_Julian);

	declparam("Densification", NHRU, "[0]", "0", "1", ". Densification method: 0 - simple linear, 1 - original", "()", &Densification);

	declparam("Densification_550", NHRU, "[100]", "0", "1000", ". Densification increment < 550", "()", &Densification_550);

	declparam("Densification_above_550", NHRU, "[100]", "0", "1000", ". Densification increment >= 550", "()", &Densification_above_550);

	decldiagparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporatation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("inhibit_firnmelt", NHRU, "[0]", "0", "1", "set to 1 to inhibit firn melt", "()", &inhibit_firnmelt);

	declparam("inhibit_icenmelt", NHRU, "[0]", "0", "1", "set to 1 to inhibit firn melt", "()", &inhibit_icemelt);

	declgetvar("*", "SunMax", "(h)", &sunmax);
	declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
	declgetvar("*", "QdfoD", "(MJ/m^2*d)", &QdfoD);
	declgetvar("*", "hru_tmean", "(�C)", &tmean);
	declgetvar("*", "hru_tmax", "(�C)", &tmax);
	declgetvar("*", "hru_tmin", "(�C)", &tmin);
	declgetvar("*", "hru_umean", "(m/s)", &umean);
	declgetvar("*", "hru_rhmean", "(%)", &rhmean);
	declgetvar("*", "hru_SunAct", "(h)", &sunact);
	declputvar("*", "SWE", "(mm)", &SWE);
	declputvar("*", "net_rain", "(mm/int)", &net_rain);
	declputvar("*", "snowmeltD", "(mm/d)", &snowmeltD);

	declputparam("*", "hru_elev", "(m)", &hru_elev);
	declputvar("*", "Pa", "(kPa)", &Pa);
	declputvar("*", "Albedo", "()", &Albedo);



	variation_set = VARIATION_0;

	decldiagparam("tfactor", NHRU, "[0.0]", "0.0", "10.0", "degree day melt factor", "(mm/d*�C)", &tfactor);

	decldiagparam("nfactor", NHRU, "[0.0]", "0.0", "10.0", "net radiation factor (typical value 3.0(mm*m^2/MJ))", "(mm*m^2/MJ)", &nfactor);

	decldiagparam("Use_QnD", NHRU, "[0]", "0", "1", "1 - Use QnD if available", "()", &Use_QnD);


	variation_set = VARIATION_0 + VARIATION_3;

	declreadobs("QnD", NHRU, "net radiation", "(MJ/m^2*d)", &QnD, HRU_OBS_Q, true); // must check for NULL


	variation_set = VARIATION_1 + VARIATION_2;

	declstatvar("Qnsn_Acc", NHRU, "accumulator for Qnsn_Var/Qnsn", "(W/m^2)", &Qnsn_Acc); // daily value


	variation_set = VARIATION_1;

	declgetvar("*", "Qnsn_Var", "(W/m^2*int)", &Qnsn_Var); // interval value


	variation_set = VARIATION_2;

	declreadobs("Qnsn", NHRU, "net radiation", "(W/m^2*int)", &Qnsn, HRU_OBS_Q);

	variation_set = VARIATION_ORG;
}

void Classglacier::init(void) {

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);

	if (nlay < 3) {
	 string S = string("'") + Name + " (glacier)' project file nlay(number of layers) must be greater than 2";
		CRHMException TExcept(S.c_str(), TERMINATE);
		LogError(TExcept);
		throw TExcept;
	}

	for (hh = 0; hh < nhru; ++hh) {

		ice[hh] = ice_init[hh]; // (mm)

		cumSWE_2firn[hh] = 0.0;
		cumfirn_2ice[hh] = 0.0;
		cumfirnmelt[hh] = 0.0;
		cumicemelt[hh] = 0.0;
		cumQmelt[hh] = 0.0;
		cumnet_rain_glacier[hh] = 0.0;
		cumsnowmeltD_glacier[hh] = 0.0;
		cumSWEmelt[hh] = 0.0;
		cumnet_rain_org[hh] = 0.0;
		rho_snow[hh] = 0.0;

		firn_init[hh] = 0.0;
		firn_depth[hh] = 0.0;
		SWE_2firn[hh] = 0.0;
		SWE_2firn_dens[hh] = 0.0;
		firn_2ice[hh] = 0.0;
		firn_2ice_dens[hh] = 0.0;
		firn[hh] = 0.0;
		nfirn[hh] = 0;
		GlacierMode[hh] = 1;
		glacier_h2o[hh] = 0.0;

		bool end_para = false;
		bool Warned = false;

		for (long ll = 0; ll < nlay; ++ll) {
			firn_yr_array[ll][hh] = 0.0;
			firn_h_array[ll][hh] = 0.0;
			firn_dens_array[ll][hh] = 0.0;

			if (firn_h_array_init[ll][hh] > 0.0) {
				if (end_para && !Warned) {
				 string S = string("'") + Name + " (glacier)' firn initialisation parameters not contiguous in hru = " + std::to_string(hh + 1).c_str();
					CRHMException TExcept(S.c_str(), WARNING);
					LogError(TExcept);
					Warned = true;
				}
				else if (!end_para)
					++nfirn[hh];

				firn_h_array[ll][hh] = firn_h_array_init[ll][hh] * 1000.0; // (m) to (mm)
				firn_dens_array[ll][hh] = firn_dens_array_init[ll][hh];
				firn_init[hh] += firn_h_array[ll][hh] * firn_dens_array[ll][hh] / 1000.0; // (mm)
				firn_depth[hh] += firn_h_array[ll][hh]; // (mm)

				firn[hh] += firn_h_array[ll][hh] * firn_dens_array[ll][hh] / 1000.0; // (mm)
			}
			else
				end_para = true;
		} // for nlay

		if (nfirn[hh] > nlay) { // nfirm always less than nlay
		 string S = string("'") + Name + " (glacier)' global 'nlay'(" + std::to_string(nlay).c_str() + ") must be greater than number of firn layers (" + std::to_string(nfirn[hh]).c_str() + ") in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
		}

		if (Elev_Adj_glacier_surf[hh]) // add glacier depth(m) to physical depth
			topo_elev[hh] = hru_elev[hh] - (firn_depth[hh] / 1000.0 + ice[hh] / ice_dens[hh]); // m
		else
			topo_elev[hh] = topo_elev_init[hh];

		Qmelt[hh] = 0.0;
		Qn_ebsm[hh] = 0.0;
		Qh_ebsm[hh] = 0.0;
		Qe_ebsm[hh] = 0.0;
		Qp_ebsm[hh] = 0.0;

		if (variation == VARIATION_ORG) {
			if (nfactor[hh] != 0.0 && QnD == NULL) {
				CRHMException TExcept("ebsm: nfactor > 0.0 with observation 'QnD' not defined!", TERMINATE);
				LogError(TExcept);
			}
		}
	} // for nhru

	SWEDelay = new ClassClark(SWEmelt, SWEmelt_delayed, SWEstorage, SWELag, nhru);
	firnDelay = new ClassClark(firnmelt, firnmelt_delayed, firnstorage, firnLag, nhru);
	iceDelay = new ClassClark(icemelt, icemelt_delayed, icestorage, iceLag, nhru);
}

void Classglacier::run(void) {

	long nstep;
	float umin, ref, rho;

	nstep = getstep();

	if (nstep == 1) { // must be here after 'hru_elev' parameter has been backed up
		for (hh = 0; hh < nhru; ++hh) {
			glacier_h2o[hh] = SWE[hh] + firn[hh] + ice[hh]; // water equivalent(mm)
			glacier_depth[hh] = (DepthofSnow(SWE[hh]) + firn_depth[hh]) / 1000.0 + ice[hh] / ice_dens[hh]; // (m) thickness
			glacier_Surf[hh] = glacier_depth[hh] + topo_elev[hh]; // (m)

			Pa[hh] = 101.3f*pow((293.0f - 0.0065f*glacier_Surf[hh]) / 293.0f, 5.26f);  // (kPa)
		}
	}

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		firn[hh] = 0.0;

		for (long nn = 0; nn < nfirn[hh]; ++nn)
			firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // (mm)

		if (firn[hh] <= 0.0 && ice[hh] <= 0.0) // treat as soil
			GlacierMode[hh] = 0;
		else {
			GlacierMode[hh] = 1;

			if (SWE[hh] <= 0.0 || ice_Albedo[hh] > Albedo[hh])
				if (firn[hh] > 0.0)
					Albedo[hh] = firn_Albedo[hh];
				else
					Albedo[hh] = ice_Albedo[hh]; // must be ice[hh] >= 0.0
		}

		net_rain_org[hh] = net_rain[hh];
		cumnet_rain_org[hh] += net_rain[hh];

		if (nstep == 1 || Global::Freq == 1) { // beginning of every day
			Gnet_rainD[hh] = net_rain[hh];
			if (variation == VARIATION_1)
				Qnsn_Acc[hh] = Qnsn_Var[hh];
			else if (variation == VARIATION_2)
				Qnsn_Acc[hh] = Qnsn[hh];
		}
		else {
			Gnet_rainD[hh] += net_rain[hh];
			if (variation == VARIATION_1)
				Qnsn_Acc[hh] += Qnsn_Var[hh];
			else if (variation == VARIATION_2)
				Qnsn_Acc[hh] += Qnsn[hh];
		}
	} // for hh

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		for (hh = 0; chkStruct(); ++hh) {

			Qmelt[hh] = 0.0;
			SWEmelt[hh] = snowmeltD[hh];
			cumSWEmelt[hh] += snowmeltD[hh];

			Qn_ebsm[hh] = 0.0;
			Qh_ebsm[hh] = 0.0;
			Qe_ebsm[hh] = 0.0;
			Qp_ebsm[hh] = 0.0;

			firnmelt[hh] = 0.0; // Has to be only once a daY
			icemelt[hh] = 0.0;

			// calculate SWE or firn

			if (SWE[hh] <= 0.0 && (firn[hh] > 0.0 || ice[hh] > 0.0)) {
				const_cast<long*> (inhibit_evap)[hh] = 1;

				if (variation == VARIATION_ORG && (tfactor[hh] > 0.0 || nfactor[hh] > 0.0)) {
					if (delay_melt[hh] <= julian("now")) {

						if (QnD) { // observation available (MJ/m^2*d)
							if (QnD[hh] > 0.0)
								Qn_ebsm[hh] = QnD[hh] * nfactor[hh]; // (mm/d)
						}

						Qh_ebsm[hh] = tmax[hh] * tfactor[hh]; // (mm/d)
						Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh];

						if (Qmelt[hh] <= 0.0)
							Qmelt[hh] = 0.0;
					}
				}
				else if (delay_melt[hh] <= julian("now")) {
					float eamean = Common::estar(tmean[hh])*rhmean[hh] / 100.0; \
						switch (variation) {
						case VARIATION_ORG:
							if (QnD != NULL && Use_QnD[hh]) { // observation available (MJ/m^2*d)
								if (QnD[hh] > 0.0)
									Qn_ebsm[hh] = QnD[hh];
							}
							else {
								Qn_ebsm[hh] = -0.53 + 0.47*(QdroD[hh] + QdfoD[hh])*(0.52 + 0.52*sunact[hh] / sunmax[hh])*(1.0 - Albedo[hh]);
							}
							break;
						case VARIATION_1:
							Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
							break;
						case VARIATION_2:
							Qn_ebsm[hh] = Qnsn_Acc[hh] * 0.0864 / Global::Freq; // convert to (MJ/m^2*d)
							break;
						case VARIATION_3:
							Qn_ebsm[hh] = QnD[hh]; // already (MJ/m^2*d)
							break;
						} // switch

					Qh_ebsm[hh] = -0.92 + 0.076*umean[hh] + 0.19*tmax[hh];
					Qe_ebsm[hh] = 0.08*(0.18 + 0.098*umean[hh])*(6.11 - eamean * 10.0);

					if (Gnet_rainD[hh] > 0.0)
						Qp_ebsm[hh] = Gnet_rainD[hh] * tmean[hh] * 4.2 / 1000.0;
					else
						Qp_ebsm[hh] = 0.0;

					Qmelt[hh] = Qn_ebsm[hh] + Qh_ebsm[hh] + Qe_ebsm[hh] + Qp_ebsm[hh];

					Qmelt[hh] = Qmelt[hh] / 316.8*1000.0; // thermal quality B=0.95. 316.8 = 333.5*0.95 (kJ/kg), (mm/d)

					if (Qmelt[hh] <= 0.0)
						Qmelt[hh] = 0.0;
				}
			} // no snow so melt firn or ice!

			if (firn[hh] > 0.0 || ice[hh] > 0.0) {

				if (nfirn[hh] > 0 && Qmelt[hh] > 0.0 && !inhibit_firnmelt[hh]) { // melt firn
					float h2o;
					while (nfirn[hh] > 0 && Qmelt[hh] > 0.0) {
						h2o = firn_dens_array[0][hh] * firn_h_array[0][hh] / 1000.0;
						if (Qmelt[hh] < h2o) { // melt some firn
							firnmelt[hh] += Qmelt[hh];
							cumQmelt[hh] += Qmelt[hh];
							firn_h_array[0][hh] = (h2o - Qmelt[hh])*1000.0 / firn_dens_array[0][hh];
							Qmelt[hh] = 0.0;
						}
						else { // All firn melts
							firnmelt[hh] += h2o;
							Qmelt[hh] -= h2o;
							cumQmelt[hh] += h2o;
							for (long nn = 0; nn < nfirn[hh] - 1; ++nn) { // move columns up
								firn_dens_array[nn][hh] = firn_dens_array[nn + 1][hh];
								firn_h_array[nn][hh] = firn_h_array[nn + 1][hh];
							} // end for
							--nfirn[hh];
							firn_dens_array[nfirn[hh]][hh] = 0.0;
							firn_h_array[nfirn[hh]][hh] = 0.0;
							if (ice[hh] <= 0.0)
								const_cast<long*> (inhibit_evap)[hh] = 0;
						}
						cumfirnmelt[hh] += firnmelt[hh];
					} // end while

					firn_depth[hh] = 0.0;
					firn[hh] = 0.0;

					for (long nn = 0; nn < nfirn[hh]; ++nn) {
						firn_depth[hh] += firn_h_array[nn][hh];
						firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // mm
					}
				}  // if
				   // handle ice
				else if (ice[hh] > 0.0 && Qmelt[hh] > 0.0 && !inhibit_icemelt[hh]) {
					if (Qmelt[hh] >= ice[hh]) { // melt layer
						icemelt[hh] = ice[hh];
						Qmelt[hh] -= icemelt[hh];
						cumQmelt[hh] += icemelt[hh];
						ice[hh] = 0.0;
						const_cast<long*> (inhibit_evap)[hh] = 0;
					}
					else { // melt some ice
						ice[hh] -= Qmelt[hh];
						cumQmelt[hh] += Qmelt[hh];
						icemelt[hh] = Qmelt[hh];
						Qmelt[hh] = 0.0;
					}
					cumicemelt[hh] += icemelt[hh];
				}

				// Update glacier at end of summer

				const float R = 8.314; // (J/(K.mol)
				const float RHOi = 917; // (kg/m3)

				long Julian = julian("now"); // same as "decday"
				if (SWE_to_firn_Julian[hh] == Julian) { // use fixed date - end of day    !!!!

					float k0 = 11.0*exp(-10160.0 / (R*(TKMA[hh] + CRHM_constants::Tm)));
					float k1 = 575.0*exp(-21400.0 / (R*(TKMA[hh] + CRHM_constants::Tm)));

					// Check if bottom layer of firn becomes ice
					if (nfirn[hh] && firn_dens_array[nfirn[hh] - 1][hh] >= 830.0) { // transfer
						firn_2ice[hh] = firn_dens_array[nfirn[hh] - 1][hh] * firn_h_array[nfirn[hh] - 1][hh] / 1000.0; // ice (mm)
						ice[hh] += firn_2ice[hh];
						cumfirn_2ice[hh] = firn_2ice[hh];
						firn_2ice_dens[hh] = firn_dens_array[nfirn[hh] - 1][hh];
						firn_dens_array[nfirn[hh] - 1][hh] = 0.0;
						firn_h_array[nfirn[hh] - 1][hh] = 0.0; // (mm)
						--nfirn[hh];
					}
					else {
						firn_2ice[hh] = 0.0;
						firn_2ice_dens[hh] = 0.0;
					}

					// Add new SWE

					if (SWE[hh] > 0.0) {
						if (nfirn[hh] == nlay) { // combine last two entries
							float mean_d = (firn_dens_array[nlay - 2][hh] + firn_dens_array[nlay - 1][hh]) / 2.0;
							firn_h_array[nlay - 2][hh] = (firn_h_array[nlay - 2][hh] * firn_dens_array[nlay - 2][hh] + firn_h_array[nlay - 1][hh] * firn_dens_array[nlay - 1][hh]) / mean_d;
							firn_dens_array[nlay - 2][hh] = mean_d;
							--nfirn[hh]; // remove layer from SWE
						}

						for (long nn = nlay - 2; nn >= 0; --nn) { // move column down opening space
							firn_dens_array[nn + 1][hh] = firn_dens_array[nn][hh];
							firn_h_array[nn + 1][hh] = firn_h_array[nn][hh];
						}

						if (nfirn[hh] >= nlay) { // space available to allocate layer !!! check purpose/position !!!
						 string S = string("'") + Name + " (glacier)' too many firn fronts in hru = " + std::to_string(hh + 1).c_str();
							CRHMException TExcept(S.c_str(), TERMINATE);
							LogError(TExcept);
							throw TExcept;
						}
						++nfirn[hh];

						// solve for density from SWE using Bisection method

						float h1 = 0.6, h2 = 8.00, e, h;
						long iter_max = 0;
						do {
							h = (h1 + h2) / 2.0; // (m)
							rho = (450.0 - 204.7 / h * (1.0 - exp(-h / 0.673))); // Pomeroy et al (1998)
							e = rho * h - SWE[hh]; // original equation was cm
							if (e < 0)
								h1 += (h2 - h1) / 2.0;
							else
								h2 -= (h2 - h1) / 2.0;

						} while (fabs(e) > 0.001 && h > 0.601 && ++iter_max < 100); // below 60cm the density is 250 kg/m3

						firn_h_array[0][hh] = SWE[hh] * 1000.0 / rho;
						firn_dens_array[0][hh] = rho;

						firn_yr_array[0][hh] = 1.0 / (k0*SWEAA[hh])*log((RHOi - firn_dens_array[0][hh]) / (RHOi - 550));

						SWE_2firn[hh] = SWE[hh];
						cumSWE_2firn[hh] += SWE[hh];
						SWE_2firn_dens[hh] = rho;
						SWE[hh] = 0.0;
					} // add SWE
					else
						rho = 249.0; // value for SWE = 0.1mm

									 // Update firn layer densities

					rho_snow[hh] = rho;
					firn_depth[hh] = firn_h_array[0][hh]; // (mm)
					firn[hh] = firn_dens_array[0][hh] * firn_h_array[0][hh] / 1000.0; // (mm)
					if (nfirn[hh] > 0)
						for (long nn = 1; nn < nfirn[hh]; ++nn) {
							float old_firn = firn_dens_array[nn][hh] * firn_h_array[nn][hh] / 1000.0;

							if (old_firn == 0.0) {
								old_firn = hh * 100 + nn;
								assert(0);
							}
							float h550 = 1000.0 / (RHOi*k0)*(log(550.0 / (RHOi - 550.0)) - log(rho / (RHOi - rho))); // rho is current SWE density      Densification
							if (Densification[hh] != 0) {
								if (firn_dens_array[nn][hh] < 550.0) { // density < 550
									float Z0 = exp(RHOi*k0*firn_depth[hh] / 10e6 + log(firn_dens_array[nn][hh] / (RHOi - firn_dens_array[nn][hh])));
									float New = RHOi * Z0 / (1.0 + Z0);
									if (New > firn_dens_array[nn][hh])
										firn_dens_array[nn][hh] = New;
									firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
									firn_yr_array[nn][hh] = 1.0 / (k0*SWEAA[hh])*log((RHOi - rho) / (RHOi - 550));
								}
								else { // density >= 550
									float Z1 = exp(RHOi*k1*(firn_depth[hh] / 1000.0 - h550) / 1000.0 / sqrt(SWEAA[hh]) + log(550.0 / (RHOi - 550.0)));
									float New = RHOi * Z1 / (1.0 + Z1);
									if (New > firn_dens_array[nn][hh])
										firn_dens_array[nn][hh] = New;
									firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
									float t550 = 1.0 / (k0*SWEAA[hh])*(log((RHOi - rho) / (RHOi - 550))); // units years
									firn_yr_array[nn][hh] = 1.0 / (k1*sqrt(SWEAA[hh]))*log((RHOi - 550) / (RHOi - firn_dens_array[nn][hh])) + t550;
								}
							}
							else {
								firn_yr_array[nn][hh] = 0.0;
								if (firn_dens_array[nn][hh] < 550.0) {
									firn_dens_array[nn][hh] += Densification_550[hh];
									firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
								}
								else {
									firn_dens_array[nn][hh] += Densification_above_550[hh];
									if (firn_dens_array[nn][hh] > 1000.0)
										firn_dens_array[nn][hh] = 1000.0;
									firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
								}
							}

							firn_h_array[nn][hh] = old_firn / firn_dens_array[nn][hh] * 1000.0;
							firn_depth[hh] += firn_h_array[nn][hh];

							firn[hh] += firn_h_array[nn][hh] * firn_dens_array[nn][hh] / 1000.0; // (mm)
						} // for nn
				} // end update SWE and firn
			} // update firn or ice!
		} // end for HRUs
	} // end if (end of day)

	SWEDelay->DoClark();
	firnDelay->DoClark();
	iceDelay->DoClark();

	for (hh = 0; chkStruct(); ++hh) {
		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*glacier_Surf[hh]) / 293.0f, 5.26f);  // (kPa)

		if (GlacierMode[hh] == 1) { // ie glacier
			glacier_h2o[hh] = SWE[hh] + firn[hh] + ice[hh]; // water equivalent(mm)
			glacier_depth[hh] = (DepthofSnow(SWE[hh]) + firn_depth[hh]) / 1000.0 + ice[hh] / ice_dens[hh]; // (m) thickness
			glacier_Surf[hh] = glacier_depth[hh] + topo_elev[hh]; // (m)

			net_rain[hh] += (firnmelt_delayed[hh] + icemelt_delayed[hh]) / Global::Freq;
		}
		cumnet_rain_glacier[hh] += net_rain[hh];
		cumsnowmeltD_glacier[hh] += snowmeltD[hh] / Global::Freq;
	} // end for HRUs

}

void Classglacier::finish(bool good) {

	float Glacier_All = 0.0;
	float SWE_All = 0.0;
	float firn_All = 0.0;
	float ice_All = 0.0;
	float firn_init_All = 0.0;
	float ice_init_All = 0.0;
	float firn_change_All = 0.0;
	float ice_change_All = 0.0;
	float cumfirnmelt_All = 0.0;
	float cumSWE_2firn_All = 0.0;
	float cumicemelt_All = 0.0;
	float cumfirn_2ice_All = 0.0;
	float cumnet_rain_glacier_All = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (glacier)' firn_init    (mm) (mm*hru) (mm*hru/basin): ").c_str(), firn_init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' firn_final   (mm) (mm*hru) (mm*hru/basin): ").c_str(), firn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumfirnmelt  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumfirnmelt[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumSWE_2firn (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_2firn[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' firn_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), (firn[hh] - firn_init[hh]), hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumicemelt   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumicemelt[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumfirn_2ice (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumfirn_2ice[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' ice_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice_init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' ice          (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' ice_change   (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh] - ice_init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumnet_rain_org      (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain_org[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumnet_rain_glacier  (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumnet_rain_glacier[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumSWEmelt_org       (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumSWEmelt[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (glacier)' cumsnowmeltD_glacier (mm)  (mm*hru) (mm*hru/basin): ").c_str(), cumsnowmeltD_glacier[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Glacier_All += glacier_h2o[hh];
		SWE_All += SWE[hh];
		firn_All += firn[hh];
		ice_All += ice[hh];
		firn_init_All += firn_init[hh];
		ice_init_All += ice_init[hh];
		firn_change_All += firn[hh] - firn_init[hh];
		ice_change_All += ice_init[hh] - ice[hh];
		cumfirnmelt_All += cumfirnmelt[hh];
		cumSWE_2firn_All += cumSWE_2firn[hh];
		cumicemelt_All += cumicemelt[hh];
		cumfirn_2ice_All += cumfirn_2ice[hh];
		cumnet_rain_glacier_All += cumnet_rain_glacier[hh];
		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (glacier)' SWE_All               (mm*basin): ").c_str(), SWE_All, "      *** cumulative sum of all HRU SWE");
	LogMessage(string("'" + Name + " (glacier)' firn_All              (mm*basin): ").c_str(), firn_All, "      *** cumulative sum of all HRU firn");
	LogMessage(string("'" + Name + " (glacier)' ice_All               (mm*basin): ").c_str(), ice_All, "      *** cumulative sum of all HRU ice");
	LogMessage(string("'" + Name + " (glacier)' Glacier_All           (mm*basin): ").c_str(), Glacier_All, "      *** cumulative sum of all of above");
	LogDebug(" ");
	LogMessage(string("'" + Name + " (glacier)' firn_init_All         (mm*basin): ").c_str(), firn_init_All, "      *** cumulative sum of all HRU firn_init");
	LogMessage(string("'" + Name + " (glacier)' ice_init_All          (mm*basin): ").c_str(), ice_init_All, "      *** cumulative sum of all HRU ice_init");
	LogDebug(" ");
	LogMessage(string("'" + Name + " (glacier)' firn_change_All       (mm*basin): ").c_str(), firn_change_All, "      *** cumulative sum of all HRU firn change");
	LogMessage(string("'" + Name + " (glacier)' ice_change_All        (mm*basin): ").c_str(), ice_change_All, "      *** cumulative sum of all HRU ice change");
	LogDebug(" ");
	LogMessage(string("'" + Name + " (glacier)' cumfirnmelt_All       (mm*basin): ").c_str(), cumfirnmelt_All, "      *** cumulative sum of all HRU firnmelt");
	LogMessage(string("'" + Name + " (glacier)' cumSWE_2firn_All      (mm*basin): ").c_str(), cumSWE_2firn_All, "      *** cumulative sum of all HRU cumSWE_2firn");
	LogMessage(string("'" + Name + " (glacier)' cumfirn_2ice_All      (mm*basin): ").c_str(), cumfirn_2ice_All, "      *** cumulative sum of all HRU cumSWE_2firn");
	LogMessage(string("'" + Name + " (glacier)' cumicemelt_All        (mm*basin): ").c_str(), cumicemelt_All, "      *** cumulative sum of all HRU cumicemelt");
	LogMessage(string("'" + Name + " (glacier)' cumnet_rain_glacier_All (mm*basin): ").c_str(), cumnet_rain_glacier_All, "      *** cumulative sum of all HRU rain + firn and ice melt");
	LogDebug(" ");

	delete firnDelay;
	delete iceDelay;
}

float Classglacier::DepthofSnow(float SWE) { // (mm)

											 // Tabler et al. (1990b) Calculates Snow Depth(mm) from SWE(mm)
	float rho;

	if (SWE > 1.0) {
		rho = 522.0 - 204700 / SWE * (1.0 - exp(-SWE / 673.0)); // converted from original cm to mm
		return SWE / rho * 1000.0; // (mm)
	}
	else
		return 0.0;

} // DepthofSnow

ClassXG* ClassXG::klone(string name) const {
	return new ClassXG(name);
}

void ClassXG::decl(void) {

	Description = "'A Simple Thaw-Freeze Algorithm (Changwei, 2013).' \
                 'using variable surface temperature hru_tsf (�C),' \
                 'using variable air temperature hru_t (�C) and uses parameter n_factor (Woo (2012, p. 57) to estimate surface temperature from the air temperature during snow free periods.'";

	ko = 0.21;  // W/(m K) organic material
	km = 2.50;  // W/(m K) mineral
	ka = 0.025; // W/(m K) air
	ki = 2.24;  // W/(m K) ice  2.24
	kw = 0.57;  // W/(m K) water   0.57

	variation_set = VARIATION_ORG;

	declstatvar("Zd_front", NDEFN, "depth of freezing/thawing fronts", "(m)", &Zd_front, &Zd_front_array, Global::nlay);

	declstatvar("Zdf", NHRU, "active freezing front", "(m)", &Zdf);

	declstatvar("Zdt", NHRU, "active thawing front", "(m)", &Zdt);

	declstatvar("Th_low_lay", NHRU, "lowest thawed layer", "()", &Th_low_lay);

	declstatvar("Fz_low_lay", NHRU, "lowest frozen layer", "()", &Fz_low_lay);

	declstatvar("nfront", NHRU, "number of freezing/thawing fronts", "()", &nfront);

	declstatvar("Bfr", NHRU, "freeze degree days", "(�C*d)", &Bfr);

	declstatvar("Bth", NHRU, "thaw degree days", "(�C*d)", &Bth);

	declvar("pf", NDEFN, "freezing ratios", "()", &pf, &pf_lay, Global::nlay);

	declvar("pt", NDEFN, "thawing ratios", "()", &pt, &pt_lay, Global::nlay);

	declstatvar("ttc", NDEFN, "thawing thermal conductivity", "(W/(m*K)", &ttc, &ttc_lay, Global::nlay);

	declstatvar("ftc", NDEFN, "freezing thermal conductivity", "(W/(m*K)", &ftc, &ftc_lay, Global::nlay);

	declstatvar("ttc_contents", NDEFN, "thawing 0/1 thaw/freeze", "()", &ttc_contents, &ttc_contents_lay, Global::nlay);

	declstatvar("ftc_contents", NDEFN, "freezing 0/1 freeze/thaw", "()", &ftc_contents, &ftc_contents_lay, Global::nlay);

	declvar("tc_composite", NDEFN, "freeze/thaw composite ftc/ttc value", "(W/(m*K)", &tc_composite, &tc_composite_lay, Global::nlay);

	declvar("tc_composite2", NDEFN, "freeze/thaw composite2 ftc/ttc value", "(W/(m*K)", &tc_composite2, &tc_composite2_lay, Global::nlay);

	declvar("layer_h2o", NDEFN, "water content", "(kg/m^3)", &layer_h2o, &h2o_lay, Global::nlay);

	decllocal("B", NHRU, "freeze degree days", "()", &B);

	decllocal("TrigAcc", NHRU, "freeze degree days", "()", &TrigAcc);

	decllocal("TrigState", NHRU, "1/0/-1 thaw/standby/freeze", "()", &TrigState);

	decldiag("XG_moist_d", NHRU, "soil moisture depth", "()", &XG_moist_d);

	decldiag("XG_rechr_d", NHRU, "XG calculated soil recharge depth", "()", &XG_rechr_d);

	decllocal("check_XG_moist", NHRU, "sum of XG soil_moist should equal SoilX soil_moist", "()", &check_XG_moist);

	decllocal("t_trend", NHRU, "temperature long term trend", "(�C)", &t_trend);

	decllocal("check_t", NHRU, "check temperature source", "(�C)", &check_t);

	declstatvar("XG_max", NDEFN, "layer maximum soil moisture content", "(mm)", &XG_max, &XG_max_lay, Global::nlay);

	declstatvar("XG_moist", NDEFN, "layer soil moisture content", "(mm)", &XG_moist, &XG_moist_lay, Global::nlay);

	declvar("theta", NDEFN, "XG theta calulated from soil moistures and defaults", "(m^3/m^3)", &theta, &theta_lay, Global::nlay);

	declstatvar("rechr_fract", NDEFN, "fraction of layer moisture assigned to soilX soil_rechr.", "()", &rechr_fract, &rechr_fract_lay, Global::nlay);

	declstatvar("moist_fract", NDEFN, "fraction of layer moisture assigned to soilX soil_moist.", "()", &moist_fract, &moist_fract_lay, Global::nlay);

	declstatvar("default_fract", NDEFN, "below defined soil_moist profile - use default ", "()", &default_fract, &default_fract_lay, Global::nlay);


	decldiagparam("Trigthrhld", NHRU, "[100.0]", "50.0", "1000.0", "Trigger reference level in degree days", "(�C*d)", &Trigthrhld);

	declparam("N_Soil_layers", NHRU, "[2]", "1", "20", "number of soil layers. Must be less than or equal nlay. Define Parameters for layers used. All others are ignored", "()", &N_Soil_layers);

	declparam("calc_coductivity", NHRU, "[0]", "0", "1", "0 - linear method, 1 - use Johansen 1975", "()", &calc_coductivity);

	declparam("depths", NDEFN, "[0.5]", "0.0", "10.0", "depths(thickness) of soil layers", "(m)", &depths, &depths_lay, Global::nlay);

	declparam("por", NDEFN, "[0.5]", "0.0", "1.0", "porosity", "(m^3/m^3)", &por, &por_lay, Global::nlay);

	declparam("theta_default", NDEFN, "[0.5]", "0.0", "1.0", "default degree of saturation when not defined by soil module profile from module 'soilX')", "(m^3/m^3)", &theta_default, &theta_default_lay, Global::nlay);

	declparam("theta_min", NHRU, "[0.001]", "0.0001", "0.1", "minimum value of theta to prevent divide by zero errors)", "(m^3/m^3)", &theta_min);

	declparam("soil_solid_km", NDEFN, "[2.5]", "0.03", "4", "dry soil thermal conductivity", "(W/(m*K)", &soil_solid_km, &soil_solid_km_lay, Global::nlay);

	declparam("soil_solid_km_ki", NDEFN, "[2.5]", "0.03", "4", "saturated frozen soil thermal conductivity", "(W/(m*K)", &soil_solid_km_ki, &soil_solid_km_ki_lay, Global::nlay);

	declparam("soil_solid_km_kw", NDEFN, "[2.5]", "0.03", "4", "saturated unfrozen soil thermal conductivity.", "(W/(m*K)", &soil_solid_km_kw, &soil_solid_km_kw_lay, Global::nlay);

	declparam("SWE_k", NHRU, "[0.35]", "0.1", "1.0", "thermal conductivity of blowing snow.", "(W/(m*K)", &SWE_k);

	declparam("Zdf_init", NHRU, "[0]", "0.0", "3", "initial depth of freezing front. Maximum value limited by freezing algorithm.", "(m)", &Zdf_init);

	declparam("Zdt_init", NHRU, "[0]", "0.0", "3", "initial depth of thawing front. Maximum value limited by thawing algorithm.", "(m)", &Zdt_init);

	declparam("Zpf_init", NHRU, "[2]", "0.0", "30", "initial depth of permafrost front. Maximum value limited by thawing algorithm. If zero set to 2m", "(m)", &Zpf_init);

	declparam("freeze_kw_ki_update", NHRU, "[0]", "0", "1", "Change thermal conductivities kw to ki behind freezing front.", "()", &freeze_kw_ki_update);

	declparam("thaw_ki_kw_update", NHRU, "[0]", "0", "1", "Change thermal conductivities ki to kw behind thawing front.", "()", &thaw_ki_kw_update);

	declparam("k_update", NHRU, "[0]", "0", "2", "Change thermal conductivities ki to kw 0 - never, 1 _ after processing layer, 2 - continuously through layer.", "()", &k_update);

	declgetparam("*", "soil_moist_max", "(mm)", &soil_moist_max); // used since no declgetparam defined

	declgetparam("*", "soil_rechr_max", "(mm)", &soil_rechr_max); // used since no declgetparam defined


	declgetvar("*", "soil_moist", "(mm)", &soil_moist);

	declgetvar("*", "soil_rechr", "(mm)", &soil_rechr);


	variation_set = VARIATION_0;

	declgetvar("*", "hru_tsf", "(�C)", &hru_tsf);


	variation_set = VARIATION_1;

	declparam("n_factor_a", NHRU, "[0.5]", "0", "1.2", "n_factor = n_factor_a - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_a);

	declparam("n_factor_b", NHRU, "[0.54]", "0.0", "1.0", "n_factor = n_factor_b - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_b);

	declparam("n_factor_c", NHRU, "[0.05]", "0.0", "0.1", "n_factor = n_factor_c - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_c);

	decllocal("n_factor_T", NHRU, "Days after the start of thaw", "()", &n_factor_T);

	decllocal("n_factor", NHRU, "calculated value of n_factor from parameters. Woo (2012), p. 57", "()", &n_factor);

	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "SWE", "(mm)", &SWE);


	variation_set = VARIATION_ORG;
}

void ClassXG::init(void) {

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);

	front_size = nlay; // first two locations used by active Zdf and Zdt. Last location always 0.0, i.e. end of stack. Not related to nlay. Only dimensioned as nlay for convenience

	if (front_size < 4) { //
		CRHMException TExcept("number of layers (nlay) should 4 or greater to give 1 or more fronts.", TERMINATE);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {

		if (N_Soil_layers[hh] > nlay) {
			CRHMException TExcept("nlay cannot be less than N_Soil_layers.", TERMINATE);
			LogError(TExcept);
		}

		nfront[hh] = 0;
		Fz_low_lay[hh] = 1;
		Th_low_lay[hh] = 1;
		t_trend[hh] = 0.0;

		if (Zpf_init[hh] <= 0.0)
			const_cast<float *> (Zpf_init)[hh] = 2.0;

		for (long ll = 0; ll < nlay; ++ll)
			Zd_front_array[ll][hh] = 0.0;

		float rechrmax = soil_rechr_max[hh];
		float soilmax = soil_moist_max[hh];
		float profile_depth = 0.0;

		XG_rechr_d[hh] = 0.0;
		XG_moist_d[hh] = 0.0;

		for (long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
			tc_composite_lay[ll][hh] = 0;
			tc_composite2_lay[ll][hh] = 0;
			profile_depth += depths_lay[ll][hh];

			XG_max_lay[ll][hh] = por_lay[ll][hh] * depths_lay[ll][hh] * 1000.0;
			theta_lay[ll][hh] = theta_default_lay[ll][hh]; // initially make the default value

			if (rechrmax > 0.0) { // distribute moisture over layers
				if (rechrmax > XG_max_lay[ll][hh]) {
					XG_rechr_d[hh] += depths_lay[ll][hh];
					rechr_fract_lay[ll][hh] = 1.0;
					rechrmax -= XG_max_lay[ll][hh];
				}
				else {
					float amount = rechrmax / XG_max_lay[ll][hh];
					rechr_fract_lay[ll][hh] = rechrmax / XG_max_lay[ll][hh];

					XG_rechr_d[hh] += depths_lay[ll][hh] * amount;
					float left = 1.0 - amount;
					if (soilmax >= XG_max_lay[ll][hh] * left) { // layer all used
						moist_fract_lay[ll][hh] = left;
						soilmax -= XG_max_lay[ll][hh] * left;
						XG_moist_d[hh] += depths_lay[ll][hh];
					}
					else { // layer partly used
						moist_fract_lay[ll][hh] = (soilmax - rechrmax) / XG_max_lay[ll][hh];
						float used = rechr_fract_lay[ll][hh] + moist_fract_lay[ll][hh];
						default_fract_lay[ll][hh] = 1.0 - used;
						XG_moist_d[hh] += (XG_rechr_d[hh] + depths_lay[ll][hh] * used);
						soilmax = 0.0;
					}
					rechrmax = 0.0;
				}
			}
			else if (soilmax > 0.0) { // distribute remaining moisture over layers
				if (soilmax >= XG_max_lay[ll][hh]) {
					XG_moist_d[hh] += depths_lay[ll][hh];
					moist_fract_lay[ll][hh] = 1.0;
					soilmax -= XG_max_lay[ll][hh];
				}
				else {
					float amount = soilmax / XG_max_lay[ll][hh];
					XG_moist_d[hh] += depths_lay[ll][hh] * amount;
					moist_fract_lay[ll][hh] = amount;

					float left = 1.0 - amount;
					if (left) // adjust last layer depth
						default_fract_lay[ll][hh] = left;
					soilmax = 0.0;
				}
			}
			else { // profile below active SoilX
				default_fract_lay[ll][hh] = 1;

			}
		} // for soil layers

		  // Calculate thermal conductivities

		Th_low_lay[hh] = 1;
		Fz_low_lay[hh] = 1;
		check_XG_moist[hh] = 0.0;

		for (long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
			if (soil_moist_max[hh] > 0.0) // handle soil_moist_max = 0.0, i.e. slough
				XG_moist_lay[ll][hh] = rechr_fract_lay[ll][hh] * XG_max_lay[ll][hh] * soil_rechr[hh] / soil_rechr_max[hh]
				+ moist_fract_lay[ll][hh] * XG_max_lay[ll][hh] * (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				XG_moist_lay[ll][hh] = 0.0;

			check_XG_moist[hh] += XG_moist_lay[ll][hh];

			XG_moist_lay[ll][hh] += default_fract_lay[ll][hh] * XG_max_lay[ll][hh] * theta_default_lay[ll][hh]; // adjust for below profile theta

			theta_lay[ll][hh] = XG_moist_lay[ll][hh] / XG_max_lay[ll][hh];

			if (theta_lay[ll][hh] <= theta_min[hh]) // do not allow zero values
				theta_lay[ll][hh] = theta_min[hh];

			h2o_lay[ll][hh] = theta_lay[ll][hh] * por_lay[ll][hh] * 1000; // water kg/m3 was water fraction

			if (k_update[hh]) { // change all layers to dynamic
				if (ftc_contents_lay[ll][hh] == 1) // always set somewhere else
					ftc_lay[ll][hh] = get_ttc_lay(ll);
				else
					ftc_lay[ll][hh] = get_ftc_lay(ll);

				if (ttc_contents_lay[ll][hh] == 1) // always set somewhere else
					ttc_lay[ll][hh] = get_ftc_lay(ll);
				else
					ttc_lay[ll][hh] = get_ttc_lay(ll);
			}
			else {
				ftc_lay[ll][hh] = get_ftc_lay(ll);
				ttc_lay[ll][hh] = get_ttc_lay(ll);

				ftc_contents_lay[ll][hh] = 0;
				ttc_contents_lay[ll][hh] = 0;
			}
		} // for layers

		for (long ll = 1; ll < N_Soil_layers[hh]; ++ll) {
			pf_lay[ll][hh] = sqrt(ftc_lay[ll - 1][hh] * h2o_lay[ll][hh] / (ftc_lay[ll][hh] * h2o_lay[ll - 1][hh])); // water kg/m3
			pt_lay[ll][hh] = sqrt(ttc_lay[ll - 1][hh] * h2o_lay[ll][hh] / (ttc_lay[ll][hh] * h2o_lay[ll - 1][hh])); // water kg/m3
		}

		if (rechrmax != 0.0 || soilmax != 0.0) {
		 string S = string("'") + Name + " (XG)' too few layers (nlay) to handle soil_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
		}

		if (profile_depth + 0.00001 < Zpf_init[hh]) { // values in Debug Inspector identical but comparison TRUE
		 string S = string("'") + Name + " (XG)' sum of soil layer depths is less than the depth of the initial permafrost in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
		}

		bool EndofProfile = false;

		for (long ll = 0; ll < nlay; ++ll) {

			if (ll + 1 > N_Soil_layers[hh]) {
				EndofProfile = true;
			}

			if (depths_lay[ll][hh] == 0.0 && !EndofProfile) {
				CRHMException TExcept("Fewer soil layers defined than specified in N_Soil_layers.", TERMINATE);
				LogError(TExcept);
			}
		} // for nlay

		TrigAcc[hh] = 0.0;
		TrigState[hh] = 0;
		B[hh] = 0.0;
		Zdf[hh] = 0.0;
		Zdt[hh] = 0.0;
		Bfr[hh] = 0.0;
		Bth[hh] = 0.0;

		if (variation == VARIATION_1)
			n_factor[hh] = 0.0;

	} // for hh
} // init

void ClassXG::run(void) {

	float Za, X, X1;
	float L = 335000;// the latent heat of fusion of ice(J/kg);
	long  nstep = getstep();

	for (hh = 0; chkStruct(); ++hh) {

		if (nstep == 1) {
			const_cast<float *> (depths_lay[N_Soil_layers[hh] - 1])[hh] = 100.0; // ensure stays in last layer. Must be here to be restored
			if (Zdf_init[hh] > 0.0 && Bfr[hh] <= 0.0) // not set by state file
				find_freeze_D(Zdf_init[hh]); // initialises Bfr and Zdf from Zdf_init
			if (Zdt_init[hh] && Zdt_init[hh] < Zpf_init[hh] && Bth[hh] <= 0.0) // not set by state file
				find_thaw_D(Zdt_init[hh]); // initialises Bth and Zdt from Zdt_init
		}


		if (nstep%Global::Freq == 1 || Global::Freq == 1) // end of every day
			B[hh] = 0.0;

		if (variation == VARIATION_ORG)
			B[hh] += hru_tsf[hh] / Global::Freq; // use hru_tsf
		else
			B[hh] += hru_t[hh] / Global::Freq; // use hru_t

		TrigAcc[hh] += B[hh];

		t_trend[hh] -= t_trend[hh] / 192;

		t_trend[hh] += B[hh] / 192;

		if (getstep() % Global::Freq == 0 || Global::Freq == 1) { // end of every day

			if (TrigAcc[hh] > Trigthrhld[hh]) // keep TrigAcc within +- Trigthrhld
				TrigAcc[hh] = Trigthrhld[hh];
			else if (TrigAcc[hh] < -Trigthrhld[hh])
				TrigAcc[hh] = -Trigthrhld[hh];

			// Enter freeze or thaw from idle

			if (TrigAcc[hh] >= Trigthrhld[hh] / 2.0 && TrigState[hh] == 0 && (Zdf[hh] > 0.0 || nfront[hh])) { // thaw
				TrigState[hh] = 1;
				Zd_front_array[1][hh] = -Zdf[hh];
				t_trend[hh] = 0.0;
			} // if

			if (TrigAcc[hh] <= -Trigthrhld[hh] / 2.0 && TrigState[hh] == 0) { // freeze    
				TrigState[hh] = -1;
				Zd_front_array[1][hh] = Zdt[hh];
				t_trend[hh] = 0.0;
			} // if

			  // Goto idle from freeze or thaw

			if (TrigState[hh] == -1 && TrigAcc[hh] >= Trigthrhld[hh] / 2.0 && t_trend[hh] > 0.0) { // changing state from freeze
				TrigState[hh] = 0;

				if (Zdt[hh] > 0.0 && Zdf[hh] > 0.0) {
					if (Zdt[hh] > Zdf[hh]) { // did not reach last thawing front
						push_front(Zdt[hh]);
						Zdt[hh] = 0.0;
						Bth[hh] = 0.0;
						Zd_front_array[0][hh] = 0.0;
						Zd_front_array[1][hh] = -Zdf[hh];
					} // if
				} // if
			} // if

			if (TrigState[hh] == 1 && TrigAcc[hh] <= -Trigthrhld[hh] / 2.0 && t_trend[hh] < 0.0) { // changing state from thaw
				TrigState[hh] = 0;

				if (variation == VARIATION_1)
					n_factor[hh] = 0.0;

				if (Zdf[hh] > 0.0 && Zdt[hh] > 0.0) {
					if (Zdf[hh] > Zdt[hh]) { // did not reach last freezing front
						push_front(-Zdf[hh]); // did not reach last freezing front
						Zdf[hh] = 0.0;
						Bfr[hh] = 0.0;
						Zd_front_array[0][hh] = 0.0;
						Zd_front_array[1][hh] = Zdt[hh];
					}
				}
			}

			// Calculate thermal conductivities

			Th_low_lay[hh] = 1;
			Fz_low_lay[hh] = 1;
			check_XG_moist[hh] = 0.0;

			for (long ll = 0; ll < N_Soil_layers[hh]; ++ll) {
				if (soil_moist_max[hh] > 0.0) // handle soil_moist_max = 0.0, i.e. slough
					XG_moist_lay[ll][hh] = rechr_fract_lay[ll][hh] * XG_max_lay[ll][hh] * soil_rechr[hh] / soil_rechr_max[hh]
					+ moist_fract_lay[ll][hh] * XG_max_lay[ll][hh] * (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
				else
					XG_moist_lay[ll][hh] = 0.0;

				check_XG_moist[hh] += XG_moist_lay[ll][hh];

				XG_moist_lay[ll][hh] += default_fract_lay[ll][hh] * XG_max_lay[ll][hh] * theta_default_lay[ll][hh]; // adjust for below profile theta

				theta_lay[ll][hh] = XG_moist_lay[ll][hh] / XG_max_lay[ll][hh];

				if (theta_lay[ll][hh] <= theta_min[hh]) // do not allow zero values
					theta_lay[ll][hh] = theta_min[hh];

				h2o_lay[ll][hh] = theta_lay[ll][hh] * por_lay[ll][hh] * 1000; // water kg/m3 was water fraction

				if (k_update[hh]) { // change all layers to dynamic
					if (ftc_contents_lay[ll][hh] == 1) // always set somewhere else
						ftc_lay[ll][hh] = get_ttc_lay(ll);
					else
						ftc_lay[ll][hh] = get_ftc_lay(ll);

					if (ttc_contents_lay[ll][hh] == 1) // always set somewhere else
						ttc_lay[ll][hh] = get_ftc_lay(ll);
					else
						ttc_lay[ll][hh] = get_ttc_lay(ll);
				}
				else {
					ftc_lay[ll][hh] = get_ftc_lay(ll);
					ttc_lay[ll][hh] = get_ttc_lay(ll);

					ftc_contents_lay[ll][hh] = 0;
					ttc_contents_lay[ll][hh] = 0;
				}
			} // for layers

			for (long ll = 1; ll < N_Soil_layers[hh]; ++ll) {
				pf_lay[ll][hh] = sqrt(ftc_lay[ll - 1][hh] * h2o_lay[ll][hh] / (ftc_lay[ll][hh] * h2o_lay[ll - 1][hh])); // water kg/m3
				pt_lay[ll][hh] = sqrt(ttc_lay[ll - 1][hh] * h2o_lay[ll][hh] / (ttc_lay[ll][hh] * h2o_lay[ll - 1][hh])); // water kg/m3
			}

			// Execute freeze or thaw

			if (TrigState[hh] < 0.0) { // handle freezing
				Bfr[hh] -= B[hh];  // Calculate the value of Degree-day for every day
				if (Bfr[hh] > 0.0) {
					freeze(); // XG-Algorithm - Freezing
							  // check for thaw front
					if (Zdt[hh] > 0.0 && Zdf[hh] >= Zdt[hh]) {
						if (nfront[hh] > 0) {
							float Last = last_front();
							if (Last < 0.0) { // frozen front
								Zdf[hh] = pop_front();
								find_freeze_D(Zdf[hh]);
								float Last = last_front();
								if (Last > 0.0) { // thaw front
									Zdt[hh] = pop_front();
									find_thaw_D(Zdf[hh]);
									Zd_front_array[1][hh] = Zdt[hh];
								}
								else if (Last < 0.0) { // never two frozen fronts together
									assert(0);
								}
								else { // no thaw front
									Zdt[hh] = 0.0;
									Bth[hh] = 0.0;
									Zd_front_array[1][hh] = 0.0;
								}
							}
							else if (Last < 0.0) { // never two freeze fronts together
								assert(0);
							}
							else { // no thaw layer
								Zdt[hh] = 0.0;
								Bth[hh] = 0.0;
								Zd_front_array[1][hh] = 0.0;
							}
						}
						else { // no fronts
							Zdt[hh] = 0.0;
							Bth[hh] = 0.0;
							Zd_front_array[1][hh] = 0.0;
						}
					}
				}
				Zd_front_array[0][hh] = -Zdf[hh];
			} // freezing handled

			else if (TrigState[hh] > 0.0) { // Surface thawing lower ground frozen

				if (variation == VARIATION_1) {
					if (SWE[hh] > 0.0)
						n_factor_T[hh] = 0.0;
					else
						++n_factor_T[hh];

					n_factor[hh] = n_factor_a[hh] - n_factor_b[hh] * exp(-n_factor_c[hh] * n_factor_T[hh]);
					if (n_factor[hh] >= 0.0)
						B[hh] = B[hh] * n_factor[hh]; // modify
				}

				Bth[hh] += B[hh];  // Calculate the value of Degree-day for every day

				if (Bth[hh] <= 0.0) {
					Bfr[hh] = Bth[hh];
					Zdt[hh] = 0.0;
					Bth[hh] = 0.0;
				}
				else {
					thaw(); // XG-Algorithm - Thawing
							// check for freeze front
					if (Zdf[hh] > 0.0 && Zdt[hh] >= Zdf[hh]) {
						if (nfront[hh] > 0) {
							float Last = last_front();
							if (Last > 0.0) { // thaw front
								Zdt[hh] = pop_front();
								find_thaw_D(Zdt[hh]);
								Last = last_front();
								if (Last < 0.0) { // frozen front
									Zdf[hh] = pop_front();
									find_freeze_D(Zdf[hh]);
									Zd_front_array[1][hh] = -Zdf[hh];
								}
								else if (Last > 0.0) { // never two thaw fronts together
									assert(0);
								}
								else { // no frozen front
									Zdf[hh] = 0.0; // no frozen layers
									Bfr[hh] = 0.0;
									Zd_front_array[1][hh] = 0.0;
								}
							}
							else if (Last < 0.0) { // never two freeze fronts together
								assert(0);
							}
							else { // no thaw layer
								Zdf[hh] = 0.0;
								Bfr[hh] = 0.0;
								Zd_front_array[1][hh] = 0.0;
							}
						}
						else { // no fronts
							Zdf[hh] = 0.0; // no frozen layer
							Bfr[hh] = 0.0;
							Zdt[hh] = 0.0;
							Bth[hh] = 0.0;
							TrigState[hh] = 0;
							Zd_front_array[1][hh] = 0.0;
						}
					} // if
				} // else
				Zd_front_array[0][hh] = Zdt[hh];
			} // thawing handled
		} // end of every day
	} // for hh
}

void ClassXG::freeze(void) { // XG-Algorithm - Freezing

	long lay = 1;
	float Za;
	float L = 335000; // the latent heat of fusion of ice(3.35�105J/kg);

	Zdf[hh] = 0.0;

	float ftc;
	if (k_update[hh] == 2)
		ftc = Interpolated_ftc_lay(Zdf[hh], lay);
	else
		ftc = ftc_lay[lay - 1][hh];

	Za = sqrt(2 * 86400 * ftc*Bfr[hh] / (h2o_lay[lay - 1][hh] * L));


	while (Za > depths_lay[lay - 1][hh] && lay < N_Soil_layers[hh]) {
		Zdf[hh] += depths_lay[lay - 1][hh];

		Za = (Za - depths_lay[lay - 1][hh]) / pf_lay[lay][hh];
		++lay;

		if (k_update[hh] > 0 && freeze_kw_ki_update[hh] && lay > Fz_low_lay[hh]) { // change layer to ki
			ftc_lay[Fz_low_lay[hh] - 1][hh] = get_ttc_lay(Fz_low_lay[hh] - 1);
			ftc_contents_lay[Fz_low_lay[hh] - 1][hh] = 1;
			pf_lay[Fz_low_lay[hh]][hh] = sqrt(ftc_lay[Fz_low_lay[hh] - 1][hh] * h2o_lay[Fz_low_lay[hh]][hh] / (ftc_lay[Fz_low_lay[hh]][hh] * h2o_lay[Fz_low_lay[hh] - 1][hh])); // water kg/m3
			Fz_low_lay[hh] = lay;
			tc_composite_lay[lay - 1][hh] = ftc_lay[lay - 1][hh];
		}
	} // while
	Zdf[hh] += Za;

	if (Zdf[hh] > Zpf_init[hh])
		Zdf[hh] = Zpf_init[hh]; // limit to less than permafrost depth
}

void ClassXG::thaw(void) { // XG-Algorithm - Thawing

	long lay = 1;
	float Za;
	float L = 335000;// the latent heat of fusion of ice(3.35�105J/kg);

	Zdt[hh] = 0.0;

	float ttc;
	if (k_update[hh] == 2)
		ttc = Interpolated_ttc_lay(Zdf[hh], lay);
	else
		ttc = ttc_lay[lay - 1][hh];

	Za = sqrt(2 * 86400 * ttc*Bth[hh] / (h2o_lay[lay - 1][hh] * L)); //Stefan Equation

	while (Za > depths_lay[lay - 1][hh] && lay < N_Soil_layers[hh]) {
		Zdt[hh] += depths_lay[lay - 1][hh];

		Za = (Za - depths_lay[lay - 1][hh]) / pt_lay[lay][hh];
		++lay;

		if (k_update[hh] > 0 && thaw_ki_kw_update[hh] && lay > Th_low_lay[hh]) { // change layer to kw
			ttc_lay[Th_low_lay[hh] - 1][hh] = get_ftc_lay(Th_low_lay[hh] - 1);
			ttc_contents_lay[Th_low_lay[hh] - 1][hh] = 1;
			pt_lay[Th_low_lay[hh]][hh] = sqrt(ttc_lay[Th_low_lay[hh] - 1][hh] * h2o_lay[Th_low_lay[hh]][hh] /
				(ttc_lay[Th_low_lay[hh]][hh] * h2o_lay[Th_low_lay[hh] - 1][hh]));
			Th_low_lay[hh] = lay;
			tc_composite_lay[lay - 1][hh] = ttc_lay[lay - 1][hh];
		}
	} // while
	Zdt[hh] += Za;

	if (Zdt[hh] > Zpf_init[hh])
		Zdt[hh] = Zpf_init[hh];
}

float ClassXG::Interpolated_ttc_lay(float Za, long lay) { //

	if (!thaw_ki_kw_update[hh])
		return (ttc_lay[lay - 1][hh]);

	float split = (Za - Zdt[hh]) / depths_lay[lay - 1][hh];
	if (split >= 1.0)
		split = 1.0;

	float combination = ttc_lay[lay - 1][hh] - split * (ttc_lay[lay - 1][hh] - ftc_lay[lay - 1][hh]); // thawed(18k) to frozen (4k)

	tc_composite2_lay[lay - 1][hh] = combination;

	return (combination);
}

float ClassXG::Interpolated_ftc_lay(float Za, long lay) { //

	if (!freeze_kw_ki_update[hh])
		return (ftc_lay[lay - 1][hh]);

	float split = (Za - Zdf[hh]) / depths_lay[lay - 1][hh];
	if (split >= 1.0)
		split = 1.0;

	float combination = ftc_lay[lay - 1][hh] + split * (ttc_lay[lay - 1][hh] - ftc_lay[lay - 1][hh]); // frozen (4k) to thawed(18k)

	tc_composite2_lay[lay - 1][hh] = combination;

	return (combination);
}

void ClassXG::find_thaw_D(float dt) { // XG-Algorithm - Thawing - used by init
									  // solve for Bth from Zdt using Bisection method

	if (dt == 0)
		return;

	for (long B = 1; B < 50000; ++B) {
		Bth[hh] = B;
		thaw();
		if (Zdt[hh] > dt || Zdt[hh] >= Zpf_init[hh])
			return;
	}

 string S = string("'") + Name + " (XG)' Zdt too large in hru = " + std::to_string(hh + 1).c_str();
	CRHMException TExcept(S.c_str(), TERMINATE);
	LogError(TExcept);
	throw TExcept;
}


void ClassXG::find_freeze_D(float df) { // XG-Algorithm - Thawing - used by init
										// solve for Bfr from Zdt using Bisection method

	if (df == 0)
		return;

	for (long B = 1; B < 50000; ++B) {
		Bfr[hh] = B;
		freeze();
		if (Zdf[hh] > df || Zdf[hh] >= Zpf_init[hh])
			return;
	}

 string S = string("'") + Name + " (XG)' Zdf too large in hru = " + std::to_string(hh + 1).c_str();
	CRHMException TExcept(S.c_str(), TERMINATE);
	LogError(TExcept);
	throw TExcept;
}

void ClassXG::push_front(float D) {

	if (nfront[hh] >= front_size - 3) { // space to allocate plus Zdf/Zdt(2 slots) plus top of stack indicator
	 string S = string("'") + Name + " (XG)' too many fronts in hru = " + std::to_string(hh + 1).c_str();
		CRHMException TExcept(S.c_str(), TERMINATE);
		LogError(TExcept);
		throw TExcept;
	}

	for (long ii = nfront[hh] + 1; 2 <= ii; --ii) // move contents up
		Zd_front_array[ii + 1][hh] = Zd_front_array[ii][hh];

	++nfront[hh];
	Zd_front_array[2][hh] = D; // add new entry
}

float ClassXG::pop_front(void) {

	float D = fabs(Zd_front_array[2][hh]); // always positive

	for (long ii = 2; ii < nfront[hh] + 1; ++ii) // move contents down
		Zd_front_array[ii][hh] = Zd_front_array[ii + 1][hh];

	Zd_front_array[nfront[hh] + 1][hh] = 0.0; // clear memory

	--nfront[hh];

	return D;
}

float ClassXG::last_front(void) {

	if (!nfront[hh])
		return 0.0;
	else
		return (Zd_front_array[2][hh]);
}

/*float ClassXG::SWE_to_rho(float SWE) { // Pomeroy et al (1998)

// solve for desity from SWE using Bisection method

float h1 = 0.6, h2 = 8.00, e, h, rho;
long iter_max = 0;
do {
h = (h1 + h2)/2.0; // m
rho = (450.0 - 204.7/h*(1.0 - exp(-h/0.673)));
e = rho*h - SWE; // original equation was cm
if(e < 0)
h1 += (h2 - h1)/2.0;
else
h2 -= (h2 - h1)/2.0;

} while(fabs(e) > 0.001 && h > 0.601 && ++iter_max < 100); // below 60cm the density is 250 kg/m3

return rho;
}*/

void ClassXG::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (XG)'  Zdt     (mm): ").c_str(), Zdt[hh]);
		LogMessageA(hh, string("'" + Name + " (XG)'  Zdf     (mm): ").c_str(), Zdf[hh]);
		LogMessageA(hh, string("'" + Name + " (XG)'  nfront  ()  : ").c_str(), nfront[hh]);
	}
	LogDebug(" ");
}

float ClassXG::get_ftc_lay(long lay) { // unfrozen(thawed) soil to be frozen
	if (calc_coductivity[hh]) {
		return (soil_solid_km_ki_lay[lay][hh] - soil_solid_km_lay[lay][hh])*sqr(h2o_lay[lay][hh] / (1000.0*por_lay[lay][hh])) + soil_solid_km_lay[lay][hh];
	}
	else
		return (1.0 - por_lay[lay][hh])*soil_solid_km_lay[lay][hh] + h2o_lay[lay][hh] / 1000.0*kw + (por_lay[lay][hh] - h2o_lay[lay][hh] / 1000.0)*ka;
}

float ClassXG::get_ttc_lay(long lay) { // frozen soil to be unfrozen(thawed)
	if (calc_coductivity[hh]) {
		return  soil_solid_km_lay[lay][hh] * pow(soil_solid_km_ki_lay[lay][hh] / soil_solid_km_lay[lay][hh], h2o_lay[lay][hh] / (1000.0*por_lay[lay][hh]));
	}
	else
		return (1.0 - por_lay[lay][hh])*soil_solid_km_lay[lay][hh] + h2o_lay[lay][hh] / 1000.0*ki + (por_lay[lay][hh] - h2o_lay[lay][hh] / 1000.0)*ka;
}


Classcontribution* Classcontribution::klone(string name) const {
	return new Classcontribution(name);
}

void Classcontribution::decl(void) {

	Description = "'calculates contributing area.'";

	declvar("contrib_area", NHRU, "contributing area", "(mm^2)", &contrib_area);

	declvar("pre_contrib_area", NHRU, "maximum contributing area of HRU before transfer", "(mm^2)", &pre_contrib_area);

	declvar("connected", NHRU, "connected HRUs", "()", &connected);

	declvar("N_connected", NHRU, "number of connected HRUs", "()", &N_connected);

	declvar("connectedTo", NHRU, "connected HRUs", "()", &connectedTo);

	declvar("Results", NDEFN, "calulated distributions", "()", &Results, &Results_lay, nhru);

	decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);



	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

	declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);


	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

	declgetvar("*", "Sd", "(mm)", &Sd);

}

void Classcontribution::init(void) {

	if (soil_runoffDiv > 1) {
	 string S = "Netroute:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	nhru = getdim(NHRU);
	for (hh = 0; hh < nhru; ++hh) {
		contrib_area[hh] = 0.0;
		pre_contrib_area[hh] = 0.0;
	}
}

void Classcontribution::run(void) {

	long  nstep = getstep() % Global::Freq;

	if (getstep() == 1) {
		for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
			distrib_sum[hh] = 0.0;

			for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
				if (distrib_hru[hh][hhh] < 0.0)
					const_cast<float **> (distrib_hru)[hh][hhh] = -distrib_hru[hh][hhh] * hru_area[hh];
				distrib_sum[hh] += distrib_hru[hh][hhh];
			}

			if (distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0) {
				const_cast<float *> (distrib_Basin)[hh] = 1;
			}

			distrib_sum[hh] += distrib_Basin[hh];

		}
	}

	for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		contrib_area[hh] = hru_area[hh]; // assign values
		pre_contrib_area[hh] = 0.0; // reset
		connected[hh] = 0.0; // clear values
		N_connected[hh] = 0; // clear values
		connectedTo[hh] = 0; // clear values
		for (long hhh = 0; chkStruct(hhh); ++hhh)
			Results_lay[hhh][hh] = 0.0;
	} // hh

	for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
		for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
			if ((Sd[hh] >= Sdmax[hh] || soil_runoff_Buf[hh] > 0.0) && distrib_hru[hh][hhh] > 0.0) {  //
				Results_lay[hhh][hh] = distrib_hru[hh][hhh] - 1; // parameter value used as index
				connected[hh] += distrib_hru[hh][hhh]; // parameter value only
				connectedTo[hh] = hhh;
			}
		} // hhh
	} // hh

	for (long hh = 6; chkStruct(hh); ++hh) {
		if (connected[hh]) {
			pre_contrib_area[hh] = contrib_area[hh];
			contrib_area[connectedTo[hh]] += contrib_area[hh];
			contrib_area[hh] = 0.0;
			++N_connected[connectedTo[hh]];
			++N_connected[nhru - 1];
		}
	} // hh

	float sum2 = 0;
	for (long hh = 6; chkStruct(hh); ++hh) {
		sum2 += contrib_area[hh];
	} // hh

	if (nstep == 0) { // end of every day
		for (hh = 0; chkStruct(); ++hh) {
			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;
		}
	}
}


void Classcontribution::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (intcp)'  contrib_area  (mm) (mm*hru) (mm*hru/basin): ").c_str(), contrib_area[hh], hru_area[hh], basin_area[0]);
	}
	LogDebug(" ");
}

ClassSoilX* ClassSoilX::klone(string name) const {
	return new ClassSoilX(name);
}

void ClassSoilX::decl(void) {

	Description = "'Handles soil moisture throughout the year. Expanded to handle frost depth and detention layer.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'";

	variation_set = VARIATION_1;

	depths_size = 2; // handles recharge and lower layers

	declvar("culvert_Q", NHRU, "flow in culvert.", "(m^3/s)", &culvert_Q);

	declvar("culvert_water_H", NHRU, "depth of pond at culvert inlet.", "(m)", &culvert_water_H);

	declvar("culvert_water_A", NHRU, "surface area of culvert pond.", "(m^2)", &culvert_water_A);

	declvar("culvert_water_V", NHRU, "volume of water in culvert pond.", "(m^3)", &culvert_water_V);

	declvar("culvert_over_Q", NHRU, "flow over the road.", "(m^3/s)", &culvert_over_Q);

	declvar("culvert_evap", NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

	declstatdiag("cum_culvert", NHRU, "Cumulative culvert HRU flow.", "(m^3)", &cum_culvert);

	declstatdiag("cum_culvert_over", NHRU, "Cumulative culvert HRU overflow.", "(m^3)", &cum_culvert_over);

	decldiag("HD", NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", &HD);

	declparam("channel_slope", NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

	declparam("side_slope", NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

	declparam("culvert_diam", NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

	declparam("culvert_water_Dmax", NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

	declparam("number_culverts", NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

	declparam("culvert_type", NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


	variation_set = VARIATION_ORG;

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

	declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

	declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

	declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

	declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
		"portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

	declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

	decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

	decllocal("Dts_runoff_K", NHRU, "daily detention storage runoff drainage factor. Values from parameters Dts_snow_runoff_K or Dts_organic_runoff_K determined from snowcover", "mm/d", &Dts_runoff_K);

	declvar("depth_layers", NDEFN, "thickness of soil layer.", "(m)", &depth_layers, &depth_layers_lay, depths_size);

	declvar("thaw_layers", NDEFN, "fraction of layer thawed.", "()", &thaw_layers, &thaw_layers_lay, depths_size);

	declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

	declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

	declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

	declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

	declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

	declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

	declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

	declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

	declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

	declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

	declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

	declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

	declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

	declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

	declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

	declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

	declstatdiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

	declstatdiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);


	decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

	decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

	decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

	decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

	decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

	decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

	decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

	decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

	declparam("Sdinit", NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
		"Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

	declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
		"that is routed directly to the associated groundwater reservoir each day. Modified by thaw_upper.", "(mm/d)", &soil_gw_K);

	declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

	declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

	declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

	declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge. Modified by thaw_upper.", "(mm/d)", &rechr_ssr_K);

	declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column. Modified by thaw_lower.", "(mm/d)", &lower_ssr_K);

	declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor. Modified by thaw_all.", "(mm/d)", &Sd_ssr_K);

	declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

	declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
		"Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
		&soil_withdrawal, &soil_withdrawal_Tables, 2);

	declparam("cov_type", NHRU,
		"[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
		"0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

	declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

	declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

	declparam("porosity_upper", NHRU, "[0.5]", "0.0", "1.0", "upper soil porosity (recharge layer).", "(m^3/m^3)", &porosity_upper);

	declparam("porosity_lower", NHRU, "[0.5]", "0.0", "1.0", "lower soil porosity.", "(m^3/m^3)", &porosity_lower);

	declparam("evap_from_runoff", NHRU, "[0]", "0", "1", "when equal to 1, allow evaporation from runoff.", "()", &evap_from_runoff);

	declparam("NO_Freeze", NHRU, "[0]", "0", "1", "when equal to 1, keeps soil from freezing.", "()", &NO_Freeze);

	declgetparam("*", "inhibit_evap", "()", &inhibit_evap); // used since no declgetparam defined


	declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

	declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


	declgetvar("*", "Zdt", "(m)", &Zdt);

	declgetvar("*", "Zdf", "(m)", &Zdf);

	declgetvar("*", "Zd_front", "(m)", &Zd_front, &Zd_front_array);

	evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);


	declgetvar("*", "infil", "(mm/int)", &infil);

	snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

	runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

	meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);

	declparam("Dts_snow_max", NHRU, "[0]", "0.0", "5000.0", "Maximum detention storage in snowcover period.", "(mm)", &Dts_snow_max);

	declparam("Dts_organic_max", NHRU, "[0]", "0.0", "5000.0", "Maximum detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_max);

	declparam("Dts_snow_init", NHRU, "[0]", "0.0", "5000.0", "Initial detention storage in snowcover period.", "(mm)", &Dts_snow_init);

	declparam("Dts_snow_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of snow runoff drainage factor.", "(mm/d)", &Dts_snow_runoff_K);

	declparam("Dts_organic_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of organic layer runoff drainage factor.", "(mm/d)", &Dts_organic_runoff_K);

	declparam("Dts_organic_init", NHRU, "[0]", "0.0", "5000.0", "Initial detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_init);

	declvar("Dts", NHRU, "Detention storage.", "(mm)", &Dts);

	declvar("Dts_max", NHRU, "Maximum detention storage.", "(mm)", &Dts_max);
}

void ClassSoilX::init(void) {

	nhru = getdim(NHRU);
	nlay = getdim(NLAY);

	if (nlay < 2) {
	 string S = string("'") + Name + " (SoilX)' project file nlay(number of layers) must be greater 2 or greater";
		CRHMException TExcept(S.c_str(), TERMINATE);
		LogError(TExcept);
		throw TExcept;
	}

	if (snowinfilDiv > 1) {
	 string S = "Soil:  \"snowinfil\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (evapDiv > 1) {
	 string S = "Soil:  \"hru_evap\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (meltrunoffDiv > 1) {
	 string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (runoffDiv > 1) {
	 string S = "Netroute:  \"runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {

		if (soil_moist[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}

		if (soil_rechr[hh] > soil_rechr_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}
		if (soil_rechr_max[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
			throw TExcept;
		}

		if (Sdinit[hh] > Sdmax[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (gw_init[hh] > gw_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		soil_rechr[hh] = soil_rechr_init[hh];
		soil_moist[hh] = soil_moist_init[hh];

		redirected_residual[hh] = 0.0;
		cum_redirected_residual[hh] = 0.0;

		Sd[hh] = Sdinit[hh];

		gw[hh] = gw_init[hh];

		hru_cum_actet[hh] = 0.0;
		cum_hru_condense[hh] = 0.0;
		cum_infil_act[hh] = 0.0;

		soil_runoff_D[hh] = 0.0;
		soil_ssr_D[hh] = 0.0;
		soil_gw_D[hh] = 0.0;
		gw_flow_D[hh] = 0.0;
		infil_act[hh] = 0.0;
		infil_act_D[hh] = 0.0;

		cum_soil_runoff[hh] = 0.0;
		cum_soil_ssr[hh] = 0.0;
		cum_rechr_ssr[hh] = 0.0;
		cum_soil_gw[hh] = 0.0;
		cum_gw_flow[hh] = 0.0;

		cum_runoff_to_Sd[hh] = 0.0;

		if (inhibit_evap[hh] == 1) {  // when snowcover
			Dts_max[hh] = Dts_snow_max[hh];
			Dts[hh] = Dts_snow_init[hh];
		}
		else if (inhibit_evap[hh] == 0) {  // when no snowcover
			Dts_max[hh] = Dts_organic_max[hh];
			Dts[hh] = Dts_organic_init[hh];
		}

		depth_layers_lay[0][hh] = soil_rechr_max[hh] / porosity_upper[hh] / 1000.0;
		depth_layers_lay[1][hh] = (soil_moist_max[hh] - soil_rechr_max[hh]) / porosity_lower[hh] / 1000.0;

		thaw_layers_lay[0][hh] = 1.0; // unfrozen
		thaw_layers_lay[1][hh] = 1.0; // unfrozen

		if (variation == VARIATION_1) {
			if (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) {
			 string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + std::to_string(hh + 1);
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}
			culvert_water_V[hh] = 0.0;
			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;
			cum_culvert[hh] = 0.0;
			cum_culvert_over[hh] = 0.0;
		}
	}
}

void ClassSoilX::run(void) {

	float soil_lower, excs, condense, Dss;
	float et;
	float runoff_to_Sd = 0.0;

	long nstep = getstep();

	if (nstep == 1)
		for (hh = 0; chkStruct(); ++hh) {
			LogMessageA(hh, string("'" + Name + " (SoilX)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilX)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilX)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilX)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
			soil_moist_Init[hh] = soil_moist[hh];
			soil_rechr_Init[hh] = soil_rechr[hh];
			Sd_Init[hh] = Sd[hh];
			gw_Init[hh] = gw[hh];
		}

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (snowinfilDiv == 1) // interval value
			snowinfil_buf[hh] = snowinfil[hh];

		if (runoffDiv == 1) // interval value
			runoff_buf[hh] = runoff[hh];

		if (meltrunoffDiv == 1) // interval value
			meltrunoff_buf[hh] = meltrunoff[hh];

		if (evapDiv == 1) // interval value
			hru_evap_buf[hh] = hru_evap[hh];

		if (nstep == 0) {

			for (long ll = 0; ll < depths_size; ++ll)
				if (NO_Freeze[hh])
					thaw_layers_lay[ll][hh] = 1.0; // all unfrozen
				else
					thaw_layers_lay[ll][hh] = 0.0; // all frozen

			if (soil_moist_max[hh] > 0.0 && !NO_Freeze[hh] && Zd_front_array[0][hh] > 0.0) {

				float layer_start = 0.0; // start of current layer
				float layer_end = 0.0; // end of current layer
				long ll = 0;

				while (ll < depths_size && Zdt[hh] > 0.0) {
					layer_end += depth_layers_lay[ll][hh];
					if (Zdt[hh] >= layer_end) { // frozen to bottom of layer
						thaw_layers_lay[ll][hh] = 1.0; // all unfrozen
						layer_start = layer_end;
						++ll;
					}
					else { // no
						if (Zdt[hh] >= layer_start && Zdt[hh] < layer_end) { // in layer ?
							thaw_layers_lay[ll][hh] = (Zdt[hh] - layer_start) / depth_layers_lay[ll][hh];
							++ll;
							break;
						}
					} // else
				} // while ll
			}
		} // finished daily upgrade

		if (nstep == 1) { // beginning of every day
			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;
			infil_act_D[hh] = 0.0;
		}

		hru_actet[hh] = 0.0;
		infil_act[hh] = 0.0;
		soil_gw[hh] = 0.0;
		soil_ssr[hh] = 0.0;
		rechr_ssr[hh] = 0.0;
		soil_runoff[hh] = 0.0;

		if (hru_evap_buf[hh] < 0.0) {
			condense = -hru_evap_buf[hh];
			cum_hru_condense[hh] += condense;
			hru_evap_buf[hh] = 0.0;
		}
		else
			condense = 0.0;

		//******Add infiltration to soil and compute excess

		if (soil_moist_max[hh] > 0.0) {
			soil_lower = soil_moist[hh] - soil_rechr[hh];

			float potential = infil[hh] + snowinfil_buf[hh] + condense;

			float possible = thaw_layers_lay[0][hh] * (soil_rechr_max[hh] - soil_rechr[hh]);

			if (possible > potential || NO_Freeze[hh])
				possible = potential;
			else
				soil_runoff[hh] = potential - possible;

			soil_rechr[hh] = soil_rechr[hh] + possible; // infiltrates into entire upper layer

			if (soil_rechr[hh] > soil_rechr_max[hh]) {
				excs = soil_rechr[hh] - soil_rechr_max[hh];
				soil_rechr[hh] = soil_rechr_max[hh];
				soil_lower = soil_lower + excs;
			}

			soil_moist[hh] = soil_lower + soil_rechr[hh];

			if (soil_moist[hh] > soil_moist_max[hh]) {
				excs = soil_moist[hh] - soil_moist_max[hh];
				soil_moist[hh] = soil_moist_max[hh];
			}
			else
				excs = 0.0;

			infil_act[hh] = possible - excs;
			cum_infil_act[hh] += infil_act[hh];
			infil_act_D[hh] += infil_act[hh];

			//  Handle subsurface runoff

			if (!inhibit_evap[hh]) { // only when no snowcover
				rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq*thaw_layers_lay[0][hh]; // regulate by amount unfrozen
				if (rechr_ssr[hh] > soil_rechr[hh] * thaw_layers_lay[0][hh])
					rechr_ssr[hh] = soil_rechr[hh] * thaw_layers_lay[0][hh];

				soil_rechr[hh] -= rechr_ssr[hh];
				if (soil_rechr[hh] < 0.0)
					soil_rechr[hh] = 0.0;

				soil_moist[hh] -= rechr_ssr[hh];
				soil_ssr[hh] = rechr_ssr[hh];
				cum_rechr_ssr[hh] += rechr_ssr[hh];
			}

			float s2gw_k = soil_gw_K[hh] / Global::Freq*thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer

																				//  Handle excess to gw
			if (excs > 0.0 && s2gw_k > 0.0) {
				if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
					soil_gw[hh] = s2gw_k;
					excs -= s2gw_k;
				}
				else { // to gw
					soil_gw[hh] = excs;
					excs = 0.0;
				}
			}

			//  Handle excess to interflow or runoff

			if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow regulated by amount of unfrozen upper layer
				soil_ssr[hh] += excs * thaw_layers_lay[1][hh];
				excs = excs * (1.0 - thaw_layers_lay[1][hh]);
			}
		}
		else { // soil_moist_max <= 0.0, i.e. Pond
			excs = infil[hh] + snowinfil_buf[hh] + condense;
		}

		float runoff_to_Sd = 0.0;

		soil_runoff[hh] += (meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh] / hru_area[hh]); // last term (mm*km^2/int)

		cum_redirected_residual[hh] += redirected_residual[hh];

		redirected_residual[hh] = 0;

		if (soil_runoff[hh] > 0.0 && Dts_max[hh] > 0.0) {

			if (inhibit_evap[hh] == 1) // when snowcover
				Dts_max[hh] = Dts_snow_max[hh];

			else if (inhibit_evap[hh] == 0) // when no snowcover
				Dts_max[hh] = Dts_organic_max[hh];

			Dss = Dts_max[hh] - Dts[hh];

			if (Dss > 0.0) {
				if (soil_runoff[hh] > Dss) {
					soil_runoff[hh] -= Dss;
					if (soil_runoff[hh] < 0.0)
						soil_runoff[hh] = 0.0;
					Dts[hh] += Dss;
				}
				else {
					Dts[hh] += soil_runoff[hh];
					soil_runoff[hh] = 0.0;
				}
			}
		}

		// lateral drainage of detention storage to soil_runoff

		if (inhibit_evap[hh] == 1)  // when snowcover
			Dts_runoff_K[hh] = Dts_snow_runoff_K[hh];
		if (inhibit_evap[hh] == 0)  // when no snowcover
			Dts_runoff_K[hh] = Dts_organic_runoff_K[hh];

		if (Dts[hh] > 0.0 && Dts_runoff_K[hh] > 0.0) {
			float Dss2runoff_k = Dts_runoff_K[hh] / Global::Freq;
			if (Dss2runoff_k >= Dts[hh])
				Dss2runoff_k = Dts[hh];
			soil_runoff[hh] += Dss2runoff_k;
			Dts[hh] -= Dss2runoff_k;
		}

		if (Dts[hh] < 0.0001)
			Dts[hh] = 0.0;

		if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
			float Fix = -12.0;
			if (soil_runoff[hh] / Sdmax[hh] < 12.0)
				Fix = -soil_runoff[hh] / Sdmax[hh];
			Dss = (Sdmax[hh] - Sd[hh])*(1 - exp(Fix));

			if (soil_moist_max[hh] <= 0.0) // handle pond
				Dss = Sdmax[hh] - Sd[hh];

			if (Dss > 0.0) {
				if (soil_runoff[hh] > Dss) {
					soil_runoff[hh] -= Dss;
					if (soil_runoff[hh] < 0.0)
						soil_runoff[hh] = 0.0;
					Sd[hh] += Dss;
					runoff_to_Sd += Dss;
				}
				else {
					Sd[hh] += soil_runoff[hh];
					runoff_to_Sd += soil_runoff[hh];
					soil_runoff[hh] = 0.0;
				}
			}
		}

		if (variation == VARIATION_1) {

			float culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;

			if ((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
				culvert_water_V[hh] += soil_runoff[hh] * (hru_area[hh] * 1000.0); // convert mm to m3
				soil_runoff[hh] = 0.0;

				culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

				if (culvert_water_H[hh] > 0.0) {

					// calculate overflow if culvert level exceeds Dmax

					culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

					if (culvert_water_H[hh] > culvert_water_Dmax[hh]) { // (m) overflow over road
						culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
						float maxVol = pow(culvert_water_Dmax[hh], 3.0) / (3.0*channel_slope[hh] * side_slope[hh]); // (m3)

						culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400.0*Global::Freq; // (m3) to (m3/int)
						culvert_water_V[hh] = maxVol; // (m3)

						cum_culvert_over[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
						soil_runoff[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
					}
					HD[hh] = culvert_water_H[hh] / culvert_diam[hh];

					// calculate flow through culvert

					if (HD[hh] <= 0.0)
						culvert_Q[hh] = 0.0;
					else if (HD[hh] < 1.5)
						culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
							+ 0.159413*HD[hh] + 0.00772254)*culvert_C[culvert_type[hh]] * number_culverts[hh] * pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
					else
						culvert_Q[hh] = culvert_C[culvert_type[hh]] * number_culverts[hh] * 0.785*pow(culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

					if (culvert_water_V[hh] > culvert_Q[hh] * 86400.0 / Global::Freq) // (m3/s) to (m3))
						culvert_water_V[hh] -= culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
					else {
						culvert_Q[hh] = culvert_water_V[hh] * Global::Freq / 86400.0;  // (m3) to (m3/s)
						culvert_water_V[hh] = 0.0;
					}

					cum_culvert[hh] += culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3/int)
					soil_runoff[hh] += culvert_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
				}
				culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (channel_slope[hh] * side_slope[hh]); // used for evaporation
			} // culvert addition
		}

		soil_runoff_D[hh] += soil_runoff[hh];
		cum_soil_runoff[hh] += soil_runoff[hh];
		cum_runoff_to_Sd[hh] += runoff_to_Sd;

		if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
			float Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
			if (Sd2gw_k > Sd[hh])
				Sd2gw_k = Sd[hh];
			soil_gw[hh] += Sd2gw_k;
			Sd[hh] -= Sd2gw_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		soil_gw_D[hh] += soil_gw[hh];
		cum_soil_gw[hh] += soil_gw[hh];

		gw[hh] += soil_gw[hh];
		gw_flow[hh] = 0.0;
		if (gw[hh] > gw_max[hh]) {
			gw_flow[hh] += (gw[hh] - gw_max[hh]);
			gw[hh] = gw_max[hh];
		}

		if (gw_max[hh] > 0.0) { // prevents divide by zero error
			float spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
			gw[hh] -= spill;
			gw_flow[hh] += spill;
		}

		gw_flow_D[hh] += gw_flow[hh];
		cum_gw_flow[hh] += gw_flow[hh];

		if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
			float Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
			if (Sd2ssr_k >= Sd[hh])
				Sd2ssr_k = Sd[hh];
			soil_ssr[hh] += Sd2ssr_k;
			Sd[hh] -= Sd2ssr_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		if (lower_ssr_K[hh] > 0.0) {
			float s2ssr_k = lower_ssr_K[hh] / Global::Freq*thaw_layers_lay[1][hh]; // regulate by amount of unfrozen lower layer
			float avail = soil_moist[hh] - soil_rechr[hh];
			if (s2ssr_k >= avail)
				s2ssr_k = avail;
			soil_moist[hh] -= s2ssr_k;
			soil_ssr[hh] += s2ssr_k;
		}

		cum_soil_ssr[hh] += soil_ssr[hh];
		soil_ssr_D[hh] += soil_ssr[hh];

		//******Compute actual evapotranspiration

		float culvert_pond = 0.0; // convert m3 to mm

		float culvert_evapL = 0;

		if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation
			culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
			culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

			if (culvert_evapL > culvert_pond) // limit to amount available
				culvert_evapL = culvert_pond;

			culvert_evap[hh] = culvert_evapL;
			hru_actet[hh] += culvert_evapL;
			culvert_water_V[hh] = (culvert_pond - culvert_evapL)*(hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
		}

		float avail_evap = hru_evap_buf[hh] - culvert_evapL;
		if (Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
			avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
		else
			avail_evap = 0.0;

		if (Sd[hh] > 0.0 && avail_evap > 0.0) {
			if (Sd[hh] >= avail_evap) {
				Sd[hh] -= avail_evap;
				if (Sd[hh] < 0.0)
					Sd[hh] = 0.0;
			}
			else {
				avail_evap = Sd[hh];
				Sd[hh] = 0.0;
			}
			hru_actet[hh] += avail_evap;
		}
		else
			avail_evap = 0.0;

		avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

		if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

			float pctl, pctr, etl, ets, etr;

			if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
				pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				pctl = 0.0;

			pctr = soil_rechr[hh] / soil_rechr_max[hh];

			etr = avail_evap; // default

			switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
			case 1: //******sandy soil
				if (pctr < 0.25)
					etr = 0.5*pctr*avail_evap;
				break;
			case 2: //******loam soil
				if (pctr < 0.5)
					etr = pctr * avail_evap;
				break;
			case 3: //******clay soil
				if (pctr <= 0.33)
					etr = 0.5*pctr*avail_evap;
				else if (pctr < 0.67)
					etr = pctr * avail_evap;
				break;
			case 4: //******organic soil
					//         use default above etr = avail_evap;
				break;
			} // recharge switch

			if (etr > avail_evap) {
				etl = 0.0; // default value
				etr = avail_evap;
			}
			else
				etl = avail_evap - etr; // default value

			switch (soil_withdrawal_Tables[1][hh]) {  // handle lower layer
			case 1: //******sandy soil
				if (pctl < 0.25)
					etl = 0.5*pctl*etl;
				break;
			case 2: //******loam soil
				if (pctl < 0.5)
					etl = pctl * etl;
				break;
			case 3: //******clay soil
				if (pctl <= 0.33)
					etl = 0.5*pctl*etl;
				else if (pctr < 0.67)
					etl = pctl * etl;
				break;
			case 4: //******organic soil
					//         use default above etl = avail_evap - etr;
				break;
			} // lower switch

			  //******Soil moisture accounting  Remember that soil_moist includes soil_rechr[hh][hh]

			long et_type = cov_type[hh];

			//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
			//****** et_type = 1 - recharge layer only, crops - cov_type = 1
			//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

			if (transp_limited[hh] == 1 && et_type == 2)
				et_type = 1;

			et = 0.0;

			switch (et_type) {  // handle evaporation
			case 0:   // avail_evap <= 0
				break;
			case -1:  // avail_evap <= 0
				break;
			case 1:
				if (etr > soil_rechr[hh]) {
					soil_rechr[hh] = 0.0;
					et = soil_rechr[hh];
				}
				else {
					soil_rechr[hh] = soil_rechr[hh] - etr;
					et = etr;
				}
				soil_moist[hh] = soil_moist[hh] - et;
				break;
			case 2:
				if (etr + etl >= soil_moist[hh]) {
					et = soil_moist[hh];
					soil_moist[hh] = 0.0;
					soil_rechr[hh] = 0.0;
				}
				else {
					et = etr + etl;
					soil_moist[hh] = soil_moist[hh] - et;

					if (etr > soil_rechr[hh]) {
						soil_rechr[hh] = 0.0;
					}
					else
						soil_rechr[hh] = soil_rechr[hh] - etr;
				}
				break;
			} // switch

			hru_actet[hh] += et;

		} // soil_moist[hh] > 0.0

		if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
			hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

		hru_cum_actet[hh] += hru_actet[hh];

		if (nstep == 0) { // end of every day
			if (snowinfilDiv > 1) // daily value - ready for next day
				snowinfil_buf[hh] = snowinfil[hh] / snowinfilDiv;

			if (runoffDiv > 1) // daily value - ready for next day
				runoff_buf[hh] = runoff[hh] / runoffDiv;

			if (meltrunoffDiv > 1) // daily value - ready for next day
				meltrunoff_buf[hh] = meltrunoff[hh] / meltrunoffDiv;

			if (evapDiv > 1) // daily value - ready for next day
				hru_evap_buf[hh] = hru_evap[hh] / evapDiv;
		}
	} // for
}

void ClassSoilX::finish(bool good) {

	float Allcum_soil_runoff = 0.0;
	float Allcum_soil_ssr = 0.0;
	float Allcum_rechr_ssr = 0.0;
	float Allcum_soil_gw = 0.0;
	float Allcum_gw_flow = 0.0;
	float Allcum_infil_act = 0.0;
	float Allcum_soil_moist_change = 0.0;
	float Allcum_Sd_change = 0.0;
	float Allcum_gw_change = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (SoilX)' soil_rechr        (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilX)' soil_rechr_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilX)' soil_moist        (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' soil_moist_change (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' hru_cum_actet     (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_hru_condense  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_hru_condense[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_infil_act(all)(mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_soil_gw       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_soil_runoff   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_rechr_ssr     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_soil_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' Sd                (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' Sd_change         (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_runoff_to_Sd  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' gw                (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' gw_change         (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_gw_flow       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (SoilX)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU runoff");
		LogDebug(" ");

		if (variation == VARIATION_1) {
			LogMessageA(hh, string("'" + Name + " (SoilX)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilX)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
		}
		LogDebug(" ");

		Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
		Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
		Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
		Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
		Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
		Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
		Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
		Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
		Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];
		LogDebug(" ");
	}

	LogMessage(string("'" + Name + " (SoilX)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_soil_gw(mm*basin): ").c_str(), Allcum_soil_gw);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
	LogMessage(string("'" + Name + " (SoilX)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
	LogDebug(" ");
}

ClassMod_Exec* ClassMod_Exec::klone(string name) const {
	return new ClassMod_Exec(name);
}

void ClassMod_Exec::decl(void) {

	Description = "'Link variables and parameters to routines in external DLL.'";

	declvar("statusInit", ONE, "status of variables", "()", &statusInit);

	declvar("statusStep", ONE, "status of time step", "()", &statusStep);

	declvar("Dummy", NHRU, "non constant", "()", &Dummy);

	declvar("Dummy2", NHRU, "constant", "()", &Dummy2);

	DLL_name = declparam("DLL_name", ONE, " ", "DLL name, e.g. 'C:/Jose/Borland/Jose1.dll' ", DLL_name);

	trk_Vars = decldiagparam("trk_Vars", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.", trk_Vars);

	chg_Pars = decldiagparam("chg_Pars", TEN, "' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '", "Trace these variables at end of loop.", chg_Pars);

	decldiagparam("Borland_Dll", ONE, "1", "0", "1", "Borland_Dll requires an underscore before routine name", "()", &Borland_Dll);

}

void ClassMod_Exec::init(void) {

	Vars_Cnt = 0;
	Pars_Cnt = 0;

 string S;

	nhru = getdim(NHRU);

	ClassVar *newVar;
	ClassPar *newPar;

	//auto &trk_Vars = TStringList();


	S_Vars = "";
	S_Pars = "";

	VarArray = NULL;
	ParArray = NULL;

	bool Root = false;

	if (this->GroupCnt)
		Root = true;

	long  GetUnit;

	if (trk_Vars->Count) {
		VarArray = new float *[trk_Vars->Count];

		for (long ii = 0; ii < trk_Vars->Count; ++ii) {
			/*S = trk_Vars->strings[ii].Trim();
			if (S.IsEmpty())
			break;*/

			GetUnit = FindWildVarFloat(S.c_str(), newVar); // name changed 08/16/16 needs checked
			VarArray[ii] = newVar->values;
			S_Vars += (newVar->name + " ").c_str();
			++Vars_Cnt;
		}
	}

	if (chg_Pars->Count) {
		ParArray = new float *[chg_Pars->Count];

		for (long ii = 0; ii < chg_Pars->Count; ++ii) {
			/*S = chg_Pars->strings[ii].Trim();
			if (S.IsEmpty())
			break;*/

			GetUnit = FindWildParFloat(S.c_str(), newPar, false, Root); // name
			ParArray[ii] = newPar->values;
			S_Pars += (newPar->param + " ").c_str();
			++Pars_Cnt;
		}

	}

	//DLL = LoadLibrary(DLL_name->strings[0].c_str()); // Borland  or gcc "C:/Jose/CodeBlocks_Jose/Jose_dll/bin/debug/Jose_Dll.dll

	//if (!DLL) {
	//	CRHMException TExcept((string("Could not open DLL file: ") + DLL_name->strings[0]).c_str(), TERMINATE);
	//	LogError(TExcept);
	//}

 string Routine1 = "CRHM_Init";
 string Routine2 = "CRHM_Step";
	if (Borland_Dll[0]) {
		Routine1 = "_" + Routine1;
		Routine2 = "_" + Routine2;
	}

	// Get the address of the function.
	//LoadUserInit = (LoadModuleTypeInit *)GetProcAddress(DLL, Routine1.c_str());

	//// Make sure we have the address then call the function.
	//if (!LoadUserInit) {
	//	Imodules = FreeLibrary(DLL);
	//	while (Imodules)
	//		Imodules = FreeLibrary(DLL);

	//	CRHMException TExcept((string("Could not open DLL file entry point: ") + Routine1).c_str(), TERMINATE);
	//	LogError(TExcept);
	//}

	// Get the address of the function.
	//LoadUserStep = (LoadModuleTypeStep *)GetProcAddress(DLL, Routine2.c_str());

	//// Make sure we have the address then call the function.
	//if (!LoadUserStep) {
	//	Imodules = FreeLibrary(DLL);
	//	while (Imodules)
	//		Imodules = FreeLibrary(DLL);

	//	CRHMException TExcept((string("Could not open DLL file entry point: ") + Routine2).c_str(), TERMINATE);
	//	LogError(TExcept);
	//}
}

void ClassMod_Exec::run(void) {

	if (getstep() == 1) {
		statusInit[0] = LoadUserInit(this->Name.c_str(), this->GroupCnt, nhru, S_Vars.c_str(), Vars_Cnt, VarArray, S_Pars.c_str(), Pars_Cnt, ParArray);
	}

	double Fix = std::stod(getTimeGG());
	statusStep[0] = LoadUserStep(Fix);
}

void ClassMod_Exec::finish(bool good) {

	statusStep[0] = LoadUserStep(0.0);

	/*if (DLL) {
	Imodules = FreeLibrary(DLL);
	while (Imodules)
	Imodules = FreeLibrary(DLL);
	}*/

	delete[] VarArray;

	delete[] ParArray;
}



ClassFlowInSnow* ClassFlowInSnow::klone(string name) const {
	return new ClassFlowInSnow(name);
}

void ClassFlowInSnow::decl(void) {

	Description = "'Calculates Flow in Snow.'";

	declvar("Ksat_snow", NHRU, "saturated permeability of snow", "(m^2)", &Ksat_snow);

	declvar("K_snow", NHRU, "intrinsic permeability of snow", "(m^2)", &K_snow);

	declvar("u_down", NHRU, "Colbeck's downward flux of water flow in snow based on Darcy's Law", "(m/s)", &u_down);

	declvar("K_down", NHRU, "mass flow of Colbeck's downward flux in snow", "(m/s)", &K_down);

	declvar("K_slope", NHRU, "mass flow in snow along slope", "(m/s)", &K_slope);

	declvar("Meltrunoff_K", NHRU, "melt runoff storage constant", "(d)", &Meltrunoff_K);

	decldiag("In_storage", NHRU, "melt runoff in storage at the beginning of interval!", "(mm)", &In_storage);

	decldiag("runKstorage_var", NHRU, "modified value of runKstorage", "(d)", &runKstorage_var);


	declparam("S_I", NHRU, "[3.3]", "1.0", "7.0", "soil index", "()", &S_I);

	declparam("d_g", NHRU, "[3.0]", "0.0", "10.0", "snow grain diameter", "(mm)", &d_g);

	declparam("t_inhibit_flow", NHRU, "[-2.0]", "-15", "5", "threshold temperature of inhibit flow in snow; i.e. inhibit when lower snowpack temperature is below this threshold temperature", "(�C)", &t_inhibit_flow);

	declparam("runKstorage_winter", NHRU, "[2.0]", "0", "200.0", "runoff storage constant when lower snowpack temperature is below the threshold temperature", "(d)", &runKstorage_winter);

	declparam("runKstorage_summer", NHRU, "[2.0]", "0", "200.0", "runoff storage constant for snowcover free period", "(d)", &runKstorage_summer);

	declparam("Sr", NHRU, "[0.07]", "0.0", "1.0", "residual saturation of snow", "()", &Sr);

	declparam("hru_GSL", NHRU, "[0.0]", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "()", &hru_GSL);

	declparam("route_L", NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

	declputparam("*", "runKstorage", "(d)", &runKstorage);


	declgetvar("*", "rho", "((kg/m^3))", &rho);

	declgetvar("*", "h2o_sat", "()", &h2o_sat);

	declgetvar("*", "T_s_l", "(�C)", &T_s_l);

	declgetvar("*", "z_s", "((kg/m^3))", &z_s);

}

void ClassFlowInSnow::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		Ksat_snow[hh] = 0.0;
		K_snow[hh] = 0.0;
		u_down[hh] = 0.0;
		K_down[hh] = 0.0;
		K_slope[hh] = 0.0;
		Meltrunoff_K[hh] = 0.0;
		runKstorage[hh] = 0.0;
		In_storage[hh] = 0.0;
	}

	Netroute_module = (ClassModule*)FindModule_from_parameter("*", "runKstorage");
}

void ClassFlowInSnow::run(void) {
	const float UnitWidth = 1.0, UnitArea = 1.1;
	for (hh = 0.0; chkStruct(); ++hh) {
		if (rho[hh] > 0) {
			if (T_s_l[hh] >= t_inhibit_flow[hh] && h2o_sat[hh] > Sr[hh]) {
				Ksat_snow[hh] = 0.077*sqr((d_g[hh] / 1000))*exp(-7.8*(rho[hh] / 1000));
				K_snow[hh] = Ksat_snow[hh] * (pow((h2o_sat[hh] - Sr[hh]) / (1 - Sr[hh]), S_I[hh]));
				u_down[hh] = K_snow[hh] * 1000 * 9.8 / 0.001787;
				K_down[hh] = u_down[hh] * z_s[hh] * UnitWidth / UnitArea;
				K_slope[hh] = K_down[hh] * sin(hru_GSL[hh] * DEGtoRAD);
				Meltrunoff_K[hh] = route_L[hh] / (K_slope[hh]) / (60 * 60 * 24);
				runKstorage[hh] = route_L[hh] / (K_slope[hh]) / (60 * 60 * 24);
				if (Meltrunoff_K[hh] > runKstorage_winter[hh]) {
					Meltrunoff_K[hh] = runKstorage_winter[hh];
					runKstorage[hh] = runKstorage_winter[hh];
				}
				runKstorage_var[hh] = runKstorage[hh];
				//        In_storage[hh] = Netroute_module->Function2(runKstorage, hh);

			}
			else {
				if (T_s_l[hh]<t_inhibit_flow[hh] || h2o_sat[hh] <= Sr[hh]) {
					u_down[hh] = 0.0;
					Meltrunoff_K[hh] = runKstorage_winter[hh];
					runKstorage[hh] = runKstorage_winter[hh];
					runKstorage_var[hh] = runKstorage[hh];
					In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
				}
			}
		}
		else {
			Meltrunoff_K[hh] = runKstorage_summer[hh];
			runKstorage[hh] = runKstorage_summer[hh];
			runKstorage_var[hh] = runKstorage[hh];
			In_storage[hh] = Netroute_module->Function2(runKstorage, hh);
		}
	} // for
}

ClassSWEslope* ClassSWEslope::klone(string name) const {
	return new ClassSWEslope(name);
}

void ClassSWEslope::decl(void) {

	Description = "'calculates SWE slope transport (Bernhardt & Schulz, 2010).' \
                 'Standard version for use with the glacier module,' \
                 'Standard version for use without the glacier module. Identical code but links to snowmeltD.'";


	variation_max = VARIATION_1;


	declvar("SWE_out", NHRU, "outgoing snow slide transport SWE", "(mm/int)", &SWE_out);

	declvar("SWE_in", NHRU, "incoming snow slide transport SWE", "(mm/int)", &SWE_in);

	declstatdiag("cumSWE_in", NHRU, "incoming cumulative Slide transport SWE from other HRU", "(mm)", &cumSWE_in);

	declstatdiag("cumSWE_out", NHRU, "outgoing cumulative Slide transport SWE to other HRU", "(mm)", &cumSWE_out);

	declvar("Hd", NHRU, "SWE holding depth of snow", "(mm)", &Hd);

	/* parameters */

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "sequence of HRUs for slide routing ", "()", &order);

	declparam("Disable_SWEslope", NHRU, "[0]", "0", "1", "set to 1 to disable module", "()", &Disable_SWEslope);

	declparam("Hd_min", NHRU, "[50.0]", "0", "750", "minimum SWE holding depth", "(mm)", &Hd_min);

	declparam("use_rho", NHRU, "[1]", "0", "1", "0: user defined snow density, 1: use rho from Snobal", "()", &use_rho);

	declparam("snow_density", NHRU, "[100]", "50", "750", "density of snow", "(kg/m^3)", &snow_density);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("distrib_SWEslope", NDEFN, "[0.0]", "0.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs. Source HRU can include itself in the re-distribution", "()", &distrib_SWEslope, &distrib_hru, nhru);


	declputvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "rho", "(kg/m^3)", &rho);
}

void ClassSWEslope::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		SWE_in[hh] = 0.0;
		SWE_out[hh] = 0.0;
		cumSWE_in[hh] = 0.0;
		cumSWE_out[hh] = 0.0;
		Hd[hh] = 0.0;
	}
}

void ClassSWEslope::run(void) {

	for (long hh = 0; chkStruct(hh); ++hh) {
		SWE_in[hh] = 0.0;
		SWE_out[hh] = 0.0;
		Hd[hh] = 0.0;
	}

	for (long hhh = 0; chkStruct(hhh); ++hhh) {
		if (Disable_SWEslope[hhh])
			continue;

		hh = order[hhh] - 1; // do HRUs in the desired sequence

		if (hru_GSL[hh] > 25.0) {
			float den_snow;
			if (use_rho[hh])
				den_snow = rho[hh];
			else
				den_snow = snow_density[hh];

			Hd[hh] = 3178.4*pow(hru_GSL[hh], -1.998)*den_snow; // equation in mm SWE and slope in degrees

			if (Hd[hh] > Hd_min[hh] && SWE[hh] > Hd[hh]) {

				float Used, total = 0.0;
				float Amount = SWE[hh];

				for (long To = 0; chkStruct(To); ++To) // distribute SWE flow of this HRU
					total += distrib_hru[hh][To]; // includes itself
				if (total == 0 || total <= distrib_hru[hh][hh]) break; // no distribution

				for (long To = 0; chkStruct(To); ++To) { // distribute SWE outflow of HRU
					if (hh != To && Amount > 0.0 && distrib_hru[hh][To] > 0.0) {
						Used = Amount * distrib_hru[hh][To] / total;
						SWE_out[hh] = Used;
						cumSWE_out[hh] += Used;
						SWE[hh] -= Used;

						Used = Used * hru_area[hh] / hru_area[To]; // adjust to area of destination HRU
						SWE[To] += Used;
						SWE_in[To] = Used;
						cumSWE_in[To] += Used;
					} // if
				} // end for (hhh)
			} // end of moving
		} // slide possible
	} // end for (hh)
}

void ClassSWEslope::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (SWESlope)' cumSWE_in (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_in[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SWESlope)' cumSWE_out (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumSWE_out[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassSoilDS* ClassSoilDS::klone(string name) const {
	return new ClassSoilDS(name);
}

void ClassSoilDS::decl(void) {

	Description = "' Handles soil moisture throughout the year. Expanded to handle detention layer.' \
                 'Standard version,' \
                 'Version with Culvert limited runoff.'";

	variation_set = VARIATION_1;

	declvar("culvert_Q", NHRU, "flow in culvert.", "(m^3/s)", &culvert_Q);

	declvar("culvert_water_H", NHRU, "depth of pond at culvert inlet.", "(m)", &culvert_water_H);

	declvar("culvert_water_A", NHRU, "surface area of culvert pond.", "(m^2)", &culvert_water_A);

	declvar("culvert_water_V", NHRU, "volume of water in culvert pond.", "(m^3)", &culvert_water_V);

	declvar("culvert_over_Q", NHRU, "flow over the road.", "(m^3/s)", &culvert_over_Q);

	declvar("culvert_evap", NHRU, "Depth of water evaporating from culvert pond.", "(mm/int)", &culvert_evap);

	declstatdiag("cum_culvert", NHRU, "Cumulative culvert HRU flow.", "(m^3)", &cum_culvert);

	declstatdiag("cum_culvert_over", NHRU, "Cumulative culvert HRU overflow.", "(m^3)", &cum_culvert_over);

	decldiag("HD", NHRU, "ratio of depth of water at culvert/culvert diameter.", "()", &HD);

	declparam("channel_slope", NHRU, "[0.002]", "0.0001", "0.01", "soil slope to culvert.", "()", &channel_slope);

	declparam("side_slope", NHRU, "[0.02]", "0.0001", "0.01", "side soil slope mormal to culvert slope.", "()", &side_slope);

	declparam("culvert_diam", NHRU, "[0.5]", "0.1", "5.0", "culvert diameter.", "(m)", &culvert_diam);

	declparam("culvert_water_Dmax", NHRU, "[2.0]", "0.1", "10.0", "maximum depth of pond at culvert inlet.", "(m)", &culvert_water_Dmax);

	declparam("number_culverts", NHRU, "[1.0]", "0.0", "10.0", "number of culverts and efficiency factor. Zero = no culvert.", "()", &number_culverts);

	declparam("culvert_type", NHRU, "[0]", "0", "4", "0- thin walled projection, 1- square edged (flush) inlet, 2- socket and concrete pipe, 3- 45 degree beveled inlet, 4- well-rounded (streamlined) inlet.", "()", &culvert_type);


	variation_set = VARIATION_ORG;

	if (Global::nlay < 2) {
		Global::nlay = 2;
		Global::maxlay = 2;
	}

	declvar("redirected_residual", NHRU, "redirected residual after topping up Sd and soil_rechar in Netroute/_D/_M/_M_D.", "(mm*km^2/int)", &redirected_residual);

	declstatdiag("cum_redirected_residual", NHRU, "cumulative HRU redirected_residual to another HRU.", "(mm*km^2)", &cum_redirected_residual);

	declstatvar("Sd", NHRU, "Depression storage.", "(mm)", &Sd);

	declstatvar("gw", NHRU, "ground water storage.", "(mm)", &gw);

	declstatvar("soil_rechr", NHRU, "moisture content of soil recharge zone, ie, the"//
		"portion of the soil profile from which evaporation can take place.", "(mm)", &soil_rechr);

	declstatvar("soil_moist", NHRU, "moisture content of soil profile to the depth"//
		"of the rooting zone of the major vegetation type on the HRU.", "(mm)", &soil_moist);

	decllocal("cum_hru_condense", NHRU, "cumulative condensation over HRU.", "(mm)", &cum_hru_condense);

	decllocal("Dts_runoff_K", NHRU, "daily detention storage runoff drainage factor. Values from parameters Dts_snow_runoff_K or Dts_organic_runoff_K determined from snowcover.", "mm/d", &Dts_runoff_K);

	declvar("soil_gw", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/int)", &soil_gw);

	declvar("soil_gw_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_gw_D);

	declvar("gw_flow", NHRU, "Drainage from HRU ground water reservoir.", "(mm/int)", &gw_flow);

	declvar("gw_flow_D", NHRU, "Daily drainage from HRU ground water reservoir.", "(mm/d)", &gw_flow_D);

	declvar("infil_act", NHRU, "Actual amount of water infiltrating the soil on each HRU.", "(mm/int)", &infil_act);

	declvar("cum_infil_act", NHRU, "Accumulation of the actual amount of water infiltrating the soil on each HRU.", "(mm)", &cum_infil_act);

	declvar("infil_act_D", NHRU, "Daily actual amount of water infiltrating the soil on each HRU.", "(mm/d)", &infil_act_D);

	declstatdiag("cum_gw_flow", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_gw_flow);

	declvar("soil_ssr", NHRU, "Portion of soil moisture and recharge excess from a HRU that enters subsurface reservoirs.", "(mm/int)", &soil_ssr);

	declvar("rechr_ssr", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/int)", &rechr_ssr);

	declstatdiag("cum_soil_ssr", NHRU, "Accumulation of soil moisture from a HRU to ssr.", "(mm)", &cum_soil_ssr);

	declstatdiag("cum_rechr_ssr", NHRU, "Accumulation of Portion of excess from a HRU to ssr.", "(mm)", &cum_rechr_ssr);

	declvar("soil_ssr_D", NHRU, "Portion of excess soil water from a HRU that enters subsurface reservoirs.", "(mm/d)", &soil_ssr_D);

	declvar("soil_runoff", NHRU, "Portion of excess soil water from a HRU to runoff.", "(mm/int)", &soil_runoff);

	declstatdiag("cum_soil_runoff", NHRU, "Accumulation of Portion of excess soil water from a HRU to runoff.", "(mm)", &cum_soil_runoff);

	declvar("soil_runoff_D", NHRU, "Portion of excess soil water from a HRU that enters groundwater reservoirs.", "(mm/d)", &soil_runoff_D);

	declstatdiag("cum_runoff_to_Sd", NHRU, "Cumulative portion of runoff to depression storage.", "(mm/int)", &cum_runoff_to_Sd);

	declstatdiag("cum_soil_gw", NHRU, "Accumulation of excess soil water from a HRU that enters groundwater reservoirs.", "(mm)", &cum_soil_gw);


	decllocal("snowinfil_buf", NHRU, "buffer snow infiltration.", "(mm/d)", &snowinfil_buf);

	decllocal("runoff_buf", NHRU, "buffer runoff.", "(mm/d)", &runoff_buf);

	decllocal("meltrunoff_buf", NHRU, "buffer melt runoff.", "(mm/d)", &meltrunoff_buf);

	decllocal("hru_evap_buf", NHRU, "buffer evaporation.", "(mm/d)", &hru_evap_buf);

	decllocal("soil_moist_Init", NHRU, "initial soil moisture.", "(mm)", &soil_moist_Init);

	decllocal("soil_rechr_Init", NHRU, "initial soil recharge.", "(mm)", &soil_rechr_Init);

	decllocal("Sd_Init", NHRU, "initial Depression storage.", "(mm)", &Sd_Init);

	decllocal("gw_Init", NHRU, "initial ground water storage.", "(mm)", &gw_Init);


	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area.", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area.", "(km^2)", &hru_area);

	declparam("Sdmax", NHRU, "[0]", "0.0", "5000.0", "Maximum depression storage.", "(mm)", &Sdmax);

	declparam("Sdinit", NHRU, "[0]", "0.0", "5000.0", "Initial depression storage.", "(mm)", &Sdinit);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0",
		"Maximum value for soil recharge zone (upper portion of soil_moist where losses occur as both evaporation "//
		"and transpiration).  Must be less than or equal to soil_moist.", "(mm)", &soil_rechr_max);

	declparam("soil_rechr_init", NHRU, "[30.0]", "0.0", "250.0", "Initial value for soil recharge zone (upper part of "//
		"soil_moist).  Must be less than or equal to soil_moist_init.", "(mm)", &soil_rechr_init);

	declparam("soil_moist_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of soil profile."//
		"Soil profile is surface to bottom of rooting zone.", "(mm)", &soil_moist_max);

	declparam("soil_moist_init", NHRU, "[187.0]", "0.0", "5000.0",
		"Initial value of available water in soil profile.", "(mm)", &soil_moist_init);

	declparam("soil_gw_K", NHRU, "[0.0]", "0.", "100.0", "The maximum amount of the soil water excess for an HRU "//
		"that is routed directly to the associated groundwater reservoir each day.", "(mm/d)", &soil_gw_K);

	declparam("gw_max", NHRU, "[375.0]", "0.0", "5000.0", "Maximum available water holding capacity of ground water reservoir.", "(mm)", &gw_max);

	declparam("gw_init", NHRU, "[187.0]", "0.0", "5000.0", "Initial value of available water in ground water reservoir.", "(mm)", &gw_init);

	declparam("gw_K", NHRU, "[0.0]", "0.", "100.0", "daily ground water drainage from gw reservoir.", "(mm/d)", &gw_K);

	declparam("rechr_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from recharge.", "(mm/d)", &rechr_ssr_K);

	declparam("lower_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily ssr drainage from soil column.", "(mm/d)", &lower_ssr_K);

	declparam("Sd_ssr_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage ssr drainage factor.", "(mm/d)", &Sd_ssr_K);

	declparam("Sd_gw_K", NHRU, "[0.0]", "0.", "100.0", "daily depression storage gw drainage.", "(mm/d)", &Sd_gw_K);

	declparam("soil_withdrawal", NDEFN, "[3]", "1", "4",
		"Select water withdrawal function for soil type: 1 = sand, 2 = loam, 3 = clay, 4 = organic. soil_withdrawal[1] - rechr layer, soil_withdrawal[2] - lower layer", "()",
		&soil_withdrawal, &soil_withdrawal_Tables, 2);

	declparam("cov_type", NHRU,
		"[1]", "0", "2", "Vegetation evaporation type designation for HRU:  "//
		"0 = bare soil (no evaporation), 1 = crops (recharge layer), 2 = grasses & shrubs (all soil moisture).", "()", &cov_type);

	declparam("transp_limited", NHRU, "[0]", "0", "1", "limit transpiration to recharge layer only  on-1/off-0.", "()", &transp_limited);

	declparam("soil_ssr_runoff", NHRU, "[1]", "0", "1", "soil column excess to interflow(ssr)/runoff (and possibly Sd)  interflow-0/runoff-1.", "()", &soil_ssr_runoff);

	declgetparam("*", "inhibit_evap", "()", &inhibit_evap); // used since no declgetparam defined

	declputvar("*", "hru_actet", "(mm/int)", &hru_actet);

	declputvar("*", "hru_cum_actet", "(mm)", &hru_cum_actet);


	evapDiv = declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);


	declgetvar("*", "infil", "(mm/int)", &infil);

	snowinfilDiv = declgetvar("*", "snowinfil", "(mm/int)", &snowinfil);

	runoffDiv = declgetvar("*", "runoff", "(mm/int)", &runoff);

	meltrunoffDiv = declgetvar("*", "meltrunoff", "(mm/int)", &meltrunoff);

	declparam("Dts_snow_max", NHRU, "[0]", "0.0", "5000.0", "Maximum detention storage in snowcover period.", "(mm)", &Dts_snow_max);

	declparam("Dts_organic_max", NHRU, "[0]", "0.0", "5000.0", "Maximum detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_max);

	declparam("Dts_snow_init", NHRU, "[0]", "0.0", "5000.0", "Initial detention storage in snowcover period.", "(mm)", &Dts_snow_init);

	declparam("Dts_snow_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of snow runoff drainage factor.", "(mm/d)", &Dts_snow_runoff_K);

	declparam("Dts_organic_runoff_K", NHRU, "[0.0]", "0.", "100.0", "daily detention storage of organic layer runoff drainage factor.", "(mm/d)", &Dts_organic_runoff_K);

	declparam("Dts_organic_init", NHRU, "[0]", "0.0", "5000.0", "Initial detention storage in organic layer for snow free period.", "(mm)", &Dts_organic_init);

	declvar("Dts", NHRU, "Detention storage.", "(mm)", &Dts);

	declvar("Dts_max", NHRU, "Maximum detention storage.", "(mm)", &Dts_max);
}

void ClassSoilDS::init(void) {

	nhru = getdim(NHRU);

	if (snowinfilDiv > 1) {
	 string S = "Soil:  \"snowinfil\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (evapDiv > 1) {
	 string S = "Soil:  \"hru_evap\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (meltrunoffDiv > 1) {
	 string S = "Netroute:  \"meltrunoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (runoffDiv > 1) {
	 string S = "Netroute:  \"runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {

		if (soil_moist[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_moist cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}

		if (soil_rechr[hh] > soil_rechr_max[hh]) {
		 string S = string("'") + Name + " (Soil)' soil_rechr cannot be greater than soil_rechr_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), TERMINATE);
			LogError(TExcept);
			throw TExcept;
		}
		if (soil_rechr_max[hh] > soil_moist_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Soil_rechr_max cannot be greater than soil_moist_max in hru = " + std::to_string(hh + 1).c_str();
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
			throw TExcept;
		}

		if (Sdinit[hh] > Sdmax[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of depression storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		if (gw_init[hh] > gw_max[hh]) {
		 string S = string("'") + Name + " (Soil)' Initial value of gw storage is greater than the maximum value in hru = " + std::to_string(hh + 1).c_str();
			CRHMException Except(S.c_str(), TERMINATE);
			LogError(Except);
			throw Except;
		}

		soil_rechr[hh] = soil_rechr_init[hh];
		soil_moist[hh] = soil_moist_init[hh];

		redirected_residual[hh] = 0.0;
		cum_redirected_residual[hh] = 0.0;

		Sd[hh] = Sdinit[hh];

		gw[hh] = gw_init[hh];

		hru_cum_actet[hh] = 0.0;
		cum_hru_condense[hh] = 0.0;
		cum_infil_act[hh] = 0.0;

		soil_runoff_D[hh] = 0.0;
		soil_ssr_D[hh] = 0.0;
		soil_gw_D[hh] = 0.0;
		gw_flow_D[hh] = 0.0;
		infil_act[hh] = 0.0;
		infil_act_D[hh] = 0.0;

		cum_soil_runoff[hh] = 0.0;
		cum_soil_ssr[hh] = 0.0;
		cum_rechr_ssr[hh] = 0.0;
		cum_soil_gw[hh] = 0.0;
		cum_gw_flow[hh] = 0.0;

		cum_runoff_to_Sd[hh] = 0.0;

		if (inhibit_evap[hh] == 1) {  // when snowcover
			Dts_max[hh] = Dts_snow_max[hh];
			Dts[hh] = Dts_snow_init[hh];
		}
		else if (inhibit_evap[hh] == 0) {  // when no snowcover
			Dts_max[hh] = Dts_organic_max[hh];
			Dts[hh] = Dts_organic_init[hh];
		}

		if (variation == VARIATION_1) {
			if (culvert_water_Dmax[hh] / culvert_diam[hh] > 2.5) {
			 string S = "soil: " + string(Name.c_str()) + " ratio of H/D > 2.5 in HRU " + std::to_string(hh + 1);
				CRHMException TExcept(S.c_str(), WARNING);
				LogError(TExcept);
			}
			culvert_water_V[hh] = 0.0;
			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;
			cum_culvert[hh] = 0.0;
			cum_culvert_over[hh] = 0.0;
		}
	}
}

void ClassSoilDS::run(void) {

	float soil_lower, excs, condense, Dss;
	float et;

	long nstep = getstep();

	if (nstep == 1)
		for (hh = 0; chkStruct(); ++hh) {
			LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist_init     (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilDS)' gw_init             (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
			soil_moist_Init[hh] = soil_moist[hh];
			soil_rechr_Init[hh] = soil_rechr[hh];
			Sd_Init[hh] = Sd[hh];
			gw_Init[hh] = gw[hh];
		}

	nstep = nstep % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (snowinfilDiv == 1) // interval value
			snowinfil_buf[hh] = snowinfil[hh];

		if (runoffDiv == 1) // interval value
			runoff_buf[hh] = runoff[hh];

		if (meltrunoffDiv == 1) // interval value
			meltrunoff_buf[hh] = meltrunoff[hh];

		if (evapDiv == 1) // interval value
			hru_evap_buf[hh] = hru_evap[hh];

		if (nstep == 1) { // beginning of every day
			soil_runoff_D[hh] = 0.0;
			soil_ssr_D[hh] = 0.0;
			soil_gw_D[hh] = 0.0;
			gw_flow_D[hh] = 0.0;
			infil_act_D[hh] = 0.0;
		}

		hru_actet[hh] = 0.0;
		infil_act[hh] = 0.0;
		soil_gw[hh] = 0.0;
		soil_ssr[hh] = 0.0;
		rechr_ssr[hh] = 0.0;

		if (hru_evap_buf[hh] < 0.0) {
			condense = -hru_evap_buf[hh];
			cum_hru_condense[hh] += condense;
			hru_evap_buf[hh] = 0.0;
		}
		else
			condense = 0.0;

		//******Add infiltration to soil and compute excess

		if (soil_moist_max[hh] > 0.0) {
			soil_lower = soil_moist[hh] - soil_rechr[hh];

			float potential = infil[hh] + snowinfil_buf[hh] + condense;

			soil_rechr[hh] = soil_rechr[hh] + potential;

			if (soil_rechr[hh] > soil_rechr_max[hh]) {
				excs = soil_rechr[hh] - soil_rechr_max[hh];
				soil_rechr[hh] = soil_rechr_max[hh];
				soil_lower = soil_lower + excs;
			}

			soil_moist[hh] = soil_lower + soil_rechr[hh];

			if (soil_moist[hh] > soil_moist_max[hh]) {
				excs = soil_moist[hh] - soil_moist_max[hh];
				soil_moist[hh] = soil_moist_max[hh];
			}
			else
				excs = 0.0;

			infil_act[hh] = potential - excs;
			cum_infil_act[hh] += infil_act[hh];
			infil_act_D[hh] += infil_act[hh];

			//  Handle subsurface runoff

			if (!inhibit_evap[hh]) { // only when no snowcover
				rechr_ssr[hh] = soil_rechr[hh] / soil_rechr_max[hh] * rechr_ssr_K[hh] / Global::Freq;
				if (rechr_ssr[hh] > soil_rechr[hh])
					rechr_ssr[hh] = soil_rechr[hh];

				soil_rechr[hh] -= rechr_ssr[hh];
				if (soil_rechr[hh] < 0.0)
					soil_rechr[hh] = 0.0;

				soil_moist[hh] -= rechr_ssr[hh];
				soil_ssr[hh] = rechr_ssr[hh];
				cum_rechr_ssr[hh] += rechr_ssr[hh];
			}

			float s2gw_k = soil_gw_K[hh] / Global::Freq;

			//  Handle excess to gw

			if (excs >= s2gw_k) { // to gw 03/04/10 changed from >
				soil_gw[hh] = s2gw_k;
				excs -= s2gw_k;
			}
			else { // to gw
				soil_gw[hh] = excs;
				excs = 0.0;
			}

			//  Handle excess to interflow or runoff

			if (!soil_ssr_runoff[hh] && excs > 0.0) { // to interflow
				soil_ssr[hh] += excs;
				excs = 0.0;
			}
		}
		else { // soil_moist_max <= 0.0, i.e. Pond
			excs = infil[hh] + snowinfil_buf[hh] + condense;
		}

		float runoff_to_Sd = 0.0;

		soil_runoff[hh] = meltrunoff_buf[hh] + runoff_buf[hh] + excs + redirected_residual[hh] / hru_area[hh]; // last term (mm*km^2/int)

		cum_redirected_residual[hh] += redirected_residual[hh];

		redirected_residual[hh] = 0;

		if (soil_runoff[hh] > 0.0 && Dts_max[hh] > 0.0) {

			if (inhibit_evap[hh] == 1) // when snowcover
				Dts_max[hh] = Dts_snow_max[hh];

			else if (inhibit_evap[hh] == 0) // when no snowcover
				Dts_max[hh] = Dts_organic_max[hh];

			Dss = Dts_max[hh] - Dts[hh];

			if (Dss > 0.0) {
				if (soil_runoff[hh] > Dss) {
					soil_runoff[hh] -= Dss;
					if (soil_runoff[hh] < 0.0)
						soil_runoff[hh] = 0.0;
					Dts[hh] += Dss;
				}
				else {
					Dts[hh] += soil_runoff[hh];
					soil_runoff[hh] = 0.0;
				}
			}
		}

		// lateral drainage of detention storage to soil_runoff
		if (inhibit_evap[hh] == 1)  // when snowcover
			Dts_runoff_K[hh] = Dts_snow_runoff_K[hh];
		if (inhibit_evap[hh] == 0)  // when no snowcover
			Dts_runoff_K[hh] = Dts_organic_runoff_K[hh];

		if (Dts[hh] > 0.0 && Dts_runoff_K[hh] > 0.0) {
			float Dss2runoff_k = Dts_runoff_K[hh] / Global::Freq;
			if (Dss2runoff_k >= Dts[hh])
				Dss2runoff_k = Dts[hh];
			soil_runoff[hh] += Dss2runoff_k;
			Dts[hh] -= Dss2runoff_k;
		}

		if (Dts[hh] < 0.0001)
			Dts[hh] = 0.0;

		if (soil_runoff[hh] > 0.0 && Sdmax[hh] > 0.0) {
			float Fix = -12.0;
			if (soil_runoff[hh] / Sdmax[hh] < 12.0)
				Fix = -soil_runoff[hh] / Sdmax[hh];
			Dss = (Sdmax[hh] - Sd[hh])*(1 - exp(Fix));

			if (soil_moist_max[hh] <= 0.0) // handle pond
				Dss = Sdmax[hh] - Sd[hh];

			if (Dss > 0.0) {
				if (soil_runoff[hh] > Dss) {
					soil_runoff[hh] -= Dss;
					if (soil_runoff[hh] < 0.0)
						soil_runoff[hh] = 0.0;
					Sd[hh] += Dss;
					runoff_to_Sd += Dss;
				}
				else {
					Sd[hh] += soil_runoff[hh];
					runoff_to_Sd += soil_runoff[hh];
					soil_runoff[hh] = 0.0;
				}
			}
		}

		if (variation == VARIATION_1) {

			float culvert_C[5] = { 0.5, 0.6, 0.7, 0.75, 0.97 };

			culvert_water_H[hh] = 0.0;
			culvert_water_A[hh] = 0.0;
			culvert_over_Q[hh] = 0.0;
			culvert_Q[hh] = 0.0;
			culvert_evap[hh] = 0.0;

			if ((soil_runoff[hh] > 0.0 || culvert_water_V[hh] > 0.0) && number_culverts[hh] > 0.0) { // culvert addition. Inputs are in (mm)
				culvert_water_V[hh] += soil_runoff[hh] * (hru_area[hh] * 1000.0); // convert mm to m3
				soil_runoff[hh] = 0.0;

				culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

				if (culvert_water_H[hh] > 0.0) {

					// calculate overflow if culvert level exceeds Dmax

					culvert_water_H[hh] = pow(3.0*culvert_water_V[hh] * channel_slope[hh] * side_slope[hh], 1.0 / 3.0); // (m)

					if (culvert_water_H[hh] > culvert_water_Dmax[hh]) { // (m) overflow over road
						culvert_water_H[hh] = culvert_water_Dmax[hh]; // (m)
						float maxVol = pow(culvert_water_Dmax[hh], 3.0) / (3.0*channel_slope[hh] * side_slope[hh]); // (m3)

						culvert_over_Q[hh] = (culvert_water_V[hh] - maxVol) / 86400.0*Global::Freq; // (m3) to (m3/int)
						culvert_water_V[hh] = maxVol; // (m3)

						cum_culvert_over[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
						soil_runoff[hh] += culvert_over_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
					}
					HD[hh] = culvert_water_H[hh] / culvert_diam[hh];

					// calculate flow through culvert

					if (HD[hh] <= 0.0)
						culvert_Q[hh] = 0.0;
					else if (HD[hh] < 1.5)
						culvert_Q[hh] = max <float>((-0.544443*pow(HD[hh], 4.0) + 0.221892*pow(HD[hh], 3.0) + 2.29756*pow(HD[hh], 2.0)
							+ 0.159413*HD[hh] + 0.00772254)*culvert_C[culvert_type[hh]] * number_culverts[hh] * pow(culvert_diam[hh], 2.5), 0.0); // (m3/s)
					else
						culvert_Q[hh] = culvert_C[culvert_type[hh]] * number_culverts[hh] * 0.785*pow(culvert_diam[hh], 2.5)*sqrt(2.0*9.81*(HD[hh] - 0.5));

					if (culvert_water_V[hh] > culvert_Q[hh] * 86400.0 / Global::Freq) // (m3/s) to (m3))
						culvert_water_V[hh] -= culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3)
					else {
						culvert_Q[hh] = culvert_water_V[hh] * Global::Freq / 86400.0;  // (m3) to (m3/s)
						culvert_water_V[hh] = 0.0;
					}

					cum_culvert[hh] += culvert_Q[hh] * 86400.0 / Global::Freq; // (m3/s) to (m3/int)
					soil_runoff[hh] += culvert_Q[hh] * 86400.0 / Global::Freq / (hru_area[hh] * 1000.0); // (m3/s) to (mm/int)
				}
				culvert_water_A[hh] = sqr(culvert_water_H[hh]) / (channel_slope[hh] * side_slope[hh]); // used for evaporation
			} // culvert addition
		}

		soil_runoff_D[hh] += soil_runoff[hh];
		cum_soil_runoff[hh] += soil_runoff[hh];
		cum_runoff_to_Sd[hh] += runoff_to_Sd;

		if (Sd[hh] > 0.0 && Sd_gw_K[hh] > 0.0) {
			float Sd2gw_k = Sd_gw_K[hh] / Global::Freq;
			if (Sd2gw_k > Sd[hh])
				Sd2gw_k = Sd[hh];
			soil_gw[hh] += Sd2gw_k;
			Sd[hh] -= Sd2gw_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		soil_gw_D[hh] += soil_gw[hh];
		cum_soil_gw[hh] += soil_gw[hh];

		gw[hh] += soil_gw[hh];
		gw_flow[hh] = 0.0;
		if (gw[hh] > gw_max[hh]) {
			gw_flow[hh] += (gw[hh] - gw_max[hh]);
			gw[hh] = gw_max[hh];
		}

		if (gw_max[hh] > 0.0) { // prevents divide by zero error
			float spill = gw[hh] / gw_max[hh] * gw_K[hh] / Global::Freq;
			gw[hh] -= spill;
			gw_flow[hh] += spill;
		}

		gw_flow_D[hh] += gw_flow[hh];
		cum_gw_flow[hh] += gw_flow[hh];

		if (Sd[hh] > 0.0 && Sd_ssr_K[hh] > 0.0) {
			float Sd2ssr_k = Sd_ssr_K[hh] / Global::Freq; // WHY not proportional?
			if (Sd2ssr_k >= Sd[hh])
				Sd2ssr_k = Sd[hh];
			soil_ssr[hh] += Sd2ssr_k;
			Sd[hh] -= Sd2ssr_k;
			if (Sd[hh] < 0.0)
				Sd[hh] = 0.0;
		}

		float s2ssr_k = lower_ssr_K[hh] / Global::Freq;
		if (s2ssr_k > 0.0) {
			float avail = soil_moist[hh] - soil_rechr[hh];
			if (s2ssr_k >= avail)
				s2ssr_k = avail;
			soil_moist[hh] -= s2ssr_k;
			soil_ssr[hh] += s2ssr_k;
		}

		cum_soil_ssr[hh] += soil_ssr[hh];
		soil_ssr_D[hh] += soil_ssr[hh];

		//******Compute actual evapotranspiration

		float culvert_pond = 0.0; // convert m3 to mm

		float culvert_evapL = 0;

		if (variation == VARIATION_1 && culvert_water_V[hh] > 0.0 && hru_evap_buf[hh] > 0.0) { // conditions for culvert evaporation
			culvert_pond = culvert_water_V[hh] / (hru_area[hh] * 1000.0); // convert m3 to mm over HRU area
			culvert_evapL = hru_evap_buf[hh] * culvert_water_A[hh] / (hru_area[hh] * 1e6); // calculate potential evaporation from pond

			if (culvert_evapL > culvert_pond) // limit to amount available
				culvert_evapL = culvert_pond;

			culvert_evap[hh] = culvert_evapL;
			hru_actet[hh] += culvert_evapL;
			culvert_water_V[hh] = (culvert_pond - culvert_evapL)*(hru_area[hh] * 1000.0); // remove evaporation from culvert pond and convert to volume
		}

		float avail_evap = hru_evap_buf[hh] - culvert_evapL;
		if (Sd[hh] + soil_moist[hh] + culvert_pond > 0.0)
			avail_evap *= (Sd[hh] / (Sd[hh] + soil_moist[hh]));
		else
			avail_evap = 0.0;

		if (Sd[hh] > 0.0 && avail_evap > 0.0) {
			if (Sd[hh] >= avail_evap) {
				Sd[hh] -= avail_evap;
				if (Sd[hh] < 0.0)
					Sd[hh] = 0.0;
			}
			else {
				avail_evap = Sd[hh];
				Sd[hh] = 0.0;
			}
			hru_actet[hh] += avail_evap;
		}
		else
			avail_evap = 0.0;

		avail_evap = hru_evap_buf[hh] - avail_evap - culvert_evapL;

		if (avail_evap > 0.0 && soil_moist[hh] > 0.0 && cov_type[hh] > 0) {

			float pctl, pctr, etl, ets, etr;

			if ((soil_moist_max[hh] - soil_rechr_max[hh]) > 0.0)
				pctl = (soil_moist[hh] - soil_rechr[hh]) / (soil_moist_max[hh] - soil_rechr_max[hh]);
			else
				pctl = 0.0;

			pctr = soil_rechr[hh] / soil_rechr_max[hh];

			etr = avail_evap; // default

			switch (soil_withdrawal_Tables[0][hh]) {  // handle recharge layer
			case 1: //******sandy soil
				if (pctr < 0.25)
					etr = 0.5*pctr*avail_evap;
				break;
			case 2: //******loam soil
				if (pctr < 0.5)
					etr = pctr * avail_evap;
				break;
			case 3: //******clay soil
				if (pctr <= 0.33)
					etr = 0.5*pctr*avail_evap;
				else if (pctr < 0.67)
					etr = pctr * avail_evap;
				break;
			case 4: //******organic soil
					//         use default above etr = avail_evap;
				break;
			} // recharge switch

			if (etr > avail_evap) {
				etl = 0.0; // default value
				etr = avail_evap;
			}
			else
				etl = avail_evap - etr; // default value

			switch (soil_withdrawal_Tables[1][hh]) {  // handle lower layer
			case 1: //******sandy soil
				if (pctl < 0.25)
					etl = 0.5*pctl*etl;
				break;
			case 2: //******loam soil
				if (pctl < 0.5)
					etl = pctl * etl;
				break;
			case 3: //******clay soil
				if (pctl <= 0.33)
					etl = 0.5*pctl*etl;
				else if (pctr < 0.67)
					etl = pctl * etl;
				break;
			case 4: //******organic soil
					//         use default above etl = avail_evap - etr;
				break;
			} // lower switch

			  //******Soil moisture accounting  Remember that soil_moist includes soil_rechr[hh][hh]

			long et_type = cov_type[hh];

			//****** et_type = 0 - no evaporation, bare soil - cov_type = 0
			//****** et_type = 1 - recharge layer only, crops - cov_type = 1
			//****** et_type = 2 - all soil moisture, grasses & shrubs - cov_type = 2

			if (transp_limited[hh] == 1 && et_type == 2)
				et_type = 1;

			et = 0.0;

			switch (et_type) {  // handle evaporation
			case 0:   // avail_evap <= 0
				break;
			case -1:  // avail_evap <= 0
				break;
			case 1:
				if (etr > soil_rechr[hh]) {
					soil_rechr[hh] = 0.0;
					et = soil_rechr[hh];
				}
				else {
					soil_rechr[hh] = soil_rechr[hh] - etr;
					et = etr;
				}
				soil_moist[hh] = soil_moist[hh] - et;
				break;
			case 2:
				if (etr + etl >= soil_moist[hh]) {
					et = soil_moist[hh];
					soil_moist[hh] = 0.0;
					soil_rechr[hh] = 0.0;
				}
				else {
					et = etr + etl;
					soil_moist[hh] = soil_moist[hh] - et;

					if (etr > soil_rechr[hh]) {
						soil_rechr[hh] = 0.0;
					}
					else
						soil_rechr[hh] = soil_rechr[hh] - etr;
				}
				break;
			} // switch

			hru_actet[hh] += et;

		} // soil_moist[hh] > 0.0

		if (soil_moist_max[hh] <= 0.0 && Sdmax[hh] <= 0.0) // assume lake evaporation
			hru_actet[hh] = hru_evap_buf[hh]; // evaporate all

		hru_cum_actet[hh] += hru_actet[hh];

		if (nstep == 0) { // end of every day
			if (snowinfilDiv > 1) // daily value - ready for next day
				snowinfil_buf[hh] = snowinfil[hh] / snowinfilDiv;

			if (runoffDiv > 1) // daily value - ready for next day
				runoff_buf[hh] = runoff[hh] / runoffDiv;

			if (meltrunoffDiv > 1) // daily value - ready for next day
				meltrunoff_buf[hh] = meltrunoff[hh] / meltrunoffDiv;

			if (evapDiv > 1) // daily value - ready for next day
				hru_evap_buf[hh] = hru_evap[hh] / evapDiv;
		}
	} // for
}

void ClassSoilDS::finish(bool good) {

	float Allcum_soil_runoff = 0.0;
	float Allcum_soil_ssr = 0.0;
	float Allcum_rechr_ssr = 0.0;
	float Allcum_soil_gw = 0.0;
	float Allcum_gw_flow = 0.0;
	float Allcum_infil_act = 0.0;
	float Allcum_soil_moist_change = 0.0;
	float Allcum_Sd_change = 0.0;
	float Allcum_gw_change = 0.0;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_rechr_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_rechr[hh] - soil_rechr_Init[hh], hru_area[hh], basin_area[0], " *** information only - already included in 'soil_moist'.");
		LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist         (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' soil_moist_change  (mm) (mm*hru) (mm*hru/basin): ").c_str(), soil_moist[hh] - soil_moist_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' hru_cum_actet      (mm) (mm*hru) (mm*hru/basin): ").c_str(), hru_cum_actet[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_infil_act(all) (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_infil_act[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_gw        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_runoff    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_runoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_rechr_ssr      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_rechr_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_soil_ssr       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_soil_ssr[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' Sd_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), Sd[hh] - Sd_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_runoff_to_Sd   (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_runoff_to_Sd[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' gw                 (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' gw_change          (mm) (mm*hru) (mm*hru/basin): ").c_str(), gw[hh] - gw_Init[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_gw_flow        (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_gw_flow[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
		LogMessageA(hh, string("'" + Name + " (Soil)' cum_redirected_residual (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_redirected_residual[hh] / hru_area[hh], hru_area[hh], basin_area[0], " *** Added to this HRU surface runoff");
		LogDebug(" ");

		if (variation == VARIATION_1) {
			LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_culvert      (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert[hh], hru_area[hh], basin_area[0]);
			LogMessageA(hh, string("'" + Name + " (SoilDS)' cum_culvert_over (m3) (m3*hru) (m3*hru/basin): ").c_str(), cum_culvert_over[hh], hru_area[hh], basin_area[0]);
			LogDebug(" ");
		}

		Allcum_soil_runoff += cum_soil_runoff[hh] * hru_area[hh];
		Allcum_soil_ssr += cum_soil_ssr[hh] * hru_area[hh];
		Allcum_rechr_ssr += cum_rechr_ssr[hh] * hru_area[hh];
		Allcum_soil_gw += cum_soil_gw[hh] * hru_area[hh];
		Allcum_gw_flow += cum_gw_flow[hh] * hru_area[hh];
		Allcum_infil_act += cum_infil_act[hh] * hru_area[hh];
		Allcum_soil_moist_change += (soil_moist[hh] - soil_moist_Init[hh])*hru_area[hh];
		Allcum_Sd_change += (Sd[hh] - Sd_Init[hh])*hru_area[hh];
		Allcum_gw_change += (gw[hh] - gw_Init[hh])*hru_area[hh];
	}

	LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_runoff (mm*basin): ").c_str(), Allcum_soil_runoff);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_ssr (mm*basin): ").c_str(), Allcum_soil_ssr);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_rechr_ssr (mm*basin): ").c_str(), Allcum_rechr_ssr);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_gw (mm*basin): ").c_str(), Allcum_soil_gw);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_gw_flow (mm*basin): ").c_str(), Allcum_gw_flow);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_infil_act (mm*basin): ").c_str(), Allcum_infil_act);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_soil_moist_change (mm*basin): ").c_str(), Allcum_soil_moist_change);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_Sd_change (mm*basin): ").c_str(), Allcum_Sd_change);
	LogMessage(string("'" + Name + " (SoilDS)' Allcum_gw_change (mm*basin): ").c_str(), Allcum_gw_change);
	LogDebug(" ");
}

Classalbedoobs2* Classalbedoobs2::klone(string name) const {
	return new Classalbedoobs2(name);
}

void Classalbedoobs2::decl(void) {

	Description = "'Every interval sets the variable Albedo to the value of the observation Albedo_obs with enhancements.'";

	declstatvar("Albedo", NHRU, "Albedo()", "()", &Albedo);

	declvar("meltflag", NHRU, "meltflag = 1 - melt true", "()", &meltflag);

	declvar("winter", NHRU, "winter = 1 - true", "()", &winter);

	declvar("net_snowD", NHRU, "daily snow fall", "(mm/d)", &net_snowD);

	declvar("newsnowcnt", NHRU, "snow age count", "()", &newsnowcnt);


	decldiagparam("Albedo_bare", NHRU, "[0.17]", "0.0", "1.0", "albedo for bare ground", "()", &Albedo_bare); // pseudo

	decldiagparam("Albedo_snow", NHRU, "[0.85]", "0.0", "1.0", "albedo for fresh snow covered ground", "()", &Albedo_snow); // pseudo

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declreadobs("Albedo_obs", NHRU, "albedo observation", "()", &Albedo_obs, HRU_OBS_Q, true);


	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);
	declgetvar("*", "hru_newsnow", "()", &hru_newsnow);
	declgetvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
	declgetvar("*", "net_snow", "(mm/int)", &net_snow);
}

void Classalbedoobs2::init(void) {

	nhru = getdim(NHRU);

	if (Albedo_obs == NULL) {
		CRHMException TExcept("\"albedo_obs\". No observation albedo data!  Using calculated albedo instead.", WARNING);
		LogError(TExcept);
	}
	else {
		CRHMException TExcept("\"albedo_obs\". Using observation albedo data!.", WARNING);
		LogError(TExcept);
	}

	for (hh = 0; hh < nhru; ++hh) {
		if (SWE[hh] > 5.0) {
			Albedo[hh] = Albedo_snow[hh];
			winter[hh] = 1;
		}
		else {
			Albedo[hh] = Albedo_bare[hh];
			winter[hh] = 0;
		}
		net_snowD[hh] = 0.0;
		meltflag[hh] = 0;
		newsnowcnt[hh] = 0;
	}
}

void Classalbedoobs2::run(void) {

	long nstep, jday;

	nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) { // calculate daily snow accumulation

		if (nstep == 1 || Global::Freq == 1) // beginning of every day
			net_snowD[hh] = net_snow[hh];
		else
			net_snowD[hh] += net_snow[hh];
	}

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		jday = julian("now");

		for (hh = 0; chkStruct(); ++hh) {
			float hemisphere = (hru_lat[hh] < 0.0);
			if ((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
				winter[hh] = 1;
				Albedo[hh] = Albedo_snow[hh];
			}
		}

		for (hh = 0; chkStruct(); ++hh) {
			meltflag[hh] = 0;
			if (hru_newsnow[hh] > 0)
				newsnowcnt[hh] = 0;
			else
				newsnowcnt[hh] = newsnowcnt[hh] + 1;

			if (SWE[hh] <= 0.0) {
				Albedo[hh] = Albedo_bare[hh];
				winter[hh] = 0;
				meltflag[hh] = 0;
			}
			else { // SWE[hh] > 0.0

				float Qnc = -0.371 + 5.22*QdroD[hh] * (1 - Albedo[hh]);

				float MT = -0.064*jday + 6.69;

				if (hru_tmax[hh] < -6.0 && Qnc < 1.0) {
					winter[hh] = 1;
					if (hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 || hru_tmax[hh] > MT && Qnc > -0.5)
						meltflag[hh] = 1;
				}

				if (Albedo_obs)
					Albedo[hh] = Albedo_obs[hh]; // Albedo set internally by routine
				else
					albedo(jday, Qnc); // value

				if (!winter[hh]) {
					if (Albedo[hh] < Albedo_bare[hh])
						Albedo[hh] = Albedo_bare[hh];
					meltflag[hh] = 1;
				}
			} // SWE > 0.0
		} // for HRU
	} //end of every day
}

void Classalbedoobs2::albedo(long jday, float Qnc) {

	float DR = 0.071;

	if (SWE[hh] > 60.0 && Albedo[hh] > 0.65)
		DR = 0.015;

	if (SWE[hh] > 60.0 && Albedo[hh] < 0.65)
		DR = 0.001;

	if (net_snowD[hh] > 0.25) { // SF = SWE*2 if density 0.005 (0.5cm)
		Albedo[hh] = Albedo[hh] + net_snowD[hh] * 0.1*2.0; // daily value
		if (Albedo[hh] > Albedo_snow[hh])
			Albedo[hh] = Albedo_snow[hh];
	}

	if (winter[hh] == 1) {

		if (newsnowcnt[hh] < 3) {
			Albedo[hh] = Albedo[hh] - 0.05;
		}
		else {
			float MT = -0.064*jday + 6.69;

			if (hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 ||
				hru_tmax[hh] > MT && Qnc > -0.5) {
				Albedo[hh] = Albedo[hh] - DR;

			}
			else
				if (Albedo[hh] > 0.65)
					Albedo[hh] = Albedo[hh] - 0.006;
		}
	}
	else
		Albedo[hh] = Albedo[hh] - 0.02;
}


Classwinter_meltflag* Classwinter_meltflag::klone(string name) const {
	return new Classwinter_meltflag(name);
}

void Classwinter_meltflag::decl(void) {

	Description = "'Estimates the snow albedo during the winter and the melt period. Use with \"ebsm\".'";

	declvar("meltflag", NHRU, "meltflag = 1 - melt true", "()", &meltflag);

	declvar("winter", NHRU, "winter = 1 - true", "()", &winter);

	declparam("hru_lat", NHRU, "[51.317]", "-90.0", "90.0", "latitude. Negative values for Southern Hemisphere.", "(�)", &hru_lat);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);
	declgetvar("*", "SWE", "(mm)", &SWE);
	declgetvar("*", "QdroD", "(MJ/m^2*d)", &QdroD);
	declgetvar("*", "Albedo", "()", &Albedo);
}

void Classwinter_meltflag::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		if (SWE[hh] > 5.0)
			winter[hh] = 1;
		else
			winter[hh] = 0;

		meltflag[hh] = 0;
	}
}

void Classwinter_meltflag::run(void) {

	long nstep, jday;

	nstep = getstep() % Global::Freq;

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		jday = julian("now");

		for (hh = 0; chkStruct(); ++hh) {
			float hemisphere = (hru_lat[hh] < 0.0);
			if ((!hemisphere && (jday > 300 || jday < 2) || hemisphere && (jday > 117 || jday < 185)) && SWE[hh] > 5.0) {  // changed
				winter[hh] = 1;
			}
			continue;
		}

		for (hh = 0; chkStruct(); ++hh) {
			meltflag[hh] = 0;

			if (SWE[hh] <= 0.0) {
				winter[hh] = 0;
				meltflag[hh] = 0;
			}
			else { // SWE[hh] > 0.0

				float Qnc = -0.371 + 5.22*QdroD[hh] * (1 - Albedo[hh]);

				if (hru_tmax[hh] < -6.0 && Qnc < 1.0)
					winter[hh] = 1;

				if (winter[hh] == 1) {
					float MT = -0.064*jday + 6.69;

					if (hru_tmin[hh] > -4.0 || Qnc > 1.0 && hru_tmax[hh] > 0.0 || hru_tmax[hh] > MT && Qnc > -0.5) {
						meltflag[hh] = 1;
					}
				}
				else
					meltflag[hh] = 1;

			} // SWE > 0.0
		} // for HRU
	} //end of every day
}

Class_z_s_rho* Class_z_s_rho::klone(string name) const {
	return new Class_z_s_rho(name);
}

void Class_z_s_rho::decl(void) {

	Description = "'Required when pbsmSnobal used with glacier and glacier_org. Replaces z_s and rho normally supplied by module SnobalCRHM to pbsmSnobal.'";

	declstatvar("z_s", NHRU, "total snowcover thickness", "(m)", &z_s);

	declstatvar("rho", NHRU, "average snowcover density", "(kg/m^3)", &rho);

	declgetvar("*", "SWE", "(mm)", &SWE);

}

void Class_z_s_rho::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		z_s[hh] = 0.0;
		rho[hh] = 218.0; // 10/18/16
	}
}

void Class_z_s_rho::run(void) {

	float SWE_Max;

	for (hh = 0; chkStruct(); ++hh) {
		z_s[hh] = DepthofSnow(SWE[hh]); // returns zero if SWE <= 2.05 mm
		if (z_s[hh] > 0.0)
			rho[hh] = SWE[hh] / z_s[hh];
		else
			rho[hh] = 218.0; // 10/18/16
	}
}

Classtsurface* Classtsurface::klone(string name) const {
	return new Classtsurface(name);
}

void Classtsurface::decl(void) {

	Description = "'Module to calculate ground surface temperature ' \
    'use hru_t for surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use hru_t for surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57).' \
    'use previous daily mean snowpack temperature with thermal conductivity and energy of snowpack (***Snobal*** case) to estimate surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use previous daily mean hru_t with thermal conductivity and energy of snowpack (***ebsm*** case) to estimate surface temperature during snowcover period; use Radiative-Conductive-Convective approach to estimate surface temperature(Williams et al, 2015) during snow free periods.' \
    'use previous daily mean snowpack temperature with thermal conductivity and energy of snowpack (***Snobal*** case) to estimate surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57).' \
    'use previous daily mean hru_t with thermal conductivity and energy of snowpack (***ebsm*** case) to estimate surface temperature during snowcover period; use parameter n_factor to estimate surface temperature from the air temperature during snow free periods (Woo, 2012, p. 57). '";

	declvar("hru_tsf", NHRU, "surface/skin temperature", "(�C)", &hru_tsf);

	declvar("hru_tsf_D", NHRU, "mean daily surface/skin temperature", "(�C)", &hru_tsf_D);

	decldiag("hru_tsf_acc", NHRU, "mean daily surface/skin temperature", "(�C)", &hru_tsf_acc);

	declgetvar("*", "SWE", "(m)", &SWE);

	declgetvar("*", "hru_t", "(�C)", &hru_t);


	variation_set = VARIATION_2 + VARIATION_4; // Snobal

	decllocal("hru_T_s_D", NHRU, "mean daily surface/skin temperature", "(�C)", &hru_T_s_D);

	decllocal("hru_T_s_acc", NHRU, "sum interval air temperature from previous day", "(�C)", &hru_T_s_acc);

	declgetvar("*", "z_s", "(m)", &z_s);

	declgetvar("*", "rho", "(kg/m^3)", &rho);

	declgetvar("*", "T_s", "( �C)", &T_s);

	declgetvar("*", "G", "(W/m^2)", &G);


	variation_set = VARIATION_3 + VARIATION_5; // ebsm

	decllocal("hru_t_D", NHRU, "mean daily snowpack temperature from previous day", "(�C)", &hru_t_D);

	decllocal("hru_t_acc", NHRU, "sum interval air temperature from previous day", "(�C)", &hru_t_acc);

	declgetvar("*", "hru_tmin", "(�C)", &tmin);

	declgetvar("*", "snowdepth", "(m)", &snowdepth);


	variation_set = VARIATION_0 + VARIATION_2 + VARIATION_3;

	decllocal("Zdt_last", NHRU, "Last value of thaw depth", "(m)", &Zdt_last);

	declparam("W_a", NHRU, "[0.77]", "0.0", "1.5", "empirical constant for air temperature", "()", &W_a);

	declparam("W_b", NHRU, "[0.02]", "0.0", "0.1", "empirical constant for net radiation at ground surface", "()", &W_b);

	declparam("W_c", NHRU, "[7.0]", "0.0", "10.0", "empirical constant for frost table", "()", &W_c);

	declparam("W_d", NHRU, "[0.03]", "0.0", "0.1", "empirical constant for frost table", "()", &W_d);

	declgetvar("*", "netD", "(MJ/m^2*d)", &netD);

	declputvar("*", "Zdt", "(m)", &Zdt); // used as a get but allows Classtsurface to load before ClassXG


	variation_set = VARIATION_1 + VARIATION_4 + VARIATION_5;

	declparam("n_factor_a", NHRU, "[1.0]", "0", "1.2", "a constant in n_factor = n_factor_a - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_a);

	declparam("n_factor_b", NHRU, "[0.0]", "0.0", "1.0", "a constant in n_factor = n_factor_b - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_b);

	declparam("n_factor_c", NHRU, "[0.0]", "0.0", "0.1", "a constant in n_factor = n_factor_c - n_factor_b*exp(-n_factor_c*T) where T is days after start of ground thaw.", "()", &n_factor_c);

	decllocal("n_factor_T", NHRU, "Days after the start of thaw", "()", &n_factor_T);

	decllocal("n_factor", NHRU, "Calculated value of n_factor from parameters", "()", &n_factor);


	variation_set = VARIATION_2 + VARIATION_3 + VARIATION_4 + VARIATION_5;

	declvar("SWE_tc", NHRU, "SWE thermal conductivity", "(W/(m*K)", &SWE_tc);

	declvar("SWE_density", NHRU, "SWE density", "( kg/m^3)", &SWE_density);


	variation_set = VARIATION_ORG;
}

void Classtsurface::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; chkStruct(); ++hh) {
		hru_tsf_D[hh] = 0.0;
		hru_tsf_acc[hh] = 0.0;

		if (variation == VARIATION_3 || variation == VARIATION_5) { // ebsm
			hru_t_D[hh] = 0.0;
			hru_t_acc[hh] = 0.0;
		}

		if (variation == VARIATION_2 || variation == VARIATION_4) { // Snobal
			hru_T_s_D[hh] = 0.0;
			hru_T_s_acc[hh] = 0.0;
		}

		if (variation == VARIATION_2 || variation == VARIATION_3 || variation == VARIATION_4 || variation == VARIATION_5) {
			SWE_tc[hh] = 0.0;
			SWE_density[hh] = 0.0;
		}
	}
}

void Classtsurface::run(void) {

	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		if (SWE[hh] <= 0.0) { // bare ground
			if (variation == VARIATION_ORG || variation == VARIATION_2 || variation == VARIATION_3) {
				if (Zdt[hh] > Zdt_last[hh])
					Zdt_last[hh] = Zdt[hh];
				float Qn = netD[hh] * 1E6 / 86400; // MJ/m^2*d to W/m^2
				hru_tsf[hh] = (W_a[hh] * hru_t[hh] + W_b[hh] * Qn)*atan(W_c[hh] * (Zdt_last[hh] + W_d[hh]))*2.0 / M_PI;
			}
			else if (variation == VARIATION_1 || variation == VARIATION_4 || variation == VARIATION_5) {
				n_factor_T[hh] += 1.0 / Global::Freq;

				n_factor[hh] = n_factor_a[hh] - n_factor_b[hh] * exp(-n_factor_c[hh] * n_factor_T[hh]);

				if (n_factor[hh] >= 0.0)
					hru_tsf[hh] = hru_t[hh] * n_factor[hh];
				else
					hru_tsf[hh] = 0.0;
			}
		}
		else { // has snowcover
			if (variation == VARIATION_1)
				n_factor_T[hh] = 0.0;
			if (variation == VARIATION_2 || variation == VARIATION_4) { // SnobalCRHM case
				SWE_density[hh] = rho[hh];
				if (SWE_density[hh] < 156)  // Sturm et al. 1997. The thermal conductivity of seasonal snow
					SWE_tc[hh] = 0.023 - 1.01* SWE_density[hh] / 1000.0 + 0.234*sqr(SWE_density[hh] / 1000.0);
				else
					SWE_tc[hh] = 0.138 - 1.01* SWE_density[hh] / 1000.0 + 3.233*sqr(SWE_density[hh] / 1000.0);
				hru_tsf[hh] = hru_T_s_D[hh] - G[hh] * 0.5*z_s[hh] / SWE_tc[hh];
			}

			if (variation == VARIATION_3 || variation == VARIATION_5) { // ebsm case
				if (snowdepth[hh] > 0.0)
					SWE_density[hh] = SWE[hh] / snowdepth[hh];
				else
					SWE_density[hh] = 0.0;

				if (SWE_density[hh] < 156)  // Sturm et al. 1997. The thermal conductivity of seasonal snow
					SWE_tc[hh] = 0.023 - 1.01* SWE_density[hh] / 1000.0 + 0.234*sqr(SWE_density[hh] / 1000.0);
				else
					SWE_tc[hh] = 0.138 - 1.01* SWE_density[hh] / 1000.0 + 3.233*sqr(SWE_density[hh] / 1000.0);

				float t_minus = tmin[hh];

				if (tmin[hh] >= 0.0)
					t_minus = 0.0;

				float umin = SWE[hh] * (2.115 + 0.00779*t_minus)*t_minus / 1000.0;

				hru_tsf[hh] = hru_t_D[hh] - (umin*1E6 / 86400)*snowdepth[hh] / SWE_tc[hh]; // 1E6/86400 is conversion: MJ/m^2*d to W/m^2
			}

			if (hru_t[hh] > 0.0) // ignore plus temperatures when snow covered
				hru_tsf[hh] = 0.0;
			else
				hru_tsf[hh] = hru_t[hh];
		}

		if (nstep == 0) {
			hru_tsf_D[hh] = hru_tsf_acc[hh];
			hru_tsf_acc[hh] = 0.0;

			if (variation == VARIATION_3 || variation == VARIATION_5) { // ebsm
				hru_t_D[hh] = hru_t_acc[hh] / Global::Freq;
				hru_t_acc[hh] = 0.0;
			}

			if (variation == VARIATION_2 || variation == VARIATION_4) { // Snobal
				hru_T_s_D[hh] = hru_T_s_acc[hh] / Global::Freq;
				hru_T_s_acc[hh] = 0.0;
			}
		}

		hru_tsf_acc[hh] += hru_tsf[hh];

		if (variation == VARIATION_3 || variation == VARIATION_5) // ebsm
			hru_t_acc[hh] += hru_t[hh];

		if (variation == VARIATION_2 || variation == VARIATION_4) // Snobal
			hru_T_s_acc[hh] += T_s[hh];

	} // for
}
//---------------------------------------------------------------------------

Classqdrift* Classqdrift::klone(string name) const {
	return new Classqdrift(name);
}

void Classqdrift::decl(void) {

	Description = "'Generates the drift melt from hummock-covered hillslopes in the Arctic tundra. CRHM compatible.' \
                 'using using observation \"p\" original version. ' \
                 'using using variable \"hru_p\" to be CRHM compatible. '";

	Global::OBS_AS_IS = 1; // ClassModule uses only intvl for NFREQ observation reads

	declvar("SWE", NHRU, "mean snow water equivalent over HRU", "(mm)", &SWE);

	decllocal("driftmeltOrg", NHRU, "snow melt without delay", "(m^3/int)", &driftmelt); // pack

	declvar("driftmelt", NHRU, "snow melt with delay", "(m^3/int)", &driftmeltDly); // with delay

	decllocal("cumdriftmeltOrg", NHRU, "cumulative snow melt", "(km^3)", &cumdriftmelt); // pack

	declvar("driftmeltD", NHRU, "daily snow melt with delay", "(m^3/d)", &driftmeltD); // with delay

	declvar("snowmeltD", NHRU, "daily snow melt with delay", "(m^3/d)", &snowmeltD); // with delay

	declvar("cumdriftmelt", NHRU, "cumulative snow melt with delay", "(m^3)", &cumdriftmeltDly); // with delay


	declparam("DrainTo", NHRU, "[0]", "0", "20", " drift drain to hru, 0=NOWHERE, otherwise HRU# (1->MAXHRU)", "()", &DrainTo);

	declparam("InitSWE", NHRU, "[0.0]", "0", "1E3", "initial mean snow water equivalent", "(mm)", &InitSWE);

	declparam("length", NHRU, "[1]", "1", "1E4", "length normal to creek", "(m)", &length);

	declparam("meltstorage", NHRU, "[0]", "0", "20", "melt Storage", "(d)", &meltstorage);

	declparam("meltLag", NHRU, "[0]", "0", "48", "melt delay", "(h)", &meltLag);


	declgetvar("*", "Qm", "(MJ/m^2*int)", &Qm);


	variation_set = VARIATION_0;

	declreadobs("p", NOBS, "precipitation", "(mm/int)", &p, true); // share location

	declparam("Type", NHRU, "[NOTUSED]", "0", "2", "hru land type, 0=NOTUSED/1=DRIFT/2=HUMMOCK", "()", &Type);


	variation_set = VARIATION_1;

	declgetvar("*", "hru_p", "(mm/int)", &hru_p);


	variation_set = VARIATION_ORG;
}

void Classqdrift::init(void) {

	nhru = getdim(NHRU);

	Delaymelt = new ClassClark(driftmelt, driftmeltDly, meltstorage, meltLag, nhru);

	for (int hh = 0; hh < nhru; ++hh) {
		driftmelt[hh] = 0.0;
		cumdriftmelt[hh] = 0.0;
		driftmeltDly[hh] = 0.0;
		driftmeltD[hh] = 0.0;
		snowmeltD[hh] = 0.0;
		cumdriftmeltDly[hh] = 0.0;

		SWE[hh] = InitSWE[hh];

		if (hh == 0) LogDebugT("Initial");

		if (variation == VARIATION_0 && Type[hh] != DRIFT)
			continue;  // drift

		float c = 0.0;
		if (SWE[hh] > 0.0)
			c = length[hh] * InitSWE[hh] / 1E3;
		LogMessageA(hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length[hh]);
	}
}

void Classqdrift::run(void) {

	for (int hh = 0; hh < nhru; ++hh) {

		if ((getstep() % Global::Freq) == 1) driftmeltD[hh] = 0.0; // reset beginning of day

		if (variation == VARIATION_0 && Type[hh] != DRIFT)
			continue;  // drift

		driftmelt[hh] = 0.0;

		if (SWE[hh] > 0.0) { // still drift

			if (Qm[hh] > 0.0) {
				float melt = Qm[hh] / 334.4*1E3;

				if (melt > SWE[hh]) {
					melt = SWE[hh];
					SWE[hh] = 0.0;
				}
				else
					SWE[hh] -= melt;

				float lastcumdriftmelt = cumdriftmelt[hh];  // following avoids round off error
				cumdriftmelt[hh] = length[hh] * InitSWE[hh] * (1.0 - sqr(SWE[hh] / InitSWE[hh])); // (mm.l)
				driftmelt[hh] = (cumdriftmelt[hh] - lastcumdriftmelt) / 1E3; // (m3/Int)
			}
		}

		if (variation == VARIATION_ORG) {
			if (p != NULL) // handle precipitation
				driftmelt[hh] += (p[0] * length[hh]);
		}
		else if (variation == VARIATION_1)
			driftmelt[hh] += (hru_p[0] * length[hh]);

	} // for loop

	Delaymelt->DoClark();

	for (hh = 0; hh < nhru; ++hh) {
		if (variation == VARIATION_ORG && Type[hh] != DRIFT)
			continue;  // drift
		cumdriftmeltDly[hh] += driftmeltDly[hh];
		driftmeltD[hh] += driftmeltDly[hh];
		snowmeltD[hh] = driftmeltD[hh];
	}
}

void Classqdrift::finish(bool good) {

	for (hh = 0; hh < nhru; ++hh) {

		if (hh == 0) LogDebugT("Final");

		if (variation == VARIATION_ORG && Type[hh] != DRIFT)
			continue;  // drift

		float c = 0.0;
		if (SWE[hh] > 0.0)
			c = length[hh] * InitSWE[hh] * sqr(SWE[hh] / InitSWE[hh]) / 1E3;
		LogMessageA(hh, "(Drift  ) - water content (m^3) (m/m^2): ", c, length[hh]);
		LogMessageA(hh, "(Drift  ) - water storage (m^3) (m/m^2): ", Delaymelt->Left(hh), length[hh]);
		LogDebug(" ");
	}

	delete Delaymelt;
}

Classqmelt* Classqmelt::klone(string name) const {
	return new Classqmelt(name);
}

void Classqmelt::decl(void) {

	Description = "'Generates the drift and ground melt from hummock-covered hillslopes in the Arctic tundra. Original version but now CRHM compatible.' \
                 'using using observations \"ta\" (changed from t to avoid conflict with obs module) and \"ts\". '";

	Global::OBS_AS_IS = 1; // ClassModule uses only intvl for NFREQ observation reads

	declvar("Qm", NHRU, "degree day/daily mean air temperature/partitioned", "(MJ/m^2*int)", &Qm);

	declvar("Qg", NHRU, "degree day/daily mean skin temperature/partitioned", "(MJ/m^2*int)", &Qg);

	declvar("cum_Qm", NHRU, "cumulative melt flux from degree day/daily mean air temperature/partitioned", "(MJ/m^2)", &cum_Qm);

	declvar("cum_Qg", NHRU, "cumulative ground flux from degree day/daily mean skin temperature/partitioned", "(MJ/m^2)", &cum_Qg);

	decllocal("QmD", NHRU, "daily melt from degree day/daily mean air temperature", "(MJ/m^2)", &QmD);

	decllocal("QgD", NHRU, "daily ground flux from degree day/daily mean skin temperature", "(MJ/m^2)", &QgD);

	declparam("TIa0Mn", NHRU, "[0.0]", "-10", "10", "Qm: degree day/daily mean air temperature", "(�C)", &TIa0Mn);

	declparam("TIa1Mn", NHRU, "[0.8844, 0.0]", "0", "10", "Qm: degree day/daily mean air temperature", "(MJ/d*�C)", &TIa1Mn);

	declparam("TIs0Mn", NHRU, "[0.0]", "-10", "10", "Qg: degree day/daily mean skin temperature", "(�C)", &TIs0Mn);

	declparam("TIs1Mn", NHRU, "[0.0, 0.2]", "0", "10", "Qg: degree day/daily mean skin temperature", "(MJ/d*�C)", &TIs1Mn);


	declreadobs("ta", NOBS, "air temperature", "(�C)", &t);

	declreadobs("ts", NOBS, "skin temperature", "(�C)", &ts);


	declobsfunc("ta", "Tmean", &tmean, AVG);
	declobsfunc("ts", "Tsmean", &tsmean, AVG);
	declobsfunc("ta", "Tpos", &tpos, POS);
	declobsfunc("ts", "Tspos", &tspos, POS);
}

void Classqmelt::init(void) {

	nhru = getdim(NHRU);

	for (long hh = 0; hh < nhru; ++hh) {
		cum_Qg[hh] = 0.0;
		cum_Qm[hh] = 0.0;
		QmD[hh] = 0.0;
		QgD[hh] = 0.0;
	}
}

void Classqmelt::run(void) {

	bool start = getstep() % Global::Freq == 1;

	if (start) { // calculate daily regression

		for (hh = 0; chkStruct(); ++hh) {
			if (tmean[0] - TIa0Mn[hh] > 0.0)
				QmD[hh] = (tmean[0] - TIa0Mn[hh])*TIa1Mn[hh];   // mean air temperature degree day
			else
				QmD[hh] = 0.0;

			if (tsmean[0] - TIs0Mn[hh] > 0.0)
				QgD[hh] = (tsmean[0] - TIs0Mn[hh])*TIs1Mn[hh];  // mean skin temperature degree day
			else
				QgD[hh] = 0.0;
		}
	}

	for (hh = 0; chkStruct(); ++hh) {

		if (ts[0] > 0.0 && tsmean[0] > 0.0)
			Qg[hh] = QgD[hh] * ts[0] / tspos[0];  // distribute daily to interval
		else
			Qg[hh] = 0.0;

		cum_Qg[hh] += Qg[hh];

		if (t[0] > 0.0 && tmean[0] > 0.0)
			Qm[hh] = QmD[hh] * t[0] / tpos[0];  // distribute daily to interval
		else
			Qm[hh] = 0.0;

		cum_Qm[hh] += Qm[hh];
	}
}

Classquinton* Classquinton::klone(string name) const {
	return new Classquinton(name);
}

void Classquinton::decl(void) {

	Description = "'Handles the subsurface drainage from hummock-covered hillslopes in the Arctic tundra. CRHM compatible.' \
                 'using using observation \"p\" original version. ' \
                 'using using variable \"hru_p\" to be CRHM compatible. '";

	Global::OBS_AS_IS = 1; // ClassModule uses only intvl for NFREQ observation reads

	declvar("Depth", NHRU, "water depth above the frost table.", "(m)", &Depth);

	declvar("theta", NLAY, "volumetric soil moisture.", "(m^3/m^3)", &theta, &theta_lay);

	declvar("layerwater", NLAY, "depth of drainable liquid water in layer.", "(m)", &layerwater, &layerwater_lay);

	declvar("capillary", NLAY, "depth of capillary liquid water in layer.", "(m)", &capillary, &capillary_lay);

	declvar("tension", NLAY, "tension in layer.", "(m)", &tension, &tension_lay);

	declvar("dmelt", NHRU, "frost table depth from surface.", "(m)", &dmelt);

	declvar("k", NHRU, "hydraulic conductivity.", "(m/d)", &k);

	declvar("d_surface", NHRU, "water depth used to calculate horizontal hydraulic conductivity.", "(m)", &d_surface);

	declvar("watertable", NHRU, "depth of the water table surface from the ground surface.", "(m)", &watertable);

	declvar("flowin", NHRU, "flow into HRU depth (water only).", "(m/m^2*int)", &flowin);

	declvar("flowinm3", NHRU, "flow into HRU depth.", "(m^3/int)", &flowinm3);

	declvar("cumflowin", NHRU, "cumulative flow into HRU depth (water only).", "(m/m^2)", &cumflowin);

	declvar("loss", NHRU, "water loss from all layers (water only).", "(m/m^2*int)", &loss);

	declvar("transit", NHRU, "transit time through HRU.", "(d)", &transit);

	decllocal("runoffI", NHRU, "runoff from HRU no delay.", "(m/m^2*int)", &runoff);

	declvar("runoff", NHRU, "runoff from HRU delayed (water only).", "(m/m^2*int)", &runoffDly);

	declvar("runoffm3", NHRU, "runoff from HRU delayed.", "(m^3/int)", &runoffm3Dly);

	declvar("cumrunoff", NHRU, "cumulative runoff from HRU delayed.", "(m/m^2)", &cumrunoff);

	decllocal("flowI", NHRU, "flow from all layers no delay.", "(m/m^2*int)", &flow);

	declvar("flow", NHRU, "flow from all layers delayed (water only).", "(m/m^2*int)", &flowDly);

	declvar("flowm3", NHRU, "flow from all layers delayed.", "(m^3/int)", &flowm3Dly);

	declvar("cumflow", NHRU, "cumulative flow from all layers delayed (water only).", "(m/m^2)", &cumflow);

	declvar("Cvis", NLAY, "Heat capacity sat/frozen.", "(J/m^3*K)", &Cvis, &Cvis_lay);

	declvar("Cvisa", NLAY, "Heat capacity unsat/frozen.", "(J/m^3*K)", &Cvisa, &Cvisa_lay);

	declvar("Cvws", NLAY, "Heat capacity sat/unfrozen.", "(J/m^3*K)", &Cvws, &Cvws_lay);

	declvar("Cvwsa", NLAY, "Heat capacity unsat/unfrozen.", "(J/m^3*K)", &Cvwsa, &Cvwsa_lay);

	declvar("lamis", NLAY, "Thermal conductivity sat/frozen.", "(W/m*K)", &lamis, &lamis_lay);

	declvar("lamws", NLAY, "Thermal conductivity sat/unfrozen.", "(W/m*K)", &lamws, &lamws_lay);

	declvar("lamwsa", NLAY, "Thermal conductivity unsat/unfrozen.", "(W/m*K)", &lamwsa, &lamwsa_lay);

	declvar("wDrained", NHRU, "depth of drained frozen organic material from surface.", "(m)", &wDrained);

	decllocal("tlayer", NLAY, "layer temperature.", "(�C)", &tlayer, &tlayer_lay);


	declparam("Type", NHRU, "drift, [HUMMOCK]", "0", "2", "hru land type, 0=NOTUSED/1=DRIFT/2=HUMMOCK.", "()", &Type);

	declparam("DrainTo", NHRU, "[0]", "0", "20", " drift drains to hru, 0=NOWHERE, otherwise HRU# (1->MAXHRU).", "()", &DrainTo);

	declparam("soil_type", NLAY, "[0, 1, 2]", "0", "4",
		"HRU soil type: 0 = loam1, 1 = loam2, 2 = loam3, 3 = sand, 4 = clay.", "()", &soil_type, &soil_type_lay);

	declparam("Pors", NDEF, "0.96, 0.9, 0.87, 0.43, 0.43", "0.0", "1.0", "porosity at layer depths.", "(m^3/m^3)", &Pors, &Pors_def, CLAY + 1);

	declparam("d", NLAY, "[0.15] , [0.1], [0.1] ,[0.1]", "0.0", "100.0", "layer depth.", "(m)", &d, &d_lay);

	declparam("tinit", NLAY, "[-8.0] , [-8.0], [-8.0] ,[-8.0]", "-40.0", "10.0", "initial layer temperature.", "(�C)", &tinit, &tinit_lay);

	declparam("slope", NHRU, "[0.01]", "0.0", "1.0", "slope.", "(m/m)", &slope);

	declparam("length", NHRU, "[1]", "1", "1E4", "length normal to creek", "(m)", &length);

	declparam("K_btm", NHRU, "[1.4]", "0.6", "2.5", "horizontal bottom hydraulic conductivity.", "(m/d)", &Kbtm);

	declparam("K_top", NHRU, "[360]", "30", "1200", "horizontal top hydraulic conductivity.", "(m/d)", &Ktop);

	declparam("z_trn", NHRU, "[0.15]", "0.12", "0.18", "hydraulic conductivity transition depth.", "(m)", &ztrn);

	declparam("Residual", NLAY, "[0.5], [0.8], [0.8]", "0.0", "1.0", "Organic non-drainable porosity.", "(m^3/m^3)", &Residual, &Residual_lay);

	declparam("n", NLAY, "[2], [1.6], [1.6]", "0.0", "10.0", "empirical constant.", "()", &n_const, &n_const_lay);

	declparam("a", NLAY, "[25], [15], [15]", "0.0", "50.0", "empirical constant for alpha.", "()", &a_const, &a_const_lay);

	declparam("Drained", NHRU, "[0.0]", "0.0", "1.0", "depth of saturated organic material(ice or water).", "(m)", &Drained);

	declparam("FrozenTo", NHRU, "[0.0]", "0.0", "1.0", "initial depth of frost table.", "(m)", &FrozenTo);

	declparam("runoffstorage", NHRU, "[0]", "0", "20", "runoff Storage.", "(d)", &runoffstorage);

	declparam("runoffLag", NHRU, "[0]", "0", "48", "runoff delay.", "(h)", &runoffLag);

	declparam("flowstorage", NHRU, "[0]", "0", "20", "flow Storage.", "(d)", &flowstorage);

	declparam("flowLag", NHRU, "[0]", "-1", "192", "flow delay.", "(h)", &flowLag);



	declgetvar("*", "Qg", "(MJ/m^2*d)", &Qg);

	declgetvar("Qdrift", "driftmelt", "(mm/int)", &driftmelt);


	variation_set = VARIATION_0;

	declreadobs("p", NOBS, "precipitation", "(mm/int)", &p, true);


	variation_set = VARIATION_1;

	declgetvar("*", "hru_p", "(mm/int)", &hru_p);


	variation_set = VARIATION_ORG;
}

void Classquinton::init(void) {

	nlay = getdim(NLAY);

	Delayrunoff = new ClassClark(runoff, runoffDly, runoffstorage, runoffLag, nhru); // input runoff
	Delayflow = new ClassClark(flow, flowDly, flowstorage, flowLag, nhru); // flow from soil layers

	for (int nn = 0; nn <= CLAY; ++nn)
		if (Pors_def[nn][0] > 0.0)
			const_cast<float*> (por_s)[nn] = Pors_def[nn][0];

	for (hh = 0; chkStruct(); ++hh) {

		Depth[hh] = 0.0;
		flowin[hh] = 0.0;
		cumflowin[hh] = 0.0;
		flow[hh] = 0.0;
		flowDly[hh] = 0.0;
		cumflow[hh] = 0.0;
		runoff[hh] = 0.0;
		runoffDly[hh] = 0.0;
		cumrunoff[hh] = 0.0;
		loss[hh] = 0.0;
		k[hh] = 0.0;
		d_surface[hh] = 0.0;
		watertable[hh] = 0.0;
		transit[hh] = 0.0;
		dmelt[hh] = FrozenTo[hh];

		float DrainD = Drained[hh];
		bool AsWater = FrozenTo[hh] > Drained[hh]; // frost table below drained table

		if (!AsWater) // pre-thaw
			wDrained[hh] = Drained[hh];
		else
			wDrained[hh] = 0.0;

		float d_cum = 0.0; // top of layer

		for (int nn = 0; nn < nlay; ++nn) {

			if (Residual_lay[nn][hh] >= por_s[soil_type_lay[nn][hh]] && Type[hh] == HUMMOCK) {
			 string S = "residual cannot be greater or equal to the layer porosity in HRU " +
					std::to_string(hh + 1) + ", layer " + std::to_string(nn + 1);
				CRHMException TExcept(S.c_str(), TERMINATE);
				LogError(TExcept);
			}

			theta_lay[nn][hh] = 0.0;
			layerwater_lay[nn][hh] = 0.0;
			capillary_lay[nn][hh] = 0.0;
			tension_lay[nn][hh] = 0.0;

			// if not frozen move water to capillary
			if (AsWater) {
				if (Drained[hh] <= d_cum + d_lay[nn][hh] && Drained[hh] > d_cum) {
					// water table in this layer
					if (FrozenTo[hh] >= d_cum + d_lay[nn][hh])  // frost table below layer
						capillary_lay[nn][hh] = (d_cum + d_lay[nn][hh] - Drained[hh]);
					else if (FrozenTo[hh] < d_cum + d_lay[nn][hh])  // frost table in layer
						capillary_lay[nn][hh] = (FrozenTo[hh] - Drained[hh]);

					Depth[hh] = FrozenTo[hh] - Drained[hh];
					d_surface[hh] = FrozenTo[hh] - Depth[hh] / 2.0;
					watertable[hh] = FrozenTo[hh] - Depth[hh];
				}
				else if (Drained[hh] < d_cum && FrozenTo[hh] > d_cum) { // water table above this layer
					if (FrozenTo[hh] >= d_cum + d_lay[nn][hh])
						capillary_lay[nn][hh] += d_lay[nn][hh]; // frost table below layer
					else
						capillary_lay[nn][hh] += FrozenTo[hh] - d_cum; // frost table in layer
				}
			}
			d_cum += d_lay[nn][hh];

			tlayer_lay[nn][hh] = tinit_lay[nn][hh];

			Cvis_lay[nn][hh] = 0.0;
			Cvisa_lay[nn][hh] = 0.0;
			Cvws_lay[nn][hh] = 0.0;
			Cvwsa_lay[nn][hh] = 0.0;

			lamis_lay[nn][hh] = 0.0;
			lamws_lay[nn][hh] = 0.0;
			lamwsa_lay[nn][hh] = 0.0;

		} // for layers

		if (Type[hh] != HUMMOCK) continue;  // drift

		float c = 0.0;
		d_cum = 0.0; // bottom of layer
		float Top; // residual depth above Drained - residual
		float Bot; // residual depth below Drained - saturated

		DrainD = Drained[hh];

		for (int nn = 0; nn < nlay; ++nn) {
			d_cum += d_lay[nn][hh];
			Top = 0.0; Bot = 0.0;

			// does not matter if frozen or unfrozen
			if (DrainD >= d_cum) // all residual
				Top = d_lay[nn][hh];
			else if (DrainD <= (d_cum - d_lay[nn][hh])) // all saturated
				Bot = d_lay[nn][hh];
			else { // mixed
				Bot = d_cum - DrainD;
				Top = d_lay[nn][hh] - Bot;
			}

			c += Top * Residual_lay[nn][hh];
			c += Bot * por_s[soil_type_lay[nn][hh]];

		} // for layers

		LogMessageA(hh, "(Hummock) - water content (m^3) (m/m^2): ", c*length[hh], length[hh]);
	} // for nhru
}

void Classquinton::run(void) {

	for (hh = 0; chkStruct(); ++hh) {

		if (Type[hh] != HUMMOCK) continue;

		for (int nn = 0; nn < nlay; ++nn) {

			Cvis_lay[nn][hh] = Cv_i * por_s[soil_type_lay[nn][hh]] // frozen/saturated
				+ Cv_s[soil_type_lay[nn][hh]] * (1.0 - por_s[soil_type_lay[nn][hh]]);

			Cvisa_lay[nn][hh] = Cv_i * Residual_lay[nn][hh] // frozen/unsaturated - drained to residual
				+ Cv_s[soil_type_lay[nn][hh]] * (1.0 - por_s[soil_type_lay[nn][hh]])
				+ Cv_a * (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);

			Cvws_lay[nn][hh] = Cv_w * por_s[soil_type_lay[nn][hh]] // unfrozen/saturated
				+ Cv_s[soil_type_lay[nn][hh]] * (1.0 - por_s[soil_type_lay[nn][hh]]);

			Cvwsa_lay[nn][hh] = Cv_w * Residual_lay[nn][hh] // unfrozen/unsaturated - drained to residual
				+ Cv_s[soil_type_lay[nn][hh]] * (1.0 - por_s[soil_type_lay[nn][hh]])
				+ Cv_a * (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);

			float Xs = 1.0 - por_s[soil_type_lay[nn][hh]];
			float Xw = por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh];
			float Xa = 1.0 - Xs - Xw; // also equals PR

			float n = por_s[soil_type_lay[nn][hh]];

			float ga;
			if (Xw >= 0.09)
				ga = 0.333 - Xa / n * (0.333 - 0.035);
			else
				ga = 0.013 + 0.944*Xw;

			float gc = 1.0 - 2.0*ga;

			float Fs = 1.0 / 3.0*(2.0 / (1 + (ks_s[soil_type_lay[nn][hh]] / lam_w - 1.0)*0.125)
				+ (1.0 / ((1 + (ks_s[soil_type_lay[nn][hh]] / lam_w - 1.0)*0.75))));

			float Fa = 1.0 / 3.0*(2.0 / (1 + (lam_a / lam_w - 1.0)*ga) + (1.0 / ((1 + (lam_a / lam_w - 1.0)*gc))));

			float a = Farouki_a(por_s[soil_type_lay[nn][hh]]);

			lamis_lay[nn][hh] = lam_i * a*a + lam_s[soil_type_lay[nn][hh]] * sqr(1.0 - a)
				+ lam_s[soil_type_lay[nn][hh]] * lam_i*(2 * a - 2 * sqr(a))
				/ (lam_s[soil_type_lay[nn][hh]] * a + lam_i * (1.0 - a));

			lamws_lay[nn][hh] = lam_w * a*a + lam_s[soil_type_lay[nn][hh]] * sqr(1.0 - a)
				+ lam_s[soil_type_lay[nn][hh]] * lam_w*(2 * a - 2 * sqr(a))
				/ (lam_s[soil_type_lay[nn][hh]] * a + lam_w * (1.0 - a));

			lamwsa_lay[nn][hh] = (Xw*lam_w + Fa * Xa*lam_a + Fs * Xs*lam_s[soil_type_lay[nn][hh]])
				/ (Xw + Fa * Xa + Fs * Xs);
		} // for layers

		float d_cum = 0.0; // bottom of layer
		float Top; // residual depth above Drained - residual
		float Bot; // residual depth below Drained - saturated
		float DrainD = wDrained[hh]; // zero if unfrozen

		if (Qg[hh] > 0.0) {

			float Energy = Qg[hh] * 1.0E6; // work in Joules

			for (int nn = 0; nn < nlay; ++nn) {

				d_cum += d_lay[nn][hh];

				if (dmelt[hh] >= d_cum) continue; // layer thawed

				Top = 0.0; Bot = 0.0;

				if (DrainD - d_cum >= 0.0) // all residual
					Top = d_lay[nn][hh];
				else if (DrainD - (d_cum - d_lay[nn][hh]) <= 0.0) // all saturated
					Bot = d_lay[nn][hh];
				else { // mixed
					Top = DrainD - (d_cum - d_lay[nn][hh]);
					Bot = d_cum - DrainD;
				}

				if (Top > 0.0 && dmelt[hh] < d_cum - Bot) {  // handle residual in top layer
															 // Calculate the melt depth for this interval and this layer

					float d = Energy / (-tlayer_lay[nn][hh] * Cvisa_lay[nn][hh] +
						Hf * 1e3*Residual_lay[nn][hh]); // (m)

					if ((d + dmelt[hh]) > d_cum) { // all layer melted

												   // actual volume of water melted m.m2
						float dif = d_cum - dmelt[hh];

						// energy used to melt remaining ice in this layer
						float used = (-tlayer_lay[nn][hh] * Cvisa_lay[nn][hh]
							+ Hf * 1e3*Residual_lay[nn][hh])*dif; // (m)
						Energy -= used;
						dmelt[hh] = d_cum;
						capillary_lay[nn][hh] += 0.0; // for documentation purposes only
						continue; // layer melted
					}
					else { // partial layer melt
						dmelt[hh] += d;
						capillary_lay[nn][hh] += 0.0; // for documentation purposes only
						break;  // energy all used up
					}
				} // if(Top > 0.0 && dmelt[hh] < d_cum - Bot)

				if (Bot > 0.0) { // handle saturated bottom

					float d = Energy / (-tlayer_lay[nn][hh] * Cvis_lay[nn][hh]
						+ Hf * 1e3*por_s[soil_type_lay[nn][hh]]); // (m)

					if ((d + dmelt[hh]) > d_cum) { // all layer melted

												   // actual volume of water melted m.m2
						float dif = d_cum - dmelt[hh];

						// energy used to melt remaining ice in this layer
						float used = (-tlayer_lay[nn][hh] * Cvis_lay[nn][hh]
							+ Hf * 1e3*por_s[soil_type_lay[nn][hh]])*dif; // (m)
						Energy -= used;
						dmelt[hh] = d_cum;
						capillary_lay[nn][hh] += dif;
					}
					else { // partial layer melt
						dmelt[hh] += d;
						capillary_lay[nn][hh] += d;
						break;  // energy all used up
					}
				} // if(Bot > 0.0)
			} // for layers
		} // if(Qg[hh] > 0.0)

		  // if water table blow Drained - disable drained
		if (wDrained[hh] > 0 && dmelt[hh] >= wDrained[hh])
			wDrained[hh] = 0.0;

		// calculate water depth above the frost table

		Depth[hh] = 0.0;
		flow[hh] = 0.0;
		d_cum = 0.0; // top of layer

		for (int nn = 0; nn < nlay; ++nn) {
			if (dmelt[hh] <= d_cum) break; // skip if fozen

			d_cum += d_lay[nn][hh];

			tension_lay[nn][hh] = 0.0;

			if (n_const_lay[nn][hh] > 0.001) { // use Van Genuchten

				float m = 1.0 - 1.0 / n_const_lay[nn][hh];
				float alph = a_const_lay[nn][hh] * m - 1.0;
				// bubbling pressure = 1/alph
				float fieldtheta = (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh])*pow(2.0f, -m);
				float thawedthislayer = dmelt[hh] - (d_cum - d_lay[nn][hh]);

				if (thawedthislayer > d_lay[nn][hh])
					thawedthislayer = d_lay[nn][hh];

				if (capillary_lay[nn][hh] / thawedthislayer > fieldtheta) {
					float drain = (capillary_lay[nn][hh] - thawedthislayer * fieldtheta);
					if (drain > capillary_lay[nn][hh]) drain = capillary_lay[nn][hh];
					layerwater_lay[nn][hh] += drain;
					capillary_lay[nn][hh] -= drain;
				}

				if (capillary_lay[nn][hh] > 0.0) {
					float tension;
					if (d_surface[hh] > d_cum) // water table below layer
						tension = (d_surface[hh] - d_cum) + d_lay[nn][hh]; //
					else if (d_surface[hh] > d_cum - d_lay[nn][hh])// in layer
						tension = (d_surface[hh] - (d_cum - d_lay[nn][hh])); //
					else
						tension = 0.0;

					tension_lay[nn][hh] = tension;

					if (tension > 1.0 / alph) { // greater than bubbling pressure
						float theta = (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh])
							*pow(1.0f + pow(alph*tension, n_const_lay[nn][hh]), -m);
						float excess = capillary_lay[nn][hh]
							- theta * d_lay[nn][hh] / por_s[soil_type_lay[nn][hh]]; // (m)

						if (excess > 0.0) {
							if (excess >= capillary_lay[nn][hh]) {
								layerwater_lay[nn][hh] += capillary_lay[nn][hh];
								capillary_lay[nn][hh] = 0.0;
							}
							else {
								capillary_lay[nn][hh] -= excess;
								layerwater_lay[nn][hh] += excess;
							}
						}
					}
				}
				else {
					layerwater_lay[nn][hh] += capillary_lay[nn][hh];
					capillary_lay[nn][hh] = 0.0;
				}
			}
			else { // NOT using Van Genuchten
				layerwater_lay[nn][hh] += capillary_lay[nn][hh];
				capillary_lay[nn][hh] = 0.0;
			}
			Depth[hh] += layerwater_lay[nn][hh];
		}

		d_surface[hh] = dmelt[hh] - Depth[hh] / 2.0;

		watertable[hh] = dmelt[hh] - Depth[hh];

		if (d_surface[hh] < 0.0)
			d_surface[hh] = 0.001;

		if (Depth[hh] > 0.0) {
			float Y = log(Kbtm[hh]) + (log(Ktop[hh]) - log(Kbtm[hh])) / (1.0f + pow(d_surface[hh] / ztrn[hh], 4.3f));
			float YY = exp(Y);
			k[hh] = exp(Y);

			float kd = k[hh]; // m/day

			float lasttransit = transit[hh]; // unit of hours

			transit[hh] = length[hh] * 24.0 / kd; // unit of hours

			if (lasttransit != transit[hh] && flowLag[hh] > 0.0)
				Delayflow->ChangeLag(transit, hh);

			double Loss = kd / Global::Freq*slope[hh] * Depth[hh]; // m/day to m/Int/m2
			loss[hh] = Loss;

			for (int nn = 0; nn < nlay; ++nn) {

				if (layerwater_lay[nn][hh] > 0.0) {
					float available = layerwater_lay[nn][hh] * (por_s[soil_type_lay[nn][hh]]
						- Residual_lay[nn][hh]);
					if (available > Loss) {
						layerwater_lay[nn][hh] -= Loss / (por_s[soil_type_lay[nn][hh]]
							- Residual_lay[nn][hh]);
						flow[hh] += Loss;
						Loss = 0.0;
						break; // loss satisfied - exit layer loop
					}
					else {
						flow[hh] += available;
						Loss -= available;
						layerwater_lay[nn][hh] = 0.0;
					}
				}
			} // for layers
		} // if(Depth[hh] > 0.0)

		flowin[hh] = 0.0;

		for (long hhh = 0; hhh < hh; ++hhh) {
			if (DrainTo[hhh] - 1 == hh) {
				if (Type[hhh] == DRIFT)
					flowin[hh] += driftmelt[hhh] / length[hh]; // convert mm to m
				else if (Type[hhh] == HUMMOCK) {
					flowin[hh] += runoffDly[hhh] * length[hhh] / length[hh]; // runoffDly[hhh]*length[hhh] = runoffm3Dly[hhh]
					flowin[hh] += flowDly[hhh] * length[hhh] / length[hh]; // flowDly[hhh]*length[hhh] = flowm3Dly[hhh]
				}
			}
		} // for

		if (variation == VARIATION_ORG)
			if (p != NULL)
				flowin[hh] += p[0];
			else if (variation == VARIATION_1)
				flowin[hh] += hru_p[0];

		//Added after to get rid of errors 
		float MINFLOAT = 0.00;

		if (flowin[hh] > MINFLOAT * 2) cumflowin[hh] += flowin[hh];
		flowinm3[hh] = flowin[hh] * length[hh];

		d_cum = 0.0; // bottom of layer

		if (flowin[hh] > 0.0) {  // infiltrate surface excess water into layers

			float maxdepth;
			float frozmaxdepth;

			runoff[hh] = flowin[hh];

			for (int nn = 0; nn < nlay; ++nn)
				d_cum += d_lay[nn][hh]; // bottom of bottom layer

			for (int nn = nlay - 1; nn >= 0; --nn) {

				DrainD = wDrained[hh];
				maxdepth = 0.0; frozmaxdepth = 0.0;

				if (dmelt[hh] >= d_cum) { // layer all unfrozen
					maxdepth = d_lay[nn][hh];
					d_cum -= d_lay[nn][hh]; // goto top of layer
				}
				else {
					d_cum -= d_lay[nn][hh]; // goto top of layer
					if (dmelt[hh] <= d_cum) { // layer still frozen
						if (DrainD <= d_cum) continue; // frozen saturated
													   // frost table should be above drained depth

						frozmaxdepth = DrainD - max(dmelt[hh], d_cum); // top up frozen drained
					}
					else { // partially frozen layer with frost table above drained depth
						maxdepth = dmelt[hh] - d_cum;
						if (DrainD > dmelt[hh])
							frozmaxdepth = DrainD - dmelt[hh];
					}
				}

				if (frozmaxdepth > 1e-6) {
					float froztopup = frozmaxdepth * (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);

					if (runoff[hh] > froztopup) { // top up frozen drained area first
												  //            wDrained[hh] -= frozmaxdepth;
						capillary_lay[nn][hh] += frozmaxdepth;
						runoff[hh] -= froztopup;
					}
					else
					{
						frozmaxdepth = runoff[hh] / (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);
						//            wDrained[hh] -= frozmaxdepth;
						capillary_lay[nn][hh] += frozmaxdepth;
						runoff[hh] = 0.0;
						break;  // surface excess water all used up - exit layer loop
					}
				} // if(frozmaxdepth > 1e-6)

				if (maxdepth > 1e-6) {
					float topup = (maxdepth - (layerwater_lay[nn][hh] + capillary_lay[nn][hh]))
						*(por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);

					if (runoff[hh] > topup) {
						capillary_lay[nn][hh] += topup / (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);
						runoff[hh] -= topup;
					}
					else
					{
						capillary_lay[nn][hh] += runoff[hh] / (por_s[soil_type_lay[nn][hh]] - Residual_lay[nn][hh]);
						runoff[hh] = 0.0;
						break;  // surface excess water all used up - exit layer loop
					}
				} // if(maxdepth > 1e-6)
			} // for layers
		} // if(flowin[hh] > 0.0)
		else
			runoff[hh] = 0.0;

		d_cum = 0.0; // bottom of layer
		DrainD = wDrained[hh];

		for (int nn = 0; nn < nlay; ++nn) {
			d_cum += d_lay[nn][hh];
			Top = 0.0; Bot = 0.0;

			if (DrainD > 0.0) { // unsaturated - all frozen
				if (DrainD >= d_cum) { // all residual
					theta_lay[nn][hh] = Residual_lay[nn][hh] * por_s[soil_type_lay[nn][hh]];
					continue;
				}
				else if (DrainD <= (d_cum - d_lay[nn][hh])) { // all saturated
					theta_lay[nn][hh] = por_s[soil_type_lay[nn][hh]];
					continue;
				}
				else { // mixed
					Top = DrainD - (d_cum - d_lay[nn][hh]);
					Bot = d_cum - DrainD;
				}
			}
			else { // originally all saturated

				if (dmelt[hh] <= d_cum - d_lay[nn][hh]) { // all saturated
					theta_lay[nn][hh] = por_s[soil_type_lay[nn][hh]];
					continue;
				}
				else if (dmelt[hh] >= d_cum && (layerwater_lay[nn][hh] + capillary_lay[nn][hh]) <= 0) { // all unsaturated
					theta_lay[nn][hh] = Residual_lay[nn][hh];
					continue;
				}
				else { // mixed
					   //          Bot = layerwater_lay[nn][hh] + capillary_lay[nn][hh];
					if (dmelt[hh] < d_cum)
						Bot = d_cum - dmelt[hh];
					Top = d_lay[nn][hh] - Bot;
				}
			}  // DrainD > 0.0

			theta_lay[nn][hh] = ((Top*Residual_lay[nn][hh] + Bot)*por_s[soil_type_lay[nn][hh]] + capillary_lay[nn][hh])
				/ d_lay[nn][hh];

		} // for layers

		Delayflow->DoClark(hh); // need to update for later HRUs
		Delayrunoff->DoClark(hh); // need to update for later HRUs

	} // for HRUs

	for (hh = 0; chkStruct(); ++hh) {
		if (Type[hh] != HUMMOCK) continue;
		cumrunoff[hh] += runoffDly[hh];
		cumflow[hh] += flowDly[hh];
		flowm3Dly[hh] = flowDly[hh] * length[hh];
		runoffm3Dly[hh] = runoffDly[hh] * length[hh];
	}
}

void Classquinton::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {

		if (Type[hh] != HUMMOCK) continue;  // drift

		float c = 0.0;
		float d_cum = 0.0; // bottom of layer
		float Top, Bot;
		float DrainD = wDrained[hh];

		for (int nn = 0; nn < nlay; ++nn) {
			d_cum += d_lay[nn][hh];
			Top = 0.0; Bot = 0.0;

			if (DrainD > 0.0) { // unsaturated - all frozen
				if (DrainD >= d_cum) // all residual
					Top = d_lay[nn][hh];
				else if (DrainD <= (d_cum - d_lay[nn][hh])) // all saturated
					Bot = d_lay[nn][hh];
				else { // mixed
					Top = DrainD - (d_cum - d_lay[nn][hh]);
					Bot = d_cum - DrainD;
				}
			}
			else { //
				if (dmelt[hh] >= d_cum && (layerwater_lay[nn][hh] + capillary_lay[nn][hh]) < 0.0) // all unsaturated
					Top = d_lay[nn][hh];
				else if (dmelt[hh] <= d_cum - d_lay[nn][hh]) // all saturated
					Bot = d_lay[nn][hh];
				else { // mixed
					Bot = layerwater_lay[nn][hh] + capillary_lay[nn][hh];
					if (dmelt[hh] < d_cum)
						Bot += d_cum - dmelt[hh];
					Top = d_lay[nn][hh] - Bot;
				}
			}

			c += Top * Residual_lay[nn][hh];
			c += Bot * por_s[soil_type_lay[nn][hh]];

		} // for layers

		LogMessageA(hh, "(Hummock) - water content      (m^3) (m/m^2): ", c*length[hh], length[hh]);
		LogMessageA(hh, "(Hummock) - cumulative flowin  (m^3) (m/m^2): ", cumflowin[hh] * length[hh], length[hh]);
		LogMessageA(hh, "(Hummock) - cumulative flowout (m^3) (m/m^2): ", cumflow[hh] * length[hh], length[hh]);
		LogMessageA(hh, "(Hummock) - flowout in storage (m^3) (m/m^2): ", Delayflow->Left(hh)*length[hh], length[hh]);
		LogMessageA(hh, "(Hummock) - cumulative runoff  (m^3) (m/m^2): ", cumrunoff[hh] * length[hh], length[hh]);
		LogMessageA(hh, "(Hummock) - runoff in storage  (m^3) (m/m^2): ", Delayrunoff->Left(hh)*length[hh], length[hh]);
		LogDebug(" ");

	} // for HRUs

	delete Delayflow;
	delete Delayrunoff;
}

//---------------------------------------------------------------------------

ClassICEflow* ClassICEflow::klone(string name) const {
	return new ClassICEflow(name);
}

void ClassICEflow::decl(void) {

	Description = "'Simulates ICE flow dynamic.'";

	declvar("Ice_out", NHRU, "outgoing iceflow transport", "(mm/int)", &Ice_out);

	declvar("Ice_in", NHRU, "incoming iceflow transport", "(mm/int)", &Ice_in);

	declvar("Ux", NHRU, "plastic flow due to its own weight. Can be channel flow or slab flow(shallow iceflow).", "(m)", &Ux);

	declvar("Ub", NHRU, "velocity due to basal slip", "(m)", &Ub);

	declvar("Utot", NHRU, "sum of plastic deformation and basal slip", "(m)", &Utot);

	declvar("cumulative_net_rain", NHRU, "cumulative meltwater and rain", "(m/yr)", &cumulative_net_rain);

	decldiag("cumIce_in", NHRU, "incoming cumulative Slip transport ice from other HRU", "(mm)", &cumIce_in);

	decldiag("cumIce_out", NHRU, "outgoing cumulative Slip transport ice to other HRU", "(mm)", &cumIce_out);

	/* parameters */

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "sequence of HRUs for iceflow distribution", "()", &order);

	declparam("Disable_ICEflow", NHRU, "[0]", "0", "1", "set to 1 to disable module", "()", &Disable_ICEflow);

	declparam("distrib_iceflow", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "distribute this HRU iceflow to these HRUs", "()", &distrib, &distrib_hru, nhru);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_GSL", NHRU, "0.0", "0.0", "90.0", "ground slope - increasing the slope positively, tilts the plane to the north with ASL = 0", "(�)", &hru_GSL);

	declparam("SWE_to_firn_Julian", NHRU, "[274]", "0", "366", "convert any SWE to firn on Julian day. 0 - inhibit transfer", "()", &SWE_to_firn_Julian);

	declparam("test_option", NHRU, "[-1]", "-1", "100", "negative - disable testing option, >= 0 sets Utot to value of test option.", "(mm)", &test_option);

	declparam("channel_option", NHRU, "[0]", "0", "1", "0 - channel flow, 1 - slab flow.", "()", &channel_option);

	declparam("basal_option", NHRU, "[1]", "1", "2", "1 - u_basal option 1, 2 - u_basal option 2", "()", &basal_option);

	declparam("radius_glacier", NHRU, "[1000]", "100", "10000", "radius of glacier", "(m)", &radius_glacier);

	declparam("Arrhenius_const", NHRU, "[2.935E-17]", "1E-30", "1E-2", "Arrhenius constant", "(1/Pa*yr)", &Arrhenius_const); // Cuffey and Paterson (2010)

	declparam("slip_sf", NHRU, "[0.5]", "0.0", "2.0", "shape factor for the shear stress in channel flow", "()", &slip_sf); // Nye J.F. (1965). The flow of a glacier in a channel of rectangular, elliptic, or parabolic cross-section. Journal of Glaciology. Vol 5, 661-690.

	declparam("slip_m", NHRU, "[3.0]", "0.0", "3.0", "exponent constant for basal slip", "()", &slip_m); // Generally 2 to 3 (Oerlemans, 2001)

	declparam("slip_c", NHRU, "[0.1]", "0.0", "1.0", "constant for physical characteristics of the bed", "()", &slip_c);

	declparam("slip_fs", NHRU, "[1.8E-12]", "1E-25", "1.0", "sliding parameter from Budd et al. (1979) for basal option 2", "(Pa^-3*m^2*yr)", &slip_fs); // fs = 5.7e-20*(365.2422*24*3600) Oerlemans J. (2001). Glaciers and Climate Change. A.A. Balkema Publishers, Lisse.


	declputvar("*", "ice", "(mm)", &ice); // water equivalent of ice
	declgetvar("*", "firn", "(mm)", &firn); // water equivalent of firn
	declgetvar("*", "net_rain", "(mm)", &net_rain); // meltwater and rain
}

void ClassICEflow::init(void) {

	nhru = getdim(NHRU);

	for (hh = 0; hh < nhru; ++hh) {
		Ice_in[hh] = 0.0;
		Ice_out[hh] = 0.0;
		cumIce_in[hh] = 0.0;
		cumIce_out[hh] = 0.0;
		Ux[hh] = 0.0;
		Ub[hh] = 0.0;
		Utot[hh] = 0.0;
		cumulative_net_rain[hh] = 0.0;
	} // for
}

void ClassICEflow::run(void) {

	const float ice_dens = 917;
	const float g = 9.81;
	const float n_Glen = 3;  // Glen's flow parameter
	const float alpha = M_PI / 180.0;  // degrees to radians
	const float water_dens = 1000;  // kg/m^3

	long nstep = getstep() % Global::Freq;

	for (long hh = 0; chkStruct(hh); ++hh)
		cumulative_net_rain[hh] += net_rain[hh]; // from glacier module. It includes melt and rain

	if (nstep == 0 || Global::Freq == 1) { // end of every day

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (Disable_ICEflow[hh])
				continue;

			hh = order[hhh] - 1; // do HRUs in the desired sequence

			long Julian = julian("now"); // same as "decday"
			if (SWE_to_firn_Julian[hh] == Julian) {
				if (hh == 0)
					for (long mm = 0; chkStruct(mm); ++mm)
						Ice_in[mm] = 0.0;


				Ice_out[hh] = 0.0;
				Ux[hh] = 0.0;
				Ub[hh] = 0.0;
				Utot[hh] = 0.0;

				if (test_option[hh] >= 0.0) // use user value for ice flow
					Utot[hh] = test_option[hh];
				else {
					float ICE = ice[hh] + firn[hh];
					if (channel_option[hh] == 0) // channel flow
						Ux[hh] = 2 * Arrhenius_const[hh] * pow(slip_sf[hh] * ice_dens*g*sin(hru_GSL[hh] * alpha), n_Glen)*pow(radius_glacier[hh], n_Glen + 1) / (n_Glen + 2);
					else // by default slab flow
						Ux[hh] = 2 * Arrhenius_const[hh] * pow(ice_dens*g*sin(hru_GSL[hh] * alpha), n_Glen)*pow(ICE / ice_dens, n_Glen + 1) / (n_Glen + 2);

					float ice_thickness = ICE / ice_dens; //ICE is in mm water equivalent, and ice_dens is in kg/m3, therefore, ice_thickness is in m
					float Iw = ice_dens * g*ice_thickness;
					float tau_b = slip_sf[hh] * ice_dens*g*ice_thickness*sin(hru_GSL[hh] * alpha);

					if (basal_option[hh] == 1) {
						float Pw = water_dens * g*cumulative_net_rain[hh] / 1000.0; // (mm) > (m)
						Ub[hh] = slip_c[hh] * pow(tau_b, slip_m[hh]) / (Iw - Pw);
					}
					else { // by default option 2
						Ub[hh] = slip_fs[hh] * pow(tau_b, slip_m[hh]) / ice_thickness;
					}

					Utot[hh] = Ux[hh] + Ub[hh];
				} // else

				if (Utot[hh] > 0.0) { // distribute flow

					for (long To = 0; chkStruct(To); ++To) { // distribute ice outflow of HRU

						if (hh != To && Utot[hh] > 0.0 && distrib_hru[hh][To] > 0.0) {
							float Amount = Utot[hh] * distrib_hru[hh][To];
							Ice_out[hh] = Amount;
							cumIce_out[hh] += Amount;
							ice[hh] -= Amount;

							Amount = Amount * hru_area[hh] / hru_area[To]; // adjust to area of destination HRU
							ice[To] += Amount;
							Ice_in[To] = Amount;
							cumIce_in[To] += Amount;
						} // if
					} // for
				} // end of moving
				cumulative_net_rain[hh] = 0.0; // reset at end of season
			} // end of Julian date
		} // end for hhh(hh)
	} // end of day
}

void ClassICEflow::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (ICESlope)' ice        (mm) (mm*hru) (mm*hru/basin): ").c_str(), ice[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (ICESlope)' cumIce_in  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumIce_in[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (ICESlope)' cumIce_out (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumIce_out[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassXGAyers* ClassXGAyers::klone(string name) const {
	return new ClassXGAyers(name);
}

void ClassXGAyers::decl(void) {

	Description = "'Snow melt handled by XG and and Ayers, .'";

	declvar("infil", NHRU, "Potential rain infiltration", "(mm/int)", &infil);

	declstatdiag("cuminfil", NHRU, "cumulative potential rain infiltration", "(mm)", &cuminfil);

	declvar("snowinfil", NHRU, "melt infiltration", "(mm/int)", &snowinfil);

	declstatvar("cumsnowinfil", NHRU, "cumulative melt infiltration", "(mm)", &cumsnowinfil); // for looping

	declvar("meltrunoff", NHRU, "melt runoff = 0.0", "(mm/int)", &meltrunoff);

	declstatdiag("cummeltrunoff", NHRU, "cumulative melt runoff = 0.0", "(mm)", &cummeltrunoff);

	declvar("runoff", NHRU, "rainfall runoff", "(mm/int)", &runoff);

	declstatdiag("cumrunoff", NHRU, "cumulative rainfall runoff", "(mm)", &cumrunoff);


	declparam("texture", NHRU, "[1]", "1", "4",
		"texture: 1 - coarse/medium over coarse, 2 - medium over medium, 3 - medium/fine over fine, 4 - soil over shallow bedrock.", "(%)", &texture);

	declparam("groundcover", NHRU, "[1]", "1", "6",
		"groundcover: 1 - bare soil, 2 - row crop, 3 - poor pasture, 4 - small grains, 5 - good pasture, 6 - forested.", "(%)", &groundcover);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);


	declgetvar("*", "snowmeltD", "(mm/d)", &snowmeltD); // mm day

	declgetvar("*", "net_rain", "(mm/int)", &net_rain);
}

void ClassXGAyers::init(void) {

	nhru = getdim(NHRU);


	for (hh = 0; hh < nhru; ++hh) {
		infil[hh] = 0.0;
		runoff[hh] = 0.0;
		snowinfil[hh] = 0.0;
		meltrunoff[hh] = 0.0;
		cuminfil[hh] = 0.0;
		cumsnowinfil[hh] = 0.0;
		cummeltrunoff[hh] = 0.0;
		cumrunoff[hh] = 0.0;
	}
}

void ClassXGAyers::run(void) {


	long nstep = getstep() % Global::Freq;

	for (hh = 0; chkStruct(); ++hh) {

		infil[hh] = 0.0;
		runoff[hh] = 0.0;

		if (net_rain[hh] > 0.0) {
			float maxinfil = textureproperties[texture[hh] - 1][groundcover[hh] - 1] * 24.0 / Global::Freq; // mm/int
			if (maxinfil > net_rain[hh])
				infil[hh] = net_rain[hh];
			else {
				infil[hh] = maxinfil;
				runoff[hh] = net_rain[hh] - maxinfil;
			}

			cuminfil[hh] += infil[hh];
			cumrunoff[hh] += runoff[hh];
		}

		snowinfil[hh] = 0.0;
		meltrunoff[hh] = snowmeltD[hh] / Global::Freq;
	} // for
}

void ClassXGAyers::finish(bool good) {

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumsnowinfil       (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumsnowinfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cummeltrunoff      (mm) (mm*hru) (mm*hru/basin): ").c_str(), cummeltrunoff[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cuminfil(rain)     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cuminfil[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (frozenAyers)' cumrunoff(rain)    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cumrunoff[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

ClassCRHMCanopyClearing* ClassCRHMCanopyClearing::klone(string name) const {
	return new ClassCRHMCanopyClearing(name);
}

void ClassCRHMCanopyClearing::decl(void) {

	Description = "'Prototype all season canopy/clearing module. Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), '\
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2), '";

	// Observations

	variation_set = VARIATION_0 + VARIATION_1;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);


	variation_set = VARIATION_0 + VARIATION_2;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


	variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);


	variation_set = VARIATION_2 + VARIATION_3;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);


	variation_set = VARIATION_4;

	declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


	variation_set = VARIATION_ORG;

	// get variables:

	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	declgetvar("*", "hru_rh", "()", &hru_rh);

	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

	declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

	declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

	declgetvar("*", "SolAng", "(r)", &SolAng);

	declgetvar("*", "Albedo", "(r)", &Albedo);

	declputvar("*", "SWE", "(mm)", &SWE);

	// declared observations

	declobs("Ts", NHRU, "snow surface temperature", "(�C)", &Ts);

	declobs("Qnsn", NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn);

	declvar("Qnsn_Var", NHRU, "net all-wave at snow surface", "(W/m^2*int)", &Qnsn_Var);

	declobs("Qsisn", NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn);

	declvar("Qsisn_Var", NHRU, "incident short-wave at surface", "(W/m^2*int)", &Qsisn_Var);

	declobs("Qlisn", NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn);

	declvar("Qlisn_Var", NHRU, "incident short-wave at surface", "(W/m^2*int)", &Qlisn_Var);

	declobs("Qlosn", NHRU, "reflected long-wave at surface", "(W/m^2)", &Qlosn);

	// declared variables

	decldiag("k", NHRU, "extinction coefficient", "()", &k);

	decldiag("Tauc", NHRU, "short-wave transmissivity", "(W/m^2)", &Tauc);

	decllocal("Pa", NHRU, "Average surface pressure", "(kPa)", &Pa);

	declvar("ra", NHRU, "", "(s/m)", &ra);

	declvar("drip_cpy", NHRU, "canopy drip", "(mm/int)", &drip_Cpy);

	declvar("direct_rain", NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

	declvar("net_rain", NHRU, " direct_rain + drip", "(mm/int)", &net_rain);

	declstatdiag("cum_net_rain", NHRU, " direct_rain + drip", "(mm)", &cum_net_rain);

	declvar("Subl_Cpy", NHRU, "canopy snow sublimation", "(mm/int)", &Subl_Cpy);

	declstatdiag("cum_Subl_Cpy", NHRU, "canopy snow sublimation", "(mm)", &cum_Subl_Cpy);

	decldiag("Pevap", NHRU, "used when ground is snow covered to calculate canopy evaporation (Priestley-Taylor)", "(mm)", &Pevap);

	declstatvar("rain_load", NHRU, "canopy rain load", "(mm)", &rain_load);

	declstatvar("Snow_load", NHRU, "canopy snow load (timetep start)", "(mm)", &Snow_load);

	declvar("direct_snow", NHRU, "snow 'direct' Thru", "(mm/int)", &direct_snow);

	declvar("SUnload", NHRU, "unloaded canopy snow", "(mm)", &SUnload);

	declvar("SUnload_H2O", NHRU, "unloaded canopy snow as water", "(mm)", &SUnload_H2O);

	declstatdiag("cum_SUnload_H2O", NHRU, "Cumulative unloaded canopy snow as water", "(mm)", &cum_SUnload_H2O);

	declstatdiag("cum_SUnload", NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", &cum_SUnload);

	declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

	declstatdiag("cum_net_snow", NHRU, "Cumulative Canopy unload ", "(mm)", &cum_net_snow);

	declvar("net_p", NHRU, "total precipitation after interception", "(mm/int)", &net_p);

	decldiag("u_FHt", NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

	decldiag("Cc", NHRU, "Canopy coverage", "()", &Cc);

	declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);

	declstatdiag("cum_intcp_evap", NHRU, "HRU Evaporation from interception", "(mm)", &cum_intcp_evap);


	// parameters:

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);


	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "forest/vegetation height", "(m)", &Ht);

	declparam("Zref", NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	declparam("LAI", NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

	declparam("Sbar", NHRU, "[6.6]", "0.0", "100.0", "maximum canopy snow interception load", "(kg/m^2)", &Sbar);

	declparam("Zvent", NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

	declparam("unload_t", NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(�C)", &unload_t);

	declparam("unload_t_water", NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(�C)", &unload_t_water);

	declparam("CanopyClearing", NHRU, "[0]", "0", "1", "canopy - 0/clearing - 1", "()", &CanopyClearing);

	decldiagparam("Alpha_c", NHRU, "[0.1]", "0.05", "0.2", "canopy albedo", "()", &Alpha_c);

	decldiagparam("B_canopy", NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter. Suggestions are Colorado - 0.23 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopyClearing::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRU's to module

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa

		rain_load[hh] = 0.0;
		Snow_load[hh] = 0.0;

		cum_net_snow[hh] = 0.0;
		cum_net_rain[hh] = 0.0;
		cum_Subl_Cpy[hh] = 0.0;
		cum_intcp_evap[hh] = 0.0;
		cum_SUnload[hh] = 0.0;
		cum_SUnload_H2O[hh] = 0.0;

		if (Ht[hh] > Zwind[hh]) {
			CRHMException TExcept(string("'" + Name + " (CanopyClearing)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), WARNING);
			LogError(TExcept);
		}
	}
}

void ClassCRHMCanopyClearing::run(void) {

	float Kstar_H;

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Qsi_ = Qsi[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_1:
			Qsi_ = Qsi[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_2:
			Qsi_ = QsiS_Var[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_3:
			Qsi_ = QsiS_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_4:
			Qsi_ = QsiA_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		} // switch

		net_rain[hh] = 0.0;
		direct_rain[hh] = 0.0;
		drip_Cpy[hh] = 0.0;
		intcp_evap[hh] = 0.0;

		net_snow[hh] = 0.0;
		direct_snow[hh] = 0.0;
		SUnload[hh] = 0.0;
		SUnload_H2O[hh] = 0.0;
		Subl_Cpy[hh] = 0.0;

		// Canopy temperature is approximated by the air temperature.
		float T1 = hru_t[hh] + CRHM_constants::Tm;

		if (CanopyClearing[hh] == 0) {

			float Exposure = Ht[hh] - DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
			if (Exposure < 0.0)
				Exposure = 0.0;

			float LAI_ = LAI[hh] * Exposure / Ht[hh];

			float Vf = 0.45 - 0.29*log(LAI[hh]);

			float Vf_ = Vf + (1.0 - Vf)*sin((Ht[hh] - Exposure) / Ht[hh] * M_PI_2);

			if (SolAng[hh] > 0.001) {
				k[hh] = 1.081*SolAng[hh] * cos(SolAng[hh]) / sin(SolAng[hh]);
				Tauc[hh] = exp(-k[hh] * LAI_);
			}
			else {
				k[hh] = 0.0;
				Tauc[hh] = 0.0;
			}

			Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh]));

			Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f) + B_canopy[hh] * Kstar_H;

			Qlisn_Var[hh] = Qlisn[hh];

			Qsisn[hh] = Qsi_ * Tauc[hh];

			Qsisn_Var[hh] = Qsisn[hh];
		}
		else {

			Qlisn[hh] = Qli_; // CanopyClearing[hh] == 1

			Qlisn_Var[hh] = Qlisn[hh];

			Qsisn[hh] = Qsi_;

			Qsisn_Var[hh] = Qsisn[hh];
		}


		float rho = Pa[hh] * 1000 / (CRHM_constants::Rgas*T1);

		float U1 = hru_u[hh]; // Wind speed (m/s)

		ra[hh] = (log(Zref[hh] / Z0snow[hh])*log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

		float deltaX = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas*sqr(T1));

		float q = (hru_rh[hh] / 100)*Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)


		Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_ - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho / ra[hh]) /
			(4 * CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*deltaX)*rho / ra[hh]);

		Ts[hh] -= CRHM_constants::Tm;

		if (Ts[hh] > 0.0 || SWE[hh] <= 0.0)
			Ts[hh] = 0.0;

		Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

		Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

		Qnsn_Var[hh] = Qnsn[hh];

		if (CanopyClearing[hh] == 0) {
			//==============================================================================
			// coupled forest snow interception and sublimation routine:
			// after Hedstom & Pomeroy / Parviainen & Pomeroy:
			// calculate maximum canopy snow load (L*):

			if (Snow_load[hh] > 0.0 || hru_snow[hh] > 0.0) { // handle snow interception

				if (Sbar[hh] >= 0.0) {
					float RhoS = 67.92 + 51.25* exp(hru_t[hh] / 2.59);
					float LStar = Sbar[hh] * (0.27 + 46.0 / RhoS)* LAI[hh];

					if (Snow_load[hh] > LStar) { // after increase in temperature
						direct_snow[hh] = Snow_load[hh] - LStar;
						Snow_load[hh] = LStar;
					}

					// calculate intercepted snowload

					if (Ht[hh] - 2.0 / 3.0*Zwind[hh] > 0.0)
						u_FHt[hh] = hru_u[hh] * log((Ht[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]);
					else
						u_FHt[hh] = 0.0;

					double I1 = 0.0;

					if (hru_snow[hh] > 0.0) {
						if (fabs(hru_snow[hh] / LStar) < 50.0) {
							if (u_FHt[hh] <= 1.0)  // if wind speed at canopy top > 1 m/s
								I1 = (LStar - Snow_load[hh])*(1.0 - exp(-Cc[hh] * hru_snow[hh] / LStar));
							else
								I1 = (LStar - Snow_load[hh])*(1.0 - exp(-hru_snow[hh] / LStar));

							if (I1 <= 0)
								I1 = 0;

							Snow_load[hh] += I1;
						}

						// calculate canopy snow throughfall before unloading:

						direct_snow[hh] += (hru_snow[hh] - I1);
					}

					// calculate snow ventilation windspeed:

					//=============================================================================
					const float gamma = 1.15;
					const float AlbedoIce = 0.8;       // albedo of ideal ice sphere
					const float Radius = 5.0e-4;       // radii of single 'ideal' ice sphere in, m)
					const float KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
					const float ks = 0.0114;           // snow shape coefficient for jack pine
					const float Fract = 0.37;          // fractal dimension of intercepted snow
					const float ci = 2.102e-3;         // heat capacity of ice (MJ/kg/K)
					const float Hs = 2.838e6;          // heat of sublimation (MJ/kg)
													   //==============================================================================

					float xi2 = 1 - Zvent[hh];
					float windExt2 = (gamma * LAI[hh] * xi2);

					float uVent = u_FHt[hh] * exp(-1 * windExt2);


					// calculate sublimation of intercepted snow from ideal intercepted ice sphere (500 microns diameter):

					float Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;

					float Es = 611.15f * exp(22.452f*hru_t[hh] / (hru_t[hh] + 273.0f));  // {sat pressure}

					float SvDens = Es * PBSM_constants::M / (PBSM_constants::R*(hru_t[hh] + 273.0f)); // {sat density}

					Lamb = 6.3e-4*(hru_t[hh] + 273.0) + 0.0673;  // thermal conductivity of atmosphere
					Nr = 2.0 * Radius * uVent / KinVisc;  // Reynolds number
					Nu = 1.79 + 0.606 * sqrt((float)Nr); // Nusselt number
					SStar = M_PI * sqr(Radius) * (1.0f - AlbedoIce) * Qsi_;  // SW to snow particle !!!! changed
					A1 = Lamb * (hru_t[hh] + 273) * Nu;
					B1 = Hs * PBSM_constants::M / (PBSM_constants::R * (hru_t[hh] + 273.0f)) - 1.0;
					J = B1 / A1;
					Sigma2 = hru_rh[hh] / 100 - 1;
					D = 2.06e-5* pow((hru_t[hh] + 273.0f) / 273.0f, -1.75f); // diffusivity of water vapour
					C1 = 1.0 / (D*SvDens*Nu);

					Alpha = 5.0;
					Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Radius*Radius*Radius *(1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

					// sublimation rate of single 'ideal' ice sphere:

					float Vs = (2.0* M_PI* Radius*Sigma2 - SStar * J) / (Hs* J + C1) / Mpm;

					// snow exposure coefficient (Ce):

					float Ce;
					if ((Snow_load[hh] / LStar) <= 0.0)
						Ce = 0.07;
					else
						Ce = ks * pow((Snow_load[hh] / LStar), -Fract);

					// calculate 'potential' canopy sublimation:

					float Vi = Vs * Ce;

					// limit sublimation to canopy snow available and take sublimated snow away from canopy snow at timestep start

					Subl_Cpy[hh] = -Snow_load[hh] * Vi*Global::Interval * 24 * 3600; // make W/m2
					if (Subl_Cpy[hh] > Snow_load[hh]) {
						Subl_Cpy[hh] = Snow_load[hh];
						Snow_load[hh] = 0.0;
					}
					else {
						Snow_load[hh] -= Subl_Cpy[hh];
						if (Snow_load[hh] < 0.0)
							Snow_load[hh] = 0.0;
					}

					// calculate 'ice-bulb' temperature of intercepted snow:

					float IceBulbT = hru_t[hh] - (Vi* Hs / 1e6 / ci);
					float Six_Hour_Divisor = Global::Freq / 4.0; // used to unload over 6 hours

					const float c = 0.678 / (24 * 7 * 24 / Global::Freq); // weekly dimensionless unloading coefficient -> to CRHM time interval

																		  // determine whether canopy snow is unloaded:

					if (IceBulbT >= unload_t_water[hh]) {
						drip_Cpy[hh] = Snow_load[hh] / Six_Hour_Divisor;
						SUnload_H2O[hh] = drip_Cpy[hh];
						Snow_load[hh] -= SUnload_H2O[hh];
						cum_SUnload_H2O[hh] += SUnload_H2O[hh];
					}
					else if (IceBulbT >= unload_t[hh]) {
						SUnload[hh] = Snow_load[hh] / Six_Hour_Divisor;
						Snow_load[hh] -= SUnload[hh];
						cum_SUnload[hh] += SUnload[hh];
					}
					else if (IceBulbT < unload_t[hh]) { // has to be at least one interval. Trip on half step
						SUnload[hh] = Snow_load[hh] * c; // the dimensionless unloading coefficient already /interval
						if (SUnload[hh] > Snow_load[hh]) {
							SUnload[hh] = Snow_load[hh];
							Snow_load[hh] = 0.0;
						}
						else
							Snow_load[hh] -= SUnload[hh];

						cum_SUnload[hh] += SUnload[hh];
					}

					// calculate total sub-canopy snow:

					net_snow[hh] = direct_snow[hh] + SUnload[hh];
				}
				else { // handle snow when Sbar is zero
					direct_snow[hh] += hru_snow[hh];
					net_snow[hh] = direct_snow[hh];
				}
			}// handle snow interception

		} // if canopy
		else { // clearing
			net_snow[hh] = hru_snow[hh];
			net_rain[hh] = hru_rain[hh];
		}

		// calculate horizontal canopy-coverage (Cc):

		if (CanopyClearing[hh] == 0) {

			Cc[hh] = 0.29 * log(LAI[hh]) + 0.55;
			if (Cc[hh] <= 0.0)
				Cc[hh] = 0.0;

			float smax = Cc[hh] * LAI[hh] * 0.2;

			//  Forest rain interception and evaporation model
			// 'sparse' Rutter interception model (i.e. Valente 1997):

			// calculate direct throughfall:

			if (hru_rain[hh] > 0.0) {

				direct_rain[hh] = hru_rain[hh] * (1 - Cc[hh]);

				// calculate rain accumulation on canopy before evap loss:

				if (rain_load[hh] + hru_rain[hh] * Cc[hh] > smax) {
					drip_Cpy[hh] += (rain_load[hh] + hru_rain[hh] * Cc[hh] - smax);
					rain_load[hh] = smax;
				}
				else
					rain_load[hh] += hru_rain[hh] * Cc[hh];

			}  // if hru_rain[hh] > 0.0

			   // calculate 'actual evap' of water from canopy and canopy storage after evaporation::

			if (rain_load[hh] > 0.0) {
				if (inhibit_evap[hh] == 0) { // use Granger when no snowcover
					if (rain_load[hh] >= hru_evap[hh] * Cc[hh]) { // (evaporation in mm)
						intcp_evap[hh] = hru_evap[hh] * Cc[hh];  //
						rain_load[hh] -= hru_evap[hh] * Cc[hh];
					}
					else {
						intcp_evap[hh] = rain_load[hh];
						rain_load[hh] = 0.0;
					}
				}
				else { // use Priestley-Taylor when snowcover
					float Q = Qsi_ * 86400 / Global::Freq / 1e6 / lambda(hru_t[hh]); // convert w/m2 to mm/m2/int

					if (Qsi_ > 0.0)
						Pevap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
					else
						Pevap[hh] = 0.0;

					if (rain_load[hh] >= Pevap[hh] * Cc[hh]) {  // (evaporation in mm)
						intcp_evap[hh] = Pevap[hh] * Cc[hh];  // check
						rain_load[hh] -= Pevap[hh] * Cc[hh];
					}
					else {
						intcp_evap[hh] = rain_load[hh]; // check
						rain_load[hh] = 0.0;
					}
				}
			} // if rain_load[hh] > 0.0

			  // cumulative amounts....

			net_rain[hh] = direct_rain[hh] + drip_Cpy[hh];

			cum_intcp_evap[hh] += intcp_evap[hh];
			cum_Subl_Cpy[hh] += Subl_Cpy[hh];

		}  // if CanopyClearing

		net_p[hh] = net_rain[hh] + net_snow[hh];
		cum_net_rain[hh] += net_rain[hh];
		cum_net_snow[hh] += net_snow[hh];
	} // end for
}

void ClassCRHMCanopyClearing::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_net_snow    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_snow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_net_rain    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_rain[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_Subl_Cpy    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Subl_Cpy[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_intcp_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_SUnload     (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_SUnload[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearing)'  cum_SUnload_H2O (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_SUnload_H2O[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassCRHMCanopyClearing::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

float ClassCRHMCanopyClearing::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassCRHMCanopyClearing::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float ClassCRHMCanopyClearing::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R = 2870;
	return (1E4*Pa / (R*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

ClassCRHMCanopyClearingGap* ClassCRHMCanopyClearingGap::klone(string name) const {
	return new ClassCRHMCanopyClearingGap(name);
}

void ClassCRHMCanopyClearingGap::decl(void) {

	Description = "'Prototype all season canopy/clearing module. Calculates short, long and all-wave radiation components at the snow surface.' \
                 'Inputs are observations Qsi (W/m^2) and Qli (W/m^2), ' \
                 'Inputs are observation Qsi (W/m^2) and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and observation Qli (W/m^2), ' \
                 'Inputs are variable QsiS_Var (W/m^2)(slope) from Annandale and variable QliVt_Var (W/m^2), ' \
                 'Inputs are variable QsiA_Var (W/m^2)(horizontal) from Annandale and variable QliVt_Var (W/m^2).'";

	// Observations

	variation_set = VARIATION_0 + VARIATION_1;

	declreadobs("Qsi", NHRU, "incident short-wave", "(W/m^2)", &Qsi, HRU_OBS_Q);


	variation_set = VARIATION_0 + VARIATION_2;

	declreadobs("Qli", NHRU, "incident long-wave", "(W/m^2)", &Qli, HRU_OBS_Q);


	variation_set = VARIATION_1 + VARIATION_3 + VARIATION_4;

	declgetvar("*", "QliVt_Var", "(W/m^2)", &QliVt_Var);


	variation_set = VARIATION_2 + VARIATION_3;

	declgetvar("*", "QsiS_Var", "(W/m^2)", &QsiS_Var);

	variation_set = VARIATION_4;

	declgetvar("*", "QsiA_Var", "(W/m^2)", &QsiA_Var);


	variation_set = VARIATION_ORG;

	// get variables:

	declgetvar("*", "hru_t", "(�C)", &hru_t);

	declgetvar("*", "hru_u", "(m/s)", &hru_u);

	declgetvar("*", "hru_rh", "()", &hru_rh);

	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);

	declgetvar("*", "hru_snow", "(mm/int)", &hru_snow);

	declgetvar("*", "hru_rain", "(mm/int)", &hru_rain);

	declgetvar("*", "hru_evap", "(mm/int)", &hru_evap);

	declgetvar("*", "SolAng", "(r)", &SolAng);

	declgetvar("*", "cosxs", "(r)", &cosxs);

	declgetvar("*", "cosxsflat", "(r)", &cosxsflat);

	declgetvar("*", "Qdfo", "(W/m^2)", &Qdfo);

	declgetvar("*", "Albedo", "()", &Albedo);

	declputvar("*", "SWE", "(mm)", &SWE);

	// declared observations

	declobs("Ts", NHRU, "snow surface temperature", "(�C)", &Ts);

	declobs("Qnsn", NHRU, "net all-wave at snow surface", "(W/m^2)", &Qnsn);

	declvar("Qnsn_Var", NHRU, "net all-wave at snow surface", "(W/m^2*int)", &Qnsn_Var);

	declobs("Qsisn", NHRU, "incident short-wave at surface", "(W/m^2)", &Qsisn);

	declvar("Qsisn_Var", NHRU, "incident short-wave at surface", "(W/m^2*int)", &Qsisn_Var);

	declobs("Qlisn", NHRU, "incident long-wave at surface", "(W/m^2)", &Qlisn);

	declvar("Qlisn_Var", NHRU, "incident long-wave at surface", "(W/m^2*int)", &Qlisn_Var);

	declobs("Qlosn", NHRU, "reflected long-wave at surface", "(W/m^2)", &Qlosn);

	// declared variables

	decldiag("k", NHRU, "extinction coefficient", "()", &k);

	decldiag("Tauc", NHRU, "short-wave transmissivity", "(W/m^2)", &Tauc);

	decllocal("Pa", NHRU, "Average surface pressure", "(kPa)", &Pa);

	declvar("ra", NHRU, "", "(s/m)", &ra);

	declvar("drip_cpy", NHRU, "canopy drip", "(mm/int)", &drip_Cpy);

	declvar("direct_rain", NHRU, "direct rainfall through canopy", "(mm/int)", &direct_rain);

	declvar("net_rain", NHRU, " direct_rain + drip", "(mm/int)", &net_rain);

	declstatdiag("cum_net_rain", NHRU, " direct_rain + drip", "(mm)", &cum_net_rain);

	declvar("Subl_Cpy", NHRU, "canopy snow sublimation", "(mm/int)", &Subl_Cpy);

	declstatdiag("cum_Subl_Cpy", NHRU, "canopy snow sublimation", "(mm)", &cum_Subl_Cpy);

	decldiag("Pevap", NHRU, "used when ground is snow covered to calculate canopy evaporation (Priestley-Taylor)", "(mm)", &Pevap);

	declstatvar("rain_load", NHRU, "canopy rain load", "(mm)", &rain_load);

	declstatvar("Snow_load", NHRU, "canopy snow load (timetep start)", "(mm)", &Snow_load);

	declvar("direct_snow", NHRU, "snow 'direct' Thru", "(mm/int)", &direct_snow);

	declvar("SUnload", NHRU, "unloaded canopy snow", "(mm)", &SUnload);

	declvar("SUnload_H2O", NHRU, "unloaded canopy snow as water", "(mm)", &SUnload_H2O);

	declstatdiag("cum_SUnload_H2O", NHRU, "Cumulative unloaded canopy snow as water", "(mm)", &cum_SUnload_H2O);

	declstatdiag("cum_SUnload", NHRU, "Cumulative unloaded canopy snow as snow", "(mm)", &cum_SUnload);

	declvar("net_snow", NHRU, "hru_snow minus interception", "(mm/int)", &net_snow);

	declstatdiag("cum_net_snow", NHRU, "Cumulative Canopy unload ", "(mm)", &cum_net_snow);

	declvar("net_p", NHRU, "total precipitation after interception", "(mm/int)", &net_p);

	decldiag("u_FHt", NHRU, "wind speed at forest top (z = FHt)", "(m/s)", &u_FHt);

	decldiag("Cc", NHRU, "Canopy coverage", "()", &Cc);

	declvar("intcp_evap", NHRU, "HRU Evaporation from interception", "(mm/int)", &intcp_evap);

	declstatdiag("cum_intcp_evap", NHRU, "HRU Evaporation from interception", "(mm)", &cum_intcp_evap);


	// parameters:

	declparam("inhibit_evap", NHRU, "[0]", "0", "1", "inhibit evaporation, 1 -> inhibit", "()", &inhibit_evap);

	declparam("basin_area", BASIN, "3", "1e-6", "1e+09", "total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e+09", "hru area", "(km^2)", &hru_area);

	declparam("hru_elev", NHRU, "[637]", "0.0", "100000.0", "altitude", "(m)", &hru_elev);

	declparam("Surrounding_Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "surrounding canopy height", "()", &Surrounding_Ht);

	declparam("Gap_diameter", NHRU, "[100]", "10", "1000", "representative gap diameter", "(m)", &Gap_diameter);


	declparam("Ht", NHRU, "[20.0]", "0.001", "100.0", "forest/vegetation height", "(m)", &Ht);

	declparam("Zref", NHRU, "[1.5]", "0.01", "100.0", "temperature measurement height", "(m)", &Zref);

	declparam("Zwind", NHRU, "[10]", "0.01", "100.0", "wind measurement height", "(m)", &Zwind);

	declparam("Z0snow", NHRU, "[0.01]", "0.0001", "0.01", "snow roughness length", "(m)", &Z0snow);

	declparam("LAI", NHRU, "[2.2]", "0.1", "20.0", "leaf-area-index", "()", &LAI);

	declparam("Sbar", NHRU, "[6.6]", "0.0", "100.0", "maximum canopy snow interception load", "(kg/m^2)", &Sbar);

	declparam("Zvent", NHRU, "[0.75]", "0.0", "1.0", "ventilation wind speed height (z/Ht)", "()", &Zvent);

	declparam("unload_t", NHRU, "[1.0]", "-10.0", "20.0", "if ice-bulb temp >= t : canopy snow is unloaded as snow", "(�C)", &unload_t);

	declparam("unload_t_water", NHRU, "[4.0]", "-10.0", "20.0", "if ice-bulb temp >= t: canopy snow is unloaded as water", "(�C)", &unload_t_water);

	declparam("CanopyClearing", NHRU, "[0]", "0", "2", "canopy - 0/clearing - 1/gap - 2", "()", &CanopyClearing);

	decldiagparam("Alpha_c", NHRU, "[0.1]", "0.05", "0.2", "canopy albedo", "()", &Alpha_c);

	decldiagparam("B_canopy", NHRU, "[0.038]", "0.0", "0.2", "canopy enhancement parameter. Suggestions are Colorado - 0.023 and Alberta - 0.038", "()", &B_canopy);
}

void ClassCRHMCanopyClearingGap::init(void) {

	nhru = getdim(NHRU); // transfers current # of HRU's to module

	for (hh = 0; hh < nhru; ++hh) {

		Pa[hh] = 101.3f*pow((293.0f - 0.0065f*hru_elev[hh]) / 293.0f, 5.26f);  // kPa

		rain_load[hh] = 0.0;
		Snow_load[hh] = 0.0;

		cum_net_snow[hh] = 0.0;
		cum_net_rain[hh] = 0.0;
		cum_Subl_Cpy[hh] = 0.0;
		cum_intcp_evap[hh] = 0.0;
		cum_SUnload[hh] = 0.0;
		cum_SUnload_H2O[hh] = 0.0;

		if (Ht[hh] > Zwind[hh]) {
			CRHMException TExcept(string("'" + Name + " (CanopyClearingGap)' Vegetation height greater than wind reference height, i.e. (Ht > Zwind)!").c_str(), WARNING);
			LogError(TExcept);
		}
	}
}

void ClassCRHMCanopyClearingGap::run(void) {

	float Exposure, LAI_, Vf, Vf_, Tau, Kstar_H, Kd;

	for (hh = 0; chkStruct(); ++hh) {

		switch (variation) {
		case VARIATION_ORG:
			Qsi_ = Qsi[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_1:
			Qsi_ = Qsi[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_2:
			Qsi_ = QsiS_Var[hh];
			Qli_ = Qli[hh];
			break;
		case VARIATION_3:
			Qsi_ = QsiS_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		case VARIATION_4:
			Qsi_ = QsiA_Var[hh];
			Qli_ = QliVt_Var[hh];
			break;
		} // switch

		net_rain[hh] = 0.0;
		direct_rain[hh] = 0.0;
		drip_Cpy[hh] = 0.0;
		intcp_evap[hh] = 0.0;

		net_snow[hh] = 0.0;
		direct_snow[hh] = 0.0;
		SUnload[hh] = 0.0;
		SUnload_H2O[hh] = 0.0;
		Subl_Cpy[hh] = 0.0;

		// Canopy temperature is approximated by the air temperature.

		float T1 = hru_t[hh] + CRHM_constants::Tm;

		float rho = Pa[hh] * 1000 / (CRHM_constants::Rgas*T1);

		float U1 = hru_u[hh]; // Wind speed (m/s)

		ra[hh] = (log(Zref[hh] / Z0snow[hh])*log(Zwind[hh] / Z0snow[hh])) / sqr(CRHM_constants::kappa) / U1;

		float deltaX = 0.622*CRHM_constants::Ls*Common::Qs(Pa[hh], T1) / (CRHM_constants::Rgas*sqr(T1));

		float q = (hru_rh[hh] / 100)*Common::Qs(Pa[hh], T1); // specific humidity (kg/kg)

		Ts[hh] = T1 + (CRHM_constants::emiss*(Qli_ - CRHM_constants::sbc*pow(T1, 4.0f)) + CRHM_constants::Ls*(q - Common::Qs(Pa[hh], T1))*rho / ra[hh]) /
			(4 * CRHM_constants::emiss*CRHM_constants::sbc*pow(T1, 3.0f) + (CRHM_constants::Cp + CRHM_constants::Ls*deltaX)*rho / ra[hh]);

		Ts[hh] -= CRHM_constants::Tm;

		if (Ts[hh] > 0.0 || SWE[hh] <= 0.0)
			Ts[hh] = 0.0;

		switch (CanopyClearing[hh]) {
		case 0: // canopy

			Exposure = Ht[hh] - DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
			if (Exposure < 0.0)
				Exposure = 0.0;

			LAI_ = LAI[hh] * Exposure / Ht[hh];

			Vf = 0.45 - 0.29*log(LAI[hh]);

			Vf_ = Vf + (1.0 - Vf)*sin((Ht[hh] - Exposure) / Ht[hh] * M_PI_2);

			if (SolAng[hh] > 0.001 && cosxs[hh] > 0.001 && cosxsflat[hh] > 0.001) {
				k[hh] = 1.081*SolAng[hh] * cos(SolAng[hh]) / sin(SolAng[hh]);
				float limit = cosxsflat[hh] / cosxs[hh];
				if (limit > 2.0)
					limit = 2.0;
				Tauc[hh] = exp(-k[hh] * LAI_*limit);
			}
			else {
				k[hh] = 0.0;
				Tauc[hh] = 0.0;
			}

			Kstar_H = Qsi_ * (1.0 - Alpha_c[hh] - Tauc[hh] * (1.0 - Albedo[hh]));

			Qlisn[hh] = Qli_ * Vf_ + (1.0f - Vf_)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f) + B_canopy[hh] * Kstar_H;

			Qlisn_Var[hh] = Qlisn[hh];

			Qsisn[hh] = Qsi_ * Tauc[hh];

			Qsisn_Var[hh] = Qsisn[hh];

			Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

			Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

			Qnsn_Var[hh] = Qnsn[hh];

			break;
		case 1:  // clearing

			Qlisn[hh] = Qli_;

			Qlisn_Var[hh] = Qlisn[hh];

			Qsisn[hh] = Qsi_;

			Qsisn_Var[hh] = Qsisn[hh];

			Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

			Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1.0 - Albedo[hh]);

			Qnsn_Var[hh] = Qnsn[hh];

			break;
		case 2:  // gap
			Exposure = Surrounding_Ht[hh] - DepthofSnow(SWE[hh]); /* depths(m) SWE(mm) */
			if (Exposure < 0.0)
				Exposure = 0.0;

			LAI_ = LAI[hh] * Exposure / Surrounding_Ht[hh];

			Vf = 0.45 - 0.29*log(LAI[hh]);

			float Tau_d = Vf + (1.0 - Vf)*sin((Surrounding_Ht[hh] - Exposure) / Surrounding_Ht[hh] * M_PI_2); // previously Vf_

																											  // calculate forest clearing sky view factor (Vgap) via Reifsnyder and Lull�s (1965) expression:

			float Vgap = sqr(sin(atan2(Gap_diameter[hh], 2.0*Surrounding_Ht[hh])));

			// calculate beam pathlength correction (variable �Gap_beam_corr�) for gap:

			float Gap_beam_corr = 0;
			if (Qsi_ > 0.0 && SolAng[hh] > 0.001) {
				float cosxsLim = 3;
				if (cosxs[hh] >  0.33)
					cosxsLim = 1.0 / cosxs[hh];

				Gap_beam_corr = cosxsLim * Surrounding_Ht[hh] * (1.0 / cos(SolAng[hh]) - Gap_diameter[hh] / (2.0*Surrounding_Ht[hh]) / sin(SolAng[hh]));
				if (Gap_beam_corr > 10.0)
					Gap_beam_corr = 10.0;
				else if (Gap_beam_corr < 0.0)
					Gap_beam_corr = 0.0;
			}
			// calculate beam shortwave transmittance of the gap:

			float product = LAI[hh] * Gap_beam_corr;
			if (product > 50)
				product = 50;

			float Tau_b_gap = exp(-product);

			Kd = Qsi_ * (1.0 - Alpha_c[hh] - Tau_b_gap * (1.0 - Albedo[hh]));

			Qlisn[hh] = Vgap * Qli_ + (1.0 - Vgap)*((Qli_*Tau_b_gap + (1.0 - Tau_b_gap)*CRHM_constants::emiss_c*CRHM_constants::sbc*pow(T1, 4.0f)) + B_canopy[hh] * Kd);

			Qlisn_Var[hh] = Qlisn[hh];

			Qsisn[hh] = cosxs[hh] * Qdfo[hh] * Tau_b_gap + Vgap * (Qsi_ - Qdfo[hh]) + (1.0 - Vgap)*Tau_d*(Qsi_ - Qdfo[hh]);
			if (Qsisn[hh] < 0.0)
				Qsisn[hh] = 0.0;

			Qsisn_Var[hh] = Qsisn[hh];

			Qlosn[hh] = CRHM_constants::emiss*CRHM_constants::sbc*pow(Ts[hh] + CRHM_constants::Tm, 4.0f);

			Qnsn[hh] = Qlisn[hh] - Qlosn[hh] + Qsisn[hh] * (1 - Albedo[hh]);

			Qnsn_Var[hh] = Qnsn[hh];

			break;
		} // switch

		switch (CanopyClearing[hh]) {
		case 0: { // canopy
				  //==============================================================================
				  // coupled forest snow interception and sublimation routine:
				  // after Hedstom & Pomeroy / Parviainen & Pomeroy:
				  // calculate maximum canopy snow load (L*):

			if (Snow_load[hh] > 0.0 || hru_snow[hh] > 0.0) { // handle snow interception

				if (Sbar[hh] >= 0.0) {
					float RhoS = 67.92 + 51.25* exp(hru_t[hh] / 2.59);
					float LStar = Sbar[hh] * (0.27 + 46.0 / RhoS)* LAI[hh];

					if (Snow_load[hh] > LStar) { // after increase in temperature
						direct_snow[hh] = Snow_load[hh] - LStar;
						Snow_load[hh] = LStar;
					}

					// calculate intercepted snowload

					if (Ht[hh] - 2.0 / 3.0*Zwind[hh] > 0.0)
						u_FHt[hh] = hru_u[hh] * log((Ht[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]) / log((Zwind[hh] - 2.0 / 3.0*Zwind[hh]) / 0.123*Zwind[hh]);
					else
						u_FHt[hh] = 0.0;

					double I1 = 0.0;

					if (hru_snow[hh] > 0.0) {
						if (fabs(hru_snow[hh] / LStar) < 50.0) {
							if (u_FHt[hh] <= 1.0)  // if wind speed at canopy top > 1 m/s
								I1 = (LStar - Snow_load[hh])*(1.0 - exp(-Cc[hh] * hru_snow[hh] / LStar));
							else
								I1 = (LStar - Snow_load[hh])*(1.0 - exp(-hru_snow[hh] / LStar));

							if (I1 <= 0)
								I1 = 0;

							Snow_load[hh] += I1;
						}

						// calculate canopy snow throughfall before unloading:

						direct_snow[hh] += (hru_snow[hh] - I1);
					}

					// calculate snow ventilation windspeed:

					//=============================================================================
					const float gamma = 1.15;
					const float AlbedoIce = 0.8;       // albedo of ideal ice sphere
					const float Radius = 5.0e-4;       // radii of single 'ideal' ice sphere in, m)
					const float KinVisc = 1.88e-5;     // kinematic viscosity of air (Sask. avg. value)
					const float ks = 0.0114;           // snow shape coefficient for jack pine
					const float Fract = 0.37;          // fractal dimension of intercepted snow
					const float ci = 2.102e-3;         // heat capacity of ice (MJ/kg/K)
					const float Hs = 2.838e6;          // heat of sublimation (MJ/kg)
													   //==============================================================================

					float xi2 = 1 - Zvent[hh];
					float windExt2 = (gamma * LAI[hh] * xi2);
					float uVent = u_FHt[hh] * exp(-1 * windExt2);

					// calculate sublimation of intercepted snow from ideal intercepted ice sphere (500 microns diameter):

					float Alpha, A1, B1, C1, J, D, Lamb, Mpm, Nu, Nr, SStar, Sigma2;

					float Es = 611.15f * exp(22.452f*hru_t[hh] / (hru_t[hh] + 273.0f));  // {sat pressure}

					float SvDens = Es * PBSM_constants::M / (PBSM_constants::R*(hru_t[hh] + 273.0f)); // {sat density}

					Lamb = 6.3e-4*(hru_t[hh] + 273.0) + 0.0673;  // thermal conductivity of atmosphere
					Nr = 2.0 * Radius * uVent / KinVisc;  // Reynolds number
					Nu = 1.79 + 0.606 * sqrt((float)Nr); // Nusselt number
					SStar = M_PI * sqr(Radius) * (1.0f - AlbedoIce) * Qsi_;  // SW to snow particle !!!! changed
					A1 = Lamb * (hru_t[hh] + 273) * Nu;
					B1 = Hs * PBSM_constants::M / (PBSM_constants::R * (hru_t[hh] + 273.0f)) - 1.0;
					J = B1 / A1;
					Sigma2 = hru_rh[hh] / 100 - 1;
					D = 2.06e-5* pow((hru_t[hh] + 273.0f) / 273.0f, -1.75f); // diffusivity of water vapour
					C1 = 1.0 / (D*SvDens*Nu);

					Alpha = 5.0;
					Mpm = 4.0 / 3.0 * M_PI * PBSM_constants::DICE * Radius*Radius*Radius *(1.0 + 3.0 / Alpha + 2.0 / sqr(Alpha));

					// sublimation rate of single 'ideal' ice sphere:

					float Vs = (2.0* M_PI* Radius*Sigma2 - SStar * J) / (Hs* J + C1) / Mpm;

					// snow exposure coefficient (Ce):

					float Ce;
					if ((Snow_load[hh] / LStar) <= 0.0)
						Ce = 0.07;
					else
						Ce = ks * pow((Snow_load[hh] / LStar), -Fract);

					// calculate 'potential' canopy sublimation:

					float Vi = Vs * Ce;

					// limit sublimation to canopy snow available and take sublimated snow away from canopy snow at timestep start

					Subl_Cpy[hh] = -Snow_load[hh] * Vi*Hs*Global::Interval * 24 * 3600 / Hs; // make W/m2
					if (Subl_Cpy[hh] > Snow_load[hh]) {
						Subl_Cpy[hh] = Snow_load[hh];
						Snow_load[hh] = 0.0;
					}
					else {
						Snow_load[hh] -= Subl_Cpy[hh];
						if (Snow_load[hh] < 0.0)
							Snow_load[hh] = 0.0;
					}

					// calculate 'ice-bulb' temperature of intercepted snow:

					float IceBulbT = hru_t[hh] - (Vi* Hs / 1e6 / ci);
					float Six_Hour_Divisor = Global::Freq / 4.0; // used to unload over 6 hours

					const float c = 0.678 / (24 * 7 * 24 / Global::Freq); // weekly dimensionless unloading coefficient -> to CRHM time interval

																		  // determine whether canopy snow is unloaded:

					if (IceBulbT >= unload_t_water[hh]) {
						drip_Cpy[hh] = Snow_load[hh] / Six_Hour_Divisor;
						SUnload_H2O[hh] = drip_Cpy[hh];
						Snow_load[hh] -= SUnload_H2O[hh];
						cum_SUnload_H2O[hh] += SUnload_H2O[hh];
					}
					else if (IceBulbT >= unload_t[hh]) {
						SUnload[hh] = Snow_load[hh] / Six_Hour_Divisor;
						Snow_load[hh] -= SUnload[hh];
						cum_SUnload[hh] += SUnload[hh];
					}
					else if (IceBulbT < unload_t[hh]) { // has to be at least one interval. Trip on half step
						SUnload[hh] = Snow_load[hh] * c; // the dimensionless unloading coefficient already /interval
						if (SUnload[hh] > Snow_load[hh]) {
							SUnload[hh] = Snow_load[hh];
							Snow_load[hh] = 0.0;
						}
						else
							Snow_load[hh] -= SUnload[hh];

						cum_SUnload[hh] += SUnload[hh];
					}

					// calculate total sub-canopy snow:

					net_snow[hh] = direct_snow[hh] + SUnload[hh];

				}// handle snow
				break;
			} // case canopy
		case 1:  // clearing
		case 2:  // gap
			net_snow[hh] = hru_snow[hh];
			net_rain[hh] = hru_rain[hh];
			break;
		}
		}  // switch

		   // calculate horizontal canopy-coverage (Cc):

		float smax, Q; // cannot be in switch structure

		switch (CanopyClearing[hh]) {

		case 0:  // canopy

			Cc[hh] = 0.29 * log(LAI[hh]) + 0.55;
			if (Cc[hh] <= 0.0)
				Cc[hh] = 0.0;

			smax = Cc[hh] * LAI[hh] * 0.2;

			//  Forest rain interception and evaporation model
			// 'sparse' Rutter interception model (i.e. Valente 1997):

			// calculate direct throughfall:

			if (hru_rain[hh] > 0.0) {

				direct_rain[hh] = hru_rain[hh] * (1 - Cc[hh]);

				// calculate rain accumulation on canopy before evap loss:

				if (rain_load[hh] + hru_rain[hh] * Cc[hh] > smax) {
					drip_Cpy[hh] += (rain_load[hh] + hru_rain[hh] * Cc[hh] - smax);
					rain_load[hh] = smax;
				}
				else
					rain_load[hh] += hru_rain[hh] * Cc[hh];

			}  // if hru_rain[hh] > 0.0

			   // calculate 'actual evap' of water from canopy and canopy storage after evaporation::

			if (rain_load[hh] > 0.0) {
				if (inhibit_evap[hh] == 0) { // use Granger when no snowcover
					if (rain_load[hh] >= hru_evap[hh] * Cc[hh]) { // (evaporation in mm)
						intcp_evap[hh] = hru_evap[hh] * Cc[hh];  //
						rain_load[hh] -= hru_evap[hh] * Cc[hh];
					}
					else {
						intcp_evap[hh] = rain_load[hh];
						rain_load[hh] = 0.0;
					}
				}
				else { // use Priestley-Taylor when snowcover
					Q = Qsi_ * 86400 / Global::Freq / 1e6 / lambda(hru_t[hh]); // convert w/m2 to mm/m2/int

					if (Qsi_ > 0.0)
						Pevap[hh] = 1.26*delta(hru_t[hh])*Q / (delta(hru_t[hh]) + gamma(Pa[hh], hru_t[hh]));
					else
						Pevap[hh] = 0.0;

					if (rain_load[hh] >= Pevap[hh] * Cc[hh]) {  // (evaporation in mm)
						intcp_evap[hh] = Pevap[hh] * Cc[hh];  // check
						rain_load[hh] -= Pevap[hh] * Cc[hh];
					}
					else {
						intcp_evap[hh] = rain_load[hh]; // check
						rain_load[hh] = 0.0;
					}
				}
			} // if rain_load[hh] > 0.0

			  // cumulative amounts....

			net_rain[hh] = direct_rain[hh] + drip_Cpy[hh];

			cum_intcp_evap[hh] += intcp_evap[hh];
			cum_Subl_Cpy[hh] += Subl_Cpy[hh];
			break;
		default:  // clearing and gap
			break;
		}  // switch

		net_p[hh] = net_rain[hh] + net_snow[hh];
		cum_net_rain[hh] += net_rain[hh];
		cum_net_snow[hh] += net_snow[hh];
	} // end for
}

void ClassCRHMCanopyClearingGap::finish(bool good) {
	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (CanopyClearingGap)'  cum_net_snow    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_snow[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearingGap)'  cum_net_rain    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_net_rain[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearingGap)'  cum_Subl_Cpy    (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_Subl_Cpy[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearingGap)'  cum_intcp_evap  (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (CanopyClearingGap)'  cum_SUnload_H2O (mm) (mm*hru) (mm*hru/basin): ").c_str(), cum_intcp_evap[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");
	}
}

double ClassCRHMCanopyClearingGap::delta(float t) // Slope of sat vap p vs t, kPa/�C
{
	if (t > 0.0)
		return(2504.0*exp(17.27 * t / (t + 237.3)) / sqr(t + 237.3));
	else
		return(3549.0*exp(21.88 * t / (t + 265.5)) / sqr(t + 265.5));
}

float ClassCRHMCanopyClearingGap::lambda(float t) // Latent heat of vaporization (mJ/(kg �C))
{
	return(2.501 - 0.002361 * t);
}

double ClassCRHMCanopyClearingGap::gamma(float Pa, float t) // Psychrometric constant (kPa/�C)
{
	return(0.00163 * Pa / lambda(t)); // lambda (mJ/(kg �C))
}

float ClassCRHMCanopyClearingGap::RHOa(float t, float ea, float Pa) // atmospheric density (kg/m^3)
{
	const float R = 2870;
	return (1E4*Pa / (R*(273.15 + t))*(1.0 - 0.379*(ea / Pa))); //
}

ClassWQ_Netroute_M_D* ClassWQ_Netroute_M_D::klone(string name) const {
	return new ClassWQ_Netroute_M_D(name);
}

float ClassWQ_Netroute_M_D::Function1(float *I, long hh) {
	return runDelay->ChangeLag(I, hh);
}

float ClassWQ_Netroute_M_D::Function2(float *X, long hh) {
	return runDelay->ChangeStorage(X, hh);
}

void ClassWQ_Netroute_M_D::decl(void) {

	Description = "'Handles the routing of surface runoff, subsurface runoff and HRU routing using the lag and route method.'";

	declvar("inflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &inflow);

	declvar("inflow_conc", NHRU, "Concentration: inflow from other HRUs", "(g/l)", &inflow_conc);

	declstatdiag("cuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &cuminflow);

	declstatdiag("cuminflow_mWQ", NHRU, "cumulative mass of solute inflow from other HRUs", "(g*km^2)", &cuminflow_mWQ);

	declvar("outflow", NHRU, "HRU outflow", "(mm*km^2/int)", &outflow);

	declvar("outflow_conc", NHRU, "Concentration: HRU outflow", "(g/l)", &outflow_conc);

	declstatdiag("cumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &cumoutflow);

	declstatdiag("cumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(g*km^2)", &cumoutflow_mWQ);

	decldiag("outflow_diverted", NHRU, "HRU outflow diverted to another HRU", "(mm*km^2/int)", &outflow_diverted);

	decldiag("outflow_diverted_conc", NHRU, "Concentration: HRU outflow diverted to another HRU", "(g/l)", &outflow_diverted_conc);

	declstatdiag("cumoutflow_diverted", NHRU, "cumulative HRU outflow diverted to another HRU", "(mm*km^2/int)", &cumoutflow_diverted);

	declstatdiag("cumoutflow_diverted_mWQ", NHRU, "cumulative mass of solute HRU outflow diverted to another HRU", "(g*km^2/int)", &cumoutflow_diverted_mWQ);

	declstatdiag("cum_to_Sd", NHRU, "cumulative other HRU to depressional storage (Sd) of this HRU", "(mm)", &cum_to_Sd);

	declstatdiag("cum_to_Sd_mWQ", NHRU, "cumulative mass of solute from other HRU to depressional storage (Sd) of this HRU", "(g)", &cum_to_Sd_mWQ);

	declstatdiag("cum_to_soil_rechr", NHRU, "cumulative other HRU to soil_rechr of this HRU", "(mm)", &cum_to_soil_rechr);

	declstatdiag("cum_to_soil_rechr_mWQ", NHRU, "cumulative mass of solute from other HRU to soil_rechr of this HRU", "(g)", &cum_to_soil_rechr_mWQ);

	declvar("gwinflow", NHRU, "ground water inflow", "(mm*km^2/int)", &gwinflow);

	declvar("gwinflow_conc", NHRU, "Concentration: ground water inflow", "(g/l)", &gwinflow_conc);

	declstatdiag("gwcuminflow", NHRU, "cumulative gw inflow", "(mm*km^2)", &gwcuminflow);

	declstatdiag("gwcuminflow_mWQ", NHRU, "cumulative mass of solute gw inflow", "(g*km^2)", &gwcuminflow_mWQ);

	declvar("gwoutflow", NHRU, "HRU gw outflow", "(mm*km^2/int)", &gwoutflow);

	declvar("gwoutflow_mWQ", NHRU, "Concentration: HRU gw outflow", "(g/l)", &gwoutflow_mWQ);

	declstatdiag("gwcumoutflow", NHRU, "cumulative HRU gw outflow", "(mm*km^2)", &gwcumoutflow);

	declstatdiag("gwcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU gw outflow", "(g*km^2)", &gwcumoutflow_mWQ);

	decldiag("gwoutflow_diverted", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted);

	decldiag("gwoutflow_diverted_conc", NHRU, "HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwoutflow_diverted_conc);

	declstatdiag("gwcumoutflow_diverted", NHRU, "cumulative HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted);

	declstatdiag("gwcumoutflow_diverted_mWQ", NHRU, "cumulative mass of solute HRU gw outflow diverted to another HRU", "(mm*km^2/int)", &gwcumoutflow_diverted_mWQ);

	declvar("ssrinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &ssrinflow);

	declvar("ssrinflow_conc", NHRU, "Concentration: inflow from other HRUs", "(g/l)", &ssrinflow_conc);

	declstatdiag("ssrcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &ssrcuminflow);

	declstatdiag("ssrcuminflow_mWQ", NHRU, "cumulative mass of solute of inflow from other HRUs", "(g*km^2)", &ssrcuminflow_mWQ);

	declvar("ssroutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &ssroutflow);

	declvar("ssroutflow_mWQ", NHRU, "Concentration: HRU outflow", "(g/l)", &ssroutflow_mWQ);

	declstatdiag("ssrcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &ssrcumoutflow);

	declstatdiag("ssrcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(g*km^2)", &ssrcumoutflow_mWQ);

	declstatdiag("HRU_cumbasinflow", NHRU, "cumulative HRU to basinflow", "(mm*km^2)", &HRU_cumbasinflow);

	declstatdiag("HRU_cumbasinflow_conc", NHRU, "cumulative mass of solute HRU to basinflow", "(g*km^2)", &HRU_cumbasinflow_conc);

	declstatdiag("cum_preferential_flow_to_gw", NHRU, "cumulative other HRU's runoff to this HRU's gw via preferential flow path", "(mm)", &cum_preferential_flow_to_gw);

	declparam("preferential_flow", NHRU, "[0]", "0", "1", "0 - no preferential and remain as runoff routing to other HRU, 1 - preferential flow and route runoff to other HRU's gw.", "()", &preferential_flow);

	declvar("runinflow", NHRU, "inflow from other HRUs", "(mm*km^2/int)", &runinflow);

	declvar("runinflow_conc", NHRU, "Concentration: inflow from other HRUs", "(g/l)", &runinflow_conc);

	declstatdiag("runcuminflow", NHRU, "cumulative inflow from other HRUs", "(mm*km^2)", &runcuminflow);

	declstatdiag("runcuminflow_mWQ", NHRU, "cumulative mass of solute inflow from other HRUs", "(g*km^2)", &runcuminflow_mWQ);

	declvar("runoutflow", NHRU, "HRU outflow", "(mm*km^2/int)", &runoutflow);

	declvar("runoutflow_mWQ", NHRU, "Concentration: HRU outflow", "(g/l)", &runoutflow_mWQ);

	declstatdiag("runcumoutflow", NHRU, "cumulative HRU outflow", "(mm*km^2)", &runcumoutflow);

	declstatdiag("runcumoutflow_mWQ", NHRU, "cumulative mass of solute HRU outflow", "(g*km^2)", &runcumoutflow_mWQ);


	declstatdiag("cumscaling_boost", NHRU, "cumulative amout inflow boosted", "(mm*km^2)", &cumscaling_boost);

	declvar("basinflow", BASIN, "basin surface and sub-surface outflow", "(m^3/int)", &basinflow);

	declvar("basinflow_mWQ", BASIN, "basin surface and sub-surface outflow", "(g/l)", &basinflow_mWQ);

	decldiag("basinflow_s", BASIN, "basin surface and sub-surface outflow", "(m^3/s)", &basinflow_s);

	declstatdiag("cumbasinflow", BASIN, "cumulative basin surface and sub-surface outflow", "(m^3)", &cumbasinflow);

	declstatdiag("cumbasinflow_mWQ", BASIN, "cumulative mass of solute basin surface and sub-surface outflow", "(m^3)", &cumbasinflow_mWQ);

	declvar("basingw", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw);

	declvar("basingw_mWQ", BASIN, "cumulative basin groundwater outflow", "(m^3/int)", &basingw_mWQ);

	decldiag("basingw_s", BASIN, "cumulative basin groundwater outflow", "(m^3/s)", &basingw_s);

	declstatdiag("cumbasingw", BASIN, "cumulative basin groundwater outflow", "(m^3)", &cumbasingw);

	declstatdiag("cumbasingw_mWQ", BASIN, "cumulative mass of solute basin groundwater outflow", "(m^3)", &cumbasingw_mWQ);

	decllocal("soil_ssr_Buf", NHRU, "buffer subsurface runoff", "(mm/d)", &soil_ssr_Buf);

	decllocal("meltrunoff_Buf", NHRU, "buffer melt runoff", "(mm/d)", &meltrunoff_Buf);

	decllocal("soil_runoff_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_runoff_Buf);

	decllocal("soil_gw_Buf", NHRU, "buffer rain runoff", "(mm/d)", &soil_gw_Buf);

	decllocal("Ktravel", NHRU, "travel time", "(d)", &Ktravel);

	decllocal("distrib_sum", NHRU, "HRU distribution sum", "()", &distrib_sum);


	declparam("basin_area", BASIN, "3", "1e-6", "1e09", "Total basin area", "(km^2)", &basin_area);

	declparam("hru_area", NHRU, "[1]", "1e-6", "1e09", "HRU area", "(km^2)", &hru_area);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "lag delay", "(h)", &Lag);

	declparam("route_n", NHRU, "[0.025]", "0.016", "0.2", "Manning roughness coefficient", "()", &route_n);

	declparam("route_R", NHRU, "[0.5]", "0.01", "1.0E4", "hydraulic radius", "(m)", &route_R);

	declparam("route_S0", NHRU, "[1e-3]", "1e-6", "1.0", "longitudinal channel slope", "()", &route_S0);

	declparam("route_L", NHRU, "[200.0]", "0.01", "1.0E10", "routing length", "(m)", &route_L);

	declparam("route_X_M", NHRU, "[0.25]", "0.0", "0.5", "dimensionless weighting factor", "()", &route_X_M);

	declparam("Lag", NHRU, "[0.0]", "0.0", "1.0E4.0", "aggregated lag delay", "(h)", &Lag);

	declparam("ssrKstorage", NHRU, "[0.0]", "0.0", "200.0", "subsurface runoff storage constant", "(d)", &ssrKstorage);

	declparam("ssrLag", NHRU, "[0.0]", "0.0", "1.0E4.0", "subsurface runoff lag delay", "(h)", &ssrLag);

	declparam("runKstorage", NHRU, "[0.0]", "0.0", "200.0", "runoff storage constant", "(d)", &runKstorage);

	declparam("runLag", NHRU, "[0.0]", "0.0", "1.0E4", "runoff lag delay", "(h)", &runLag);

	declparam("gwKstorage", NHRU, "[0.0]", "0.0", "200.0", "gw storage constant", "(d)", &gwKstorage);

	declparam("gwLag", NHRU, "[0.0]", "0.0", "1.0E4", "gw lag delay", "(h)", &gwLag);

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);

	declparam("distrib_Route", NDEFN, "[0.0]", "-1.0E6.0", "1.0E6.0", "route this HRU to these HRUs", "()", &distrib, &distrib_hru, nhru);

	declparam("distrib_Basin", NHRU, "[1.0]", "0.0", "100.0", "route this HRU to basin (and other HRU(s) determined by 'distrib_Route')", "()", &distrib_Basin);

	declparam("gwwhereto", NHRU, "[0]", "-1000", "1000", "send to: 0 - basingw, >0 - other HRU surface input <0 - other abs(-HRU) gw input, or (< -HRUmax or > +HRUmax) - surface basinflow", "()", &gwwhereto);

	declparam("Sdmax", NHRU, "[0]", "0.0", "1000.0", "Maximum depression storage", "(mm)", &Sdmax);

	declparam("soil_rechr_max", NHRU, "[60.0]", "0.0", "350.0", "soil recharge maximum (<= soil_moist_max).", "(mm)", &soil_rechr_max);

	decldiagparam("Sd_ByPass", NHRU, "[0]", "0", "1", "0 - normal, 1 - Bypass Pond/Depressional storage (i.e. Sd).", "()", &Sd_ByPass);

	decldiagparam("soil_rechr_ByPass", NHRU, "[1]", "0", "1", "0 - normal, 1 - Bypass recharge layer (i.e. soil_rechr).", "()", &soil_rechr_ByPass);


	declparam("Channel_shp", NHRU, "[0]", "0", "2", "rectangular - 0/parabolic - 1/triangular - 2", "()", &route_Cshp);

	decldiagparam("scaling_factor", NHRU, "[1.0]", "0.0", "1.0E6", "multiplies the input to Muskingum by this scaling factor.", "()", &scaling_factor); // temporary

	declparam("order", NHRU, "[1,2,3,4,5!]", "1", "1000", "HRU routing process order", "()", &order);


	soil_gwDiv = declgetvar("*", "gw_flow", "(mm/int)", &soil_gw);

	declgetvar("*", "gw_flow_conc", "(g)", &soil_gw_conc);

	soil_ssrDiv = declgetvar("*", "soil_ssr", "(mm/int)", &soil_ssr);

	declgetvar("*", "soil_ssr_conc", "(g)", &soil_ssr_conc);

	soil_runoffDiv = declgetvar("*", "soil_runoff", "(mm/int)", &soil_runoff);

	declgetvar("*", "soil_runoff_conc", "(g)", &soil_runoff_conc);


	declputvar("*", "Sd", "(mm)", &Sd);

	declputvar("*", "Sd_conc", "(g)", &Sd_conc);

	declputvar("*", "soil_moist", "(mm)", &soil_moist);

	declputvar("*", "soil_moist_conc", "(g)", &soil_moist_conc);

	declputvar("*", "soil_lower", "(mm)", &soil_lower);

	declputvar("*", "soil_lower_conc", "(g)", &soil_lower_conc);

	declputvar("*", "soil_rechr", "(mm)", &soil_rechr);

	declputvar("*", "soil_rechr_conc", "(g)", &soil_rechr_conc);

	declputvar("*", "redirected_residual", "(mm*km^2/int)", &redirected_residual);

	declputvar("*", "redirected_residual_conc", "(g)", &redirected_residual_conc);

	declputvar("*", "cum_redirected_residual", "(mm*km^2/int)", &cum_redirected_residual);

	declputvar("*", "cum_redirected_residual_mWQ", "(g)", &cum_redirected_residual_mWQ);

	declputvar("*", "gw", "(mm)", &gw);

	declputvar("*", "gw_conc", "(g)", &gw_conc);
}

void ClassWQ_Netroute_M_D::init(void) {

	nhru = getdim(NHRU);

	if (soil_ssrDiv > 1) {
	 string S = "WQ_Netroute_M_D:  \"soil_ssr\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_runoffDiv > 1) {
	 string S = "WQ_Netroute_M_D:  \"soil_runoff\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	if (soil_gwDiv > 1) {
	 string S = "WQ_Netroute_M_D:  \"gw_flow\". Converting to mm/int";
		CRHMException TExcept(S.c_str(), WARNING);
		LogError(TExcept);
	}

	const float Vw[3] = { 1.67, 1.44, 1.33 }; // rectangular - 0/parabolic - 1/triangular - 2

	for (hh = 0; hh < nhru; ++hh) {
		float Vavg = (1.0 / route_n[hh])*pow(route_R[hh], 2.0 / 3.0)*pow(route_S0[hh], 0.5f); // (m/s)
		Ktravel[hh] = route_L[hh] / (Vw[route_Cshp[hh]] * Vavg) / 86400.0; // (d)
	}

	hruDelay = new ClassMuskingum(inflow, outflow, Ktravel, route_X_M, Lag, nhru);
	ssrDelay = new ClassClark(ssrinflow, ssroutflow, ssrKstorage, ssrLag, nhru);
	runDelay = new ClassClark(runinflow, runoutflow, runKstorage, runLag, nhru);
	gwDelay = new ClassClark(gwinflow, gwoutflow, gwKstorage, gwLag, nhru);

	hruDelay_cWQ = new ClassMuskingum(inflow_conc, outflow_conc, Ktravel, route_X_M, Lag, nhru);  // check parameters
	ssrDelay_cWQ = new ClassClark(ssrinflow_conc, ssroutflow_mWQ, ssrKstorage, ssrLag, nhru);
	runDelay_cWQ = new ClassClark(runinflow_conc, runoutflow_mWQ, runKstorage, runLag, nhru);
	gwDelay_cWQ = new ClassClark(gwinflow_conc, gwoutflow_mWQ, gwKstorage, gwLag, nhru);

	for (hh = 0; hh < nhru; ++hh) {
		if (Ktravel[hh] >= (Global::Interval / (2.0*route_X_M[hh]))) {
		 string S = string("'" + Name + " (WQ_Netroute_M_D) Muskingum coefficient negative in HRU ").c_str() + std::to_string(hh + 1);
			CRHMException TExcept(S.c_str(), WARNING);
			LogError(TExcept);
		}

		if (Ktravel[hh] < (Global::Interval / (2.0*(1.0 - route_X_M[hh])))) { //    if(hruDelay->c0[hh] < 0.0)
			hruDelay->c0[hh] = 0.0;
			hruDelay->c1[hh] = 1.0;
			hruDelay->c2[hh] = 0.0;
		}
	}

	Reset_WQ(0, basinflow, basinflow_mWQ);
	basinflow_s[0] = 0.0;
	Reset_WQ(0, cumbasinflow, cumbasinflow_mWQ);
	Reset_WQ(0, basingw, basingw_mWQ);
	basingw_s[0] = 0.0;
	Reset_WQ(0, cumbasingw, cumbasingw_mWQ);

	for (hh = 0; hh < nhru; ++hh) {

		Reset_WQ(hh, HRU_cumbasinflow, HRU_cumbasinflow_conc); HRU_cumbasinflow[hh] = 0.0;

		Reset_WQ(hh, inflow, inflow_conc);
		Reset_WQ(hh, cuminflow, cuminflow_mWQ);
		Reset_WQ(hh, outflow, outflow_conc);
		cumscaling_boost[hh] = 0.0;

		Reset_WQ(hh, gwinflow, gwinflow_conc); ;
		Reset_WQ(hh, gwcuminflow, gwcuminflow_mWQ); ;
		Reset_WQ(hh, gwoutflow, gwoutflow_mWQ);
		Reset_WQ(hh, gwcumoutflow, gwcumoutflow_mWQ);

		Reset_WQ(hh, ssrinflow, ssrinflow_conc);
		Reset_WQ(hh, ssrcuminflow, ssrcuminflow_mWQ);
		Reset_WQ(hh, ssroutflow, ssroutflow_mWQ);
		Reset_WQ(hh, ssrcumoutflow, ssrcumoutflow_mWQ);

		Reset_WQ(hh, runinflow, runinflow_conc);
		Reset_WQ(hh, runcuminflow, runcuminflow_mWQ);
		Reset_WQ(hh, runoutflow, runoutflow_mWQ);
		Reset_WQ(hh, runcumoutflow, runcumoutflow_mWQ);

		Reset_WQ(hh, outflow_diverted, outflow_diverted_conc);
		cumoutflow_diverted[hh] = 0.0;
		cumoutflow_diverted_mWQ[hh] = 0.0;

		Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc);
		Reset_WQ(hh, gwcumoutflow_diverted, gwcumoutflow_diverted_mWQ);

		cum_to_Sd[hh] = 0.0;
		cum_to_Sd_mWQ[hh] = 0.0;
		cum_to_soil_rechr[hh] = 0.0;
		cum_to_soil_rechr_mWQ[hh] = 0.0;

		soil_ssr_Buf[hh] = 0.0;
		meltrunoff_Buf[hh] = 0.0;
		soil_runoff_Buf[hh] = 0.0;
		soil_gw_Buf[hh] = 0.0;

		bool OK = false;
		for (long jj = 0; chkStruct(jj); ++jj)
			if (order[jj] - 1 == hh) {
				OK = true;
				break;
			}

		if (!OK) {
		 string SS = string("'" + Name + " (WQ_Netroute_M_D)' the 'order' parameter does not have a unique value for each HRU");
			CRHMException Except(SS.c_str(), ERR);
			LogError(Except);
			throw Except;
		}
	}
}

void ClassWQ_Netroute_M_D::run(void) {

	long step = getstep();
	long nstep = step % Global::Freq;

	Reset_WQ(0, basinflow, basinflow_mWQ);
	Reset_WQ(0, basingw, basingw_mWQ);

	if (getstep() == 1) {
		for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence.
			distrib_sum[hh] = 0.0;

			for (long hhh = 0; chkStruct(hhh); ++hhh) { // do HRUs in sequence
				if (distrib_hru[hh][hhh] < 0.0)
					const_cast<float **> (distrib_hru)[hh][hhh] = -distrib_hru[hh][hhh] * hru_area[hh];
				distrib_sum[hh] += distrib_hru[hh][hhh];
			}

			if (distrib_sum[hh] <= 0 && distrib_Basin[hh] <= 0.0) {
				const_cast<float *> (distrib_Basin)[hh] = 1;
			}

			distrib_sum[hh] += distrib_Basin[hh];
		}
	}

	float gw_amount;

	for (long jj = 0; chkStruct(jj); ++jj) { // HRUs not in sequence

		for (hh = 0; chkStruct(hh); ++hh)
			if (order[hh] - 1 == jj)
				break;

		if (soil_gwDiv == 1) // interval value
			soil_gw_Buf[hh] = soil_gw[hh];

		gwinflow[hh] = soil_gw_Buf[hh] * hru_area[hh];
		gwinflow_conc[hh] = soil_gw_conc[hh];

		Reset_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc);

		gw_amount = 0.0;

		for (long hhh = 0; chkStruct(hhh); ++hhh) {
			if (gwoutflow[hhh] > 0.0 && gwwhereto[hhh] && (abs(gwwhereto[hhh]) - 1 == hh || abs(gwwhereto[hhh]) > nhru)) { // handles "gwwhereto" <> 0
				Set_WQ(hh, gwoutflow_diverted, gwoutflow_diverted_conc, gwoutflow[hhh] / hru_area[hh], gwoutflow_mWQ[hhh]); // gwoutflow_diverted[hh] = gwoutflow[hhh];
				gw_amount = gwoutflow_diverted[hh] / hru_area[hh]; // units (mm*km^2/int)

				gwcumoutflow_diverted[hh] += gw_amount;
				gwcumoutflow_diverted_mWQ[hh] += gw_amount * gwoutflow_mWQ[hhh];

				if (abs(gwwhereto[hhh]) <= nhru) {
					if (gwwhereto[hhh] > 0) { // direct to HRU surface
						float free = soil_rechr_max[hh] - soil_rechr[hh];
						if (free > 0.0 && !soil_rechr_ByPass[hh]) {
							if (free > gw_amount) { // units (mm*km^2/int)

								Add_WQ(hh, soil_rechr, soil_rechr_conc, gw_amount, gwoutflow_mWQ[hh]); // soil_rechr[hh] += gw_amount/hru_area[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, gw_amount, gwoutflow_mWQ[hh]); // soil_moist[hh] += gw_amount/hru_area[hh];

								cum_to_soil_rechr[hh] += gw_amount;
								cum_to_soil_rechr_mWQ[hh] += gw_amount * gwoutflow_mWQ[hh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								cum_to_soil_rechr_mWQ[hh] += free * gwoutflow_mWQ[hh];

								Set_WQ(hh, soil_rechr, soil_rechr_conc, soil_rechr_max[hh], gwoutflow_mWQ[hh]); // soil_rechr[hh] = soil_rechr_max[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, free, gwoutflow_mWQ[hh]); // soil_moist[hh] += free;
							}
						}

						free = Sdmax[hh] - Sd[hh];
						if (free > 0.0 && gw_amount > 0.0 && !Sd_ByPass[hh]) {
							if (free > gw_amount) { // units (mm*km^2/int)
								Add_WQ(hh, Sd, Sd_conc, gw_amount, gwoutflow_mWQ[hhh]); // Sd[hh] += gw_amount/hru_area[hh];
								cum_to_Sd[hh] += gw_amount;
								cum_to_Sd_mWQ[hh] += gw_amount * gwoutflow_mWQ[hhh];
								gw_amount = 0.0;
							}
							else {
								gw_amount = (gw_amount - free);
								cum_to_Sd[hh] += free;
								cum_to_Sd_mWQ[hh] += free * gwoutflow_mWQ[hhh];
								Set_WQ(hh, Sd, Sd_conc, Sdmax[hh], gwoutflow_mWQ[hh]); // Sd[hh] = Sdmax[hh];
							}
						}
					} // hh > 0
					else { // hh < 0
						Add_WQ(hh, gw, gw_conc, gw_amount / hru_area[hh], gwoutflow_mWQ[hh]); // gw[hh] +=  gw_amount/hru_area[hh];
						gw_amount = 0.0;
					}
				} // is HRU
				else if (gw_amount > 0.0) { // > nhru then put in basinflow
					basinflow[0] += gw_amount * 1000; // (m3)
					HRU_cumbasinflow[hh] = gw_amount;
					cumoutflow[hh] += gw_amount;
					gw_amount = 0.0;
				}
			} // match hh
		} // for hhh

		gwcuminflow[hh] += gwinflow[hh];
		gwcuminflow_mWQ[hh] += gwinflow[hh] * gwinflow_conc[hh];
		outflow_diverted[hh] = 0.0;
	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) { // do HRUs in sequence

		if (soil_ssrDiv == 1) // interval value
			soil_ssr_Buf[hh] = soil_ssr[hh];

		if (soil_runoffDiv == 1) // interval value
			soil_runoff_Buf[hh] = soil_runoff[hh];

		Set_WQ(hh, runinflow, runinflow_conc, soil_runoff_Buf[hh] * hru_area[hh], soil_runoff_conc[hh]); // runinflow[hh] = soil_runoff_Buf[hh]*hru_area[hh]; // includes melt and rain runoff
		runcuminflow[hh] += runinflow[hh];
		runcuminflow_mWQ[hh] += runinflow[hh] * soil_runoff_conc[hh];


		Set_WQ(hh, ssrinflow, ssrinflow_conc, soil_ssr_Buf[hh] * hru_area[hh], soil_ssr_conc[hh]); // ssrinflow[hh] = soil_ssr_Buf[hh]*hru_area[hh]; // subsurface runoff
		ssrcuminflow[hh] += ssrinflow[hh];
		ssrcuminflow_mWQ[hh] += ssrinflow[hh] * soil_ssr_conc[hh];

		ssrcumoutflow[hh] += ssroutflow[hh];
		ssrcumoutflow_mWQ[hh] += ssroutflow[hh] * ssroutflow_mWQ[hh];
		runcumoutflow[hh] += runoutflow[hh];
		runcumoutflow_mWQ[hh] += runoutflow[hh] * runoutflow_mWQ[hh];

		inflow[hh] = scaling_factor[hh] * (runoutflow[hh] + ssroutflow[hh]); // add this HRU runoff and subsurface flow
		if (inflow[hh])
			inflow_conc[hh] = (runoutflow[hh] * runoutflow_mWQ[hh] + ssroutflow_mWQ[hh] * ssroutflow[hh]) / inflow[hh];
		else
			inflow_conc[hh] = 0.0;

		//    cuminflow[hh] += inflow[hh];
		//    cuminflow_mWQ[hh] += inflow[hh]*inflow_conc[hh];

		if (outflow[hh] > 0.0) {

			float Used = outflow[hh] * distrib_Basin[hh] / distrib_sum[hh];
			if (distrib_Basin[hh] > 0.0) { // direct to basin
				basinflow[0] += Used * 1000; // (m3)
				HRU_cumbasinflow[hh] += Used;
				cumoutflow[hh] += Used;
				HRU_cumbasinflow_conc[hh] += outflow[hh] * outflow_conc[hh];
				cumoutflow_mWQ[hh] += outflow[hh] * outflow_conc[hh];
			}
			for (long To = 0; chkStruct(To); ++To) { // distribute outflow of HRUs

				if (hh != To && distrib_hru[hh][To] > 0.0) {
					float Amount = (outflow[hh] - Used) / hru_area[To] * distrib_hru[hh][To] / (distrib_sum[hh] - distrib_Basin[hh]); // outflow (mm*km^2/int)

					if (preferential_flow[hh]) {
						gw[To] += Amount;
						cum_preferential_flow_to_gw[To] += Amount;
						Amount = 0.0;
					}
					else {
						float free = soil_rechr_max[To] - soil_rechr[To];
						if (free > 0.0 && !soil_rechr_ByPass[To]) {
							if (free > Amount) { // outflow (mm*km^2/int)
								Add_WQ(hh, soil_rechr, soil_rechr_conc, Amount, outflow_conc[To]); // soil_rechr[hh] += outflow[hhh]/hru_area[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, Amount, outflow_conc[To]); // soil_moist[hh] += outflow[hhh]/hru_area[hh];
								cum_to_soil_rechr[hh] += Amount;
								cum_to_soil_rechr_mWQ[hh] += Amount * outflow_conc[To];
								Amount = 0.0; // outflow[To] = 0.0;
							}
							else {
								Amount = (Amount - free); // outflow[hhh] = (outflow[To]/hru_area[hh] - free)*hru_area[hh];
								cum_to_soil_rechr[hh] += free;
								cum_to_soil_rechr_mWQ[hh] += free * outflow_conc[To];

								Set_WQ(hh, soil_rechr, soil_rechr_conc, soil_rechr_max[hh], outflow_conc[hh]); // soil_rechr[hh] = soil_rechr_max[hh];
								Add_WQ(hh, soil_moist, soil_moist_conc, free, outflow_conc[hh]); // soil_moist[hh] += free;
							}
						} // if

						free = Sdmax[To] - Sd[To];
						if (free > 0.0 && !Sd_ByPass[To] && Amount > 0.0) {
							if (free > Amount) { // units (mm*km^2/int)
								Add_WQ(hh, Sd, Sd_conc, Amount, outflow_conc[To]); // Sd[hh] += outflow[To]/hru_area[hh];
								cum_to_Sd[hh] += Amount;
								cum_to_Sd_mWQ[hh] += Amount * outflow_conc[To];
								Amount = 0.0; // outflow[To] = 0.0;
							}
							else {
								Amount = (Amount - free); // outflow[hhh] = (outflow[To]/hru_area[hh] - free)*hru_area[hh];
								cum_to_Sd[hh] += free;
								cum_to_Sd_mWQ[hh] += free * outflow_conc[To];
								Set_WQ(hh, Sd, Sd_conc, Sdmax[hh], outflow_conc[hh]); // Sd[hh] = Sdmax[hh];
							}
						} // if
					} // else

					if (Amount > 0.0)
						redirected_residual[To] += Amount * hru_area[To]; // Return to module soil. Previously handled by Netroute. (mm*km^2/int)

				} // contribute to this HRU
			} // distribute outflow over HRUs (To)
		} // outflow > 0.0

		if (gwwhereto[hh] == 0) { // move to basin gw
			basingw[0] += gwoutflow[hh] * 1000; // (m3) end of every day
			gwcumoutflow[hh] += gwoutflow[hh];
		}

		if (nstep == 0) { // end of every day
			if (soil_ssrDiv > 1) // daily value - ready for next day
				soil_ssr_Buf[hh] = soil_ssr[hh] / soil_ssrDiv;

			if (soil_runoffDiv > 1) // daily value - ready for next day
				soil_runoff_Buf[hh] = soil_runoff[hh] / soil_runoffDiv;

			if (soil_gwDiv > 1) // daily value - ready for next day
				soil_gw_Buf[hh] = soil_gw[hh] / soil_gwDiv;
		} // end if

		Sub_WQ(hh, soil_lower, soil_lower_conc, soil_moist, soil_moist_conc, soil_rechr, soil_rechr_conc);
	} // for hh

	for (hh = 0; chkStruct(hh); ++hh) {
		cuminflow[hh] += inflow[hh];
		cumscaling_boost[hh] += inflow[hh] * (scaling_factor[hh] - 1.0);

		outflow_diverted[hh] = 0.0;
		if (distrib_sum[hh] > 0.0) { // does not apply to last HRU
			for (long hhh = 0; chkStruct(hhh); ++hhh) {
				outflow_diverted[hh] += outflow[hh] * distrib_hru[hh][hhh] / distrib_sum[hh];
			}
		}
		cumoutflow_diverted[hh] += outflow_diverted[hh];
	} //end for

	hruDelay->DoMuskingum();
	runDelay->DoClark();
	ssrDelay->DoClark();
	gwDelay->DoClark();

	hruDelay_cWQ->DoMuskingum();
	runDelay_cWQ->DoClark();
	ssrDelay_cWQ->DoClark();
	gwDelay_cWQ->DoClark();

	basinflow_s[0] = basinflow[0] * Global::Freq / 86400.0;
	basingw_s[0] = basingw[0] * Global::Freq / 86400.0;

	cumbasinflow[0] += basinflow[0];
	cumbasinflow_mWQ[0] += basinflow[0] * outflow_conc[hh];
	cumbasingw[0] += basingw[0];
	cumbasingw_mWQ[0] += basingw[0] * gwoutflow_mWQ[hh];
}

void ClassWQ_Netroute_M_D::finish(bool good) {

	float Allcuminflow = 0.0;
	float Allcumoutflow = 0.0;
	float Allcumoutflowdiverted = 0.0;

	float Allcuminflow_mWQ = 0.0;
	float Allcumoutflow_mWQ = 0.0;
	float Allcumoutflowdiverted_mWQ = 0.0;

	float Allgwcuminflow = 0.0;
	float Allgwcumoutflow = 0.0;
	float Allgwcumoutflowdiverted = 0.0;

	float Allgwcuminflow_mWQ = 0.0;
	float Allgwcumoutflow_mWQ = 0.0;
	float Allgwcumoutflowdiverted_mWQ = 0.0;

	float Allssrcuminflow = 0.0;
	float Allssrcumoutflow = 0.0;
	float Allruncuminflow = 0.0;
	float Allruncumoutflow = 0.0;

	float Allssrcuminflow_mWQ = 0.0;
	float Allssrcumoutflow_mWQ = 0.0;
	float Allruncuminflow_mWQ = 0.0;
	float Allruncumoutflow_mWQ = 0.0;

	float AllSdcuminflow = 0.0;
	float Allrechrcuminflow = 0.0;

	float AllSdcuminflow_mWQ = 0.0;
	float Allrechrcuminflow_mWQ = 0.0;
	float AllTotal = 0.0;
	float Total;

	for (hh = 0; chkStruct(); ++hh) {
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cuminflow                   (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cumoutflow                  (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cumoutflow_diverted         (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' hruDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), hruDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cuminflow_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cumoutflow_mWQ              (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cumoutflow_diverted_mWQ     (mm) (mm*km^2) (mm*basin): ").c_str(), cumoutflow_diverted_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' ssrcuminflow                (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' ssrcumoutflow               (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' ssrDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), ssrDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' ssrcuminflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' ssrcumoutflow_mWQ           (mm) (mm*km^2) (mm*basin): ").c_str(), ssrcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' runoffcuminflow             (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' runoffcumoutflow            (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' runDelay_in_storage         (mm) (mm*km^2) (mm*basin): ").c_str(), runDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' runoffcuminflow_mWQ         (mm) (mm*km^2) (mm*basin): ").c_str(), runcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' runoffcumoutflow_mWQ        (mm) (mm*km^2) (mm*basin): ").c_str(), runcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcuminflow                 (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcumoutflow                (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcum_diverted              (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwDelay_in_storage          (mm) (mm*km^2) (mm*basin): ").c_str(), gwDelay->Left(hh) / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcuminflow_mWQ             (mm) (mm*km^2) (mm*basin): ").c_str(), gwcuminflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcumoutflow_mWQ            (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' gwcumoutflow_diverted_mWQ   (mm) (mm*km^2) (mm*basin): ").c_str(), gwcumoutflow_diverted_mWQ[hh], hru_area[hh], basin_area[0]);

		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_to_Sd                   (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_to_Sd_mWQ               (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_Sd_mWQ[hh], hru_area[hh], basin_area[0], " *** Added to this HRU Sd");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_to_soil_rechr           (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_to_soil_rechr_mWQ       (mm) (mm*km^2) (mm*basin): ").c_str(), cum_to_soil_rechr_mWQ[hh], hru_area[hh], basin_area[0], " *** Added to this HRU recharge");
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_redirected_residual     (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' cum_redirected_residual_mWQ (mm) (mm*km^2) (mm*basin): ").c_str(), cum_redirected_residual_mWQ[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' HRU_cumbasinflow            (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow[hh] / hru_area[hh], hru_area[hh], basin_area[0]);
		LogMessageA(hh, string("'" + Name + " (Netroute_M_D_WQ)' HRU_cumbasinflow_conc        (mm) (mm*km^2) (mm*basin): ").c_str(), HRU_cumbasinflow_conc[hh], hru_area[hh], basin_area[0]);
		LogDebug(" ");

		Total = cumoutflow[hh] + gwcumoutflow[hh] - HRU_cumbasinflow[hh] - cum_to_Sd_mWQ[hh] - cum_to_soil_rechr[hh] - gwcumoutflow[hh]
			+ cumoutflow_diverted[hh] + gwcumoutflow_diverted[hh] - cum_redirected_residual[hh];
		AllTotal += Total;
		LogMessageA(hh, string("'" + Name + " (Soil_WQ)' Total                           (mm) (mm*hru) (mm*hru/basin): ").c_str(), Total, hru_area[hh], basin_area[0], " *** HRU mass balance");
		LogDebug(" ");

		Allcuminflow += cuminflow[hh];
		Allcumoutflow += cumoutflow[hh];
		Allcumoutflowdiverted += cumoutflow_diverted[hh];

		Allgwcuminflow += gwcuminflow[hh];
		Allgwcumoutflow += gwcumoutflow[hh];
		Allgwcumoutflowdiverted += gwcumoutflow_diverted[hh];

		Allssrcumoutflow += ssrcumoutflow[hh];
		Allssrcuminflow += ssrcuminflow[hh];
		Allruncuminflow += runcuminflow[hh];
		Allruncumoutflow += runcumoutflow[hh];

		AllSdcuminflow += cum_to_Sd[hh];
		Allrechrcuminflow += cum_to_soil_rechr[hh];

		Allcuminflow_mWQ += cuminflow_mWQ[hh];
		Allcumoutflow_mWQ += cumoutflow_mWQ[hh];
		Allcumoutflowdiverted_mWQ += cumoutflow_diverted_mWQ[hh];

		Allgwcuminflow_mWQ += gwcuminflow_mWQ[hh];
		Allgwcumoutflow_mWQ += gwcumoutflow_mWQ[hh];
		Allgwcumoutflowdiverted_mWQ += gwcumoutflow_diverted_mWQ[hh];

		Allssrcumoutflow_mWQ += ssrcumoutflow_mWQ[hh];
		Allssrcuminflow_mWQ += ssrcuminflow_mWQ[hh];
		Allruncuminflow_mWQ += runcuminflow_mWQ[hh];
		Allruncumoutflow_mWQ += runcumoutflow_mWQ[hh];

		AllSdcuminflow_mWQ += cum_to_Sd_mWQ[hh];
		Allrechrcuminflow_mWQ += cum_to_soil_rechr_mWQ[hh];
	}

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' cumbasinflow (m^3):                     ").c_str(), cumbasinflow[0]);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' cumbasinflow_mWQ ():                    ").c_str(), cumbasinflow_mWQ[0]);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' cumbasingw   (m^3):                     ").c_str(), cumbasingw[0]);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' cumbasingw_mWQ ():                      ").c_str(), cumbasingw_mWQ[0]);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcuminflow (mm*basin):              ").c_str(), Allgwcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcuminflow_mWQ (mm*basin):          ").c_str(), Allgwcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcumoutflow (mm*basin):             ").c_str(), Allgwcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcumoutflow_mWQ (mm*basin):         ").c_str(), Allgwcumoutflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcumoutflowdiverted (mm*basin):     ").c_str(), Allgwcumoutflowdiverted);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allgwcumoutflowdiverted_mWQ (mm*basin): ").c_str(), Allgwcumoutflowdiverted_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcuminflow (mm*basin):                ").c_str(), Allcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcuminflow_mWQ (mm*basin):            ").c_str(), Allcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcumoutflow (mm*basin):               ").c_str(), Allcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcumoutflow_mWQ (mm*basin):           ").c_str(), Allcumoutflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcumoutflowdiverted (mm*basin):       ").c_str(), Allcumoutflowdiverted);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allcumoutflowdiverted_mWQ (mm*basin):   ").c_str(), Allcumoutflowdiverted_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allssrcuminflow (mm*basin):             ").c_str(), Allssrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allssrcuminflow_mWQ (mm*basin):         ").c_str(), Allssrcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allssrcumoutflow (mm*basin):            ").c_str(), Allssrcumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allssrcumoutflow_mWQ (mm*basin):        ").c_str(), Allssrcumoutflow_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allruncuminflow (mm*basin):             ").c_str(), Allruncuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allruncuminflow_mWQ (mm*basin):         ").c_str(), Allruncuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allruncumoutflow (mm*basin):            ").c_str(), Allruncumoutflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allruncumoutflow_mWQ (mm*basin):        ").c_str(), Allruncumoutflow_mWQ);
	LogDebug(" ");

	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' AllSdcuminflow (mm*basin):              ").c_str(), AllSdcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' AllSdcuminflow_mWQ (mm*basin):          ").c_str(), AllSdcuminflow_mWQ);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allrechrcuminflow (mm*basin):           ").c_str(), Allrechrcuminflow);
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' Allrechrcuminflow_mWQ (mm*basin):       ").c_str(), Allrechrcuminflow_mWQ);
	LogDebug(" ");
	LogMessage(string("'" + Name + " (Netroute_M_D_WQ)' AllTotal              (mm*basin):       ").c_str(), AllTotal);
	LogDebug(" ");

	delete hruDelay;
	delete ssrDelay;
	delete runDelay;
	delete gwDelay;
}

void ClassWQ_Netroute_M_D::Add_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ) {

	var_cWQ[hru] = (var_cWQ[hru] * var[hru] + amount * amount_cWQ);
	var[hru] += amount;

	if (var[hru] > 0.0 && var_cWQ[hru] > 0.0)
		var_cWQ[hru] /= var[hru];
	else {
		//    var[hru] = 0.0;
		var_cWQ[hru] = 0.0;
	}
}

void ClassWQ_Netroute_M_D::Set_WQ(long hru, float *var, float *var_cWQ, float amount, float amount_cWQ) {

	var[hru] = amount;
	if (amount > 0.0)
		var_cWQ[hru] = amount_cWQ;
	else
		var_cWQ[hru] = 0.0;
}

void ClassWQ_Netroute_M_D::Sub_WQ(long hru, float *var, float *var_cWQ, float *var2, float *var2_cWQ, float *var3, float *var3_cWQ) {

	var_cWQ[hru] = var2[hru] * var2_cWQ[hru] - var3[hru] * var2_cWQ[hru];

	var[hru] = (var2[hru] - var3[hru]);

	if (var[hru] > 0.0 && var_cWQ[hru] > 0.0)
		var_cWQ[hru] /= var[hru];
	else {
		//    var[hru] = 0.0;
		var_cWQ[hru] = 0.0;
	}
}

void ClassWQ_Netroute_M_D::Reset_WQ(long hru, float *var, float *var_cWQ) {
	var[hru] = 0.0;
	var_cWQ[hru] = 0.0;
}

Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA* Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::klone(string name) const {
	return new Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA(name);
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::decl()
{
	cb->decl();
	//cg->decl();
	co->decl();
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::init()
{
	cb->init();
	//cg->init();
	co->init();
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::pre_run()
{
	cb->pre_run();
	//cg->pre_run();
	co->pre_run();	
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::Harder()
{	
	co->Harder();
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::finish(bool good)
{
	cb->finish(good);
	//cg->finish(good);
	co->finish(good);
}

void Class_SmithCreekBasin_GroupTemplate_Modified_20Oct_GrpA::run()
{
	cb->run();
	//cg->run();
	co->run();
	/*
	for (int i = 0; i < Global::AllModulesList->Count; i++)
	{		
		ClassModule *p = (ClassModule*)Global::AllModulesList->Objects[i];
		if (p->NameRoot == "basin" 
			|| p->NameRoot == "global"
			|| p->NameRoot == "Grow_Crop"
			|| p->NameRoot == "walmsley_wind"
			|| p->NameRoot == "netall"
			|| p->NameRoot == "albedo"
			|| p->NameRoot == "ebsm"
			|| p->NameRoot == "Soil"
			|| p->NameRoot == "Volumetric"
			) 
		{ 
			p->run(); 
		}
	}
	*/

	/*Problematic modules
	
	obs
	pbsm
	Netroute_M_D
	
	*/



	/*
	ClassModule *p = (ClassModule*)Global::OurModulesList->Objects[Global::CurrentModuleRun];


	cb->run();
	cg->run();
	co->run();
	cgc->run();
	ca->run();
	cw->run();
	cl->run();
	cc->run();
	cn->run();
	cp->run();
	cal->run();
	ce->run();
	cev->run();
	cpr->run();
	cs->run();
	cv->run();
	cnet->run();
	*/

}


////////////////////////////////////////////////////////////////////////////////////
void ClassGrow_Crop::decl(void)
{
	/*
	'declparam, Ht, NHRU,"[0.1, 0.25, 1.0]", 0.001, 100.0, "vegetation height", (m)'
	'declparam, Init_Crop_Ht, NHRU,"[0.001]", 0.001, 100.0, "initial crop height", (m)'
	'declparam, Crop_Grow_Rate, NHRU,"[0.0]", 0.0, 1.0, "crop growth rate", (m/d)'
	'declparam, JCrop_Start, NHRU,"[121]", 1, 366, "start Julian day", ()'
	'declparam, JCrop_Mature, NHRU,"[182]", 1, 366, "maturity Julian day", ()'
	'declparam, JCrop_Harvest, NHRU,"[228]", 1, 366, "harvest Julian day", ()'
	'declvar, Crop_Ht, NHRU, "crop height", (m)'
	*/


	declparam("Init_Crop_Ht", NHRU, "[0.001]", "0.001", "100.0", "initial crop height", "(m)", &Init_Crop_Ht);
	declparam("Crop_Grow_Rate", NHRU, "[0.0]", "0.0", "1.0", "crop growth rate", "(m/d)", &Crop_Grow_Rate);
	declparam("JCrop_Start", NHRU, "[121]", "1", "366", "start Julian day", "()", &JCrop_Start);
	declparam("JCrop_Mature", NHRU, "[182]", "1", "366", "maturity Julian day", "()", &JCrop_Mature);
	declparam("JCrop_Harvest", NHRU, "[228]", "1", "366", "harvest Julian day", "()", &JCrop_Harvest);
	//declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);

	declvar("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", &Ht);
	declvar("Crop_Ht", NHRU, "crop height", "m", &Crop_Ht);
	declvar("above", NHRU, "testing", "testing", &above);
	declvar("below", NHRU, "testing", "testing", &below);

	//Global::nhru = 52;
	//Global::nlay = 2;
	//Global::nobs = 1;
}
void ClassGrow_Crop::run(void)
{
	for (hh = 0; hh < nhru; ++hh) {

		if (getstep() == 1)
		{
			Ht[hh] = Init_Crop_Ht[hh];
			Crop_Ht[hh] = Ht[hh];
		}

		if (getstep() % Global::Freq == 0)
		{
			float f = Julian("now");
			if (f >= JCrop_Start[hh] && f < JCrop_Mature[hh] && Crop_Grow_Rate[hh] > 0.0)
			{
				Ht[hh] = Ht[hh] + Crop_Grow_Rate[hh];
			}
			else
			{
				if (f == JCrop_Harvest[hh]) { Ht[hh] = Init_Crop_Ht[hh]; }
			}
		}

		Crop_Ht[hh] = Ht[hh];
	}
}

ClassGrow_Crop* ClassGrow_Crop::klone(string name) const {
	return new ClassGrow_Crop(name);
}
////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////
Classdisplay* Classdisplay::klone(string name) const {
	return new Classdisplay(name);
}
void Classdisplay::decl()
{
	declvar("Above", NHRU, "Temperature above zero", "(�C)", &Above);
	declvar("Below", NHRU, "Temperature below zero", "(�C)", &Below);
	declreadobs("t", NOBS, "Temperature", "(�C)", &t, HRU_OBS_t_rh_ea);
}

void Classdisplay::run()
{
	for (hh = 0; hh < nhru; ++hh) 
	{
		if (t[hh] >= 0.0)
		{
			Above[hh] = t[hh];
			Below[hh] = 0.0;
		}
		else
		{
			Above[hh] = 0.0;
			Below[hh] = t[hh];
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
void ClassSWE_peak:: decl()
{
	declgetvar("*", "SWE", "(mm)", &SWE);
	declvar("Peak_SWE", NHRU, "peak SWE", "(mm)", &Peak_SWE);
	declvar("Day_Peak_SWE", NHRU, "day peak SWE occurred", "()", &Day_Peak_SWE);
	declvar("Prob", NHRU, "Probability", "()", &Prob);
}

void ClassSWE_peak::run()
{
	{
		for (hh = 0; hh < nhru; ++hh)
		{
			if (getstep() == 1)
			{
				Peak_SWE[hh] = 0;
				Day_Peak_SWE[hh] = 0;
			}
			if (SWE[hh] > Peak_SWE[hh])
			{
				Peak_SWE[hh] = SWE[hh];
				Day_Peak_SWE[hh] = Julian("now");
			}
		}
	}
}

ClassSWE_peak* ClassSWE_peak::klone(string name) const {
	return new ClassSWE_peak(name);
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
void ClassAlbedo_Change::decl()
{
	declvar("Albedo", NHRU, "vegetation Albedo", "()", &Albedo);
	declvar("Albedo_Start", NHRU, "vegetation Albedo", "()", &Albedo_Start);

	declparam("Albedo_change", NHRU, "0.001", "0.0", "1.0", "albedo step", "(m)", &Albedo_change);
	declparam("Albedo_min", NHRU, "0.1", "0.01", "1.0", "minimum albedo", "(m)", &Albedo_min);
	declparam("Albedo_max", NHRU, "0.1", "0.01", "1.0", "maximum albedo", "(m)", &Albedo_max);
	declparam("Albedo_Julian", NHRU, "195", "1", "366", "Julian day", "()", &Albedo_Julian);
}

void ClassAlbedo_Change::run()
{
	{
		for (hh = 0; hh < nhru; ++hh)
		{
			if (getstep() == 1)
			{
				Albedo[hh] = Albedo_min[hh];
			}

			float f = Julian("now");

			if (f >= Albedo_Julian[hh])
			{
				Albedo_Start[hh] = f;

				if (getstep() % Global::Freq == 0)
				{
					Albedo[hh] = Albedo[hh] + Albedo_change[hh];
				}

				if (Albedo[hh] > Albedo_max[hh])
				{
					Albedo[hh] = Albedo_max[hh];
				}
			}

		}
	}
}

ClassAlbedo_Change* ClassAlbedo_Change::klone(string name) const {
	return new ClassAlbedo_Change(name);
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
void ClassCalc_tmean::decl()
{
	declvar("Status", NHRU, "indicates if Obs available", "()", &Status);
	declvar("t_mean", NHRU, "calculated t mean", "(�C)", &t_mean);

	declreadobs("t", NOBS, "temperature observation", "(�C)", &t, HRU_OBS_t_rh_ea);
}

void ClassCalc_tmean::run()
{
	float sum = 0.0;
	int i, ReadAheadObs;

	for (hh = 0; hh < nhru; ++hh)
	{
		if (getstep() == 1)
		{
			t_mean[hh] = 0;
		}
		if (getstep() % Global::Freq == 0)
		{
			sum = 0;
			Status[hh] = 0;
			for (i = 0; i < Global::Freq; i = i + 1)
			{
				ReadAheadObs = i;
				Status[hh] = Status[hh] + ReadAheadObs;
				sum = sum + t[hh];
			}
			t_mean[hh] = sum / Global::Freq;
		}
	}
}

ClassCalc_tmean* ClassCalc_tmean::klone(string name) const {
	return new ClassCalc_tmean(name);
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassConvert_Qnsn_QnD* ClassConvert_Qnsn_QnD::klone(string name) const {
	return new ClassConvert_Qnsn_QnD(name);
}

void ClassConvert_Qnsn_QnD::decl()
{
	declreadobs("Qnsn", NOBS, "net radiation", "(W/m^2)", &Qnsn, HRU_OBS_Q);
	declreadobs("QnD#", NHRU, "net radiation", "(MJ/m^2*d)", &QnD, HRU_OBS_Q, true);
}

void ClassConvert_Qnsn_QnD::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		if (getstep() % Global::Freq == 1)
		{
			QnDhash[hh] = Qnsn[hh] * 0.0864 / Global::Freq;
		}
		else 
		{ 
			QnDhash[hh] = QnD[hh] + Qnsn[hh] * 0.0864 / Global::Freq;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
Classea_RH * Classea_RH::klone(string name) const {
	return new Classea_RH(name);
}

void Classea_RH::decl()
{
	declvar("RH", NHRU, "calculated rh", "(kPa)", &RH);
	declgetvar("*", "hru_t", "(�C)", &hru_t);
	declgetvar("*", "hru_ea", "(kPa)", &hru_ea);
}

void Classea_RH::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		RH[hh] = hru_ea[hh] / Common::estar(hru_t[hh]) * 100;
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassHt_Change * ClassHt_Change::klone(string name) const {
	return new ClassHt_Change(name);
}

void ClassHt_Change::decl()
{
	declvar("Ht_Var", NHRU, "vegetation height", "(m)", &Ht_Var);
	declparam("Ht", NHRU, "[0.1, 0.25, 1.0]", "0.001", "100.0", "vegetation height", "(m)", &Ht);
}

void ClassHt_Change::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		//Ht[hh] = Heights[hh];
		//Ht_Var[hh] = Heights[hh];

		Ht_Var[hh] = Ht[hh];
	}
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
ClassJulian_Test * ClassJulian_Test::klone(string name) const {
	return new ClassJulian_Test(name);
}

void ClassJulian_Test::decl()
{
	declvar("Julian_Var", NHRU, "Julian variable", "()", &Julian_Var);
}
void ClassJulian_Test::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		Julian_Var[hh] = Julian("now");
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassNo_Display_Macro * ClassNo_Display_Macro::klone(string name) const {
	return new ClassNo_Display_Macro(name);
}

void ClassNo_Display_Macro::decl()
{
	declvar("No_Display", NHRU, "no errors", "()", &No_Display);
	declreadobs("Qdflat_err", NOBS, "measured short-wave", "(W/m^2)", &Qdflat_err, HRU_OBS_Q);
}
void ClassNo_Display_Macro::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		if (Qdflat_err[hh] > -9999 && Qdflat_err[hh] < 9999)
		{
			No_Display[hh] = Qdflat_err[hh];
		}
		else
		{
			No_Display[hh] = 0;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
ClassSicartLong * ClassSicartLong::klone(string name) const {
	return new ClassSicartLong(name);
}

void ClassSicartLong::decl()
{
	declreadobs("t", NOBS, "temp", "(�C)", &t, HRU_OBS_t_rh_ea);
	declreadobs("rh", NOBS, "relative humidity", "()", &rh, HRU_OBS_t_rh_ea);
	declreadobs("ea", NOBS, "vapour pressure", "()", &ea, HRU_OBS_t_rh_ea);

	declvar("Qlong", NHRU, "Sicart long", "(W/m^2)", &Qlong);
}
void ClassSicartLong::run()
{
	float tau = 0.75;
	for (hh = 0; hh < nhru; ++hh)
	{
		double d1 = pow(((ea[0] * 10) / (t[0] + 273.15)), (1 / 7));
		double d2 = pow((t[0] + 273.15),4);
		Qlong[hh] = 1.24*d1*(1 + 0.44*rh[0] / 100 - 0.18*tau)*5.67E-8*d2;
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassSlope_Qsi2 * ClassSlope_Qsi2::klone(string name) const {
	return new ClassSlope_Qsi2(name);
}

void ClassSlope_Qsi2::decl()
{
	declobs("Qsi", NHRU, "Created short-wave", "(W/m2)", &Qsi);	
	declreadobs("Qsi", NOBS, "measured short-wave", "(W/m2)", &Qsihash, HRU_OBS_Q);

	declvar("Short", NHRU, "short-wave", "(W/m^2)", &Short);
	declvar("ShortC", NHRU, "corrected short-wave for slope", "(W/m^2)", &ShortC);

	declgetvar("*", "Qdro", "(W/m2)", &Qdro);
	declgetvar("*", "Qdfo", "(W/m2)", &Qdfo);
	declgetvar("*", "Qdflat", "(W/m2)", &Qdflat);
	
}
void ClassSlope_Qsi2::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		Short[hh] = Qdro[hh] + Qdfo[hh];
		if (Qdflat[hh] > 0.01)
		{
			ShortC[hh] = Qsihash[hh] / Qdflat[hh] * Short[hh];
			Qsi[hh] = ShortC[hh];
		}
		else
		{
			ShortC[hh] = 0;
			Qsi[hh] = 0;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassCalc_t * ClassCalc_t::klone(string name) const {
	return new ClassCalc_t(name);
}

void ClassCalc_t::decl()
{
	declvar("t_calc", NHRU, "calculated t", "(�C)", &t_calc);
	declvar("Last_tmax", NHRU, "last tmax", "(�C)", &Last_tmax);
	declvar("Mod_n", NHRU, "step", "()", &Mod_n);

	declgetvar("*", "hru_tmax", "(�C)", &hru_tmax);
	declgetvar("*", "hru_tmin", "(�C)", &hru_tmin);	
}
void ClassCalc_t::run()
{
	float D=0, Diff=0;
	for (hh = 0; hh < nhru; ++hh)
	{
		
		if (getstep() % Global::Freq == 0)
		{
			Last_tmax[hh] = hru_tmax[hh];
		}
		D = getstep() % Global::Freq / Global::Freq;
		Diff = hru_tmax[hh] - hru_tmin[hh];
		Mod_n[hh] = D;
		if (D > 0.625)
		{
			t_calc[hh] = hru_tmax[hh] - Diff * (D - 0.625) / 0.375;
		}
		else
		{
			if (D > 0.25)
			{
				t_calc[hh] = hru_tmin[hh] + Diff * (D - 0.25) / 0.375;
			}
			else
			{
				Diff = Last_tmax[hh] - hru_tmin[hh];
				t_calc[hh] = hru_tmin[hh] + Diff * (0.25 - D) / 0.625;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
ClassHt_Change_Julian * ClassHt_Change_Julian::klone(string name) const {
	return new ClassHt_Change_Julian(name);
}

void ClassHt_Change_Julian::decl()
{
	//declparam("Ht", NHRU, "0.1", "0.01", "100.0", "description", "(m)", &Ht);
	declparam("Ht_change", NHRU, "0.1", "0.01", "1.0", "description", "(m)", &Ht_change);
	declparam("Ht_min", NHRU, "0.1", "0.01", "3.0", "description", "(m)", &Ht_min);
	declparam("Ht_max", NHRU, "0.1", "0.01", "3.0", "description", "(m)", &Ht_max);

	declvar("Ht", NHRU, "description", "(m)", &Ht);
	declvar("Ht_Var", NHRU, "Vegetation height", "(m)", &Ht_Var);
	declvar("Date_Var", NHRU, "finds date", "(m)", &Date_Var);
	declvar("Date_Julian", NHRU, "Julian date", "()", &Date_Julian);
}
void ClassHt_Change_Julian::run()
{	
	for (hh = 0; hh < nhru; ++hh)
	{
		if (getstep() == 1)
		{
			Ht[hh] = Ht_min[hh];
		}
		else
		{
			if (getstep() % Global::Freq == 0)
			{
				Ht[hh] = Ht[hh] + Ht_change[hh];
			}
			if (Ht[hh] > Ht_max[hh])
			{
				Ht[hh] = Ht_max[hh];
			}
		}

		if (Ht[hh] > 0.17)
		{
			Ht_Var[hh] = Ht[hh];
		}
		else
		{
			Ht_Var[hh] = 0.0;
		}

		
		
		int year, month, day, h, m;
		Common::DecodeDateTime(Global::DTnow, &year, &month, &day, &h, &m);

		if (month == 5 && day == 27 && getstep() % Global::Freq == 1)
		{
			Date_Var[hh] = 1;
		}

		Date_Julian[hh] = Julian("now");
	}
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
ClassTest_NDEFN * ClassTest_NDEFN::klone(string name) const {
	return new ClassTest_NDEFN(name);
}

void ClassTest_NDEFN::decl()
{
	//declparam("Ht", NHRU, "0.1", "0.01", "100.0", "description", "(m)", &Ht);
	declparam("Distrib", NDEFN, "[1.0]", "0.0", "100.0", "Test 2D parametert", "()", &Distrib);
	declvar("Test_NDEFN", NDEFN, "Test 2D variable", "()", &Test_NDEFN);
	declvar("Test_NDEFN_P", NDEFN, "Test 2D variable", "()", &Test_NDEFN_P);
	declgetvar("*", "Results", "()", &Results);
}
void ClassTest_NDEFN::run()
{
	for (hh = 0; hh < nhru; ++hh)
	{
		//Test_NDEFN[hh][1] = Results[hh][1];
		//Test_NDEFN_P[hh][1] = Distrib[hh][1];
	}
}
////////////////////////////////////////////////////////////////////////////////////
