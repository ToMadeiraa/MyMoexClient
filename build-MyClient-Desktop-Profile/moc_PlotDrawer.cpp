/****************************************************************************
** Meta object code from reading C++ file 'PlotDrawer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/PlotDrawer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlotDrawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlotDrawer_t {
    QByteArrayData data[10];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlotDrawer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlotDrawer_t qt_meta_stringdata_PlotDrawer = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PlotDrawer"
QT_MOC_LITERAL(1, 11, 8), // "drawPlot"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "setNewRange"
QT_MOC_LITERAL(4, 33, 12), // "QWheelEvent*"
QT_MOC_LITERAL(5, 46, 1), // "e"
QT_MOC_LITERAL(6, 48, 12), // "setNewRangeX"
QT_MOC_LITERAL(7, 61, 12), // "setNewRangeY"
QT_MOC_LITERAL(8, 74, 10), // "mouseMoved"
QT_MOC_LITERAL(9, 85, 12) // "QMouseEvent*"

    },
    "PlotDrawer\0drawPlot\0\0setNewRange\0"
    "QWheelEvent*\0e\0setNewRangeX\0setNewRangeY\0"
    "mouseMoved\0QMouseEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlotDrawer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    5,

       0        // eod
};

void PlotDrawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlotDrawer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->drawPlot(); break;
        case 1: _t->setNewRange((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 2: _t->setNewRangeX(); break;
        case 3: _t->setNewRangeY(); break;
        case 4: _t->mouseMoved((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlotDrawer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PlotDrawer.data,
    qt_meta_data_PlotDrawer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlotDrawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotDrawer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlotDrawer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlotDrawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
