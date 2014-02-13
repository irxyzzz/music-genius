#include "octavekeybd.h"
#include <QtDebug>

OctaveKeybd::OctaveKeybd(QWidget *parent) : PianoKeybd(parent)
{
}

void OctaveKeybd::keyPressEvent(QKeyEvent *e)
{
    if(e->key()>48 && e->key()<56) {
        emit this->changeOctave(e->key()-48);
    } else if(e->key()==Qt::Key_Space && e->modifiers()==Qt::NoModifier) {
        emit this->changePause(-1);
    } else if(e->key()==Qt::Key_Space && e->modifiers()==Qt::ShiftModifier){
        emit this->changePause(-2);
    } else if(e->key()==Qt::Key_Z && e->modifiers()==Qt::ShiftModifier){
        emit this->editChange(-3);
    } else if(e->key()==Qt::Key_Z && e->modifiers()==(Qt::ShiftModifier|Qt::ControlModifier)){
        emit this->editChange(-4);
    } else {
        PianoKeybd::keyPressEvent(e);
    }
}
