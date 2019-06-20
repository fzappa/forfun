#ifndef BASICLL
#define BASICLL

#include <string>

// This class define a simple node that point to the next node
class Node {
  public:
    std::string nodeName;
    Node *nextNode;

    Node() { nextNode = nullptr; }
    Node(std::string name, Node *ptr = nullptr)
    {
        nodeName = name;
        nextNode = ptr;
    }
};

class NodeList {
  private:
    Node *headNode, *tailNode;

  public:
    NodeList() { headNode = tailNode = nullptr; }

    ~NodeList();

    int isEmpty() { return headNode == nullptr; }

    void addHeadNode(std::string);
    void addTailNode(std::string);
    bool isInList(std::string) const;
};

#endif
