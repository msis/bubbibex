#include "drawPaving.h"
#include "ibex.h"
using namespace std;
using namespace ibex;




drawPaving::drawPaving(QObject *parent) :
    QObject(parent)
{
}

void drawPaving::update(repere& R,IntervalVector& Xout,IntervalVector& Xprob):{
    R.Clean();
    if (Xout[1].contains(t))
        R.DrawBox(Xout[0][0].lb(),Xout[0][0].ub(),Xout[0][1].lb(),Xout[0][1].ub(),QPen(Qt::blue),QBrush(Qt::NoBrush));
    R.DrawBox(Xprob[0][0].lb(),Xprob[0][0].ub(),Xprob[0][1].lb(),Xprob[0][1].ub(),QPen(Qt::Yellow),QBrush(Qt::NoBrush));

}
