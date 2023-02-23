#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include "Node.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std ;

class AVLTree {
public:
    AVLTree() ;
    ~AVLTree() ;
    void insert(const string&) ;
    int balanceFactor(Node*) const ;
    void printBalanceFactors() const ;
    void visualizeTree(const string&) ;

private:
    Node* root ;
    void rotateLeft(Node*) ;
    void rotateRight(Node*) ;
    void TreeRebalance(Node* node) ;
    void recurBalanceFactors(Node *node) const ;
    void visualizeTree(ofstream&, Node*) ;
    void insertHelper(Node*) ;
    void updateHeight(Node*) ;
    bool SetChild(Node*, const string&, Node*) ;
    bool ReplaceChild(Node*, Node*, Node*) ;
};

#endif // __AVL_TREE_H__
