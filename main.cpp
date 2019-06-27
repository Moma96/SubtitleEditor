#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(690 ,802);
    w.show();

    return a.exec();
}
