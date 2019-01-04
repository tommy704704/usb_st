#ifndef USBDLL_GLOBAL_H
#define USBDLL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef USBDLL_LIB
# define USBDLL_EXPORT Q_DECL_EXPORT
#else
# define USBDLL_EXPORT Q_DECL_IMPORT
#endif

#endif // USBDLL_GLOBAL_H
