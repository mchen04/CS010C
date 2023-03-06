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

void insert(const string&)
{
    
}

void Tree::insertHelper(Node*& currNode, const string& key)
{

}

bool Tree::remove(string key&) {
   if (root->isLeaf() && root->numKeys == 1 && root->keys[0] == key) {
      tree->root = nullptr;
      return true;
   }
 
   Node* cur = tree->root;
   while (cur != nullptr) {
      if (cur->numKeys == 1 && cur != tree->root) {
         cur = Merge(cur);
      }
      int keyIndex = GetKeyIndex(cur, key);
      if (keyIndex != -1) {
         if (cur->isLeaf()) {
            remove(cur, keyIndex);
            return true;
         }
         Node* tmpChild = GetChild(cur, keyIndex + 1);
         string tmpKey = MinKey(tmpChild);
         remoev(tree, tmpKey);
         Swap(tree->root, key, tmpKey);
         return true;
      }
         
      cur = BTreeNextNode(cur, key);
   }
   return false;
}



Node* Tree::Merge(Node* node) {
   Node* leftSib = GetLeftSibling(node);
   Node* rightSib = GetRightSibling(node);

   if (leftSib != nullptr && leftSib->numKeys >= 2)
      RotateRight(leftSib);
   else if (rightSib != nullptr && rightSib->numKeys >= 2)
      RotateLeft(rightSib);
   else {
      // Fuse
      if (leftSib == nullptr)
         node = Fuse(node, rightSib);
      else
         node = Fuse(leftSib, node);
   }

   return node;
}

string Tree::MinKey(Node* node) {
   Node* cur = node;

   while (cur->left != nullptr) {
      cur = cur->left;
   }

   return cur->keys[0];
}

Node* Tree::GetChild(Node* node, int childIndex) {
   if (childIndex == 0)
      return node->left;
   else if (childIndex == 1)
      return node->middle1;
   else if (childIndex == 2)
      return node->middle2;
   else if (childIndex == 3)
      return node->right;
   else
      return nullptr;
}

Node* Tree::BTreeNextNode(Node* node, string key) {
   if (key < node->keys[0])
      return node->left;
   else if (node->keys[1] == nullptr || key < node->keys[1])
      return node->middle1;
   else if (node->keys[2] == nullptr || key < node->keys[2])
      return node->middle2;
   else
      return node->right;
}

bool Tree::BTreeKeySwap(Node* node, string existing, string replacement) {
   if (node == nullptr)
      return false;

   int keyIndex = GetKeyIndex(node, existing);
   if (keyIndex == -1) {
      Node* next = NextNode(node, existing);
      return KeySwap(next, existing, replacement);
   }

   if (keyIndex == 0)
      node->keys[0] = replacement;
   else if (keyIndex == 1)
      node->keys[1] = replacement;
   else
      node->keys[2] = replacement;

   return true;
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