#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_MAX 1024

int main(int argc, char* argv[]){
	// open file
	if(argc < 3){
		printf("USAGE: ./a.out <input.xyz> <milliseconds-index>\n");
		return EXIT_FAILURE;
	}
	char * filename = argv[1];
	FILE * input = fopen(filename, "r");
	if( input == NULL ){
		printf("Invalid input file =C\n");
		return EXIT_FAILURE;
	}

	// read file
	char buffer[BUFFER_MAX];
	double x, y, z;
	fgets(buffer, BUFFER_MAX, input);
	int len = strlen(buffer);
	if( buffer[len-1] == '\n' ) buffer[len-1] = '\0';
	char line[BUFFER_MAX];
	int min = 0;
	int sec = atoi(argv[2]); // aa = 0;
	int ms = 0;
	while (buffer != NULL && ms < 1000000){
		strcpy(line, buffer);
		x = atof(strtok(line, " "));
		y = atof(strtok(NULL, " "));
		z = atof(strtok(NULL, " "));
	
		printf("INSERT INTO DataValues(DataValue, LocalDateTime, UTCOffset, SiteID, VariableID, SourceID) VALUES (%.2f, 2014-02-01 00:%02d:%02d.%06d, -5, 2014-02-01 05:%01d:%01d.%06d, 1, 1, 1);\n", x,min,sec,ms, min,sec,ms);
		printf("INSERT INTO DataValues(DataValue, LocalDateTime, UTCOffset, SiteID, VariableID, SourceID) VALUES (%.2f, 2014-02-01 00:%02d:%02d.%06d, -5, 2014-02-01 05:%01d:%01d.%06d, 1, 2, 1);\n", y,min,sec,ms, min,sec,ms);
		printf("INSERT INTO DataValues(DataValue, LocalDateTime, UTCOffset, SiteID, VariableID, SourceID) VALUES (%.2f, 2014-02-01 00:%02d:%02d.%06d, -5, 2014-02-01 05:%01d:%01d.%06d, 1, 3, 1);\n", z,min,sec,ms, min,sec,ms);
		fgets(buffer, BUFFER_MAX, input);
		int len = strlen(buffer);
		if( buffer[len-1] == '\n' ) buffer[len-1] = '\0';
		ms++;
	}// /while reading lines
	return EXIT_SUCCESS;
}
