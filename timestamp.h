#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>
using namespace std;


class Timestamp {

public:
    struct tConvert{
        static long getTime(int h, int m, int s, int ms);
        static long getTime(long t, double fps);
        static long getTime(double t, double sum);
    };

    struct tDeconvert{
        static int getH(long t);
        static int getM(long t);
        static int getS(long t);
        static int getMS(long t);
        static long getFpsTime(long t, double fps);
        static double getSubTime(long t, double sum);
    };

    static Timestamp add(const Timestamp& t1, const Timestamp& t2);
    static Timestamp substract(const Timestamp& t1, const Timestamp& t2);

    Timestamp() = default;
    Timestamp(long t);
    Timestamp(int h, int m, int s, int ms);
    Timestamp(long t, double fps);
    Timestamp(double t, double sum);

    bool isAfter(const Timestamp &t) const;
    bool isBefore(const Timestamp &t) const;
    bool isEqual(const Timestamp &t) const;
    bool isAfterOrE(const Timestamp &t) const;
    bool isBeforeOrE(const Timestamp &t) const;
    bool isAfter(long t) const;
    bool isBefore(long t) const;
    bool isEqual(long t) const;
    bool isAfterOrE(long t) const;
    bool isBeforeOrE(long t) const;
    long getTime() const;
    void setTime(long t);
    string toString() const;

private:
    long time;
};

#endif // TIMESTAMP_H
