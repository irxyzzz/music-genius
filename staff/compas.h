#ifndef COMPAS_H
#define COMPAS_H

#include "nota.h"
#include "staff.h"

#include <QList>

class Compas
{
public :
    Compas();

    bool getOpened();
    void setOpened(bool n);

    double getStartTime();
    void setStartTime(double T);

    double getEndTime();
    void setEndTime(double T);

    QList<Nota *> * getNotas();
    bool addNota(Nota * n);
    void setNotas(QList<Nota *> *ns);

    int getNumerador();
    void setNumerador(int n);

    int getDenominador();
    void setDenominador(int d);

    int getShowMet();
    void setShowMet(bool b);

private :
    bool opened;
    double startTime;
    double endTime;
    QList<Nota *> *notas;
    int numerador;
    int denominador;
    bool showMet;
    int capacity;
};

#endif
