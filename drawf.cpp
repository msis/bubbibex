#include "drawf.h"

void Drawf::updateDrawf(IntervalVector& X, double &t, repere& R){

    double x1, x2, x3;

    //Parametres de trace des fle
    QPen pen1;
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(1);
    pen1.setColor(Qt::black);


    //Creation du cadre
    double eps=0.5;  //precision du maillage
    for (x1=X[0].lb();x1<=X[0].ub();x1+=eps){
        for (x2=X[1].lb();x2<=X[1].ub();x2+=eps){
            for(x3=X[2].lb();x3<=X[2].ub();x3+=eps){

            double _p[4][2]={{x1,x1},{x2,x2},{x3,x3},{t,t}};
//            double _p[4]={x1,x2,x3,t};

            IntervalVector p(4,_p);

            IntervalVector b = f-> eval_vector(p);
            double f1=b[0].mid();
            double f2=b[1].mid();


            //Calcul des normes des vecteurs
            double n=sqrt(pow(f1,2)+pow(f2,2));

            //Trace des fleches
            R.DrawArrow(x1,x2,eps*f1/n,eps*f2/n,0.1,pen1);

            }

        }
    }
}

Drawf::Drawf(QList<IntervalVector> &Bgprob, double t, repere& R){

    //Recuperation des fonctions
    f = new Function("f.txt");
    for(int i = 0; i<Bgprob.size(); i++)
    {
        IntervalVector Xgprob = Bgprob.at(i);
        if(Xgprob[3].contains(t))
            updateDrawf(Xgprob,t,R); // en attente du sivia bulle
    }

    delete f;

}

