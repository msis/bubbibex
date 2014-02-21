#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtScript/qscriptengine.h"
#include "qdebug.h"

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

    R = ui->graphicsView;
    R->setDrawingArea(xmin,xmax,ymin,ymax);
    R->Scene->setSceneRect(0,0,R->geometry().width()-3,R->geometry().height()-3);


    ui->graphicsView->setMouseTracking(true);

    connect(R,SIGNAL(repaint_all()),this,SLOT(drawAll()));

    //Scenario
    senario = new Scenario();
    QString sf,sg;
    senario->load(sf,sg);


    ui->textf->setPlainText(sf);
    ui->textg->setPlainText(sg);


    //Simulation
    Function f("f.txt");
    Function g("g.txt");
    Variable x;

    Simu = new simulation(f,g);
    ui->timeBar->setMaximum(ui->tmaxField->value()-1);
    Simu->simuMonteCarlo(1000);

    //Intervalles
    sivia = NULL;
    on_push_runSivia_clicked();
    drawAll();

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
}

double MainWindow::str2double(QString s){

    QScriptEngine e;
    s.replace(QRegExp("PI"),"Math.PI");
    QScriptValue v = e.evaluate(s);
    return v.toNumber();
}

QString interval2String(Interval &i){
    QString s;
    s+= "[" + QString::number(i.lb()) + "," + QString::number(i.ub()) + "]";
    return s;
}

void MainWindow::on_push_runSivia_clicked()
{
    QScriptEngine e;
    double _box[4][2];
    _box[0][0] = (ui->x_min->text()).toDouble();
    _box[0][1] = (ui->x_max->text()).toDouble();
    _box[1][0] = (ui->y_min->text()).toDouble();
    _box[1][1] = (ui->y_max->text()).toDouble();
    _box[2][0] = str2double(ui->th_min->text());
    _box[2][1] = str2double(ui->th_max->text());
    _box[3][0] = (ui->t_min->text()).toDouble();
    _box[3][1] = (ui->t_max->text()).toDouble();

    if(sivia!=NULL) delete sivia;

    IntervalVector box(4, _box);
    //cout << box;

    QTime t;
    QString info;


    t.start();
    sivia = new Sivia(*R,ui->epsilonBox->value(), box);
    double tsiv = t.elapsed()/1000.0;

    info += "Elapsed time: " + QString::number(tsiv) + " s\n";

    info += "\nInitial box:\n\tx:\t[" + QString::number(_box[0][0]) + "," + QString::number(_box[0][1]) + "]\n";
    info += "\ty:\t[" + QString::number(_box[1][0]) + "," + QString::number(_box[1][1]) + "]\n";
    info += "\ttheta:\t[" + QString::number(_box[2][0]) + "," + QString::number(_box[2][1]) + "]\n";
    info += "\tt:\t[" + QString::number(_box[3][0]) + "," + QString::number(_box[3][1]) + "]\n";
    info += "\tepsilon: " + QString::number(ui->epsilonBox->value()) + "\n";

    info += "\nNumber of boxes: " + QString::number(sivia->Sout.size()+sivia->Sp.size());
    info += "\nUnsafe boxes: " + QString::number(sivia->Sp.size());

    QMessageBox::information(this,"Sivia report",info);

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


