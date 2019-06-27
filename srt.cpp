#include "srt.h"

SRT::SRT(SubtitleApp* app, string s): SubtitleIO(app,s,"SubRip") {}

void SRT::read(){

    open();
    int no, h1, m1, s1, ms1;
    int h2, m2, s2, ms2;
    char col1, col2, comm1;
    char col3, col4, comm2;
    string arrow, str;

    while (1){
        if (!(fs >> no >> h1 >> col1 >> m1 >> col2 >> s1 >> comm1 >> ms1 >> arrow >> h2 >> col3 >> m2 >> col4 >> s2 >> comm2 >> ms2)) break;
        if (!(getline(fs, str))) break;
        if (!(getline(fs, str))) break;
        string nstr=str;
        while(1){
            if (!(getline(fs,nstr))) break;
            if (nstr=="") break;
            str+="\n"+nstr;
        }
        if (arrow+col1+col2+col3+col4+comm1+comm2 != "-->::::,,"){
            BadFormat b(app->getW());
            if (b.question()==true)
                break;
            else{
                app->getSubs()->removeAll();
                break;
            }
        }
        if (!app->getSubs()->add(new Subtitle(str, Timestamp(h1, m1, s1, ms1), Timestamp(h2, m2, s2, ms2)))) break; // throw Exception
    }
    close();
}

void SRT::write(){

    open();
    int no = 1;
    for (Subtitles::SubCont::iterator i = app->getSubs()->begin(); i != app->getSubs()->afterEnd(); i++, no++){
        fs << no << '\n';
        fs << i->second->getTimeOfAppearance().toString() << " --> " << i->second->getTimeOfRemoval().toString() << '\n';
        fs << i->second->getString() << '\n';
        fs << '\n';
    }
    close();
}
