#include <QUndoCommand>
#include "partituracommands.h"
#include "staff/nota.h"
#include "staff/compas.h"
#include "staff/partitura.h"
#include "renderpartitura.h"

AddNotaCommand::AddNotaCommand(RenderPartitura *rp,Nota *nota, Compas *compas, int p, Partitura *partitura)
{
	n = nota;
	c = compas;
	pos = p;
	partit = partitura;
	rendpart = rp;

	tiefrom= NULL;
	tieto= NULL;
}

void AddNotaCommand::undo()
{
	if(grNotes.size() > 0){
		QList<Nota *> * groupedNotes = new QList<Nota *>(grNotes);
		for(int i=0;i<grNotes.size();i++){			
			grNotes.at(i)->setJNotes(groupedNotes);
		}
		grNotes.clear();
	}

	if(tiefrom != NULL && tieto != NULL){
		tiefrom->setTie(tieto);
	}	

	if(slur.size() > 0){
		QList<Nota *> * slurNotes = new QList<Nota *>(slur);
		for(int i=0;i<slur.size();i++){
			slur.at(i)->setSlur(slurNotes);
		}
		slur.clear();
	}

	c->getNotas()->removeAt(pos);

	rendpart->update();
}

void AddNotaCommand::redo()
{
	c->getNotas()->insert(pos,n);

	if(n != c->getNotas()->last()){
		if(c->getNotas()->at(pos+1)->getJNotes()->size()>0){
			grNotes=c->getNotas()->at(pos+1)->getJNotes()->mid(0);
			c->getNotas()->at(pos+1)->getJNotes()->clear();
		}
	}

	if(pos > 0){
		if(c->getNotas()->at(pos-1)->getTie() != NULL){
			tiefrom = c->getNotas()->at(pos-1);
			tieto = c->getNotas()->at(pos-1)->getTie();
			c->getNotas()->at(pos-1)->setTie(NULL);
		} else if(c->getNotas()->at(pos-1)->getChord()->size() > 0){
			QList<Nota *> *chord = c->getNotas()->at(pos-1)->getChord();
			for(int i=0;i<chord->size();i++){
				if(chord->at(i)->getTie() != NULL){
					tiefrom = chord->at(i);
					tieto = chord->at(i)->getTie();
					chord->at(i)->setTie(NULL);
				}
			}
		}
	} else {
		int indc = partit->getCompases()->indexOf(c);
		if(indc > 0){
			if(partit->getCompases()->at(indc-1)->getNotas()->size() > 0){
				Nota *tnota = partit->getCompases()->at(indc-1)->getNotas()->last();
				if(tnota!=NULL){
					if(tnota->getTie() != NULL){
						tnota->setTie(NULL);
					} else if(tnota->getChord()->size() > 0){
						QList<Nota *> * chord = tnota->getChord();
						for(int i=0;i<chord->size();i++){
							if(chord->at(i)->getTie() != NULL){
								tiefrom = chord->at(i);
								tieto = chord->at(i)->getTie();
								chord->at(i)->setTie(NULL);
							}
						}
					}
				}
			}
		}
	}

	if(pos>0){
		QList<Nota *> *lslur=c->getNotas()->at(pos-1)->getSlur();
		if(lslur->size() > 0 && lslur->last() != c->getNotas()->at(pos-1)){
			slur = lslur->mid(0);
			lslur->clear();
		}
	} else {
		int indc = partit->getCompases()->indexOf(c)-1;
		while(indc>=0 && partit->getCompases()->at(indc)->getNotas()->size() == 0){
			indc--;
		}
		if(indc >= 0 && partit->getCompases()->at(indc)->getNotas()->size() > 0){
			Nota * lastNote = partit->getCompases()->at(indc)->getNotas()->last();
			if (lastNote->getSlur()->size() > 0 && lastNote != lastNote->getSlur()->last()){
				slur = lastNote->getSlur()->mid(0);
				lastNote->getSlur()->clear();
			}
		}
	}
	rendpart->update();
}


AddChordCommand::AddChordCommand(RenderPartitura *rp,Nota *nota,Nota *pnota,bool first,int position)
{
	rendpart=rp;
	n=nota;
	inota=pnota;
	firstAdd=first;
	pos=position;
}


void AddChordCommand::undo()
{
	if(firstAdd){
		inota->getChord()->clear();
	} else {
		inota->getChord()->removeAll(n);
	}
	rendpart->update();
}


void AddChordCommand::redo()
{
	if(firstAdd){
		if(inota->getTono() < n->getTono()){
			inota->getChord()->append(inota);
			inota->getChord()->append(n);
		} else {
			inota->getChord()->append(n);
			inota->getChord()->append(inota);
		}		
	} else {
		inota->getChord()->insert(pos,n);
	}
	
	rendpart->update();
}


DeleteNoteCommand::DeleteNoteCommand(RenderPartitura *rp,Nota * n,QList<Compas *> *compases)
{
	rendpart=rp;
	nota=n;
	comps=compases;
	inota=0;
	
	tiefrom=NULL;
}


void DeleteNoteCommand::undo()
{
	if(grNotes.size() > 0){
		QList<Nota *> * groupedNotes = new QList<Nota *>(grNotes);
		for(int i=0;i<grNotes.size();i++){			
			grNotes.at(i)->setJNotes(groupedNotes);
		}
		grNotes.clear();
	}

	if(tiefrom != NULL ){
		tiefrom->setTie(nota);
	}	

	if(slur.size() > 0){
		QList<Nota *> * slurNotes = new QList<Nota *>(slur);
		for(int i=0;i<slur.size();i++){
			slur.at(i)->setSlur(slurNotes);
		}
		slur.clear();
	}
	nota->getParent()->getNotas()->insert(inota,nota);
	
	rendpart->update();
}


void DeleteNoteCommand::redo()
{

	if( nota->getJNotes()->size() > 0){
		grNotes = nota->getJNotes()->mid(0);
		nota->getJNotes()->clear();
	}
	

	if(nota->getTie() == NULL){
		for(int ic=0;ic<comps->size();ic++){
			Compas *curc=comps->at(ic);
			for(int in=0;in<curc->getNotas()->size();in++){
				if (curc->getNotas()->at(in)->getTie() == nota){
					tiefrom = curc->getNotas()->at(in);
					curc->getNotas()->at(in)->setTie(NULL);
				}
			}
		}
	}
	

	if(nota->getSlur() != NULL){
		if(nota->getSlur()->size() > 0){
			slur=nota->getSlur()->mid(0);
			nota->getSlur()->clear() ;
		}
	}
	inota=nota->getParent()->getNotas()->indexOf(nota);
	nota->getParent()->getNotas()->removeAll(nota);
	
	rendpart->update();
}


PasteNotesCommand::PasteNotesCommand(RenderPartitura *rp,Compas *compas,int position,QList<Nota *> *lnotas)
{
	rendpart=rp;
	c=compas;
	pos=position;
	notas=lnotas;
	for(int i=0;i<notas->size();i++){
		notas->at(i)->setParent(compas);
	}
}


void PasteNotesCommand::undo()
{
	if(pos > 0){
		for(int i=0;i<jnotes.size();i++){
			c->getNotas()->at(pos-1)->getJNotes()->append(jnotes.at(i));
		}
		for(int i=0;i<snotes.size();i++){
			c->getNotas()->at(pos-1)->getSlur()->append(snotes.at(i));
		}
		c->getNotas()->at(pos-1)->setTie(tie);
	}
	for(int i=0;i<notas->size();i++){
		c->getNotas()->removeAll(notas->at(i));
	}
	
	rendpart->update();
}


void PasteNotesCommand::redo()
{
	if (pos > 0){
		if (!c->getNotas()->at(pos-1)->getJNotes()->isEmpty()){
			jnotes = c->getNotas()->at(pos-1)->getJNotes()->mid(0);
			c->getNotas()->at(pos-1)->getJNotes()->clear();
		}
		if (!c->getNotas()->at(pos-1)->getSlur()->isEmpty()){
			snotes = c->getNotas()->at(pos-1)->getSlur()->mid(0);
			c->getNotas()->at(pos-1)->getSlur()->clear();
		}
		if (c->getNotas()->at(pos-1)->getTie() != NULL){
			tie = c->getNotas()->at(pos-1)->getTie();
			c->getNotas()->at(pos-1)->setTie(NULL);
		}
	}
	for(int i=0;i<notas->size();i++){
		c->getNotas()->insert(pos+i,notas->at(i));
	}
	
	rendpart->update();
}

GroupNotesCommand::GroupNotesCommand(RenderPartitura *rp, QList<Nota *> *lnotas)
{
	rendpart=rp;
	ln = new QList<Nota *>(*lnotas);
}


void GroupNotesCommand::undo()
{
	for(int i=0;i<ln->size();i++){
		ln->at(i)->getJNotes()->clear();
	}
	
	for(int i=0;i<llist.size();i++){
		for(int a=0;a<llist.at(i)->size();a++){
			llist.at(i)->at(a)->setJNotes(llist.at(i));
		}
	}
	llist.clear();
	rendpart->update();
}


void GroupNotesCommand::redo()
{
	QList<Nota *> *listaNotas = new QList<Nota *>(*ln);
	for(int i=0;i<listaNotas->size();i++){
		llist<<new QList<Nota *>(*listaNotas->at(i)->getJNotes());
		if(listaNotas->at(i)->getJNotes()->size()==0){
			listaNotas->at(i)->setJNotes(listaNotas);
		} else {
			listaNotas->at(i)->getJNotes()->clear();
			listaNotas->at(i)->setJNotes(listaNotas);
		}
	}
	
	rendpart->update();
}


TieNotesCommand::TieNotesCommand(RenderPartitura *rp, Nota *from, Nota *to)
{
	rendpart = rp;
	tiefrom = from;
	tieto = to;
}


void TieNotesCommand::undo()
{
	tiefrom->setTie(NULL);
	
	rendpart->update();
}


void TieNotesCommand::redo()
{
	tiefrom->setTie(tieto);
	
	rendpart->update();
}

SlurNotesCommand::SlurNotesCommand(RenderPartitura *rp, QList<Nota *> *lnotas)
{
	rendpart=rp;
	ln = new QList<Nota *>(*lnotas);	
}


void SlurNotesCommand::undo()
{
	for(int i=0;i<ln->size();i++){
		ln->at(i)->getSlur()->clear();
	}
	
	for(int i=0;i<llist.size();i++){
		for(int a=0;a<llist.at(i)->size();a++){
			llist.at(i)->at(a)->setSlur(llist.at(i));
		}
	}
	llist.clear();
	rendpart->update();
}


void SlurNotesCommand::redo()
{
	QList<Nota *> *listaNotas = new QList<Nota *>(*ln);
	for(int i=0;i<listaNotas->size();i++){
		llist<<new QList<Nota *>(*listaNotas->at(i)->getSlur());
		if(listaNotas->at(i)->getSlur()->size()==0){
			listaNotas->at(i)->setSlur(listaNotas);
		} else {
			listaNotas->at(i)->getSlur()->clear();
			listaNotas->at(i)->setSlur(listaNotas);
		}
	}
	rendpart->update();
}

SetTimeSignCommand::SetTimeSignCommand(RenderPartitura *rp, Compas *c, int n, int d, bool sm)
{
	rendpart=rp;
	compas = c;
	num=n;
	den=d;
	showMet=sm;
	oldSm=c->getShowMet();
	oldNum=c->getNumerador();
	oldDen=c->getDenominador();
}

void SetTimeSignCommand::undo()
{
	compas->setDenominador(oldDen);
	compas->setNumerador(oldNum);
	compas->setShowMet(oldSm);
	rendpart->update();
}

void SetTimeSignCommand::redo()
{
	compas->setDenominador(den);
	compas->setNumerador(num);
	compas->setShowMet(showMet);
	rendpart->update();
}
