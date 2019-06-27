#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<iostream>
#include<string>
#include<exception>
#include"mainwindow.h"

using namespace std;

class ErrorWindow: public exception {
public:
    ErrorWindow(MainWindow* w);
    bool question(const char* s);
    void information(const char* s);

protected:
    MainWindow* w;
};

class BadFormat: public ErrorWindow {
public:
    BadFormat(MainWindow* w);
    bool question();
};

class NotSupportedFormat: public ErrorWindow {
public:
    NotSupportedFormat(MainWindow* w);
    void information();
};

class FileNotFound: public ErrorWindow {
public:
    FileNotFound(MainWindow* w);
    void information();
};

class FileNotClosed: public ErrorWindow {
public:
    FileNotClosed(MainWindow* w);
    void information();
};


class BadTimeInput: public ErrorWindow {
public:
    BadTimeInput(MainWindow* w);
    void information();
};

class TOAisAfterTOR: public ErrorWindow {
public:
    TOAisAfterTOR(MainWindow* w);
    void information();
};

class BadNumberOfChars: public ErrorWindow {
public:
    BadNumberOfChars(MainWindow* w);
    void information();
};

class BadNumberOfMS: public ErrorWindow {
public:
    BadNumberOfMS(MainWindow* w);
    void information();
};

class BadNumberOfOccur: public ErrorWindow {
public:
    BadNumberOfOccur(MainWindow* w);
    void information();
};


class AdditionFailed: public ErrorWindow {
public:
    AdditionFailed(MainWindow* w);
    void information();
};

class RemovalFailed: public ErrorWindow {
public:
    RemovalFailed(MainWindow* w);
    void information();
};

class PosNotFound: public ErrorWindow {
public:
    PosNotFound(MainWindow* w);
    void information();
};

#endif // EXCEPTIONS_H
