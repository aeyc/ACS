//
//  CS201 HW4
//  Ayca Begum Tascioglu
//  ACS.cpp
//
//  Created by Ayca Begum Tascioglu on 8.05.2018.
//  Copyright © 2018 Ayca Begum Tascioglu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "ACS.h"
using namespace std;

ACS::ACS():trackCount(0),head(NULL){
    
}
ACS::~ACS(){
    if (!isEmpty()){
        while (head != NULL){
            Node *cur = head;
            head = head->next;
            cur->next = NULL;
            delete cur;
            cur = NULL;
        }
    }
}
ACS::ACS( const ACS& systemToCopy ):trackCount(systemToCopy.trackCount){
    if (systemToCopy.head == NULL)
        head = NULL;
    else {
        head = new Node;
        head->t = systemToCopy.head->t;
        Node *newPtr = head;
        
        for (Node *origPtr = systemToCopy.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new Node;
            newPtr = newPtr->next;
            newPtr->t = origPtr->t;
        }
        newPtr->next = NULL;
    }
}
void ACS::operator=( const ACS& right ){
    if ( &right != this){
        if ( trackCount != right.trackCount){
            if ( trackCount > 0 ){
                head->next = NULL;
                delete head;
                head = NULL;
            }
            trackCount = right.trackCount;
            if (trackCount > 0 ){
                head = right.head;
            }
            else
                head = NULL;
        }
        Node* newNode = head;
        for( Node* cur = right.head ; cur !=NULL; cur = cur->next, newNode = newNode->next){
            newNode->t = cur->t;
            
        }
    }
}
void ACS::addTrack( string trackName ){
    if ( findTrack(trackName) == NULL ){
        Node* newItem = new Node;
        newItem->t.setTrackName(trackName);
        newItem->next = NULL;

        if (!isEmpty()){
            Node *cur = head;
            while(cur->next != NULL)
                cur = cur->next;
           if( cur->next == NULL){
                cur->next = newItem;
           }
        }
        else{
            head = newItem;
        }
        trackCount++;
    }
    else{
        cout<<"--WARNING--"<<endl;
        cout<<"The track is already in the system, ADDING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
}
void ACS::removeTrack( string trackName ){
    if ( findTrack(trackName) != NULL ){
        Node* toBeDeleted = findTrack(trackName);
        Node* prev = NULL;
        if (toBeDeleted != head){
            for( Node* cur = head; cur != NULL; cur = cur->next){
                if (cur->next == toBeDeleted){
                    prev = cur;
                    prev->next = cur->next;
                }
            }
        }
        else{
            head = head->next;
        }
        delete prev;
        delete toBeDeleted;
    }
    else{
        cout<<"--WARNING--"<<endl;
        cout<<"The author is not in the paper, REMOVING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
}
void ACS::displayAllTracks(){
    if ( !isEmpty()){
        for( Node* cur = head; cur != NULL; cur = cur->next){
            cout<< "Track: "<< cur->t.getTrackName();
            cur->t.displayAllPapers();
        }
    }
    else
        cout <<"--EMPTY--"<<endl;
}
void ACS::addPaper( string trackName, string paperName ){
    if (findTrack(trackName) == NULL){
        cout<<"The track could not found"<<endl;
    }
    else{
        Node* tmpTrack = findTrack(trackName);
        if( !tmpTrack->t.found(paperName)){
            tmpTrack->t.addPaper(paperName, "", 0);
        }
        else{
            cout<<"Paper is already in the desired track" <<endl;
        }
    }
}
void ACS::removePaper( string trackName, string paperName ){
    if (findTrack(trackName) == NULL){
        cout<<"The track could not found"<<endl;
    }
    else{
        Node* tmpTrack = findTrack(trackName);
        if( tmpTrack->t.found(paperName)){
            tmpTrack->t.removePaper(paperName);
        }
        else{
            cout<<"Paper is not in the desired track" <<endl;
        }
    }
}
void ACS::addAuthor( string trackName, string paperName, int authorID, string authorName ){
    Node* tmp = findTrack(trackName);
    tmp->t.addAuthorToPaper(paperName, authorName,authorID);
}
void ACS::removeAuthor(string trackName, string paperName, int authorID ){
    Node* tmp = findTrack(trackName);
    tmp->t.removeAuthorFromPaper( paperName,authorID);
}
void ACS::displayTrack( string trackName ){
    Node* tmp = findTrack(trackName);
    //cout<< "Track: " << tmp->t.getTrackName()<< endl;
    tmp->t.displayAllPapers();
}
void ACS::displayAuthor( int authorID ){
    for (Node* t = head; t != NULL; t = t->next){
        t->t.displayAnAuthorInPapers(authorID);
    }
}
bool ACS::isEmpty(){
    return (head == NULL) && (trackCount == 0);
}
ACS::Node* ACS::findTrack(string trackName){
    int count = 0;
    for(Node *temp = head; temp != NULL; temp = temp->next)
    {
        if(temp->t.getTrackName().length() == trackName.length())
        {
            count = 0;
            for(int j = 0; j < trackName.length(); j++)
            {
                if(tolower(temp->t.getTrackName()[j]) == tolower(trackName[j]))
                {
                    count++;
                }
            }
            if(count == trackName.length())
            {
                return temp;
            }
        }
    }
    return NULL;
}

