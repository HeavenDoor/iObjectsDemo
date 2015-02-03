#ifndef MAPBASE_GLOBAL_H
#define MAPBASE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MAPBASE_LIB
# define MAPBASE_EXPORT Q_DECL_EXPORT
#else
# define MAPBASE_EXPORT Q_DECL_IMPORT
#endif

#endif // MAPBASE_GLOBAL_H
