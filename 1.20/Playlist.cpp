#include "Playlist.h"

#include <iostream>

using namespace std;


void PlaylistNode::InsertAfter(PlaylistNode* Node)
{
    PlaylistNode* temp = nextNodePtr ; //sets a pointer to the next node
    nextNodePtr = Node ; //sets next node to parameter node
    Node -> SetNext(temp) ; //uses Setter to set the next node to node where temp is pointing to
}

void Playlist::ChangePosition(int initialPos, int newPos)
{
    //intializing variables and pointers
    int StartingIndex = 1 ;
    PlaylistNode* prevNode = nullptr ;
    PlaylistNode* currNode = head ;

    if (initialPos < 1) //checks boundaries case of Position being too low
    {
        cout << "Invalid current position." << endl ;
        return ; //exits
    }

    while (StartingIndex < initialPos) //iterating through while assigning previous and current nodes while counting position
    {
        if (currNode != nullptr)
        {
            prevNode = currNode ; //assigns previous node to current
            currNode = currNode -> GetNext() ; //current goes to next
            StartingIndex++ ; //increment of one
        }
    }

    if (prevNode != nullptr) //if current isn't head
    {
        prevNode -> SetNext(currNode -> GetNext()) ; //skips over current node, skipping over current
    }

    else //if current is head
    {
        head = currNode -> GetNext() ; //assigns head to next
    } 

    if (currNode == tail) //checking if current is tail
    {
        tail = prevNode ; //setting previus node to the tail
    }

    if (newPos <= 1) //checks if user wants to move below 1 (will assign to head)
    {
        if (head == nullptr) //checks empty list
        {
            tail = currNode ; // sets tailt to current node
        }

        currNode -> SetNext(head) ; //puts current in front of head by setting next to head
        head = currNode ; //reassigns head
        cout << '"' << currNode -> GetSongName() << '"' << " moved to position 1" << endl ;
    }
    else 
    {
        if (head == nullptr) //checks empty list
        {
            push_back(currNode) ; //calls push_back to add Node to list
            cout << '"' << currNode -> GetSongName() << '"' << " moved to position 1" << endl ;
        }
        else
        {
            int newPositionIndex = 2 ; //starts index from 2 since checked 1 already
            PlaylistNode* previousNode = head ;
            PlaylistNode* afterNode = head -> GetNext() ;

            while (newPositionIndex < newPos && afterNode != nullptr) //iterating through
            {
                //reassigns previous, current and adds increments fo 1 to position index
                previousNode = afterNode ;
                afterNode = afterNode -> GetNext() ;
                newPositionIndex++ ;
            }

            previousNode -> InsertAfter(currNode) ; //inserts current after previous

            if (afterNode == nullptr)  //checks if afterNode is last node
            {
                tail = currNode ; //reassigns tail
            }
            cout << '"' << currNode -> GetSongName() << '"' << " moved to position " << newPositionIndex << endl ;
        }
    }
}

void Playlist::RemoveSong(string ID) {
    PlaylistNode* temp = head ;//intiaizalize pointer 

    while (temp != nullptr) {
        if (temp -> GetNext() -> GetID() == ID){ //uses next in order to delete and connect previous to enxt
            PlaylistNode* DeleteNode = temp -> GetNext() ; //pointer to node we want to delete

            cout << '"' << DeleteNode -> GetSongName() << '"' << " removed." << endl << endl ;

            temp -> SetNext(temp -> GetNext() -> GetNext()) ; //sets previous next to current next to "skip" over current

            delete DeleteNode ; //deletes wanted node
            DeleteNode -> SetNext(nullptr) ; //gets rid of dangling pointer
            
            return ;
        }
        temp = temp -> GetNext() ; //goes through list
    }
    cout << "Song with unique ID " << ID << " not found!" << endl << endl ;
}

void Playlist::OutputFullPlaylist(string title) const
{
    int Counter = 1 ; //intialize position counter variable

    cout << title << " - OUTPUT FULL PLAYLIST" << endl ;

    if (head == nullptr) //checks for empty list
    {
        cout << "Playlist is empty" << endl << endl ;
        return ;
    }

    PlaylistNode* temp = head ; //creates pointer to head to traverse list

    while (temp != nullptr)
    {
        cout << Counter << "." << endl ;
        temp -> PrintPlaylistNode() ; //calls print function
        cout << endl ;

        Counter++ ; //increases position count
        temp  = temp -> GetNext() ; //used to traverse list
    }
}

void Playlist::push_back(PlaylistNode* NewNode)
{
    NewNode -> SetNext(nullptr) ; //gets rid of dangling pointer

    if (head == nullptr)  //checks for empty list
    {
        head = tail = NewNode ; //sets head and tail to node
        return ;
    }

    tail -> SetNext(NewNode) ; //adds Node to tail
    tail = NewNode ; //reassigns tail
}

void Playlist::PrintSpecificArtist(string artistName) const
{
    int Counter = 1 ; //initalize position counter variable

    PlaylistNode* temp = head ; //creates pointer to head

    while (temp != nullptr)
    {
        if (temp -> GetArtistName() == artistName) //checks if names are the same
        {
            cout << Counter << "." << endl ;
            temp -> PrintPlaylistNode() ; //calls print function
            cout << endl ; 
        }

        Counter++; //increments countera variable
        temp = temp -> GetNext() ; //used to traverse list
    }
}

int Playlist::TotalTime() const
{
    int TotalTime = 0 ; //initialize total to 0
    PlaylistNode* temp = head ; //pointer to head
    
    while (temp != nullptr) {
        TotalTime += temp -> GetSongLength() ; //adds time of node to total time
        temp = temp -> GetNext() ; //traverse list
    }

    return TotalTime ; //returns int of total time
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength) //constructor
{
    this -> uniqueID = uniqueID ;
    this -> songName = songName ;
    this -> artistName = artistName ;
    this -> songLength = songLength ;
    nextNodePtr = nullptr ;
}

Playlist::Playlist() : head(nullptr), tail(nullptr){}

void PlaylistNode::PrintPlaylistNode() const //prints information of a node in a certain format
{
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

void PlaylistNode::SetNext(PlaylistNode* PlaylistNode)
{
    nextNodePtr = PlaylistNode ;
}

string PlaylistNode::GetID() const
{
    return uniqueID ;
}

string PlaylistNode::GetSongName() const
{
    return songName ;
}

string PlaylistNode::GetArtistName() const
{
    return artistName ;
}

int PlaylistNode::GetSongLength() const
{
    return songLength ;
}

PlaylistNode* PlaylistNode::GetNext() const
{
    return nextNodePtr ;
}