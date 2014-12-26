#include "stdafx.h"
#include "iobjectsdemo.h"

#include <QLabel>
#include <QWidget>

iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");
	loadControls();
	if(!loadToolBoxPlugin())
	{
		exit(0);
	}
	if (!loadMapTabsPlugin())
	{
		exit(0);
	}
	if (!loadIntelligencePlugin())
	{
		exit(0);
	}
}

iObjectsDemo::~iObjectsDemo()
{

}

void iObjectsDemo::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void iObjectsDemo::OnCloseBtnClicked()
{
	this->close();
}

bool iObjectsDemo::loadToolBoxPlugin()
{
	bool bToolbox = false;
	QDir path("../bin/debug");
	foreach( QString filename, path.entryList(QDir::Files) )
	{
		qDebug()<<filename;
		QPluginLoader loader( path.absoluteFilePath( filename ) );
		QObject *couldBeFilter = loader.instance();
		if( couldBeFilter )
		{
			m_pToolBox = qobject_cast<ToolBoxInterface*>( couldBeFilter );
			if( m_pToolBox )
			{
				//bToolbox = true;
			}
		}
	}
	return bToolbox;
}

bool iObjectsDemo::loadControls()
{
	QLabel *lable = new QLabel(this);
	lable->setText(QStringLiteral("我是中文"));
	setGeometry(200,200,1247,766);


	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("CloseBtn");
	m_pCloseBtn->setFixedHeight(48);
	m_pCloseBtn->setFixedWidth(48);
	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());


	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));

	return true;
}

bool iObjectsDemo::loadMapTabsPlugin()
{
	return true;
}

bool iObjectsDemo::loadIntelligencePlugin()
{
	return true;
}
