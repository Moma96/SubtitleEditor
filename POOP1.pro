#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T21:57:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = POOP1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    subtitleapp.cpp \
    subtitleio.cpp \
    subtitles.cpp \
    subtitle.cpp \
    timestamp.cpp \
    subtitleprocessing.cpp \
    srt.cpp \
    microdvd.cpp \
    mpsub.cpp \
    exceptions.cpp

HEADERS  += mainwindow.h \
    subtitleapp.h \
    subtitleio.h \
    subtitles.h \
    subtitle.h \
    timestamp.h \
    subtitleprocessing.h \
    srt.h \
    microdvd.h \
    mpsub.h \
    exceptions.h

FORMS    += mainwindow.ui
