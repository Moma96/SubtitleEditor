#include "subtitleio.h"
#include "exceptions.h"

SubtitleIO::SubtitleIO(SubtitleApp* app, string f, string form): app(app), name(f), format(form){}

void SubtitleIO::open(){//throw FileNotOpened

    fs.open(name);
    if (!fs.is_open()) throw FileNotFound(app->getW());
}

void SubtitleIO::close(){//throw filenotclosed

    fs.close();
    if (fs.is_open()) throw FileNotClosed(app->getW());
}

string SubtitleIO::getFormat() const {

    return format;
}

string SubtitleIO::getExtension(string f, int n){

    reverse(f.begin(), f.end());
    f = f.substr(0, n);
    reverse(f.begin(), f.end());
    return f;
}
