#include "microdvd.h"

MicroDVD::MicroDVD(SubtitleApp* app, string s, double f): SubtitleIO(app,s,"MicroDVD"), fps(f) {}

void MicroDVD::read(){

    open();
    long t1, t2;
    char brckt1, brckt2, brckt3, brckt4;
    string str;

    while (1){
        if (!(fs >> brckt1 >> t1 >> brckt2 >> brckt3 >> t2 >> brckt4)) break;
        if (!(getline(fs, str))) break;
        replace( str.begin(), str.end(), '|', '\n');
        string s=""; if (s+brckt1+brckt2+brckt3+brckt4 != "{}{}"){
            BadFormat b(app->getW());
            if (b.question()==true)
                break;
            else{
                app->getSubs()->removeAll();
                break;
            }
        }
        if (!app->getSubs()->add(new Subtitle(str, Timestamp(t1,fps), Timestamp(t2,fps)))) break; // throw Exception
    }
    close();
}

void MicroDVD::write(){

    open();
    fs.clear();
    for (Subtitles::SubCont::iterator i = app->getSubs()->begin(); i != app->getSubs()->afterEnd(); i++){
        fs << '{' << Timestamp::tDeconvert::getFpsTime(i->second->getTimeOfAppearance().getTime(),fps) << '}';
        fs << '{' << Timestamp::tDeconvert::getFpsTime(i->second->getTimeOfRemoval().getTime(),fps) << '}';
        string str = i->second->getString();
        replace( str.begin(), str.end(), '\n', '|');
        fs << str << '\n';
    }
    close();
}
