#include "Tree.h"

/// <summary>
/// constractor
/// </summary>
Tree::Tree() : root(new Node()) {}
/// <summary>
/// distractor
/// </summary>
Tree::~Tree()
{
    delete root;
}
/// <summary>
/// copy constractor
/// </summary>
/// <param name="value"></param>
Tree::Tree(const std::string& value) : root(new Node(value)) {}

/// <summary>
/// get the root of the tree
/// </summary>
/// <returns>root</returns>
Node* Tree::getRoot()
{
    return root;
}
/// <summary>
/// delet the tree and add a new discotion title
/// </summary>
/// <param name="title"></param>
void Tree::newSubject(const std::string& title)
{
    delete this->root;
    this->root = new Node(title);
}

/// <summary>
/// find response in the tree
/// search in recursion the response according to the given value,
///  can also return the father of the response
/// </summary>
/// <param name="value">the response we search</param>
/// <param name="node">the currnt node to the recursion</param>
/// <param name="getFather">the father of response we search</param>
/// <returns>the response or the father of the response or null</returns>
Node* Tree::findResponse(const std::string& value, Node* node, std::string getFather)
{
    Node* result = node->findResponseNode(value);

    if (result != NULL)
    {
        if (getFather == "father")
            return node; // return the father of the response
        else
            return result; // return the response 
    }

    for (std::list<Node*>::iterator iter = node->getResponses().begin();
        iter != node->getResponses().end(); ++iter)
    {
        if (!(*iter)->getResponses().empty())//check if the node as children
        {
            result = findResponse(value, (*iter), getFather);//recursion
            if (result)
                return result;
        }
    }
    if (result)
        return result;
    else
        return NULL;
}

/// <summary>
/// overlode fanction to just find the node
/// or the father of the node witeout recursion
/// </summary>
/// <param name="value">the response we search</param>
/// <param name="getFather">the father of response we search</param>
/// <returns></returns>
Node* Tree::findResponse(const std::string& value, std::string getFather)
{
    return this->findResponse(value, root, getFather);
}
/// <summary>
/// overlode fanction to just find the node witeout recursion
/// </summary>
/// <param name="value"></param>
/// <returns></returns>
Node* Tree::findResponse(const std::string& value)
{
    if (root->getContent() == value)
        return root;
    return this->findResponse(value, root, "son");
}

/// <summary>
/// add response to the tree by a given father
/// </summary>
/// <param name="father"></param>
/// <param name="son"></param>
/// <returns>true if the addition was made, else false</returns>
bool Tree::addResponse(const std::string& father, const std::string& son)
{
    if (father == root->getContent()) {
        root->addResponse(son); // if the father is the root
        return true;
    }

    Node* fatherNode = this->findResponse(father); // search for the father in the tree 
    if (fatherNode == NULL)
        return false;

    fatherNode->addResponse(son);
    return true;
}

/// <summary>
/// delete sub tree by a given value of responses
/// </summary>
/// <param name="value"></param>
bool Tree::deleteSubTree(const std::string& value)
{
    Node* treeToDel = this->findResponse(value); // search the response
    Node* theFather = this->findResponse(value, "father"); // get the father of the response

    if (treeToDel != NULL && theFather != NULL) {
        theFather->getResponses().remove(treeToDel); // delete
        return true;
    }

    return false;
}

/// <summary>
/// print the tree by recursion
/// the level is to know in which level the response is 
/// and put speces in a good layout
/// </summary>
/// <param name="level">level of the response</param>
/// <param name="node">the node for the recursion</param>
void Tree::printTree(int level, Node* node)
{
    std::cout << node->getContent() << std::endl; // print the currnt node

    for (std::list<Node*>::iterator iter = node->getResponses().begin();
        iter != node->getResponses().end(); ++iter)
    {
        putSpaces(level);
        if (!(*iter)->getResponses().empty()) // check if the node as children
            printTree(level + 1, (*iter)); // recursion
        else { // print the next responses in the currnt responses list
            std::cout << (*iter)->getContent() << std::endl;
        }
    }
}
/// <summary>
/// overlode the prev function to start from the root
/// </summary>
void Tree::printTree()
{
    printTree(1, root);
    std::cout << "\n\n";
}

/// <summary>
/// get the path from root to a given response
/// by recursion
/// </summary>
/// <param name="value">the response</param>
/// <param name="node">the node for the recursion</param>
/// <param name="output">the list of the output to get the path from the node to the root</param>
/// <returns>true if it is a success search </returns>
bool Tree::printPathFromRoot(const std::string& value, Node* node, std::list<std::string>& output)
{
    output.push_front(node->getContent()); // print the currnt node

    for (std::list<Node*>::iterator iter = node->getResponses().begin();
        iter != node->getResponses().end(); ++iter)
    {
        output.push_front(" => ");
        if ((*iter)->getContent() == value) { // the last item in the path
            output.push_front((*iter)->getContent());
            return true;
        }

        if (!(*iter)->getResponses().empty()) // check if the node as children
        {
            if (printPathFromRoot(value, (*iter), output) == true)
                return true;
        }
        else // print the next response in the currnt responses list
            output.push_front((*iter)->getContent()); // Because it is part of the path
    }

    return false;
}
/// <summary>
/// overlode the prev function to start from the root
/// </summary>
/// <param name="value">the given response</param>
bool Tree::printPathFromRoot(const std::string& value)
{
    Node* out = this->findResponse(value);
    bool success = false;
    if (out == NULL) { // check first if the response in the tree
        return false;
    }
    printTree(1, out);
    std::cout << "\n";

    std::list<std::string> output;
    success = this->printPathFromRoot(value, root, output);

    for (std::list<std::string>::iterator iter = output.begin();
        iter != output.end(); ++iter)
        std::cout << *iter;

    return success;
}

/// <summary>
/// print sub tree by a given response 
/// </summary>
/// <param name="value">the given response</param>
void Tree::printSubTree(const std::string& value)
{
    Node* subTtee = this->findResponse(value);

    if (subTtee == NULL)
        return;

    this->printTree(1, subTtee);
    std::cout << "\n\n";
}

void putSpaces(int level)
{
    for (int i = 0; i < level; i++)
        std::cout << "    ";
}