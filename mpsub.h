#ifndef MPSUB_H
#define MPSUB_H

#include "subtitleio.h"
#include "exceptions.h"

class MPSub: public SubtitleIO{

public:
    MPSub(SubtitleApp* app, string s);

    void write() override;
    void read() override;
};

#endif // MPSUB_H
