/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sat Mar 12 11:55:59 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x0a,
      33,   12,   11,   11, 0x0a,
      51,   46,   11,   11, 0x0a,
      76,   68,   11,   11, 0x0a,
     108,   99,   11,   11, 0x0a,
     144,  132,   11,   11, 0x0a,
     181,  171,   11,   11, 0x0a,
     210,  206,   11,   11, 0x0a,
     232,  230,   11,   11, 0x0a,
     250,   11,   11,   11, 0x08,
     280,   11,   11,   11, 0x08,
     306,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,
     355,   11,   11,   11, 0x08,
     374,   11,   11,   11, 0x08,
     393,   11,   11,   11, 0x08,
     412,   11,   11,   11, 0x08,
     431,   11,   11,   11, 0x08,
     450,   11,   11,   11, 0x08,
     469,   11,   11,   11, 0x08,
     488,   11,   11,   11, 0x08,
     507,   11,   11,   11, 0x08,
     526,   11,   11,   11, 0x08,
     554,   11,   11,   11, 0x08,
     580,   11,   11,   11, 0x08,
     606,   11,   11,   11, 0x08,
     640,  632,   11,   11, 0x08,
     681,   11,   11,   11, 0x08,
     702,  693,   11,   11, 0x08,
     741,  721,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0midiNote\0noteOn(int)\0"
    "noteOff(int)\0flag\0pauseActive(int)\0"
    "channel\0setChannelChanged(int)\0velocity\0"
    "setVelocityChanged(int)\0base_octave\0"
    "setBase_octaveChanged(int)\0transpose\0"
    "setTransposeChanged(int)\0run\0"
    "setEditEnable(bool)\0p\0editChord(QPoint)\0"
    "on_actionOpenMidi_triggered()\0"
    "on_actionOpen_triggered()\0"
    "on_actionPlayMidi_triggered()\0"
    "on_btn_9_clicked()\0on_btn_8_clicked()\0"
    "on_btn_7_clicked()\0on_btn_6_clicked()\0"
    "on_btn_5_clicked()\0on_btn_4_clicked()\0"
    "on_btn_3_clicked()\0on_btn_2_clicked()\0"
    "on_btn_1_clicked()\0on_btn_0_clicked()\0"
    "on_chordAnalyse_triggered()\0"
    "on_redoAction_triggered()\0"
    "on_undoAction_triggered()\0"
    "on_actionSave_triggered()\0checked\0"
    "on_actionMIDI_controller_triggered(bool)\0"
    "saveStaff()\0fileName\0loadStaff(QString)\0"
    "exitCode,exitStatus\0"
    "processFinished(int,QProcess::ExitStatus)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: noteOn((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 1: noteOff((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: pauseActive((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: setChannelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: setVelocityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: setBase_octaveChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: setTransposeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: setEditEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: editChord((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 9: on_actionOpenMidi_triggered(); break;
        case 10: on_actionOpen_triggered(); break;
        case 11: on_actionPlayMidi_triggered(); break;
        case 12: on_btn_9_clicked(); break;
        case 13: on_btn_8_clicked(); break;
        case 14: on_btn_7_clicked(); break;
        case 15: on_btn_6_clicked(); break;
        case 16: on_btn_5_clicked(); break;
        case 17: on_btn_4_clicked(); break;
        case 18: on_btn_3_clicked(); break;
        case 19: on_btn_2_clicked(); break;
        case 20: on_btn_1_clicked(); break;
        case 21: on_btn_0_clicked(); break;
        case 22: on_chordAnalyse_triggered(); break;
        case 23: on_redoAction_triggered(); break;
        case 24: on_undoAction_triggered(); break;
        case 25: on_actionSave_triggered(); break;
        case 26: on_actionMIDI_controller_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: saveStaff(); break;
        case 28: loadStaff((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: processFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 30;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
