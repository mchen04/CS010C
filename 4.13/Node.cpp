#include "Node.h"

Node::Node(string data) : data(data), left(nullptr), right(nullptr), count(1) { }

void Node::setData(string _data)
{
    data = _data ;
}

void Node::setLeft(Node* newLeft)
{
    left = newLeft ;
}

void Node::setRight(Node* newRight)
{
    right = newRight ;
}

void Node::setCount(int newCount)
{
    count = newCount ;
}

string Node::getData() const
{
    return data ;
}

Node *Node::getLeft() const
{
    return left ;
}

Node *Node::getRight() const
{
    return right ;
}

int Node::getCount() const
{
    return count ;
}