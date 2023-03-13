#include "Node.h"

Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) { }

bool Node::hasTwoStrings() const
{
    return !large.empty();
}

bool Node::hasTwoChildren() const {
    return left && middle && right;
}
