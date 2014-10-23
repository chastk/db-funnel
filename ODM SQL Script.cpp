#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char* argv[]){
	//
	//						==USAGE==
	//
	//  ** column headers must be from among the following: **
	//      value, year, month, day, hour, min, sec, ms, 
	//      UTCOffset, SiteID, VariableID, SourceID
	//   they can be in any order, but spelled exactly!
	//
	//  set the parameters in the box below if they are not already in your data file
	//
	//==============================//==
	std::string UTCOffset = "-5";	//==
	std::string SiteID = "-1";		//==
	std::string VariableID = "-1";	//==
	std::string SourceID = "-1";	//==
	//==============================//==
	
	std::string options[] = {"value", "year", "month", "day", "hour", "min", "sec", "ms", "UTCOffset", "SiteID", "VariableID", "SourceID"};
	std::string defaultVal[] = {"ERROR", "ERROR", "ERROR", "ERROR", "0", "0", "0", "0", "0", UTCOffset, SiteID, VariableID, SourceID};
	std::map< std::string, std::string > data;
	
	// open file
	if(argc < 2){
		printf("USAGE: ./a.out <input.xyz>\n");
		return EXIT_FAILURE;
	}
	std::ifstream input(argv[1], std::ios::binary);
	if( !input ){
		printf("Invalid input file =C\n");
		return EXIT_FAILURE;
	}
			
	//read header line (store the order of the columns)
	std::string line;
	std::getline(input, line, '\n');
	std::cout << "Line: " << line << std::endl;
	std::string token;
	std::vector< std::string > columns;
	std::istringstream iss(line);
	while (std::getline(iss, token, ',')){
		columns.push_back(token);
	}
	
	//read data
	while(std::getline(input, line)){
		int i=0;
		std::istringstream iss2(line);
		data.clear();
		while (std::getline(iss2, token, ',')){
			data[columns[i]] = token;
			i++;
		}
		for(int j=0; j<12; j++){
			if(data.find(options[j]) != data.end()){
				data[options[j] = defaultVal[j]];
			}
		}
		//check month and day formats
		
		
		std::cout << "INSERT INTO DataValues(DataValue, LocalDateTime, UTCOffset, SiteID, VariableID, SourceID) ";
		std::cout << "VALUES (" << data["value"] << ", " << data["year"] << "-" << std::setfill('0') << std::setw(2) << data["month"];
		std::cout << "-" << std::setfill('0') << std::setw(2) << data["day"] << " " << std::setfill('0') << std::setw(2) <<  data["hour"];
		std::cout << ":" << std::setfill('0') << std::setw(2) <<  data["min"] << ":" << std::setfill('0') << std::setw(2) <<  data["sec"];
		std::cout << "." << std::setfill('0') << std::setw(2) <<  data["ms"] << ", " << data["UTCOffset"] << ", " << data["SiteID"];
		std::cout << ", " << data["VariableID"] << ", " << data["SourceID"] << ")" << std::endl;
	}
	return EXIT_SUCCESS;
}