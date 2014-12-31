#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>

#include "title.h"
#include "plugin/ToolBox/toolboxinterface.h"
#include "plugin/MapTab/maptabinterface.h"
#include "plugin/InteLayers/intelayersinterface.h"

class iObjectsDemo : public QWidget
{
	Q_OBJECT

public:
	iObjectsDemo(QWidget *parent = 0);
	~iObjectsDemo();
	void test(){}
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
signals:

private slots:
	void OnCloseBtnClicked();
	void OnTitleCollapsed();
private:
	bool loadControls();
	bool loadPlugins(const QString& path, const QString& pluginName);
private:
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;
	ToolBoxInterface* m_pToolBox;
	MapTabInterface* m_pMapTab;
	InteLayersInterface* m_pInteLayers;
	Title* m_pTitle;
};

#endif // IOBJECTSDEMO_H
