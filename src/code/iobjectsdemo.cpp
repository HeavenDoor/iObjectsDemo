#include "stdafx.h"
#include "iobjectsdemo.h"

#include <QLabel>
#include <QWidget>

iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");
	loadControls();

	if (!loadPlugins("../bin/debug", "ToolBox"))
	{
		exit(0);
	}

	m_pPopBtn = new QPushButton(this);
	m_pPopBtn->setObjectName("PopTitleBtn");
	m_pPopBtn->setFixedWidth(40);
	m_pPopBtn->setFixedHeight(8);
	m_pPopBtn->setGeometry(width()/2 - m_pPopBtn->width()/2, 0, m_pPopBtn->width(), m_pPopBtn->height());
	m_pPopBtn->hide();
	


	m_pTitle = new Title(this);
	//m_pTitle->setFixedHeight(85);
	//m_pTitle->setFixedWidth(530);
	//m_pTitle->setGeometry(width()/2 - m_pTitle->width()/2, 0, 530, 85 /*m_pTitle->width(), m_pTitle->height()*/);
	connect(m_pTitle, SIGNAL(collapse()), this, SLOT(OnTitleCollapsed()));
	connect(m_pPopBtn, SIGNAL(clicked()), m_pTitle, SLOT(expandTitle()));

	m_pToolBox->getWidget()->setParent(this);
	m_pToolBox->getWidget()->setGeometry(0,height()-50,width(),50);
	m_pToolBox->getWidget()->show();
	m_pToolBox->getWidget()->raise();
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

void iObjectsDemo::resizeEvent(QResizeEvent* e)
{
	if (m_pCloseBtn)
	{
		m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
	}
	
	if (m_pToolBox->getWidget())
	{
		m_pToolBox->getWidget()->setGeometry(0,height()-50,width(),50);
	}

	if (m_pTitle)
	{
		m_pTitle->setGeometry(width()/2 - m_pTitle->width()/2, 0, m_pTitle->width(), m_pTitle->height());
	}
	if (m_pPopBtn)
	{
		m_pPopBtn->setGeometry(width()/2 - m_pPopBtn->width()/2, 0, m_pPopBtn->width(), m_pPopBtn->height());
	}

	QWidget::resizeEvent(e);
}

void iObjectsDemo::OnCloseBtnClicked()
{
	this->close();
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

/*

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
bToolbox = true;
}
}
}
return bToolbox;
}

bool iObjectsDemo::loadMapTabsPlugin()
{
	return true;
}

bool iObjectsDemo::loadIntelligencePlugin()
{
	return true;
}

*/

bool iObjectsDemo::loadPlugins(const QString& path, const QString& pluginName)
{
	bool bToolbox = false;
	qApp->addLibraryPath(path); // ../bin/debug
	QPluginLoader loader(pluginName) ;  
	//QPluginLoader loader(QString("libMyPlugin.so")) ;  
	QObject* object;
	if ( (object=loader.instance()) != NULL )  
	{  
		qDebug("plugin loaded .");  
		m_pToolBox = qobject_cast<ToolBoxInterface*>(object) ;  
		if (m_pToolBox)  
		{
			bToolbox = true;
		}
	}  
	else  
	{  
		qDebug("failed to load plugin !! ");  
		QString errorStr = loader.errorString();  
		qDebug()<<errorStr;  
	}  


	return true;
}

void iObjectsDemo::OnTitleCollapsed()
{
	if (m_pPopBtn)
	{
		if (m_pPopBtn->isVisible())
		{
			m_pPopBtn->hide();
		}
		else
		{
			m_pPopBtn->show();
		}
		
	}
}
