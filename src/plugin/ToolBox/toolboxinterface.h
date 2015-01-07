#ifndef TOOLBOXINTERFACE_H
#define TOOLBOXINTERFACE_H

#include <QObject>
#include <QtWidgets/QWidget>
#include "..\\widgetplugininterface.h"

class ToolBoxInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	//virtual QWidget* getWidget() = 0;  主界面应该不需要获得plugin widget

// 	virtual void setPluginParent(QWidget* parentWidget) = 0;
// 	virtual QObject* getObject() = 0;  // 通过object connect signal
// 	virtual void setPluginGeometry(const QRect& rect) = 0;
// 	virtual void setPluginGeometry(int ax, int ay, int aw, int ah) = 0;
// 	virtual void showPlugin() = 0;
// 	virtual void raisePlugin() = 0;
// 	virtual void resizePlugin(int ax, int ay, int aw, int ah) = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(ToolBoxInterface, "{269649A4-5E60-4B63-BA70-665DF7BF2917}")
QT_END_NAMESPACE

#endif
