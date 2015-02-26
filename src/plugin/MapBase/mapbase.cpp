#include "stdafx.h"
#include "mapbase.h"
#include "..\\..\\commom\\sysconfig.h"

#include <QDir>
#include <QStyleOption>
#include <QPainter>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>

MapBase::MapBase(QWidget *parent) : QWidget(parent)
{
	setObjectName("MapTab");

	m_pMapControl = NULL;
	m_pMapController = NULL;
	m_pMapLayers = NULL;

	setObjectName("Map2DContainer");
	m_pMap2DLayout = new QHBoxLayout(this);


	m_pMapController = new MapController(this);
	m_pMapController->setFixedHeight(32);
	m_pMapController->setFixedWidth(32*5);
	connect(m_pMapController, SIGNAL(selectClicked()), this, SLOT(OnSelectClicked()));
	connect(m_pMapController, SIGNAL(panClicked()), this, SLOT(OnPanClicked()));
	connect(m_pMapController, SIGNAL(entireClicked()), this, SLOT(OnEntireClicked()));
	connect(m_pMapController, SIGNAL(zoominClicked()), this, SLOT(OnZoomInClicked()));
	connect(m_pMapController, SIGNAL(zoomoutClicked()), this, SLOT(OnZoomOutClicked()));

	m_pMapLayers = new MapLayers(this);
	connect(m_pMapLayers, SIGNAL(changeLayers(const QString&, int )), this, SLOT(OnChangeLayers(const QString&, int)));
	//m_pMapLayers->setAttribute(Qt::WA_TranslucentBackground);

	m_pMapControl = new MapControl(this);
	connect(m_pMapControl, SIGNAL(showTips()), this, SIGNAL(showTips()));

	QWidget* map2D = dynamic_cast<QWidget*>(m_pMapControl);
	m_pMap2DLayout->addWidget(map2D);
	this->setLayout(m_pMap2DLayout);
	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);

	QFileInfo info("../Map/China/China400.smwu");
	QString ssb = info.absoluteFilePath();
	QDir::setCurrent(ss);

	m_MapUrl = SysConfig::getValue("DefaultMap/DefaultMapPath").toString();
	int flag = m_pMapControl->OpenMap(m_MapUrl);


	if (flag != 0)
	{
		QMessageBox::warning(NULL, "", QString::number(flag));
		return;
	}
	m_pMapControl->show();
	m_pMapController->show();
	m_pMapController->raise();
	m_Layers = m_pMapControl->getLayersList();
	//m_Layers.push_front(m_MapUrl);

	m_pMapLayers->setGeometry(300,100,220,360);
	m_pMapLayers->setFixedWidth(220);
	m_pMapLayers->setFixedHeight(360);

	m_pMapLayers->initLayers(m_Layers);

	m_pMapLayers->show();
	m_pMapLayers->raise();

	QFile file(":/mapbase.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}

MapBase::~MapBase()
{
 	m_Layers.clear();
 
	if (m_pMapLayers)
	{
		delete m_pMapLayers;
		m_pMapLayers = NULL;
	}
	if (m_pMapController)
	{
		delete m_pMapController;
		m_pMapController = NULL;
	}
	if (m_pMapControl)
	{
		m_pMapControl->Release();
		delete m_pMapControl;
		m_pMapControl = NULL;
	}
}

void MapBase::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

QWidget* MapBase::getWidget()
{
	return this;
}


void* MapBase::getUGMapEditorWnd()
{
	if (!m_pMapControl) return NULL;
	{
	}
}



QWidget* MapBase::getMapLayers()
{
	return m_pMapLayers;
}

void MapBase::test()
{

}

void MapBase::resizeEvent( QResizeEvent* e)
{
	if (m_pMapControl)
	{
		m_pMapControl->setGeometry(0, 0, width(), height());
	}

// 	if (m_pMapController)
// 	{
// 		m_pMapController->setGeometry(20, height() - 100, m_pMapController->width(), m_pMapController->height());
// 	}

// 	if (m_pMapLayers)
// 	{
// 		m_pMapLayers->setGeometry(300,100,220,360);
// 	}

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

// void MapBase::loadSkin()
// {
// 	QFile file(":/maptab.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 	this->setStyleSheet(style);
// 	file.close();
// }



void MapBase::OnSelectClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Select();
	}
}

void MapBase::OnPanClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Pan();
	}
}

void MapBase::OnEntireClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ViewEntire();
	}
}

void MapBase::OnZoomInClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomIn();
	}
}

void MapBase::OnZoomOutClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomOut();
	}
}

QString MapBase::getMapUrl() const
{
	return m_MapUrl;
}

/*QVector<QString>*/QVector<QVariantList> MapBase::getLayers() const
{
	return m_Layers;
}

QString MapBase::getStyleSheet()
{
	return this->styleSheet();
}

void MapBase::OnChangeLayers( const QString& text , int index)
{
	if (m_pMapControl)
	{
		m_pMapControl->openLayers(text, index);
	}
}

QWidget* MapBase::getMapController()
{
	return m_pMapController;
}



