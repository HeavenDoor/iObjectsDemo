#include "stdafx.h"
#include "intelayers.h"

#include "..\\commom\\widgetrect.h"
#include <QtWidgets\QMessageBox>
#include <QMouseEvent>

InteLayers::InteLayers(QWidget* parent) : QWidget(parent)
{
	//m_pTabWidget = NULL;
	m_pHead = NULL;
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

	
	m_pTabWidget = new QWidget(this);
	m_pTabWidget->setObjectName("InteLayersBody");

	m_pTabWidget->setFixedWidth(216);
	m_pTabWidget->setFixedHeight(410-43);


	m_pVLayout->addWidget(m_pHead);
	m_pVLayout->addWidget(m_pTabWidget);

	

	m_pProAnima = new QPropertyAnimation(this, "geometry");
	connect(m_pProAnima, SIGNAL(finished()), this, SLOT(OnAnimationFinished()));

	m_pCollapseBtn = new QPushButton(this);
	m_pCollapseBtn->setObjectName("InteLayersCollapseBtn");
	m_pCollapseBtn->setFixedWidth(32);
	m_pCollapseBtn->setFixedHeight(32);
	m_pCollapseBtn->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
	m_pCollapseBtn->setAttribute(Qt::WA_TranslucentBackground);
	m_pCollapseBtn->setVisible(false);
	connect(m_pCollapseBtn, SIGNAL(clicked()), this, SLOT(OnInteLayersExpand()));
	
	qApp->installEventFilter(this);

	m_pBody = new QWidget(m_pTabWidget);
	m_pBody->setFixedHeight(m_pTabWidget->height() - 16);
	m_pBody->setFixedWidth(m_pTabWidget->width() - 16);
}

InteLayers::~InteLayers()
{

}

void InteLayers::addLayers( QWidget* layers )
{
	
	//layers->setGeometry(10,10, width() - 20, height() - 20);
	//QWidget
	m_pBody->setGeometry(m_pTabWidget->x() + 6, 5, m_pBody->width(), m_pBody->height());
	QVBoxLayout* p = new QVBoxLayout(m_pBody);

	p->setContentsMargins(0, 0, 0, 0);

	p->setSpacing(0);
	m_pBody->setLayout(p);
	p->addWidget(layers);
}

bool InteLayers::eventFilter(QObject* obj, QEvent* e)
{
	if(e->type() == QEvent::Move)
	{
		QMoveEvent* en = dynamic_cast<QMoveEvent*>(e);
		if(!en) return false;
		
		QPoint point = en->pos();;
		if (m_pCollapseBtn && m_pCollapseBtn->isVisible())
		{
			QRect re = WidgetRect::widgetGlobalRect(this);
			m_pCollapseBtn->setGeometry(re.right(), re.top(), m_pCollapseBtn->width(), m_pCollapseBtn->height());
		}
	}
	return false;
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
	if (m_pCollapseBtn && width() == 0)
	{
		QRect re = WidgetRect::widgetGlobalRect(this);
		m_pCollapseBtn->setGeometry(re.right(), re.top(), m_pCollapseBtn->width(), m_pCollapseBtn->height());
	}


	QWidget::resizeEvent(e);
}



void InteLayers::moveEvent( QMoveEvent* e)
{
	if (m_pCollapseBtn && m_pCollapseBtn->isVisible())
	{
		QRect re = WidgetRect::widgetGlobalRect(this);
		m_pCollapseBtn->setGeometry(re.right(), re.top(), m_pCollapseBtn->width(), m_pCollapseBtn->height());
	}
}

void InteLayers::OnInteLayersCollapse()
{
	if(m_pProAnima->state()==QPropertyAnimation::Running)
	{
		m_pProAnima->stop();
	}
	m_pProAnima->setDuration(timespan);
	QRect rec = this->geometry();//WidgetRect::widgetGlobalRect(this);
	m_width = rec.width();
	m_pProAnima->setStartValue(QRect(rec.left(), rec.top(),rec.width() , rec.height()));
	m_pProAnima->setEndValue(QRect(rec.left(), rec.top(), -1, rec.height()));
	m_pProAnima->setEasingCurve(QEasingCurve::OutSine);
	m_pProAnima->start();
}

void InteLayers::OnInteLayersExpand()
{

	if(m_pProAnima->state()==QPropertyAnimation::Running)
	{
		m_pProAnima->stop();
	}

	m_pProAnima->setDuration(timespan);
	QRect rec = this->geometry();//WidgetRect::widgetGlobalRect(this);
	m_pProAnima->setStartValue(QRect(rec.left(), rec.top(),rec.width() , rec.height()));
	m_pProAnima->setEndValue(QRect(rec.left(), rec.top(), m_width, rec.height()));
	m_pProAnima->setEasingCurve(QEasingCurve::OutSine);
	m_pProAnima->start();
	m_pCollapseBtn->hide();
}


void InteLayers::OnAnimationFinished()
{
	int m = this->width();
	if (!m_pCollapseBtn) return;

	if (!m_pCollapseBtn->isVisible() && width() == 0)
	{
		m_pCollapseBtn->show();
	}
	else
	{
		m_pCollapseBtn->hide();
	}

	emit refeshWindow();
}

 void InteLayers::setInteLayersWidth( int width )
 {
 	m_width = width;
 }
 
 void InteLayers::setInteLayersHeight( int height )
 {
 	m_height = height;
 }
 
 int InteLayers::InteLayersWidth()
 {
 	return m_width;
 	return width();
 }
 
 int InteLayers::InteLayersHeight()
 {
 	return m_height;
 }

