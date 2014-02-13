#ifndef NOTA_H
#define NOTA_H

#include <QList>

class Compas;

class Nota
{
	public :
		Nota(Compas *p);
		int getDuracion();
		void setDuracion(int d);
                int getTono() const;
                void setTono(int t);
                int getRTono() const;
                void setRTono(int rt);

		Compas * getParent();
		void setParent(Compas *p);
	
		QList<Nota *> * getJNotes();
		void setJNotes(QList<Nota *> *jn);
	
		bool getSilencio();
		void setSilencio(bool s);

		void setTie(Nota *t);
		Nota * getTie();
	
		QList<Nota *> * getSlur();
		void setSlur(QList<Nota *> *sl);
	
		QList<Nota *> * getChord();
		void setChord(QList<Nota *> *ch);

	private :
		int duracion;

		int tono;

                int rTono;

		bool silencio;

		Compas * parent;
	
		QList<Nota *> *jNotes;

		Nota *tie;

		QList<Nota *> *slur;

		QList<Nota *> *chord;

};

#endif
