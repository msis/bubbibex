#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 1.0;
}


void simulation::simuMonteCarlo(repere* R,int NB)
{
    //Genere les positions x1,x2 aleatoirement (methode de Monte Carlo)
    double dt = 0.01;
    double t = 0;
    double x1, x2, x3;
    x1 = rand()% 20 - 10;
    x2 = rand()% 20 - 10;
    x3 = rand()%10 - 5;

    //Transforme les doubles en intervals pour computer les
    IntervalVector box(4);
    box[0] = Interval(x1);
    box[1] = Interval(x2);
    box[2] = Interval(x3);
    box[3] = Interval(t);

    for (double i=0 ; i<NB ;i++){
        data.push_back(box);
        box = box + dt*fonct_f.eval_vector(box);
        box[3] = Interval(t+dt);
    }

}

void simulation::drawtraj(repere* R){
    IntervalVector cur(4);
    IntervalVector next(4);
    for(int i;i<data.size();i++){
        cur=data[i];
        next=data[i+1];
        R->DrawLine(cur[0].mid(),cur[1].mid(),next[0].mid(),next[1].mid(),QPen(Qt::black));
    }

}

void simulation::drawrob(repere* R,double t){
    IntervalVector current(4);
    double x,y,theta;
    t_trackbar = t;
    current=data[int(t_trackbar/dt)];
    x = current[0].mid();
    y = current[1].mid();
    theta = current[2].mid();
    R->DrawRobot(x,y,theta);
}
