#include "subtitleprocessing.h"
#include "exceptions.h"

SubtitleProcessing::SubtitleProcessing(SubtitleApp* app): app(app), editSub(app), editTiming(app) {}


SubtitleProcessing::EditSub::EditSub(SubtitleApp* app): app(app) {}

void SubtitleProcessing::EditSub::addSub(Subtitle* s){ // throws AdditionFailed

    if (!app->getSubs()->add(s)) throw AdditionFailed(app->getW());

    app->getSubs()->resolveOverlap();
    app->getSubs()->updateKeys();
}

bool SubtitleProcessing::EditSub::replaceSub(Subtitles::SubCont::iterator i, string s){

    if (s.empty()) return false;

    i->second->setString(s);
    return true;
}

bool SubtitleProcessing::EditSub::appendSent(Subtitles::SubCont::iterator i, string s){

    if (s.empty()) return false;

    string str = i->second->getString();
    str.append(s);
    i->second->setString(str);
    return true;
}

bool SubtitleProcessing::EditSub::deleteSent(Subtitles::SubCont::iterator &i, string s, int occ){ // throws BadNumberOfOccur, PosNotFound

    if (s.empty()) return false;
    if (occ <= 0) throw BadNumberOfOccur(app->getW());

    string str = i->second->getString();
    size_t pos = i->second->calcStringPosition(s, occ);

    if (pos == string::npos) throw PosNotFound(app->getW());
    str.erase(pos, s.size());

    if (str.empty()) deleteSub(i);
    else
        i->second->setString(str);
    return true;
}

void SubtitleProcessing::EditSub::deleteSub(Subtitles::SubCont::iterator &i){ // throws RemovalFailed

    if (app->getSubs()->empty()) throw RemovalFailed(app->getW());
    app->getSubs()->remove(i);
}

bool SubtitleProcessing::EditSub::deleteSubs(Timestamp t1, Timestamp t2){ // throws badtime

     if (t1.getTime() < 0 || t2.getTime() < 0 || t1.isAfterOrE(t2)) throw BadTimeInput(app->getW());

    Subtitles::SubCont::iterator i = app->getSubs()->findClosest(t1);
    Subtitles::SubCont::iterator j = app->getSubs()->findClosest(t2);
    while (i != j)
        app->getSubs()->remove(i);
    app->getSubs()->remove(i);
    return true;
}

void SubtitleProcessing::EditSub::mergeAll(int ms, int ch){ // throws BadNumberOfMS, BadNumberOfChars

    if (ms <= 0) throw BadNumberOfMS(app->getW());
    if (ch <= 0) throw BadNumberOfChars(app->getW());

    bool happened = true;
    while (happened){
        happened = false;
        for (Subtitles::SubCont::iterator i = app->getSubs()->begin(); i != app->getSubs()->end(); i++)
            if (app->getSubs()->mergeWithNext(i, ms, ch)) happened = true;
    }
    app->getSubs()->updateKeys();
}

void SubtitleProcessing::EditSub::separateAll(int ch){ // throws BadNumberOfChars

    if (ch <= 0) throw BadNumberOfChars(app->getW());

    Subtitles::SubCont::iterator i = app->getSubs()->begin();
    while (i != ++app->getSubs()->end())
        if (!app->getSubs()->separate(i, ch)) i++;
    app->getSubs()->updateKeys();
}


SubtitleProcessing::EditTiming::EditTiming(SubtitleApp* app): app(app) {}

void SubtitleProcessing::EditTiming::transfer(Timestamp t1, Timestamp t2, int ms, bool extr){ //throws BadTimeInput, TOAisAfterTOR

    if (t1.getTime() < 0 || t2.getTime() < 0) throw BadTimeInput(app->getW());
    if (t1.isAfter(t2)) throw TOAisAfterTOR(app->getW());

    Subtitles::SubCont::iterator it1 = app->getSubs()->findClosest(t1);
    Subtitles::SubCont::iterator it2 = ++(app->getSubs()->findClosest(t2));

    for (Subtitles::SubCont::iterator i = it1; i != it2; i++)
        i->second->transfer(ms);
    if (extr){
        Subtitles::SubCont::iterator end = app->getSubs()->afterEnd();
        it2++;
        for (Subtitles::SubCont::iterator i = it2; i != end; i++)
            i->second->transfer(ms);
    }
    app->getSubs()->resolveOverlap();
    app->getSubs()->updateKeys();
}

void SubtitleProcessing::EditTiming::scaleMS(Timestamp t1, Timestamp t2, int ms, bool extr){ //throws BadTimeInput

    if (t1.getTime() < 0 || t2.getTime() < 0 || t1.isAfterOrE(t2)) throw BadTimeInput(app->getW());

    Subtitles::SubCont::iterator it1 = app->getSubs()->findClosest(t1);
    Subtitles::SubCont::iterator it2 = ++app->getSubs()->findClosest(t2);

    int s = 0;
    for (Subtitles::SubCont::iterator i = it1; i != it2; i++){
        s += ms;
        i->second->transfer(s);
    }
    if (extr){
        Subtitles::SubCont::iterator end = app->getSubs()->afterEnd();
        it2++;
        for (Subtitles::SubCont::iterator i = it2; i != end; i++){
            s += ms;
            i->second->transfer(s);
        }
    }
    else app->getSubs()->resolveOverlap();
    app->getSubs()->updateKeys();
}

void SubtitleProcessing::EditTiming::scaleBetween(Timestamp t1, Timestamp t2){ // throws badTime

    if (t1.getTime() < 0 || t2.getTime() < 0 || t1.isAfterOrE(t2)) throw BadTimeInput(app->getW());
    long oldl = app->getSubs()->duration().getTime();
    long l = Timestamp::substract(t2, t1).getTime();
    Subtitles::SubCont::iterator it;

    for (it = app->getSubs()->begin(); it != app->getSubs()->afterEnd(); it++){
        it->second->setTimeOfAppearance(Timestamp(t1.getTime() + (long)((double)l/(double)oldl*it->second->getTimeOfAppearance().getTime())));
        it->second->setTimeOfRemoval(Timestamp(t1.getTime() + (long)((double)l/(double)oldl*it->second->getTimeOfRemoval().getTime())));
    }

    app->getSubs()->updateKeys();
}

void SubtitleProcessing::save(){

    app->getIO()->write();
}
