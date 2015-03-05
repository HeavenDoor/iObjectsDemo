#include "stdafx.h"
#include "propertypanel.h"

#include <QStyleOption>
#include <QPainter>

PropertyPanel::PropertyPanel(QWidget *parent) : QWidget(parent)
{
	setObjectName("PropertyPanel");
	m_pVLayout = NULL;
	m_pHead = NULL;
	m_pCentral = NULL;
	m_pPinBtn = NULL;

	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setContentsMargins(0, 0, 0, 0);
	m_pVLayout->setSpacing(0);

 	m_pHead = new QWidget(this);
 	m_pHead->setObjectName("PropertyPanelHead");
 	m_pHead->setFixedHeight(20);
 	m_pHead->setFixedWidth(216);
 	m_pHead->setGeometry(0,0,216,20);

	m_pTitle = new QLabel(m_pHead);
	m_pPinBtn = new QPushButton(m_pHead);
	m_pPinBtn->setObjectName("PinBtn");
	m_pPinBtn->setFixedHeight(16);
	m_pPinBtn->setFixedWidth(16);
	connect(m_pPinBtn, SIGNAL(clicked()), this, SIGNAL(pinBtnClicked()));


	m_pCentral = new QWidget(this);
	m_pCentral->setObjectName("PropertyPanelBody");

	m_pCentral->setFixedWidth(216);
	//m_pCentral->setFixedHeight(410-43);


	m_pBodyLayout = new QVBoxLayout(m_pCentral);
	m_pBodyLayout->setContentsMargins(0, 0, 0, 0);
	m_pBodyLayout->setSpacing(0);
	m_pCentral->setLayout(m_pBodyLayout);

	m_pVLayout->addWidget(m_pHead);
	m_pVLayout->addWidget(m_pCentral);

	this->setLayout(m_pVLayout);
}

PropertyPanel::~PropertyPanel()
{
	if (m_pTitle)
	{
		delete m_pTitle;
		m_pTitle = NULL;
	}

	if (m_pHead)
	{
		delete m_pHead;
		m_pHead = NULL;
	}
	if (m_pCentral)
	{
		delete m_pCentral;
		m_pCentral = NULL;
	}
	if (m_pVLayout)
	{
		delete m_pVLayout;
		m_pVLayout = NULL;
	}
}

void PropertyPanel::paintEvent( QPaintEvent *e )
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void PropertyPanel::resizeEvent( QResizeEvent *e )
{
	if (m_pCentral && m_pHead)
	{
		m_pCentral->setGeometry(0, m_pHead->height(), m_pCentral->width(), height() - m_pHead->height());
	}
	if (m_pHead && m_pPinBtn)
	{
		m_pPinBtn->setGeometry(m_pHead->width() - m_pPinBtn->width() - 10, 2, m_pPinBtn->width(), m_pPinBtn->height());
	}
}

void PropertyPanel::setCentralWidget( QWidget* p )
{
	if(!m_pCentral) return;
	m_pBodyLayout->addWidget(p);
}


void PropertyPanel::setPropertyPanelTitle( const QString& title )
{
	if (m_pTitle && m_pHead)
	{
		QFont ft;
		ft.setPointSize(8);
		ft.setWeight(13);
		ft.setBold(true);
		m_pTitle->setFont(ft);

		QPalette pa;
		pa.setColor(QPalette::WindowText,Qt::white);
		m_pTitle->setPalette(pa);

		m_pTitle->setText(title);
		m_pTitle->adjustSize();
		m_pTitle->setGeometry(5, m_pHead->height()/2 - m_pTitle->height()/2, m_pTitle->width(), m_pTitle->height());
		
		
	}
}