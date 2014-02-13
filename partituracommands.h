
#ifndef PARTITURACOMMANDS_H
#define PARTITURACOMMANDS_H

#include <QUndoCommand>
#include <QList>

#include "staff/nota.h"
#include "staff/compas.h"
#include "staff/partitura.h"
#include "renderpartitura.h"

class AddNotaCommand : public QUndoCommand
{
	public:
		AddNotaCommand(RenderPartitura *rp,Nota *nota, Compas *compas, int p, Partitura *partitura);
		void undo();
		void redo();

	private:

		Nota *n;

		Compas *c;

		int pos;

		Partitura *partit;

		RenderPartitura *rendpart;

		QList<Nota *> grNotes;

		Nota * tiefrom;

		Nota * tieto;

		QList<Nota *> slur;
};

class AddChordCommand : public QUndoCommand
{
	public:
		AddChordCommand(RenderPartitura *rp,Nota *nota,Nota *pnota,bool first,int pos);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		Nota *n;

		Nota *inota;

		bool firstAdd;

		int pos;
};

class DeleteNoteCommand : public QUndoCommand
{
	public:
		DeleteNoteCommand(RenderPartitura *rp,Nota * n,QList<Compas *> *compases);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		Nota *nota;

		QList<Compas *> *comps;

		QList<Nota *> grNotes;

		Nota * tiefrom;

		QList<Nota *> slur;

		int inota;
};

class PasteNotesCommand : public QUndoCommand
{
	public:
		PasteNotesCommand(RenderPartitura *rp,Compas *compas,int position,QList<Nota *> *lnotas);
		void undo();
		void redo();	

	private:

		RenderPartitura *rendpart;

		Compas *c;

		int pos;

		QList<Nota *> *notas;

		QList<Nota *> jnotes;

		QList<Nota *> snotes;

		Nota * tie;
};

class GroupNotesCommand : public QUndoCommand
{
	public:
		GroupNotesCommand(RenderPartitura *rp, QList<Nota *> *lnotas);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		QList<Nota *> *ln;

		QList<QList<Nota *> *> llist;
};

class TieNotesCommand : public QUndoCommand
{
	public:
		TieNotesCommand(RenderPartitura *rp, Nota *from, Nota *to);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		Nota *tiefrom;

		Nota *tieto;
};

class SlurNotesCommand : public QUndoCommand
{
	public:
		SlurNotesCommand(RenderPartitura *rp, QList<Nota *> *lnotas);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		QList<Nota *> *ln;

		QList<QList<Nota *> *> llist;

};

class SetTimeSignCommand : public QUndoCommand
{
	public:
		SetTimeSignCommand(RenderPartitura *rp, Compas *c, int n, int d,bool sm);
		void undo();
		void redo();

	private:

		RenderPartitura *rendpart;

		Compas *compas;

		int num;

		int den;

		int oldNum;

		int oldDen;

		bool oldSm;

		bool showMet;
};


#endif
