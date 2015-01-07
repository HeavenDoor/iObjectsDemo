#ifndef INFOPANEL_GLOBAL_H
#define INFOPANEL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef INFOPANEL_LIB
# define INFOPANEL_EXPORT Q_DECL_EXPORT
#else
# define INFOPANEL_EXPORT Q_DECL_IMPORT
#endif

#endif // INFOPANEL_GLOBAL_H
