//
//  CS201 HW4
//  Author.cpp class to create an author
//
//  Created by Ayca Begum Tascioglu on 8.05.2018.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "Author.h"
using namespace std;

Author::Author():name(""),aid(0){
}
Author::Author(const int aid, const string name):name(name),aid(aid){
}
int Author::getID(){
    return aid;
}
string Author::getName(){
    return name;
}
void Author::setName(string aName){
    name = aName;
}
void Author::setId(int aId){
    aid = aId;
}
