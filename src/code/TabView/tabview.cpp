#include "stdafx.h"
#include "tabview.h"



TabView::TabView(QWidget *parent) : QWidget(parent)
{
	setObjectName("TabView");

	m_pTabWidget = new TabWidget(this);

	m_pTabBar = new TabBar(this);
	m_pTabBar->setFixedHeight(58);
	m_pTabBar->raise();
//	m_pTabBar->setFixedWidth(162);
	m_pTabBar->show();
	connect(m_pTabBar, SIGNAL(changeIndex(int)), this, SLOT(OnChangeIndex(int)));
	int j = m_pTabBar->width();

	loadDefaultSkin();
}

TabView::~TabView()
{
	delete m_pTabWidget;
	m_pTabWidget = NULL;

	delete m_pTabBar;
	m_pTabBar = NULL;
}
 
void TabView::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void TabView::resizeEvent( QResizeEvent* e)
{
	if (m_pTabWidget)
	{
		m_pTabWidget->setGeometry(0,0,width(), height());
	}

	if (m_pTabBar)
	{
		m_pTabBar->setFixedWidth(m_pTabBar->tabCount()*tabrwidth);
		m_pTabBar->setGeometry(width() - m_pTabBar->tabCount()*tabrwidth - 100, 25, m_pTabBar->width(), m_pTabBar->height());
	}

	QWidget::resizeEvent(e);
}



void TabView::OnChangeIndex(int index)
{
	if(!m_pTabWidget) return;
	m_pTabWidget->resize(width(), height());
	m_pTabWidget->setCurrentIndex(index);
}

void TabView::addCentralWidget( QWidget* map, int tabIndex, QString tabName)
{
	if (!m_pTabWidget || !m_pTabBar) return;
	if (m_pTabWidget->count() < tabIndex) tabIndex = m_pTabWidget->count();
	if (tabIndex < 0) tabIndex = 0;
	//map->setParent(this);
	
	//m_pTabBar->setFixedWidth((m_pTabBar->tabCount() + 1)*tabrwidth);
	//m_pTabBar->setGeometry(width() - (m_pTabBar->tabCount() + 1)*tabrwidth - 100, 25, m_pTabBar->width(), m_pTabBar->height());
	m_pTabBar->insertTabbar(tabIndex, tabName);
	m_pTabWidget->addCentralWidget(map, tabIndex, tabName);
	setCurrentIndex(tabIndex);
	loadDefaultSkin();
	m_pTabBar->setFixedWidth(m_pTabBar->tabCount()*tabrwidth);
	m_pTabBar->resize(m_pTabBar->width(), m_pTabBar->height());
	m_pTabBar->setGeometry(width() - m_pTabBar->tabCount()*tabrwidth - 100, 25, m_pTabBar->width(), m_pTabBar->height());
}

void TabView::setCurrentIndex( int index )
{
	if (!m_pTabWidget || !m_pTabBar) return;
	if (m_pTabWidget->count() <= index) index = m_pTabWidget->count() - 1;
	m_pTabWidget->setCurrentIndex(index);
	m_pTabBar->setCurrentIndex(index);
}

void TabView::loadDefaultSkin()
{
	QFile file(":/tabbar.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());

	//qDebug()<<style;
	this->setStyleSheet(style);
	file.close();
}

void TabView::loadCustomStyleSheet( const QString& styleSheet )
{
	this->setStyleSheet(styleSheet);
}
