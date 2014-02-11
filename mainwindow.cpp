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

    this->show();

    // Build the frame
    double xmin=-10;
    double xmax=10;
    double ymin=-10;
    double ymax=10;

    R = new repere(this,ui->graphicsView,xmin,xmax,ymin,ymax);
    R->DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::blue),QBrush(Qt::NoBrush));

    //Scenario
    //TO DO

    //Simulation
    S = new simulation(/*f*/,/*g*/); //TO DO

    //Intervalles


    //Pavage

}

MainWindow::~MainWindow() {
    delete ui;
}

//Gestion redimensionnement
void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);

    // Build the frame
    double xmin=-10;
    double xmax=10;
    double ymin=-10;
    double ymax=10;

    if(R!=NULL && this->isVisible()){
        R->Scene->setSceneRect(0,0,ui->graphicsView->geometry().width()-3,ui->graphicsView->geometry().height()-3);
        R->Clean();
        R->DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::blue),QBrush(Qt::NoBrush));

        drawAll();
    }
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
        S->drawrob(R, t);
    }

    //Drawing Field if box checked
    if(ui->buttonField->isChecked()){
        //TO DO
    }
}
