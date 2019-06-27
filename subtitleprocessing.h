#ifndef SUBTITLEPROCESSING_H
#define SUBTITLEPROCESSING_H

#include <iostream>
#include <valarray>
#include "subtitleapp.h"

using namespace std;

class SubtitleProcessing{

public:
    SubtitleProcessing(SubtitleApp* app);

    class EditSub{
    public:
        EditSub(SubtitleApp* app);
        void addSub(Subtitle* s);
        bool replaceSub(Subtitles::SubCont::iterator i, string s);
        bool appendSent(Subtitles::SubCont::iterator i, string s);
        bool deleteSent(Subtitles::SubCont::iterator &i, string s, int occ);
        void deleteSub(Subtitles::SubCont::iterator &i);
        bool deleteSubs(Timestamp t1, Timestamp t2);
        void mergeAll(int ms, int ch);
        void separateAll(int ch);
    private:
        SubtitleApp* app;
    };

    class EditTiming{
    public:
        EditTiming(SubtitleApp* app);
        void transfer(Timestamp t1, Timestamp t2, int ms, bool extr);
        void scaleMS(Timestamp t1, Timestamp t2, int ms, bool extr);
        void scaleBetween(Timestamp t1, Timestamp t2);
    private:
        SubtitleApp* app;
    };

    EditSub editSub;
    EditTiming editTiming;
    void save();

private:
    SubtitleApp* app;
};

#endif // SUBTITLEPROCESSING_H
