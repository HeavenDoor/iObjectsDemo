#include "stdafx.h"
#include "intelayers.h"

InteLayers::InteLayers(QWidget* parent) : QWidget(parent)
{
	setObjectName("InteLayers");

	m_pVLayout = new QVBoxLayout(this);
	m_pVLayout->setContentsMargins(0, 0, 0, 0);
	m_pVLayout->setSpacing(0);

	m_pHead = new QWidget(this);
	m_pHead->setObjectName("InteLayersHead");
	m_pHead->setFixedHeight(43);
	m_pHead->setFixedWidth(216);
	m_pHead->setGeometry(0,0,216,43);

	m_pCloseBtn = new QPushButton(m_pHead);
	m_pCloseBtn->setObjectName("CloseInteLayersBtn");
	m_pCloseBtn->setFixedHeight(19);
	m_pCloseBtn->setFixedWidth(19);
	m_pCloseBtn->setGeometry(m_pHead->width() - m_pCloseBtn->width() - 10, m_pHead->height()/2 - m_pCloseBtn->height()/2 , m_pCloseBtn->width(), m_pCloseBtn->height() );
	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnInteLayersCollapse()));

	
	m_pTabWidget = new TabWidget(this);
	m_pTabWidget->setObjectName("InteLayersTabWidget");

	m_pTabWidget->setFixedWidth(216);
	m_pTabWidget->setFixedHeight(400-43);


	m_pVLayout->addWidget(m_pHead);
	m_pVLayout->addWidget(m_pTabWidget);



	m_pProAnima = new QPropertyAnimation(this, "geometry");

	QFile file(":/intelayers.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}

InteLayers::~InteLayers()
{

}

QWidget* InteLayers::getWidget()
{
	return this;
}

void InteLayers::test()
{

}

void InteLayers::paintEvent( QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void InteLayers::resizeEvent( QResizeEvent* e)
{
	if (m_pCloseBtn && m_pHead)
	{
		m_pCloseBtn->setGeometry(m_pHead->width() - m_pCloseBtn->width() - 10, m_pHead->height()/2 - m_pCloseBtn->height()/2 , m_pCloseBtn->width(), m_pCloseBtn->height() );
	}
	QWidget::resizeEvent(e);
}

void InteLayers::OnInteLayersCollapse()
{
	if(m_pProAnima->state()==QPropertyAnimation::Running)
	{
		m_pProAnima->stop();
	}
	m_pProAnima->setDuration(timespan);
	QRect rec = this->geometry();//WidgetRect::widgetGlobalRect(this);
	m_pProAnima->setStartValue(QRect(rec.left(), rec.top(),rec.width() , rec.height()));
	m_pProAnima->setEndValue(QRect(rec.left(), rec.top(), -1, rec.height()));
	m_pProAnima->setEasingCurve(QEasingCurve::OutSine);
	m_pProAnima->start();
}
