#include "stdafx.h"
#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent)
{
	this->setObjectName("ToolBox");

	m_pOutLayout = NULL;
	m_pLeftLayout = NULL;
	m_pRightLayout = NULL;
	m_size.setWidth(50);
	m_size.setHeight(50);


	m_pOutLayout = new QHBoxLayout(this);
 	m_pOutLayout->setContentsMargins(0, 0, 0, 0);
 	m_pOutLayout->setSpacing(width());
	m_pOutLayout->setAlignment(Qt::AlignHorizontal_Mask);

	m_pLeftLayout = new QHBoxLayout(this);
	m_pLeftLayout->setContentsMargins(0, 0, 0, 0);
	m_pLeftLayout->setSpacing(10);
	m_pLeftLayout->setAlignment(Qt::AlignLeft);

	
	//m_pOutLayout->add
	m_pRightLayout = new QHBoxLayout(this);
	m_pRightLayout->setContentsMargins(0, 0, 0, 0);
	m_pRightLayout->setSpacing(10);
	m_pRightLayout->setAlignment(Qt::AlignRight);

// 	m_pSearch = new QPushButton(this);
// 	m_pSearch->setObjectName("search");
// 	m_pSearch->setFixedHeight(50);
// 	m_pSearch->setFixedWidth(50);
// 	//m_pSearch->setGeometry(5,3,m_pSearch->width(), m_pSearch->height());
// 	m_pLeftLayout->addWidget(m_pSearch);
// 	connect(m_pSearch, SIGNAL(clicked()), this, SIGNAL(ToolBoxPlugin_SearchBtnClicked()));
// 
// 	m_pSet = new QPushButton(this);
// 	m_pSet->setObjectName("set");
// 	m_pSet->setFixedHeight(50);
// 	m_pSet->setFixedWidth(50);
// 	//m_pSet->setGeometry(width()/* - m_pSet->width() - 5*/,3,m_pSet->width(), m_pSet->height());
// 	m_pRightLayout->addWidget(m_pSet);
// 	connect(m_pSet, SIGNAL(clicked()), this, SIGNAL(ToolBoxPlugin_SettingBtnClicked()));


	m_pOutLayout->addLayout(m_pLeftLayout);
	m_pOutLayout->addStretch(0);
	//m_pOutLayout->setStretch(0,2);
	m_pOutLayout->addLayout(m_pRightLayout);

	this->setLayout(m_pOutLayout);

// 
// 	QFile file(":/toolbox.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 
// 	//qDebug()<<style;
// 	this->setStyleSheet(style);
// 	file.close();

	
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
// 	if (m_pSet)
// 	{
// 		m_pSet->setGeometry(width() - m_pSet->width() - 5, 3, m_pSet->width(), m_pSet->height());
// 	}

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

void ToolBox::lowerPlugin()
{
	lower();
}

void ToolBox::setPluginWidth( int width )
{
	setFixedWidth(width);
}

void ToolBox::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int ToolBox::pluginWidth()
{
	return width();
}

int ToolBox::pluginHeight()
{
	return height();
}

QObject* ToolBox::createToolButton( const QString& objectName, Qt::Alignment align /*= Qt::AlignLeft*/ )
{
	QPushButton* pBtn = new QPushButton(this);	
	pBtn->setObjectName(objectName);
	pBtn->setFixedSize(m_size);
	if (align != Qt::AlignRight)
	{
		m_pLeftLayout->addWidget(pBtn);
	}
	else
	{
		m_pRightLayout->addWidget(pBtn);
	}
	return pBtn;
}

void ToolBox::setToolButtonSize( QSize size )
{
	m_size = size;
}
