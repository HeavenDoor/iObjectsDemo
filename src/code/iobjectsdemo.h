#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>

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

signals:

private slots:
	void OnCloseBtnClicked();

private:
	bool loadControls();
	bool loadToolBoxPlugin();
	bool loadMapTabsPlugin();
	bool loadIntelligencePlugin();
private:
	QPushButton* m_pCloseBtn;
	ToolBoxInterface* m_pToolBox;
};

#endif // IOBJECTSDEMO_H
