#include <stdio.h>
#include <iostream>
#include <string>
#include "SimpleACS.h"
using namespace std;

ACS::ACS():trackCount(0),head(NULL){
    name = "";
    topic = "";
}
ACS::~ACS(){
    while ( head != NULL)
    {
        TrackNode *temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
        temp = NULL;
    }
}
ACS::ACS(const ACS& acsToCopy):trackCount(acsToCopy.trackCount){
    if (acsToCopy.head == NULL)
        head = NULL;
    else {
        head = new TrackNode;
        head->t.setTrackName(acsToCopy.head->t.getTrackName());
        TrackNode *newPtr = head;
        
        for (TrackNode *origPtr = acsToCopy.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new TrackNode;
            newPtr = newPtr->next;
            newPtr->t.setTrackName(origPtr->t.getTrackName());
        }
        newPtr->next = NULL;
    }

}
void ACS::operator=(const ACS& right){
    if (!isEmpty()){
        for( TrackNode* cur = head; cur != NULL; cur = cur->next){
            head = head->next;
        }
        delete head;
    }
    TrackNode* cur = right.head;
    while(cur != NULL){
        addTrack(cur->t.getTrackName());
        cur = cur->next;
    }
    head = cur;
}
bool ACS::addTrack(const string trackName){
    if ( findTrack(trackName) == NULL ){
        TrackNode* newItem = new TrackNode;
        newItem->t.setTrackName(trackName);
        newItem->next = NULL;
        
        if (!isEmpty()){
            TrackNode* cur = head;
            while( cur->next != NULL ){
                cur = cur->next;
            }
            cur->next = newItem;
        }
        else{
            head = newItem;
        }
        trackCount++;
        return true;
    }
    return false;
}
bool ACS::removeTrack (const string trackName){
    TrackNode* toBeDeleted = findTrack(trackName);
    TrackNode* prev = NULL;
    if ( toBeDeleted != NULL ){
        if (toBeDeleted != head){
            for( TrackNode* cur = head; cur != NULL; cur = cur->next){
                if (cur->next == toBeDeleted){
                    prev = cur;
                    prev->next = cur->next;
                    trackCount--;
                    return true;
                }
            }
        }
        else{
            head = head->next;
            trackCount--;
            return true;
        }
    }
    delete prev;
    delete toBeDeleted;
    return false;
}
void ACS::displayTracks(){
    if ( !isEmpty()){
        for( TrackNode* cur = head; cur != NULL; cur = cur->next){
            cout <<"Track "<< cur->t.getTrackName()<<endl;
        }
    }
    else
        cout <<"--EMPTY--"<<endl;
}
ACS::TrackNode *ACS::findTrack(string trackName){
    if (!isEmpty()){
        for (TrackNode* cur = head; cur != NULL; cur = cur->next){
            if( trackName.length() == cur->t.getTrackName().length()){
                int count = 0;
                for ( int j = 0; j < trackName.length(); j++){
                    if ( tolower(trackName[j]) == tolower(cur->t.getTrackName()[j])){
                        count++;
                    }
                }
                if (count == trackName.length())
                    return cur;
            }
        }
    }
        return NULL;
}
bool ACS::isEmpty(){
    return head == NULL && trackCount ==0;
}

