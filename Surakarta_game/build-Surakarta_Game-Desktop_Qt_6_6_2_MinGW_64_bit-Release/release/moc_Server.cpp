/****************************************************************************
** Meta object code from reading C++ file 'Server.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Surakarta_Game/Server.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSServerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSServerENDCLASS = QtMocHelpers::stringData(
    "Server",
    "Player_Black",
    "",
    "Player_White",
    "prt",
    "port_reset",
    "receiveData",
    "QTcpSocket*",
    "client",
    "NetworkData",
    "data",
    "slotNewConnection",
    "slot_timeout",
    "on_pushButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSServerENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[7];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[4];
    char stringdata5[11];
    char stringdata6[12];
    char stringdata7[12];
    char stringdata8[7];
    char stringdata9[12];
    char stringdata10[5];
    char stringdata11[18];
    char stringdata12[13];
    char stringdata13[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSServerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSServerENDCLASS_t qt_meta_stringdata_CLASSServerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Server"
        QT_MOC_LITERAL(7, 12),  // "Player_Black"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 12),  // "Player_White"
        QT_MOC_LITERAL(34, 3),  // "prt"
        QT_MOC_LITERAL(38, 10),  // "port_reset"
        QT_MOC_LITERAL(49, 11),  // "receiveData"
        QT_MOC_LITERAL(61, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(73, 6),  // "client"
        QT_MOC_LITERAL(80, 11),  // "NetworkData"
        QT_MOC_LITERAL(92, 4),  // "data"
        QT_MOC_LITERAL(97, 17),  // "slotNewConnection"
        QT_MOC_LITERAL(115, 12),  // "slot_timeout"
        QT_MOC_LITERAL(128, 21)   // "on_pushButton_clicked"
    },
    "Server",
    "Player_Black",
    "",
    "Player_White",
    "prt",
    "port_reset",
    "receiveData",
    "QTcpSocket*",
    "client",
    "NetworkData",
    "data",
    "slotNewConnection",
    "slot_timeout",
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSServerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    0,   65,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    2,   66,    2, 0x0a,    5 /* Public */,
      11,    0,   71,    2, 0x0a,    8 /* Public */,
      12,    0,   72,    2, 0x0a,    9 /* Public */,
      13,    0,   73,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Server::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSServerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSServerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSServerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Server, std::true_type>,
        // method 'Player_Black'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Player_White'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'port_reset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>,
        // method 'slotNewConnection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slot_timeout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Server *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Player_Black(); break;
        case 1: _t->Player_White(); break;
        case 2: _t->prt(); break;
        case 3: _t->port_reset(); break;
        case 4: _t->receiveData((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[2]))); break;
        case 5: _t->slotNewConnection(); break;
        case 6: _t->slot_timeout(); break;
        case 7: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Server::*)();
            if (_t _q_method = &Server::Player_Black; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Server::*)();
            if (_t _q_method = &Server::Player_White; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Server::*)();
            if (_t _q_method = &Server::prt; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Server::*)();
            if (_t _q_method = &Server::port_reset; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Server::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSServerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Server::Player_Black()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Server::Player_White()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Server::prt()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Server::port_reset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
