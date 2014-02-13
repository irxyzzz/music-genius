/****************************************************************************
** Meta object code from reading C++ file 'renderpartitura.h'
**
** Created: Sat Mar 12 11:23:15 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "renderpartitura.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderpartitura.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderPartitura[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x05,
      53,   49,   16,   16, 0x05,
      84,   82,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     101,   82,   16,   16, 0x0a,
     119,   17,   16,   16, 0x0a,
     140,   16,   16,   16, 0x0a,
     152,   16,   16,   16, 0x0a,
     173,  166,   16,   16, 0x0a,
     196,   16,   16,   16, 0x0a,
     210,   16,   16,   16, 0x0a,
     217,   16,   16,   16, 0x0a,
     223,   16,   16,   16, 0x0a,
     235,  231,   16,   16, 0x0a,
     257,  255,   16,   16, 0x0a,
     277,   16,   16,   16, 0x0a,
     289,   16,   16,   16, 0x0a,
     300,   16,   16,   16, 0x0a,
     314,  312,   16,   16, 0x0a,
     326,  324,   16,   16, 0x0a,
     351,  346,  342,   16, 0x0a,
     381,   16,   16,   16, 0x08,
     397,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RenderPartitura[] = {
    "RenderPartitura\0\0compas\0"
    "showWaveCompass(Compas*)\0x,y\0"
    "ensureVisibleSignal(int,int)\0p\0"
    "addChord(QPoint)\0setPuntillo(bool)\0"
    "showCompass(Compas*)\0expandAll()\0"
    "collapseAll()\0action\0changeCursor(QAction*)\0"
    "deleteNotes()\0copy()\0cut()\0paste()\0"
    "n,d\0setMetrica(int,int)\0i\0setCurrentPent(int)\0"
    "joinNotes()\0tieNotes()\0slurNotes()\0k\0"
    "setK(int)\0m\0setMeter(Meter)\0int\0part\0"
    "calculateDistance(Partitura*)\0"
    "updateCompass()\0pasteIn()\0"
};

const QMetaObject RenderPartitura::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RenderPartitura,
      qt_meta_data_RenderPartitura, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderPartitura::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderPartitura::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderPartitura::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderPartitura))
        return static_cast<void*>(const_cast< RenderPartitura*>(this));
    return QWidget::qt_metacast(_clname);
}

int RenderPartitura::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: showWaveCompass((*reinterpret_cast< Compas*(*)>(_a[1]))); break;
        case 1: ensureVisibleSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: addChord((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: setPuntillo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: showCompass((*reinterpret_cast< Compas*(*)>(_a[1]))); break;
        case 5: expandAll(); break;
        case 6: collapseAll(); break;
        case 7: changeCursor((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 8: deleteNotes(); break;
        case 9: copy(); break;
        case 10: cut(); break;
        case 11: paste(); break;
        case 12: setMetrica((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: setCurrentPent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: joinNotes(); break;
        case 15: tieNotes(); break;
        case 16: slurNotes(); break;
        case 17: setK((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setMeter((*reinterpret_cast< Meter(*)>(_a[1]))); break;
        case 19: { int _r = calculateDistance((*reinterpret_cast< Partitura*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 20: updateCompass(); break;
        case 21: pasteIn(); break;
        default: ;
        }
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void RenderPartitura::showWaveCompass(Compas * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RenderPartitura::ensureVisibleSignal(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RenderPartitura::addChord(QPoint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
