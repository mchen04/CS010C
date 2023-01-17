#include "Playlist.h"

#include <iostream>

using namespace std;


void PlaylistNode::InsertAfter(PlaylistNode* node)
{

}

void Playlist::changePos(int initialPos, int newPos)
{

}

void Playlist::RemoveSong(string ID) {
    PlaylistNode* temp = head ;
    while (temp != nullptr) {
        if (temp -> GetNext() -> GetID() == ID){
            PlaylistNode* DeleteNode = temp -> GetNext() ;

            cout << '"' << DeleteNode -> GetSongName() << '"' << " removed." << endl << endl ;

            temp -> SetNext(temp -> GetNext() -> GetNext()) ;

            delete DeleteNode ;
            DeleteNode -> SetNext(nullptr) ;
            
            return ;
        }
        temp = temp -> GetNext() ;
    }
    cout << "Song with unique ID " << ID << " not found!" << endl << endl ;
}

void Playlist::OutputFullPlaylist(string title) const
{
    int Counter = 1 ;

    cout << title << " - OUTPUT FULL PLAYLIST" << endl ;

    if (head == nullptr)
    {
        cout << "Playlist is empty" << endl << endl ;
        return ;
    }

    PlaylistNode* temp = head;
    while (temp != nullptr)
    {
        cout << Counter << "." << endl ;
        temp -> PrintPlaylistNode() ;
        cout << endl ;

        Counter++;
        temp  = temp -> GetNext() ;
    }
}

void Playlist::PrintSpecificArtist() const
{
    string artistName ;
    int Counter = 1 ;

    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << "\n" ;
    cout << "Enter artist's name:" << endl ; 
    getline(cin, artistName) ;
    cout << endl;

    PlaylistNode* temp = head ;
    while (head != nullptr)
    {
        if (temp -> GetArtistName() == artistName)
        {
            cout << Counter << "." << endl ;
            temp -> PrintPlaylistNode() ;
            cout << endl ; 
        }

        Counter++;
        temp = temp -> GetNext() ;
    }
}

int Playlist::TotalTime() const
{
    int TotalTime = 0 ;
    PlaylistNode* temp = head ;
    
    while (temp != nullptr) {
        TotalTime += temp -> GetSongLength() ;
        temp = temp -> GetNext() ;
    }

    return TotalTime ;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength)
{
    this -> uniqueID = uniqueID ;
    this -> songName = songName ;
    this -> artistName = artistName ;
    this -> songLength = songLength ;
    nextNodePtr = nullptr ;
}

Playlist::Playlist() : head(nullptr), tail(nullptr){}

void Playlist::push_back(PlaylistNode* NewNode)
{
    if (head == nullptr) {
        head = tail = NewNode ;
        return ;
    }

    tail -> SetNext(NewNode) ;
    NewNode = tail ;
}

void PlaylistNode::PrintPlaylistNode() const
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