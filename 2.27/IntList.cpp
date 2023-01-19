#include "IntList.h"

#include <iostream>

using namespace std ;

IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0))
{
    dummyHead -> next = dummyTail ;
    dummyTail -> prev = dummyHead ;
}

IntList::~IntList() 
{
    IntNode* temp = dummyHead ;
    while (temp != dummyTail) 
    {
        IntNode* DeleteNode = temp ;
        temp = temp -> next ;

        delete DeleteNode ;
    }
    delete temp ;
}

void IntList::push_front(int NodeValue)  
{
    IntNode* AddNode = new IntNode(NodeValue) ;
    IntNode* temp = dummyHead -> next ;

    dummyHead -> next = AddNode ;
    AddNode -> prev = dummyHead ;
    AddNode -> next = temp ;
    temp -> prev = AddNode ;
}

void IntList::pop_front() 
{
    IntNode* DeleteNode = dummyHead -> next ;
    IntNode* temp = dummyHead -> next -> next ;
    dummyHead -> next = dummyHead -> next -> next ;
    temp -> prev = dummyHead ;
    delete DeleteNode ;
}

void IntList::push_back(int NodeValue) 
{
    IntNode* AddNode = new IntNode(NodeValue) ;
    IntNode* temp = dummyTail -> prev ;
    AddNode -> next = dummyTail ;
    AddNode -> prev = temp ;
    dummyTail -> prev = AddNode ;
    temp -> next = AddNode ;
}

void IntList::pop_back() 
{
    IntNode* DeleteNode = dummyTail -> prev ;
    IntNode* temp = dummyTail -> prev -> prev ;
    delete DeleteNode ;
    temp -> next = dummyTail ;
    dummyTail -> prev = temp ;
}

bool IntList::empty() const 
{
    return (dummyHead -> next == dummyTail) ;
}

ostream & operator<<(ostream& out, const IntList& rhs) {
    if (!rhs.empty()) {
        if (rhs.dummyHead -> next -> next == rhs.dummyTail)
        {
            out << rhs.dummyHead -> next -> data ;
        }

        else 
        {
            IntNode* temp = rhs.dummyHead -> next ;
            while (temp != rhs.dummyTail)
            {
                out << temp -> data ;
                if (temp -> next != rhs.dummyTail ) 
                {
                    out << " " ;
                }
                temp = temp -> next ;
            }
        }
    }

    return out ;
}

void IntList::printReverse() const 
{
    if (empty()) 
    {
        return ;
    }

    else if (dummyHead -> next -> next == dummyTail)
    {
        cout << dummyHead -> next -> data ;
        return ;
    }
    else 
    {
        IntNode* temp = dummyTail -> prev ;
        while (temp != dummyHead)
        {
            cout << temp -> data ;
            if (temp -> prev != dummyHead ) 
            {
                cout << " " ;
            }
            temp = temp -> prev ;
        }
    }
}