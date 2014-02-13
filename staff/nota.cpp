#include "nota.h"
#include "compas.h"
#include <QList>
#include <QtDebug>
#include <iostream>

Nota::Nota(Compas *p)
{
	parent=p;
	duracion = 0;
	tono =0;
	tie=NULL;
	jNotes=new QList<Nota *>();
	slur=new QList<Nota *>();
	chord=new QList<Nota *>();
	silencio=false;
}

Compas * Nota::getParent()
{
	return parent;
}

void Nota::setParent(Compas *p)
{
	parent=p;
}

QList<Nota *> * Nota::getJNotes()
{
	return jNotes;
}

void Nota::setJNotes(QList<Nota *> *jn)
{
	jNotes=jn;
}

int Nota::getDuracion()
{
	return duracion;
}

void Nota::setDuracion(int d)
{
	duracion = d;
}

int Nota::getTono() const
{
        return tono;
}

void Nota::setTono(int t)
{
        tono = t;
}

int Nota::getRTono() const
{
        return rTono;
}

void Nota::setRTono(int rt)
{
//    int remainder = rt%12;
//    int quotient = rt/12;
//    switch(remainder) {
//    case 0:  setTono(quotient+0);
//    case 1:  setTono(quotient+0);
//    case 2:  setTono(quotient+0);
//    case 3:  setTono(quotient+0);
//    case 4:  setTono(quotient+0);
//    case 5:  setTono(quotient+0);
//    case 6:  setTono(quotient+0);
//    case 7:  setTono(quotient+0);
//    case 8:  setTono(quotient+0);
//    case 9:  setTono(quotient+0);
//    case 10: setTono(quotient+0);
//    case 11: setTono(quotient+0);
//    }
        rTono = rt;
}

bool Nota::getSilencio()
{
	return silencio;
}

void Nota::setSilencio(bool s)
{
	silencio = s;
}

void Nota::setTie(Nota *t)
{
	tie=t;
}

Nota * Nota::getTie()
{
	return tie;
}

QList<Nota *> * Nota::getSlur()
{
	return slur;
}

void Nota::setSlur(QList<Nota *> *sl)
{
	slur=sl;
}

QList<Nota *> * Nota::getChord()
{
	return chord;
}

void Nota::setChord(QList<Nota *> *ch)
{
	chord=ch;
}
