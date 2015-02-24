/****************************************************************************
** Meta object code from reading C++ file 'selectmodulemenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/selectmodulemenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectmodulemenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SelectModuleMenu_t {
    QByteArrayData data[10];
    char stringdata[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectModuleMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectModuleMenu_t qt_meta_stringdata_SelectModuleMenu = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 17),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 7),
QT_MOC_LITERAL(4, 44, 15),
QT_MOC_LITERAL(5, 60, 7),
QT_MOC_LITERAL(6, 68, 25),
QT_MOC_LITERAL(7, 94, 30),
QT_MOC_LITERAL(8, 125, 27),
QT_MOC_LITERAL(9, 153, 19)
    },
    "SelectModuleMenu\0setModulesEnabled\0\0"
    "enabled\0QList<QAction*>\0actions\0"
    "setRPeeksDetectionEnabled\0"
    "setRPeeksDetectionGroupEnabled\0"
    "setQRSDetectionGroupEnabled\0"
    "setRestGroupEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectModuleMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       6,    1,   44,    2, 0x08 /* Private */,
       7,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void SelectModuleMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SelectModuleMenu *_t = static_cast<SelectModuleMenu *>(_o);
        switch (_id) {
        case 0: _t->setModulesEnabled((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QList<QAction*>(*)>(_a[2]))); break;
        case 1: _t->setRPeeksDetectionEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setRPeeksDetectionGroupEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setQRSDetectionGroupEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setRestGroupEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QAction*> >(); break;
            }
            break;
        }
    }
}

const QMetaObject SelectModuleMenu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_SelectModuleMenu.data,
      qt_meta_data_SelectModuleMenu,  qt_static_metacall, 0, 0}
};


const QMetaObject *SelectModuleMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectModuleMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectModuleMenu.stringdata))
        return static_cast<void*>(const_cast< SelectModuleMenu*>(this));
    return QMenu::qt_metacast(_clname);
}

int SelectModuleMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
