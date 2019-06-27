#include "mpsub.h"

MPSub::MPSub(SubtitleApp* app, string s): SubtitleIO(app,s,"MPlayer") {}

void MPSub::read(){

    open();
    double t1, t2, sum = 0;
    string str;

    while (1){
        if (!(fs >> t1 >> t2)) break;
        if (!(getline(fs, str))) break;
        if (!(getline(fs, str))) break;
        string nstr=str;
        while(1){
            if (!(getline(fs, nstr))) break;
            if (nstr=="") break;
            str+="\n"+nstr;
        }
        if (t1<0 || t2<0) {
            BadFormat b(app->getW());
            if (b.question()==true)
                break;
            else{
                app->getSubs()->removeAll();
                break;
            }
        }
        Timestamp tm1(t1,sum);
        sum+=t1;
        Timestamp tm2(t2,sum);
        sum+=t2;
        if (!app->getSubs()->add(new Subtitle(str, tm1, tm2))) break; // throw Exception
    }
    close();
}

void MPSub::write(){

    open();
    fs.clear();
    double sum = 0;
    for (Subtitles::SubCont::iterator i = app->getSubs()->begin(); i != app->getSubs()->afterEnd(); i++){
        fs << Timestamp::tDeconvert::getSubTime(i->second->getTimeOfAppearance().getTime(), sum) << ' ';
        sum += Timestamp::tDeconvert::getSubTime(i->second->getTimeOfAppearance().getTime(), sum);
        fs << Timestamp::tDeconvert::getSubTime(i->second->getTimeOfRemoval().getTime(), sum) << '\n';
        sum += Timestamp::tDeconvert::getSubTime(i->second->getTimeOfRemoval().getTime(), sum);
        fs << i->second->getString() << '\n';
        fs << '\n';
    }
    close();
}
