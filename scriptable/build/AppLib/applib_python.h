

#ifndef SBK_APPLIB_PYTHON_H
#define SBK_APPLIB_PYTHON_H

#include <sbkpython.h>
#include <sbkconverter.h>
// Module Includes
#include <pyside6_qtwidgets_python.h>
#include <pyside6_qtgui_python.h>
#include <pyside6_qtcore_python.h>

// Bound library includes
#include <mainwindow.h>
// Conversion Includes - Primitive Types
#include <QAnyStringView>
#include <QString>
#include <QStringList>
#include <QStringView>

// Conversion Includes - Container Types
#include <pysideqflags.h>
#include <QList>
#include <QMap>
#include <pysideqflags.h>
#include <QMultiMap>
#include <QPair>
#include <QQueue>
#include <QSet>
#include <QStack>
#include <list>
#include <map>
#include <utility>
#include <unordered_map>
#include <vector>

// Type indices
enum : int {
    SBK_MAINWINDOW_IDX                                       = 0,
    SBK_AppLib_IDX_COUNT                                     = 1
};
// This variable stores all Python types exported by this module.
extern PyTypeObject **SbkAppLibTypes;

// This variable stores the Python module object exported by this module.
extern PyObject *SbkAppLibModuleObject;

// This variable stores all type converters exported by this module.
extern SbkConverter **SbkAppLibTypeConverters;

// Converter indices
enum : int {
    SBK_APPLIB_QLIST_INT_IDX                                 = 0, // QList<int >
    SBK_APPLIB_QLIST_QDOCKWIDGETPTR_IDX                      = 1, // QList<QDockWidget* >
    SBK_APPLIB_QLIST_QVARIANT_IDX                            = 2, // QList<QVariant >
    SBK_APPLIB_QLIST_QSTRING_IDX                             = 3, // QList<QString >
    SBK_APPLIB_QMAP_QSTRING_QVARIANT_IDX                     = 4, // QMap<QString,QVariant >
    SBK_AppLib_CONVERTERS_IDX_COUNT                          = 5
};
// Macros for type check

namespace Shiboken
{

// PyType functions, to get the PyObjectType for a type T
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
template<> inline PyTypeObject *SbkType< ::MainWindow >() { return reinterpret_cast<PyTypeObject *>(SbkAppLibTypes[SBK_MAINWINDOW_IDX]); }
QT_WARNING_POP

} // namespace Shiboken

#endif // SBK_APPLIB_PYTHON_H

