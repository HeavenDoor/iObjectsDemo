#ifndef TOOLBOXINTERFACE_H
#define TOOLBOXINTERFACE_H

#include <QObject>
#include <QtWidgets/QWidget>
#include "widgetplugininterface.h"

class ToolBoxInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	//ToolBox has a QHBoxLayout , the Align shuold be either Qt::AlignLeft or Qt::AlignRight
	virtual QObject* createToolButton(const QString& objectName, Qt::Alignment align = Qt::AlignLeft) = 0;
	virtual void setToolButtonSize(QSize size) = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(ToolBoxInterface, "{269649A4-5E60-4B63-BA70-665DF7BF2917}")
QT_END_NAMESPACE

#endif
