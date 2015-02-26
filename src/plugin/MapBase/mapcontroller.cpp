#include "stdafx.h"
#include "mapcontroller.h"
#include <QStyleOption>
#include <QPainter>

MapController::MapController(QWidget *parent) : QWidget(parent)
{
	setObjectName("Map2DController");
	m_pHboxLayout = NULL;
	m_pSelect = NULL;
	m_pPan = NULL;
	m_pEntire = NULL;
	m_pZoomIn = NULL;
	m_pZoomOut = NULL;


	m_pHboxLayout = new QHBoxLayout(this);
	m_pHboxLayout->setContentsMargins(0, 0, 0, 0);
	m_pHboxLayout->setSpacing(0);
	m_pHboxLayout->setAlignment(Qt::AlignHorizontal_Mask);


	m_pSelect = new QToolButton(this);
	m_pSelect->setFixedHeight(height());
	m_pSelect->setFixedWidth(height());
	m_pSelect->setObjectName("SelectBtn");
	//m_pSelect->setIcon(QIcon(":/select.png"));
	m_pSelect->setIcon(QPixmap(":/select.png").scaled(height(), height()));
	connect(m_pSelect, SIGNAL(clicked()), this, SIGNAL(selectClicked()));

	m_pPan = new QToolButton(this);
	m_pPan->setFixedHeight(height());
	m_pPan->setFixedWidth(height());
	m_pPan->setObjectName("PanBtn");
	//m_pPan->setIcon(QIcon(":/Pan.png"));
	m_pPan->setIcon(QPixmap(":/Pan.png").scaled(height(), height()));
	connect(m_pPan, SIGNAL(clicked()), this, SIGNAL(panClicked()));

	m_pEntire = new QToolButton(this);
	m_pEntire->setFixedHeight(height());
	m_pEntire->setFixedWidth(height());
	m_pEntire->setObjectName("EntireBtn");
	//m_pEntire->setIcon(QIcon(":/Entire.png"));
		m_pEntire->setIcon(QPixmap(":/Entire.png").scaled(height(), height()));
	connect(m_pEntire, SIGNAL(clicked()), this, SIGNAL(entireClicked()));

	m_pZoomIn = new QToolButton(this);
	m_pZoomIn->setFixedHeight(height());
	m_pZoomIn->setFixedWidth(height());
	m_pZoomIn->setObjectName("ZoomInBtn");
	//m_pZoomIn->setIcon(QIcon(":/Zoomin.png"));
	m_pZoomIn->setIcon(QPixmap(":/Zoomin.png").scaled(48, 48));
	connect(m_pZoomIn, SIGNAL(clicked()), this, SIGNAL(zoominClicked()));

	m_pZoomOut = new QToolButton(this);
	m_pZoomOut->setFixedHeight(height());
	m_pZoomOut->setFixedWidth(height());
	m_pZoomOut->setObjectName("ZoomOutBtn");
	//m_pZoomOut->setIcon(QIcon(":/Zoomout.png"));
	m_pZoomOut->setIcon(QPixmap(":/Zoomout.png").scaled(height(), height()));
	connect(m_pZoomOut, SIGNAL(clicked()), this, SIGNAL(zoomoutClicked()));


	m_pHboxLayout->addWidget(m_pSelect);
	m_pHboxLayout->addWidget(m_pPan);
	m_pHboxLayout->addWidget(m_pEntire);
	m_pHboxLayout->addWidget(m_pZoomIn);
	m_pHboxLayout->addWidget(m_pZoomOut);
	this->setLayout(m_pHboxLayout);
}

MapController::~MapController()
{

}


void MapController::paintEvent( QPaintEvent * e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void MapController::resizeEvent( QResizeEvent * )
{
	m_pSelect->setFixedHeight(height());
	m_pSelect->setFixedWidth(height());
	m_pPan->setFixedHeight(height());
	m_pPan->setFixedWidth(height());
	m_pEntire->setFixedHeight(height());
	m_pEntire->setFixedWidth(height());
	m_pZoomIn->setFixedHeight(height());
	m_pZoomIn->setFixedWidth(height());
	m_pZoomOut->setFixedHeight(height());
	m_pZoomOut->setFixedWidth(height());
}
