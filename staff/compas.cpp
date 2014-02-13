#include "compas.h"

Compas::Compas()
{
    opened=true;
    startTime=0;
    endTime=0;
    notas = new QList<Nota *>();
    switch(CurrentStatus::Instance()->getMeter()) {
    case 0:
        numerador=2;
        denominador=4;
        capacity=48;
        break;
    case 1:
        numerador=3;
        denominador=4;
        capacity=72;
        break;
    case 2:
        numerador=4;
        denominador=4;
        capacity=96;
        break;
    case 3:
        numerador=6;
        denominador=8;
        capacity=72;
        break;
    }
    showMet=false;
}

bool Compas::getOpened()
{
    return opened;
}
void Compas::setOpened(bool n)
{
    opened=n;
}
double Compas::getStartTime()
{
    return startTime;
}
void Compas::setStartTime(double T)
{
    startTime=T;
}
double Compas::getEndTime()
{
    return endTime;
}
void Compas::setEndTime(double T)
{
    endTime=T;
}
QList<Nota *> * Compas::getNotas()
{
    return notas;
}
void Compas::setNotas(QList<Nota *> *ns)
{
    notas=ns;
}
int Compas::getNumerador()
{
    return numerador;
}
void Compas::setNumerador(int n)
{
    numerador = n;
}
int Compas::getDenominador()
{
    return denominador;
}
void Compas::setDenominador(int d)
{
    denominador=d;
}
int Compas::getShowMet()
{
    return showMet;
}
void Compas::setShowMet(bool b)
{
    showMet = b;
}

bool Compas::addNota(Nota * n)
{
    int duration = 0;
    foreach(Nota *nota, *notas) {
        duration += nota->getDuracion();
    }
    if((duration+n->getDuracion()) <= capacity) {
        notas->append(n);
        return true;
    } else
        return false;
}
