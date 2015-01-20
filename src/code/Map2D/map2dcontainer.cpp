#include "stdafx.h"
#include "map2dcontainer.h"

Map2DContainer::Map2DContainer(QWidget *parent) : QWidget(parent)
{
	setObjectName("Map2DContainer");
	m_pMap2DLayout = new QHBoxLayout(this);
	m_pMapControl = NULL;

	m_pMapControl = new MapControl(this);
	QWidget* map2D = dynamic_cast<QWidget*>(m_pMapControl);
	m_pMap2DLayout->addWidget(map2D);
	this->setLayout(m_pMap2DLayout);
// 	QString mm = QApplication::applicationDirPath() + "/Map/China/China400.smwu";
// 	int flag = m_pMapControl->OpenMap("C:/Users/Administrator/Desktop/iObjectsDemo/bin/Debug/Map/Shanghai/Shanghai.smwu");
 	int flag = m_pMapControl->OpenMap("C:/Users/Administrator/Desktop/China/China400.smwu");
 	m_pMapControl->show();

	//QPushButton* pbtn = new QPushButton(this);
	//connect(pbtn,SIGNAL(clicked()), this, SLOT(onclicked()));
}

Map2DContainer::~Map2DContainer()
{

}

void Map2DContainer::resizeEvent( QResizeEvent * )
{
// 	if (m_pMap2DLayout && m_pMapControl)
// 	{
// 		m_pMap2DLayout->setGeometry(QRect(0, 0, width(), height()));
// 	}
	if (m_pMapControl)
	{
		m_pMapControl->setGeometry(geometry());
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
