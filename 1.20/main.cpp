#include "Playlist.h"

#include <iostream>

using namespace std ;

Playlist* playlist ;

void PrintMenu(string);

int main() {
    string user_title ;
    cout << "Enter playlist's title:" << endl ;
    getline(cin, user_title) ;
    cout << endl ;

    playlist = new Playlist() ;
    PrintMenu(user_title) ;
}

void PrintMenu(string title)
{
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

    string user_choice ;
    getline(cin, user_choice) ;

    if (user_choice == "q") // Quit       DONE
    {
        return ;
    }

    else if (user_choice == "a") // Add song           DONE
    {
        cout << "ADD SONG" << "\n";
        string id, name, artist ;
        int length ;

        cout << "Enter song's unique ID:" << endl ;
        getline(cin, id);
        cout << "Enter song's name:" << endl ;
        getline(cin, name);
        cout << "Enter artist's name:" << endl ;
        getline(cin, artist);
        cout << "Enter song's length (in seconds):" << endl ;
        cin >> length ;
        cin.ignore() ;

        PlaylistNode* addNode = new PlaylistNode(id, name, artist, length) ;
        playlist -> push_back(addNode) ;

        cout << endl ;
        PrintMenu(title) ;
    }

    else if (user_choice == "d") // Remove song         DONe
    {
        cout << "REMOVE SONG" << "\n" ;
        cout << "Enter song's unique ID:" << "\n" ;
        string ID ;
        getline(cin, ID) ;
        playlist -> RemoveSong(ID) ;
        PrintMenu(title) ;
    }

    else if (user_choice == "c") // Change position of song
    {
        cout << "CHANGE POSITION OF SONG" << endl;
        int initial;
        int newPos;
        cout << "Enter song's current position:" << endl;
        cin >> initial;
        cout << "Enter new position for song:" << endl;
        cin >> newPos;
        cin.ignore();

        playlist->changePos(initial, newPos);
        cout << endl;
        PrintMenu(title);
    }

    else if (user_choice == "s") // Output songs by specific artist     DONE
    {
        playlist -> PrintSpecificArtist() ;
        PrintMenu(title);
    }

    else if (user_choice == "t") // Output total time of playlist (in seconds)    DONE
    {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << "\n" ;
        cout << "Total time: " << playlist -> TotalTime() << " seconds" << "\n" ;
        cout << endl ;
        PrintMenu(title) ;
    }

    else if (user_choice == "o") // Output full playlist   
    {
        playlist -> OutputFullPlaylist(title) ;
        PrintMenu(title);
    }

    else
    {
        cout << "Invalid selection." << endl ;
        PrintMenu(title) ;
    }
}