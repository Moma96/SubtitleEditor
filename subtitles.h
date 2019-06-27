#ifndef SUBTITLES_H
#define SUBTITLES_H

class Subtitle;

#include <iostream>
#include <map>
#include <algorithm>
#include "subtitle.h"
#include "subtitleio.h"

using namespace std;

class Subtitles{

public:
    typedef map<long,Subtitle*> SubCont;

    Subtitles();
    ~Subtitles();
    bool add(Subtitle* s);
    bool remove(SubCont::iterator &i); //, bool adji); // adji - adjust iterator i
    bool remove(long k);
    void removeAll();
    void reallyRemoveAll();
    bool exists(long k);
    bool empty() const;
    bool updateKeys();
    void resolveOverlap(int dly = 100);
    int getQuantity() const;
    SubCont::iterator findClosest(int h, int m, int s, int ms);
    SubCont::iterator findClosest(long t);
    SubCont::iterator findClosest(Timestamp t);
    SubCont::iterator begin();
    SubCont::iterator end();
    SubCont::iterator afterEnd();
    SubCont::iterator next(SubCont::iterator i);
    SubCont::iterator previous(SubCont::iterator i);
    Timestamp duration();
    bool mergeWithNext(SubCont::iterator i, int ms, int ch); // ms - too few miliseconds
                                                             // ch - too few characters
    bool separate(SubCont::iterator &i, int ch); // ch - too much characters

private:
    SubCont* subs;
    const string emptymsg = "ERROR: no more subtitles!";
};

#endif // SUBTITLES_H
