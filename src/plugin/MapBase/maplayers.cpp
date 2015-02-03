#include "stdafx.h"
#include "maplayers.h"

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QLabel>
#include <QStyleOption>
#include <QPainter>

MapLayers::MapLayers(QWidget *parent) : QWidget(parent)
{
	m_pLayersVLayout = NULL;
	m_pLayersScroll = NULL;
	m_pLayersContainer = NULL;

	setObjectName("MapLayers");

	m_pLayersScroll = new QScrollArea(this);
	//scroll->setClearColor(Qt::transparent);
	m_pLayersScroll->setStyleSheet("background-color:#00000000;");//transparent
	m_pLayersScroll->setAttribute(Qt::WA_TranslucentBackground);

	m_pLayersContainer = new EmptyWidget(m_pLayersScroll);
	//m_pLayersContainer->setAttribute(Qt::WA_TranslucentBackground);
	m_pLayersContainer->setObjectName("LayersContainer");
	m_pLayersContainer->setStyleSheet("background-color:#00000000;");

	m_pLayersVLayout = new QVBoxLayout(m_pLayersScroll);
	m_pLayersVLayout->setContentsMargins(0, 0, 0, 0);
	m_pLayersVLayout->setSpacing(3);
	m_pLayersVLayout->setAlignment(Qt::AlignHorizontal_Mask);
	m_pLayersScroll->setWidget(m_pLayersContainer);

	//m_pLayersScroll->setObjectName("scroll");
	QScrollBar* vBar = m_pLayersScroll->verticalScrollBar();//new QScrollBar(scroll);
	//vBar->setObjectName("VScroll");
	vBar->setFixedWidth(1);
	vBar->hide();

	QScrollBar* hBar = m_pLayersScroll->horizontalScrollBar();
	hBar->setFixedHeight(1);
	hBar->hide();
	m_pLayersScroll->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	m_pLayersScroll->setWidgetResizable(true);

	m_pLayersContainer->setLayout(m_pLayersVLayout);

}

MapLayers::~MapLayers()
{

}

void MapLayers::initLayers( const QVector<QString>& layers )
{
	int h = width();
	int m = m_pLayersContainer->width();
	int k = m_pLayersScroll->width();

	
	foreach (QString name, layers)
	{
		EmptyWidget* p = new EmptyWidget(this);
		connect(p, SIGNAL(changeLayers(const QString&)), this, SIGNAL(changeLayers(const QString&)));
		p->setObjectName("InteLayersItem");
		p->setFixedWidth(width());

		p->m_pLayerText->setText(name);
		QPalette pe;
		pe.setColor(QPalette::WindowText,Qt::white);
		p->m_pLayerText->setPalette(pe);
		
		p->setFixedHeight(40);
		p->setFixedWidth(width());
		p->m_pLayerText->setGeometry(3, p->height()/2 - p->m_pLayerText->height()/2, width(), p->m_pLayerText->height());
		p->setToolTip(name);
		m_pLayersVLayout->addWidget(p);
	}
}

void MapLayers::paintEvent( QPaintEvent * e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void MapLayers::resizeEvent( QResizeEvent * )
{
	if (m_pLayersScroll)
	{
		m_pLayersScroll->setGeometry(0,0,width(),height());
	}
	if (m_pLayersContainer)
	{
		m_pLayersContainer->setGeometry(0,0,width(),height());
	}
}

EmptyWidget::EmptyWidget( QWidget *parent /*= NULL*/ ) : QWidget(parent)
{
	//setObjectName("EmptyWidget");
	m_pLayerText = NULL;
	setAttribute(Qt::WA_TranslucentBackground);
	m_pLayerText = new QLabel(this);
	

}

EmptyWidget::~EmptyWidget()
{
	delete m_pLayerText;
	m_pLayerText = NULL;
}

void EmptyWidget::paintEvent( QPaintEvent * e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void EmptyWidget::mousePressEvent( QMouseEvent * e)
{
	if (m_pLayerText)
	{
		emit changeLayers(m_pLayerText->text());
	}
	
}
