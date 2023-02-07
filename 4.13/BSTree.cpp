#include "BSTree.h"
#include <iostream>

using namespace std ;

BSTree::BSTree()
{
    root = nullptr ;
}


BSTree::~BSTree()
{
    delete root ;
}

/* Mutators */
/* Insert an item into the binary search tree. 
Be sure to keep BST properties. 
When an item is first inserted into the tree the count should be set to 1. 
When adding a duplicate string (case sensitive), rather than adding another node, 
the count variable should be incremented 
*/
void BSTree::insert(const string &newString)
{
    Node* parent = nullptr ;
    Node* curr = root ;
    bool isLeft = true ;

    while (curr != nullptr && !(newString == curr -> getData()))
    {
        parent = curr ;
        if (curr -> getData() > newString)
        {
            curr = curr -> getLeft() ;
            isLeft = true ;
        }
        else
        {
            curr = curr -> getRight() ; 
            isLeft = false ;
        }
    }

    if (curr != nullptr) 
    {
        curr -> setCount(curr -> getCount() + 1) ;
    }
    else 
    {
        Node* addNode = new Node(newString) ;

        if (parent != nullptr) 
        {
            if (isLeft)
            {
                parent -> setLeft(addNode) ;
            }
            else
            {
                parent -> setRight(addNode) ;
            }
        }
        else 
        {
            root = addNode;
        }
    }
}



/* Remove a specified string from the tree. 
Be sure to maintain all bianry search tree properties. 
If removing a node with a count greater than 1, just decrement the count, otherwise, 
if the count is simply 1, remove the node. 
You MUST follow the remove algorithm shown in the slides and discussed in class or else 
your program will not pass the test functions. 
When removing, 
if removing a leaf node, simply remove the leaf. Otherwise, 
if the node to remove has a left child, replace the node to remove with the largest 
string value that is smaller than the current string to remove 
(i.e. find the largest value in the left subtree of the node to remove). 
If the node has no left child, replace the node to remove with the smallest value 
larger than the current string to remove 
(i.e. find the smallest value in the right subtree of the node to remove. 
*/
void BSTree::remove(const string &key)
{
    if (!search(key))
    {
        return ;
    }
    if(root -> getLeft() == nullptr && root -> getRight() == nullptr) {
        delete root ;
        root = NULL ;
        return ;
    }
    remove(root, key) ;
}

Node* BSTree::remove(Node* temp, const string &key)
{
    if (temp == nullptr)
    {
        return nullptr ;
    }
	if (key < temp -> getData()) { 
	    temp -> setLeft(remove(temp -> getLeft(), key)) ;
	}
	else if (key > temp -> getData()) {  
		temp -> setRight(remove(temp -> getRight(), key)) ;
	}
	else 
    {
		if (temp -> getCount() > 1) {
			temp -> setCount(temp -> getCount() - 1);
            return temp ;
		}
		else if (temp -> getLeft() == nullptr && temp -> getRight() == nullptr) {
			delete temp ;
			return nullptr ;
		}
		else if (temp -> getLeft() == nullptr) {
			Node *curr = FindMin(temp -> getRight()) ;
			temp -> setData(curr -> getData()) ;
			temp -> setCount(curr -> getCount()) ;
			curr -> setCount(0) ;

			temp -> setRight(remove(temp -> getRight(), curr -> getData())) ;
			return temp ;
		}
		else if (temp -> getRight() == nullptr) {
			Node *curr = FindMax(temp -> getLeft()) ;
			temp -> setData(curr -> getData()) ;
			temp -> setCount(curr -> getCount()) ;
			temp-> setCount(0) ;

			temp -> setLeft(remove(temp -> getLeft(), curr -> getData())) ;
			return temp ;
		}
		else {
			Node *curr2 = FindMax(temp -> getLeft()) ;
			temp -> setData(curr2 -> getData()) ;
			temp -> setCount(curr2 -> getCount()) ;
			curr2 -> setCount(1) ;
			temp -> setLeft(remove(temp -> getLeft(), curr2 ->getData())) ;
            return temp ;
		}
	}
	return temp;
}

Node* BSTree::FindMin(Node* temp) 
{
    Node* curr = temp ;

    while (curr && curr -> getLeft() != nullptr )
    {
        curr = curr -> getLeft() ;
    }
    return curr ;
}

Node* BSTree::FindMax(Node* temp) 
{
    Node* curr = temp ;

    while (curr && curr -> getRight() != nullptr )
    {
        curr = curr -> getRight() ;
    }
    return curr ;
}

/* Accessors */
/* Search for a string in the binary search tree. 
It should return true if the string is in the tree, and false otherwise. 
*/
bool BSTree::search(const string &key) const
{
    return search(root, key) ;
}

bool BSTree::search(Node* node, const string &key) const
{
    if (node == nullptr)
    {
        return false ;
    }

    if (node -> getData() == key)
    {
        return true ;
    }

    return (search(node -> getLeft(), key) || search(node -> getRight(), key)) ;
}

/* Find and return the largest value in the tree. Return an empty string if the tree is empty */
string BSTree::largest() const
{
    Node* curr = root ;

    if(curr == nullptr)
    {
        return "" ;
    }

    while (curr -> getRight() != nullptr )
    {
        curr = curr -> getRight() ;
    }
    return curr -> getData() ;
}

/* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
string BSTree::smallest() const
{
    Node* curr = root ;

    if(curr == nullptr)
    {
        return "" ;
    }

    while (curr -> getLeft() != nullptr )
    {
        curr = curr -> getLeft() ;
    }
    return curr -> getData() ;
}

/* Compute and return the height of a particular string in the tree. 
The height of a leaf node is 0 (count the number of edges on the longest path). 
Return -1 if the string does not exist. 
*/
int BSTree::height(const string& findString) 
{
    Node* temp = root;

    while (temp && temp -> getData() != findString)
    {
        if (temp -> getData() > findString)
        {
            temp = temp -> getLeft();
        }
        else
        {
            temp = temp -> getRight();
        }
    }

    return temp ? height(0, temp) : -1;
}

int BSTree::height(int Height, Node* temp) const
{
    if (!temp -> getLeft() && !temp -> getRight())
    {
        return Height ;
    }
    else
    {
       int left = 0 ;
       int right = 0 ;

       if (temp -> getLeft())
       {
           left = height(1 + Height, temp -> getLeft()) ;
       }

       if (temp -> getRight())
       {
           right = height(1 + Height, temp -> getRight()) ;
       }

       return max(left, right) ;
    }
}


/* Printing */
/* For all printing orders, each node should be displayed as follows:
<string> (<count>)
e.g. goodbye(1), Hello World(3)
*/
void BSTree::preOrder() const
{
    preOrder(root) ;
}

void BSTree::postOrder() const
{
    postOrder(root) ;
}

void BSTree::inOrder() const
{
    inOrder(root) ;
}

void BSTree::preOrder(Node* node) const
{
    if (node) 
    {
        cout << node -> getData() << "(" << node -> getCount() << "), " ;
        preOrder(node -> getLeft()) ;
        preOrder(node -> getRight()) ;
    }
}

void BSTree::postOrder(Node* node) const
{
    if (node) 
    {
        postOrder(node -> getLeft()) ;
        postOrder(node -> getRight()) ;
        cout << node -> getData() << "(" << node -> getCount() << "), " ;
    }
}

void BSTree::inOrder(Node* node) const
{
    if (node) 
    {
        inOrder(node -> getLeft()) ;
        cout << node -> getData() << "(" << node -> getCount() << "), " ;
        inOrder(node -> getRight()) ;
    }
}