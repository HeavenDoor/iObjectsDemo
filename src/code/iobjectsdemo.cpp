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
	setAcceptDrops(true);
	m_pTitle = NULL;
	//m_pCloseBtn = NULL;
	m_pPopBtn = NULL;
	m_pToolBox = NULL;
	m_pMapBase = NULL;
	m_pSceneBase = NULL;
	m_pInteLayers = NULL;
	m_pInfoPanel = NULL;
	m_pTabView = NULL;
	m_pFlowTabView = NULL;
	m_pPopupPanel = NULL;
	m_pPluginloader = NULL;
	m_pFlowLayout = NULL;
	m_pTabBarPanel = NULL;
	m_pMirrorPanel = NULL;


//	m_pMainLayout = new QGridLayout();
	initInteLayers();
	initTabView();
	initToolBox();
// 	m_pPluginloader = new Pluginloader(NULL);
// 	m_pPluginloader->showModel();

 	pluginPath = "../plugins";
 
 	m_pluginMap = PluginManager::instance()->getDefaultPluginMap();
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

	//setLayout(m_pMainLayout);
	//qApp->installEventFilter(this);
}

iObjectsDemo::~iObjectsDemo()
{

}

bool iObjectsDemo::initTabView()
{
 	m_pTabView = new TabView(this);
	m_pTabView->setProperty("Names", "NoFlow");
// 	QWidget* e = new QWidget(m_pTabView);
// 	e->setObjectName("TwoDimension");
// 	m_pTabView->addCentralWidget(e, 3, QStringLiteral("成都"));
// 	QWidget* rr = new QWidget(m_pTabView);
// 	rr->setObjectName("rr");
// 	m_pTabView->addCentralWidget(rr, 0, "rr");

// 	m_pFlowTabView = new TabView(NULL);
// 	m_pFlowTabView->setProperty("Names", "FlowUp");
// 	m_pFlowTabView->setWindowFlags(Qt::Window);
// 	m_pFlowTabView->setGeometry(100,100,800,600);
// 
// 	m_pFlowTabView->setCurrentIndex(0);
// 	m_pFlowTabView->loadDefaultSkin();
// //	m_pFlowTabView->show();
// 	m_pFlowTabView->hide();
// 	//m_pFlowTabView->raise();
	





	m_pMirrorPanel = new MirrorPanel();
	m_pMirrorPanel->setWindowFlags(Qt::Window);
	m_pMirrorPanel->setGeometry(200,200,800,600);
	m_pMirrorPanel->show();

	connect(m_pTabView, SIGNAL(moveTabPage(QWidget*, QString)), m_pMirrorPanel->getTabView(), SLOT(OnMoveTabPage( QWidget*, QString )));
	connect(m_pMirrorPanel->getTabView(), SIGNAL(moveTabPage(QWidget*, QString)), m_pTabView, SLOT(OnMoveTabPage( QWidget*, QString )));

	connect(m_pTabView, SIGNAL(removeTabPage(QWidget*, QString)), m_pMirrorPanel->getTabView(), SLOT(OnReMoveTabPage( QWidget*, QString )));
	connect(m_pMirrorPanel->getTabView(), SIGNAL(removeTabPage(QWidget*, QString)), m_pTabView, SLOT(OnReMoveTabPage( QWidget*, QString )));

	connect(m_pTabView, SIGNAL(tabViewChange()), this, SLOT(OnTabViewChange()));
	connect(m_pMirrorPanel, SIGNAL(tabViewChange()), this, SLOT(OnTabViewChange()));
	return true;
}


bool iObjectsDemo::initInteLayers()
{
	m_pInteLayers = new InteLayers(this);
	m_pInteLayers->setInteLayersTitle(QStringLiteral("超图软件公司"));
	connect(m_pInteLayers, SIGNAL(refeshWindow()), this, SLOT(OnInteLayersPlugin_RefeshWindow()));
	m_pInteLayers->setInteLayersWidth(216);
	m_pInteLayers->setInteLayersHeight(410);
	m_pInteLayers->setGeometry(15, height()/2 - m_pInteLayers->InteLayersHeight()/2, m_pInteLayers->InteLayersWidth(), m_pInteLayers->InteLayersHeight());
	m_pInteLayers->raise();
	return true;
}

bool iObjectsDemo::initToolBox()
{
	m_pToolBox = new ToolBox(this);
	m_pToolBox->setFixedHeight(50);
	m_pToolBox->addSpacing(5);
	//m_pToolBox->setToolButtonSize(QSize(40,40));
	m_pToolBox->setToolButtonSize(QSize(32,32)); // m_pToolBox->height() - 10,m_pToolBox->height() - 10
// 	QObject* obj = m_pToolBox->createToolButton("search");
// 	if(obj) connect(obj, SIGNAL(clicked()), this, SLOT(OnToolBoxPlugin_SearchBtnClicked()));
	QObject* obj = m_pToolBox->createToolButton("set");
	if(obj) connect(obj, SIGNAL(clicked()), this, SLOT(OnToolBoxPlugin_SettingBtnClicked()));
	m_pToolBox->addLine();

	//m_pCloseBtn = new QPushButton(this);

	obj = m_pToolBox->createToolButton("CloseBtn", Qt::AlignRight);
	obj->setObjectName("CloseBtn");
	m_pToolBox->addSpacing(5, Qt::AlignRight);
// 	obj->setFixedHeight(48);
// 	obj->setFixedWidth(48);
	//m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
	connect(obj, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));


	//m_pMainLayout->addWidget(m_pToolBox, 0, 1);
	
	return true;
}

bool iObjectsDemo::initControls()
{
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


	m_pTabBarPanel = new TabBarPanel(this);
	m_pTabBarPanel->setFixedWidth(32);
	m_pTabBarPanel->addTabBarWidget(m_pTabView->getTabBar());
	if (m_pMapBase)
	{
		m_pTabBarPanel->addTrigerWidget(m_pMapBase->getPropertyTrigger());
		m_pMapBase->getPropertyTrigger()->hide();
		//m_pTabBarPanel->addTrigerWidget(new QPushButton("aaa"));
	}
	
	//m_pMainLayout->addWidget(m_pTabBarContainer, 0, 1);


// 	m_pCloseBtn = new QPushButton(this);
// 	m_pCloseBtn->setObjectName("CloseBtn");
// 	m_pCloseBtn->setFixedHeight(48);
// 	m_pCloseBtn->setFixedWidth(48);
// 	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
// 	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));

	//m_pInfoPanel = new InfoPanel(this);
	//m_pInfoPanel->setPluginWidth(280);
	//m_pInfoPanel->setPluginHeight(370);
	////m_pInfoPanel->setGeometry(15, height()/2 - 200, 280, 370);
	//m_pInfoPanel->show();
	//m_pInfoPanel->raise();
	//m_pInfoPanel->setAnimationTimespan(600);
	//m_pInfoPanel->setGeometry(width() - m_pInfoPanel->pluginWidth() - 15 ,height()/2 - m_pInfoPanel->pluginHeight()/2, m_pInfoPanel->pluginWidth(), m_pInfoPanel->pluginHeight());
	
// 	dock = new QDockWidget(this);
// 	addDockWidget(Qt::RightDockWidgetArea, dock);
// 	QDockWidget* c = new QDockWidget(this);
// 	addDockWidget(Qt::RightDockWidgetArea, c);
// 	c->setFixedWidth(150);
	return true;
}

bool iObjectsDemo::unLoadPlugins(const QString& pluginName )
{
	bool bPluginunload = false;
	QPluginLoader* loader = qobject_cast<QPluginLoader*>(this->findChild<QPluginLoader*>(pluginName));

	if (pluginName == "MapBase"/*loader->instance()->inherits("MapTabInterface")*/)
	{
		if (m_pTabView && m_pMapBase && m_pInteLayers)
		{
			m_pInteLayers->removeLayers(m_pMapBase->getMapLayers());
			m_pToolBox->removeWidget(m_pMapBase->getMapController());
			m_pTabView->removeCentralWidget(m_pMapBase->getWidget());
			
		}
		bPluginunload = loader->unload();
		m_pMapBase = NULL;
	}
	if (pluginName == "SceneBase")
	{
		if (m_pTabView && m_pSceneBase)
		{
			//m_pInteLayers->removeLayers(m_pMapBase->getMapLayers());
			//m_pToolBox->removeWidget(m_pMapBase->getMapController());
			m_pTabView->removeCentralWidget(m_pSceneBase->getWidget());
		}
		bPluginunload = loader->unload();
		m_pSceneBase = NULL;
	}
	return bPluginunload;
}

bool iObjectsDemo::loadPlugins(const QString& path, const QString& pluginName)
{
// 	while (true)
// 	{
// 
// 	}
	bool bPluginLoaded = false;

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);

	qApp->addLibraryPath(path);
	QStringList ll = qApp->libraryPaths();
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
						connect(m_pMapBase->getObject(), SIGNAL(showTips()), this, SLOT(OnShowMapBaseTips()));
						m_pTabView->addCentralWidget(m_pMapBase->getWidget(), 0, QStringLiteral("二维"));
						m_pTabView->setCurrentIndex(0);
						m_pTabView->loadDefaultSkin();
						m_pInteLayers->addLayers(m_pMapBase->getMapLayers());
						m_pToolBox->addWidget(m_pMapBase->getMapController());
						setStyleSheet(m_pMapBase->getStyleSheet());
					}					
				}
			}
		}

		if (object->inherits("SceneBaseInterface"))
		{
			m_pSceneBase = qobject_cast<SceneBaseInterface*>(object) ;  
			if (m_pSceneBase)  
			{
				bPluginLoaded = true;
				m_pSceneBase->setPluginParent(this);	
				{
					if (m_pTabView)
					{
// 						connect(m_pMapBase->getObject(), SIGNAL(showTips()), this, SLOT(OnShowMapBaseTips()));
 						
						if (m_pMapBase)
						{
							m_pSceneBase->setUGMapEditorWnd(m_pMapBase->getUGMapEditorWnd());
						}
// 						QWidget* w = new QWidget(this);
// 						QVBoxLayout* pLayout;
// 						pLayout = new QVBoxLayout();
// 						pLayout->setSpacing(0);
// 						pLayout->setMargin(0);
// 						w->setLayout(pLayout);
// 						m_pSceneBase->setPluginParent(w);
// 						pLayout->addWidget(m_pSceneBase->getWidget());
						m_pTabView->addCentralWidget(m_pSceneBase->getWidget(), 1, QStringLiteral("三维"));
 						m_pTabView->setCurrentIndex(0);
 						m_pTabView->loadDefaultSkin();
						int m = m_pTabView->width();
						int n = m_pTabView->height();
						m_pSceneBase->resizePlugin(0,0,width(), height());
// 						m_pInteLayers->addLayers(m_pMapBase->getMapLayers());
// 						m_pToolBox->addWidget(m_pMapBase->getMapController());
 						//setStyleSheet(m_pSceneBase->getStyleSheet());
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
// 	if (m_pCloseBtn)
// 	{
// 		m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());
// 	}

	
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

	if (m_pTabBarPanel && m_pToolBox)
	{
		m_pTabBarPanel->setGeometry(width() - m_pTabBarPanel->width(), 0 , m_pTabBarPanel->width(), height() - m_pToolBox->height());
	}
	if (m_pTabView &&m_pTabBarPanel)
	{
		m_pTabView->setGeometry(0, 0, width() - m_pTabBarPanel->width(), height() - m_pToolBox->height());
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
	if (!m_pPluginloader)
	{
		m_pPluginloader = new Pluginloader(NULL);
		connect(m_pPluginloader, SIGNAL(reload()), this, SLOT(reloadPlugins()));
	}	
	m_pPluginloader->showModel();
	m_pPluginloader->raise();
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

void iObjectsDemo::mousePressEvent( QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		m_PressPoint = mapToGlobal(e->pos());
	}
}

void iObjectsDemo::OnShowMapBaseTips()
{
	m_pPopupPanel =new PopupPanel(this);
	connect(m_pPopupPanel, SIGNAL(closePopupPanel()), this, SLOT(OnClosePopupPanel()));
	m_pPopupPanel->setFixedHeight(350);
	m_pPopupPanel->setFixedWidth(500);
	m_pPopupPanel->setGeometry(m_PressPoint.x() - m_pPopupPanel->width()/2, m_PressPoint.y() - m_pPopupPanel->height(), m_pPopupPanel->width(), m_pPopupPanel->height());
	m_pPopupPanel->show();
	m_pPopupPanel->raise();
}

bool iObjectsDemo::eventFilter(QObject* obj, QEvent* e)
{


	if(e->type() == QEvent::Drop)
	{
		int m = 0;
	}

	if(e->type() == QEvent::DragMove)
	{
// 		if (e->mimeData()->hasFormat("application/x-dnditemdata")) 
// 		{
// 		}
		QDragMoveEvent* en = dynamic_cast<QDragMoveEvent*>(e);
		//if(!en) return false;
// 
		QByteArray itemData = en->mimeData()->data("application/x-dnditemdata");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPixmap pixmap;
		QString offset;
		dataStream >> pixmap >> offset;

		int m = 0;
// 		if (en->buttons() && Qt::LeftButton)
// 		{  
// 			if (m_pPopupPanel)
// 			{
// 				delete m_pPopupPanel;
// 				m_pPopupPanel = NULL;
// 			}
// 			m_PressPoint = en->pos();
// 		}
// 		QPoint point = en->globalPos();
// 		QRect rect = WidgetRect::widgetGlobalRect(this);

	}


	return false;
}

void iObjectsDemo::OnClosePopupPanel()
{
	if (m_pPopupPanel)
	{
		delete m_pPopupPanel;
		m_pPopupPanel = NULL;
	}
}

void iObjectsDemo::dragEnterEvent( QDragEnterEvent *event )
{

}

void iObjectsDemo::dropEvent( QDropEvent *event )
{

}

void iObjectsDemo::OnTabViewChange()
{
	if (m_pInteLayers)
	{
		m_pInteLayers->raise();
	}
}
