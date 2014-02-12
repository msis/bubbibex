#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 0.05;
}


int simulation::mainOde()
{
    OdeSimulation odesim(&fonct_f);
    dataf.clear();datag.clear();
    state_type x = { 10.0 , 1.0 , 1.0 }; // initial conditions
    double x1, x2, x3;
    x_vec.clear(); times.clear();
    x1 = rand()% 20 - 10;
    x2 = rand()% 20 - 10;
    x3 = ((double)rand()/RAND_MAX) *M_PI - M_PI_2;
    x[0] = x1; x[1] = x2; x[2] = x3;
    x_vec.push_back(x);
//    int nbStep =  integrate( odesim , x , 0.0 , 100.0 , dt, push_back_state_and_time( x_vec , times ));

//    double  t = 0;
    runge_kutta4< state_type > stepper;

    //Box pour f
    IntervalVector boxf(4);
    boxf[0] = Interval(x1);
    boxf[1] = Interval(x2);
    boxf[2] = Interval(x3);
    boxf[3] = Interval(t);

    //Box pour g
    IntervalVector boxg(2);
//    boxg[0] = Interval(x1);
//    boxg[1] = Interval(x2);
//    boxg[2] = Interval(x3);
//    boxg[3] = Interval(t);




//    for (double i=0 ; i<x_vec.size() ;i++){
    for (double t = 0; t < 100; t+=dt){
        x = x_vec.back();
        stepper.do_step( odesim , x , t , dt );
        x_vec.push_back(x);
        times.push_back(t);
        boxf[3] = Interval(t);
        IntervalVector bg(1,boxf[3]);
        dataf.push_back(boxf);
        datag.push_back(boxg);
        boxf = boxf + dt*fonct_f.eval_vector(boxf);
        boxg = fonct_g.eval_vector(bg);
        boxf[3] = Interval(t);
    }

//    qDebug() << "size "<< dataf.size() << x_vec.size();

}




void simulation::simuMonteCarlo(repere* R,int NB)
{
    dataf.clear();datag.clear();
    //Genere les positions x1,x2 aleatoirement (methode de Monte Carlo)
    double dt = 0.001;
    double t = 0;
    double x1, x2, x3;
    x1 = rand()% 20 - 10;
    x2 = rand()% 20 - 10;
    x3 = rand()%10 - 5;

    //Box pour f
    IntervalVector boxf(4);
    boxf[0] = Interval(x1);
    boxf[1] = Interval(x2);
    boxf[2] = Interval(x3);
    boxf[3] = Interval(t);

    //Box pour g
    IntervalVector boxg(2);
//    boxg[0] = Interval(x1);
//    boxg[1] = Interval(x2);
//    boxg[2] = Interval(x3);
//    boxg[3] = Interval(t);




    for (double i=0 ; i<NB ;i++){
        IntervalVector bg(1,boxf[3]);
        dataf.push_back(boxf);
        datag.push_back(boxg);
        boxf = boxf + dt*fonct_f.eval_vector(boxf);
        boxg = fonct_g.eval_vector(bg);
        t += dt;
        boxf[3] = Interval(t);
    }

}

void simulation::drawtraj(repere* R){
    //if(x_vec.size() < 2) return ;
    qDebug() << "size of x_vect " << x_vec.size() << dataf.size();
    IntervalVector curf(4);
    IntervalVector nextf(4);
    IntervalVector curg(4);
    IntervalVector nextg(4);
    for(int i=1;i<x_vec.size()-1;i++){
        curf=dataf[i-1];
        nextf=dataf[i];
        curg=datag[i-1];
        nextg=datag[i];
        R->DrawLine(curf[0].mid(),curf[1].mid(),nextf[0].mid(),nextf[1].mid(),QPen(Qt::blue));
       // R->DrawLine(curg[0].mid(),curg[1].mid(),nextg[0].mid(),nextg[1].mid(),QPen(Qt::green));

        R->DrawLine(x_vec[i-1][0],x_vec[i-1][1], x_vec[i][0],x_vec[i][1], QPen(Qt::red));
    }

    R->DrawEllipse(x_vec[0][0],x_vec[0][1],1, QPen(Qt::green), QBrush(Qt::green));

}

void simulation::drawrob(repere* R,double t){
//    IntervalVector currentf(4);
//    IntervalVector currentg(4);
//    double x,y,theta,cx,cy;
//    double Ra = 1;//Radius of the target
//    t_trackbar = t;
//    currentf=dataf[int(t_trackbar/dt)];
//    currentg=datag[int(t_trackbar/dt)];
//    x = currentf[0].mid();
//    y = currentf[1].mid();
//    cx = currentg[0].mid();
//    cy = currentg[1].mid();
//    theta = currentf[2].mid();
//    R->Center(x,y);
//    R->DrawRobot(x,y,theta);
//    R->DrawEllipse(cx,cy,Ra,QPen(Qt::green),QBrush(Qt::NoBrush));

}


void OdeSimulation::operator()(const state_type &x, state_type &dxdt, const double t)
{
        //Box pour f
        IntervalVector boxf(4);
        boxf[0] = Interval(x[0]);
        boxf[1] = Interval(x[1]);
        boxf[2] = Interval(x[2]);
        boxf[3] = Interval(t);

        IntervalVector boxdf = f->eval_vector(boxf);

        dxdt[0] = boxdf[0].mid();
        dxdt[1] = boxdf[1].mid();
        dxdt[2] = boxdf[2].mid();

}
