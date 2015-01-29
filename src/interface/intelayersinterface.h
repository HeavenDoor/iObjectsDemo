#ifndef INTELAYERSINTERFACE_H
#define INTELAYERSINTERFACE_H

#include <QtWidgets/QWidget>
#include "widgetplugininterface.h"
class InteLayersInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	//virtual QWidget* getWidget() = 0;
	virtual void addTabPage(QVector<QString> vec) = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(InteLayersInterface, "{FE9E88E6-BD9C-49BF-9B96-6E8F9AA770F9}")
QT_END_NAMESPACE

#endif