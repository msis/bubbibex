#include "sivia.h"


void Sivia::contract_and_draw(Ctc& c, IntervalVector& X, const QColor & pencolor, const QColor & brushcolor) {
    IntervalVector X0=X;       // get a copy
    try {
        c.contract(X);
        if (X==X0) return;     // nothing contracted.
        IntervalVector* rest;
        int n=X0.diff(X,rest); // calculate the set difference
        for (int i=0; i<n; i++) {     // display the boxes
            R.DrawBox(rest[i][0].lb(),rest[i][0].ub(), rest[i][1].lb(),rest[i][1].ub(),QPen(pencolor),QBrush(brushcolor));
        }
        delete[] rest;
    } catch(EmptyBoxException&) {
        R.DrawBox(X0[0].lb(),X0[0].ub(),X0[1].lb(),X0[1].ub(),QPen(pencolor),QBrush(brushcolor));
    }
}


Sivia::Sivia(repere& R, double epsilon) : R(R) {

    // Create the function we want to apply SIVIA on.
    Variable x,y;
    Function f(x,y,sin(x+y)-0.1*x*y);

    NumConstraint c1(x,y,f(x,y)<=2);
    NumConstraint c2(x,y,f(x,y)>=0);
    NumConstraint c3(x,y,f(x,y)>2);
    NumConstraint c4(x,y,f(x,y)<0);

    // Create contractors with respect to each
    // of the previous constraints.
    CtcFwdBwd out1(c1);
    CtcFwdBwd out2(c2);
    CtcFwdBwd in1(c3);
    CtcFwdBwd in2(c4);

    // Create a contractor that removes all the points
    // that do not satisfy either f(x,y)<=2 or f(x,y)>=0.
    // These points are "outside" of the solution set.
    CtcCompo outside(out1,out2);

    // Create a contractor that removes all the points
    // that do not satisfy both f(x,y)>2 or f(x,y)<0.
    // These points are "inside" the solution set.
    CtcUnion inside(in1,in2);

    // Build the initial box.
    IntervalVector box(2);
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);

    // Build the way boxes will be bisected.
    // "LargestFirst" means that the dimension bisected
    // is always the largest one.
    LargestFirst lf;

    stack<IntervalVector> s;
    s.push(box);

    while (!s.empty()) {
        IntervalVector box=s.top();
        s.pop();
            contract_and_draw(inside,box,Qt::magenta,Qt::red);
            if (box.is_empty()) { continue; }

            contract_and_draw(outside,box,Qt::darkBlue,Qt::cyan);
            if (box.is_empty()) { continue; }

            if (box.max_diam()<epsilon) {
                R.DrawBox(box[0].lb(),box[0].ub(),box[1].lb(),box[1].ub(),QPen(Qt::yellow),QBrush(Qt::NoBrush));
            } else {
                pair<IntervalVector,IntervalVector> boxes=lf.bisect(box);
                s.push(boxes.first);
                s.push(boxes.second);
            }
    }


    R.Save("paving");
}
