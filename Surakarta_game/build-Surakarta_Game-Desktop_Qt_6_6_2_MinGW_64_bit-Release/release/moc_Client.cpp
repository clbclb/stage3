/****************************************************************************
** Meta object code from reading C++ file 'Client.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Surakarta_Game/Client.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Client.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSClientENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSClientENDCLASS = QtMocHelpers::stringData(
    "Client",
    "Player_Black",
    "",
    "Player_White",
    "ip_reset",
    "prt",
    "receiveData",
    "NetworkData",
    "data",
    "slot_panel_button2_Clicked",
    "initgame",
    "on_pushButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSClientENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[7];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[9];
    char stringdata5[4];
    char stringdata6[12];
    char stringdata7[12];
    char stringdata8[5];
    char stringdata9[27];
    char stringdata10[9];
    char stringdata11[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSClientENDCLASS_t qt_meta_stringdata_CLASSClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Client"
        QT_MOC_LITERAL(7, 12),  // "Player_Black"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 12),  // "Player_White"
        QT_MOC_LITERAL(34, 8),  // "ip_reset"
        QT_MOC_LITERAL(43, 3),  // "prt"
        QT_MOC_LITERAL(47, 11),  // "receiveData"
        QT_MOC_LITERAL(59, 11),  // "NetworkData"
        QT_MOC_LITERAL(71, 4),  // "data"
        QT_MOC_LITERAL(76, 26),  // "slot_panel_button2_Clicked"
        QT_MOC_LITERAL(103, 8),  // "initgame"
        QT_MOC_LITERAL(112, 21)   // "on_pushButton_clicked"
    },
    "Client",
    "Player_Black",
    "",
    "Player_White",
    "ip_reset",
    "prt",
    "receiveData",
    "NetworkData",
    "data",
    "slot_panel_button2_Clicked",
    "initgame",
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSClientENDCLASS[] = {

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
       6,    1,   66,    2, 0x0a,    5 /* Public */,
       9,    0,   69,    2, 0x0a,    7 /* Public */,
      10,    0,   70,    2, 0x0a,    8 /* Public */,
      11,    0,   71,    2, 0x08,    9 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Client::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Client, std::true_type>,
        // method 'Player_Black'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Player_White'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ip_reset'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'prt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'receiveData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>,
        // method 'slot_panel_button2_Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'initgame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Client *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Player_Black(); break;
        case 1: _t->Player_White(); break;
        case 2: _t->ip_reset(); break;
        case 3: _t->prt(); break;
        case 4: _t->receiveData((*reinterpret_cast< std::add_pointer_t<NetworkData>>(_a[1]))); break;
        case 5: _t->slot_panel_button2_Clicked(); break;
        case 6: _t->initgame(); break;
        case 7: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Client::*)();
            if (_t _q_method = &Client::Player_Black; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (_t _q_method = &Client::Player_White; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (_t _q_method = &Client::ip_reset; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Client::*)();
            if (_t _q_method = &Client::prt; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Client::Player_Black()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Client::Player_White()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Client::ip_reset()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void Client::prt()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
