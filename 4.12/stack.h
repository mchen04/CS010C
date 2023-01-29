#ifndef _STACK_H_
#define _STACK_H_

using namespace std ;

template<typename T>

class stack 
{
    private :
        static const int MAX_SIZE = 20 ;
        T data[MAX_SIZE] ;
        int size ;
    public :
        stack() 
        {
            size = 0 ;
        }

        void push(T val)
        {
            if (size == MAX_SIZE) 
            {
                throw overflow_error("Called push on full stack.") ;
            }

            data[size] = val ;
            size++ ;
        }

        void pop()
        {   
            if (empty()) 
            {
                throw out_of_range("Called pop on empty stack.") ;
            }  

            size-- ;
        }

        void pop_two ()
        {
            if (empty()) 
            {
                throw out_of_range("Called pop_two on empty stack.") ;
            }  

            if (size == 1) 
            {
                throw out_of_range("Called pop_two on a stack of size 1.") ;
            } 
            
            size -= 2 ;
        }

        T top () const
        {
            if (empty()) 
            {
                throw overflow_error("Called top on empty stack.") ;
            }     

            return data[size - 1] ;
        }

        bool empty () const
        {
            return size == 0 ;
        }
} ;

#endif