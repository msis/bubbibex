#ifndef DRAWF_H
#define DRAWF_H

#include <QDebug>
#include <QMainWindow>
#include <QObject>
#include <QtCore>
#include <QtGui>
#include <cmath>
#include "ibex.h"
#include "frame.h"

using namespace ibex;
using namespace std;

class Drawf {

public:

Drawf(Frame& frame, double x1min, double x1max, double x2min, double x2max);


private:
Function *f_inf;
Function *f_sup;

};

#endif // DRAWF_H
