#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std ;

//function templates and prototypes
template<typename T> 
unsigned min_index(const vector<T> &vals, unsigned index) ;
template<typename T>
void selection_sort(vector<T> &vals) ;
template<typename T>
T getElement(vector<T> vals, int index) ;
template<typename T>
void print_vector(vector<T> &vals) ;

vector<char> createVector(){ //given function
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main(){
    vector<int>* intVector = new vector<int>();
    intVector->push_back(32);
    intVector->push_back(38);
    intVector->push_back(3);
    intVector->push_back(100);
    intVector->push_back(42231);

    selection_sort(*intVector);
    print_vector(*intVector);

    vector<char>* charVector = new vector<char>();
    charVector->push_back('h');
    charVector->push_back('e');
    charVector->push_back('4');
    charVector->push_back('*');
    charVector->push_back('P');

    selection_sort(*charVector);
    print_vector(*charVector);

    vector<string>* stringVector = new vector<string>();
    stringVector->push_back("michael");
    stringVector->push_back("alex");
    stringVector->push_back("megan");
    stringVector->push_back("mark");
    stringVector->push_back("emily");

    selection_sort(*stringVector);
    print_vector(*stringVector);


    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}

template<typename T> //function template
unsigned min_index(const vector<T> &vals, unsigned index) { //function to find index of smallest value
    unsigned min_index = index ; //variable to hold current lowest index
    for (unsigned i = index; i < vals.size(); i++) //for loop, goes through entire vector
    {
        if (vals[i] < vals[min_index]) //compares values at current minimum index 
        {
            min_index = i ; //reassigns index
        }
    }
    return min_index ; //returns index
}

template<typename T> //function template
void selection_sort(vector<T> &vals)  //function to selection sort a vector
{
    //for loop, iterates until one less than size of vector due to always comparing to at least the next value
    for (unsigned i = 0; i + 1 < vals.size(); i++) 
    {
        unsigned minIndex = min_index(vals, i ) ; //finds the lowest index after our current i (replaces extra for loop)
        swap(vals[i], vals[minIndex]) ; //swaps values at those indices
    }
}

template<typename T> //function template
T getElement(vector<T> vals, int index) { //function to get value at an index in vector
    try { //error handling constructs
        unsigned compare_index = index ; //intializes variable to index -> avoids warning error
        if (index < 0 || compare_index >= vals.size()) { //checks for out of points
            throw runtime_error("std::outofrange") ; //calls runtime error 
        }         
        return vals[index] ; //return value
    }
    catch (runtime_error& excpt) { //handles the exception
        cout << "out of range exception occured" << endl;
    }
    throw runtime_error("enum_to_int: this can never happen") ; //throw to stop errors
}

template<typename T> //function template
void print_vector(vector<T> &vals) //fucntion to print values in a vector
{
    for (unsigned i = 0; i < vals.size(); ++i) 
    {
        cout << vals.at(i) << " ";
    }
    cout << endl;
}