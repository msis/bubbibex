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
    else {
        //qDebug() << "[" << X[3].lb() << " " << X[3].ub() << "]" << t;
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

    for(int i = 0; i<Sprob.size();i++)
    {

        IntervalVector Xprob= Sprob.at(i);
        update(t,R,Xprob,QPen(Qt::darkGray),QBrush(Qt::lightGray));
    }



}

