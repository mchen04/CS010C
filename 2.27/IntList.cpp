#include "IntList.h"

#include <iostream>

using namespace std ;

IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0)) //initialization list
{
    //sets next and prev for dummy head and tail
    dummyHead -> next = dummyTail ; 
    dummyTail -> prev = dummyHead ;
}

IntList::~IntList() //destructor
{
    IntNode* temp = dummyHead ; 
    while (temp != dummyTail) //while loop to iterate through list
    {
        IntNode* DeleteNode = temp ; //assigns to current node
        temp = temp -> next ; //moes to next node

        delete DeleteNode ; //deletes node
    }
    delete temp ; //deletes last one
}

void IntList::push_front(int NodeValue) //push_front   
{
    IntNode* AddNode = new IntNode(NodeValue) ; //creates a new node
    IntNode* temp = dummyHead -> next ; //first node
    //shifts around next and prev to accomodate to new node
    dummyHead -> next = AddNode ; 
    AddNode -> prev = dummyHead ;   
    AddNode -> next = temp ; 
    temp -> prev = AddNode ;
}

void IntList::pop_front() //pop_front
{
    IntNode* DeleteNode = dummyHead -> next ; //assigns first node to pointer
    // shifts around next and prev to ignore first node
    IntNode* temp = dummyHead -> next -> next ;
    dummyHead -> next = dummyHead -> next -> next ;
    temp -> prev = dummyHead ;
    delete DeleteNode ; //deletes first node
    DeleteNode -> next = nullptr ; //get rid of dangling pointer
}

void IntList::push_back(int NodeValue) //push_back
{
    IntNode* AddNode = new IntNode(NodeValue) ; //creates new node
    //shifts around prev and next to add a file before dummyTail
    IntNode* temp = dummyTail -> prev ;
    AddNode -> next = dummyTail ;
    AddNode -> prev = temp ;
    dummyTail -> prev = AddNode ;
    temp -> next = AddNode ;
}

void IntList::pop_back() //pop_back
{
    IntNode* DeleteNode = dummyTail -> prev ; //create node to delete later
    IntNode* temp = dummyTail -> prev -> prev ; //
    delete DeleteNode ; //deletes node
    //shifts prev and neck to get exclude last node
    temp -> next = dummyTail ;
    dummyTail -> prev = temp ;
    DeleteNode -> next = nullptr ; //get rid of dangling pointer
}

bool IntList::empty() const //empty
{
    return (dummyHead -> next == dummyTail) ; //checks if there are no nodes between dummy tail and head
}

ostream & operator<<(ostream& out, const IntList& rhs) { //ostream
    if (!rhs.empty()) { //checks if empty
        if (rhs.dummyHead -> next -> next == rhs.dummyTail) //bordr case for one node in list
        {
            out << rhs.dummyHead -> next -> data ; //returns data at the one node
        }

        else 
        {
            IntNode* temp = rhs.dummyHead -> next ;
            while (temp != rhs.dummyTail) //while loop to iterate through list
            {
                out << temp -> data ; //ostream data
                if (temp -> next != rhs.dummyTail ) //ostream a space if not at the end
                {
                    out << " " ;
                }
                temp = temp -> next ;
            }
        }
    }

    return out ;
}

void IntList::printReverse() const //printing reverse
{
    if (!empty()) //checks if empty
    {
        if (dummyHead -> next -> next == dummyTail) //checks for one nose
        {
            cout << dummyHead -> next -> data ; //returns one node data
            return ;
        }
        else 
        {
            IntNode* temp = dummyTail -> prev ;
            while (temp != dummyHead) //while loop to iterate backwards though list
            {
                cout << temp -> data ; //outputs data
                if (temp -> prev != dummyHead ) //checks if not at front
                {
                    cout << " " ; //outputs space
                }
                temp = temp -> prev ; //prev instead of next to go backwards
            }
        }
    }
}