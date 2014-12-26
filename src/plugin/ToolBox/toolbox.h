#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "toolbox_global.h"
#include "toolboxinterface.h"

#include <QtWidgets/QWidget>
#include <QObject>

class ToolBox : public QWidget , ToolBoxInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{E10C47F9-2D9E-4096-B08E-22CAA71B52BB}" FILE "toolbox.json")
	Q_INTERFACES(ToolBoxInterface)
public:
	ToolBox(QWidget *parent = 0);
	~ToolBox();
	virtual void test();
private:

};

#endif // TOOLBOX_H
