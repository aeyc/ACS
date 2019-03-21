//
//  CS201 HW 4
//  Track.cpp create a track object and perform its functions
//  Created by Ayca Begum Tascioglu on 30.04.2018.
//  Copyright © 2018 Ayca Begum Tascioglu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "Track.h"
using namespace std;

/*
 Track contructor to construct a new Track object
 it initializes name as the desired-given by user name
 head as null to emphasize list is empty
 and paper count to 0
 */
Track::Track(const string tname):trackName(tname),head(NULL),paperCount(0){
}
/*
 Track Destructor to destruct Track class's dynamic data - nodes- linked list
 to avoid memory leaks
 */
//reference: linked list slides
Track::~Track(){
    while ( !isEmpty())
    {
        PaperNode* cur = head;
        head = head->next;
        cur->next = NULL;
        delete cur;
        cur = NULL;
    }
}
//reference: linked list slides
//copy constructor for Track object
Track::Track (const Track &trackToCopy){
    if (trackToCopy.head == NULL)
        head = NULL;  
    else {
        head = new PaperNode;
        head->p = trackToCopy.head->p;
        PaperNode *newPtr = head;
        
        for (PaperNode *origPtr = trackToCopy.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new PaperNode;
            newPtr = newPtr->next;
            newPtr->p = origPtr->p;
        }
        newPtr->next = NULL;
    }
}
//Track object assignment operator
//reference: classes deeper look slides
void Track::operator=(const Track &right){
    if ( &right != this){
        if ( paperCount != right.paperCount){
            if ( paperCount > 0 ){
                head->next = NULL;
                delete head;
                head = NULL;
            }
            paperCount = right.paperCount;
            
            if ( paperCount > 0 ){
                head = right.head;
            }
            else
                head = NULL;
        }
        PaperNode* newNode = head;
        for( PaperNode* cur = right.head ; cur !=NULL; cur = cur->next, newNode = newNode->next){
            newNode->p = cur->p;
            
        }
    }
}
/*
 getTrackName method to reach the name of the Track from the other classes
 */
string Track::getTrackName(){
    return trackName;
}
/*
 setTrackName method to initialize the paper name from other classes
 */
void Track::setTrackName(string tName){
    trackName = tName;
}
/*
 if the head is null then all list is empty
 isEmpty method to decide if the linked list is empty or not
 */
bool Track::isEmpty(){
    //return (head == NULL) && (paperCount == 0);
    return (head == NULL) ;
}
/*
 addPaper method to add a new Paper object to Track class' linked list
 it takes paper name, author id and author name and create a new item to be added
 then adds the new paper to this linked list's end
 if the requested action succeed then return true
 else return false-(if the paper is already in the system)
 */
bool Track::addPaper(string pName, string aName, int id){
    if ( findPaper(pName) == NULL ){    //if the paper is not in the system then execute the adding process
        PaperNode* newItem = new PaperNode;
        newItem->p.setName(pName);
        newItem->next = NULL;
        
        if (!isEmpty()){
            PaperNode* cur = head;
            while( cur->next != NULL ){
                cur = cur->next;
            }
            cur->next = newItem;
        }
        else{
            head = newItem;
        }
        paperCount++;
        return true;
    }
    else{   //if author already exists in the system display a warning message and do not perform the requested action
        cout<<"--WARNING--"<<endl;
        cout<<"The paper is already in the track, ADDING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
    return false;
}
/*
 removePapermethod to remove a paper from the Paper class's linked list
 it takes paper name- wrote a method to detect case sensitive names
 then removes the desired paper from the linked list by finding it with findPaper method
 if requested action is succeed which means paper is in system then removed- returns true
 else returns false
 */
bool Track::removePaper(string pName){
    if ( findPaper(pName) != NULL ){    //if author is in the system then start the removing process
        PaperNode* toBeDeleted = findPaper(pName);
        if (toBeDeleted != head){
            PaperNode *first = head;
            while(first->next != toBeDeleted)
            {
                first = first->next;
            }
            first->next = toBeDeleted->next;
            toBeDeleted->next = NULL;
            delete toBeDeleted;
            toBeDeleted = NULL;
        }
        else{
            if (head->next == NULL){
                delete head;
                head = NULL;
                paperCount = 0;
            }
            else{
                PaperNode *temp = head;
                head = head->next;
                temp->next = NULL;
                delete temp;
                temp = NULL;
                paperCount--;
            }
        }

    }
    else{   //if author doesnt exist then display a warning and do not perform the requested removing action
        cout<<"--WARNING--"<<endl;
        cout<<"The paper is not in the track, REMOVING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
    return false;
}
/*
 findPaper method to find the paper with specified name
 */
Track::PaperNode* Track::findPaper(string pName){
    int count = 0;
    for(PaperNode *temp = head; temp != NULL; temp = temp->next)
    {
        if(temp->p.getName().length() == pName.length())
        {
            count = 0;
            for(int j = 0; j < pName.length(); j++)
            {
                if(tolower(temp->p.getName()[j]) == tolower(pName[j]))
                {
                    count++;
                }
            }
            if(count == pName.length())
            {
                return temp;
            }
        }
    }
    return NULL;
}
/*
 display all papers in the track
 */
void Track::displayAllPapers(){
    if ( !isEmpty()){
        cout<<"Track: "<< getTrackName()<<endl;
        for( PaperNode* cur = head; cur != NULL; cur = cur->next){
            cout<< "Paper: " << cur->p.getName() <<endl;
            cur->p.displayAuthors();
        }
    }
    else
        cout <<"--EMPTY--"<<endl;
}
//this method is written for reaching whether the paper is found or not from other classes
//because find method is private type and cannot be accessed from other classes
bool Track::found(string pName){
    if (findPaper(pName) == NULL) return false;
    return true;
}

//this methods to eaze ACS class operations
void Track::addAuthorToPaper(string paperName, string authorName, int authorID){
    PaperNode* tmpPaper = findPaper(paperName);
    tmpPaper->p.addAuthor(authorID, authorName);
}
void Track::removeAuthorFromPaper(string paperName, int authorID){
    PaperNode* tmpPaper = findPaper(paperName);
    tmpPaper->p.removeAuthor(authorID);
}

void Track::displayAnAuthorInPapers( int authorID ){
    for (PaperNode* p = head; p != NULL; p = p->next){
        cout << "Track Name: " << getTrackName()<<endl;
        p->p.displayAnAuthor(authorID);
    }
}

