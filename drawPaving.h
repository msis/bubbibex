#ifndef DRAWPAVING_H
#define DRAWPAVING_H

#include <QObject>
#include <QList>

#include "ibex.h"
#include "repere.h"

using namespace std;
using namespace ibex;

class drawPaving
{
public:
    void update(double& t,repere& R,IntervalVector& X,QPen pencolor,QBrush brushcolor);
    explicit drawPaving(QList<IntervalVector>  &Sout,QList<IntervalVector> &Sprob,double t,repere& R);
};

#endif // DRAWPAVING_H
