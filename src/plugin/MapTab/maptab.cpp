#include "stdafx.h"
#include "maptab.h"



MapTab::MapTab(QWidget *parent) : QWidget(parent)
{
	setObjectName("MapTab");

	/*QPushButton* p = new QPushButton(this);
	p->setFixedHeight(50);
	p->setFixedWidth(100);
	p->setText("MapTab Control");*/
	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->tabBar()->setVisible(false);
	m_pTabWidget->setGeometry(this->geometry());
	



	m_pTwoDimension = new QWidget(m_pTabWidget);
	m_pTwoDimension->setObjectName("TwoDimension");
	m_pThreeDimension = new QWidget(m_pTabWidget);
	m_pThreeDimension->setObjectName("ThreeDimension");

	m_pTabWidget->addTab(m_pTwoDimension,"two");
	m_pTabWidget->addTab(m_pThreeDimension,"three");


	m_pTabBar = new TabBar(this);
	m_pTabBar->setFixedHeight(58);
	m_pTabBar->setFixedWidth(162);
	connect(m_pTabBar, SIGNAL(changeDimension(bool)), this, SLOT(OnChangeDimension(bool)));
	int j = m_pTabBar->width();


	QFile file(":/maptab.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());

	//qDebug()<<style;
	this->setStyleSheet(style);
	file.close();
}

MapTab::~MapTab()
{

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
		m_pTabBar->setGeometry(width() - 260, 25, m_pTabBar->width(), m_pTabBar->height());
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


void MapTab::OnChangeDimension( bool isTwoDimension )
{
	if(!m_pTabWidget) return;
	m_pTabWidget->setCurrentIndex(!isTwoDimension);
}
