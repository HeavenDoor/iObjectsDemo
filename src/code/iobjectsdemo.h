#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>

#include "title.h"
#include "plugin/ToolBox/toolboxinterface.h"


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
	//bool loadToolBoxPlugin();
	//bool loadMapTabsPlugin();
	//bool loadIntelligencePlugin();
private:
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;
	ToolBoxInterface* m_pToolBox;
	Title* m_pTitle;
};

#endif // IOBJECTSDEMO_H
