#ifndef SCENAR_H
#define SCENAR_H

#include <QString>
#include <QFile>
#include <QTextStream>

class Scenario
{
public:
    void save(QString f,QString g,QString c);
    QString initf();
    QString initg();
    QString initc();
};

#endif // SCENAR_H
