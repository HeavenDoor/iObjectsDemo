#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "infopanel_global.h"
#include "..\\..\\interface\infopanelinterface.h"


#include <QtWidgets/QWidget>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>
#include <QtQuickWidgets/QQuickWidget>

//////////////////////////////////////////////////////////////////////////
#include <qdebug.h>
#include <qdatetime.h>
#include <qbasictimer.h>
#include <qcoreapplication.h>


//////////////////////////////////////////////////////////////////////////
class InfoPanel : public QQuickWidget, InfoPanelInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{902CE857-E7E7-4F78-A034-6A40962BE4E3}" FILE "infopanel.json")
	Q_INTERFACES(InfoPanelInterface)

public:
	InfoPanel();
	~InfoPanel();
	void registerTypes(const char *uri);

	virtual void test();
	virtual QObject* getObject();
	virtual void setPluginGeometry(const QRect& rect);
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah);
	virtual void setPluginParent(QWidget* parentWidget);
	virtual void showPlugin();
	virtual void raisePlugin();
	virtual void lowerPlugin();
	virtual void resizePlugin(int ax, int ay, int aw, int ah);
	virtual void setPluginWidth(int width);
	virtual void setPluginHeight(int height);
	virtual int pluginWidth();
	virtual int pluginHeight();
};

#endif // INFOPANEL_H
