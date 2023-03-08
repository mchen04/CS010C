#include "Tree.h" // Include the header file that defines the AVLTree class.

#include <iostream>
using namespace std ;

Tree::Tree()
{
    root = nullptr;
}

Tree::~Tree()
{
    delete root ;
}

void Tree::insert(const string&key)
{
   if (!search(key))
   {
      insertHelper(root, key) ;
   }
}

void Tree::insertHelper(Node*& currNode, const string& key) {

}

void Tree::InsertKeyWithChildren(Node* parent, const string& key, Node* leftChild, Node* rightChild) {
   if (key < parent->small) {
      parent->large = parent->small;
      parent->small = key;
      parent->right = parent->middle;
      parent->middle = parent->left;
      parent->left = leftChild;
   }
   else if (parent->large.empty() || key < parent->large) {
      parent->large = key;
      parent->right = parent->middle;
      parent->middle = rightChild;
      parent->left = leftChild;
   }
   else {
      parent->large = key;
      parent->right = rightChild;
      parent->middle = leftChild;
   }
}

void Tree::remove(const string&){

}

bool Tree::search(const string &key) const {
    return searchHelper(root, key) ;
}

bool Tree::searchHelper(Node* currNode, const string &key) const {
    if (currNode) { 
        if (currNode -> small == key || currNode -> large == key) {
            return true;
        }
        else {
            if (key < currNode -> small) {
                return searchHelper(currNode -> left, key);
            }
            else if (key > currNode -> large) {
                return searchHelper(currNode -> right, key);
            }
            else {
                return searchHelper(currNode -> middle, key);
            }
        }
    }
    else {
        return false;
    }
}

void Tree::preOrder( ) const {
    preOrderHelper(root);
    cout << endl;
}

void Tree::inOrder( ) const {
    inOrderHelper(root);
    cout << endl;    
}

void Tree::postOrder( ) const {
    postOrderHelper(root);
    cout << endl;    
}

void Tree::preOrderHelper(Node* root) const {
    if (!root) {
        return;
    }
    cout << root -> small << " " ; 
    cout << root -> large << " " ;
    preOrderHelper(root -> left) ;
    preOrderHelper(root -> middle) ;
    preOrderHelper(root -> right) ;
}

void Tree::inOrderHelper(Node* root) const {
    if (!root) {
        return ;
    }
    inOrderHelper(root -> left) ;
    cout << root -> small << " " ;
    inOrderHelper(root -> middle) ;
    cout << root -> large << " " ;
    inOrderHelper(root -> right) ;
}  

void Tree::postOrderHelper(Node* root) const {
    if (!root) {
        return ;
    }    
    postOrderHelper(root -> left) ;
    postOrderHelper(root -> middle) ;
    postOrderHelper(root -> right) ;
    cout << root -> small << " " ; 
    cout << root -> large << " " ;
    
}  