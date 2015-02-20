/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 8),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 7),
QT_MOC_LITERAL(4, 29, 14),
QT_MOC_LITERAL(5, 44, 14),
QT_MOC_LITERAL(6, 59, 8),
QT_MOC_LITERAL(7, 68, 6),
QT_MOC_LITERAL(8, 75, 14),
QT_MOC_LITERAL(9, 90, 26),
QT_MOC_LITERAL(10, 117, 19),
QT_MOC_LITERAL(11, 137, 6),
QT_MOC_LITERAL(12, 144, 4),
QT_MOC_LITERAL(13, 149, 31),
QT_MOC_LITERAL(14, 181, 24),
QT_MOC_LITERAL(15, 206, 9),
QT_MOC_LITERAL(16, 216, 23),
QT_MOC_LITERAL(17, 240, 17),
QT_MOC_LITERAL(18, 258, 6),
QT_MOC_LITERAL(19, 265, 11),
QT_MOC_LITERAL(20, 277, 12),
QT_MOC_LITERAL(21, 290, 15),
QT_MOC_LITERAL(22, 306, 18)
    },
    "MainWindow\0openFile\0\0compute\0"
    "generateReport\0channelChanged\0QAction*\0"
    "action\0selectedModule\0ecgFiltrationFilterChanged\0"
    "ECGFiltrationMethod\0filter\0name\0"
    "rPeaksDetectionAlgorithmChanged\0"
    "RPeaksDetectionAlgorithm\0algorithm\0"
    "sleepApneaMethodChanged\0SleepApneaMetrics\0"
    "method\0graphZoomIn\0graphZoomOut\0"
    "graphHandCursor\0graphPointerCursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       8,    1,   80,    2, 0x08 /* Private */,
       9,    2,   83,    2, 0x08 /* Private */,
      13,    2,   88,    2, 0x08 /* Private */,
      16,    2,   93,    2, 0x08 /* Private */,
      19,    0,   98,    2, 0x08 /* Private */,
      20,    0,   99,    2, 0x08 /* Private */,
      21,    0,  100,    2, 0x08 /* Private */,
      22,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,   11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,   15,   12,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QString,   18,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->openFile(); break;
        case 1: _t->compute(); break;
        case 2: _t->generateReport(); break;
        case 3: _t->channelChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->selectedModule((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->ecgFiltrationFilterChanged((*reinterpret_cast< ECGFiltrationMethod(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->rPeaksDetectionAlgorithmChanged((*reinterpret_cast< RPeaksDetectionAlgorithm(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->sleepApneaMethodChanged((*reinterpret_cast< SleepApneaMetrics(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->graphZoomIn(); break;
        case 9: _t->graphZoomOut(); break;
        case 10: _t->graphHandCursor(); break;
        case 11: _t->graphPointerCursor(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
