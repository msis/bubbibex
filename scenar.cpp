#include "scenar.h"
#include <QDebug>
#include <stdio.h>

Scenario::Scenario()
{
    initFileFunc();
}

void Scenario::initFileFunc()
{
    //Creating function Table
    QString funcTab[3][2];

    funcTab[0][0] = initf1();
    funcTab[0][1] = initg1();
    funcTab[1][0] = initf2();
    funcTab[1][1] = initg2();
    funcTab[2][0] = initf3();
    funcTab[2][1] = initg3();


    //Generating default function files if necessary
    for(int ii=1; ii<4; ii++){
        QString sf = "f" + QString::number(ii) + ".txt";
        QString sg = "g" + QString::number(ii) + ".txt";

        QFile ff(sf);
        QFile fg(sg);

        if(!ff.exists()){
            ff.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream outf(&ff);
            outf << funcTab[ii-1][0];
            ff.close();
        }

        if(!fg.exists()){
            fg.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream outg(&fg);
            outg << funcTab[ii-1][1];
            fg.close();
        }
    }

    /*//Generating current function files if necessary
    QFile ff("f.txt");
    QFile fg("g.txt");

    if(!ff.exists()){
        ff.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream outf(&ff);
        outf << funcTab[0][0];
        ff.close();
    }

    if(!fg.exists()){
        fg.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream outg(&fg);
        outg << funcTab[0][1];
        fg.close();
    }*/

}

void Scenario::save(QString f, QString g)
{
    QFile file1("f.txt");
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))   return;
    QTextStream out1(&file1);
    out1 << f << "\n";
    file1.close();

    QFile file2("g.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))  return;
    QTextStream out2(&file2);
    out2 << g << "\n";
    file2.close();
}

void Scenario::load(QString &f, QString &g)
{
    QFile file1("f.txt");
    if (file1.exists()){
        if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) return;
        f = QString(file1.readAll());
        file1.close();
    } else {
        qDebug() << "defaut f string";
        f = initf1();
    }


    QFile file2("g.txt");
    if (file2.exists()){
        if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))  return;
        g = QString(file2.readAll());
        file2.close();
    } else {
        qDebug() << "defaut f string";
        g = initg1();
    }

    save(f,g);


//    QFile file3("constraints.txt");
//    if (!file3.open(QIODevice::WriteOnly | QIODevice::Text)) return;
//    QTextStream out3(&file3);
//    out3 << c << "\n";
//    file3.close();

}

/* **********************************************************************************************************/
/*   SYSTEME SIMPLE 1   */

QString Scenario::initf1()
{
    QString ini;
    ini.append("function f(x1,x2,x3,t) \n \
        return(\n \
            -x1+t,\n \
            -x2,\n \
            -x3\n \
        );\n \
    end");
    return ini;
}

QString Scenario::initg1()
{
    QString ini;
    ini.append("function f(x1,x2,x3,t) \n \
        return(\n \
            ((x1-t)^2+(x2)^2-1),\n \
            ((cos(x3)-1)^2 +(sin(x3))^2 - 0.2) \n \
        );\n \
    end");
    return ini;
}


/*********************************************************************************************************/
/*   SYSTEME NON HOLONOME TOUT DROIT   */

QString Scenario::initf2()
{
    QString ini;
    ini.append("function f(x1,x2,x3,t) \n \
               xd=7*t; \n \
               xdd=7; \n \
               yd=0; \n \
               ydd=0; \n \
               nx=(xd-x1+xdd);\n \
               ny=(yd-x2+ydd);\n \
               r=sqrt(nx^2+ny^2);\n \
               ux=nx/r;\n \
               uy=ny/r;\n \
        return(\n \
            r*cos(x3),\n \
            r*sin(x3),\n \
            10*(cos(x3)*uy-sin(x3)*ux)\n \
        );\n \
    end");
    return ini;  //   et non pas cos(x3)*(ydiff)-sin(x3)*(xdiff) /norm
}

QString Scenario::initg2()
{
    QString ini;
    ini.append("function g(x1,x2,x3,t)\n \
               xd=7*t; \n \
               xdd=7; \n \
               yd=0; \n \
               ydd=0; \n \
               nx=(xd-x1+xdd);\n \
               ny=(yd-x2+ydd);\n \
               r=sqrt(nx^2+ny^2);\n \
               ux=nx/r;\n \
               uy=ny/r;\n \
                  return(((x1-xd)^2+(x2-yd)^2-1),\n \
                      ((cos(x3)-ux)^2+(sin(x3)-uy)^2 ) - 0.01 \n \
                      );\nend");
    return ini;
}


/* **********************************************************************************************************/
/*   SYSTEME NON HOLONOME   */


QString Scenario::initf3()
{
    QString ini;
    ini.append("function f(x1,x2,x3,t) \n \
        xd = 7*t; \n\
        xdd = 7; \n \
        yd = sin(0.1*t);\n \
        ydd = 0.1*cos(0.1*t);\n \
        xdiff = (xd-x1+xdd);\n \
        ydiff = (yd-x2+ydd);\n \
        norm =  ( sqrt((xdiff)^2 +(ydiff)^2) );\n \
        return(\n \
            norm*cos(x3),\n \
            norm*sin(x3),\n \
            10*(cos(x3)*(ydiff)-sin(x3)*(xdiff))/norm\n \
        );\n \
    end");
    return ini;
}

QString Scenario::initg3()
{
    QString ini;
    ini.append("function g(x1,x2,x3,t)\n \
               xd=7*t; \n \
               xdd=7; \n \
               yd=sin(0.1*t); \n \
               ydd=0.1*cos(0.1*t); \n \
               xdiff=(xd-x1+xdd);\n \
               ydiff=(yd-x2+ydd);\n \
               den=sqrt(xdiff^2+ydiff^2);\n \
               return(((x1-xd)^2+(x2-yd)^2-1),\n \
                      ((cos(x3)-xdiff/den)^2+(sin(x3)-ydiff/den)^2 ) - 0.1 \n \
                      );\nend");
    return ini;
}

