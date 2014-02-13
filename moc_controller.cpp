/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created: Sat Mar 12 11:23:11 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controller[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   12,   11,   11, 0x05,
      49,   40,   11,   11, 0x05,
      82,   70,   11,   11, 0x05,
     116,  106,   11,   11, 0x05,
     142,  138,   11,   11, 0x05,
     168,  159,   11,   11, 0x05,
     199,  194,   11,   11, 0x05,
     220,  214,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     236,   12,   11,   11, 0x0a,
     259,   40,   11,   11, 0x0a,
     283,   70,   11,   11, 0x0a,
     310,  106,   11,   11, 0x0a,
     341,  335,   11,   11, 0x0a,
     368,  362,   11,   11, 0x0a,
     395,  391,   11,   11, 0x0a,
     422,  414,   11,   11, 0x08,
     452,   11,   11,   11, 0x08,
     479,  473,   11,   11, 0x08,
     513,  473,   11,   11, 0x08,
     547,  473,   11,   11, 0x08,
     579,  473,   11,   11, 0x08,
     617,  473,   11,   11, 0x08,
     657,  473,   11,   11, 0x08,
     693,  473,   11,   11, 0x08,
     736,  730,   11,   11, 0x08,
     755,  194,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Controller[] = {
    "Controller\0\0channel\0channelChanged(int)\0"
    "velocity\0velocityChanged(int)\0base_octave\0"
    "base_octaveChanged(int)\0transpose\0"
    "transposeChanged(int)\0run\0enableEdit(bool)\0"
    "duration\0durationChanged(QAction*)\0"
    "flag\0pauseFlag(int)\0isDot\0dotEnable(bool)\0"
    "setCurrentChannel(int)\0setCurrentVelocity(int)\0"
    "setCurrentBase_octave(int)\0"
    "setCurrentTranspose(int)\0speed\0"
    "setCurrentSpeed(int)\0meter\0"
    "setCurrentMeter(Meter)\0key\0"
    "setCurrentKey(int)\0checked\0"
    "on_btn_note_dot_clicked(bool)\0"
    "on_btn_run_clicked()\0value\0"
    "on_slider_speed_valueChanged(int)\0"
    "on_slider_meter_valueChanged(int)\0"
    "on_slider_key_valueChanged(int)\0"
    "on_slider_transpose_valueChanged(int)\0"
    "on_slider_base_octave_valueChanged(int)\0"
    "on_slider_channel_valueChanged(int)\0"
    "on_slider_velocity_valueChanged(int)\0"
    "btnID\0durationCheck(int)\0pauseCheck(int)\0"
};

const QMetaObject Controller::staticMetaObject = {
    { &QToolBox::staticMetaObject, qt_meta_stringdata_Controller,
      qt_meta_data_Controller, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controller::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controller))
        return static_cast<void*>(const_cast< Controller*>(this));
    return QToolBox::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: channelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: velocityChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: base_octaveChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: transposeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: enableEdit((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: durationChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 6: pauseFlag((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: dotEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: setCurrentChannel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setCurrentVelocity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: setCurrentBase_octave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: setCurrentTranspose((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: setCurrentSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: setCurrentMeter((*reinterpret_cast< Meter(*)>(_a[1]))); break;
        case 14: setCurrentKey((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: on_btn_note_dot_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: on_btn_run_clicked(); break;
        case 17: on_slider_speed_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: on_slider_meter_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: on_slider_key_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: on_slider_transpose_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: on_slider_base_octave_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: on_slider_channel_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: on_slider_velocity_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: durationCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: pauseCheck((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 26;
    }
    return _id;
}

// SIGNAL 0
void Controller::channelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::velocityChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::base_octaveChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Controller::transposeChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Controller::enableEdit(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Controller::durationChanged(QAction * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Controller::pauseFlag(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Controller::dotEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
