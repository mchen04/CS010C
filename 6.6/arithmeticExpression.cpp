#include "arithmeticExpression.h"

#include <fstream>
#include <sstream>
#include <stack>

using namespace std ;

arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr) {}

/* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */


void arithmeticExpression::buildTree()
{
    string postFix = infix_to_postfix() ;

    char key = 'a' ;

    root = buildNode(postFix, key) ;
}

TreeNode* arithmeticExpression::buildNode(string &expression, char &key)
{
    if (!expression.empty())
    {
        TreeNode* NewNode = new TreeNode(expression.at(expression.size() - 1), key) ;
        key++ ;
        expression.pop_back() ;

        if (priority(NewNode -> data) > 0)
        {
            NewNode -> right = buildNode(expression, key) ;
            NewNode -> left = buildNode(expression, key) ;
        }
        return NewNode ;
    }
    return nullptr ;
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
    infix(root);
}

void arithmeticExpression::prefix()
{
    prefix(root);
}

void arithmeticExpression::postfix()
{
    postfix(root);
}

void arithmeticExpression::infix(TreeNode *currNode)
{
    if (currNode != nullptr)
    {
        if (currNode -> left != nullptr)
        {
            cout << "(" ;
        }

        infix(currNode -> left) ;
        cout << currNode -> data ;
        infix(currNode -> right) ;

        if (currNode -> left != nullptr)
        {
            cout << ")" ;
        }
    }
}

void arithmeticExpression::prefix(TreeNode *currNode)
{
    if (currNode != nullptr)
    {
        cout << currNode -> data ;
        prefix(currNode -> left) ;
        prefix(currNode -> right) ;
    }
}

void arithmeticExpression::postfix(TreeNode *currNode)
{
    if (currNode != nullptr)
    {
        postfix(currNode -> left) ;
        postfix(currNode -> right) ;
        cout << currNode -> data ;
    }
}