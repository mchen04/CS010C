#include "BSTree.h"
#include <iostream>

using namespace std ;

// constructor that sets root to nullptr
BSTree::BSTree()
{
    root = nullptr ;
}

// destructor that deletes the root node
BSTree::~BSTree()
{
    delete root ;
}

// function that inserts new string in the binary search tree
void BSTree::insert(const string &newString)
{
    // pointers to track current node and its parent node
    Node* parentNode = nullptr ;
    Node* currNode = root ;

    // boolean to keep track of whether the new node will be inserted as the left or right child of the parent node
    bool isLeft = true ;

    // find the location where new node should be inserted
    while (currNode != nullptr && !(newString == currNode -> getData()))
    {
        parentNode = currNode ;
        if (currNode -> getData() > newString)
        {
            currNode = currNode -> getLeft() ;
            isLeft = true ;
        }
        else
        {
            currNode = currNode -> getRight() ; 
            isLeft = false ;
        }
    }

    // if the string is already present, increment its count
    if (currNode != nullptr) 
    {
        currNode -> setCount(currNode -> getCount() + 1) ;
    }
    // if the string is not present, create a new node and insert it in the tree
    else 
    {
        Node* addNode = new Node(newString) ;

        if (parentNode != nullptr) 
        {
            if (isLeft)
            {
                parentNode -> setLeft(addNode) ;
            }
            else
            {
                parentNode -> setRight(addNode) ;
            }
        }
        else 
        {
            root = addNode;
        }
    }
}

void BSTree::remove(const string &key)
{
    // If the key is not present in the tree, return
    if (!search(key))
    {
        return ;
    }

    // If the root is the only node in the tree, delete it
    if(root -> getLeft() == nullptr && root -> getRight() == nullptr) {
        delete root ;
        root = NULL ;
        return ;
    }

    // Call helper function to remove the node with the key
    remove(root, key) ;
}

Node* BSTree::remove(Node* currNode, const string &key)
{
    // If the current node is null, return nullptr
    if (currNode == nullptr)
    {
        return nullptr ;
    }

    // If the key is smaller than the current node's key, 
    // remove from the left subtree
    if (key < currNode -> getData()) { 
	    currNode -> setLeft(remove(currNode -> getLeft(), key)) ;
	}
	// If the key is larger than the current node's key, 
	// remove from the right subtree
	else if (key > currNode -> getData()) {  
		currNode -> setRight(remove(currNode -> getRight(), key)) ;
	}
	else 
    {
		// If the count of the node is greater than 1, just decrement the count
		if (currNode -> getCount() > 1) {
			currNode -> setCount(currNode -> getCount() - 1);
		}
		// If the node has no children, delete it
		else if (currNode -> getLeft() == nullptr && currNode -> getRight() == nullptr) {
			delete currNode ;
			return nullptr ;
		}
		// If the node has only a right child, 
		// replace with the minimum of the right subtree
		else if (currNode -> getLeft() == nullptr) {
			Node *MinNode = FindMin(currNode -> getRight()) ;
			currNode -> setData(MinNode -> getData()) ;
			currNode -> setCount(MinNode -> getCount()) ;
			MinNode -> setCount(0) ;

			currNode -> setRight(remove(currNode -> getRight(), MinNode -> getData())) ;
		}
		// If the node has only a left child, 
		// replace with the maximum of the left subtree
		else if (currNode -> getRight() == nullptr) {
			Node *MaxNode = FindMax(currNode -> getLeft()) ;
			currNode -> setData(MaxNode -> getData()) ;
			currNode -> setCount(MaxNode -> getCount()) ;
			MaxNode-> setCount(0) ;

			currNode -> setLeft(remove(currNode -> getLeft(), MaxNode -> getData())) ;
        }
		else 
		{
			// both children exist
			Node *MaxNode = FindMax(currNode -> getLeft());  
			// find the maximum node in the left subtree
			currNode -> setData(MaxNode -> getData()) ; 
			// replace the current node's data with the maximum node's data
			currNode -> setCount(MaxNode -> getCount()) ;
			MaxNode -> setCount(1) ;
			// update the count of the maximum node
			currNode -> setLeft(remove(currNode -> getLeft(), MaxNode -> getData()));  
			// remove the maximum node from the left subtree
		}
        return currNode ;
	}
	return currNode;
}

// BSTree::FindMin() - find the minimum node in the tree
Node* BSTree::FindMin(Node* currNode) 
{
	Node* TransverseNode = currNode;

	// transverse the tree until the leftmost node is found
	while (TransverseNode && TransverseNode -> getLeft() != nullptr)
	{
		TransverseNode = TransverseNode -> getLeft();
	}
	return TransverseNode;
}

// BSTree::FindMax() - find the maximum node in the tree
Node* BSTree::FindMax(Node* currNode) 
{
	Node* TransverseNode = currNode;

	// transverse the tree until the rightmost node is found
    while (TransverseNode && TransverseNode -> getRight() != nullptr )
    {
        TransverseNode = TransverseNode -> getRight() ;
    }
    return TransverseNode ;
}

bool BSTree::search(const string &key) const
{
    //calls helper function
    return search(root, key) ;
}

//BSTree::search - returns bool if string is found in tree
bool BSTree::search(Node* currNode, const string &key) const
{
    if (currNode == nullptr)
    {
        return false ;
    }

    //if data is found
    if (currNode -> getData() == key)
    {
        return true ;
    }
    //recursively calls function to return bool, if true is found since it is an || it will return true
    return (search(currNode -> getLeft(), key) || search(currNode -> getRight(), key)) ; 
}

string BSTree::largest() const
{
    //node to iteratre through
    Node* currNode = root ;

    if(currNode == nullptr)
    {
        return "" ;
    }

    while (currNode -> getRight() != nullptr )
    {
        currNode = currNode -> getRight() ;
    }
    //returns bottom right value
    return currNode -> getData() ;
}

string BSTree::smallest() const
{
    //node to iterate through
    Node* currNode = root ;

    if(currNode == nullptr)
    {
        return "" ;
    }

    while (currNode -> getLeft() != nullptr )
    {
        currNode = currNode -> getLeft() ;
    }
    //returns botton left value
    return currNode -> getData() ;
}

//returns height from a string
int BSTree::height(const string& findString) 
{
    Node* currNode = root;

    while (currNode && currNode -> getData() != findString)
    {
        if (currNode -> getData() > findString)
        {
            currNode = currNode -> getLeft();
        }
        else
        {
            currNode = currNode -> getRight();
        }
    }

    //if currNode isn't nullptr it calls recursion, if it is it returns -1
    return currNode ? height(0, currNode) : -1;
}

//helper function
int BSTree::height(int Height, Node* currNode) const
{
    //when hits a node with no leaves
    if (!currNode -> getLeft() && !currNode -> getRight())
    {
        return Height ;
    }
    else
    {
       int leftHeight = 0 ;
       int rightHeight = 0 ;

       if (currNode -> getLeft())
       {
            //recursively calls to count height
           leftHeight = height(1 + Height, currNode -> getLeft()) ;
       }

       if (currNode -> getRight())
       {
           rightHeight = height(1 + Height, currNode -> getRight()) ;
       }
        //return the max of the values
       return max(leftHeight, rightHeight) ;
    }
}

void BSTree::preOrder() const
{
    preOrder(root) ; //calls helper function
}

void BSTree::postOrder() const
{
    postOrder(root) ; //calls helper function
}

void BSTree::inOrder() const
{
    inOrder(root) ; //calls helper function
}

//orders with recursion
void BSTree::preOrder(Node* currNode) const
{
    if (currNode) 
    {
        cout << currNode -> getData() << "(" << currNode -> getCount() << "), " ;
        preOrder(currNode -> getLeft()) ;
        preOrder(currNode -> getRight()) ;
    }
}

//orders with recursion
void BSTree::postOrder(Node* currNode) const
{
    if (currNode) 
    {
        postOrder(currNode -> getLeft()) ;
        postOrder(currNode -> getRight()) ;
        cout << currNode -> getData() << "(" << currNode -> getCount() << "), " ;
    }
}

//orders with recursion
void BSTree::inOrder(Node* currNode) const
{
    if (currNode) 
    {
        inOrder(currNode -> getLeft()) ;
        cout << currNode -> getData() << "(" << currNode -> getCount() << "), " ;
        inOrder(currNode -> getRight()) ;
    }
}