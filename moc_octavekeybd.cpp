/****************************************************************************
** Meta object code from reading C++ file 'octavekeybd.h'
**
** Created: Sat Mar 12 11:23:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "octavekeybd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'octavekeybd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OctaveKeybd[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x05,
      43,   38,   12,   12, 0x05,
      60,   38,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_OctaveKeybd[] = {
    "OctaveKeybd\0\0octave\0changeOctave(int)\0"
    "flag\0changePause(int)\0editChange(int)\0"
};

const QMetaObject OctaveKeybd::staticMetaObject = {
    { &PianoKeybd::staticMetaObject, qt_meta_stringdata_OctaveKeybd,
      qt_meta_data_OctaveKeybd, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OctaveKeybd::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OctaveKeybd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OctaveKeybd::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OctaveKeybd))
        return static_cast<void*>(const_cast< OctaveKeybd*>(this));
    return PianoKeybd::qt_metacast(_clname);
}

int OctaveKeybd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PianoKeybd::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeOctave((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: changePause((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: editChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void OctaveKeybd::changeOctave(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OctaveKeybd::changePause(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OctaveKeybd::editChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
