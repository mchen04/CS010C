#include <iostream>
#include <fstream>
#include <algorithm>
#include "WordLadder.h"
#include <string>
#include <list>

using namespace std ;

WordLadder::WordLadder(const string &filename) {
    string word ; //
    ifstream inFS(filename) ;

    if (!inFS.is_open()) 
    {
        cout << "Error opening file " << filename << endl ;
        return ;
    }
    
    while (getline(inFS, word))
    {
        // Verify not empty string
        if (!word.empty())
        {
            // Check character count
            if (word.size() != 5)
            {
                // Word was not 5 letters
                cout << "Error: word " << word << " not 5 characters long" << endl;
                return;
            }

            dict.push_back(word);
        }
    }
}

void WordLadder::findLadder(const string &start, const string &end, list<string> &dict, stack<string> &wordLadder) {
    if (start == end) 
    {
        return;
    }

    queue<stack<string> > stack_queue;
    stack<string> string_stack;
    string_stack.push(start);
    stack_queue.push(string_stack);

    while (!stack_queue.empty()) 
    {
        stack<string> curr = stack_queue.front();
        stack_queue.pop();
        string currWord = curr.top();

        list<string>::iterator it;
        for (it = dict.begin(); it != dict.end(); it++) 
        {
            int differences = 0;
            for (int j = 0; j < 5; j++) 
            {
                if (currWord[j] != (*it)[j]) 
                {
                    differences++;
                }
            }
            if (differences == 1) 
            {
                stack<string> newStack = curr;
                newStack.push(*it);
                if (*it == end) 
                {
                    wordLadder = newStack;
                    return ;
                }
                stack_queue.push(newStack);
                it = dict.erase(it);
                it--;
            }
        }
    }
    wordLadder.push("");
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) 
{
    stack<string> wordLadder ;
    findLadder(start, end, dict, wordLadder) ;

    ofstream outFS(outputFile);
    if (!outFS.is_open()) 
    {
        cout << "Error opening file " << outputFile << endl ;
        return ;
    }

    if (start == end) 
    {
        wordLadder.push(start) ;
    }

    if (wordLadder.top() == "")
    {
        outFS << "No Word Ladder Found." << endl ;
        return;
    }

    stack<string> reverse = stack<string>();
    while (!wordLadder.empty())
    {
        reverse.push(wordLadder.top());
        wordLadder.pop();
    }

    while (!reverse.empty())
    {
        outFS << reverse.top() << endl ;
        reverse.pop() ;
    }

    outFS.close() ;
}
