#ifndef WIDGETPLUGININTERFACE_H
#define WIDGETPLUGININTERFACE_H

#include <QObject>
#include <QtWidgets/QWidget>


class WidgetPluginInterface
{
public:
	//virtual QWidget* getWidget() = 0;  主界面应该不需要获得plugin widget

	virtual void setPluginParent(QWidget* parentWidget) = 0;
	virtual QObject* getObject() = 0;  // 通过object connect signal
	virtual void setPluginGeometry(const QRect& rect) = 0;
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah) = 0;
	virtual void showPlugin() = 0;
	virtual void raisePlugin() = 0;
	virtual void lowerPlugin() = 0;
	virtual void resizePlugin(int ax, int ay, int aw, int ah) = 0;
	virtual void setPluginWidth(int width) = 0;
	virtual void setPluginHeight(int height) = 0;
	virtual int pluginWidth() = 0;
	virtual int pluginHeight() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(WidgetPluginInterface, "{74B537CD-66CD-4FAF-B2CC-C997F67B7E5B}")
QT_END_NAMESPACE

#endif