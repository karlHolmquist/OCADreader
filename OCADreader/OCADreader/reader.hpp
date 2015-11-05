#include <stdio.h>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

using namespace std;

class OCADreader {
public:
	OCADreader();
	OCADreader(string _fileName){
		fileName = _fileName;
	}

	void setFileName(string _fileName){
		fileName = _fileName;
	}

	int readFromFile(){
		char temp[48];
		unsigned char tempU[48];
		// Open file as read-only
		shared_ptr<fstream> file(new fstream(fileName.c_str(), fstream::in, fstream::binary));
		if (file == nullptr){
			cout << "Error: couldn't open file" << endl;
			return (int)RESULT::FAILURE;
		}
		file->seekg(0, fstream::beg);
		// Start parsing the file after the OCAD12 standard (could add a check for version later on)
		// Check if the file really is a OCAD file
		file->read(temp, 48);

		for (int i = 0; i < 48; i++){
			tempU[i] = temp[i];
		}

		if (tempU[0] != 173 || tempU[1] != 12){
			// File doesn't comply with OCAD standard, abort
			file->close();
			return (int) RESULT::FAILURE;
		}
		fileType = tempU[2];
		OCADversion = tempU[4] + 256*tempU[5];
		OCADsubV = tempU[6];
		OCADssubV = tempU[7];

		firstSymbolIndex = tempU[8] + 256 * tempU[9] + 256 * 256 * tempU[10] + 256 * 256 * 256 * tempU[11];
		objectIndex = tempU[12] + 256 * tempU[13] + 256 * 256 * tempU[14] + 256 * 256 * 256 * tempU[15];
		fileVersion = tempU[20] + 256 * tempU[21] + 256 * 256 * tempU[22] + 256 * 256 * 256 * tempU[23];
		firstStringIndex = tempU[32] + 256 * tempU[33] + 256 * 256 * tempU[34] + 256 * 256 * 256 * tempU[35];

		// Following are only used for tempUorary files
		FileNamePos = tempU[36] + 256 * tempU[37] + 256 * 256 * tempU[38] + 256 * 256 * 256 * tempU[39];
		FileNameSize = tempU[40] + 256 * tempU[41] + 256 * 256 * tempU[42] + 256 * 256 * 256 * tempU[43];

		// Move to the start position of the first symbol
		file->seekg(firstSymbolIndex, file->beg);

		// Move to the start of the object index block
		file->seekg(objectIndex, file->beg);

		// Move to the start of the first string
		file->seekg(firstStringIndex, file->beg);

		file->close();

		return (int)RESULT::SUCCESS;
	}

	void printHeader() {
		cout << "OCAD Header file" << endl;
		cout << "\t Filetype: ";
		auto a = [&]() -> string& {
			switch (this->fileType){ 
			case 0:
				return string("normal map");
			case 1:
				return string("course setting project");
			default:
				return string("file is saved in Server");
			}
		};
		cout << endl;
		cout << "\t OCAD version: " << OCADversion << "." << (int) OCADsubV << "." << (int) OCADssubV << endl;

	}

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


