#ifndef SRT_H
#define SRT_H

#include "subtitleio.h"
#include "exceptions.h"

class SRT: public SubtitleIO{

public:
    SRT(SubtitleApp* app, string s);

    void write() override;
    void read() override;
};

#endif // SRT_H
