#ifndef DRAWPAVING_H
#define DRAWPAVING_H

#include <QObject>
#include <QList>

#include "ibex.h"
#include "repere.h"

using namespace std;
using namespace ibex;

class drawPaving : public QObject
{
    Q_OBJECT
public:

    void update(double& t,repere& R,IntervalVector& X,QPen pencolor,QBrush brushcolor);



    explicit drawPaving(QList<IntervalVector>  Sout,QList<IntervalVector> Sprob,double& t,repere& R,QObject *parent=NULL);



signals:

public slots:

private:
    repere* R;
    double t;
    QList<IntervalVector>  Sout;
    QList<IntervalVector>  Sprob;


};

#endif // DRAWPAVING_H
