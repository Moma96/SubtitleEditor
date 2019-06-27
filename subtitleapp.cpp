#include "subtitleapp.h"
#include "srt.h"
#include "microdvd.h"
#include "mpsub.h"


SubtitleApp::SubtitleApp(MainWindow* w, string f, float fps): w(w) { //throw NotSupportedFormat, notopened

    string ext = SubtitleIO::getExtension(f);
         if(ext == "srt") io = new SRT(this, f);
    else if(ext == "sub") io = new MPSub(this, f);
    else if(ext == "txt") io = new MicroDVD(this, f, fps);
    else throw NotSupportedFormat(w);

    subs = new Subtitles();
    io->read();
}

SubtitleApp::~SubtitleApp(){

    delete subs;
    delete io;
}

SubtitleIO* SubtitleApp::getIO() const{

    return io;
}

Subtitles* SubtitleApp::getSubs() const{

    return subs;
}

MainWindow* SubtitleApp::getW() const{

    return w;
}
