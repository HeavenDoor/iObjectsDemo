#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QtWidgets/QTabWidget>
#include <QtWidgets/QHBoxLayout>
#include <QList>
#include "tabbar.h"

class TabWidget : public QTabWidget
{
	Q_OBJECT

public:
	TabWidget(QWidget *parent = NULL/*, TabBar* tabbar = NULL*/);
	~TabWidget();
	void addCentralWidget(QWidget* map, int tabIndex, QString tabName);
	// 删除tab页面  返回值 页面index 作为tabbar的参数
	int removeCentralWidget(QWidget* widget);
	QWidget* getWidget(int index);
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private:
	QList<QWidget*> m_pTabList;
};

#endif // TABWIDGET_H
