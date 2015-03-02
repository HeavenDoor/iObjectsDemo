#include "stdafx.h"
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent/*, TabBar* tabbar*/) : QTabWidget(parent)
{
	//w = NULL;
	setObjectName("Tabwidget");
	setAttribute(Qt::WA_TranslucentBackground);
	tabBar()->setFixedHeight(0);
	tabBar()->setFixedWidth(0);
	tabBar()->setVisible(false);  // Òþ²Ø×Ô´øtabbar
	//if(tabbar) setTabBar(tabbar);

}

TabWidget::~TabWidget()
{
	m_pTabList.clear();
}

 void TabWidget::paintEvent(QPaintEvent* e)
 {
 	QStyleOption opt;
 	opt.init(this);
 	QPainter p(this);
 	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 	QWidget::paintEvent(e);
 }

void TabWidget::resizeEvent(QResizeEvent* e)
{
	foreach (QWidget* w, m_pTabList)
	{
		w->setFixedWidth(width());
		w->setFixedHeight(height());
		w->setGeometry(0,0,width(), height());
	}
}

void TabWidget::addCentralWidget( QWidget* map, int tabIndex, QString tabName )
{
	map->setFixedHeight(this->height());
	map->setFixedWidth(this->width());
	map->setProperty("TabIndex", tabIndex);
	insertTab(tabIndex, map, tabName);
	//addTab(map, tabName);
	m_pTabList.insert(tabIndex, map);
// 	QPushButton* pp = new QPushButton(map);
// 	pp->setText(tabName);

}

int TabWidget::removeCentralWidget( QWidget* widget )
{
	int index = m_pTabList.indexOf(widget);
	removeTab(index);
	m_pTabList.removeOne(widget);
	return index;
}

QWidget* TabWidget::getWidget( int index )
{
	return m_pTabList.at(index);
}
