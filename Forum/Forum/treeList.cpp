#include"treeList.h"

treeList::treeList() {}

treeList::~treeList() {}

/// <summary>
/// add a new discotion title
/// </summary>
/// <param name="title"></param>
void treeList::addNewTree(std::string title)
{
	Tree* newTree = new Tree(title);
	myList.push_front(newTree);
}

void treeList::eraseTree(Tree* treePointer)
{
	delete treePointer;
}

/// <summary>
/// search all node that contain the title
/// and print path to reach it and the sub tree from title
/// </summary>
/// <param name="title"></param>
void treeList::searchAndPrint(std::string title)
{
	int success = 0;
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		if ((*iter)->getRoot()->getContent() == title)
		{
			(*iter)->printTree();
			return;
		}
		success += (*iter)->printPathFromRoot(title);

		if (success)
			std::cout << "\n";
	}

	if (!success)
		std::cout << "ERROR\n";
}

/// <summary>
/// add response to a discotion
/// </summary>
/// <param name="title"></param>
/// <param name="father"></param>
/// <param name="son"></param>
/// <returns></returns>
bool treeList::addResponse(std::string title, std::string father, std::string son)
{
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		if ((*iter)->getRoot()->getContent() == title)
		{
			if (title == father)
			{
				(*iter)->addResponse(title, son);
				return true;
			}
			else
			{
				Node* subTree = (*iter)->findResponse(father);
				if (subTree == NULL)
					return false;

				subTree->addResponse(son);
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// find a given response in the trees and delete the
/// sub tree from her locotion
/// </summary>
/// <param name="title"></param>
/// <param name="father"></param>
/// <returns></returns>
bool treeList::delResponse(std::string title, std::string father)
{
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		if ((*iter)->getRoot()->getContent() == title)
		{
			if (title == father)
			{
				myList.erase(iter);
				return true;
			}
			return (*iter)->deleteSubTree(father);
		}
	}
	return false;
}

/// <summary>
/// print a given discotion tree
/// </summary>
/// <param name="headTree"></param>
void treeList::printTree(std::string headTree)
{
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		if ((*iter)->getRoot()->getContent() == headTree) {
			(*iter)->printTree();
			return;
		}
	}
}

/// <summary>
/// print all trees in the tree list
/// </summary>
void treeList::printAllTrees()
{
	int index = 1;
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++, index++)
	{
		std::cout << "Tree #" << index << std::endl;
		if (iter == myList.end())
		{
			(*iter)->printTree();
			return;
		}
		(*iter)->printTree();
	}
}

/// <summary>
/// print a given sub tree
/// </summary>
/// <param name="headTree"></param>
/// <param name="son"></param>
void treeList::printSubTree(std::string headTree, std::string son)
{
	if (headTree == son)
	{
		this->printTree(headTree);
		return;
	}
	for (std::list<Tree*>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		if ((*iter)->getRoot()->getContent() == headTree)
		{
			(*iter)->printPathFromRoot(son);
			return;
		}
	}
}