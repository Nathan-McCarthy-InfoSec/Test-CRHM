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
#ifndef CRHM_ARGUMENTS
#define CRHM_ARGUMENTS

#include <string.h>
#include <stdio.h>

#include "CRHMmain.h"
#include "Common.h"

enum class OUTPUT_FORMAT {STD, OBS};

const std::string USE_MESSAGE = "\ncrhm [options] PROJECT_FILE\n"
	"\n"
	"\t-h - Display this message.\n"
	"\n"
	"\t-t TIME_FORMAT - Select the format for date time outputs.\n"
	"\t\tValid formats are:\n"
	"\t\tMS - Microsoft Excel floating point.\n"
	"\t\tISO - ISO 8601 extended format YYYY-MM-DDThh:mm\n"
	"\t\tYYYYMMDD - YYYY MM DD hh mm\n"
	"\n"
	"\t-f OUTPUT_FORMAT - Select the file format for the output.\n"
	"\t\tValid formats are:\n"
	"\t\tSTD - Standard output format. Sutable for a spreadsheet.\n"
	"\t\tOBS - Observation file .obs format. Sutable for reading with CRHM GUI.\n"
	"\n"
	"\t-o PATH - Specify a location to place the output file generated.\n"
	"\n"
	"\t-d DELIMITER - Specify a single character delimiter to use when generating file output. \n\t\tTab character is the default.\n"
	"\n"
	"\t--obs_file_directory DIRECTORY_PATH - Specify a directory where the obs files"
	"\n\t\t for this project are found. This directory will be prepended to the obsfile"
	"\n\t\t names specified in the project file."
	"\n\n"
	"\t-p UPDATE_FREQUENCY - Show percentage of progress towards completion during simulation run."
	"\n\t\t UPDATE_FREQUENCY specifies after how many days to update the percentage."
	"\n"
	;

class CRHMArguments
{
private:
	std::string project_name;
	std::string output_name;
	std::string obs_file_directory;
	TIMEFORMAT time_format{TIMEFORMAT::ISO};
	bool time_format_set{false};
	OUTPUT_FORMAT output_format{OUTPUT_FORMAT::STD};
	char delimiter{'\t'};
	bool show_progress;
	int update_progress;

	void read_option(char** argv, int* pos);
	void read_argument(char* argument);
	std::string unrecongnized_option(char* option);
public:
	//Standard Constructor
	CRHMArguments();

	void readCommandLine(int argc, char * argv[]);
	void validate();


	std::string get_project_name();
	std::string get_output_name();
	std::string get_obs_file_directory();
	TIMEFORMAT get_time_format();
	OUTPUT_FORMAT get_output_format();
	char get_delimiter();
	bool get_show_progress();
	int get_update_progress();
};

#endif // !CRHM_ARGUMENTS
