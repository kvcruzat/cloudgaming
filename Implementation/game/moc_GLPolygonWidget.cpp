/****************************************************************************
** Meta object code from reading C++ file 'GLPolygonWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GLPolygonWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLPolygonWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GLPolygonWidget_t {
    QByteArrayData data[20];
    char stringdata[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GLPolygonWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GLPolygonWidget_t qt_meta_stringdata_GLPolygonWidget = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 10),
QT_MOC_LITERAL(2, 27, 0),
QT_MOC_LITERAL(3, 28, 1),
QT_MOC_LITERAL(4, 30, 10),
QT_MOC_LITERAL(5, 41, 1),
QT_MOC_LITERAL(6, 43, 10),
QT_MOC_LITERAL(7, 54, 1),
QT_MOC_LITERAL(8, 56, 7),
QT_MOC_LITERAL(9, 64, 7),
QT_MOC_LITERAL(10, 72, 7),
QT_MOC_LITERAL(11, 80, 8),
QT_MOC_LITERAL(12, 89, 1),
QT_MOC_LITERAL(13, 91, 8),
QT_MOC_LITERAL(14, 100, 8),
QT_MOC_LITERAL(15, 109, 10),
QT_MOC_LITERAL(16, 120, 9),
QT_MOC_LITERAL(17, 130, 10),
QT_MOC_LITERAL(18, 141, 8),
QT_MOC_LITERAL(19, 150, 4)
    },
    "GLPolygonWidget\0translateX\0\0x\0translateY\0"
    "y\0translateZ\0z\0rotateX\0rotateY\0rotateZ\0"
    "setScale\0s\0moveTree\0setLight\0setShading\0"
    "setLeaves\0setSeasons\0nSeasons\0move"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GLPolygonWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x0a /* Public */,
       4,    1,   82,    2, 0x0a /* Public */,
       6,    1,   85,    2, 0x0a /* Public */,
       8,    1,   88,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
      10,    1,   94,    2, 0x0a /* Public */,
      11,    1,   97,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    1,  101,    2, 0x0a /* Public */,
      15,    1,  104,    2, 0x0a /* Public */,
      16,    1,  107,    2, 0x0a /* Public */,
      17,    1,  110,    2, 0x0a /* Public */,
      19,    0,  113,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,

       0        // eod
};

void GLPolygonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GLPolygonWidget *_t = static_cast<GLPolygonWidget *>(_o);
        switch (_id) {
        case 0: _t->translateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->translateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->translateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->rotateX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->rotateY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->rotateZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->moveTree(); break;
        case 8: _t->setLight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->setShading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setLeaves((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->setSeasons((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->move(); break;
        default: ;
        }
    }
}

const QMetaObject GLPolygonWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLPolygonWidget.data,
      qt_meta_data_GLPolygonWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *GLPolygonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLPolygonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLPolygonWidget.stringdata))
        return static_cast<void*>(const_cast< GLPolygonWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLPolygonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
