#include "basicLL.hpp"
#include <iostream>
#include <memory>

NodeList::~NodeList()
{
    for (Node *p; !isEmpty();) {
        p = headNode->nextNode;
        delete headNode;
        headNode = p;
    }
}

void NodeList::addHeadNode(std::string name)
{
    std::cout << "Add " << name << " node." << std::endl;
    headNode = new Node(name, headNode);
    if (tailNode == nullptr)
        tailNode = headNode;
}
void NodeList::addTailNode(std::string name)
{
    if (tailNode != nullptr) {  // if list not empty;
        tailNode->nextNode = new Node(name);
        tailNode	   = tailNode->nextNode;
    }
    else
        headNode = tailNode = new Node(name);
}

bool NodeList::isInList(std::string name) const
{
    Node *tmp;
    for (tmp = headNode; tmp != nullptr && !(tmp->nodeName == name); tmp = tmp->nextNode)
        ;
    return tmp != nullptr;
}
