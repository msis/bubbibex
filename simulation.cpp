#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 1.0;
}


void simulation::simuMonteCarlo(repere* R,int NB)
{
    dataf.empty();datag.empty();
    //Genere les positions x1,x2 aleatoirement (methode de Monte Carlo)
    double dt = 0.01;
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
    IntervalVector boxg(4);
    boxg[0] = Interval(x1);
    boxg[1] = Interval(x2);
    boxg[2] = Interval(x3);
    boxg[3] = Interval(t);


    for (double i=0 ; i<NB ;i++){
        dataf.push_back(boxf);
        datag.push_back(boxg);
        boxf = boxf + dt*fonct_f.eval_vector(boxf);
        boxg = boxg + dt*fonct_g.eval_vector(boxg);
        boxf[3] = Interval(t+dt);
        boxg[3] = Interval(t+dt);
    }

}

void simulation::drawtraj(repere* R){
    IntervalVector cur(4);
    IntervalVector next(4);
    for(int i;i<dataf.size();i++){
        cur=dataf[i];
        next=dataf[i+1];
        R->DrawLine(cur[0].mid(),cur[1].mid(),next[0].mid(),next[1].mid(),QPen(Qt::black));

    }

}

void simulation::drawrob(repere* R,double t){
    IntervalVector currentf(4);
    IntervalVector currentg(4);
    double x,y,theta,cx,cy;
    double Ra = 1;//Radius of the target
    t_trackbar = t;
    currentf=dataf[int(t_trackbar/dt)];
    currentg=datag[int(t_trackbar/dt)];
    x = currentf[0].mid();
    y = currentf[1].mid();
    cx = currentg[0].mid();
    cy = currentg[1].mid();
    theta = currentf[2].mid();
    R->DrawRobot(x,y,theta);
    R->DrawEllipse(cx,cy,Ra,QPen(Qt::black),QBrush(Qt::NoBrush));
}
