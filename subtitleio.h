#ifndef SUBTITLEIO_H
#define SUBTITLEIO_H

class SubtitleApp;
#include <fstream>
#include <iostream>
#include <regex>
#include "subtitleapp.h"

using namespace std;

class SubtitleIO{

public:
    SubtitleIO(SubtitleApp* app, string f, string form);
    virtual void read() = 0;
    virtual void write() = 0;
    string getFormat() const;
    static string getExtension(string f, int n = 3);

protected:
    void open();
    void close();
    SubtitleApp* app;
    fstream fs;
    string name;
    string format;
};


#endif // SUBTITLEIO_H
