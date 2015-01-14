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

	m_pToolBox = NULL;
	m_pMapTab = NULL;
	m_pInteLayers = NULL;
	m_pInfoPanel = NULL;

	m_pPluginloader = new Pluginloader(NULL);
	m_pPluginloader->showModel();

//#if QT_NO_DEBUG
	pluginPath = "../plugins";
// #else
// 	pluginPath = "../bin/debug";
// #endif 

	m_pluginMap = PluginManager::instance()->getPluginMap();
	QList<QString> pluginList = m_pluginMap.keys();

	qDebug()<<m_pluginMap;
	foreach(QString pluginName, pluginList)
	{
		if (!m_pluginMap.value(pluginName).toBool()) continue;
		if(!loadPlugins(pluginPath, pluginName))
			continue;
	}
	 
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

	loadControls();

	if (m_pPluginloader)
	{
		delete m_pPluginloader;
		m_pPluginloader = NULL;
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

void iObjectsDemo::resizeEvent(QResizeEvent* e)
{
	if (m_pCloseBtn)
	{
		m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
	}
	
	if (m_pToolBox)
	{
		m_pToolBox->resizePlugin(0 ,height()-m_pToolBox->pluginHeight(), width(), m_pToolBox->pluginHeight());
	}
	if (m_pInteLayers)
	{
		m_pInteLayers->resizePlugin(15, height()/2 - m_pInteLayers->pluginHeight()/2,  m_pInteLayers->pluginWidth(), m_pInteLayers->pluginHeight());

		//m_pInteLayers->resizePlugin(15, height()/2 - 200,  216, 400);
	}

	if (m_pInfoPanel)
	{
		m_pInfoPanel->resizePlugin(width() - m_pInfoPanel->pluginWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->pluginWidth(), m_pInfoPanel->pluginHeight());
	}

	if (m_pMapTab)
	{
		m_pMapTab->resizePlugin(0, 0, width(), height());
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
	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("CloseBtn");
	m_pCloseBtn->setFixedHeight(48);
	m_pCloseBtn->setFixedWidth(48);
	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));
	return true;
}

bool iObjectsDemo::unLoadPlugins(const QString& pluginName )
{
	bool bPluginunload = false;
	QPluginLoader* loader = qobject_cast<QPluginLoader*>(this->findChild<QPluginLoader*>(pluginName));
	bPluginunload = loader->unload();
	return bPluginunload;
}

bool iObjectsDemo::loadPlugins(const QString& path, const QString& pluginName)
{
	bool bPluginLoaded = false;
	qApp->addLibraryPath(path);
	QPluginLoader* loader = new QPluginLoader(pluginName, this);  
	loader->setObjectName(pluginName);
	QObject* object;
	if ( (object=loader->instance()) != NULL )  
	{  

		QString name = object->objectName();
		if (object->inherits("ToolBoxInterface"))
		{
			m_pToolBox = qobject_cast<ToolBoxInterface*>(object) ;  
			if (m_pToolBox)  
			{
				bPluginLoaded = true;
				m_pToolBox->setPluginParent(this);
				m_pToolBox->setPluginHeight(50);
				m_pToolBox->setPluginGeometry(0 ,height() - m_pToolBox->pluginHeight(), width(), m_pToolBox->pluginHeight());
				m_pToolBox->showPlugin();
				m_pToolBox->raisePlugin();
				connect(m_pToolBox->getObject(), SIGNAL(ToolBoxPlugin_SearchBtnClicked()), this, SLOT(OnToolBoxPlugin_SearchBtnClicked()));
				connect(m_pToolBox->getObject(), SIGNAL(ToolBoxPlugin_SettingBtnClicked()), this, SLOT(OnToolBoxPlugin_SettingBtnClicked()));
			}
		}
		if (object->inherits("MapTabInterface"))
		{
			m_pMapTab = qobject_cast<MapTabInterface*>(object) ;  
			if (m_pMapTab)  
			{
				bPluginLoaded = true;
				m_pMapTab->setPluginParent(this);
				m_pMapTab->setPluginGeometry(0, 0, width(), height());
				m_pMapTab->showPlugin();
				m_pMapTab->lowerPlugin();
			}
		}
		
		if (object->inherits("InteLayersInterface"))
		{
			m_pInteLayers = qobject_cast<InteLayersInterface*>(object) ;  
			if (m_pInteLayers)  
			{
				bPluginLoaded = true;
				m_pInteLayers->setPluginParent(this);
				m_pInteLayers->setPluginHeight(400);
				m_pInteLayers->setPluginWidth(216);
				m_pInteLayers->setPluginGeometry(15, height()/2 - m_pInteLayers->pluginHeight()/2, m_pInteLayers->pluginWidth(), m_pInteLayers->pluginHeight());
				//m_pInteLayers->resizePlugin(15, height()/2 - 200,  216, 400);
				m_pInteLayers->showPlugin();
				m_pInteLayers->raisePlugin();
				connect(m_pInteLayers->getObject(), SIGNAL(refeshWindow()), this, SLOT(OnInteLayersPlugin_RefeshWindow()));
			}
		}
		if (object->inherits("InfoPanelInterface"))
		{
			m_pInfoPanel = qobject_cast<InfoPanelInterface*>(object);
			if (m_pInfoPanel)
			{
				bPluginLoaded = true;
				m_pInfoPanel->setPluginParent(this);
				m_pInfoPanel->setPluginWidth(270);
				m_pInfoPanel->setPluginHeight(380);
				m_pInfoPanel->setPluginGeometry(15, height()/2 - 200, 216, 400);
				m_pInfoPanel->showPlugin();
				m_pInfoPanel->raisePlugin();
				m_pInfoPanel->resizePlugin(width() - m_pInfoPanel->pluginWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->pluginWidth(), m_pInfoPanel->pluginHeight());
			}
		}
	}  
	else  
	{  
		qDebug("failed to load plugin !! ");  
		QString errorStr = loader->errorString();  
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
