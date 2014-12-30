#include "stdafx.h"
#include "tabbar.h"


TabBar::TabBar(QWidget *parent)	: QWidget(parent)
{
	setObjectName("Tabbar");
	setAttribute(Qt::WA_TranslucentBackground);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	

	m_pHlayout = new QHBoxLayout(this);
	m_pHlayout->setContentsMargins(0, 0, 0, 0);
	m_pHlayout->setSpacing(0);

	m_pTwoBtn = new QToolButton(this);
	m_pTwoBtn->setObjectName("TwoBtn");
	m_pTwoBtn->setFixedHeight(this->height());
	m_pTwoBtn->setFixedWidth(this->width()/2);
	m_pTwoBtn->setProperty("twoselected", true);
	m_pTwoBtn->setPalette(pa);
	
	m_pTwoBtn->setText(QStringLiteral("¶þÎ¬"));
	
	connect(m_pTwoBtn, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));

	m_pThreeBtn = new QToolButton(this);
	m_pThreeBtn->setObjectName("ThreeBtn");
	m_pThreeBtn->setFixedHeight(this->height());
	m_pThreeBtn->setFixedWidth(this->width()/2);
	m_pThreeBtn->setProperty("threeselected", false);
	m_pThreeBtn->setPalette(pa);
	m_pThreeBtn->setText(QStringLiteral("ÈýÎ¬"));
	
	connect(m_pThreeBtn, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));

	m_pHlayout->addWidget(m_pTwoBtn);
	m_pHlayout->addWidget(m_pThreeBtn);
}

TabBar::~TabBar()
{

}


void TabBar::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void TabBar::OnTabButtonClicked()
{
	QToolButton* pTBtn = static_cast<QToolButton*>(sender());
	if(!pTBtn) return;
	if (pTBtn->objectName() == "TwoBtn")
	{
		if (!pTBtn->property("twoselected").toBool())
		{
			pTBtn->setProperty("twoselected", true);
			m_pThreeBtn->setProperty("threeselected", false);
			emit changeDimension(true);
		}
		else
		{
			return;
		}

	}
	else
	{
		if (!pTBtn->property("threeselected").toBool())
		{
			pTBtn->setProperty("threeselected", true);
			m_pTwoBtn->setProperty("twoselected", false);
			emit changeDimension(false);
		}
		else
		{
			return;
		}
	}

	QFile file(":/tabbar.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	file.close();

	m_pTwoBtn->setStyleSheet(style);
	m_pThreeBtn->setStyleSheet(style);
}
