#ifndef MAPTABINTERFACE_H
#define MAPTABINTERFACE_H


#include <QObject>
#include <QtWidgets/QWidget>
#include "widgetplugininterface.h"
class MapBaseInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	virtual QWidget* getWidget() = 0;
	virtual QWidget* getController() = 0;
	virtual QString getStyleSheet() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(MapBaseInterface, "{D1B7D4F8-A0E7-42B8-AE6A-DAF3122D6EB8}")
QT_END_NAMESPACE

#endif