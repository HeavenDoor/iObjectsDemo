#include "stdafx.h"
#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent)
{
	this->setObjectName("ToolBox");

	m_pSearch = new QPushButton(this);
	m_pSearch->setObjectName("search");
	m_pSearch->setFixedHeight(50);
	m_pSearch->setFixedWidth(50);
	m_pSearch->setGeometry(5,3,m_pSearch->width(), m_pSearch->height());
	connect(m_pSearch, SIGNAL(clicked()), this, SIGNAL(ToolBoxPlugin_SearchBtnClicked()));

	m_pSet = new QPushButton(this);
	m_pSet->setObjectName("set");
	m_pSet->setFixedHeight(50);
	m_pSet->setFixedWidth(50);
	m_pSet->setGeometry(width()/* - m_pSet->width() - 5*/,3,m_pSet->width(), m_pSet->height());
	connect(m_pSet, SIGNAL(clicked()), this, SIGNAL(ToolBoxPlugin_SettingBtnClicked()));

	QFile file(":/toolbox.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());

	//qDebug()<<style;
	this->setStyleSheet(style);
	file.close();
}

ToolBox::~ToolBox()
{

}

void ToolBox::test()
{

}

// QWidget* ToolBox::getWidget()
// {
// 	return this;
// }

void ToolBox::paintEvent( QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void ToolBox::resizeEvent( QResizeEvent * )
{
	if (m_pSet)
	{
		m_pSet->setGeometry(width() - m_pSet->width() - 5, 3, m_pSet->width(), m_pSet->height());
	}
}

QObject* ToolBox::getObject()
{
	return this;
}

void ToolBox::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void ToolBox::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

// void ToolBox::OnResizeEvent( const QRect& rect )
// {
// 
// }

void ToolBox::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void ToolBox::showPlugin()
{
	this->show();
}

void ToolBox::raisePlugin()
{
	this->raise();
}

void ToolBox::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}
