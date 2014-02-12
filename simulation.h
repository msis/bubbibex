#ifndef SIMULATION_H
#define SIMULATION_H

#include "repere.h"
#include "ibex.h"
#include <iostream>
#include <boost/array.hpp>

#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;


using namespace ibex;
/*
Le constructeur initialise les fonctions f&g
La fonction simumontecarlo enregistre dans dataf la trajectoire du robot à partir d'une condition initiale générée aléatoirement.
La fonction simumontecarlo enregistre dans datag la position du la bulle
La fonction drawrob permet de tracer le robot à un temps trackbar donné
*/

typedef boost::array< double , 3 > state_type;


//[ rhs_class
/* The rhs of x' = f(x) defined as a class */
class harm_osc {

    double m_gam;

public:
    harm_osc( double gam ) : m_gam(gam) { }

    void operator() ( const state_type &x , state_type &dxdt , const double /* t */ )
    {
        const double sigma = 10.0;
        const double R = 28.0;
        const double b = 8.0 / 3.0;

        const double gam = 0.15;
        dxdt[0] = sigma * ( x[1] - x[0] );
        dxdt[1] = R * x[0] - x[1] - x[0] * x[2];
        dxdt[2] = -b * x[2] + x[0] * x[1];
    }
};
//]



struct push_back_state_and_time
{
    std::vector< state_type >& m_states;
    std::vector< double >& m_times;

    push_back_state_and_time( std::vector< state_type > &states , std::vector< double > &times )
    : m_states( states ) , m_times( times ) { }

    void operator()( const state_type &x , double t )
    {
        m_states.push_back( x );
        m_times.push_back( t );
    }
};

class simulation
{
public:

    simulation(Function& f, Function& g);

    void simuMonteCarlo(repere* R,int NB);
    void drawrob(repere* R,double t);
    void drawtraj(repere* R);

    int mainOde();

    void operator() ( const state_type &x , state_type &dxdt , const double /* t */ )
        {
            dxdt[0] = x[1];
            dxdt[1] = -x[0] - 0.15*x[1];
        }

private:
    Function fonct_f;
    Function fonct_g;
    double t_trackbar;
    double dt;
    Interval t;
    vector<IntervalVector> dataf;
    vector<IntervalVector> datag;

    vector<state_type> x_vec;
    vector<double> times;
};

#endif // SIMULATION_H
