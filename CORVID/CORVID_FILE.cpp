#include "CORVID_FILE.h"

CORVID_FILE::CORVID_FILE() {
	objects = new std::vector<std::vector<int>*>();
};
CORVID_FILE::CORVID_FILE(path fileName) {
	std::ifstream* fs = new std::ifstream(fileName, std::ios::binary);
	int index = 0;
	int buffer;
	objects = new std::vector<std::vector<int>*>();
	while (!fs->eof()) {
		fs->read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		if (index % 8 == 0) {
			objects->push_back(new std::vector<int>());
			objects->back()->push_back(buffer);
		}
		else {
			objects->back()->push_back(buffer);
		}
		index++;
	}
};
void writeToText() {
	std::ifstream fileStream;
	//fileStream.open("C:\\Users\\jason\\source\\repos\\CORVID\\CORVID\\testo\\dataDump.txt.txt", std::ios::in | std::ios::out);
	//for (int i = 0; i < data->size(); i++) {
	//	fileStream << data->at(i);
	//	if (i % 8 == 0) { fileStream << "\n"; } else { fileStream << " "; }
	//}
	fileStream.close();
}