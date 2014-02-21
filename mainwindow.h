#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QString>

#include "repere.h"
#include "simulation.h"
#include "scenar.h"
#include "sivia.h"
#include "drawPaving.h"
#include "drawf.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void Init();


private:
    Ui::MainWindow *ui;
    repere* R;
    Scenario* senario;
    simulation* Simu;
    Sivia *sivia;

    // Build the frame
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    double str2double(QString s);


protected:
    void resizeEvent(QResizeEvent*);


signals:


private slots:


private slots:
    void on_pushZoomRaz_clicked();
    void on_pushZoomMinus_clicked();
    void on_pushZoomPlus_clicked();
    void on_textg_textChanged();
    void on_textf_textChanged();
    void on_push_run_clicked();
    void on_pushSave_clicked();
    void on_timeBar_valueChanged(int position);
    //void on_tmaxField_valueChanged(int );
    void on_buttonSimu_stateChanged(int );
    void on_buttonPaving_stateChanged(int );
    void on_buttonField_stateChanged(int );
    void drawAll();

    void on_loadfFromFile_clicked();
    void on_loadgFromFile_clicked();
};



#endif // MAINWINDOW_H
