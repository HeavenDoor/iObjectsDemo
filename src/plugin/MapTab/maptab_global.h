#ifndef MAPTAB_GLOBAL_H
#define MAPTAB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MAPTAB_LIB
# define MAPTAB_EXPORT Q_DECL_EXPORT
#else
# define MAPTAB_EXPORT Q_DECL_IMPORT
#endif

#endif // MAPTAB_GLOBAL_H
