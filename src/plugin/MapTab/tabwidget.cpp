#include "stdafx.h"
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent/*, TabBar* tabbar*/) : QTabWidget(parent)
{
	w = NULL;
	setObjectName("Tabwidget");
	setAttribute(Qt::WA_TranslucentBackground);
	//tabBar()->setVisible(false);  // 隐藏自带tabbar
	tabBar()->setVisible(false);  // 隐藏自带tabbar
	//if(tabbar) setTabBar(tabbar);
	m_pTwoDimension = NULL;
	m_pThreeDimension = NULL;

	m_pTwoDimension = new QWidget(this);
	//m_pTwoDimension->setObjectName("TwoDimension");
	m_pThreeDimension = new QWidget(this);
	//m_pThreeDimension->setObjectName("ThreeDimension");

	addTab(m_pTwoDimension,"two");
	addTab(m_pThreeDimension,"three");
}

TabWidget::~TabWidget()
{

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
// 	if (w)
// 	{
// 		w->setGeometry(this->geometry());
// 	}
	if (m_pTwoDimension)
	{
		m_pTwoDimension->setGeometry(0,0,width(), height());
	}
	if (m_pThreeDimension)
	{
		m_pThreeDimension->setGeometry(this->geometry());
	}
}

void TabWidget::addCentralWidget( QWidget* map, int tabIndex )
{
	map->setParent(this);
	map->setFixedHeight(this->height());
	map->setFixedWidth(this->width());
	map->setProperty("TabIndex", tabIndex);
//	map->setObjectName("TabIndex" + QString::number(tabIndex));
	w = map;
// 	addTab(map,"two");
// 	m_pThreeDimension = new QWidget(this);
// 	addTab(m_pThreeDimension,"three");
}
