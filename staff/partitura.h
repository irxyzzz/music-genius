#ifndef PARTITURA_H
#define PARTITURA_H

#include "compas.h"
#include <QList>
#include <QString>
#include <QUndoStack>

class Partitura
{
	public :
		Partitura(QString *name,int cl);
    
		QList<Compas *> * getCompases();
		void setCompases(QList<Compas *> *n);
		void addCompas(Compas * c);
    
		void setPartituraName(QString *pName);
		QString * getPartituraName();
    
		int getClave();
		void setClave(int c);
    
		Partitura * getAuxPent();
		void setAuxPent(Partitura *p);

		QUndoStack* getUndoStack();
		void setUndoStack(QUndoStack *stack);
    
		enum tClave{claveDo,claveSol,claveFa};

	private :
		QList<Compas *> *compases;

		QString *partituraName;
    
		int clave;

		Partitura * auxPent;

		QUndoStack *undoStack;

};

#endif
