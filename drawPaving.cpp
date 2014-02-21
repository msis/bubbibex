#include "drawPaving.h"
/* Cette fonction recoit le temps t de la trackbar, le repere cree dans la fenetre principale,
un vecteur d'intervalles (et non pas une liste de vecteurs d'intervalles), et les couleurs.
Elle sera ensuite utilisée pour dessiner les pavages incertains et out.
*/

void drawPaving::update(double& t,repere& R,IntervalVector& X,QPen pencolor,QBrush brushcolor)
{

    if (X[3].contains(t))
    {

        R.DrawBox(X[0].lb(),X[0].ub(),X[1].lb(),X[1].ub(),pencolor,brushcolor);

    }
}



drawPaving::drawPaving(QList<IntervalVector> &Sout, QList<IntervalVector> &Sprob, double t, repere& R)
{
//    R.Clean();
    // on parcours la liste des interval vecteur out et on les represente
    //qDebug() << "drawpaving "<< Sout.size() << " " << Sprob.size() << "t : "<<t;
    for(int i = 0; i<Sout.size(); i++)
    {
        IntervalVector Xout = Sout.at(i);
        update(t,R,Xout,QPen(Qt::black),QBrush(Qt::white));
    }

    // // on parcours la liste des interval vecteur probables et on les represente
    QList<IntervalVector> Sprob_t;

    for(int i = 0; i<Sprob.size();i++)
    {

        IntervalVector Xprob= Sprob.at(i);
        update(t,R,Xprob,QPen(Qt::yellow),QBrush(Qt::yellow));
        if (Xprob[3].contains(t))
        {
          Sprob_t.push_back(Xprob);
        }


    }

    if((Sprob_t).isEmpty()!=1){

        int l=Sprob_t.size();
        cout<<l;
        for (int i =0;i<10;i++){
            int x1 = (rand()% l);
            IntervalVector x = Sprob_t.at(x1);
            cout<<x;
            if (x[3].contains(t))
            {
            R.DrawRobot(x[0].mid(),x[1].mid(),x[2].mid(),0.05);
            }
        }
    }




}

