/****************************************************************************
** Meta object code from reading C++ file 'UartConnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../../Documenti/Scorbot-CA/unionExe/Scorbot-V2/scorbotMainWindows/UI_useCase/UartConnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UartConnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UartConnect_t {
    QByteArrayData data[7];
    char stringdata0[107];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UartConnect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UartConnect_t qt_meta_stringdata_UartConnect = {
    {
QT_MOC_LITERAL(0, 0, 11), // "UartConnect"
QT_MOC_LITERAL(1, 12, 8), // "uartMake"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 21), // "serialConnect_handler"
QT_MOC_LITERAL(4, 44, 19), // "uartChoised_handler"
QT_MOC_LITERAL(5, 64, 23), // "closeConnection_handler"
QT_MOC_LITERAL(6, 88, 18) // "resetBoard_handler"

    },
    "UartConnect\0uartMake\0\0serialConnect_handler\0"
    "uartChoised_handler\0closeConnection_handler\0"
    "resetBoard_handler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UartConnect[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UartConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UartConnect *_t = static_cast<UartConnect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uartMake(); break;
        case 1: _t->serialConnect_handler(); break;
        case 2: _t->uartChoised_handler(); break;
        case 3: _t->closeConnection_handler(); break;
        case 4: _t->resetBoard_handler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (UartConnect::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UartConnect::uartMake)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UartConnect::staticMetaObject = {
    { &UartChoise::staticMetaObject, qt_meta_stringdata_UartConnect.data,
      qt_meta_data_UartConnect,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UartConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UartConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UartConnect.stringdata0))
        return static_cast<void*>(this);
    return UartChoise::qt_metacast(_clname);
}

int UartConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = UartChoise::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void UartConnect::uartMake()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
