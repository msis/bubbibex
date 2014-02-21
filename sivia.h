#ifndef SIVIA_H
#define SIVIA_H

#include "repere.h"
#include "ibex.h"

using namespace ibex;
using namespace std;

class Sivia {
public:

    /*
     * Run the SIVIA algorithm.
     *
     * Parameters:
     * R:   where to draw the boxes.
     * epsilon: precision downto which boxes are bisected.
     */
    Sivia(repere& R, double epsilon, IntervalVector box);

    /*
     * Contract "box" with "c" and draw the trace (i.e., the difference between box and c(box))
     * with the colors "pencolor" and "brushcolor".
     */
    void contract_and_store(Ctc &c, IntervalVector &X, QList<IntervalVector> &Sout);
    void runSivia(Ctc &c, IntervalVector &box, QList<IntervalVector> &Sout, QList<IntervalVector> &Sp);

    /* List for storing results */
    QList<IntervalVector> Sp;
    QList<IntervalVector> Sout;
private:
    repere& R;
    double epsilon;
};

#endif // SIVIA_H
