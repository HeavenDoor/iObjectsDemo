#include "stdafx.h"
#include "iobjectsdemo.h"
#include "commom/widgetrect.h"
#include "pluginloader.h"
#include "pluginmanager.h"
#include "fileutils.h"

#include <QLabel>
#include <QWidget>
#include <QUrl>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQuick/QtQuick>

iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");
	setGeometry(200,200,1247,766);

	m_pTitle = NULL;
	m_pPopBtn = NULL;
	m_pToolBox = NULL;
	m_pMapBase = NULL;
	m_pInteLayers = NULL;
	m_pInfoPanel = NULL;
	m_pTabView = NULL;
	m_pPopupPanel = NULL;

	initInteLayers();
	initTabView();

	m_pPluginloader = new Pluginloader(NULL);
	m_pPluginloader->showModel();

 	pluginPath = "../plugins";
 
 	m_pluginMap = PluginManager::instance()->getPluginMap();
 	QList<QString> pluginList = m_pluginMap.keys();
 
 	qDebug()<<m_pluginMap;
 	foreach(QString pluginName, pluginList)
 	{
 		if (!m_pluginMap.value(pluginName).toBool()) continue;
 		if(!loadPlugins(pluginPath, pluginName))
 			continue;
 	}
 	 
	initControls();

	if (m_pInteLayers) m_pInteLayers->raise();
	if (m_pInfoPanel) m_pInfoPanel->raise();

	if (m_pPluginloader)
	{
		delete m_pPluginloader;
		m_pPluginloader = NULL;
	}
}

iObjectsDemo::~iObjectsDemo()
{

}

bool iObjectsDemo::initTabView()
{
	m_pTabView = new TabView(this);
	QWidget* e = new QWidget(m_pTabView);
	e->setObjectName("TwoDimension");
	m_pTabView->addCentralWidget(e, 3, "ren");
	QWidget* rr = new QWidget(m_pTabView);
	rr->setObjectName("rr");
	m_pTabView->addCentralWidget(rr, 0, "rr");

// 	m_pTabView->setCurrentIndex(0);
// 	m_pTabView->loadDefaultSkin();
	return true;
}


bool iObjectsDemo::initInteLayers()
{
	m_pInteLayers = new InteLayers(this);
	connect(m_pInteLayers, SIGNAL(refeshWindow()), this, SLOT(OnInteLayersPlugin_RefeshWindow()));
	m_pInteLayers->setInteLayersWidth(216);
	m_pInteLayers->setInteLayersHeight(410);
	m_pInteLayers->setGeometry(15, height()/2 - m_pInteLayers->InteLayersHeight()/2, m_pInteLayers->InteLayersWidth(), m_pInteLayers->InteLayersHeight());
	m_pInteLayers->raise();
	return true;
}


bool iObjectsDemo::initControls()
{
	m_pPopupPanel = new PopupPanel(this);
	m_pPopupPanel->setFixedHeight(200);
	m_pPopupPanel->setFixedWidth(350);
	m_pPopupPanel->setGeometry(400,200,m_pPopupPanel->width(), m_pPopupPanel->height());
	m_pPopupPanel->raise();
	m_pPopupPanel->show();


	m_pPopBtn = new QPushButton(this);
	m_pPopBtn->setObjectName("PopTitleBtn");
	m_pPopBtn->setFixedWidth(40);
	m_pPopBtn->setFixedHeight(8);
	m_pPopBtn->setGeometry(width()/2 - m_pPopBtn->width()/2, 0, m_pPopBtn->width(), m_pPopBtn->height());
	m_pPopBtn->hide();

	m_pTitle = new Title(this);
	connect(m_pTitle, SIGNAL(collapse()), this, SLOT(OnTitleCollapsed()));
	connect(m_pPopBtn, SIGNAL(clicked()), m_pTitle, SLOT(expandTitle()));
	m_pTitle->raise();
	m_pTitle->hide();

	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("CloseBtn");
	m_pCloseBtn->setFixedHeight(48);
	m_pCloseBtn->setFixedWidth(48);
	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));

	m_pToolBox = new ToolBox(this);
	m_pToolBox->setFixedHeight(50);
	m_pToolBox->setToolButtonSize(QSize(m_pToolBox->height(),m_pToolBox->height()));
	QObject* obj = m_pToolBox->createToolButton("search");
	if(obj) connect(obj, SIGNAL(clicked()), this, SLOT(OnToolBoxPlugin_SearchBtnClicked()));
	obj = m_pToolBox->createToolButton("set", Qt::AlignRight);
	if(obj) connect(obj, SIGNAL(clicked()), this, SLOT(OnToolBoxPlugin_SettingBtnClicked()));

	m_pInfoPanel = new InfoPanel(this);
	m_pInfoPanel->setPluginWidth(280);
	m_pInfoPanel->setPluginHeight(370);
	//m_pInfoPanel->setGeometry(15, height()/2 - 200, 280, 370);
	m_pInfoPanel->show();
	m_pInfoPanel->raise();
	m_pInfoPanel->setAnimationTimespan(600);
	m_pInfoPanel->setGeometry(width() - m_pInfoPanel->pluginWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->pluginWidth(), m_pInfoPanel->pluginHeight());
	return true;
}

bool iObjectsDemo::unLoadPlugins(const QString& pluginName )
{
	bool bPluginunload = false;
	QPluginLoader* loader = qobject_cast<QPluginLoader*>(this->findChild<QPluginLoader*>(pluginName));

	if (pluginName == "MapBase"/*loader->instance()->inherits("MapTabInterface")*/)
	{
		bPluginunload = loader->unload();
		m_pMapBase = NULL;
	}
	return bPluginunload;
}

bool iObjectsDemo::loadPlugins(const QString& path, const QString& pluginName)
{
	bool bPluginLoaded = false;

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);

	qApp->addLibraryPath(path);
	QPluginLoader* loader = new QPluginLoader(pluginName, this);  
	loader->setObjectName(pluginName);
	QObject* object;
	if ( (object=loader->instance()) != NULL )  
	{  
		QString name = object->objectName();
		if (object->inherits("MapBaseInterface"))
		{
			m_pMapBase = qobject_cast<MapBaseInterface*>(object) ;  
			if (m_pMapBase)  
			{
				bPluginLoaded = true;
				m_pMapBase->setPluginParent(this);	
				{
					if (m_pTabView)
					{
						m_pTabView->addCentralWidget(m_pMapBase->getWidget(), 0, "sheng");
						m_pTabView->setCurrentIndex(0);
						m_pTabView->loadDefaultSkin();
						m_pInteLayers->addLayers(m_pMapBase->getMapLayers());
						setStyleSheet(m_pMapBase->getStyleSheet());
					}					
				}
			}
		}
	}  
	else  
	{  
		qDebug("failed to load plugin !! ");  
		QString errorStr = loader->errorString();  
		qDebug()<<errorStr; 
		QMessageBox::warning(NULL,"",errorStr);
	}  
	QDir::setCurrent(ss);
	return true;
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

	if (m_pToolBox)
	{
		m_pToolBox->setGeometry(0, height() - m_pToolBox->height(), width(), m_pToolBox->height());
	}

	if (m_pInteLayers && m_pInteLayers->width() !=0)
	{
		m_pInteLayers->setGeometry(15, height()/2 - m_pInteLayers->InteLayersHeight()/2,  m_pInteLayers->InteLayersWidth(), m_pInteLayers->InteLayersHeight());
	}

	if (m_pInfoPanel)
	{
		if (m_pInfoPanel->IsExpandBtnVisible())
		{
			m_pInfoPanel->setGeometry(width() -  m_pInfoPanel->getExpandBtnWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->getExpandBtnWidth(), m_pInfoPanel->getExpandBtnHeight() + 10);
		}
		else
		{
			m_pInfoPanel->setGeometry(width() - m_pInfoPanel->pluginWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->pluginWidth(), m_pInfoPanel->pluginHeight());
		}
	}

	if (m_pTabView)
	{
		m_pTabView->setGeometry(0,0,width(),height());
	}


	if (m_pTitle)
	{
		m_pTitle->setGeometry(width()/2 - m_pTitle->width()/2, 0, m_pTitle->width(), m_pTitle->height());
	}
	if (m_pPopBtn)
	{
		m_pPopBtn->setGeometry(width()/2 - m_pPopBtn->width()/2, 0, m_pPopBtn->width(), m_pPopBtn->height());
	}

	if (m_pPopupPanel)
	{
		m_pPopupPanel->setGeometry(400,200,m_pPopupPanel->width(), m_pPopupPanel->height());
	}

	QWidget::resizeEvent(e);
}

void iObjectsDemo::OnCloseBtnClicked()
{
	this->close();
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

void iObjectsDemo::OnToolBoxPlugin_SearchBtnClicked()
{

}

void iObjectsDemo::OnToolBoxPlugin_SettingBtnClicked()
{
	m_pPluginloader = new Pluginloader(NULL);
	connect(m_pPluginloader, SIGNAL(reload()), this, SLOT(reloadPlugins()));
	m_pPluginloader->showModel();
}

void iObjectsDemo::OnInteLayersPlugin_RefeshWindow()
{
	this->repaint();
}

void iObjectsDemo::reloadPlugins()
{	
	QVariantMap pluginMap = PluginManager::instance()->getPluginMap();
	QList<QString> pluginList = pluginMap.keys();

	qDebug()<<m_pluginMap;
	foreach (QString pluginName, pluginList)
	{
		bool a = m_pluginMap.value(pluginName).toBool();
		bool b = pluginMap.value(pluginName).toBool();
		if (m_pluginMap.value(pluginName).toBool() == pluginMap.value(pluginName).toBool())
		{
			continue;
		}
		else if (m_pluginMap.value(pluginName).toBool())
		{
			unLoadPlugins(pluginName);
		}
		else
		{
			loadPlugins(pluginPath, pluginName);
		}
	}
	m_pluginMap = pluginMap;
	qDebug()<<m_pluginMap;
}

void iObjectsDemo::moveEvent( QMoveEvent* e)
{
	QWidget::moveEvent(e);
}

