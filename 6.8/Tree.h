#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>

using namespace std;

class Tree {
public:
    Tree();
    ~Tree();
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void insert(const string&);
    void remove(const string&);
    bool search(const string&) const;
    
private:
    Node *root;
    void preOrderHelper(Node*) const;
    void inOrderHelper(Node*) const;
    void postOrderHelper(Node*) const;
    void insertHelper(Node*&, const string&);
    void removeHelper(Node*&, const string&);
    bool searchHelper(Node*, const string&) const;
    Node* Merge(Node*) ;
    string MinKey(Node*) ;
    Node* GetChild(Node*, int) ;
    Node* BTreeNextNode(Node*, string) ;
    bool BTreeKeySwap(Node*, string, string) ;
    
};

#endif