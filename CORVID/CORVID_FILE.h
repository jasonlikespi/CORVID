#pragma once
#ifndef CORVID_FILE_H
#define CORVID_FILE_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

namespace CORVID_FILE {
	class CORVID_OBJFILE {
	public:
		std::vector<std::vector<int>*>* objects;
		CORVID_OBJFILE();
		CORVID_OBJFILE(std::filesystem::path fileName);
	};
	class CORVID_TEXTLIST {
	public:
		std::vector<std::filesystem::path>* imgfiles;
		CORVID_TEXTLIST();
		CORVID_TEXTLIST(std::filesystem::path masterFile);
	};
	void writeToText();
}
#endif

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