
#ifndef _FILE_READER_H
#define _FILE_READER_H

#include "includes.h"

class File_Reader {
private:
	FILE * file;
public:
	File_Reader() {

	}
	File_Reader(string file_name) {
		file = fopen(file_name.c_str(), "r");
		if (file == NULL)
			printf("File Reader Error: \'%s\' not found!\n", file_name.c_str());
	}

	int getString(char * mac_add, char* port){
		char buf[150];
		char filter[50];
		if (fgets(buf, 150, file) == NULL) // read over
			return 0;
		if (strchr(buf, ',')) // more than one port
			return 2;
		int tmp = sscanf(buf, "%s %s %s %s %s %s %s", filter, filter, mac_add, filter,filter,filter,port);
		if (tmp == 7) // normal data
			return 1;
		return 2; // unnormal data
	}

	bool getdata(char* mac_add, int& index)
	{
		char buf[100];
		if (fgets(buf, 100, file) == NULL)
			return 0;
		sscanf(buf, "%s %d", mac_add, &index);
		return 1;
	}

	~File_Reader() {
		fclose(file);
	}
};

class File_Writer {
private:
	FILE * file;
public:
	File_Writer() {

	}
	File_Writer(string file_name) {
		file = fopen(file_name.c_str(), "w");
		if (file == NULL)
			printf("File Reader Error: \'%s\' not found!\n", file_name.c_str());
	}
	void write(const char* str, int index, int q_res) {
		fprintf(file, "%s\t%d\t%d\n",str, index, q_res);
	}
	
	~File_Writer() {
		fclose(file);
	}
};

#endif
