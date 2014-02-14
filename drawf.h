#ifndef DRAWF_H
#define DRAWF_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <cmath>
#include "ibex.h"
#include <QList>

#include "repere.h"

using namespace ibex;
using namespace std;

class Drawf {

public:

    void updateDrawf(IntervalVector& X, double &t, repere& R);

    Drawf(QList<IntervalVector> &Bgprob, double t, repere& R);

private:

Function *f;



};

#endif // DRAWF_H
