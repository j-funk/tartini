/****************************************************************************
** Meta object code from reading C++ file 'fftview.h'
**
** Created: Mon May 21 18:21:22 2007
**      by: The Qt Meta Object Compiler version 59 (Qt 4.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widgets/fft/fftview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fftview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_FFTView[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets

       0        // eod
};

static const char qt_meta_stringdata_FFTView[] = {
    "FFTView\0"
};

const QMetaObject FFTView::staticMetaObject = {
    { &ViewWidget::staticMetaObject, qt_meta_stringdata_FFTView,
      qt_meta_data_FFTView, 0 }
};

const QMetaObject *FFTView::metaObject() const
{
    return &staticMetaObject;
}

void *FFTView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FFTView))
	return static_cast<void*>(const_cast< FFTView*>(this));
    return ViewWidget::qt_metacast(_clname);
}

int FFTView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ViewWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
