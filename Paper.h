//
//  CS201 HW4
//  Paper.h
//
//  Created by Ayca Begum Tascioglu on 5.05.2018.
//  Copyright © 2018 Ayca Begum Tascioglu. All rights reserved.
//

#ifndef __PAPER_H
#define __PAPER_H
#include <string>
using namespace std;
#include "Author.h"
class Paper{
public:
    Paper();
    Paper( const string name );
    ~Paper();
    Paper( const Paper& paperToCopy );
    void operator=( const Paper& right );
    string getName();
    bool addAuthor( const int id, const string name );
    bool removeAuthor ( const int id );
    void displayAuthors();
    
    bool isEmpty();
    
    void setName(string paperName);
    void setAuthor(string aName, int aID);
    string getAuthorName(int aID);
    
    void displayAnAuthor(int authorID);

private:
    struct AuthorNode {
        Author a;
        AuthorNode* next;
    };
    AuthorNode *head;
    string name;
    int authorCount;
    AuthorNode* findAuthor(int id);
};
#endif
