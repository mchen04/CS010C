#ifndef _STACK_H_
#define _STACK_H_

// Adding guard statement to prevent multiple inclusion of the header file.

using namespace std ;

template<typename T>

// Template class to create stack of any data type.

class stack 
{
    private :
        static const int MAX_SIZE = 20 ;
        // Maximum size of stack is set to 20.
        T data[MAX_SIZE] ;
        // Array to store elements of the stack.
        int size ;
        // Size of the stack.
    public :
        stack() 
        {
            size = 0 ;
            // Initializing size to 0.
        }

        void push(T val)
        {
            if (size == MAX_SIZE) 
            {
                throw overflow_error("Called push on full stack.") ;
                // Throws an overflow_error if stack is already full.
            }

            data[size] = val ;
            size++ ;
            // Pushes element onto the stack.
        }

        void pop()
        {   
            if (empty()) 
            {
                throw out_of_range("Called pop on empty stack.") ;
                // Throws an out_of_range error if stack is empty.
            }  

            size-- ;
            // Pops element from the stack through reducing size by 1
        }

        void pop_two ()
        {
            if (empty()) 
            {
                throw out_of_range("Called pop_two on empty stack.") ;
                // Throws an out_of_range error if stack is empty.
            }  

            if (size == 1) 
            {
                throw out_of_range("Called pop_two on a stack of size 1.") ;
                // Throws an out_of_range error if stack has only one element.
            } 
            
            size -= 2 ;
            // Pops two elements from the stack through reducing size by 2
        }

        T top () const
        {
            if (empty()) 
            {
                throw overflow_error("Called top on empty stack.") ;
                // Throws an overflow_error if stack is empty.
            }     

            return data[size - 1] ;
            // Returns top element of the stack using index and size
        }

        bool empty () const
        {
            return size == 0 ;
            // Returns true if stack is empty, false otherwise.
        }
} ;

#endif
