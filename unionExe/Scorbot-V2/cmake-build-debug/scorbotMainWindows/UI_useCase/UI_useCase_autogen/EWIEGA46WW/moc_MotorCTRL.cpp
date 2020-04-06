/****************************************************************************
** Meta object code from reading C++ file 'MotorCTRL.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../scorbotMainWindows/UI_useCase/MotorCTRL.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MotorCTRL.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MotorCTRL_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MotorCTRL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MotorCTRL_t qt_meta_stringdata_MotorCTRL = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MotorCTRL"
QT_MOC_LITERAL(1, 10, 9), // "changeObj"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "EncoderMot*"
QT_MOC_LITERAL(4, 33, 6), // "newObj"
QT_MOC_LITERAL(5, 40, 6), // "goHome"
QT_MOC_LITERAL(6, 47, 18), // "motorDirectControl"
QT_MOC_LITERAL(7, 66, 4), // "push"
QT_MOC_LITERAL(8, 71, 22), // "freeMoveWindowsShowing"
QT_MOC_LITERAL(9, 94, 4) // "show"

    },
    "MotorCTRL\0changeObj\0\0EncoderMot*\0"
    "newObj\0goHome\0motorDirectControl\0push\0"
    "freeMoveWindowsShowing\0show"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MotorCTRL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,
       6,    1,   38,    2, 0x08 /* Private */,
       8,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,

       0        // eod
};

void MotorCTRL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MotorCTRL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeObj((*reinterpret_cast< EncoderMot*(*)>(_a[1]))); break;
        case 1: _t->goHome(); break;
        case 2: _t->motorDirectControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->freeMoveWindowsShowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MotorCTRL::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MotorCTRL.data,
    qt_meta_data_MotorCTRL,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MotorCTRL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MotorCTRL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MotorCTRL.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MotorCTRL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
