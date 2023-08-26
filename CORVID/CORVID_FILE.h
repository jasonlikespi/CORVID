#ifndef CORVID_FILE_H
#define CORVID_FILE_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
// Notes on Structure of File
// Object Data File follows the format ( One int for each)
// 0- Header Int
// 1- Location X Value
// 2- Location Y Value
// 3- Size X Value
// 4- Size Y Value
// 5- Object Type Value (0 is static, 1 is dynamic, 2 is background, 3 is checkpoint)
// 6- Texture Value
// 7- Movement Behavior Value

//Texture List
/*
 * 0 - brick.png
 * 1 - titleScreen.png
 * 2 - sky.png
 *
 *
 *
 *
 */
using namespace std::filesystem;

class CORVID_FILE {
public:
	std::vector<std::vector<int>*>* objects;
	CORVID_FILE() {
		objects = new std::vector<std::vector<int>*>();
	};
	CORVID_FILE(path fileName) {
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
};
#endif