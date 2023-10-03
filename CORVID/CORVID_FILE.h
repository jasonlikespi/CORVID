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
}
#endif

