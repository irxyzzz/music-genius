#include "partitura.h"
#include "compas.h"
#include <QList>
#include <QUndoStack>

Partitura::Partitura(QString *name,int cl)
{
	clave=cl;
	partituraName=name;
	auxPent=NULL;
	compases=new QList<Compas *>();
	undoStack= new QUndoStack();
}

QUndoStack* Partitura::getUndoStack()
{
	return undoStack;
}

void Partitura::setUndoStack(QUndoStack *ustack)
{
	undoStack = ustack;
}

QList<Compas *> * Partitura::getCompases()
{
	return compases;
}

void Partitura::setCompases(QList<Compas *> *n)
{
	compases= n;
}

void Partitura::addCompas(Compas * c)
{
	compases->append(c);
}

void Partitura::setPartituraName(QString *pName)
{
	partituraName=pName;
}

QString * Partitura::getPartituraName()
{
	return partituraName;
}

int Partitura::getClave()
{
	return clave;
}

void Partitura::setClave(int c)
{
	clave=c;
}

Partitura * Partitura::getAuxPent()
{
	return auxPent;
}

void Partitura::setAuxPent(Partitura *p)
{
	auxPent=p;
}
