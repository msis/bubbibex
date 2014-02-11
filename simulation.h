#ifndef SIMULATION_H
#define SIMULATION_H

#include "repere.h"
#include "ibex.h"

using namespace ibex;

class simulation
{
public:
    simulation(Function& f, Function& g);
    void set_f(Function& f);
    void set_g(Function& g);
    void set_t_trackbar(double t);

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
