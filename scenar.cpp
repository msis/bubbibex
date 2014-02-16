#include "scenar.h"
#include <QDebug>



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

//    QFile file3("constraints.txt");
//    if (!file3.open(QIODevice::WriteOnly | QIODevice::Text)) return;
//    QTextStream out3(&file3);
//    out3 << c << "\n";
//    file3.close();

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
        f = initf();
    }


    QFile file2("g.txt");
    if (file2.exists()){
        if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))  return;
        g = QString(file2.readAll());
        file2.close();
    } else {
        qDebug() << "defaut f string";
        g = initg();
    }

    save(f,g);


//    QFile file3("constraints.txt");
//    if (!file3.open(QIODevice::WriteOnly | QIODevice::Text)) return;
//    QTextStream out3(&file3);
//    out3 << c << "\n";
//    file3.close();

}

QString Scenario::initf()
{
    QString ini;
//    ini.append("function f(x1,x2,x3,t)\nreturn(sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2)*cos(x3);\nsqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2)*sin(x3);\n(cos(x3)*(sin(t/10)-x2+(1/10)*cos(t/10))-sin(x3)*(7*t-x1+7))/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2));\nend");
    ini.append("function f(x1,x2,x3,t)\n \
               \txd	= 7*t;\n \
               \txdd	= 7;\n \
               \tyd	= sin(0.1*t);\n \
               \tydd	= 0.1*cos(0.1*t);\n \
               \txdiff	= ( xd - x1 + xdd );\n \
               \tydiff	= ( yd - x2 + ydd );\n \
               \tnorm 	= sqrt( (xdiff)^2 +(ydiff)^2 );\n \
               \treturn(\n \
               \t\t( norm*cos(x3) ),\n \
               \t\t( norm*sin(x3) ),\n \
               \t\t( ( cos(x3)*(ydiff)-sin(x3)*(xdiff) ) /norm )\n \
               \t);\nend\n");
    return ini;
}
QString Scenario::initg()
{
    QString ini;
//    "function g(x1,x2,x3,t)\n\txd\t=7*t;\n\txdd\t=7;\n\tyd\t=sin(0.1*t);\n\tydd\t=0.1*cos(0.1*t);\n\txdiff=(xd-x1+xdd);\n\tydiff=(yd- x2 + ydd);\n\tden 	= sqrt(xdiff^2 + ydiff^2);\n\treturn(((x1-xd)^2+(x2-yd)^2-1),\n\t\t((cos(x3)-xdiff/den)^2+(sin(x3)-ydiff/den)^2 ) - 0.2 \n\t);\nend");
//    ini.append("function g(x1,x2,x3,t)\nreturn((x1-7*t)^2+(x2-sin(t/10))^2-1;\n(cos(x3)-((7*t-x1+7)/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2))^2+(sin(x3)-((sin(t/10)-x2+(1/10)*cos(t/10))/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2))^2 -0.2);\nend");
    ini.append("function g(x1,x2,x3,t)\n\
        \txd	= 7*t;\n\
        \txdd	= 7;\n\
        \tyd	= sin(0.1*t);\n\
        \tydd	= 0.1*cos(0.1*t);\n\
        \txdiff	= ( xd - x1 + xdd );\n\
        \tydiff	= ( yd - x2 + ydd );\n\
        \tnorm 	= sqrt( (xdiff)^2 +(ydiff)^2 );\n\
        \treturn(\n\
        \t\t( (x1-xd)^2 + (x2-yd)^2 - 1) ,\n\
        \t\t( ( cos(x3)- (xdiff/norm) )^2 + ( sin(x3) - (ydiff/norm) )^2 - 0.2)\n\
        );\nend");

    return ini;
}
//QString Scenario::initc()
//{
//    QString ini;
//    ini.append("");
//    return ini;
//}
