/****************************************************************************
** Meta object code from reading C++ file 'plotsdrawer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../plotsdrawer.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotsdrawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN11PlotsDrawerE_t {};
} // unnamed namespace

template <> constexpr inline auto PlotsDrawer::qt_create_metaobjectdata<qt_meta_tag_ZN11PlotsDrawerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlotsDrawer",
        "redrawPlotByBinSizeChange_slot",
        "",
        "bs",
        "drawPlot",
        "onCandleXAxisChanged",
        "QCPRange",
        "range",
        "onCandleYAxisChanged",
        "onXAxisPlotRangeChanged",
        "syncAxesToCandleX",
        "syncAxesToCandleY"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'redrawPlotByBinSizeChange_slot'
        QtMocHelpers::SlotData<void(uint)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::UInt, 3 },
        }}),
        // Slot 'drawPlot'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onCandleXAxisChanged'
        QtMocHelpers::SlotData<void(const QCPRange &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onCandleYAxisChanged'
        QtMocHelpers::SlotData<void(const QCPRange &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'onXAxisPlotRangeChanged'
        QtMocHelpers::SlotData<void(const QCPRange &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'syncAxesToCandleX'
        QtMocHelpers::SlotData<void(const QCPRange &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Slot 'syncAxesToCandleY'
        QtMocHelpers::SlotData<void(const QCPRange &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlotsDrawer, qt_meta_tag_ZN11PlotsDrawerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlotsDrawer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlotsDrawerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlotsDrawerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11PlotsDrawerE_t>.metaTypes,
    nullptr
} };

void PlotsDrawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlotsDrawer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->redrawPlotByBinSizeChange_slot((*reinterpret_cast<std::add_pointer_t<uint>>(_a[1]))); break;
        case 1: _t->drawPlot(); break;
        case 2: _t->onCandleXAxisChanged((*reinterpret_cast<std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 3: _t->onCandleYAxisChanged((*reinterpret_cast<std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 4: _t->onXAxisPlotRangeChanged((*reinterpret_cast<std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 5: _t->syncAxesToCandleX((*reinterpret_cast<std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 6: _t->syncAxesToCandleY((*reinterpret_cast<std::add_pointer_t<QCPRange>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PlotsDrawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlotsDrawer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11PlotsDrawerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PlotsDrawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
