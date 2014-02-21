#ifndef SIMULATION_H
#define SIMULATION_H

#include "repere.h"
#include "ibex.h"

using namespace ibex;
/*
Le constructeur initialise les fonctions f&g
La fonction simumontecarlo enregistre dans dataf la trajectoire du robot à partir d'une condition initiale générée aléatoirement.
La fonction simumontecarlo enregistre dans datag la position du la bulle
La fonction drawrob permet de tracer le robot à un temps trackbar donné
*/
class simulation
{
public:
    simulation(Function& f, Function& g);

    void simuMonteCarlo(repere* R,int NB);
    void drawrob(repere* R,double t);
    void drawtraj(repere* R);

private:
    Function fonct_f;
    Function fonct_g;
    double t_trackbar;
    double dt;
    Interval t;
    vector<IntervalVector> dataf;
    vector<IntervalVector> datad;

};

#endif // SIMULATION_H
