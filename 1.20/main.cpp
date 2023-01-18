#include "Playlist.h"

#include <iostream>

using namespace std ; 

Playlist* playlist ; //initializing a playlist object

void PrintMenu(string); //constructor to call later

int main() {
    string user_title ; 
    cout << "Enter playlist's title:" << endl ;
    getline(cin, user_title) ; //getline to take in user inpit
    cout << endl ;

    playlist = new Playlist() ; //allocating memory for new playlist object
    PrintMenu(user_title) ; //calls menu function
}

void PrintMenu(string title)
{
    //outputs default menu with choices
    cout << title << " PLAYLIST MENU" << "\n" ;
    cout << "a - Add song" << "\n" ;
    cout << "d - Remove song" << "\n" ;
    cout << "c - Change position of song" << "\n" ; 
    cout << "s - Output songs by specific artist" << "\n" ;
    cout << "t - Output total time of playlist (in seconds)" << "\n" ;
    cout << "o - Output full playlist" << "\n" ;
    cout << "q - Quit" << "\n" ;
    cout << "\n" ;
    cout << "Choose an option:" ;
    cout << "\n" ;

    //initalizing variable and taking input
    string user_choice ;
    getline(cin, user_choice) ;

    if (user_choice == "q") // Quit      
    {
        return ; //exits function
    }

    else if (user_choice == "a") // Add song   
    {
        //intializing variables 
        cout << "ADD SONG" << "\n";
        string id, name, artist ;
        int length ;

        //storing input in variables for parameters of new PlaylistNode
        cout << "Enter song's unique ID:" << endl ;
        getline(cin, id);
        cout << "Enter song's name:" << endl ;
        getline(cin, name);
        cout << "Enter artist's name:" << endl ;
        getline(cin, artist);
        cout << "Enter song's length (in seconds):" << endl ;
        cin >> length ;
        cin.ignore() ; //cleans out the input buffer 

        PlaylistNode* addNode = new PlaylistNode(id, name, artist, length) ; //creates a new PlaylistNode with 4 parameter constructor
        playlist -> push_back(addNode) ; //calls push_back function

        cout << endl ;
        PrintMenu(title) ; //calls PrintMenu function to bring up choices and allow for 
    }

    else if (user_choice == "d") // Remove song       
    {
        cout << "REMOVE SONG" << "\n" ;
        cout << "Enter song's unique ID:" << "\n" ;

        //intialize variable and take input
        string ID ; 
        getline(cin, ID) ;

        //calls RemoveSong function with String ID (stored input) as parameter
        playlist -> RemoveSong(ID) ;
        PrintMenu(title) ; 
    }

    else if (user_choice == "c") // Change position of song
    {
        int initialPosition, newPosition ; //intializing variables

        cout << "CHANGE POSITION OF SONG" << "\n" ;
        cout << "Enter song's current position:" << endl ;
        cin >> initialPosition;
        cout << "Enter new position for song:" << endl ;
        cin >> newPosition ;
        cin.ignore() ;

        playlist -> ChangePosition(initialPosition, newPosition) ; //calls function with 2 int parameters

        cout << endl ;
        PrintMenu(title) ;
    }

    else if (user_choice == "s") // Output songs by specific artist     
    {
        string artist ;

        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << "\n" ;
        cout << "Enter artist's name:" << endl ;
        getline(cin, artist) ;
        cout << endl ;

        playlist -> PrintSpecificArtist(artist) ; //calls function on playlsit object with string as parameter
        PrintMenu(title) ;
    }

    else if (user_choice == "t") // Output total time of playlist (in seconds)    
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << "\n" ;
        cout << "Total time: " << playlist -> TotalTime() << " seconds" << "\n" ; //because function returns an int, can use it in cout statement
        cout << endl ;

        PrintMenu(title) ;
    }

    else if (user_choice == "o") // Output full playlist   
    {
        playlist -> OutputFullPlaylist(title) ; //calls function with string as parameter
        PrintMenu(title);
    }

    else    
    {
        cout << "Invalid selection." << endl ; //outputs error message
        PrintMenu(title) ;
    }
}