//
//  CS201 HW4
//  Author.h class to specify Author.cpp class functions, create an author
//
//  Created by Ayca Begum Tascioglu on 8.05.2018.
//
#ifndef __AUTHOR_H
#define __AUTHOR_H
#include <string>
using namespace std;
class Author{
public:
    Author();
    Author(const int id, const string name);
    int getID();
    string getName();
    void setName(string aName);
    void setId(int aId);
private:
    string name;
    int aid;
};
#endif
