#ifndef __SIMPLE_TRACK_H
#define __SIMPLE_TRACK_H
#include <string>
#include "Paper.h"
using namespace std;
class Track {
public:
    Track(const string tname = "");
    ~Track ();
    Track (const Track &trackToCopy);
    void operator=(const Track &right);
    string getTrackName();
    void setTrackName(string tName);
    
    bool isEmpty();
    bool addPaper(string pName, string aName, int id);
    bool removePaper(string pName);

    void displayAllPapers();
    bool found(string pName);
    
    void addAuthorToPaper(string paperName, string authorName, int authorID);
    void removeAuthorFromPaper(string paperName, int authorID);
    
    void displayAnAuthorInPapers( int authorID );
private:
    string trackName;
    struct PaperNode{
        Paper p;
        PaperNode* next;
    };
    PaperNode *head;
    int paperCount;
    PaperNode* findPaper(string pName);
};
#endif

