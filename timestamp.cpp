#include "timestamp.h"

Timestamp Timestamp::add(const Timestamp& t1, const Timestamp& t2){

    return Timestamp(t1.getTime() + t2.getTime());
}

Timestamp Timestamp::substract(const Timestamp& t1, const Timestamp& t2){

    return Timestamp(t1.getTime() - t2.getTime());
}

Timestamp::Timestamp(long t): time(t){}

Timestamp::Timestamp(int h, int m, int s, int ms){

    time = tConvert::getTime(h, m, s, ms);
}

Timestamp::Timestamp(long t, double fps){

    time = tConvert::getTime(t, fps);
}

Timestamp::Timestamp(double t, double sum){

    time = tConvert::getTime(t, sum);
}


bool Timestamp::isAfter(const Timestamp &t) const{

    return time > t.getTime();
}

bool Timestamp::isBefore(const Timestamp &t) const{

    return time < t.getTime();
}

bool Timestamp::isEqual(const Timestamp &t) const{

    return time == t.getTime();
}

bool Timestamp::isAfterOrE(const Timestamp &t) const{

    return time >= t.getTime();
}

bool Timestamp::isBeforeOrE(const Timestamp &t) const{

    return time <= t.getTime();
}


bool Timestamp::isAfter(long t) const{

    return time > t;
}

bool Timestamp::isBefore(long t) const{

    return time < t;
}

bool Timestamp::isEqual(long t) const{

    return time == t;
}

bool Timestamp::isAfterOrE(long t) const{

    return time >= t;
}

bool Timestamp::isBeforeOrE(long t) const{

    return time <= t;
}


long Timestamp::getTime() const {

    return time;
}

void Timestamp::setTime(long t){

    time = t;
}

string Timestamp::toString() const{

    return to_string(Timestamp::tDeconvert::getH(time)) + ':' + to_string(Timestamp::tDeconvert::getM(time)) + ':' + to_string(Timestamp::tDeconvert::getS(time)) + ',' + to_string(Timestamp::tDeconvert::getMS(time));
}


long Timestamp::tConvert::getTime(int h, int m, int s, int ms){

    return h*3600000 + m*60000 + s*1000 + ms;
}

long Timestamp::tConvert::getTime(long t, double fps){ // throws badFps

    //if (fps < 0) throw badFps;
    return (double)t / fps * 1000;
}

long Timestamp::tConvert::getTime(double t, double sum){

    return (sum + t)*1000;
}

int Timestamp::tDeconvert::getH(long t){

    return t / 3600000;
}

int Timestamp::tDeconvert::getM(long t){

    return t % 3600000 / 60000;
}

int Timestamp::tDeconvert::getS(long t){

    return t % 3600000 % 60000 / 1000;
}

int Timestamp::tDeconvert::getMS(long t){

    return t % 3600000 % 60000 % 1000;
}


long Timestamp::tDeconvert::getFpsTime(long t, double fps){ // throws badFps

    //if (fps < 0) throw badFps;
    return (double)t / 1000 * fps;
}

double Timestamp::tDeconvert::getSubTime(long t, double sum){

    return (double)t / 1000 - sum;
}
