#include "WordLadder.h"

#include <fstream>
#include <iostream>
#include <queue>

using namespace std ;

    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file. 
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */
WordLadder::WordLadder(const string &filename) {
    string words ;

    ifstream inFS(filename);

    if (!inFS.is_open())
    {
        cout << "Error opening file " << filename << endl ;
        return ;
    }

    while (inFS >> words) 
    {
        if (words.length() != 5)
        {
            cout << "Word does not have 5 characters" << endl ;
            return ;
        }
        dict.push_back(words) ;
    }

    return ;
}

    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
void outputLadder(const string &start, const string &end, const string &outputFile) 
{
    stack<string> string_stack = stack<string> () ;
    string_stack.push(start) ;

    queue<stack> queue_stack = queue<stack> () ;
    queue_stack.push(string_stack) ;
}