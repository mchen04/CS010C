#include "arithmeticExpression.h"

#include <fstream>
#include <sstream>
#include <stack>

using namespace std ;

arithmeticExpression::arithmeticExpression(const string &expression) : infixExpression(expression), root(nullptr) {}

/* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */

/*
void arithmeticExpression::buildTree()
{

}

TreeNode* arithmeticExpression::buildNode(string &eq, char &key)
{

}
*/

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

void arithmeticExpression::infix(TreeNode *node)
{
    if (node != nullptr)
    {
        infix(node->left);
        cout << node->data;
        infix(node->right);
    }
}

void arithmeticExpression::prefix(TreeNode *node)
{
    if (node != nullptr)
    {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix(TreeNode *node)
{
    if (node != nullptr)
    {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}