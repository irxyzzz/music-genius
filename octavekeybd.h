#ifndef OCTAVEKEYBD_H
#define OCTAVEKEYBD_H

#include "pianokeybd.h"
#include <QKeyEvent>

class OctaveKeybd : public PianoKeybd
{
    Q_OBJECT
public:
    OctaveKeybd(QWidget *parent = 0);
signals:
    void changeOctave(int octave);
    void changePause(int flag); // staffSol: -1; staffFa: -2;
    void editChange(int flag);  // undo: -3; redo: -4
protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // OCTAVEKEYBD_H
