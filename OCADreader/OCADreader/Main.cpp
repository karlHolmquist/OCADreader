#include "reader.hpp"

using namespace std;

int main(int argc, char* argv[]){
	string filePath = "C:\\Users\\Karl\\Desktop\\rydsbladet.ocd";

	OCADreader r(filePath);
	if (r.readFromFile() != 0) {
		cout << "Error: couldn't read file" << endl;
		return 0;
	}
	r.printHeader();

	return 1;

}