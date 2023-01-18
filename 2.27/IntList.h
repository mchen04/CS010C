#ifndef _INTLIST_H_
#define _INTLIST_H_

#include <string>

using std::ostream ;

struct IntNode {
    int data ;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
} ;

class IntList {
    private:
        IntNode* dummyHead ;
        IntNode* dummyTail ;
    public:
        IntList() ;
        ~IntList() ;
        void push_front(int) ;
        void pop_front() ;
        void push_back(int) ;
        void pop_back() ;
        bool empty() const ;
        friend ostream & operator<<(ostream &, const IntList &) ;
        void printReverse() const ;
} ;

#endif