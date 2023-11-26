#include "CORVID_FILE.h"

CORVID_OBJFILE::CORVID_OBJFILE() {
	objects = new std::vector<std::vector<int>*>();
	name = "";
};
// Originally buffer was uninitialized, I changed that at the request of the compiler
// Just putting this here in case for some reason that breaks something
// Also, TODO That's definitely not what name should be initialized to
CORVID_OBJFILE::CORVID_OBJFILE(std::filesystem::path fileName) {
	name = "";
	std::ifstream* fs = new std::ifstream(fileName, std::ios::binary);
	int index = 0;
	int buffer = 0;
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
void CORVID_OBJFILE::save(std::filesystem::path folder) {};
CORVID_TEXTLIST::CORVID_TEXTLIST() {
	imgfiles = new std::vector<std::filesystem::path>();
};

CORVID_TEXTLIST::CORVID_TEXTLIST(std::filesystem::path masterFile) {
	std::ifstream* fs = new std::ifstream(masterFile);
	imgfiles = new std::vector<std::filesystem::path>();
	std::string buffer;
	while (fs->good()) {
		std::getline(*fs, buffer);
		imgfiles->push_back((std::filesystem::path(std::filesystem::current_path()) / buffer));
	}
};