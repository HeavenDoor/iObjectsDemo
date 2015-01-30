#ifndef SCENETAB_GLOBAL_H
#define SCENETAB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SCENETAB_LIB
# define SCENETAB_EXPORT Q_DECL_EXPORT
#else
# define SCENETAB_EXPORT Q_DECL_IMPORT
#endif

#endif // SCENETAB_GLOBAL_H
