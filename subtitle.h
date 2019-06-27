#ifndef SUBTITLE_H
#define SUBTITLE_H

#include <string>
#include "timestamp.h"
#include "subtitleio.h"

using namespace std;

class Subtitle{
    friend class Subtitleio;

public:
    Subtitle() = default;
    Subtitle(string n, Timestamp st, Timestamp end);

    string getString() const;
    Timestamp getTimeOfAppearance() const;
    Timestamp getTimeOfRemoval() const;
    Timestamp calcDuration() const;
    size_t calcStringPosition(string s, size_t occ) const; // occ - occurence
    void setString(string s);
    void setTimeOfAppearance(Timestamp t);
    void setTimeOfRemoval(Timestamp t);
    void transfer(int ms);

private:
    string str;
    Timestamp start;
    Timestamp end;
};

#endif // SUBTITLE_H
