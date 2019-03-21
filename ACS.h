#ifndef __ACS_H
#define __ACS_H
#include <string>
using namespace std;
#include "Track.h"
class ACS {
public:
    ACS();
    ~ACS();
    ACS( const ACS& systemToCopy );
    void operator=( const ACS& right );
    void addTrack( string trackName );
    void removeTrack( string trackName );
    void displayAllTracks();
    void addPaper( string trackName, string paperName );
    void removePaper( string trackName, string paperName );
    void addAuthor( string trackName, string paperName, int authorID, string authorName );
    void removeAuthor(string trackName, string paperName, int authorID );
    void displayTrack( string trackName );
    void displayAuthor( int authorID );
    
    bool isEmpty();
private:
    struct Node {
        Track t;
        Node* next;
    };
    Node *head;
    int trackCount;
    Node* findTrack(string trackName);
};
#endif
