#ifndef INFOPANELINTERFACE_H
#define INFOPANELINTERFACE_H

#include "widgetplugininterface.h"
#include <QtWidgets/QWidget>
class InfoPanelInterface 
{
public:
	virtual void test() = 0;
	virtual QWidget* getWidget() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(InfoPanelInterface, "{482AA820-A4BF-48E9-8A7A-05DCFC77B9B6}")
QT_END_NAMESPACE


#endif