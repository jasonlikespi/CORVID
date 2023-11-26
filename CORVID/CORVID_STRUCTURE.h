#ifndef CORVID_STRUCTURE_H
#define CORVID_STRUCTURE_H
#include <vector>
#include "CORVID_CLASS.h"
#include <functional>
// This is a general Node for a tree class
template <class KEY, class VALUE>
class CORVID_NODE {
	KEY key;
	CORVID_NODE<KEY, VALUE>* parent;
	CORVID_NODE<KEY, VALUE>* leftChild;
	CORVID_NODE<KEY, VALUE>* rightChild;
	CORVID_NODE(VALUE* value);
};
// This is a general tree for a tree class
//
template <class KEY, class VALUE>
class CORVID_TREE {
	CORVID_NODE<KEY, VALUE>* head;
	int size;
	CORVID_TREE();
	void add(CORVID_NODE<KEY, VALUE>* nodeToAdd);
	void remove(CORVID_NODE<KEY, VALUE>* nodeToRemove);
	int getsize();
};


// This is a class used just for elements in CORVID_STRUCTURE
// The reason that there is a seperate above/below/left/right to the tree values is because
// In cases of overlapping objects; They must be exactly adjacent for this distinction.
template <class KEY, class VALUE>
class CORVID_ELEMENT : public VALUE{
	KEY* key;
	bool mobile;
	VALUE* above;
	VALUE* below;
	VALUE* left;
	VALUE* right;
	// I think I'm going to have this maintain a list of all objects within double the radius
	std::vector<CORVID_ELEMENT<KEY, VALUE>*>* neighbors;
	CORVID_ELEMENT<KEY, VALUE>(VALUE* element);
};


// This is a complicated Data Structure used for data relations
// Each object exists in 3D Space
// TODO Get Iterator Working
// TODO I'm also trying to add a tree in there
// TODO Add this stuff to CORVID_CLASS
template <class KEY, class VALUE>
class CORVID_STRUCTURE{
	CORVID_ELEMENT<KEY, VALUE>* active;
	CORVID_TREE<KEY, VALUE>* horizontalTree;
	CORVID_TREE<KEY, VALUE>* verticalTree;
	int size;
	CORVID_STRUCTURE();
	void add(CORVID_ELEMENT<KEY, VALUE>* newElement);
	void remove(CORVID_ELEMENT<KEY, VALUE>* toBeRemoved);
	int getsize() { return this->size;};
	// Use this as iterator for things like render, updateobject, ect?
	void iter(std::function<void(VALUE* arg)> operation);
};
// TODO Write the documentation for this file (and CORVID_STRUCTURE.cpp)

#endif
