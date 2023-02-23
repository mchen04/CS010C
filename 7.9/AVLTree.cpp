// This code implements an AVL tree data structure for storing and maintaining a set of strings.

#include "AVLTree.h" // Include the header file that defines the AVLTree class.

using namespace std;

// The constructor initializes the root pointer to null.
AVLTree::AVLTree() : root(nullptr) {}

// The destructor deletes the root node, which in turn deletes all the other nodes in the tree.
AVLTree::~AVLTree() {
delete root ;
}

void AVLTree::insert(const string& key) {
    Node* currNode = root ;
    while (currNode)
    {
        if (currNode -> data > key)
        {
            currNode = currNode -> left;
        }
        else if (currNode -> data < key)
        {
            currNode = currNode -> right;
        }
        else
        {
            return ; // key already exists in the tree
        }
    }

    Node* newNode = new Node(key) ;  // create a new node with the given key
    insertHelper(newNode);  // insert the new node into the AVL tree
}

// Helper function to insert a node into the AVL tree
void AVLTree::insertHelper(Node* newNode) {
   if (!root) { // the tree is empty
      root = newNode ;
      newNode -> parent = nullptr ;
      return ;
   }

   Node* currNode = root;
   while (currNode) {
      if (newNode -> data < currNode -> data) { // the node should be inserted in the left subtree
         if (!currNode -> left) { // if the left child of cur is null
            currNode -> left = newNode ; // insert the node as the left child of cur
            newNode -> parent = currNode ;
            currNode = nullptr ; // exit the loop
         }
         else { // the left child of cur is not null
            currNode = currNode -> left ; // keep traversing down the left subtree
         }
      }
      else { // the node should be inserted in the right subtree
         if (!currNode -> right) { // if the right child of cur is null
            currNode -> right = newNode ; // insert the node as the right child of cur
            newNode -> parent = currNode ;
            currNode = nullptr ; // exit the loop
         }
         else { // the right child of cur is not null
            currNode = currNode -> right ; // keep traversing down the right subtree
         }
      }
   }

   // Rebalance the tree
   newNode = newNode -> parent ; // start at the parent of the inserted node
   while (newNode) { // traverse up the tree until the root is reached
      TreeRebalance(newNode) ; // rebalance the tree at each node
      newNode = newNode -> parent ; // move up to the parent of the current node
   }
}

// Print the balance factors of all nodes in the tree
void AVLTree::printBalanceFactors() const
{
    recurBalanceFactors(root) ; // call the recursive helper function
    cout << endl ;
}

// Helper function to recursively print the balance factors of all nodes in the tree
void AVLTree::recurBalanceFactors(Node *currNode) const
{
    if (currNode)
    {
        recurBalanceFactors(currNode -> left) ; // traverse the left subtree
        cout << currNode -> data << "(" << balanceFactor(currNode) << "), " ; // print the balance factor of the current node
        recurBalanceFactors(currNode -> right) ; // traverse the right subtree
    }
}

// Update the height of a node based on the heights of its children
void AVLTree::updateHeight(Node* currNode) {
   int leftHeight = -1 ;
   if (currNode -> left)
      leftHeight = currNode -> left -> height ;
   int rightHeight = -1 ;
   if (currNode -> right)
      rightHeight = currNode -> right -> height ;
   currNode -> height = max(leftHeight, rightHeight) + 1 ;
}

// This function calculates the balance factor of a given node in the AVL tree.
// It returns the difference between the height of the node's left subtree
// and the height of its right subtree.
int AVLTree::balanceFactor(Node* currNode) const {
   int leftHeight = -1 ;
   if (currNode -> left)
      leftHeight = currNode -> left -> height ;
   int rightHeight = -1 ;
   if (currNode -> right)
      rightHeight = currNode -> right -> height ;
   return leftHeight - rightHeight ;
}

// This function rebalances the tree starting at the given node. It updates the
// height of the node, checks its balance factor, and performs necessary rotations
// to balance the tree.
void AVLTree::TreeRebalance(Node* currNode) {
   updateHeight(currNode) ;
   if (balanceFactor(currNode) == -2) {
      if (balanceFactor(currNode -> right) == 1) {
         // Double rotation case: right-left rotation
         rotateRight(currNode -> right) ;
      }
      // Single rotation case: left rotation
      rotateLeft(currNode) ;
   }
   else if (balanceFactor(currNode) == 2) {
      if (balanceFactor(currNode -> left) == -1) {
         // Double rotation case: left-right rotation
         rotateLeft(currNode -> left) ;
      }
      // Single rotation case: right rotation
      rotateRight(currNode) ;
   }
   // Note: the return statement in the pseudocode is unnecessary,
   // since we're modifying the tree in place rather than returning a new node.
}

// This function performs a right rotation around the given node.
// It assumes that node has a left child and that left child has a right child.
void AVLTree::rotateRight(Node* currNode) {
   Node* leftRightChild = currNode -> left -> right ;
   if (currNode -> parent) {
      ReplaceChild(currNode -> parent, currNode, currNode -> left) ;
   }
   else { // node is root
      root = currNode -> left ;
      root -> parent = nullptr ;
   }
   SetChild(currNode -> left, "right", currNode) ;
   SetChild(currNode, "left", leftRightChild) ;
}

// This function performs a left rotation around the given node.
// It assumes that node has a right child and that right child has a left child.
void AVLTree::rotateLeft(Node* currNode) {
   Node* rightLeftChild = currNode -> right -> left ;
   if (currNode -> parent) {
      ReplaceChild(currNode -> parent, currNode, currNode -> right) ;
   }
   else { // node is root
      root = currNode -> right ;
      root -> parent = nullptr ;
   }
   SetChild(currNode -> right, "left", currNode) ;
   SetChild(currNode, "right", rightLeftChild) ;
}

// This function sets the child of a given parent node
// whichChild parameter should be either "left" or "right"
// Returns true if successful, false otherwise
bool AVLTree::SetChild(Node* parent, const string& whichChild, Node* child) {
    if (whichChild != "left" && whichChild != "right")
    {
        return false ;
    }
    if (whichChild == "left")
    {
        parent -> left = child ;
    }
    else
    {
        parent -> right = child ;
    }
    if (child)
    {
        child -> parent = parent ;
    }

   updateHeight(parent) ;
   return true ;
}

// This function replaces a child node of a given parent with a new node
// Returns true if successful, false otherwise
bool AVLTree::ReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
   if (parent -> left == currentChild)
   {
      return SetChild(parent, "left", newChild);
   }
   else if (parent -> right == currentChild)
   {
      return SetChild(parent, "right", newChild);
   }
   return false ;
}


void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout << "Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}