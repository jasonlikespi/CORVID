#pragma once
#ifndef CORVID_FILE_H
#define CORVID_FILE_H
// Needed to interact with files
#include <fstream>
// TODO Low Priority Might be able to change these into arrays
// But I'm fairly certain that it wouldn't improve efficiency a lot
// TODO Slightly Higher Priority Check for Memory Leaks
#include <vector>
// Needed for filenames
#include <string>
// Needed to interact with folders
#include <filesystem>

// I'm not sure if this should be its own namespace
// TODO Check if I should just seperate the classes
namespace CORVID_FILE {
	// Class that turns my custom made binary file into a vector of data for sprite creation
	// Effectively an Abstract Class that is the superclass for CORVID_WORLD
	class CORVID_OBJFILE {
	public:
		// Vector of object data to be turned into the level
		std::vector<std::vector<int>*>* objects;
		// Empty Constructor
		// Do not Use
		// @return an object with an empty vector
		CORVID_OBJFILE();
		// First Complete Constructor
		// TODO consider renaming fileName to like filePath or something
		// @param fileName A path to a file with the name of the level
		// @return a CORVID_OBJFILE Consisting of a vector of int[8] data ready to be loaded into a level
		CORVID_OBJFILE(std::filesystem::path fileName);
	};
	// Class that turns a text file into a vector of file paths for the games textures
	// I only use it for one method making it effectively static
	class CORVID_TEXTLIST {
	public:
		// Vector of all file paths that store the games texture data
		std::vector<std::filesystem::path>* imgfiles;
		// Empty Constructor
		// Do not Use
		// @return an object with an empty vector
		CORVID_TEXTLIST();
		// First Complete Constructor
		// TODO consider renaming masterFile to textureFile or something
		// @param masterFile a path to a file with a .txt extension
		// @return a CORVID_TEXTLIST object with a vector of paths corresponding to each line masterFile
		CORVID_TEXTLIST(std::filesystem::path masterFile);
	};
}
#endif

