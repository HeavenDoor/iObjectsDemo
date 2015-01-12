#include "stdafx.h"
#include "iobjectsdemo.h"
#include "commom/widgetrect.h"
#include "pluginloader.h"

#include <QLabel>
#include <QWidget>
#include <QUrl>

#include <QQuickWidget>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQuick/QtQuick>



iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");
	setGeometry(200,200,1247,766);
	
	Pluginloader* loader = new Pluginloader(NULL);
	loader->showModel();

	QString pluginPath;
#if QT_NO_DEBUG
	pluginPath = "../bin/release";
#else
	pluginPath = "../bin/debug";
#endif 

	if (!loadPlugins(pluginPath, "MapTab"))
	{
		exit(0);
	}

	if (!loadPlugins(pluginPath, "ToolBox"))
	{
		exit(0);
	}

	if (!loadPlugins(pluginPath, "InteLayers"))
	{
		exit(0);
	}



	m_pMapTab->setPluginParent(this);
	m_pMapTab->setPluginGeometry(0, 0, width(), height());
	m_pMapTab->showPlugin();

	 
	m_pPopBtn = new QPushButton(this);
	m_pPopBtn->setObjectName("PopTitleBtn");
	m_pPopBtn->setFixedWidth(40);
	m_pPopBtn->setFixedHeight(8);
	m_pPopBtn->setGeometry(width()/2 - m_pPopBtn->width()/2, 0, m_pPopBtn->width(), m_pPopBtn->height());
	m_pPopBtn->hide();
	



	m_pTitle = new Title(this);
	//m_pTitle->setFixedHeight(85);
	//m_pTitle->setFixedWidth(530);
	//m_pTitle->setGeometry(width()/2 - m_pTitle->width()/2, 0, 530, 85 );
	connect(m_pTitle, SIGNAL(collapse()), this, SLOT(OnTitleCollapsed()));
	connect(m_pPopBtn, SIGNAL(clicked()), m_pTitle, SLOT(expandTitle()));



	m_pInteLayers->setPluginParent(this);
	m_pInteLayers->setPluginGeometry(15, height()/2 - 200, 216, 400);
	m_pInteLayers->showPlugin();
	m_pInteLayers->raisePlugin();
	connect(m_pInteLayers->getObject(), SIGNAL(refeshWindow()), this, SLOT(OnInteLayersPlugin_RefeshWindow()));
	
	m_pToolBox->setPluginParent(this);
	m_pToolBox->setPluginGeometry(15, height()/2 - 200, 216, 400);
	m_pToolBox->showPlugin();
	m_pToolBox->raisePlugin();
	connect(m_pToolBox->getObject(), SIGNAL(ToolBoxPlugin_SearchBtnClicked()), this, SLOT(OnToolBoxPlugin_SearchBtnClicked()));
	connect(m_pToolBox->getObject(), SIGNAL(ToolBoxPlugin_SettingBtnClicked()), this, SLOT(OnToolBoxPlugin_SettingBtnClicked()));


	
	m_pInfoPanel = new QQuickWidget(this);
	m_pInfoPanel->setFixedWidth(270);
	m_pInfoPanel->setFixedHeight(380);

	m_pInfoPanel->setResizeMode(QQuickWidget::SizeRootObjectToView);
	//view->setWindowOpacity(0.2);
	m_pInfoPanel->setClearColor(Qt::transparent);
	m_pInfoPanel->setAttribute(Qt::WA_AlwaysStackOnTop);
	m_pInfoPanel->setMouseTracking(true);

	m_pInfoPanel->engine()->addImportPath("Resources/TimeExample");
	//m_pInfoPanel->engine()->addImportPath("C:/Users/Administrator/Desktop/iObjectsDemo/src/Resources");
	//m_pInfoPanel->engine()->addImportPath("C:/Users/Administrator/Desktop/iObjectsDemo/src/Resources/TimeExample");
	//m_pInfoPanel->engine()->addPluginPath("C:/Users/Administrator/Desktop/iObjectsDemo/src/Resources/TimeExample");

	m_pInfoPanel->engine()->addPluginPath("../bin/Debug");

	QStringList list = m_pInfoPanel->engine()->importPathList();

	QStringList li = m_pInfoPanel->engine()->pluginPathList();
	QList<QQmlError> errorss;
	//QString s = qApp->applicationDirPath();
	//QString b = s + "/InfoPanel.dll";
	bool m = m_pInfoPanel->engine()->importPlugin("../bin/Debug/InfoPanel.dll", "TimeExample", &errorss);

	//C:/Users/Administrator/Desktop/iObjectsDemo/bin/Debug/InfoPanel.dll
	//QString yy = errorss.at(0).toString();


	//view->setSource(QUrl("Resources/TimeExample/a/plugins.qml"));
	m_pInfoPanel->setSource(QUrl("Resources/TimeExample/plugins.qml"));
	m_pInfoPanel->show();
 	m_pInfoPanel->raise();



	loadControls();

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
		m_pToolBox->resizePlugin(0 ,height()-50, width(), 50);
	}
	if (m_pInteLayers)
	{
		m_pInteLayers->resizePlugin(15, height()/2 - 200, 216, 400);
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

	if (m_pInfoPanel)
	{
		m_pInfoPanel->setGeometry(width() - m_pInfoPanel->width() - 15 ,height()/2 - 200,270,380);
	}
	
	
	QWidget::resizeEvent(e);
}

void iObjectsDemo::OnCloseBtnClicked()
{
	this->close();
}


bool iObjectsDemo::loadControls()
{
	//QLabel *lable = new QLabel(this);
	//lable->setText(QStringLiteral("我是中文"));
	
	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("CloseBtn");
	m_pCloseBtn->setFixedHeight(48);
	m_pCloseBtn->setFixedWidth(48);
	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());

	
	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));

	return true;
}

bool iObjectsDemo::loadPlugins(const QString& path, const QString& pluginName)
{
	bool bPluginLoaded = false;
	qApp->addLibraryPath(path); // ../bin/debug
	QPluginLoader loader(pluginName) ;  
	//QPluginLoader loader(QString("libMyPlugin.so")) ;  
	QObject* object;
	if ( (object=loader.instance()) != NULL )  
	{  

		QString name = object->objectName();
		if (object->inherits("ToolBoxInterface"))
		{
			m_pToolBox = qobject_cast<ToolBoxInterface*>(object) ;  
			if (m_pToolBox)  
			{
				bPluginLoaded = true;
			}
		}
		if (object->inherits("MapTabInterface"))
		{
			m_pMapTab = qobject_cast<MapTabInterface*>(object) ;  
			if (m_pMapTab)  
			{
				bPluginLoaded = true;
			}
		}

		if (object->inherits("InteLayersInterface"))
		{
			m_pInteLayers = qobject_cast<InteLayersInterface*>(object) ;  
			if (m_pInteLayers)  
			{
				bPluginLoaded = true;
			}
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

void iObjectsDemo::OnToolBoxPlugin_SearchBtnClicked()
{

}

void iObjectsDemo::OnToolBoxPlugin_SettingBtnClicked()
{

}

void iObjectsDemo::OnInteLayersPlugin_RefeshWindow()
{
	this->repaint();
}
