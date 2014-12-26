#ifndef TOOLBOX_GLOBAL_H
#define TOOLBOX_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TOOLBOX_LIB
# define TOOLBOX_EXPORT Q_DECL_EXPORT
#else
# define TOOLBOX_EXPORT Q_DECL_IMPORT
#endif

#endif // TOOLBOX_GLOBAL_H
