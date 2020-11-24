#pragma once
#include "Tree.h"


class treeList
{
private:
	std::list<Tree*> myList;
public:
	treeList();//constrector
	~treeList();//distractor

	void addNewTree(std::string title);
	void eraseTree(Tree* treePointer);
	void searchAndPrint(std::string title); //search all node that contain string and print path to reach it

	bool addResponse(std::string title, std::string father, std::string son); //add response in a certain tree +vav?
	bool delResponse(std::string headTree, std::string node);//search node and erase sub tree from node

	void printTree(std::string headTree);
	void printAllTrees();
	void printSubTree(std::string headTree, std::string son); // given  name of head tree and response print path to it and subtree
};
