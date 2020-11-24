#pragma once
#include "Node.h"

class Tree {
    Node* root;

public:
    Tree();//constrector
    ~Tree();//distractor
    Tree(const std::string& value);//copy constractor

    void newSubject(const std::string& value);

    Node* getRoot();
    Node* findResponse(const std::string& value, Node* node, std::string getFather);
    Node* findResponse(const std::string& value, std::string getFather);
    Node* findResponse(const std::string& value);

    bool addResponse(const std::string& father, const std::string& son);

    bool deleteSubTree(const std::string& value);
    void printTree(int level, Node* tree);
    void printTree();
    bool printPathFromRoot(const std::string& value, Node*, std::list<std::string>& output);
    bool printPathFromRoot(const std::string& value);
    void printSubTree(const std::string& value);
};

void putSpaces(int level);