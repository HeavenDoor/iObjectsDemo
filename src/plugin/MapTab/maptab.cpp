#include "stdafx.h"
#include "maptab.h"



MapTab::MapTab(QWidget *parent) : QWidget(parent)
{
	setObjectName("MapTab");

	m_pTabWidget = new TabWidget(this);

	m_pTabBar = new TabBar(this);
	m_pTabBar->setFixedHeight(58);
	m_pTabBar->raise();
//	m_pTabBar->setFixedWidth(162);
	m_pTabBar->show();
	connect(m_pTabBar, SIGNAL(changeDimension(int)), this, SLOT(OnChangeDimension(int)));
	int j = m_pTabBar->width();
}

MapTab::~MapTab()
{
	delete m_pTabWidget;
	m_pTabWidget = NULL;

	delete m_pTabBar;
	m_pTabBar = NULL;
}
 
 void MapTab::paintEvent(QPaintEvent* e)
 {
 	QStyleOption opt;
 	opt.init(this);
 	QPainter p(this);
 	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 	QWidget::paintEvent(e);
 }

// QWidget* MapTab::getWidget()
// {
// 	return this;
// }

void MapTab::test()
{

}

void MapTab::resizeEvent( QResizeEvent* e)
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


QObject* MapTab::getObject()
{
	return this;
}

void MapTab::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void MapTab::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void MapTab::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void MapTab::showPlugin()
{
	this->show();
}

void MapTab::raisePlugin()
{
	this->raise();
}

void MapTab::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}


void MapTab::OnChangeDimension( int isTwoDimension )
{
	if(!m_pTabWidget) return;
	m_pTabWidget->resize(width(), height());
	m_pTabWidget->setCurrentIndex(isTwoDimension);
}

void MapTab::lowerPlugin()
{
	lower();
}

void MapTab::setPluginWidth( int width )
{
	setFixedWidth(width);
}


void MapTab::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int MapTab::pluginWidth()
{
	return width();
}

int MapTab::pluginHeight()
{
	return height();
}

void MapTab::addCentralWidget( QWidget* map, int tabIndex, QString tabName)
{
	if (!m_pTabWidget ||  !m_pTabBar) return;
	if (m_pTabWidget->count() < tabIndex) tabIndex = m_pTabWidget->count();
	if (tabIndex < 0) tabIndex = 0;
	//map->setParent(this);
	m_pTabBar->insertTabbar(tabIndex, tabName);
	m_pTabWidget->addCentralWidget(map, tabIndex, tabName);
}

void MapTab::setCurrentIndex( int index )
{
	if (!m_pTabWidget ||  !m_pTabBar) return;
	if (m_pTabWidget->count() <= index) index = m_pTabWidget->count() - 1;
	m_pTabWidget->setCurrentIndex(index);
	m_pTabBar->setCurrentIndex(index);
}

void MapTab::loadSkin()
{
	QFile file(":/maptab.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());

	//qDebug()<<style;
	this->setStyleSheet(style);
	file.close();
}
