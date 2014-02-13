#include <QtGui>
#include <iostream>
#include <QTimer>
#include <QRegion>
#include <QPainter>
#include <QPoint>
#include <QTransform>
#include <QListIterator>
#include "staff/nota.h"
#include "staff/partitura.h"
#include "staff/compas.h"
#include "renderpartitura.h"
#include "partituracommands.h"

#define MARGINLEFT 10
#define MARGINRIGHT 25
#define MARGINTOP 50
#define NOTELENGTH 35
#define PENTHEIGHT 40
#define MIDDLEMARGIN 90
#define DEFAULTPENTLENGTH 800
#define CLEFLENGTH 70
#define TSIGNLEN 30
#define LINEHEIGHT 10

#define max(A,B) ((A) > (B) ? (A) : (B))
#define abs(A) ((A) >= (0) ? (A) : ((A) * -1))

RenderPartitura::RenderPartitura(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);

    this->partitura = new Partitura(&QString("sol"), 1);
    this->partitura->setAuxPent(new Partitura(&QString("fa"), 2));
    partitura1=partitura;
    partitura2=partitura1->getAuxPent();
    dual=(partitura2 != NULL);

    undoStack=partitura1->getUndoStack();

    selectedP=NULL;
    selectedN=NULL;
    toPaste=false;

    toSetMetrica=false;

    hasText = false;
    num=0;
    den=0;

    selS=QPoint(0,0);
    selE=QPoint(0,0);

    splitOver=NULL;
    setMouseTracking(true);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    currentCursor=select;
    selecting=false;

    puntillo=false;

    resize(800,270);

    createContextMenu();

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCompass()));
}

RenderPartitura::RenderPartitura(int k, Meter m, Partitura *p, QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::ClickFocus);

    key = k;
    meter = m;
    switch(meter) {
    case FOUR2:
        this->setMetrica(2,4);
        break;
    case FOUR3:
        this->setMetrica(3,4);
        break;
    case FOUR4:
        this->setMetrica(4,4);
        break;
    case EIGHT6:
        this->setMetrica(6,8);
        break;
    }

    this->partitura = p;
    partitura1=partitura;
    partitura2=partitura1->getAuxPent();
    dual=(partitura2 != NULL);

    undoStack=partitura1->getUndoStack();

    selectedP=NULL;
    selectedN=NULL;
    toPaste=false;

    hasText = false;
    selS=QPoint(0,0);
    selE=QPoint(0,0);

    splitOver=NULL;
    setMouseTracking(true);

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    currentCursor=select;
    selecting=false;

    puntillo=false;

    resize(800,270);

    createContextMenu();

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateCompass()));

    flat7 <<    1 << 4 << 1 << 4 << 1 << 1 << 4 << 1 << 4 << 1 << 4 << 1;
    flat6 <<    1 << 4 << 1 << 4 << 1 << 4 << 4 << 1 << 4 << 1 << 4 << 1;
    flat5 <<    4 << 4 << 1 << 4 << 1 << 4 << 2 << 1 << 2 << 1 << 2 << 1;
    flat4 <<    4 << 4 << 1 << 4 << 1 << 4 << 2 << 4 << 4 << 1 << 4 << 1;
    flat3 <<    4 << 2 << 4 << 4 << 1 << 4 << 2 << 4 << 4 << 1 << 4 << 1;
    flat2 <<    4 << 2 << 4 << 4 << 1 << 4 << 2 << 4 << 2 << 4 << 4 << 1;
    flat1 <<    4 << 2 << 4 << 2 << 4 << 4 << 2 << 4 << 2 << 4 << 4 << 1;
    natural <<  4 << 3 << 4 << 3 << 4 << 4 << 3 << 4 << 3 << 4 << 3 << 4;
    sharp1 <<   4 << 3 << 4 << 3 << 4 << 1 << 4 << 4 << 4 << 4 << 3 << 4;
    sharp2 <<   1 << 4 << 4 << 3 << 4 << 1 << 4 << 4 << 4 << 4 << 3 << 4;
    sharp3 <<   1 << 4 << 4 << 3 << 4 << 1 << 4 << 1 << 3 << 4 << 3 << 4;
    sharp4 <<   1 << 4 << 1 << 4 << 4 << 1 << 4 << 1 << 4 << 4 << 3 << 4;
    sharp5 <<   1 << 4 << 1 << 4 << 4 << 1 << 4 << 1 << 4 << 1 << 4 << 4;
    sharp6 <<   1 << 4 << 1 << 4 << 1 << 1 << 4 << 1 << 4 << 1 << 4 << 4;
    sharp7 <<   1 << 4 << 1 << 4 << 1 << 1 << 4 << 1 << 4 << 1 << 4 << 1;

}

void RenderPartitura::setPuntillo(bool p)
{
	puntillo = p;
}

void RenderPartitura::setCurrentPent(int i)
{
        partitura1=this->partitura;
	partitura2=partitura1->getAuxPent();
	dual=(partitura2 != NULL);
	undoStack=partitura1->getUndoStack();
	undoStack->setActive(true);
	update();
}

void RenderPartitura::createContextMenu()
{
	contextMenu = new QMenu(this);
    
        deleteAction = new QAction(QIcon(":/images/delete.png"),tr("Borrar"),this);
	deleteAction->setShortcut(tr("Del"));
	connect(deleteAction,SIGNAL(triggered()),this, SLOT(deleteNotes()));
    
        cutAction = new QAction(QIcon(":/images/cut.png"),tr("Cortar"),this);
	cutAction->setShortcut(tr("Ctrl+X"));
	connect(cutAction,SIGNAL(triggered()),this, SLOT(cut()));    
    
        copyAction = new QAction(QIcon(":/images/copy.png"),tr("Copiar"),this);
	copyAction->setShortcut(tr("Ctrl+C"));
	connect(copyAction,SIGNAL(triggered()),this, SLOT(copy()));    
    
        pasteAction = new QAction(QIcon(":/images/paste.png"),tr("Pegar"),this);
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setEnabled(false);
	connect(pasteAction,SIGNAL(triggered()),this, SLOT(pasteIn()));     
    
	joinAction = new QAction(tr("Unir notas"),this);
	connect(joinAction,SIGNAL(triggered()),this, SLOT(joinNotes()));     
    
	tieAction = new QAction(tr("Ligar notas"),this);
	connect(tieAction,SIGNAL(triggered()),this, SLOT(tieNotes()));
	
	slurAction = new QAction(tr("Ligadura de expresión"),this);
	connect(slurAction,SIGNAL(triggered()),this, SLOT(slurNotes()));

	contextMenu->addAction(deleteAction);
	contextMenu->addAction(cutAction);
	contextMenu->addAction(copyAction);
	contextMenu->addAction(pasteAction);
	contextMenu->addSeparator();
	contextMenu->addAction(joinAction);
	contextMenu->addAction(tieAction);
	contextMenu->addAction(slurAction);
}

void RenderPartitura::slurNotes()
{

	QList<Nota *> * ln= editAction(false,false);
    
	if(ln != NULL){
		if(ln->size()>1){
			undoStack->setActive(true);
			undoStack->push(new SlurNotesCommand(this,ln));
			update();
		}
	}
}

void RenderPartitura::tieNotes()
{

	QPoint a=selS;
	QPoint b=QPoint(selE.x(),selS.y());
	Compas *ca=calcCompassHit(a);
	Compas *cb=calcCompassHit(b);
	if(ca!=cb){
		if(ca==NULL || cb==NULL){
                        return;
		} else {
			Partitura * p= getPartitura(a);
			if(abs(p->getCompases()->indexOf(ca) - p->getCompases()->indexOf(cb)) != 1){
				return;
			}
		}
	}
	

	QList<Nota *> * ln= editAction(false,false);
    
	if(ln != NULL){

		if(ln->size() == 2){		
			if (ln->at(0)->getChord()->size() > 0 &&  ln->at(1)->getChord()->size() > 0) {
				QPoint pta=selS,ptb=selE;
				if(selS.x() > selE.x()){
					pta=selE; ptb=selS;
				}
				int tonoa = calcTono(pta);
				int tonob = calcTono(ptb);
				if(tonoa==tonob){
					Nota * n1 = NULL;
					Nota * n2 = NULL;
					QList<Nota *> * ch0 = ln->at(0)->getChord();
					QList<Nota *> * ch1 = ln->at(1)->getChord();
					for(int i=0;i<ch0->size();i++){
						if(ch0->at(i)->getTono() == tonoa){
							n1 = ch0->at(i);
						}
					}
					for(int i=0;i<ch1->size();i++){
						if(ch1->at(i)->getTono() == tonob){
							n2 = ch1->at(i);
						}
					}
					if(n1 != NULL && n2 != NULL){
						undoStack->setActive(true);
						undoStack->push(new TieNotesCommand(this,n1,n2));
						update();
					}
				}
			}else if(ln->at(0)->getChord()->size() > 0){
				int tononc = ln->at(1)->getTono();
				QList<Nota *> * ch0 = ln->at(0)->getChord();
				for(int i=0;i<ch0->size();i++){
					if(ch0->at(i)->getTono() == tononc){
						undoStack->setActive(true);
						undoStack->push(new TieNotesCommand(this,ch0->at(i),ln->at(1)));
						update();
					}
				}
			}else if(ln->at(1)->getChord()->size() > 0){
				int tononc = ln->at(0)->getTono();
				QList<Nota *> * ch1 = ln->at(1)->getChord();
				for(int i=0;i<ch1->size();i++){
					if(ch1->at(i)->getTono() == tononc){
						undoStack->setActive(true);
						undoStack->push(new TieNotesCommand(this,ln->at(0),ch1->at(i)));
						update();
					}
				}
			}else if(ln->at(0)->getTono() == ln->at(1)->getTono()){
				undoStack->setActive(true);
				undoStack->push(new TieNotesCommand(this,ln->at(0),ln->at(1)));
				update();
			}
			selS=QPoint(0,0);
			selE=QPoint(0,0);
		}
	}
}

void RenderPartitura::joinNotes()
{

	QList<Nota *> * ln= editAction(false,false);
    
	if(ln != NULL){
		if(ln->size()>1){

			Compas *pc=ln->at(0)->getParent();
			for(int i=0;i<ln->size();i++){
				if(ln->at(i)->getParent() != pc || ln->at(i)->getDuracion()<8 || ln->at(i)->getSilencio()){
					return;
				}
			}

			undoStack->setActive(true);
			undoStack->push(new GroupNotesCommand(this,ln));
			update();
		}

	}
}

void RenderPartitura::setMetrica(int n,int d)
{
	num=n;
	den=d;
	toSetMetrica=true;
}

void RenderPartitura::changeCursor(QAction *action)
{
    selS.setX(0); selS.setY(0);
    selE.setX(0); selE.setY(0);
    int tcursor = action->data().toInt();
    switch(tcursor){
        case redonda:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case blanca:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case negra:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case corchea:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case semicorchea:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case fusa:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case semifusa:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s1:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s2:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s4:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s8:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s16:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s32:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        case s64:
                setCursor(Qt::ArrowCursor);
                emit this->addChord(QPoint(-1, -1));
                break;
        default:
                setCursor(Qt::ArrowCursor);
                lastCursor = currentCursor;
                break;
    }
    currentCursor=tcursor;
    update();
}

int RenderPartitura::getCompasLength(Compas *compas)
{
        int length = 20;
        if(compas->getOpened()){
                if(compas->getNotas()->size() > 0){
                        length = ((compas->getNotas()->size() * NOTELENGTH ) + 80);
                        if(compas->getShowMet()){
                                length += TSIGNLEN;
                        }
                } else {
                        length = 100;
                }
        }
        return length;
}

void RenderPartitura::showCompass(Compas *compas){
	if(!timer->isActive()){
		QList<Compas *> *compases1= partitura1->getCompases();
                int dist= 35 + (abs(key)+1)*8 + MARGINRIGHT ;
		for(int a=0;a<compases1->count();a++){
			int cl = maxCompasLength(a);
			if(compases1->at(a) == compas){
				compases1->at(a)->setOpened(true);
				if(dual) partitura2->getCompases()->at(a)->setOpened(true);

				cl = maxCompasLength(a);
				updatedRegionA = new QRegion(dist, MARGINTOP, cl, PENTHEIGHT);
				updatedRegionB = new QRegion(dist, MARGINTOP+PENTHEIGHT+MIDDLEMARGIN, cl, PENTHEIGHT);
				color=0;
				timer->start(10);
				update();
				emit ensureVisibleSignal((int)(dist+cl/2),20);
				return;
			}
			dist += cl;
		}       
	}
}

void RenderPartitura::updateCompass(){
	if(color==255){
		timer->stop();
	}
	color += 5;

	update(( *updatedRegionA + *updatedRegionB).boundingRect());
}

void RenderPartitura::expandAll(){
	QList<Compas *> *compases1= partitura1->getCompases();
	QList<Compas *> *compases2=NULL;
	if(dual) compases2= partitura2->getCompases();
	for(int a=0;a<compases1->count();a++){
		compases1->at(a)->setOpened(true);
		if(dual) compases2->at(a)->setOpened(true);
	}
    
	update();
}

void RenderPartitura::collapseAll(){
	QList<Compas *> *compases1= partitura1->getCompases();
	QList<Compas *> *compases2=NULL;
	if(dual) compases2= partitura2->getCompases();
	for(int a=0;a<compases1->count();a++){
		compases1->at(a)->setOpened(false);
		if(dual) compases2->at(a)->setOpened(false);
	}  
	update();
}


QPolygonF RenderPartitura::poliPoints(float fx,float fy)
{
	QPolygonF points;
	points  << QPointF(0.0+fx, fy) 
			<< QPointF(0.0+fx, fy+40.0) 
			<< QPointF(10.0+fx, fy+40.0) 
			<< QPointF(10.0+fx, fy+21.0)
			<< QPointF(5.0+fx, fy+25.0)
			<< QPointF(5.0+fx, fy+15.0)
			<< QPointF(10.0+fx, fy+19.0)
			<< QPointF(10.0+fx, fy);    
	return points;
}

QPolygonF RenderPartitura::poliPointsInv(float fx,float fy)
{
	QPolygonF points;
	points  << QPointF(0.0+fx, fy)  
			<< QPointF(0.0+fx, fy+40.0)
			<< QPointF(10.0+fx, fy+40.0)
			<< QPointF(10.0+fx, fy+25.0)
			<< QPointF(5.0+fx, fy+20.0)
			<< QPointF(10.0+fx, fy+15.0)
			<< QPointF(10.0+fx, fy);
	return points;
}

Compas * RenderPartitura::calcButtonHit(QPoint p)
{
	QList<Compas *> * compases=NULL;
	if(p.y() < (MARGINTOP+PENTHEIGHT) && p.y() > MARGINTOP){
		compases= partitura1->getCompases();
	}else if(dual && p.y() < (MARGINTOP+PENTHEIGHT*2+MIDDLEMARGIN) && p.y() > (MARGINTOP+PENTHEIGHT+MIDDLEMARGIN)){
		compases= partitura2->getCompases();
	}

	int nButton = nButtonHit(p);
	if(compases != NULL && nButton != 0){
		return compases->at(nButton-1);   
	}

	return NULL;
}

int RenderPartitura::nButtonHit(QPoint p)
{
        int dist=35 + (abs(key)+1)*8 + MARGINRIGHT;
	QList<Compas *> *compases= partitura1->getCompases();
	for(int a=0;a<compases->count();a++){

		dist += maxCompasLength(a);
        
		if( p.x() > dist && p.x() < (dist+10) ) {
			return (a+1);
		}
	}
	return 0;
}

Compas * RenderPartitura::calcCompassHit(QPoint p)
{
    int temp = 0;
    if(this->key < 0) {
        temp = -9;
    } else {
        temp = 0;
    }
        int dist = MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT;
        int antDist = MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT;
	QList<Compas *> *compases=getPartitura(p)->getCompases();
	for(int a=0;a<compases->count();a++){

		dist += maxCompasLength(a);       
        
		if( p.x() > antDist && p.x() < dist ) {
			return compases->at(a);
		}
		antDist=dist;
	}
	return NULL;
}

void RenderPartitura::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (currentCursor==select && event->button() == Qt::LeftButton) {   

		Compas *compas = calcCompassHit(event->pos());
		if(compas != NULL){
			emit showWaveCompass(compas);
		}

		compas = calcButtonHit(event->pos());
		if(compas != NULL) {
			int nCompas = nButtonHit(event->pos())-1;
			if(compas->getOpened()){
				partitura1->getCompases()->at(nCompas)->setOpened(false);
				if(dual) partitura2->getCompases()->at(nCompas)->setOpened(false);
			} else {
				partitura1->getCompases()->at(nCompas)->setOpened(true);
				if(dual) partitura2->getCompases()->at(nCompas)->setOpened(true);
			}
			update(); 
		}
             
	}
}

int RenderPartitura::calcTono(QPoint p)
{
	const int noteSpace=5;
	int y = p.y();
	int pos = MARGINTOP-LINEHEIGHT*3-noteSpace;
	if(p.y() > MARGINTOP+PENTHEIGHT+(MIDDLEMARGIN/2)){
		pos=MARGINTOP+PENTHEIGHT+MIDDLEMARGIN-LINEHEIGHT*3-noteSpace;
	}
	for(int t=16;t>=-6;t--){
		if(y>=(pos-2) && y<(pos+3)){
			return t;
		} else {
			pos += 5;
		}
	}
	return 1;
}

int RenderPartitura::calcChordPos(QPoint p)
{
        int dist= MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT;
	int antDist=dist;
	QList<Compas *> *compases=getPartitura(p)->getCompases();
	for(int a=0;a<compases->count();a++){
		dist += maxCompasLength(a);
		if( p.x() > antDist && p.x() < dist && compases->at(a)->getOpened()) {
			Compas *c=compases->at(a);
			int len=antDist;
			if(c->getShowMet()){
				len += TSIGNLEN;
			}
			for(int i=0;i<c->getNotas()->size();i++){
				len += NOTELENGTH;
				if(p.x()>(len-10) && p.x()<(len+17)){
					return i;
				}
			}
		}
		antDist=dist;
	}
	return -1;
}

int RenderPartitura::calcNotePos(QPoint p)
{
        int dist= MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT;
	int antDist=dist;
	QList<Compas *> *compases=getPartitura(p)->getCompases();
	for(int a=0;a<compases->count();a++){

		dist += maxCompasLength(a);

		if( p.x() > antDist && p.x() < dist && compases->at(a)->getOpened()) {
			Compas *c=compases->at(a);
			int len=antDist;
			if(c->getShowMet()){
				len += TSIGNLEN;
			}
			if(c->getNotas()->count() == 0){
				return 0;
			}
			
			for(int i=0;i<c->getNotas()->size();i++){
				len += NOTELENGTH;
				if(i==0 && p.x()<=(len-10) && p.x()>antDist){
					return i;	 
				} else if(p.x()<=(len-10) && p.x()>(len-NOTELENGTH+17)){
					return i;	
				} else if ( i == (c->getNotas()->count()-1) && p.x()>(len+17)) {
					return i+1;
				}
			}
			
		}
		antDist=dist;
	}
	return -1;
}

void RenderPartitura::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton){
                if (false){
                        toSetMetrica=false;
			QList<Partitura *> lpart;
			lpart<<partitura1;
			if(dual) lpart<<partitura2;
			Partitura * temp= getPartitura(event->pos());
			Compas *compas = calcCompassHit(event->pos());
			if(compas!=NULL){
				int icompas = temp->getCompases()->indexOf(compas);
				
				undoStack->setActive();
				undoStack->beginMacro(tr("Cambiar métrica"));
				
				for(int i=0;i<lpart.size();i++){
					Partitura * p= lpart.at(i);
					bool showMet=true;
					for(int a=icompas;a<p->getCompases()->size();a++){
						undoStack->push(new SetTimeSignCommand(this,p->getCompases()->at(a),num,den,showMet));
						if(showMet) showMet=false;
					}
				}
				
				undoStack->endMacro();
			}
			update();

		}else if (toPaste){
			cursor=event->pos();
			pasteIn();
		}else if(currentCursor == select){
			selectedP=getPartitura(event->pos());
			selS=event->pos();
			selE=event->pos();
			selecting=true;
			update();
		}
	} else if(event->button() == Qt::RightButton){
		if(selectedN != NULL){
			cursor=event->pos();
			pasteAction->setEnabled(true);
		}else{
			pasteAction->setEnabled(false);
		}
		contextMenu->popup(event->globalPos());  
	}
}

bool RenderPartitura::potDos(int m)
{
	int a=1;
	do{
		if(m==a) return true;
		a *= 2;
	}while(a<128);
	return false;
}
void RenderPartitura::addNota(int tono, partituraFlag pFlag, completoFlag cFlag)
{
    int remainder = tono%12;
    int quotient = tono/12;
    int lastNotaPos = 0;
    int defaultSign = MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT + 2;
    if(cFlag == COMPLETO && pFlag == PARTITURA1) {
        lastNotaPos = this->calculateDistance(partitura1)+defaultSign;
    } else if(cFlag == COMPLETO && pFlag == PARTITURA2) {
        lastNotaPos = this->calculateDistance(partitura2)+defaultSign;
    } else if(cFlag == INCOMPLETO && pFlag == PARTITURA1) {
        lastNotaPos = this->calculateDistance(partitura1)+defaultSign;
    } else if(cFlag == INCOMPLETO && pFlag == PARTITURA2) {
        lastNotaPos = this->calculateDistance(partitura2)+defaultSign;
    } else {
    }
    switch(remainder) {
    case 0:
        this->addNota(QPoint(lastNotaPos, 100+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 1:
        this->addNota(QPoint(lastNotaPos, 100+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 2:
        this->addNota(QPoint(lastNotaPos, 95+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 3:
        this->addNota(QPoint(lastNotaPos, 95+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 4:
        this->addNota(QPoint(lastNotaPos, 90+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 5:
        this->addNota(QPoint(lastNotaPos, 85+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 6:
        this->addNota(QPoint(lastNotaPos, 85+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 7:
        this->addNota(QPoint(lastNotaPos, 80+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 8:
        this->addNota(QPoint(lastNotaPos, 80+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 9:
        this->addNota(QPoint(lastNotaPos, 75+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 10:
        this->addNota(QPoint(lastNotaPos, 75+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 11:
        this->addNota(QPoint(lastNotaPos, 70+(pFlag*70)-(quotient-4)*35), tono);
        break;
    }
    update();
}
void RenderPartitura::addNota(int tono, partituraFlag pFlag, QPoint selPos)
{
    int remainder = tono%12;
    int quotient = tono/12;
    currentCursor=lastCursor;
    switch(remainder) {
    case 0:
        this->addNota(QPoint(selPos.x(), 100+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 1:
        this->addNota(QPoint(selPos.x(), 100+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 2:
        this->addNota(QPoint(selPos.x(), 95+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 3:
        this->addNota(QPoint(selPos.x(), 95+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 4:
        this->addNota(QPoint(selPos.x(), 90+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 5:
        this->addNota(QPoint(selPos.x(), 85+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 6:
        this->addNota(QPoint(selPos.x(), 85+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 7:
        this->addNota(QPoint(selPos.x(), 80+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 8:
        this->addNota(QPoint(selPos.x(), 80+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 9:
        this->addNota(QPoint(selPos.x(), 75+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 10:
        this->addNota(QPoint(selPos.x(), 75+(pFlag*70)-(quotient-4)*35), tono);
        break;
    case 11:
        this->addNota(QPoint(selPos.x(), 70+(pFlag*70)-(quotient-4)*35), tono);
        break;
    }
    currentCursor=select;
    update();
}
void RenderPartitura::addPause(partituraFlag pFlag, completoFlag cFlag)
{
    int lastNotaPos = 0;
    int defaultSign = MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT + 2;
    if(cFlag == COMPLETO && pFlag == PARTITURA1) {
        lastNotaPos = this->calculateDistance(partitura1)+defaultSign;
        this->addNota(QPoint(lastNotaPos, 70), -1);
    } else if(cFlag == COMPLETO && pFlag == PARTITURA2) {
        lastNotaPos = this->calculateDistance(partitura2)+defaultSign;
        this->addNota(QPoint(lastNotaPos, 200), -1);
    } else if(cFlag == INCOMPLETO && pFlag == PARTITURA1) {
        lastNotaPos = this->calculateDistance(partitura1)+defaultSign;
        this->addNota(QPoint(lastNotaPos, 70), -1);
    } else if(cFlag == INCOMPLETO && pFlag == PARTITURA2) {
        lastNotaPos = this->calculateDistance(partitura2)+defaultSign;
        this->addNota(QPoint(lastNotaPos, 200), -1);
    } else {
    }
    switch(this->currentCursor){
        case s1:
            this->currentCursor = redonda;
            break;
        case s2:
            this->currentCursor = blanca;
            break;
        case s4:
            this->currentCursor = negra;
            break;
        case s8:
            this->currentCursor = corchea;
            break;
        case s16:
            this->currentCursor = semicorchea;
            break;
        case s32:
            this->currentCursor = fusa;
            break;
        case s64:
            this->currentCursor = semifusa;
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
    }
    update();
}
bool RenderPartitura::isCompasCompleto(Partitura *par)
{
    int compasCounter = par->getCompases()->size();
    int emptyCounter = 0;
    for(int i=0; i<compasCounter; i++) {
        if(par->getCompases()->at(i)->getNotas()->isEmpty()) {
            emptyCounter=i;
            break;
        }
    }
    if(emptyCounter==0) {
        emptyCounter = 1;
    }
    bool res = this->valMetrica(par->getCompases()->at(emptyCounter-1));
    return res;
}
void RenderPartitura::addNota(QPoint p, int rTono)
{
    Compas *c = calcCompassHit(p);
    if(c != NULL){
        Nota *n = new Nota(c);
        switch(currentCursor){
                case redonda :
                        n->setDuracion(1);
                        break;
                case blanca :
                        n->setDuracion(2);
                        break;
                case negra :
                        n->setDuracion(4);
                        break;
                case corchea :
                        n->setDuracion(8);
                        break;
                case semicorchea :
                        n->setDuracion(16);
                        break;
                case fusa :
                        n->setDuracion(32);
                        break;
                case semifusa :
                        n->setDuracion(64);
                        break;
                case s1:
                        n->setDuracion(1);
                        n->setSilencio(true);
                        break;
                case s2:
                        n->setDuracion(2);
                        n->setSilencio(true);
                        break;
                case s4:
                        n->setDuracion(4);
                        n->setSilencio(true);
                        break;
                case s8:
                        n->setDuracion(8);
                        n->setSilencio(true);
                        break;
                case s16:
                        n->setDuracion(16);
                        n->setSilencio(true);
                        break;
                case s32:
                        n->setDuracion(32);
                        n->setSilencio(true);
                        break;
                case s64:
                        n->setDuracion(64);
                        n->setSilencio(true);
                        break;
                case select :
                        break;
        }
        if(!n->getSilencio()){
            n->setTono(calcTono(p));
        }
        n->setRTono(rTono);
        if(puntillo && n->getDuracion() > 1){
            n->setDuracion((int)(n->getDuracion()*1.5));
        }

        int pos= calcNotePos(p);

        if(pos != -1) {
            Partitura *partit= getPartitura(p);
            QUndoCommand * undoCommand = new AddNotaCommand(this,n,c,pos,partit);
            undoStack->setActive(true);
            undoStack->push(undoCommand);
        } else if (!n->getSilencio()){
            pos = calcChordPos(p);
            if(pos != -1){
                Nota *inota=c->getNotas()->at(pos);

                int indur = inota->getDuracion();
                int ndur = n->getDuracion();
                if (!potDos(indur)) indur = (indur/3)*2;
                if (!potDos(ndur)) ndur = (ndur/3)*2;
                if(indur == ndur){
                    undoStack->setActive(true);

                    if(inota->getChord()->size()==0 && inota->getTono() != n->getTono()){
                        undoStack->push(new AddChordCommand(this,n,inota,true,0));
                    } else if(inota->getChord()->size()>0){
                        for(int i=0;i<inota->getChord()->size();i++){
                            if(inota->getChord()->at(i)->getTono() == n->getTono()){
                                return;
                            } else if( n->getTono()< inota->getChord()->at(i)->getTono()){
                                    undoStack->push(new AddChordCommand(this,n,inota,false,i));
                                return;
                            }
                        }
                        undoStack->push(new AddChordCommand(this,n,inota,false,inota->getChord()->size()));
                    }
                }
            }
        }
    }
    update();
}

void RenderPartitura::mouseReleaseEvent(QMouseEvent *event)
{
    if(currentCursor==select && selecting){
        selecting=false;
        selE=event->pos();
        emit this->addChord(event->pos());
        update();
    }
}

void RenderPartitura::mouseMoveEvent(QMouseEvent *event)
{
	if(currentCursor == select && selecting==false){
		Compas * past=splitOver;
		splitOver=calcButtonHit(event->pos());
        
		if (splitOver != past) { 
			update();
		}
        
        } else if(currentCursor == select && selecting){
		selE = event->pos();
		update();
	} else if(currentCursor!=select){
		cursor=event->pos();
		update();
        }

	if(toPaste || toSetMetrica){
		cursor=event->pos();
		update();
	}
}

void RenderPartitura::drawRedonda(QPoint c,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s1.png");
                p->drawPixmap(c.x()-7,c.y()-9,figura);
        }else{

                QPixmap figura(this->getNotaPath("cursorRedonda",sil));
                p->drawPixmap(c.x()-16,c.y()-53,figura);
        }
}
void RenderPartitura::drawBlanca(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s2.png");
                p->drawPixmap(c.x()-7,c.y()-6,figura);
        }else {

                QPixmap figura(this->getNotaPath("cursorBlanca", sil));
                if(inv){
                        QTransform transform;
                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,figura.transformed(transform));
                }else{
                        p->drawPixmap(c.x()-6,c.y()-53,figura);
                }
        }
}

void RenderPartitura::drawNegra(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s4.png");
		p->drawPixmap(c.x()-6,c.y()-17,figura);		
	}else{

                QPixmap negra(this->getNotaPath("cursorNegra", sil));
		if(inv){
			QTransform transform;

                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,negra.transformed(transform));
	
		}else{
                        p->drawPixmap(c.x()-6,c.y()-53,negra);
		}
	}
}

void RenderPartitura::drawCorchea(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s8.png");
                p->drawPixmap(c.x()-6,c.y()-9,figura);
        }else{
                if(inv){

                        QPixmap figura(this->getNotaPath("icursorCorchea", sil));
                        QTransform transform;
                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,figura.transformed(transform));
                }else{

                        QPixmap figura(this->getNotaPath("cursorCorchea", sil));
                        p->drawPixmap(c.x()-6,c.y()-53,figura);
                }
        }
}

void RenderPartitura::drawSemicorchea(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s16.png");
                p->drawPixmap(c.x()-7,c.y()-9,figura);
        }else{
                if(inv){

                        QPixmap figura(this->getNotaPath("icursorSemicorchea", sil));
                        QTransform transform;
                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,figura.transformed(transform));
                }else{

                        QPixmap figura(this->getNotaPath("cursorSemicorchea", sil));
                        p->drawPixmap(c.x()-6,c.y()-53,figura);
                }
        }
}

void RenderPartitura::drawFusa(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s32.png");
                p->drawPixmap(c.x()-9,c.y()-19,figura);
        } else {
                if(inv){

                        QPixmap figura(this->getNotaPath("icursorFusa", sil));
                        QTransform transform;
                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,figura.transformed(transform));
                }else{

                        QPixmap figura(this->getNotaPath("cursorFusa", sil));
                        p->drawPixmap(c.x()-6,c.y()-53,figura);
                }
        }
}

void RenderPartitura::drawSemifusa(QPoint c,bool inv,QPainter *p,int sil)
{
        if(sil == 0){
                QPixmap figura(":/images/s64.png");
                p->drawPixmap(c.x()-9,c.y()-19,figura);
        } else {
                if(inv){

                        QPixmap figura(this->getNotaPath("icursorSemifusa", sil));
                        QTransform transform;
                        transform.rotate(180);
                        p->drawPixmap(c.x()-19,c.y()-6,figura.transformed(transform));
                }else{

                        QPixmap figura(this->getNotaPath("cursorSemifusa", sil));
                        p->drawPixmap(c.x()-6,c.y()-53,figura);
                }
        }
}

void RenderPartitura::drawLines(int marginTop, int length, QPainter *painter,QColor color)
{
	QPen pen;
	pen.setStyle(Qt::SolidLine);
	pen.setColor(color);
	pen.setWidthF(1.0);
	painter->setPen(pen);
    
	QLine line1(MARGINLEFT,marginTop+0,length,marginTop+0);
	QLine line2(MARGINLEFT,marginTop+10,length,marginTop+10);
	QLine line3(MARGINLEFT,marginTop+20,length,marginTop+20);
	QLine line4(MARGINLEFT,marginTop+30,length,marginTop+30);
	QLine line5(MARGINLEFT,marginTop+40,length,marginTop+40);
    
	painter->drawLine(line1);
	painter->drawLine(line2);
	painter->drawLine(line3);
	painter->drawLine(line4);
	painter->drawLine(line5);
}

int RenderPartitura::calcPentLong(QList<Compas *> * compases)
{
	int length = DEFAULTPENTLENGTH;
	if(compases->size() > 0){
                length= 35 + (abs(key)+1)*8 + MARGINRIGHT; /* Espacio para la clave */
		for (int a=0;a<compases->count();a++) {
			length += getCompasLength(compases->at(a));
		}
	}
	return length;
}

int RenderPartitura::maxPentLong(QList<Compas *> * compases1,QList<Compas *> * compases2)
{
	int length = DEFAULTPENTLENGTH;
	if(compases1->size() > 0){
                length= 35 + (abs(key)+1)*8 + MARGINRIGHT; /* Espacio para la clave */
		for (int a=0;a<compases1->count();a++) {
			int incr=getCompasLength(compases1->at(a));
			if(compases2 != NULL) incr=max(incr,getCompasLength(compases2->at(a)));
			length +=incr;
		}
	}
	return length;
}

int RenderPartitura::maxCompasLength(Compas * compas, Compas * aux)
{
	int result=0;
	int mainCompasLength = getCompasLength(compas);
	if(aux != NULL ){
		int auxCompasLength = getCompasLength(aux);
		result = max(mainCompasLength,auxCompasLength);
	} else {
		result = mainCompasLength;
	}
	return result;
}

int RenderPartitura::maxCompasLength(int i)
{
	int incr =getCompasLength(partitura1->getCompases()->at(i));
	if(dual) incr = max(incr,getCompasLength(partitura2->getCompases()->at(i)));
	return incr; 
}

void RenderPartitura::deleteNotes()
{
	editAction(false,true);
	update();
}

void RenderPartitura::copy()
{
	selectedN=editAction(true,false);
}

void RenderPartitura::cut()
{
	selectedN=editAction(true,true);
	update();
}

void RenderPartitura::paste()
{
	if(selectedN != NULL){
		toPaste=true;
	}
}

void RenderPartitura::pasteIn(){
	toPaste=false;
	Compas *c= calcCompassHit(cursor);
	if(c != NULL){
		int pos=calcNotePos(cursor);
		if(pos != -1){
			undoStack->setActive(true);
			undoStack->push(new PasteNotesCommand(this,c,pos,cloneNoteList(selectedN)));
		}
	}
	update();
}

QList<Nota *> * RenderPartitura::editAction(bool toCopy,bool toDelete)
{
	if(partitura1->getCompases()->size() > 0 && selS != QPoint(0,0) && selE != QPoint(0,0)){
		QPoint begin,end;
		if(selS.x()<selE.x()){
			begin=selS;
			end=selE;
		} else {
			begin=selE;
			end=selS;
		}
		int sx=begin.x();
		int ex=end.x();
        
		QList<Compas *> * comps=getPartitura(begin)->getCompases();
		if(comps==NULL){
			return NULL;
		}

		Compas * c=calcCompassHit(begin);
		if(c==NULL){
			c=comps->first();
		}
		Compas * ce=calcCompassHit(QPoint(end.x(),begin.y()));
		if(ce==NULL){
			ce=comps->last();
		}

                int dist=35 + (abs(key)+1)*8 + MARGINRIGHT;
        
		int i=0;
		if(dual){
			while(c != partitura1->getCompases()->at(i) && c != partitura2->getCompases()->at(i)){
				dist += maxCompasLength(partitura1->getCompases()->at(i),partitura2->getCompases()->at(i));
				i++;
			}
		} else {
			while(c != partitura1->getCompases()->at(i)){
				dist += getCompasLength(partitura1->getCompases()->at(i));
				i++;
			}
		}
        
		QList<Nota *> * forSelN= new QList<Nota *>();
		
		do{
			c = comps->at(i);
            
			if(c->getOpened()){
				int tempDist=dist;
				dist += getCompasLength(c);
				QList<Nota *> * notasTemp= new QList<Nota *>();
				int nNotas = c->getNotas()->size();
				if(c->getShowMet()){
					tempDist += TSIGNLEN;
				}

				for(int a=0;a<nNotas;a++){
					tempDist += NOTELENGTH;
					int xNote=tempDist-10;
					if((sx<xNote && ex>(xNote+NOTELENGTH)) || 
									       (sx>xNote && sx<(xNote+NOTELENGTH)) ||
									       (ex>xNote && ex<(xNote+NOTELENGTH)) ){ 
						notasTemp->append(c->getNotas()->at(a));
									       }
				}

				for(int a=0;a<notasTemp->size();a++){
					forSelN->append(notasTemp->at(a));
				}
				i++;
			} else {
				dist += getCompasLength(c);
				i++;
			}
		}while(c != ce);
		
		QList<Nota *> *clonedNotes = NULL;
		if(toCopy){
			clonedNotes= cloneNoteList(forSelN);
		}
		
		if(toDelete && forSelN->size()>0){
			undoStack->setActive(true);
			undoStack->beginMacro(tr("Borrar notas"));
			for(int i=0;i<forSelN->size();i++){
				undoStack->push(new DeleteNoteCommand(this,forSelN->at(i),comps));
			}
			undoStack->endMacro();
		}
		
		if(forSelN->size() !=0){
			if(toDelete){
				selS=QPoint(0,0);
				selE=QPoint(0,0);
			}
			if(toCopy){
				return clonedNotes;
			} else {
				return forSelN;
			}
		}
	}
	return NULL;
}

QList<Nota *> * RenderPartitura::cloneNoteList(QList<Nota *> *nlist)
{
	QList<Nota *> *clonedNotes = new QList<Nota *>();
	for(int i=0;i<nlist->size();i++){
		Nota *cn = nlist->at(i);
		Nota *temp = new Nota(cn->getParent());
		temp->setDuracion(cn->getDuracion());
		temp->setTono(cn->getTono());
		temp->setSilencio(cn->getSilencio());
		temp->setChord(cn->getChord());
		clonedNotes->append(temp);
	}
	

	for(int i=0;i<nlist->size();i++){
		Nota *cn = nlist->at(i);
		bool notfound=false;
		QList<Nota *> *groupedNotes = new QList<Nota *>();
		for(int a=0;a<cn->getJNotes()->size() && !notfound;a++){
			int inota = nlist->indexOf(cn->getJNotes()->at(a));
			if(inota == -1){
				notfound=true;
			} else {
				groupedNotes->append(clonedNotes->at(inota));
			}
		}
		if(!notfound){
			clonedNotes->at(i)->setJNotes(groupedNotes);
		}
	}
	

	for(int i=0;i<nlist->size();i++){
		Nota *cn = nlist->at(i);
		bool notfound=false;
		QList<Nota *> *slurNotes = new QList<Nota *>();
		for(int a=0;a<cn->getSlur()->size() && !notfound;a++){
			int inota = nlist->indexOf(cn->getSlur()->at(a));
			if(inota == -1){
				notfound=true;
			} else {
				slurNotes->append(clonedNotes->at(inota));
			}
		}
		if(!notfound){
			clonedNotes->at(i)->setSlur(slurNotes);
		}
	}
		

	for(int i=0;i<nlist->size();i++){
		Nota *cn = nlist->at(i);
		if (cn->getTie()!=NULL){
			int inota = nlist->indexOf(cn->getTie());
			if(inota != -1){
				clonedNotes->at(i)->setTie(clonedNotes->at(inota));
			} else if (cn != nlist->last() && !cn->getChord()->isEmpty()){
				inota = nlist->at(i+1)->getChord()->indexOf(cn->getTie());
				if(inota != -1){
					clonedNotes->at(i)->setTie(clonedNotes->at(i+1)->getChord()->at(inota));
				}
			}
		}
	}
	
	return clonedNotes;
}

Partitura * RenderPartitura::getPartitura(QPoint p)
{
	Partitura * part=NULL;
	if(p.y() < (MARGINTOP+PENTHEIGHT+(MIDDLEMARGIN/2)) || !dual){
		part= partitura1;
	}else {
		part= partitura2;
	}
	return part;
}

bool RenderPartitura::valMetrica(Compas * c)
{
	bool res = true;
	if(c->getNumerador() != 0){
		double sum = 0;
		for(int i=0;i<c->getNotas()->size();i++){
			if (potDos(c->getNotas()->at(i)->getDuracion())){
				sum += (double)(1.0 / c->getNotas()->at(i)->getDuracion());
			}else{
				sum += (double)(1.0 / (c->getNotas()->at(i)->getDuracion()/2.25));
			}
		}
		double dif = abs(sum - ((double)c->getNumerador()/(double)c->getDenominador()));
		res=dif<0.01;
	}
	return res;
}

void RenderPartitura::drawMetrica(QPainter *painter,int n,int x,int y)
{
	QString temp;
	if(n>9){
		int tn = n/10;
		temp.setNum(tn);
                painter->drawPixmap(x,y,QPixmap(":/images/mn_"+temp+".png"));
		tn = n % 10;
		temp.setNum(tn);
                painter->drawPixmap(x+13,y,QPixmap(":/images/mn_"+temp+".png"));
	}else{
		temp.setNum(n);
                painter->drawPixmap(x,y,QPixmap(":/images/mn_"+temp+".png"));
	}
}

void RenderPartitura::drawChord(QPainter *painter,QPoint punto, Nota *nota, bool dPlica)
{
	if(nota->getChord()->size()>0){
		int nup=0,ndown=0,mup=nota->getTono(),mdown=nota->getTono();
		for(int i=0;i<nota->getChord()->size();i++){
			Nota *nchord=nota->getChord()->at(i);
			if(nchord->getTono()>4){
				nup++;
			}else {
				ndown++;
			}
			if(nchord->getTono()>mup){
				mup=nchord->getTono();
			}
			if(nchord->getTono()<mdown){
				mdown=nchord->getTono();
			}
		}
		
		bool plDown=true;
		if(nup<ndown || (nup==ndown && abs(mdown-5)>abs(mup-5))){
			plDown=false;
		}
		
		bool dside=false;
		int tTono=nota->getChord()->at(0)->getTono();
		for(int i=1;i<nota->getChord()->size();i++){
			int aTono=nota->getChord()->at(i)->getTono();
			if(abs(aTono-tTono) == 1){
				dside=true;
			}
			tTono=aTono;
		}
        
		QPixmap oval;
		switch(nota->getDuracion()){
			case 1:
                                oval=QPixmap(":/images/cursorRedonda.png");
				break;
			case 2:
			case 3:
                                oval=QPixmap(":/images/blancc.png");
				break;
			default:
                                oval=QPixmap(":/images/blackc.png");
				break;
		}

		if(dside){

			int aTono=nota->getChord()->at(0)->getTono();
			int sTono=nota->getChord()->at(1)->getTono();
			int imp=-7,par=4;
			if(!plDown){
				imp=4; par=-7;
			}
			for(int i=0;i<nota->getChord()->size();i++){
				Nota *nchord=nota->getChord()->at(i);
				int cTono=nchord->getTono();
				if(i<(nota->getChord()->size()-1)){
					sTono=nota->getChord()->at(i+1)->getTono();
				} else {
					sTono=cTono;
				}
				int ptoy = punto.y() +(nota->getTono() - cTono)*5 -5;
				if(!potDos(nchord->getDuracion())){ 
					int ppy = 0;
					if( (cTono % 2) == 1) ppy=5;
					drawPuntillo(painter,nota->getChord()->at(i),QPoint(punto.x()+10,ptoy+ppy));
				}
				if((abs(aTono-cTono)==1 || abs(sTono-cTono)==1) && abs(cTono%2)==1){
					painter->drawPixmap(punto.x()+imp,ptoy,oval);	
				}else{
					painter->drawPixmap(punto.x()+par,ptoy,oval);	
				}
				aTono=cTono;
			}
		}else {
			for(int i=0;i<nota->getChord()->size();i++){
				Nota *nchord=nota->getChord()->at(i);
				int ptoy = punto.y() +(nota->getTono() - nchord->getTono())*5 -5;
				if(!potDos(nchord->getDuracion())) drawPuntillo(painter,nota->getChord()->at(i),QPoint(punto.x(),ptoy+5));

				painter->drawPixmap(punto.x()-6,ptoy,oval);	
			}            
		}
        

		if(nota->getDuracion() != 1 && dPlica){
			int pty1=punto.y() +(nota->getTono() - nota->getChord()->first()->getTono())*5 -5;
			int pty2=punto.y() +(nota->getTono() - nota->getChord()->last()->getTono())*5 -5;
			int ptx=punto.x()+5;
			if(plDown){
				if(!dside)ptx -=10;
				pty1 += 45;
				if(nota->getDuracion() >= 64){
					pty1 += 10;
				}
				pty2 += 5;
			}else{
				pty2 -= 35;
				if(nota->getDuracion() >= 64){
					pty2 -= 10;
				}
				pty1 += 5;
			}
			painter->setRenderHint(QPainter::Antialiasing,true);
			painter->drawLine(ptx,pty1,ptx,pty2);
			painter->setRenderHint(QPainter::Antialiasing,false);
            

			if(nota->getDuracion() >= 8){
				QPixmap corchete;
				switch(nota->getDuracion()){
					case 8:
					case 12:
                                                corchete=QPixmap(":/images/corchete8.png");
						break;
					case 16:
					case 24:
                                                corchete=QPixmap(":/image/imagess/corchete16.png");
						break;
					case 32:
					case 48:
                                                corchete=QPixmap(":/images/corchete32.png");
						break;
					case 64:
					case 96:
                                                corchete=QPixmap(":/images/corchete64.png");
						break; 
				}
                
				if(plDown){
					QTransform transf;
					transf.scale(1,-1);
					painter->drawPixmap(ptx-1,pty1-corchete.height(),corchete.transformed(transf));
				}else{
					painter->drawPixmap(ptx-1,pty2,corchete);
				}    
			}
		}
	}
}

void RenderPartitura::drawNota(QPainter *painter,QPoint punto,Nota *nota)
{
        if(nota->getChord()->size()>0){
                drawChord(painter,punto,nota,true);
        }else {
                int rTono=nota->getRTono();
                bool inv= false;
                if(nota->getTono()>4){
                        inv=true;
                }
                switch(nota->getDuracion()){
                        case 1:
                                drawRedonda(punto,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 2:
                        case 3:
                                drawBlanca(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 4:
                        case 6:
                                drawNegra(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 8:
                        case 12:
                                drawCorchea(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 16:
                        case 24:
                                drawSemicorchea(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 32:
                        case 48:
                                drawFusa(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                        case 64:
                        case 96:
                                drawSemifusa(punto,inv,painter,this->getUpAndDownValue(rTono));
                                break;
                }
                if(!potDos(nota->getDuracion())){
                        drawPuntillo(painter,nota,punto);
                }
        }
}

void RenderPartitura::drawPuntillo(QPainter *painter, Nota *nota,QPoint punto)
{
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::black);
	painter->setBrush(brush);		
	painter->setRenderHint(QPainter::Antialiasing,true);
	int py= punto.y()-1;
	if(nota->getSilencio() && nota->getDuracion() >= 32){
		py -= 15;
	}else if((nota->getTono() % 2) != 0  || nota->getSilencio()){
		py -= 5;
	}
        painter->drawEllipse(punto.x()+11,py-7,3,3);
	painter->setRenderHint(QPainter::Antialiasing,false);
}

bool RenderPartitura::drawGroupedNotes(QPainter *painter,Nota *nota,QPoint punto,float margintop)
{
	QList<Nota *> * notas=nota->getJNotes();


	if(nota->getChord()->size() == 0){
                painter->drawPixmap(punto.x()-6,punto.y()-5,QPixmap(":/images/blackc.png"));
		if(!potDos(nota->getDuracion())) drawPuntillo(painter,nota,punto);
	} else {
		drawChord(painter,punto,nota,false);
	}

	painter->setRenderHint(QPainter::Antialiasing,true);


	int nUp=0,nDown=0;
	Nota * iUp=notas->at(0), * iDown=notas->at(0);
	for(int cont=0;cont<notas->size();cont++){
		bool nRemain=true;
		Nota *curNota=notas->at(cont);
		int ich=0;
		QList<Nota *> * cChord= notas->at(cont)->getChord();
		while(nRemain){
			if(cChord->size() > 0){
				curNota=cChord->at(ich);
				ich++;
				if(ich == cChord->size()){
					nRemain=false;
				}
			}else{
				nRemain=false;
			}
			int cTono=curNota->getTono();
			if(cTono < 5){
				nDown++;
			} else {
				nUp++;
			}
			if(iDown->getTono() > cTono){
				iDown=curNota;
			}
			if(iUp->getTono() < cTono){
				iUp=curNota;
			}
		}
	}
	
	bool abajo=true;
	if(nDown > nUp){
		abajo=false;
	} else if(nDown == nUp){
		int distUp= abs(iUp->getTono()-5);
		int distDown= abs(iDown->getTono()-5);
		if( distUp < distDown){
			abajo=false;
		}
	}
    

	if(nota == notas->at(0)){

		enum tipoLinea {ascendente,descendente,recta} tlinea=recta;

		Nota *fNota=notas->first();
		Nota *lNota=notas->last();
		if(fNota->getChord()->size() > 0){
			fNota= (abajo ? (fNota->getChord()->first()) : (fNota->getChord()->last()));
		}
		if(lNota->getChord()->size() > 0){
			lNota= (abajo ? (lNota->getChord()->first()) : (lNota->getChord()->last()));
		}
		if(fNota->getTono() < lNota->getTono()){
			tlinea=ascendente;
			for(int cont=1;cont<(notas->size()-2);cont++){
				Nota *curNota = notas->at(cont);
				if(curNota->getChord()->size() > 0){
					curNota= (abajo ? (curNota->getChord()->first()) : (curNota->getChord()->last()));
				}
				Nota *nextNota=notas->at(cont+1);
				if(nextNota->getChord()->size() > 0){
					nextNota= (abajo ? (nextNota->getChord()->first()) : (nextNota->getChord()->last()));
				}
				if(curNota->getTono() > nextNota->getTono()){
					tlinea=recta;
				}
			}
		} else if(fNota->getTono() > lNota->getTono()){
			tlinea=descendente;
			for(int cont=1;cont<(notas->size()-2);cont++){
				Nota *curNota = notas->at(cont);
				if(curNota->getChord()->size() > 0){
					curNota= (abajo ? (curNota->getChord()->first()) : (curNota->getChord()->last()));
				}
				Nota *nextNota=notas->at(cont+1);
				if(nextNota->getChord()->size() > 0){
					nextNota= (abajo ? (nextNota->getChord()->first()) : (nextNota->getChord()->last()));
				}
				if(curNota->getTono() < nextNota->getTono()){
					tlinea=recta;
				}
			}
		}

		int parx,pary,auxy,direc,desn1,desn2,tam=32;
		int nsize=notas->size();
		int minDur=8;

		for(int i=0;i<notas->size();i++){
			if(notas->at(i)->getDuracion()>minDur){
				minDur=notas->at(i)->getDuracion();
			}
		}
		switch(minDur){
			case 8:
			case 12:
				tam=32;
				break;
			case 16:
			case 24:
				tam=40;
				break;
			case 32:
			case 48:
				tam=45;
				break;
			case 64:
			case 96:
				tam=50;
				break;
		}

		switch(tlinea){
			case descendente:
				desn1=0;
				desn2=10;
				break;
			case ascendente:
				desn1=10;
				desn2=0;
				break;
			default :
				desn1=0;
				desn2=0;
				break;
		}

		if(abajo){
			parx=-6; 
			pary=-2;
			direc=1;
			auxy=(margintop+PENTHEIGHT+5-(iDown->getTono()*5))-pary+tam*direc;
		}else{
			parx=5;
			pary=1;
			direc=-1;
			auxy=(margintop+PENTHEIGHT+5-(iUp->getTono()*5))-pary+tam*direc;
		}


		int px,pya,pyb;
		for(int cont=0;cont<nsize;cont++){
			px=punto.x()+NOTELENGTH*cont+parx;
			Nota *curNota=notas->at(cont);
			if(curNota->getChord()->size() > 0){
				curNota= (abajo ? (curNota->getChord()->last()) : (curNota->getChord()->first()));
				if(abajo) px += 10;
			}
			pya=(margintop+PENTHEIGHT+5-(curNota->getTono()*5))-pary;
			pyb=auxy+(desn2/(nsize-1))*cont + (desn1/(nsize-1))*((nsize-1)-cont);
			painter->drawLine(px,pya,px,pyb);
		}


		QPolygon linea;
                 
		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::black);
		painter->setBrush(brush);

		for(int i=0;i<=3;i++){
			int ex=1;
			for(int c=0;c<3+i;c++) {ex *= 2;}
			int factor=-8*i*direc;
                
			for(int a=0;a<notas->size();a++){
				int dur=notas->at(a)->getDuracion();
				if (!potDos(dur)) dur = (dur/3)*2;

				if(dur>=ex){
					linea.clear();
					if(notas->at(a)!=notas->last()){

						int durn=notas->at(a+1)->getDuracion();
						if (!potDos(durn)) durn = (durn/3)*2;
						if(dur>=ex && durn>=ex){

							px=punto.x()+NOTELENGTH*a+parx;
							if(abajo && a==0 && !notas->first()->getChord()->isEmpty()) px += 10;
							pyb=auxy+(desn2/(nsize-1))*a + (desn1/(nsize-1))*((nsize-1)-a);
                                
							linea<<QPoint(px,pyb+factor);
							linea<<QPoint(px,pyb-(5*direc)+factor);
                                
							px=punto.x()+NOTELENGTH*(a+1)+parx;
							if(abajo && notas->last() == notas->at(a+1) && !notas->last()->getChord()->isEmpty()) px += 10;
							pyb=auxy+(desn2/(nsize-1))*(a+1) + (desn1/(nsize-1))*((nsize-1)-(a+1));
                                
							linea<<QPoint(px,pyb-(5*direc)+factor);
							linea<<QPoint(px,pyb+factor);
                                
						} else {

							px=punto.x()+NOTELENGTH*a+parx;
							if(abajo && a==0 && !notas->first()->getChord()->isEmpty()) px += 10;
							pyb=auxy+(desn2/(nsize-1))*a + (desn1/(nsize-1))*((nsize-1)-a);
                                
							linea<<QPoint(px,pyb+factor);
							linea<<QPoint(px,pyb-(5*direc)+factor);
                                
							if(abajo && notas->last() == notas->at(a+1) && !notas->last()->getChord()->isEmpty()) px += 10;
							px=px + NOTELENGTH/3;
							int ytemp=auxy+(desn2/(nsize-1))*(a+1) + (desn1/(nsize-1))*((nsize-1)-(a+1));
							if(tlinea==ascendente){
								pyb=pyb - (abs(pyb-ytemp)/3);
							} else {
								pyb=pyb + (abs(pyb-ytemp)/3);
							}
							linea<<QPoint(px,pyb-(5*direc)+factor);
							linea<<QPoint(px,pyb+factor);
						}
					} else {

						px=punto.x()+NOTELENGTH*a+parx;
						if(abajo && !notas->last()->getChord()->isEmpty()) px += 10;
						pyb=auxy+(desn2/(nsize-1))*a + (desn1/(nsize-1))*((nsize-1)-a);
                                
						linea<<QPoint(px,pyb+factor);
						linea<<QPoint(px,pyb-(5*direc)+factor);
                                
						px=px - NOTELENGTH/3;
						int ytemp=auxy+(desn2/(nsize-1))*(a-1) + (desn1/(nsize-1))*((nsize-1)-(a-1));
						if(tlinea==ascendente){
							pyb=pyb + (abs(pyb-ytemp)/3);
						} else {
							pyb=pyb - (abs(pyb-ytemp)/3);
						}
                                
						linea<<QPoint(px,pyb-(5*direc)+factor);
						linea<<QPoint(px,pyb+factor);
					}
					painter->drawPolygon(linea); 
				}
			}
		}
	}
    
	painter->setRenderHint(QPainter::Antialiasing,false);
	return abajo;
}

void RenderPartitura::drawSlur(QPainter *painter,QList<Nota *> *notas,QPoint pt1,QPoint pt2)
{
	bool slurDown=true;
	for(int i=0;i<notas->size();i++){
		if(notas->at(i)->getTono() > 4){
			slurDown=false;
		}
	}

	int sentido=1;
	if(!slurDown){
		sentido=-1;
	}

	int c1m=7,c2m=7;
	if(!slurDown){
		if(notas->first()->getTono()<5){
			c1m += 30;
		}
		if(notas->last()->getTono()<5){
			c2m += 30;
		}
	}

	int mult = 2*notas->size();
	QPoint startPoint(pt1.x()+6,pt1.y()+sentido*c1m);
	QPoint c1(pt1.x()+10,pt1.y()+sentido*(mult+c1m));
	QPoint c2(pt2.x()-10,pt2.y()+sentido*(mult+c2m));
	QPoint endPoint(pt2.x(),pt2.y()+sentido*c2m);

	QPen slurPen(Qt::SolidLine);
	QPen oldPen=painter->pen();
	slurPen.setWidth(0);

	QPainterPath slurPath;
	slurPath.moveTo(startPoint);
	slurPath.cubicTo(c1,c2,endPoint);
	if(slurDown){
		c1.setY(c1.y()+1);
		c2.setY(c2.y()+1);
	} else {
		c1.setY(c1.y()-1);
		c2.setY(c2.y()-1);
	}
	slurPath.cubicTo(c2,c1,startPoint);

	painter->setRenderHint(QPainter::Antialiasing,true);
	painter->setPen(slurPen);
	painter->drawPath(slurPath);
	painter->setRenderHint(QPainter::Antialiasing,false);

	painter->setPen(oldPen);
}

void RenderPartitura::drawTie(QPoint tiePoint,QPoint punto,QPainter *painter,bool tieInv,bool inv)
{
	QPoint startPoint,c1,c2,endPoint;
	if(inv == false && tieInv == false){
		startPoint = QPoint(tiePoint.x()+7,tiePoint.y()+3);
		c1 = QPoint(tiePoint.x()+10,tiePoint.y()+9);
		endPoint = QPoint(punto.x()-7,punto.y()+3);
		c2 = QPoint(punto.x()-10,punto.y()+9);
	} else {
		startPoint = QPoint(tiePoint.x()+7,tiePoint.y()-3);
		c1 = QPoint(tiePoint.x()+10,tiePoint.y()-9);
		endPoint = QPoint(punto.x()-7,punto.y()-3);
		c2 = QPoint(punto.x()-10,punto.y()-9);
	}

	QPen tiePen(Qt::SolidLine);
	QPen oldPen=painter->pen();
	tiePen.setWidth(0);

	QPainterPath tiePath;
	tiePath.moveTo(startPoint);
	tiePath.cubicTo(c1,c2,endPoint);
	if(inv == false && tieInv == false){
		c1.setY(c1.y()+1);
		c2.setY(c2.y()+1);
	} else {
		c1.setY(c1.y()-1);
		c2.setY(c2.y()-1);
	}
	tiePath.cubicTo(c2,c1,startPoint);

	painter->setRenderHint(QPainter::Antialiasing,true);
	painter->setPen(tiePen);
	painter->drawPath(tiePath);
	painter->setRenderHint(QPainter::Antialiasing,false);

	painter->setPen(oldPen);
}

void RenderPartitura::drawPentagrama(QPainter * painter, Partitura * part,float margintop)
{
	QList<Compas *> *compases= part->getCompases();
        int dist=MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT;
    
	QList<QPoint> tiePoint;
	QList<Nota *> tie;
	QList<bool> tieInv;
	
	QPoint slurPoint;
    

	for (int a=0;a<compases->count();a++) {
		QPolygonF poli;
        
		int incr=maxCompasLength(a);


		if(!valMetrica(compases->at(a))){
			painter->fillRect(QRect(dist,(int)margintop,incr-10,PENTHEIGHT),QBrush(QColor(255,0,0,60)));
		}


		if(compases->at(a)->getOpened()) {
			QList<Nota *> * notas = compases->at(a)->getNotas();
			int tempDist = dist;
            

			if(compases->at(a)->getShowMet()){
				tempDist+=5;
                
				int n=compases->at(a)->getNumerador();
				int m=compases->at(a)->getDenominador();
                
				int ad1=0,ad2=0;
				if(n>9 && m<10){
					ad2 +=8;                    
				}else if(n<10 && m>9){
					ad1 +=8;
				}
				drawMetrica(painter,n,tempDist+ad1,margintop);
				drawMetrica(painter,m,tempDist+ad2,margintop+20);          
				tempDist+=TSIGNLEN-5;
			}


			for(int i=0;i<notas->size();i++){
				tempDist += NOTELENGTH;
				Nota *nota=notas->at(i);
				int tono = nota->getTono();
				bool sil=nota->getSilencio();
				
				QPoint punto;
				punto.setX(tempDist);
				if(sil){
					punto.setY(margintop+PENTHEIGHT/2);
				}else{
					punto.setY(margintop+PENTHEIGHT+5-(tono*5));
				}

				int xNote = punto.x()-10;
				int sx=selS.x();
				int ex=selE.x();
				if(selS.x()>selE.x()){
					ex=selS.x();
					sx=selE.x();
				}


				if((currentCursor != select || toPaste)&& calcCompassHit(cursor)==compases->at(a)){
					if(i==0 && cursor.x()<=(tempDist-10) && cursor.x()>dist){ /* Cursor al principio del compás */
						painter->fillRect(QRect(tempDist-25,(int)margintop,18,PENTHEIGHT),QBrush(QColor(0,0,0,60)));
					} else if(cursor.x()<=(tempDist-10) && cursor.x()>(tempDist-NOTELENGTH+17)){ /* Antes de una nota */
						painter->fillRect(QRect(tempDist-18,(int)margintop,11,PENTHEIGHT),QBrush(QColor(0,0,0,60)));
					} else if(cursor.x()>(tempDist-10) && cursor.x()<(tempDist+17)){ /* Dentro de la nota */
						painter->fillRect(QRect(tempDist-10,(int)margintop,27,PENTHEIGHT),QBrush(QColor(0,0,0,60)));
					} else if ( nota == notas->last() && cursor.x()>(tempDist+17)) { /* Al final del compás */
						painter->fillRect(QRect(tempDist+17,(int)margintop,60,PENTHEIGHT),QBrush(QColor(0,0,0,60)));
					}
				}
                


				if(selectedP == part && (
				   (sx<xNote && ex>(xNote+NOTELENGTH)) || 
							       (sx>xNote && sx<(xNote+NOTELENGTH)) ||
							       (ex>xNote && ex<(xNote+NOTELENGTH)) )){
					painter->fillRect(QRect(xNote,(int)margintop,NOTELENGTH,PENTHEIGHT),QBrush(QColor(0,109,136,80)));     
							       }
				

							       if(!sil){
								       bool nRemain=true;
								       int ctono = tono;
								       int ich=0;
								       while(nRemain){
									       if(nota->getChord()->size() > 0){
										ctono=nota->getChord()->at(ich)->getTono();
										ich++;
										if(ich==nota->getChord()->size()){
										nRemain=false;
										}
									       }else{
										nRemain=false;
									       }
									       if(ctono>9){
										for(int cont=10;cont<=ctono;cont++){
										if((cont-9)%2 == 0) {
										int alt=(int)(margintop+PENTHEIGHT+5-(cont*5));
										painter->drawLine(punto.x()-12,alt,punto.x()+12,alt);
										}
										}
									       }else if(ctono<1){
										for(int cont=0;cont>=ctono;cont--){
										if((cont-1)%2 == 0) {
										int alt=(int)(margintop+PENTHEIGHT+5-(cont*5));
										painter->drawLine(punto.x()-12,alt,punto.x()+12,alt);
										}
										}
									       }
								       }
							       }
				
							       bool inv=false;
							       if(nota->getJNotes()->size() == 0){
								       if(tono>4){
									       inv=true;
								       }
								       drawNota(painter,punto,nota);
							       } else {
								       inv = drawGroupedNotes(painter,nota,punto,margintop);
							       }


							       if(tie.size() > 0){
								       bool toDraw=false;
								       if(tie.first() == nota){
									       toDraw=true;
								       }else if(nota->getChord()->size() > 0){
									       for(int cont=0;cont<nota->getChord()->size() && !toDraw;cont++){
										if(nota->getChord()->at(cont)==tie.first()){
										toDraw=true;
										}
									       }
								       }
					
								       if(toDraw){
									       QPoint tpt;
									       bool tin;
									       Nota *tnote;
									       while( tie.size() > 0 ){
										tnote=tie.takeFirst();
										tpt=tiePoint.takeFirst();
										tin=tieInv.takeFirst();
										if(tnote == nota){
										drawTie(tpt,punto,painter,tin,inv);
										} else if(nota->getChord()->size() > 0){
										for(int cont=0; cont < nota->getChord()->size() ; cont++){
										Nota * curNota=nota->getChord()->at(cont);
										if(curNota==tnote){
										int ptoy = margintop+PENTHEIGHT+5-(curNota->getTono()*5);
										bool chinv=false;
										if(curNota->getTono()>4){
										chinv=true;
										}							
										drawTie(tpt,QPoint(punto.x(),ptoy),painter,tin,chinv);
										}
										}
										}
									       }
								       }else{
									       tie.clear();
									       tiePoint.clear();
									       tieInv.clear();
								       }
							       }

							       if (nota->getChord()->size() > 0){
								       QList<Nota *> *ch=nota->getChord();
								       for(int cont=0;cont<ch->size();cont++){
									       if(ch->at(cont)->getTie() != NULL){
										int ptoy = margintop+PENTHEIGHT+5-(ch->at(cont)->getTono()*5);
										tiePoint<<QPoint(punto.x(),ptoy);
										tie<<ch->at(cont)->getTie();
										if(ch->at(cont)->getTono()>4){
										tieInv<<true;
										} else {
										tieInv<<false;
										}
									       }
								       }
							       } else if(nota->getTie() != NULL){
								       tiePoint<<punto;
								       tie<<nota->getTie();
								       tieInv<<inv;
							       }


							       if(nota->getSlur()->size()>0){
								       if(nota->getSlur()->first() == nota){
									       slurPoint=punto;	
								       } else if(nota->getSlur()->last() == nota) {
									       drawSlur(painter,nota->getSlur(),slurPoint,punto);
								       }
							       }
			}

			if(currentCursor != select && compases->at(a)->getNotas()->size()==0 && calcCompassHit(cursor)==compases->at(a)){
				painter->fillRect(QRect(dist,(int)margintop,incr-10,PENTHEIGHT),QBrush(QColor(0,0,0,60)));
			}

			dist += incr;

			poli = poliPointsInv((float)dist-10,margintop);
		} else {
			dist += getCompasLength(compases->at(a));
			poli = poliPoints((float)dist-10,margintop);
		}


		QBrush brush;
		brush.setStyle(Qt::SolidPattern);
		if ( compases->at(a) == splitOver ) {
			brush.setColor(Qt::white);
		} else {
			brush.setColor(Qt::black);
		}
		painter->setBrush(brush);
		painter->drawPolygon(poli,Qt::WindingFill);

	}

}

void RenderPartitura::paintEvent(QPaintEvent * /*evento*/)
{
    QList<Compas *> *compases1= partitura1->getCompases();
    QList<Compas *> *compases2= NULL;
    if(dual) compases2= partitura2->getCompases();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    int maxLength=maxPentLong(compases1,compases2);

    if(width()<(maxLength+50) || width()>(maxLength+300)){
        resize(maxLength+100,height());
    }

    if(timer->isActive()){
        painter.fillRect(updatedRegionA->boundingRect(),QBrush(QColor(color,color,color)));
        if(dual) painter.fillRect(updatedRegionB->boundingRect(),QBrush(QColor(color,color,color)));
    }

    int tono=calcTono(cursor);
    if(currentCursor!=select && (tono>9 || tono<1)){
        drawLines(MARGINTOP-3*LINEHEIGHT,maxLength,&painter,Qt::gray);
        drawLines(MARGINTOP+3*LINEHEIGHT,maxLength,&painter,Qt::gray);
        if(dual){
            drawLines(MARGINTOP+PENTHEIGHT+MIDDLEMARGIN-3*LINEHEIGHT,maxLength,&painter,Qt::gray);
            drawLines(MARGINTOP+PENTHEIGHT+MIDDLEMARGIN+3*LINEHEIGHT,maxLength,&painter,Qt::gray);
        }
    }
    drawLines(MARGINTOP,maxLength,&painter,Qt::black);
    if(dual) drawLines(MARGINTOP+PENTHEIGHT+MIDDLEMARGIN,maxLength,&painter,Qt::black);

    int vertLineH=(dual ? (MARGINTOP+PENTHEIGHT*2+MIDDLEMARGIN) : (MARGINTOP+PENTHEIGHT));
    painter.drawLine(MARGINLEFT,MARGINTOP,MARGINLEFT,vertLineH);

    QPixmap claveSol(":/images/claveSol.png");
    painter.drawPixmap(MARGINLEFT+10,MARGINTOP-19,claveSol);


    if (key != 0) {
        drawSharp(key, MARGINLEFT, MARGINTOP, &painter);
    }
    drawPentagrama(&painter,partitura1,MARGINTOP);

    if(dual){
        QPixmap claveFa(":/images/claveFa.png");
        painter.drawPixmap(MARGINLEFT+8,MARGINTOP+PENTHEIGHT+MIDDLEMARGIN,claveFa);
        if (key != 0) {
            drawSharp(key, MARGINLEFT, MARGINTOP+PENTHEIGHT+MIDDLEMARGIN, &painter);
        }
        drawPentagrama(&painter,partitura2,MARGINTOP+PENTHEIGHT+MIDDLEMARGIN);
    }

    if(toSetMetrica){
        drawMetrica(&painter,num,MARGINLEFT + 35 + (abs(key)+1)*8,52);
        drawMetrica(&painter,den,MARGINLEFT + 35 + (abs(key)+1)*8,72);
        if (dual) {
            drawMetrica(&painter,num,MARGINLEFT + 35 + (abs(key)+1)*8,52+PENTHEIGHT+MIDDLEMARGIN);
            drawMetrica(&painter,den,MARGINLEFT + 35 + (abs(key)+1)*8,72+PENTHEIGHT+MIDDLEMARGIN);
        }
    }

    if(toPaste){
        for(int i=0;i<selectedN->size();i++){
            int tono = selectedN->at(i)->getTono();
            bool inv=false;
            if(tono>4){
                    inv=true;
            }
            bool sil=selectedN->at(i)->getSilencio();
            QPoint punto;
            punto.setX(i*NOTELENGTH+cursor.x());
            if(sil){
                    punto.setY(cursor.y()+PENTHEIGHT/2);
            }else{
                    punto.setY((cursor.y()+PENTHEIGHT+5-(tono*5)));
            }
            drawNota(&painter,punto,selectedN->at(i));
        }
    }

    if(hasText) {
        drawText(&painter);
    }
}


void RenderPartitura::drawSharp(int k, int x, int y,QPainter *painter) {

    QPixmap claveSharp(":/images/sharp.png");
    QPixmap claveFlat(":/images/flat.png");
    x = x + 10;
    switch(k) {
    case 1:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        return ;
    case 2:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        return ;
    case 3:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        painter->drawPixmap(x + 46,y - 15,claveSharp);
        return ;
    case 4:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        painter->drawPixmap(x + 46,y - 15,claveSharp);
        painter->drawPixmap(x + 54,y,     claveSharp);
        return ;
    case 5:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        painter->drawPixmap(x + 46,y - 15,claveSharp);
        painter->drawPixmap(x + 54,y,     claveSharp);
        painter->drawPixmap(x + 62,y + 15,claveSharp);
        return ;
    case 6:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        painter->drawPixmap(x + 46,y - 15,claveSharp);
        painter->drawPixmap(x + 54,y,     claveSharp);
        painter->drawPixmap(x + 62,y + 15,claveSharp);
        painter->drawPixmap(x + 70,y - 5, claveSharp);
        return ;
    case 7:
        painter->drawPixmap(x + 30,y - 10,claveSharp);
        painter->drawPixmap(x + 38,y + 5, claveSharp);
        painter->drawPixmap(x + 46,y - 15,claveSharp);
        painter->drawPixmap(x + 54,y,     claveSharp);
        painter->drawPixmap(x + 62,y + 15,claveSharp);
        painter->drawPixmap(x + 70,y - 5, claveSharp);
        painter->drawPixmap(x + 78,y + 10,claveSharp);
        return ;
    case -1:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        return;
    case -2:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        return;
    case -3:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        painter->drawPixmap(x + 46,y + 10,claveFlat);
        return;
    case -4:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        painter->drawPixmap(x + 46,y + 10,claveFlat);
        painter->drawPixmap(x + 54,y - 5, claveFlat);
        return;
    case -5:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        painter->drawPixmap(x + 46,y + 10,claveFlat);
        painter->drawPixmap(x + 54,y - 5, claveFlat);
        painter->drawPixmap(x + 62,y + 15,claveFlat);
        return;
    case -6:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        painter->drawPixmap(x + 46,y + 10,claveFlat);
        painter->drawPixmap(x + 54,y - 5, claveFlat);
        painter->drawPixmap(x + 62,y + 15,claveFlat);
        painter->drawPixmap(x + 70,y,     claveFlat);
        return;
    case -7:
        painter->drawPixmap(x + 30,y + 5, claveFlat);
        painter->drawPixmap(x + 38,y - 10,claveFlat);
        painter->drawPixmap(x + 46,y + 10,claveFlat);
        painter->drawPixmap(x + 54,y - 5, claveFlat);
        painter->drawPixmap(x + 62,y + 15,claveFlat);
        painter->drawPixmap(x + 70,y,     claveFlat);
        painter->drawPixmap(x + 78,y + 20,claveFlat);
        return ;
    default:
        return;;
    }
}

void RenderPartitura::setK(int k) {
    this->key = k;
}

void RenderPartitura::setMeter(Meter m) {
    this->meter = m;
}

int RenderPartitura::calculateDistance(Partitura *part)
{
    int distanceLeft = 0;
    QList<Compas*>* compases = part->getCompases();
    for(int i = 0; i < compases->size()-1; i++) {
        int d = this->getCompasLength(compases->at(i), i);
        distanceLeft += d;
    }
    return distanceLeft;
}

int RenderPartitura::getCompasLength(Compas *compas, int i)
{
    int length = 0;
    if(compas->getOpened()){
            if(compas->getNotas()->size() > 0 && !valMetrica(compas)){
                length = (25 + (compas->getNotas()->size() * NOTELENGTH ));
            } else if(compas->getNotas()->size() > 0 && valMetrica(compas)) {
                length = this->maxCompasLength(i);
            } else if(compas->getNotas()->size() == 0){
                length = 0;
            }
    }
    return length;
}

int RenderPartitura::getUpAndDownValue(int rTono) {
    if (rTono == -1) {
        return 0;
    }
    int index = rTono % 12;
    switch (this->key) {
    case 0:
        return this->natural.at(index);
    case 1:
        return this->sharp1.at(index);
    case 2:
        return this->sharp2.at(index);
    case 3:
        return this->sharp3.at(index);
    case 4:
        return this->sharp4.at(index);
    case 5:
        return this->sharp5.at(index);
    case 6:
        return this->sharp6.at(index);
    case 7:
        return this->sharp7.at(index);
    case -1:
        return this->flat1.at(index);
    case -2:
        return this->flat2.at(index);
    case -3:
        return this->flat3.at(index);
    case -4:
        return this->flat4.at(index);
    case -5:
        return this->flat5.at(index);
    case -6:
        return this->flat6.at(index);
    case -7:
        return this->flat7.at(index);
    }
}

QString RenderPartitura::getNotaPath(QString fileName, int upDown) {
    QString temp;
    temp.setNum(upDown);
    QString path(":/images/" + fileName + "_" + temp + ".png");
    return path;
}

void RenderPartitura::drawText(QPainter *painter)
{
    int lastCompasHit = MARGINLEFT + 35 + (abs(key)+1)*8 + MARGINRIGHT + 2;
    for(int i=0; i<chordText.size(); i++) {
        int next = lastCompasHit;
        for(int j=0; j<chordText[i].size(); j++) {
            painter->drawText(next, 30, chordText[i][j].c_str());
            next += maxCompasLength(i)/2;
        }
        lastCompasHit += this->maxCompasLength(i);
    }
}

void RenderPartitura::setChordText(std::vector<std::vector<std::string> > text)
{
    hasText = true;
    chordText = text;
    update();
}
