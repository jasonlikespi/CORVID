#include "CORVID_FILE.h"

CORVID_FILE::CORVID_OBJFILE::CORVID_OBJFILE() {
	objects = new std::vector<std::vector<int>*>();
};

CORVID_FILE::CORVID_OBJFILE::CORVID_OBJFILE(std::filesystem::path fileName) {
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

CORVID_FILE::CORVID_TEXTLIST::CORVID_TEXTLIST() {
	imgfiles = new std::vector<std::filesystem::path>();
};

CORVID_FILE::CORVID_TEXTLIST::CORVID_TEXTLIST(std::filesystem::path masterFile) {
	std::ifstream* fs = new std::ifstream(masterFile);
	imgfiles = new std::vector<std::filesystem::path>();
	std::string buffer;
	while (!fs->eof()) {
		std::getline(*fs, buffer);
		imgfiles->push_back((std::filesystem::current_path() / buffer));
	}
};

void CORVID_FILE::writeToText() {
	std::ifstream fileStream;
	fileStream.close();
}