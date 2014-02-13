#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 1.0;
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
    IntervalVector curf(4);
    IntervalVector nextf(4);
    IntervalVector curg(4);
    IntervalVector nextg(4);
    for(int i=0;i<dataf.size()-1;i++){
        curf=dataf[i];
        nextf=dataf[i+1];
        curg=datag[i];
        nextg=datag[i+1];
        R->DrawLine(curf[0].mid(),curf[1].mid(),nextf[0].mid(),nextf[1].mid(),QPen(Qt::blue));
        R->DrawLine(curg[0].mid(),curg[1].mid(),nextg[0].mid(),nextg[1].mid(),QPen(Qt::green));
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
    R->Center(x,y);
    R->DrawRobot(x,y,theta);
    R->DrawEllipse(cx,cy,Ra,QPen(Qt::green),QBrush(Qt::NoBrush));

}
