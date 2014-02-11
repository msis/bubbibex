#include "sivia.h"
#include "math.h"
#include "stdio.h"
#define _USE_MATH_DEFINES


void Sivia::contract_and_draw(Ctc& c, IntervalVector& X, const QColor & pencolor, const QColor & brushcolor, QList<IntervalVector>& Sout) {
    IntervalVector X0=X;       // get a copy
    try {
        c.contract(X);
        if (X==X0) return;     // nothing contracted.
        IntervalVector* rest;
        int n=X0.diff(X,rest); // calculate the set difference
        for (int i=0; i<n; i++) {     // display the boxes
            //R.DrawBox(rest[i][0].lb(),rest[i][0].ub(), rest[i][1].lb(),rest[i][1].ub(),QPen(pencolor),QBrush(brushcolor));
            Sout.append(rest[i]);
            }
        delete[] rest;
    } catch(EmptyBoxException&) {
        //R.DrawBox(X0[0].lb(),X0[0].ub(),X0[1].lb(),X0[1].ub(),QPen(pencolor),QBrush(brushcolor));
        Sout.append(X0);
    }
}


Sivia::Sivia(repere& R, double epsilon) : R(R) {

    Variable x,y,z,x1,x2,x3,t;
    Function foc(x,y,z,x+sqr(y)+3*z);

    Function ff("f.txt");

    Function gg("g.txt");
    Function ggd(gg,Function::DIFF);
    //cout << gg<<endl; // ggd[0]: dgg/dx1,
    //cout << ggd[0][0]<<endl;


    // Primeira funcao G
    NumConstraint ci0(x1,x2,x3,t,ggd(x1,x2,x3,t)[0][0]*ff(x1,x2,x3,t)[0]+
                                ggd(x1,x2,x3,t)[0][1]*ff(x1,x2,x3,t)[1]+
                                ggd(x1,x2,x3,t)[0][2]*ff(x1,x2,x3,t)[2]+
                                ggd(x1,x2,x3,t)[0][3]>=0);

    NumConstraint ci1(x1,x2,x3,t,ggd(x1,x2,x3,t)[1][0]*ff(x1,x2,x3,t)[0]+
                                ggd(x1,x2,x3,t)[1][1]*ff(x1,x2,x3,t)[1]+
                                ggd(x1,x2,x3,t)[1][2]*ff(x1,x2,x3,t)[2]+
                                ggd(x1,x2,x3,t)[1][3]>=0);

    NumConstraint cii0(x1,x2,x3,t,gg(x1,x2,x3,t)[0]=0);
    NumConstraint cii1(x1,x2,x3,t,gg(x1,x2,x3,t)[1]=0);
    NumConstraint ciii(gg,LEQ);

    Array<NumConstraint> c0,c1;
    c0.add(ci0);
    c0.add(cii0);
    c0.add(ciii);

    c1.add(ci1);
    c1.add(cii1);
    c1.add(ciii);

    CtcHC4 ctc0(c0);
    CtcHC4 ctc1(c1);

    // Create a contractor that removes all the points
    // that do not satisfy both f(x,y)>2 or f(x,y)<0.
    // These points are "inside" the solution set.
    CtcUnion un(ctc0,ctc1);

    // Build the initial box.
    IntervalVector box(4); // creer un Qarray de intervales vecteurs
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);
    box[2]=Interval(0,2*M_PI);
    box[3]=Interval(0,100);

    // Build the way boxes will be bisected.
    // "LargestFirst" means that the dimension bisected
    // is always the largest one.
    LargestFirst lf;

    stack<IntervalVector> s;
    s.push(box);
    QList<IntervalVector> Sp;
    QList<IntervalVector> Sout;


    cout << "Init SIVIA! " << endl;
    while (!s.empty()) {
        IntervalVector box=s.top();
        s.pop();
            //contract_and_draw(inside,box,Qt::magenta,Qt::red);
            //if (box.is_empty()) { continue; }

            contract_and_draw(un,box,Qt::darkBlue,Qt::cyan, Sout);
            if (box.is_empty()) { continue; }

            if (box.max_diam()<epsilon) {
                //R.DrawBox(box[0].lb(),box[0].ub(),box[1].lb(),box[1].ub(),QPen(Qt::yellow),QBrush(Qt::NoBrush));
                Sp.append(box);
            } else {
                pair<IntervalVector,IntervalVector> boxes=lf.bisect(box);
                s.push(boxes.first);
                s.push(boxes.second);
            }
    }

    for(int i; i<Sp.size();i++){
        cout << "Set perhaps " << Sp.at(i) << endl;
    }
    for(int i; i<Sout.size();i++){
        cout << "Set out " << Sout.at(i) << endl;
    }


    R.Save("paving");

}
