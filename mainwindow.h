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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void Init();
    void drawAll();

private:
    Ui::MainWindow *ui;
    repere* R;
    scenar* Sce;
    simulation* Simu;
    Sivia *sivia;



protected:
    void resizeEvent(QResizeEvent*);

signals:


private slots:


private slots:
    void on_pushButton_clicked();
    void on_timeBar_valueChanged(int position);
    void on_tmaxField_valueChanged(int );
    void on_buttonSimu_stateChanged(int );
    void on_buttonPaving_stateChanged(int );
    void on_buttonField_stateChanged(int );
};



#endif // MAINWINDOW_H
