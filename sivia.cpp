#include "sivia.h"
#include "math.h"
#include "stdio.h"
#define _USE_MATH_DEFINES


void Sivia::contract_and_store(Ctc& c, IntervalVector& X, QList<IntervalVector>& Sout) {
    IntervalVector X0=X;       // get a copy
    try {
        c.contract(X);
        if (X==X0) return;     // nothing contracted.
        IntervalVector* rest;
        int n=X0.diff(X,rest); // calculate the set difference
        for (int i=0; i<n; i++) {     // display the boxes
            Sout.append(rest[i]);
        }
        delete[] rest;
    } catch(EmptyBoxException&) {
        Sout.append(X0);
    }
}

void Sivia::runSivia(Ctc& c, IntervalVector &box, QList<IntervalVector>& Sout, QList<IntervalVector>& Sp){


    // Build the way boxes will be bisected.
    // "LargestFirst" means that the dimension bisected
    // is always the largest one.
    LargestFirst lf;

    stack<IntervalVector> s;
    s.push(box);

    int k = 0;
    cout << "Init SIVIA! " << endl;
    while (!s.empty()) {
        IntervalVector box=s.top();
        s.pop();
        contract_and_store(c,box, Sout);
        if (box.is_empty()) { continue; }

        if (box.max_diam()<epsilon) {
            Sp.append(box);
        } else {

            pair<IntervalVector,IntervalVector> boxes=lf.bisect(box);
            s.push(boxes.first);
            s.push(boxes.second);
//            qDebug() << s.size() << " " << box.max_diam() << " " << k++ << " " << Sp.size() << " " << Sout.size();
        }
    }
}


Sivia::Sivia(repere& R, double epsilon) : R(R), epsilon(epsilon) {

    int n = 3; // number of variables in the state vector x = (x,y,theta)
    Variable x1,x2,x3;
    Variable x(n),t;


    double _M[4*3] = {1,0,0,0,1,0,0,0,1,0,0,0};
    double _V[4] = {0,0,0,1};
    IntervalVector boxxx(4,Interval(-1,1));
    Matrix M(n+1,n,_M);
    Vector V(n+1,_V);
    Function f("f.txt");
    Function g("g.txt");
    Function dg(g,Function::DIFF);

    Function fconst(x1,x2,x3,t,dg(x1,x2,x3,t)*(M*transpose(f(x1,x2,x3,t))+V));

    //    cout << fconst <<endl;


    NumConstraint ciii(g, LEQ); // Equation (iii) du theoreme
    NumConstraint cii0(x1,x2,x3,t,g(x1,x2,x2,t)[0] =0); // Equation (ii) du theorem pour g1
    NumConstraint ci0(x1,x2,x3,t,fconst(x1,x2,x2,t)[0] >=0); // Equation (i) du theorem pour g1
    NumConstraint cii1(x1,x2,x3,t,g(x1,x2,x2,t)[1] =0); // Equation (ii) du theorem pour g2
    NumConstraint ci1(x1,x2,x3,t,fconst(x1,x2,x2,t)[1] >=0);// Equation (i) du theorem pour g2

    /* ANCIENNE METHODE POUR LE CALCUL DES DERIVEES
    Function ff("f.txt");
    Function gg("g.txt");
    Function ggd(gg,Function::DIFF);


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
            */

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
    CtcCompo un(ctc0,ctc1);

    // Build the initial box.
    IntervalVector box(4); // creer un Qarray de intervales vecteurs
    box[0]=Interval(-10,10);
    box[1]=Interval(-10,10);
    box[2]=Interval(-M_PI_2+0.1,M_PI_2-0.1 );
    box[3]=Interval(0,100);

    runSivia(un,box,this->Sout, this->Sp);


    R.Save("paving");

}

