#include "stdafx.h"
#include "title.h"

Title::Title(QWidget *parent) : QWidget(parent)
{
	setObjectName("Title");
	//setAttribute(Qt::WA_TranslucentBackground);
	QRect rec = parent->rect();
	setGeometry(parent->width()/2 - width()/2, 0, 530, 85);
	m_pCollapseBtn = new QPushButton(this);
	m_pCollapseBtn->setObjectName("CollapseBtn");
	m_pCollapseBtn->setFixedWidth(32);
	m_pCollapseBtn->setFixedHeight(32);
	//m_pCollapseBtn->setGeometry(width() - m_pCollapseBtn->width() - 5 , 5, 32, 32);
	m_pCollapseBtn->setGeometry(width() - m_pCollapseBtn->width() - 5 , 5, width(), height());
	//connect(m_pCollapseBtn, SIGNAL(clicked()), this, SIGNAL(collapse()));
	connect(m_pCollapseBtn, SIGNAL(clicked()), this, SLOT(packupTitle()));

	m_pProAnima = new QPropertyAnimation(this, "geometry");
	connect(m_pProAnima, SIGNAL(finished()), this, SIGNAL(collapse()));

	QLabel* l = new QLabel(this);
	l->setGeometry(10,5,200,20);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	l->setPalette(pa);

	//l->setTextFormat()
	l->setText(QStringLiteral("GTHFDSDGSDHGDHXB (¸ßÁÁÉ«)"));
	l->setWindowOpacity(1);
}

Title::~Title()
{

}

void Title::paintEvent( QPaintEvent* e )
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void Title::resizeEvent( QResizeEvent * e)
{
	if (m_pCollapseBtn)
	{
		m_pCollapseBtn->setGeometry(width() - m_pCollapseBtn->width() - 5 , 5, width(), height());
	}
	//QWidget::resizeEvent(e);
}

void Title::tt()
{
	int m = 0;
}

void Title::expandTitle()
{
	if(m_pProAnima->state()==QPropertyAnimation::Running)
	{
		m_pProAnima->stop();
	}
	m_pProAnima->setDuration(timespan);
	QRect rec = this->geometry();
	m_pProAnima->setStartValue(QRect(rec.left(), rec.top(), rec.width() , 0));
	m_pProAnima->setEndValue(QRect(rec.left(), rec.top(), rec.width(), 85));//(QRect(width()-w_widget,height()-h_widget*2,w_widget,h_widget));
	m_pProAnima->setEasingCurve(QEasingCurve::OutSine);//QEasingCurve::Type()
	m_pProAnima->start();
}

void Title::packupTitle()
{
	if(m_pProAnima->state()==QPropertyAnimation::Running)
	{
		m_pProAnima->stop();
	}
	m_pProAnima->setDuration(timespan);
	QRect rec = this->geometry();//WidgetRect::widgetGlobalRect(this);
	m_pProAnima->setStartValue(QRect(rec.left(), rec.top(),rec.width() , rec.height()));
	m_pProAnima->setEndValue(QRect(rec.left(), rec.top()-1, rec.width(), 1));
	m_pProAnima->setEasingCurve(QEasingCurve::OutSine);
	m_pProAnima->start();
}

void Title::OnAnimationFinished()
{
}
