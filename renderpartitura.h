#ifndef RENDERPARTITURA_H
#define RENDERPARTITURA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QTimer>
#include <QRegion>
#include <QPainter>
#include <QMenu>
#include <QUndoStack>

#include "staff/partitura.h"
#include "staff/compas.h"

enum cursorType {select,redonda,blanca,negra,corchea,semicorchea,fusa,semifusa,s1,s2,s4,s8,s16,s32,s64};
enum partituraFlag {PARTITURA1, PARTITURA2};
enum completoFlag {INCOMPLETO, COMPLETO};

class RenderPartitura : public QWidget
{
	Q_OBJECT

public:
    RenderPartitura(QWidget *parent = 0);
    RenderPartitura(int k, Meter m, Partitura *partitura, QWidget *parent = 0);
    void addNota(int tono, partituraFlag pFlag, completoFlag cFlag);
    void addNota(int tono, partituraFlag pFlag, QPoint selPos);
    void addPause(partituraFlag pFlag, completoFlag cFlag);
    void setChordText(std::vector<std::vector<std::string> > text);
    bool isCompasCompleto(Partitura *partitura);


public slots:
    void setPuntillo(bool p);
    void showCompass(Compas *compas);
    void expandAll();
    void collapseAll();
    void changeCursor(QAction *action);
    void deleteNotes();
    void copy();
    void cut();
    void paste();
    void setMetrica(int n,int d);
    void setCurrentPent(int i);
    void joinNotes();
    void tieNotes();
    void slurNotes();
    
    // my added
    void setK(int k);
    void setMeter(Meter m);
    int calculateDistance(Partitura * part);

private slots:
    void updateCompass();
    void pasteIn();

signals :
    void showWaveCompass(Compas *compas);

    void ensureVisibleSignal(int x,int y);

    void addChord(QPoint p);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:

    QVector<int> flat7;
    QVector<int> flat6;
    QVector<int> flat5;
    QVector<int> flat4;
    QVector<int> flat3;
    QVector<int> flat2;
    QVector<int> flat1;
    QVector<int> natural;
    QVector<int> sharp1;
    QVector<int> sharp2;
    QVector<int> sharp3;
    QVector<int> sharp4;
    QVector<int> sharp5;
    QVector<int> sharp6;
    QVector<int> sharp7;

    int key;
    Meter meter;
    std::vector<std::vector<std::string> > chordText;

    Partitura *partitura;
    bool puntillo;
    bool dual;
    bool hasText;

    Partitura *partitura1;
    Partitura *partitura2;

    Compas *splitOver;
    Partitura *selectedP;
    QList<Nota *> * selectedN;
    bool selecting;
    QPoint selS;
    QPoint selE;
    bool toPaste;
    QMenu *contextMenu;

    QAction *deleteAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *joinAction;
    QAction *tieAction;
    QAction *slurAction;

    QUndoStack *undoStack;

    bool toSetMetrica;
    int num;
    int den;

    QPoint cursor;
    int currentCursor;
    int lastCursor;
    bool isSelect;

    QTimer *timer;

    int color;

    QRegion *updatedRegionA;
    QRegion *updatedRegionB;

    int calcTono(QPoint p);
    void drawRedonda(QPoint c,QPainter *p,int sil);
    void drawBlanca(QPoint c,bool inv,QPainter *p,int sil);
    void drawNegra(QPoint c,bool inv,QPainter *p,int sil);
    void drawCorchea(QPoint c,bool inv,QPainter *p,int sil);
    void drawSemicorchea(QPoint c,bool inv,QPainter *p,int sil);
    void drawFusa(QPoint c,bool inv,QPainter *p,int sil);
    void drawSemifusa(QPoint c,bool inv,QPainter *p,int sil);
    void drawLines(int marginTop, int length, QPainter *painter,QColor color);
    void drawText(QPainter *painter);
    int maxCompasLength(Compas * compas, Compas * aux=0);
    int maxCompasLength(int i);
    int getCompasLength(Compas *compas);
    int getCompasLength(Compas *compas, int i);
    int calcPentLong(QList<Compas *> * compases);
    int maxPentLong(QList<Compas *> * compases1,QList<Compas *> * compases2);
    void drawPentagrama(QPainter * painter, Partitura * part,float margintop);
    QPolygonF poliPoints(float fx,float fy);
    QPolygonF poliPointsInv(float fx, float fy);
    Compas * calcButtonHit(QPoint p);
    int nButtonHit(QPoint p);
    Compas * calcCompassHit(QPoint p);
    int calcNotePos(QPoint p);
    Partitura * getPartitura(QPoint p);
    bool valMetrica(Compas *c);
    void createContextMenu();
    void drawMetrica(QPainter *painter,int n,int x,int y);
    void drawNota(QPainter *painter,QPoint punto,Nota *nota);
    bool drawGroupedNotes(QPainter *painter,Nota *nota,QPoint punto,float margintop);
    void drawSlur(QPainter *painter,QList<Nota *> *notas,QPoint pt1,QPoint pt2);
    int calcChordPos(QPoint p);
    void drawChord(QPainter *painter,QPoint punto, Nota *nota, bool dPlica);
    void drawTie(QPoint tiePoint,QPoint punto,QPainter *painter, bool tieInv, bool inv);
    QList<Nota *> * cloneNoteList(QList<Nota *> *nlist);
    QList<Nota *> * editAction(bool toCopy,bool toDelete);
    bool potDos(int m);
    void drawPuntillo(QPainter *painter, Nota *nota,QPoint punto);
    void addNota(QPoint p, int rTono);

    void drawSharp(int k, int x, int y, QPainter *painter);
    int getUpAndDownValue(int rTono);
    QString getNotaPath(QString fileName, int upDown);
};

#endif
