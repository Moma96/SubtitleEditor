#ifndef MICRODVD_H
#define MICRODVD_H

#include <algorithm>
#include "subtitleio.h"
#include "exceptions.h"

class MicroDVD: public SubtitleIO{

public:
    MicroDVD(SubtitleApp* app, string s, double f);

    void write() override;
    void read() override;

private:
    double fps;
};

#endif // MICRODVD_H
