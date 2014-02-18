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

    this->show();

    //R = new repere(this,ui->graphicsView,xmin,xmax,ymin,ymax);
    R = ui->graphicsView;
    R->setDrawingArea(xmin,xmax,ymin,ymax);
    R->Scene->setSceneRect(0,0,R->geometry().width()-3,R->geometry().height()-3);
    R->DrawBox(xmin,xmax,ymin,ymax,QPen(Qt::blue),QBrush(Qt::NoBrush));


    ui->graphicsView->setMouseTracking(true);

    connect(R,SIGNAL(repaint_all()),this,SLOT(drawAll()));

    //Scenario
    senario = new Scenario();
    QString sf,sg;
    senario->load(sf,sg);

//    qDebug() << sf;
//    qDebug() << sg;
    ui->textf->setPlainText(sf);
    ui->textg->setPlainText(sg);
//    ui->textc->setPlainText(senario->initc());
//    senario->save(senario->initf(), senario->initg(), senario->initc());

    //Simulation
    Function f("f.txt");
    Function g("g.txt");
    Variable x;

    Simu = new simulation(f,g);
    ui->timeBar->setMaximum(ui->tmaxField->value()-1);
    Simu->simuMonteCarlo(1000);

    //Intervalles
    sivia = new Sivia(*R,0.3);

    //Pavage

}

MainWindow::~MainWindow() {
    delete sivia;
    delete senario;
    delete Simu;
//    delete R;
    delete ui;

}

//Gestion redimensionnement
void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    if(R!=NULL && this->isVisible()){
        R->Scene->setSceneRect(0,0,R->geometry().width()-3,R->geometry().height()-3);
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
    Simu->simuMonteCarlo(ui->timeBar->maximum()+1);
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
    senario->save(ui->textf->toPlainText(),
                  ui->textg->toPlainText());
//                  ui->textc->toPlainText());
}


//Fonction d'affichage
void MainWindow::drawAll(){
    double t = ui->timeBar->value();
    ui->curTime->setText(QString::number(t*Simu->dt));
    R->Clean();

    //Drawing Paving if box checked
    if(ui->buttonPaving->isChecked()){
        drawPaving(sivia->Sout,sivia->Sp,t*Simu->dt,*R);
    }

    //Drawing Simulation if box checked
    if(ui->buttonSimu->isChecked()){
        Simu->drawtraj(R);
        Simu->drawrob(R,t);
    }

    //Drawing Field if box checked
    if(ui->buttonField->isChecked()){
        Drawf(sivia->Sp,t*Simu->dt,*R);
    }
}

