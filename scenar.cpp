#include "scenar.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sivia.h"
#include "qdebug.h"



void scenar::save(QString f, QString g, QString c)
{
    QFile file1("f.txt");
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))   return;
    QTextStream out1(&file1);
    out1 << f << "\n";
    file1.close();

    QFile file2("g.txt");
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Text))  return;
    QTextStream out2(&file2);
    out2 << f << "\n";
    file2.close();

    QFile file3("constraints.txt");
    if (!file3.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out3(&file3);
    out3 << c << "\n";
    file3.close();

}

QString scenar::initf()
{
    QString ini;
    ini.append("function f(x1,x2,x3,t)\nreturn(sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2)*cos(x3);\nsqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2)*sin(x3);\n(cos(x3)*(sin(t/10)-x2+(1/10)*cos(t/10))-sin(x3)*(7*t-x1+7))/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2));\nend");
    return ini;
}
QString scenar::initg()
{
    QString ini;
    ini.append("function g(x1,x2,x3,t)\nreturn((x1-7*t)^2+(x2-sin(t/10))^2-1;\n(cos(x3)-((7*t-x1+7)/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2))^2+(sin(x3)-((sin(t/10)-x2+(1/10)*cos(t/10))/sqrt((7*t-x1+7)^2+(sin(t/10)-x2+(1/10)*cos(t/10))^2))^2 -0.2);\nend");
    return ini;
}
QString scenar::initc()
{
    QString ini;
    ini.append("");
    return ini;
}
