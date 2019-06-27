#include "exceptions.h"

ErrorWindow::ErrorWindow(MainWindow* w): w(w) {}

bool ErrorWindow::question(const char* s){

    QMessageBox::StandardButton btn = QMessageBox::question( w, "", MainWindow::tr(s),
                                                             QMessageBox::Yes | QMessageBox::No,
                                                             QMessageBox::Yes);
    if (btn == QMessageBox::Yes) {
        return true;
    }
    else if (btn == QMessageBox::No){
        return false;
    }
    return false;
}

void ErrorWindow::information(const char* s){

    QMessageBox::StandardButton btn = QMessageBox::information( w, "", MainWindow::tr(s),
                                                                QMessageBox::Ok,
                                                                QMessageBox::Ok);
    if (btn == QMessageBox::Ok)
        return;
    return;
}


BadFormat::BadFormat(MainWindow* w): ErrorWindow(w) {}

bool BadFormat::question(){
    return ErrorWindow::question("Unrecognizable sentence appeared in the document.\nDo you want to modify what is loaded? (No - abort)\n");
}


NotSupportedFormat::NotSupportedFormat(MainWindow* w): ErrorWindow(w) {}

void NotSupportedFormat::information(){
    return ErrorWindow::information("Unrecognized format.\nPlease change the input file.\n");
}


FileNotFound::FileNotFound(MainWindow* w): ErrorWindow(w) {}

void FileNotFound::information(){
    return ErrorWindow::information("File is not found.\n");
}


FileNotClosed::FileNotClosed(MainWindow* w): ErrorWindow(w) {}

void FileNotClosed::information(){
    return ErrorWindow::information("File was not closed for some reason.\n");
}


BadTimeInput::BadTimeInput(MainWindow *w): ErrorWindow(w) {}

void BadTimeInput::information(){
    return ErrorWindow::information("Inserted values for time are not valid.\nOnly positive values are accepted.\n");
}

TOAisAfterTOR::TOAisAfterTOR(MainWindow *w): ErrorWindow(w) {}

void TOAisAfterTOR::information(){
    return ErrorWindow::information("Time of appearance is before time of removal.\n");
}

BadNumberOfChars::BadNumberOfChars(MainWindow* w): ErrorWindow(w) {}

void BadNumberOfChars::information(){
    return ErrorWindow::information("Inserted value for number of characters is not valid.\nOnly positive values are accepted.\n");
}


BadNumberOfMS::BadNumberOfMS(MainWindow* w): ErrorWindow(w) {}

void BadNumberOfMS::information(){
    return ErrorWindow::information("Inserted values for miliseconds is not valid.\nOnly positive values are accepted.\n");
}


BadNumberOfOccur::BadNumberOfOccur(MainWindow* w): ErrorWindow(w) {}

void BadNumberOfOccur::information(){
    return ErrorWindow::information("Inserted values for occurence is not valid.\nOnly positive values are accepted.\n");
}

AdditionFailed::AdditionFailed(MainWindow* w): ErrorWindow(w) {}

void AdditionFailed::information(){
    return ErrorWindow::information("Addition failed.\n");
}

RemovalFailed::RemovalFailed(MainWindow* w): ErrorWindow(w) {}

void RemovalFailed::information(){
    return ErrorWindow::information("There is no more subtitles.\n");
}

PosNotFound::PosNotFound(MainWindow* w): ErrorWindow(w) {}

void PosNotFound::information(){
    return ErrorWindow::information("There is no more elements.\n");
}
