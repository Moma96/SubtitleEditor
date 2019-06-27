#include "subtitles.h"

Subtitles::Subtitles(){

    subs = new SubCont();
    do{
    (*subs)[0] = new Subtitle(emptymsg, Timestamp(0), Timestamp(0));
    } while(!exists(0));
}

Subtitles::~Subtitles(){

    reallyRemoveAll();
    delete subs;
}

bool Subtitles::add(Subtitle* s){

    if (subs->size() == 1 && subs->begin()->second->getString() == emptymsg){
        do{
        subs->erase(0);
        } while(exists(0));
    }

    (*subs)[s->getTimeOfAppearance().getTime()] = s;
    if (exists(s->getTimeOfAppearance().getTime())) return true;
    else return false;
}

bool Subtitles::remove(SubCont::iterator &i){

    if (i == end())
        return remove((i--)->first);
    return remove((i++)->first);
}

bool Subtitles::remove(long k){

    if (subs->size() == 1 && subs->begin()->second->getString() == emptymsg) return false;

    if (!exists(k)) return false;
    subs->erase(k);
    if (exists(k)) return false;

    if (subs->empty()){
        do{
        (*subs)[0] = new Subtitle(emptymsg, Timestamp(0), Timestamp(0));
        } while(!exists(0));
    }
    return true;
}

void Subtitles::removeAll(){

    for (SubCont::iterator i = subs->begin(); i!= subs->end(); i++)
        delete i->second;

    do{
    (*subs)[0] = new Subtitle(emptymsg, Timestamp(0), Timestamp(0));
    } while(!exists(0));
}

void Subtitles::reallyRemoveAll(){

    for (SubCont::iterator i = subs->begin(); i!= subs->end(); i++)
        delete i->second;
}

bool Subtitles::exists(long k){

    return (subs->find(k)!= subs->end());
}

bool Subtitles::empty() const{

    if (subs->size() == 1 && subs->begin()->second->getString() == emptymsg) return true;
    return false;
}

bool Subtitles::updateKeys(){

    SubCont* c = new SubCont();
    for (SubCont::iterator i = subs->begin(); i!= subs->end(); i++){
        (*c)[i->second->getTimeOfAppearance().getTime()] = i->second;
        if (c->find(i->second->getTimeOfAppearance().getTime()) == subs->end()) return false;
    }
    delete subs;
    subs = c;
    return true;
}

void Subtitles::resolveOverlap(int dly){

    SubCont::iterator i = subs->begin();
    SubCont::iterator j;
    Timestamp t;

    if (i->second->getTimeOfAppearance().isBefore(Timestamp(0))){
        t = Timestamp::substract(Timestamp(0), i->second->getTimeOfAppearance());
        i->second->transfer(t.getTime());
    }

    while (i!= end()){
        j = i++;
        if (i->second->getTimeOfAppearance().isBeforeOrE(j->second->getTimeOfRemoval())){
            t = Timestamp::substract(j->second->getTimeOfRemoval(), i->second->getTimeOfAppearance());
            i->second->transfer(t.getTime() + dly);
        }
    }
}

int Subtitles::getQuantity() const{

     if (subs->size() == 1 && subs->begin()->second->getString() == emptymsg) return 0;
    return subs->size();
}

Subtitles::SubCont::iterator Subtitles::findClosest(int h, int m, int s, int ms){

    long t = Timestamp::tConvert::getTime(h,m,s,ms);
    if (t < 0) return subs->end();
    return findClosest(t);
}

Subtitles::SubCont::iterator Subtitles::findClosest(long t){

    SubCont::iterator j = subs->lower_bound(t);
    SubCont::iterator i = j--;

    if (i == subs->begin() || i->first == t)
        return i;

    if (i == subs->end())
        return j;

    if (j->second->getTimeOfAppearance().getTime() <= t && j->second->getTimeOfRemoval().getTime() >= t)
        return j;

    long ii = i->second->getTimeOfAppearance().getTime() - t;
    long jj = t - j->second->getTimeOfRemoval().getTime();
    return (min(ii,jj) == ii)? i : j;
}

Subtitles::SubCont::iterator Subtitles::findClosest(Timestamp t){

    long tt = t.getTime();
    return findClosest(tt);
}

Subtitles::SubCont::iterator Subtitles::next(SubCont::iterator i){

    if (i == end()) return i;
    return ++i;
}

Subtitles::SubCont::iterator Subtitles::previous(SubCont::iterator i){

    if (i == begin()) return i;
    return --i;
}

Subtitles::SubCont::iterator Subtitles::begin(){

    return subs->begin();
}

Subtitles::SubCont::iterator Subtitles::end(){

    return --subs->end();
}

Subtitles::SubCont::iterator Subtitles::afterEnd(){

    return subs->end();
}

Timestamp Subtitles::duration(){

    return Timestamp::substract(end()->second->getTimeOfRemoval(), begin()->second->getTimeOfAppearance());
}

bool Subtitles::mergeWithNext(SubCont::iterator i, int ms, int ch) {

    if (ms <= 0 || ch <= 0) return false;

    if (i == end()) return false;

    SubCont::iterator j = i++;
    if (Timestamp::substract(i->second->getTimeOfAppearance(), j->second->getTimeOfRemoval()).isBeforeOrE(ms) &&
        (j->second->getString().size() <= (unsigned)ch || i->second->getString().size() <= (unsigned)ch )){

        j->second->setTimeOfRemoval(i->second->getTimeOfRemoval());
        j->second->setString(j->second->getString().append("\n" + i->second->getString()));
        remove(i->first);
        return true;
    }
    return false;
 }

bool Subtitles::separate(SubCont::iterator &i, int ch) {

    if (ch <= 0) return false;

    string s = i->second->getString();
    if (s.size() < (unsigned)ch ) return false;
    size_t occ = (count(s.begin(), s.end(), ' ') + count(s.begin(), s.end(), '\n')) / 2;
    size_t pos = i->second->calcStringPosition(" ", occ);
    string s1, s2;

    s1 = s2 = i->second->getString();
    s1.erase(s1.begin() + pos, s1.end());
    s2.erase(s2.begin(), s2.begin() + pos);
    long t = i->second->getTimeOfAppearance().getTime() + i->second->calcDuration().getTime() / 2;
    Subtitle* sub1 = new Subtitle(s1, i->second->getTimeOfAppearance(), Timestamp(t));
    Subtitle* sub2 = new Subtitle(s2, Timestamp(t + 1), i->second->getTimeOfRemoval());

    if (!remove(i->first)) return false;
    if (add(sub1) && add(sub2)){
        i = --(subs->find(t + 1));
        return true;
    }
    return false;
}
