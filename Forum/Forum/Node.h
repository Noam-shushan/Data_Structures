#pragma once
#include <iostream>
#include <string>
#include <list>


class Node {
    std::string content;
    std::list<Node*> responses;

public:
    Node(const std::string& title = ""); //constrector
    ~Node(); //distractor

    const std::string& getContent() const;
    std::list<Node*>& getResponses();

    Node& addResponse(const std::string& response);// add new response to the Node
    Node* findResponseNode(const std::string& value); // find response in the responses list

    // overload an operator so that the remove function from list really deleted the node
    bool operator == (const Node* n) const { return content == n->getContent(); }
    bool operator != (const Node* n) const { return !operator==(n); }
};

