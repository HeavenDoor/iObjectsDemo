#include "stdafx.h"
#include "map2dcontainer.h"
#include "sysconfig.h"

Map2DContainer::Map2DContainer(QWidget *parent) : QWidget(parent)
{
	m_pMapControl = NULL;
	m_pMap2DController = NULL;

	setObjectName("Map2DContainer");
	m_pMap2DLayout = new QHBoxLayout(this);
	

	m_pMap2DController = new Map2DController(this);
	m_pMap2DController->setFixedHeight(32);
	m_pMap2DController->setFixedWidth(32*5);
	connect(m_pMap2DController, SIGNAL(selectClicked()), this, SLOT(OnSelectClicked()));
	connect(m_pMap2DController, SIGNAL(panClicked()), this, SLOT(OnPanClicked()));
	connect(m_pMap2DController, SIGNAL(entireClicked()), this, SLOT(OnEntireClicked()));
	connect(m_pMap2DController, SIGNAL(zoominClicked()), this, SLOT(OnZoomInClicked()));
	connect(m_pMap2DController, SIGNAL(zoomoutClicked()), this, SLOT(OnZoomOutClicked()));


	m_pMapControl = new MapControl(this);
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
	}
 	m_pMapControl->show();
	m_pMap2DController->show();
	m_pMap2DController->raise();

	m_Layers = m_pMapControl->getLayersList();
	m_Layers.push_front(m_MapUrl);
//	emit showLayers(m_Layers);

}

Map2DContainer::~Map2DContainer()
{
	m_Layers.clear();

	m_pMapControl->Release();
	delete m_pMapControl;
	m_pMapControl = NULL;
}

void Map2DContainer::resizeEvent( QResizeEvent * )
{
// 	if (m_pMap2DLayout && m_pMapControl)
// 	{
// 		m_pMap2DLayout->setGeometry(QRect(0, 0, width(), height()));
// 	}
	if (m_pMapControl)
	{
		m_pMapControl->setGeometry(0, 0, width(), height());
	}

	if (m_pMap2DController)
	{
		m_pMap2DController->setGeometry(20, height() - 100, m_pMap2DController->width(), m_pMap2DController->height());
	//	m_pMap2DController->raise();
	}

}

void Map2DContainer::paintEvent( QPaintEvent * e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void Map2DContainer::onclicked()
{
	

	QString mm = QApplication::applicationDirPath() + "/Map/China/China400.smwu";
	//int flag = m_pMapControl->OpenMap("C:/Users/Administrator/Desktop/iObjectsDemo/bin/Debug/Map/Shanghai/Shanghai.smwu");
	int flag = m_pMapControl->OpenMap("C:/Users/Administrator/Desktop/China/China400.smwu");
	m_pMapControl->show();
}


void Map2DContainer::OnSelectClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Select();
	}
}

void Map2DContainer::OnPanClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Pan();
	}
}

void Map2DContainer::OnEntireClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ViewEntire();
	}
}

void Map2DContainer::OnZoomInClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomIn();
	}
}

void Map2DContainer::OnZoomOutClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomOut();
	}
}

QString Map2DContainer::getMapUrl() const
{
	return m_MapUrl;
}

QVector<QString> Map2DContainer::getLayers() const
{
	return m_Layers;
}
