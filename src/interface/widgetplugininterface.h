//////////////////////////////////////////////////////////////////////////
//控件类型的插件公共接口                   
//////////////////////////////////////////////////////////////////////////

#ifndef WIDGETPLUGININTERFACE_H
#define WIDGETPLUGININTERFACE_H

#include <QObject>
#include <QtWidgets/QWidget>


class WidgetPluginInterface
{
public:
	//virtual QWidget* getWidget() = 0;  主界面应该不需要获得plugin widget
	// 设置父控件
	virtual void setPluginParent(QWidget* parentWidget) = 0;
	// 得到插件界面指针  返回QObject*类型，避免得到插件界面直接修改，用于信号收发
	virtual QObject* getObject() = 0;  // 通过object connect signal
	// 设置插件位置
	virtual void setPluginGeometry(const QRect& rect) = 0;
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah) = 0;
	virtual void showPlugin() = 0;
	virtual void raisePlugin() = 0;
	virtual void lowerPlugin() = 0;
	virtual void resizePlugin(int ax, int ay, int aw, int ah) = 0;
	// 一下主要是针对有Geometry动画属性的插件，不能设置fixedWidth  用于记录插件宽高
	virtual void setPluginWidth(int width) = 0;
	virtual void setPluginHeight(int height) = 0;
	virtual int pluginWidth() = 0;
	virtual int pluginHeight() = 0;

	// 获得插件样式表，主界面重新加载样式表
	virtual QString getStyleSheet() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(WidgetPluginInterface, "{74B537CD-66CD-4FAF-B2CC-C997F67B7E5B}")
QT_END_NAMESPACE

#endif