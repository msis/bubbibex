#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 1.0;
}


void simulation::simuMonteCarlo(repere& R)
{
    double x1, x2;
    x1 = rand()% 20 - 10 ;
    x2 = rand()% 20 - 10;

    IntervalVector box(3);
    box[0] = Interval(x1);
    box[1] = Interval(x2);
    box[2] = Interval(0.0);

    IntervalVector boxOut(3);
    boxOut[0] = Interval(x1);
    boxOut[1] = Interval(x2);
    boxOut[2] = Interval(0.0);

    for (double i=0 ; i<1000 ;i=i+dt){
        box[2] = i;
        data.push_back(boxOut);
        Interval xPrec = boxOut[0];
        Interval yPrec = boxOut[1];
        boxOut = fonct_f.eval_vector(box);
        R.DrawLine(xPrec.mid(),yPrec.mid(),boxOut[0].mid(),boxOut[1].mid(),QPen(Qt::black));
    }

}

void simulation::drawrob(repere& R,double t){
    IntervalVector current;
    double x,y;
    t_trackbar = t;


    current=data[int(t_trackbar/dt)];
    y=current[0].mid();
    x = current[1].mid();
    R.DrawRobot(x,y,0);
}
