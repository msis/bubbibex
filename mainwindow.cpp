#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ibex.h"
#include "sivia.h"


MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow),
    xmin(-10), xmax(10), ymin(-10), ymax(10)
{
    ui->setupUi(this);
    Init();
}

void MainWindow::Init() {
    ui->timeBar->setMaximum(ui->tmaxField->value()-1);

    this->show();

    R = new repere(this,ui->graphicsView,xmin,xmax,ymin,ymax);
    R->DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::blue),QBrush(Qt::NoBrush));

    //Scenario
    senario = new Scenario();
    ui->textf->setPlainText(senario->initf());
    ui->textg->setPlainText(senario->initg());
    ui->textc->setPlainText(senario->initc());
    senario->save(senario->initf(), senario->initg(), senario->initc());

    //Simulation
    Function f("f.txt");
//    Function g("g.txt");
    Variable x;
    Function g(x,Return(7*x,sin(0.1*x)));
    Simu = new simulation(f,g);
    Simu->simuMonteCarlo(R, 1000);

    //Intervalles
    sivia = new Sivia(*R,0.1);

    //Pavage

}

MainWindow::~MainWindow() {
    delete sivia;
    delete senario;
    delete Simu;
    delete R;
    delete ui;

}

//Gestion redimensionnement
void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);



    if(R!=NULL && this->isVisible()){
        R->Scene->setSceneRect(0,0,ui->graphicsView->geometry().width()-3,ui->graphicsView->geometry().height()-3); 
        drawAll();
        R->DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::blue),QBrush(Qt::NoBrush));
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
    ui->timeBar->setMaximum(ui->tmaxField->value()-1);
    R->Clean();
    Simu->simuMonteCarlo(R, ui->timeBar->maximum()+1);
    if(ui->buttonSimu->isChecked()){       
        Simu->drawtraj(R);
        R->Center(0,0);
    }

}

void MainWindow::on_timeBar_valueChanged(int position)
{
    drawAll();
}

void MainWindow::on_pushButton_clicked()
{
    senario->save(senario->initf(), senario->initg(), senario->initc());
}


//Fonction d'affichage
void MainWindow::drawAll(){
    double t = ui->timeBar->value();
    ui->curTime->setText(QString::number(t));
    R->Clean();

    //Drawing Paving if box checked
    if(ui->buttonPaving->isChecked()){
        drawPaving(sivia->Sout,sivia->Sp,t/100.0,*R);
    }

    //Drawing Simulation if box checked
    if(ui->buttonSimu->isChecked()){
        Simu->drawtraj(R);
        Simu->drawrob(R,t);
    }

    //Drawing Field if box checked
    if(ui->buttonField->isChecked()){

    }
}

