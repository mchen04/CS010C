#include "IntList.h"

#include <iostream>

using std::cout ;
using std::endl ;

int main() {
    //creating new IntList object
    cout << "Creating new IntList." << endl ;
    IntList* list = new IntList() ;

    cout << "Printing empty list forward: " << *list << endl ;
    cout << "Printing empty list in reverse: " ;
    list -> printReverse() ;
    cout << endl << endl ;

    //checking is empty works on an empty list
    cout << "empty()" << endl ;
    if (list -> empty() == true )
    {
        cout << "This List is empty." ;
    }
    else 
    {
        cout << "This list isn't empty" ;
    }
    cout << endl << endl ;

    //testing push_front on empty list
    cout << "push_front(9)" << endl ;
    list -> push_front(9) ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ;
    cout << endl << endl ;

    //testing push_back on one node list
    cout << "push_back(10)" << endl ;
    list -> push_back(10) ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ; 
    cout << endl << endl ;

    //test push_front on multiple node list
    cout << "push_front(69)" << endl ;
    list -> push_front(69) ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ;
    cout << endl << endl ;

    //testing push_back on multiple node list
    cout << "push_back(54)" << endl ;
    list -> push_back(54) ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ; 
    cout << endl << endl ;

    //testing empty on non-empty list
    cout << "empty()" << endl ;
    if (list -> empty() == true )
    {
        cout << "This List is empty." ;
    }
    else 
    {
        cout << "This list isn't empty" ;
    }
    cout << endl << endl ;

    //testing pop_back
    cout << "pop_back()" << endl ;
    list -> pop_back() ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ;
    cout << endl << endl ;

    //testing pop_front
    cout << "pop_front()" << endl ; 
    list -> pop_front() ;
    cout << "Forward: " << *list << endl ;
    cout << "Reverse: " ;
    list -> printReverse() ;
    cout << endl << endl ;

    //testing destructor
    cout << "Destructor (deleting list)" << endl;
    delete list;

    cout << "Printing deleted pointer. Will Crash." << endl;
    cout << "Forward: " << *list << endl;
    return 0;
}