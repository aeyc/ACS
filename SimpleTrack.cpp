//
//  SimpleTrack.cpp
//  SimpleTrack
//
//  Created by Ayca Begum Tascioglu on 30.04.2018.
//  Copyright © 2018 Ayca Begum Tascioglu. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include "SimpleTrack.h"
using namespace std;

Track::Track(const string tname):trackName(tname){
}
Track::~Track (){
}
Track::Track (const Track &trackToCopy):trackName(trackToCopy.trackName){
}
void Track::operator=(const Track &right){
    if ( &right != this) trackName = right.trackName;
}
string Track::getTrackName(){
    return trackName;
}
void Track::setTrackName(string tName){
    trackName = tName;
}
