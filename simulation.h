#ifndef SIMULATION_H
#define SIMULATION_H

#include "repere.h"
#include "ibex.h"

using namespace ibex;
/*
Le constructeur initialise les fonctions f&g
La fonction simumontecarlo enregistre dans data la trajectoire à partir d'une condition initiale générée aléatoirement.
La fonction drawrob permet de tracer le robot à un temps trackbar donné
*/
class simulation
{
public:
    simulation(Function& f, Function& g);

    void simuMonteCarlo(repere& R);
    void drawrob(repere& R,double t);

private:
    Function fonct_f;
    Function fonct_g;
    double t_trackbar;
    double dt;
    Interval t;
    vector<IntervalVector> data;

};

#endif // SIMULATION_H
