#include "subtitle.h"

Subtitle::Subtitle(string n, Timestamp st, Timestamp end): str(n), start(st), end(end) {}

string Subtitle::getString() const{

    return str;
}

Timestamp Subtitle::getTimeOfAppearance() const{

    return start;
}

Timestamp Subtitle::getTimeOfRemoval() const{

    return end;
}

Timestamp Subtitle::calcDuration() const{

    return Timestamp::substract(end, start);
}

size_t Subtitle::calcStringPosition(string s, size_t occ) const{

    size_t pos = -1;
    for (int i = 0; i < occ; i++){
        pos = str.find(s, pos + 1);
        if (pos == string::npos) return string::npos;
    }
    return pos;
}

void Subtitle::setString(string s){

    str = s;
}

void Subtitle::setTimeOfAppearance(Timestamp t){

    start = t;
}

void Subtitle::setTimeOfRemoval(Timestamp t){

    end = t;
}

 void Subtitle::transfer(int ms){

     start.setTime(start.getTime() + ms);
     end.setTime(end.getTime() + ms);
 }
