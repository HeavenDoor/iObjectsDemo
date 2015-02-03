//////////////////////////////////////////////////////////////////////////
// MapBase插件功能性接口                   
//////////////////////////////////////////////////////////////////////////
#ifndef MAPBASEINTERFACE_H
#define MAPBASEINTERFACE_H


#include <QObject>
#include <QtWidgets/QWidget>
#include "widgetplugininterface.h"

class MapBaseInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	// 获得MapBase插件主界面的指针，作为主界面Tab页面显示
	virtual QWidget* getWidget() = 0;   
	// 获得MapBase插件中MapLayers控件指针，给主界面做布局处理
	virtual QWidget* getMapLayers() = 0;
	// 获得插件样式表，主界面重新加载样式表
	virtual QString getStyleSheet() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(MapBaseInterface, "{D1B7D4F8-A0E7-42B8-AE6A-DAF3122D6EB8}")
QT_END_NAMESPACE

#endif