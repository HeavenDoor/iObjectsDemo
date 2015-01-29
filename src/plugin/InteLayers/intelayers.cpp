#include "stdafx.h"
#include "intelayers.h"

#include "..\\..\\commom\widgetrect.h"
#include <QtWidgets\QMessageBox>
#include <QMouseEvent>

InteLayers::InteLayers(QWidget* parent) : QWidget(parent)
{
	m_pTabWidget = NULL;
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

	
	m_pTabWidget = new TabWidget(this);
	m_pTabWidget->setObjectName("InteLayersTabWidget");

	m_pTabWidget->setFixedWidth(216);
	m_pTabWidget->setFixedHeight(400-43);


	m_pVLayout->addWidget(m_pHead);
	m_pVLayout->addWidget(m_pTabWidget);

	

	m_pProAnima = new QPropertyAnimation(this, "geometry");
	connect(m_pProAnima, SIGNAL(finished()), this, SLOT(OnAnimationFinished()));

	m_pCollapseBtn = new QPushButton(this);
	m_pCollapseBtn->setObjectName("CollapseBtn");
	m_pCollapseBtn->setFixedWidth(32);
	m_pCollapseBtn->setFixedHeight(32);
	m_pCollapseBtn->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);
	m_pCollapseBtn->setAttribute(Qt::WA_TranslucentBackground);
	m_pCollapseBtn->setVisible(false);
	connect(m_pCollapseBtn, SIGNAL(clicked()), this, SLOT(OnInteLayersExpand()));
	
	qApp->installEventFilter(this);

	QFile file(":/intelayers.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();


	
}

InteLayers::~InteLayers()
{

}

void InteLayers::addTabPage( QVector<QString> vec )
{
	if (!m_pTabWidget) return;
	m_pTabWidget->addTabPage(vec);

	QFile file(":/intelayers.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}


// QWidget* InteLayers::getWidget()
// {
// 	return this;
// }

void InteLayers::test()
{

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
	if (m_pCollapseBtn)
	{
		QRect re = WidgetRect::widgetGlobalRect(this);
		m_pCollapseBtn->setGeometry(re.right(), re.top(), m_pCollapseBtn->width(), m_pCollapseBtn->height());
	}
	
	if (m_pCloseBtn && m_pHead)
	{
		m_pCloseBtn->setGeometry(m_pHead->width() - m_pCloseBtn->width() - 10, m_pHead->height()/2 - m_pCloseBtn->height()/2 , m_pCloseBtn->width(), m_pCloseBtn->height() );
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



QObject* InteLayers::getObject()
{
	return this;
}

void InteLayers::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void InteLayers::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void InteLayers::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void InteLayers::showPlugin()
{
	this->show();
}

void InteLayers::raisePlugin()
{
	this->raise();
}

void InteLayers::resizePlugin(int ax, int ay, int aw, int ah)
{
	if (width() == 0)
	{
		setGeometry(ax, ay, 0, ah);
	}
	else
	{
		setGeometry(ax, ay, aw, ah);
	}
	if (m_pCollapseBtn)
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

void InteLayers::lowerPlugin()
{
	lower();
}

void InteLayers::setPluginWidth( int width )
{
	m_width = width;
	//setFixedWidth(width); // Animation will mot effect if you set this
}

void InteLayers::setPluginHeight( int height )
{
	m_height = height;
	//setFixedHeight(height);
}

int InteLayers::pluginWidth()
{
	return m_width;
	return width();
}

int InteLayers::pluginHeight()
{
	return m_height;
}

