#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "toolbox_global.h"
#include "toolboxinterface.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
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
	virtual QWidget* getWidget();

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent *);
private:
	QPushButton* m_pSearch;
	QPushButton* m_pSet;
};

#endif // TOOLBOX_H
