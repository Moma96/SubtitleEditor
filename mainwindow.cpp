#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);
}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::displayCurrSub(){

    if (i == app->getSubs()->afterEnd()) return;
    ui->oSubtitle->setText(QString::fromStdString(i->second->getString()));
    ui->oAppearance->setText(QString::fromStdString(i->second->getTimeOfAppearance().toString()));
    ui->oRemoval->setText(QString::fromStdString(i->second->getTimeOfRemoval().toString()));
}

void MainWindow::displayDoc(){

    if (!app) return;
    ui->oStart->setText(QString::fromStdString(app->getSubs()->begin()->second->getTimeOfAppearance().toString()));
    ui->oEnd->setText(QString::fromStdString(app->getSubs()->end()->second->getTimeOfRemoval().toString()));
    ui->oDuration->setText(QString::fromStdString(app->getSubs()->duration().toString()));
    ui->oFormat->setText(QString::fromStdString(app->getIO()->getFormat()));
    ui->oQuantity->setText(QString::fromStdString(to_string(app->getSubs()->getQuantity())));
}

void MainWindow::on_bStart_clicked(){

    if (app || proc){
        delete app;
        delete proc;
    }
    float fps = atoi(ui->iFps->text().toStdString().c_str());
    string file = ui->iPath->text().toStdString();

    try{
        app = new SubtitleApp(this, file, fps);
        proc = new SubtitleProcessing(app);
    }
    catch(NotSupportedFormat e){
        e.information();
        delete app;
    }
    catch(FileNotFound e){
        e.information();
        delete app;
    }
    catch(FileNotClosed e){
        e.information();
        delete app;
    }

    on_bFirst_clicked();
    displayDoc();
}

void MainWindow::on_bNext_clicked(){

    if (!proc || !app) return;
    if (i == app->getSubs()->afterEnd()) return;
    i = app->getSubs()->next(i);
    displayCurrSub();
}

void MainWindow::on_bPrevious_clicked(){

    if (!proc || !app) return;
    if (i == app->getSubs()->afterEnd()) return;
    i = app->getSubs()->previous(i);
    displayCurrSub();
}

void MainWindow::on_bFirst_clicked(){

    if (!proc || !app) return;
    if (i == app->getSubs()->afterEnd()) return;
    i = app->getSubs()->begin();
    displayCurrSub();
}

void MainWindow::on_bLast_clicked(){

    if (!proc || !app) return;
    if (i == app->getSubs()->afterEnd()) return;
    i = app->getSubs()->end();
    displayCurrSub();
}

void MainWindow::on_bFind_clicked(){

    int h = atoi(ui->iH->text().toStdString().c_str());
    int m = atoi(ui->iM->text().toStdString().c_str());
    int s = atoi(ui->iS->text().toStdString().c_str());
    int ms = atoi(ui->iMS->text().toStdString().c_str());

    Subtitles::SubCont::iterator j;
    try{
        j = app->getSubs()->findClosest(h, m, s, ms);
        if (j == app->getSubs()->afterEnd()) throw BadTimeInput(app->getW());
    }catch(BadTimeInput e){
        e.information();
    }
    i = j;
    displayCurrSub();
}

void MainWindow::on_bReplace_clicked(){

    string s = ui->iSubtitle->text().toStdString();
    if (!proc->editSub.replaceSub(i, s)) return;
    displayCurrSub();
}

void MainWindow::on_bAppend_clicked(){

    string s = ui->iSubtitle->text().toStdString();

    if (!proc->editSub.appendSent(i, s)) return;

    displayCurrSub();
}

void MainWindow::on_bDeleteSent_clicked(){

    string s = ui->iSubtitle->text().toStdString();
    int occ = atoi(ui->iOccurence->text().toStdString().c_str());
    try{
    if (!proc->editSub.deleteSent(i, s, occ)) return;
    }
    catch(BadNumberOfOccur e){
        e.information();
    }
    catch(PosNotFound e){
        e.information();
    }

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bAddSub_clicked(){

    int h1 = atoi(ui->iH_1->text().toStdString().c_str());
    int m1 = atoi(ui->iM_1->text().toStdString().c_str());
    int s1 = atoi(ui->iS_1->text().toStdString().c_str());
    int ms1 = atoi(ui->iMS_1->text().toStdString().c_str());

    int h2 = atoi(ui->iH_2->text().toStdString().c_str());
    int m2 = atoi(ui->iM_2->text().toStdString().c_str());
    int s2 = atoi(ui->iS_2->text().toStdString().c_str());
    int ms2 = atoi(ui->iMS_2->text().toStdString().c_str());

    string sub = ui->iSubtitle->text().toStdString();
    Timestamp t1 = Timestamp::tConvert::getTime(h1, m1, s1, ms1);
    Timestamp t2 = Timestamp::tConvert::getTime(h2, m2, s2, ms2);

    try{
    proc->editSub.addSub(new Subtitle(sub, t1, t2));
    }
    catch(AdditionFailed e){
        e.information();
    }
    i = app->getSubs()->findClosest(t1);

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bDeleteSub_clicked(){

    int h1 = atoi(ui->iH_1->text().toStdString().c_str());
    int m1 = atoi(ui->iM_1->text().toStdString().c_str());
    int s1 = atoi(ui->iS_1->text().toStdString().c_str());
    int ms1 = atoi(ui->iMS_1->text().toStdString().c_str());

    int h2 = atoi(ui->iH_2->text().toStdString().c_str());
    int m2 = atoi(ui->iM_2->text().toStdString().c_str());
    int s2 = atoi(ui->iS_2->text().toStdString().c_str());
    int ms2 = atoi(ui->iMS_2->text().toStdString().c_str());

    Timestamp t1 = Timestamp::tConvert::getTime(h1, m1, s1, ms1);
    Timestamp t2 = Timestamp::tConvert::getTime(h2, m2, s2, ms2);

    try{
        if (t1.getTime() == 0 && t2.getTime() == 0)
            proc->editSub.deleteSub(i);
        else{
            if (t1.getTime() == 0) t1 = app->getSubs()->begin()->second->getTimeOfAppearance();
            if (t2.getTime() == 0) t2 = app->getSubs()->end()->second->getTimeOfRemoval();
                proc->editSub.deleteSubs(t1, t2);
            i = app->getSubs()->begin();
        }
    }
    catch(BadTimeInput e){
        e.information();
    }
    catch(RemovalFailed e){
        e.information();
    }

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bMerge_clicked(){

    int ms = atoi(ui->iMergeMS->text().toStdString().c_str());
    int ch = atoi(ui->iMergeChars->text().toStdString().c_str());

    try{
    proc->editSub.mergeAll(ms, ch);
    }
    catch(BadNumberOfMS e){
        e.information();
    }
    catch(BadNumberOfChars e){
        e.information();
    }

    i = app->getSubs()->begin();

    on_bFirst_clicked();
    displayDoc();
}

void MainWindow::on_bSeparate_clicked(){

    int ch = atoi(ui->iSeparateChars->text().toStdString().c_str());

    try{
        proc->editSub.separateAll(ch);
    }
    catch(BadNumberOfChars e){
        e.information();
    }
    i = app->getSubs()->begin();

    on_bFirst_clicked();
    displayDoc();
}

void MainWindow::on_bTransfer_clicked(){

    int h1 = atoi(ui->iH_1->text().toStdString().c_str());
    int m1 = atoi(ui->iM_1->text().toStdString().c_str());
    int s1 = atoi(ui->iS_1->text().toStdString().c_str());
    int ms1 = atoi(ui->iMS_1->text().toStdString().c_str());

    int h2 = atoi(ui->iH_2->text().toStdString().c_str());
    int m2 = atoi(ui->iM_2->text().toStdString().c_str());
    int s2 = atoi(ui->iS_2->text().toStdString().c_str());
    int ms2 = atoi(ui->iMS_2->text().toStdString().c_str());

    int ms = atoi(ui->iTSms->text().toStdString().c_str());
    bool extr = ui->cExtrapolation->isChecked();

    Timestamp t1 = Timestamp::tConvert::getTime(h1, m1, s1, ms1);
    Timestamp t2 = Timestamp::tConvert::getTime(h2, m2, s2, ms2);

    if (t1.getTime() == 0) t1 = app->getSubs()->begin()->second->getTimeOfAppearance();
    if (t2.getTime() == 0) t2 = app->getSubs()->end()->second->getTimeOfRemoval();
    try{
        proc->editTiming.transfer(t1, t2, ms, extr);
    }catch(BadTimeInput e){
        e.information();
    }
    i = app->getSubs()->findClosest(t1);

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bScaleMS_clicked() {

    int h1 = atoi(ui->iH_1->text().toStdString().c_str());
    int m1 = atoi(ui->iM_1->text().toStdString().c_str());
    int s1 = atoi(ui->iS_1->text().toStdString().c_str());
    int ms1 = atoi(ui->iMS_1->text().toStdString().c_str());

    int h2 = atoi(ui->iH_2->text().toStdString().c_str());
    int m2 = atoi(ui->iM_2->text().toStdString().c_str());
    int s2 = atoi(ui->iS_2->text().toStdString().c_str());
    int ms2 = atoi(ui->iMS_2->text().toStdString().c_str());

    int ms = atoi(ui->iTSms->text().toStdString().c_str());
    bool extr = ui->cExtrapolation->isChecked();

    Timestamp t1 = Timestamp::tConvert::getTime(h1, m1, s1, ms1);
    Timestamp t2 = Timestamp::tConvert::getTime(h2, m2, s2, ms2);

    if (t1.getTime() == 0) t1 = app->getSubs()->begin()->second->getTimeOfAppearance();
    if (t2.getTime() == 0) t2 = app->getSubs()->end()->second->getTimeOfRemoval();
    try{
        proc->editTiming.scaleMS(t1, t2, ms, extr);
    }catch(BadTimeInput e){
        e.information();
    }
    i = app->getSubs()->findClosest(t1);

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bScaleB_clicked(){

    int h1 = atoi(ui->iH_1->text().toStdString().c_str());
    int m1 = atoi(ui->iM_1->text().toStdString().c_str());
    int s1 = atoi(ui->iS_1->text().toStdString().c_str());
    int ms1 = atoi(ui->iMS_1->text().toStdString().c_str());

    int h2 = atoi(ui->iH_2->text().toStdString().c_str());
    int m2 = atoi(ui->iM_2->text().toStdString().c_str());
    int s2 = atoi(ui->iS_2->text().toStdString().c_str());
    int ms2 = atoi(ui->iMS_2->text().toStdString().c_str());

    Timestamp t1 = Timestamp::tConvert::getTime(h1, m1, s1, ms1);
    Timestamp t2 = Timestamp::tConvert::getTime(h2, m2, s2, ms2);

    if (t2.getTime() == 0) t2 = app->getSubs()->end()->second->getTimeOfRemoval();
    try{
        proc->editTiming.scaleBetween(t1, t2);
    }catch(BadTimeInput e){
        e.information();
    }
    i = app->getSubs()->begin();

    displayCurrSub();
    displayDoc();
}

void MainWindow::on_bSave_clicked(){

    proc->save();
}

void MainWindow::closeEvent (QCloseEvent *event){

    if (!app) QApplication::exit();
    QMessageBox::StandardButton btn = QMessageBox::question( this, "", tr("Do you want to save changes?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (btn == QMessageBox::Yes) {
        proc->save();
        delete proc;
        delete app;
        event->accept();
    }
    else if (btn == QMessageBox::No){
        delete proc;
        delete app;
        event->accept();
    }
    else event->ignore();
}
