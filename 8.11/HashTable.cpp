#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (!myfile.eof()) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}

#include "HashTable.h"
#include "WordEntry.h"

/* HashTable constructor
*  input size is the size of the array
*  set size to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable(int size)
{
    // Store the input size as an instance variable of the HashTable object
    this -> size = size ;
    
    // Allocate memory for an array of linked lists, with size equal to the input size
    // Each linked list will store WordEntry objects with the same hash value
    hashTable = new list<WordEntry>[size] ;
}

/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to
*  ensure array index doesn't go out of bounds
*/
// Compute a hash value for the input string 'word'
int HashTable::computeHash(const string &word)
{
    int hash = 0 ;  // Initialize hash value to 0
    
    // Iterate through each character in the string and add its ASCII value to the hash
    for (char c : word) {
        hash += c ;
    }
    
    // Take the modulo of the hash value with the size of the hash table
    // This ensures that the hash value is within the range of indices for the hash table array
    return hash % size ;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearance with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
// Insert a new WordEntry object into the hash table with the given word and score
void HashTable::put(const string &word, int score)
{
    // Compute the hash value for the input word to determine its index in the hash table
    int index = computeHash(word) ;
    
    // Check if the word already exists in the hash table at the given index
    // If so, update its score instead of adding a new WordEntry object
    for (WordEntry &entry : hashTable[index]) {
        if (entry.getWord() == word) {
            entry.addNewAppearance(score) ;
            return ;
        }
    }
    
    // If the word does not already exist in the hash table, create a new WordEntry object
    // and add it to the linked list at the given index
    WordEntry newEntry(word, score) ;
    hashTable[index].push_back(newEntry) ;
}


/* getAverage
*  input: string word
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/
// Compute the average score for all WordEntry objects in the hash table with the given word
double HashTable::getAverage(const string &word)
{
    // Compute the hash value for the input word to determine its index in the hash table
    int index = computeHash(word) ;
    
    // Search for the WordEntry object with the given word in the linked list at the computed index
    for (WordEntry &entry : hashTable[index]) {
        if (entry.getWord() == word) {
            // If a matching WordEntry object is found, return its average score
            return entry.getAverage() ;
        }
    }
    
    // If no matching WordEntry object is found, return a default value of 2.0
    return 2.0 ;
}


/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
// Check if the hash table contains at least one WordEntry object with the given word
bool HashTable::contains(const string &word)
{
    // Compute the hash value for the input word to determine its index in the hash table
    int index = computeHash(word) ;
    
    // Search for the WordEntry object with the given word in the linked list at the computed index
    for (WordEntry &entry : hashTable[index]) {
        if (entry.getWord() == word) {
            // If a matching WordEntry object is found, return true
            return true ;
        }
    }
    
    // If no matching WordEntry object is found, return false
    return false ;
}

