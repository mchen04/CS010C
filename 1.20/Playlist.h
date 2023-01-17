#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <string>

using namespace std;

class PlaylistNode
{
private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
public:
    PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) { }
    PlaylistNode(string, string, string, int) ;
    void InsertAfter(PlaylistNode*) ;
    void SetNext(PlaylistNode*) ;
    string GetID() const ;
    string GetSongName() const ;
    string GetArtistName() const ;
    int GetSongLength() const ;
    PlaylistNode* GetNext() const ;
    void PrintPlaylistNode() const ;
};

class Playlist
{
private:
    PlaylistNode* head ;
    PlaylistNode* tail ;
public:
    Playlist();
    void push_back(PlaylistNode*) ;
    void RemoveSong(string) ;
    void changePos(int, int) ;
    void PrintSpecificArtist() const ;
    int TotalTime() const ;
    void OutputFullPlaylist(string) const ;
};
#endif