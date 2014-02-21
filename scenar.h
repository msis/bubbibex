#ifndef SCENAR_H
#define SCENAR_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Scenario
{


public:
    explicit Scenario();

    void save(QString f,QString g/*,QString c*/);
    void load(QString &f, QString &g);
    QString initf();
    QString initg();
    //    QString initc();

    QString initg1();
    QString initg2();
    QString initf1();
    QString initf2();
    QString initg3();
    QString initf3();
    void initFileFunc();
};

#endif // SCENAR_H
