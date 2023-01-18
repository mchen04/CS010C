#include "IntList.h"

#include <iostream>

using std::cout ;
using std::endl ;

IntList() ;
~IntList() ;
void push_front(int) ;
void pop_front() ;
void push_back(int) ;
void pop_back() ;
bool empty() const ;
friend ostream & operator<<(ostream &, const IntList &) ;
void printReverse() const ;