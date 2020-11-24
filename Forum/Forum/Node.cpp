
#include "Node.h"
/// <summary>
/// constractor
/// </summary>
/// <param name="title"></param>
Node::Node(const std::string& title) : content(title) {}
/// <summary>
/// distractor
/// </summary>
Node::~Node()
{
    for (std::list<Node*>::iterator iter = responses.begin();
        iter != responses.end(); ++iter)
        delete* iter;
}
/// <summary>
/// get the content of the response
/// </summary>
/// <returns>content</returns>
const std::string& Node::getContent() const
{
    return this->content;
}
/// <summary>
/// get the responses list of the Node
/// </summary>
/// <returns>responses</returns>
std::list<Node*>& Node::getResponses()
{
    return this->responses;
}
/// <summary>
/// add new response to the responses list
/// </summary>
/// <param name="response"></param>
/// <returns></returns>
Node& Node::addResponse(const std::string& response)
{
    Node* son(new Node);
    son->content = response;
    this->responses.push_back(son);
    return *this;
}
/// <summary>
/// find the response by a given value string
/// </summary>
/// <param name="value"></param>
/// <returns>the response if it is exsist else nullptr</returns>
Node* Node::findResponseNode(const std::string& value)
{
    for (std::list<Node*>::iterator iter = responses.begin();
        iter != responses.end(); iter++)
    {
        if ((*iter)->content == value)
            return *iter;
    }
    return NULL;
}



