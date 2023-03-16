// This code defines the implementation of the Tree class, which is based on an AVL tree data structure. 

#include "Tree.h" // Include the header file that defines the AVLTree class.

#include <iostream>
using namespace std ;

Tree::Tree()
{
    root = nullptr; // Set the root node to null upon initialization.
}

Tree::~Tree()
{
    delete root ; // Free the memory allocated to the root node upon destruction.
}

void Tree::insert(const string& str) {
    if (!root) {
        // If the root node is empty, create a new node with the given string as the small string and return.
        root = new Node();
        root->small = str;
        return;
    }

    Node* targetNode = root;
    while (targetNode->left) {
        // Traverse down the tree to find the appropriate position for the new string.
        targetNode = targetNode->hasTwoStrings() ?
            (targetNode->small > str ? targetNode->left :
                (targetNode->large < str ? targetNode->right : targetNode->middle)) :
            (targetNode->small > str ? targetNode->left : targetNode->middle);
    }

    if (targetNode->hasTwoStrings()) {
        // If the target node has two strings, split it into three nodes and insert the new string between the small and large strings.
        string small, middle, large;
        if (targetNode->small > str) {
            small = str;
            middle = targetNode->small;
            large = targetNode->large;
        } else {
            small = targetNode->small;
            if (targetNode->large < str) {
                middle = targetNode->large;
                large = str;
            } else {
                middle = str;
                large = targetNode->large;
            }
        }
        Node* smallNode = new Node();
        smallNode->small = small;
        Node* largeNode = new Node();
        largeNode->small = large;
        targetNode->small = middle;
        targetNode->large = "";
        targetNode->left = smallNode;
        targetNode->middle = largeNode;
        targetNode->right = nullptr;
        smallNode->parent = targetNode;
        largeNode->parent = targetNode;
        shiftUp(targetNode);
    } else {
        // If the target node has only one string, insert the new string into the node.
        insertStringIntoNode(targetNode, str);
    }
}

void Tree::insertStringIntoNode(Node* node, const string& str) {
    if (node->small > str) {
        node->large = node->small;
        node->small = str;
    } else {
        node->large = str;
    }
}



void Tree::shiftUp(Node* node) 
{
  if (node->parent) 
  {
    Node* parent = node->parent;
    if (parent->hasTwoStrings()) 
    {
      if (parent->small > node->small) 
      {
        Node* newLarge = new Node();
        newLarge->left = parent->middle;
        newLarge->left->parent = newLarge;
        newLarge->middle = parent->right;
        newLarge->middle->parent = newLarge;
        newLarge->small = parent->large;
        parent->left = node;
        parent->middle = newLarge;
        parent->right = nullptr;
        parent->large = "";
        newLarge->parent = parent;
      } 
      else if (parent->large < node->small) 
      {
        Node* newSmall = new Node();
        newSmall->left = parent->left;
        newSmall->left->parent = newSmall;
        newSmall->middle = parent->middle;
        newSmall->middle->parent = newSmall;
        newSmall->small = parent->small;
        parent->left = newSmall;
        parent->middle = node;
        parent->right = nullptr;
        parent->small = parent->large;
        parent->large = "";
        newSmall->parent = parent;
      } 
      else 
      {
        Node* newSmall = new Node();
        newSmall->small = parent->small;
        newSmall->left = parent->left;
        newSmall->left->parent = newSmall;
        newSmall->middle = node->left;
        newSmall->middle->parent = newSmall;
        Node* newLarge = new Node();
        newLarge->small = parent->large;
        newLarge->left = node->middle;
        newLarge->left->parent = newLarge;
        newLarge->middle = parent->right;
        newLarge->middle->parent = newLarge;
        parent->left = newSmall;
        parent->middle = newLarge;
        parent->right = nullptr;
        parent->small = node->small;
        parent->large = "";
        newSmall->parent = parent;
        newLarge->parent = parent;
        delete node;
      }
      shiftUp(parent);
    } 
    else 
    {
      if (parent->small > node->small) 
      {
        parent->large = parent->small;
        parent->small = node->small;
        parent->left = node->left;
        parent->right = parent->middle;
        parent->middle = node->middle;
      } 
      else 
      {
        parent->large = node->small;
        parent->middle = node->left;
        node->left->parent = parent;
        parent->right = node->middle;
        node->middle->parent = parent;
      }
      node->left->parent = parent;
      node->middle->parent = parent;
      delete node;
    }
  }
}


// Finds the node containing the given string in the tree
// Returns a pointer to the node if found, otherwise returns nullptr
Node* Tree::findNode(const string& str) const {
    Node* searchNode = root;
    while (searchNode)
    {
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))
        {
            return searchNode;
        }
        else 
        {
            if (searchNode->small > str)
            {
                searchNode = searchNode->left;
            }
            else
            {
                if (searchNode->hasTwoStrings() && searchNode->large < str)
                {
                    searchNode = searchNode->right;
                }
                else
                {
                    searchNode = searchNode->middle;
                }
            }
        }
    }
    // String not found, return nullptr
    return nullptr;
}

// Removes the node containing the given string from the tree
void Tree::remove(const string &str)
{
    // Find the node to remove
    Node* nodeToRemove = findNode(str);

    // If the string is not found, return
    if (!nodeToRemove) {
        return;
    }

    // If the node has two strings, remove the target string
    if (nodeToRemove->hasTwoStrings())
    {
        if (str == nodeToRemove->small)
        {
            nodeToRemove->small = nodeToRemove->large;
            nodeToRemove->large = "";
        }
        else
        {
            nodeToRemove->large = "";
        }
    }
    else // Node has only one string
    {
        Node* parent = nodeToRemove->parent;
        if (parent) {
            // If node has a parent, remove it and update the parent's children
            if (parent->left == nodeToRemove) {
                parent->left = nullptr;
                parent->large = parent->middle->small;
                parent->middle = nullptr;
            } else {
                parent->middle = nullptr;
                parent->large = parent->small;
                parent->small = parent->left->small;
                parent->left = nullptr;
            }
            delete nodeToRemove;
        }
        else // Node is the root
        {
            if (root->left) { // If the root has children, create a new root with its children
                Node* temp = new Node();
                temp->small = root->left->small;
                temp->large = root->middle->small;
                root = temp;
                delete nodeToRemove;
            } else { // If the root is a leaf, simply delete it
                delete root;
                root = nullptr;
            }
        }
    }
}

bool Tree::search(const string &key) const 
{
   //calls helper function
    return searchHelper(root, key) ;
}

bool Tree::searchHelper(Node* currNode, const string &key) const 
{
   //checks if node exists
    if (currNode) 
    { 
        if (currNode -> small == key || currNode -> large == key) //checks node to see if any values are same as key
        {
            return true;
        }
        else 
        {
            //recusively calls in direction and node based on value in position in node
            if (key < currNode -> small) 
            {
                return searchHelper(currNode -> left, key);
            }
            else if (key > currNode -> large) 
            {
                return searchHelper(currNode -> right, key);
            }
            else 
            {
                return searchHelper(currNode -> middle, key);
            }
        }
    }
    else 
    {
        return false;
    }
}

// This function traverses the tree in pre-order and prints out the values
// of each node as it visits them.
void Tree::preOrder() const 
{
    preOrderHelper(root);
    cout << endl;
}

// This function traverses the tree in in-order and prints out the values
// of each node as it visits them.
void Tree::inOrder() const 
{
    inOrderHelper(root);
    cout << endl;    
}

// This function traverses the tree in post-order and prints out the values
// of each node as it visits them.
void Tree::postOrder() const 
{
    postOrderHelper(root);
    cout << endl;    
}

// This helper function traverses the tree in pre-order and prints out the values
// of each node as it visits them. It takes in the current node as a parameter.
void Tree::preOrderHelper(Node* currNode) const 
{
    if (currNode)
    {
        // If the current node has two strings, print out the smaller string
        // first, then traverse the left subtree, print out the larger string,
        // traverse the middle subtree, and finally traverse the right subtree.
        if (currNode->hasTwoStrings())
        {
            cout << currNode->small << ", ";
            preOrderHelper(currNode->left);
            cout << currNode->large << ", ";
            preOrderHelper(currNode->middle);
            preOrderHelper(currNode->right);
        }
        // If the current node has only one string, print out that string,
        // traverse the left subtree, and then traverse the middle subtree.
        else
        {
            cout << currNode->small << ", ";
            preOrderHelper(currNode->left);
            preOrderHelper(currNode->middle);
        }
    }
}

// This helper function traverses the tree in in-order and prints out the values
// of each node as it visits them. It takes in the current node as a parameter.
void Tree::inOrderHelper(Node* currNode) const 
{
    if (currNode) // checking if the current node exists
    {
        inOrderHelper(currNode->left);
        cout << currNode->small << ", ";
        inOrderHelper(currNode->middle);

        if (currNode->hasTwoStrings())
        {
            cout << currNode->large << ", ";
            inOrderHelper(currNode->right);
        }
    }
}  

void Tree::postOrderHelper(Node* currNode) const 
{
    if (currNode) // checking if the current node exists
    {
        if (currNode->hasTwoStrings())
        {
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";
            postOrderHelper(currNode->right);
            cout << currNode->large << ", ";
        }
        else
        {
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";
        }
    }
}  