//
//  CS201 HW4
//  Paper.cpp class to create a paper object
//
//  Created by Ayca Begum Tascioglu on 5.05.2018.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "Paper.h"
using namespace std;
/*
 Paper contructor to construct a new Paper object
 it initializes name as an empty string
 head as null to emphasize list is empty
 and author count to 0
 */
Paper::Paper():name(""),head(NULL),authorCount(0){
}
/*
 Paper contructor to construct a new Paper object
 it initializes name as desired name given by user
 head as null to emphasize list is empty
 and author count to 0
 */
Paper::Paper( const string name ):name(name),head(NULL),authorCount(0){
}
/*
 Paper Destructor to destruct Paper class's dynamic data - nodes- linked list
 to avoid memory leaks
 */
Paper::~Paper(){
    while ( !isEmpty() )
    {
        AuthorNode *cur = head;
        head = head->next;
        cur->next = NULL;
        delete cur;
        cur = NULL;
    }
}
//reference: linked list slides
Paper::Paper( const Paper& paperToCopy ){
    if (paperToCopy.head == NULL)
        head = NULL;
    else {
        head = new AuthorNode;
        head->a.setName(paperToCopy.head->a.getName());
        AuthorNode *newPtr = head;
        
        for (AuthorNode *origPtr = paperToCopy.head->next;
             origPtr != NULL;
             origPtr = origPtr->next){
            newPtr->next = new AuthorNode;
            newPtr = newPtr->next;
            newPtr->a.setName(origPtr->a.getName());
        }
        newPtr->next = NULL;
    }

}
//Paper object assignment operator
//reference: classes slides
void Paper::operator=( const Paper& right ){
    if ( &right != this){ //avoid self referencing
        if ( authorCount != right.authorCount){ //if their object count is different we should equalize
            if ( authorCount > 0 ){ //if our list is not empty delete all
                head->next = NULL;
                delete head;
                head = NULL;
            }
            authorCount = right.authorCount; //equalize
            
            if ( authorCount > 0 ){
                head = right.head;
            }
            else
                head = NULL;
        }
        AuthorNode* newNode = head;
        for( AuthorNode* cur = right.head ; cur !=NULL; cur = cur->next, newNode = newNode->next){
            newNode->a = cur->a;
            
        }
    }
}
/*
 getName method to reach the name of the paper from other classes
 */
string Paper::getName(){
    return name;
}
/*
 addAuthor method to add a new Author to Paper class's linked list
 it takes author id and author name and create a new item to be added
 then adds the new author to this linked list's end
 */
bool Paper::addAuthor( const int id, const string name ){
    if ( findAuthor(id) == NULL ){  //if author is not in the paper, then move to adding process
        AuthorNode* newItem = new AuthorNode; //create the new item to be added
        //set the new item's properties
        newItem->a.setName(name);
        newItem->a.setId(id);
        newItem->next = NULL;
        
        if(!isEmpty()){ //if we will not add the new item to the beginning of the linked list then...
            AuthorNode* cur = head;
            while( cur->next != NULL ){
                cur = cur->next;
            }
            cur->next = newItem;
        }
        else head = newItem;
        authorCount++;
        return true;
    }
    else{   //if author is already in the paper display a warning message
        cout<<"--WARNING--"<<endl;
        cout<<"The author is already in the paper, ADDING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
    return false;
}
/*
 removeAuthor method to remove an author from the Paper class's linked list
 it takes author id
 then removes the desired author from the linked list by finding it with findAuthor method
 */
bool Paper::removeAuthor ( const int id ){
    if ( findAuthor(id) != NULL ){  //if the author exists in system-paper
        AuthorNode* toBeDeleted = findAuthor(id);
        AuthorNode* prev = NULL;
        if (toBeDeleted != head){
            for( AuthorNode* cur = head; cur != NULL; cur = cur->next){
                if (cur->next == toBeDeleted){
                    prev = cur;
                    prev->next = cur->next;
                    return true;
                }
            }
        }
        else{
            head = head->next;
            return true;
        }
        authorCount--;
        delete prev;
        delete toBeDeleted;
    }
    else{   //display an error message if the author could not found
        cout<<"--WARNING--"<<endl;
        cout<<"The author is not in the paper, REMOVING request was not succeed"<<endl;
        cout<<"--WARNING--"<<endl;
        cout<<endl;
    }
    return false;
}
/*
 display all authors in the paper
 */
void Paper::displayAuthors(){
    if ( !isEmpty()){
        for( AuthorNode* cur = head; cur != NULL; cur = cur->next){
            cout <<"Author: "<< cur->a.getID()<< " "<< cur->a.getName()<<endl;
        }
    }
    else
        cout <<"--EMPTY--"<<endl;
}
/*
 if the head is null then all list is empty
 isEmpty method to decide if the linked list is empty or not
 */
bool Paper::isEmpty(){
    return head == NULL;
}
/*
 findAuthor method to find an author with specified name
 if it finds, return that node
 else returns null
 */
Paper::AuthorNode* Paper::findAuthor(int id){
    for(AuthorNode *temp = head; temp != NULL; temp = temp->next)
    {
        if(temp->a.getID() == id)
        {
            return temp;
        }
    }
    return NULL;
}
/*
 set name method to initialize the paper name from other classes
 */
void Paper::setName(string paperName){
    name = paperName;
}
/*
 setAuthor method to set author info from other classes
 */
void Paper::setAuthor(string aName, int aID){
    if (findAuthor(aID) != NULL){
        findAuthor(aID)->a.setName(aName);
        findAuthor(aID)->a.setId(aID);
    }
}
/*
 displayAnAuthor method the display author info
 Also, I wrote it for the displayAuthor method in ACS.cpp
 */
void Paper::displayAnAuthor(int authorID){
    AuthorNode* a = findAuthor(authorID);
    cout<< "Paper: " << getName() <<endl;
    cout<< "Author Name: " << a->a.getName()<<endl;
    cout<< "Author ID: " << a->a.getID()<<endl;
}
