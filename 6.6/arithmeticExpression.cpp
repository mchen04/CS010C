#include "arithmeticExpression.h"

#include <fstream>
#include <sstream>
#include <stack>

using namespace std ;

// constructor that initializes the infixExpression and root data members
arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr) {}

/* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */


// converts the infixExpression to its equivalent postfix string
// and then generates the tree and assigns the root node to the root data field
// the key for the first node is 'a', 'b' for the second node and so on.
void arithmeticExpression::buildTree()
{
    string postFix = infix_to_postfix(); // convert infix expression to postfix
    char key = 'a';                      // key for the first node

    root = buildNode(postFix, key); // generate the tree recursively
}

// generates a node of the expression tree
// takes a string reference and a char reference as arguments
// the string reference is the postfix expression
// the char reference is the key for the node
TreeNode* arithmeticExpression::buildNode(string& expression, char& key)
{
    if (!expression.empty()) // check if the postfix expression is not empty
    {
        TreeNode* newNode = new TreeNode(expression.back(), key); // create a new node with data as the last character in the postfix expression
        key++;                                                    // increment the key for the next node
        expression.pop_back();                                    // remove the last character from the postfix expression

        if (priority(newNode->data) > 0) // if the node is an operator
        {
            newNode->right = buildNode(expression, key); // recursively generate the right subtree
            newNode->left = buildNode(expression, key);  // recursively generate the left subtree
        }
        return newNode; // return the node
    }
    return nullptr; // return null pointer if the postfix expression is empty
}


int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
/*
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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
*/

void arithmeticExpression::infix()
{
    infix(root); // call the private infix function with the root node
}

void arithmeticExpression::prefix()
{
    prefix(root); // call the private prefix function with the root node
}

void arithmeticExpression::postfix()
{
    postfix(root); // call the private postfix function with the root node
}

void arithmeticExpression::infix(TreeNode *currNode)
{
    if (currNode != nullptr) // base case: if the node is not null
    {
        if (currNode -> left != nullptr) // if the current node has a left child, add an opening parenthesis
        {
            cout << "(" ;
        }

        infix(currNode -> left) ; // recursively traverse the left subtree

        cout << currNode -> data ; // print the current node's data

        infix(currNode -> right) ; // recursively traverse the right subtree

        if (currNode -> left != nullptr) // if the current node has a left child, add a closing parenthesis
        {
            cout << ")" ;
        }
    }
}

void arithmeticExpression::prefix(TreeNode *currNode)
{
    if (currNode != nullptr) // base case: if the node is not null
    {
        cout << currNode -> data ; // print the current node's data

        prefix(currNode -> left) ; // recursively traverse the left subtree

        prefix(currNode -> right) ; // recursively traverse the right subtree
    }
}

void arithmeticExpression::postfix(TreeNode *currNode)
{
    if (currNode != nullptr) // base case: if the node is not null
    {
        postfix(currNode -> left) ; // recursively traverse the left subtree

        postfix(currNode -> right) ; // recursively traverse the right subtree

        cout << currNode -> data ; // print the current node's data
    }
}
