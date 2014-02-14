#include "simulation.h"

simulation::simulation(Function& f, Function& g): fonct_f(f), fonct_g(g)
{
    t_trackbar = 0.0;
    dt = 0.01;
}


void simulation::simuMonteCarlo(repere* R,int NB)
{
    dataf.clear();//Nettoie la liste de positions

    //Genere les positions x1,x2 aleatoirement (methode de Monte Carlo)
    double t = 0;
    double x1, x2, x3;
    int flag = 0;

    //On verifie qu'on est bien dans la bulle de départ G0
    while(flag!=1)
    {
        x1 = (rand()% 2000 - 1000)/1000.0;
        x2 = (rand()% 2000 - 1000)/1000.0;
        x3 = (rand()% 1000 - 500)/100.0;

        IntervalVector box(4);
        box[0] = Interval(x1);
        box[1] = Interval(x2);
        box[2] = Interval(x3);
        box[3] = Interval(t);
        cout<<fonct_g.eval_vector(box)[0].mid();
        cout<<fonct_g.eval_vector(box)[0];
        if(fonct_g.eval_vector(box)[0].mid() <= 0 && fonct_g.eval_vector(box)[1].mid()<=0 )
            flag = 1;
    }



    //Box pour f
    IntervalVector boxf(4);
    boxf[0] = Interval(x1);
    boxf[1] = Interval(x2);
    boxf[2] = Interval(x3);
    boxf[3] = Interval(t);


    for (double i=0 ; i<NB ;i++){
        dataf.push_back(boxf);
        boxf = boxf + dt*fonct_f.eval_vector(boxf);
        t += dt;
        boxf[3] = Interval(t);
     }
}

void simulation::drawtraj(repere* R){
    IntervalVector curf(4);
    IntervalVector nextf(4);
    for(int i=0;i<dataf.size()-1;i++){
        curf=dataf[i];
        nextf=dataf[i+1];
        R->DrawLine(curf[0].mid(),curf[1].mid(),nextf[0].mid(),nextf[1].mid(),QPen(Qt::blue));
    }

}

void simulation::drawrob(repere* R,double t){
    IntervalVector currentf(4);
    double x,y,theta;
    t_trackbar = t;
    currentf=dataf[int(t_trackbar)];
    x = currentf[0].mid();
    y = currentf[1].mid();
    theta = currentf[2].mid();
    R->Center(x,y);
    R->DrawRobot(x,y,theta,0.2);
}
