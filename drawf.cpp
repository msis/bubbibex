#include "drawf.h"

Drawf::Drawf(Frame& frame, double x1min, double x1max, double x2min, double x2max){

    double x1, x2;

    //Parametres de trace des fle
    QPen pen1;
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(1);
    pen1.setColor(Qt::black);

    //Recuperation des fonctions
    f_inf = new Function("f_inf.txt");
    f_sup = new Function("f_sup.txt");

    //Creation du cadre
    double eps=0.5;  //precision du maillage
    for (x1=x1min;x1<=x1max;x1=x1+eps){
        for (x2=x2min;x2<=x2max;x2=x2+eps){

            double _p[2][2]={{x1,x1},{x2,x2}};
            IntervalVector p(2,_p);

            double f1=(f_inf->eval_vector(p))[0].mid();
            double f2=(f_inf->eval_vector(p))[1].mid();
            double f3=(f_sup->eval_vector(p))[0].mid();
            double f4=(f_sup->eval_vector(p))[1].mid();

            //Calcul des normes des vecteurs
            double n1=sqrt(pow(f1,2)+pow(f2,2));
            double n2=sqrt(pow(f3,2)+pow(f4,2));
            double n3=sqrt(pow(f3,2)+pow(f2,2));
            double n4=sqrt(pow(f1,2)+pow(f4,2));

            //Trace des fleches
            frame.DrawArrow(x1,x2,eps*f1/n1,eps*f2/n1,0.1,pen1);
            frame.DrawArrow(x1,x2,eps*f3/n2,eps*f4/n2,0.1,pen1);
            frame.DrawArrow(x1,x2,eps*f3/n3,eps*f2/n3,0.1,pen1);
            frame.DrawArrow(x1,x2,eps*f1/n4,eps*f4/n4,0.1,pen1);

        }
    }
}
