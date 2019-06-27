#ifndef SUBTITLEAPP_H
#define SUBTITLEAPP_H

class Subtitles;
class SubtitleIO;
class MainWindow;
#include <iostream>
#include <string>
#include "subtitleio.h"
#include "subtitles.h"

using namespace std;

class SubtitleApp{

public:
    SubtitleApp(MainWindow* w, string f, float fps);
    ~SubtitleApp();
    SubtitleIO* getIO() const;
    Subtitles* getSubs() const;
    MainWindow* getW() const;

private:
    SubtitleIO* io;
    Subtitles* subs;
    MainWindow* w;
};

#endif // SUBTITLEAPP_H
