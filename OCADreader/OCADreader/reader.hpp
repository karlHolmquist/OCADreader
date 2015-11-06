#ifndef READER
#define READER

#include <stdio.h>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

using namespace std;

class OCADreader {
public:
	OCADreader();
	OCADreader(string _fileName);

	void setFileName(string _fileName);

	int readFromFile();

	void parseSymbols();

	void parseObjects();

	void parseStrings();

	void parseFileName();

	void printHeader();

private:
	string fileName;
	unsigned char fileType;
	unsigned int OCADversion, fileVersion;
	unsigned char OCADsubV, OCADssubV;
	unsigned int firstSymbolIndex, objectIndex, firstStringIndex;
	unsigned int FileNamePos, FileNameSize;

	enum class RESULT{
		SUCCESS,
		FAILURE
	};

};


#endif