#include "stdafx.h"
#include "mapbase.h"



MapBase::MapBase(QWidget *parent) : QWidget(parent)
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

MapBase::~MapBase()
{
	delete m_pTabWidget;
	m_pTabWidget = NULL;

	delete m_pTabBar;
	m_pTabBar = NULL;
}
 
 void MapBase::paintEvent(QPaintEvent* e)
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

void MapBase::test()
{

}

void MapBase::resizeEvent( QResizeEvent* e)
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


QObject* MapBase::getObject()
{
	return this;
}

void MapBase::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void MapBase::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void MapBase::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void MapBase::showPlugin()
{
	this->show();
}

void MapBase::raisePlugin()
{
	this->raise();
}

void MapBase::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}


void MapBase::OnChangeDimension( int isTwoDimension )
{
	if(!m_pTabWidget) return;
	m_pTabWidget->resize(width(), height());
	m_pTabWidget->setCurrentIndex(isTwoDimension);
}

void MapBase::lowerPlugin()
{
	lower();
}

void MapBase::setPluginWidth( int width )
{
	setFixedWidth(width);
}


void MapBase::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int MapBase::pluginWidth()
{
	return width();
}

int MapBase::pluginHeight()
{
	return height();
}

void MapBase::addCentralWidget( QWidget* map, int tabIndex, QString tabName)
{
	if (!m_pTabWidget ||  !m_pTabBar) return;
	if (m_pTabWidget->count() < tabIndex) tabIndex = m_pTabWidget->count();
	if (tabIndex < 0) tabIndex = 0;
	//map->setParent(this);
	m_pTabBar->insertTabbar(tabIndex, tabName);
	m_pTabWidget->addCentralWidget(map, tabIndex, tabName);
}

void MapBase::setCurrentIndex( int index )
{
	if (!m_pTabWidget ||  !m_pTabBar) return;
	if (m_pTabWidget->count() <= index) index = m_pTabWidget->count() - 1;
	m_pTabWidget->setCurrentIndex(index);
	m_pTabBar->setCurrentIndex(index);
}

void MapBase::loadSkin()
{
	QFile file(":/maptab.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());

	//qDebug()<<style;
	this->setStyleSheet(style);
	file.close();
}
