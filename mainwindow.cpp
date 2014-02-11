#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ibex.h"
#include "sivia.h"



MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    Init();
}

void MainWindow::Init() {
    ui->timeBar->setMaximum(ui->tmaxField->value());
}

MainWindow::~MainWindow() {
    delete ui;
}

//Table d'evenements
void MainWindow::on_buttonField_stateChanged(int state)
{
    drawAll();
}

void MainWindow::on_buttonPaving_stateChanged(int state)
{
    drawAll();
}

void MainWindow::on_buttonSimu_stateChanged(int state)
{
    drawAll();
}

void MainWindow::on_tmaxField_valueChanged(int value)
{
    ui->timeBar->setMaximum(ui->tmaxField->value());
}

void MainWindow::on_timeBar_valueChanged(int position)
{
    drawAll();
}

//Fonction d'affichage
void MainWindow::drawAll(){
    double t = ui->timeBar->value();
    ui->curTime->setText(QString::number(t));

    //Drawing Paving if box checked
    if(ui->buttonPaving->isChecked()){
        //TO DO
    }

    //Drawing Simulation if box checked
    if(ui->buttonSimu->isChecked()){
        //TO DO
    }

    //Drawing Field if box checked
    if(ui->buttonField->isChecked()){
        //TO DO
    }
}
