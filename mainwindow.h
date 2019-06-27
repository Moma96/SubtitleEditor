#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "subtitleapp.h"
#include "subtitleprocessing.h"
#include "exceptions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bStart_clicked();

    void on_bLast_clicked();

    void on_bFirst_clicked();

    void on_bPrevious_clicked();

    void on_bNext_clicked();

    void on_bFind_clicked();

    void on_bReplace_clicked();

    void on_bAppend_clicked();

    void on_bDeleteSent_clicked();

    void on_bDeleteSub_clicked();

    void on_bMerge_clicked();

    void on_bSeparate_clicked();

    void on_bTransfer_clicked();

    void on_bScaleB_clicked();

    void on_bScaleMS_clicked();

    void on_bSave_clicked();

    void on_bAddSub_clicked();

    void closeEvent (QCloseEvent *event);

private:
    void displayCurrSub();
    void displayDoc();

    Ui::MainWindow* ui;
    SubtitleApp* app = nullptr;
    SubtitleProcessing* proc = nullptr;
    Subtitles::SubCont::iterator i;
};

#endif // MAINWINDOW_H
