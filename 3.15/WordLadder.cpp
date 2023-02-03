#include <iostream>
#include <fstream>
#include <algorithm>
#include "WordLadder.h"

using namespace std ;

WordLadder::WordLadder(const string &filename) {
    string word ;
    ifstream inFS(filename) ;

    if (!inFS.is_open()) 
    {
        cout << "Error opening file " << filename << endl ;
    }
    else 
    {
        inFS >> word ;
        if (word.length() != 5) {
            cout << "Error: Word " << word << " is not 5 characters long." << endl ;
            return ;
        }
        dict.push_back(word) ;
    }
    inFS.close() ;
}

void WordLadder::findLadder(const string &start, const string &end, list<string> &dict, stack<string> &wordLadder) {
    if (start == end) 
    {
        return ;
    }

    queue<stack<string>> stack_queue ;
    stack<string> string_stack ;
    string_stack.push(start) ;
    stack_queue.push(string_stack) ;

    while (!stack_queue.empty()) 
    {
        stack<string> curr = stack_queue.front() ;
        stack_queue.pop() ;
        string currWord = curr.top() ;

        for (auto it = dict.begin(); it != dict.end(); ++it) 
        {
            int differences = 0;
            for (int i = 0; i < 5; ++i) 
            {
                if (currWord[i] != (*it)[i]) 
                {
                    differences++ ;
                }
            }
            if (differences == 1) 
            {
                stack<string> newStack = curr ;
                newStack.push(*it) ;
                if (*it == end) 
                {
                    wordLadder = newStack ;
                    return ;
                }
                stack_queue.push(newStack) ;
                it = dict.erase(it) ;
                it-- ;
            }
        }
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) 
{
    stack<string> wordLadder ;
    findLadder(start, end, dict, wordLadder) ;

    ofstream outFS(outputFile);
    if (!outFS.is_open()) 
    {
        cout << "Error opening file " << outputFile << endl ;
    }
    else 
    {
        while (!wordLadder.empty()) 
        {
            outFS << wordLadder.top() << endl ;
            wordLadder.pop() ;
        }
    }
    outFS.close() ;
}