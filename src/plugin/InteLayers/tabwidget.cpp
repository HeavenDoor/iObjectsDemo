#include "stdafx.h"
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) : QWidget(parent)
{
	setObjectName("TabWidget");
	

	m_pTabBar = new QWidget(this);
	m_pTabBar->setObjectName("InteLayersTabBar");
	m_pTabBar->setFixedHeight(40);

	m_pHLayout = new QHBoxLayout(m_pTabBar);
	//m_pHLayout->setAlignment(Qt::AlignHorizontal_Mask);
	//m_pHLayout->setAlignment(Qt::AlignVCenter);
	m_pHLayout->setContentsMargins(0, 0, 0, 0);
	m_pHLayout->setSpacing(2);


	m_pBtn1 = new QToolButton(m_pTabBar);
	m_pBtn1->setObjectName("pBtn1");
	m_pBtn1->setFixedWidth(32);
	m_pBtn1->setFixedHeight(32);
	m_pBtn1->setProperty("ShowTabs_1", true);
	connect(m_pBtn1, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));

	m_pBtn2 = new QToolButton(m_pTabBar);
	m_pBtn2->setObjectName("pBtn2");
	m_pBtn2->setFixedWidth(32);
	m_pBtn2->setFixedHeight(32);
	m_pBtn2->setProperty("ShowTabs_2", false);
	connect(m_pBtn2, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));

	m_pBtn3 = new QToolButton(m_pTabBar);
	m_pBtn3->setObjectName("pBtn3");
	m_pBtn3->setFixedWidth(32);
	m_pBtn3->setFixedHeight(32);
	m_pBtn3->setProperty("ShowTabs_3", false);
	connect(m_pBtn3, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));

	m_pHLayout->addWidget(m_pBtn1);
	m_pHLayout->addWidget(m_pBtn2);
	m_pHLayout->addWidget(m_pBtn3);





	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setObjectName("InteLayersTabWidget");




	//////////////////////////////////////////////////////////////////////////
	m_pOne = new QWidget(m_pTabWidget);

	m_pVLayout = new QVBoxLayout(m_pOne);
	//m_pVLayout->setContentsMargins(0, 0, 0, 0);
	m_pVLayout->setSpacing(2);
	m_pVLayout->setAlignment(Qt::AlignTop);

	m_a = new QWidget(m_pOne);
	m_a->setObjectName("m_a");
	m_a->setFixedHeight(40);
	m_b = new QWidget(m_pOne);
	m_b->setObjectName("m_b");
	m_b->setFixedHeight(40);

	m_c = new QWidget(m_pOne);
	m_c->setObjectName("m_c");
	m_c->setFixedHeight(40);

	m_d = new QWidget(m_pOne);
	m_d->setObjectName("m_d");
	m_d->setFixedHeight(40);
	m_e = new QWidget(m_pOne);
	m_e->setObjectName("m_e");
	m_e->setFixedHeight(40);

	m_f = new QWidget(m_pOne);
	m_f->setObjectName("m_f");
	m_f->setFixedHeight(40);
	//m_pTabWidget->setAttribute(Qt::WA_TranslucentBackground);

	m_pVLayout->addWidget(m_a);
	m_pVLayout->addWidget(m_b);
	m_pVLayout->addWidget(m_c);
	m_pVLayout->addWidget(m_d);
	m_pVLayout->addWidget(m_e);
	m_pVLayout->addWidget(m_f);
	//////////////////////////////////////////////////////////////////////////
	m_pTwo = new QWidget(m_pTabWidget);
	m_pVLayout2 = new QVBoxLayout(m_pTwo);
	//m_pVLayout->setContentsMargins(0, 0, 0, 0);
	m_pVLayout2->setSpacing(2);
	m_pVLayout2->setAlignment(Qt::AlignTop);
	m_g = new QWidget(m_pTwo);
	m_g->setObjectName("m_g");
	m_g->setFixedHeight(40);
	m_h = new QWidget(m_pTwo);
	m_h->setObjectName("m_h");
	m_h->setFixedHeight(40);
 	m_i = new QWidget(m_pTwo);
 	m_i->setObjectName("m_i");
 	m_i->setFixedHeight(40);
	m_j = new QWidget(m_pTwo);
	m_j->setObjectName("m_j");
	m_j->setFixedHeight(40);

	m_pVLayout2->addWidget(m_g);
	m_pVLayout2->addWidget(m_h);
	m_pVLayout2->addWidget(m_i);
	m_pVLayout2->addWidget(m_j);

	//////////////////////////////////////////////////////////////////////////
	m_pThree = new QWidget(m_pTabWidget);
	m_pVLayout3 = new QVBoxLayout(m_pThree);
	//m_pVLayout->setContentsMargins(0, 0, 0, 0);
	m_pVLayout3->setSpacing(2);
	m_pVLayout3->setAlignment(Qt::AlignTop);
	m_k = new QWidget(m_pThree);
	m_k->setObjectName("m_k");
	m_k->setFixedHeight(40);
	m_l = new QWidget(m_pThree);
	m_l->setObjectName("m_l");
	m_l->setFixedHeight(40);
	m_pVLayout3->addWidget(m_k);
	m_pVLayout3->addWidget(m_l);



	m_pTabWidget->addTab(m_pOne, "one");
	m_pTabWidget->addTab(m_pTwo, "two");
	m_pTabWidget->addTab(m_pThree, "three");

	m_pTabWidget->tabBar()->setVisible(false);
}

TabWidget::~TabWidget()
{

}

void TabWidget::paintEvent( QPaintEvent * e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void TabWidget::resizeEvent( QResizeEvent* e)
{
	if (m_pTabBar)
	{
		m_pTabBar->setGeometry(4, 2, width()-10, m_pTabBar->height());
	}

	if (m_pTabWidget)
	{
		m_pTabWidget->setGeometry(7, m_pTabBar->height(), width() - 18, height() - m_pTabBar->height() - 25);
 		if (m_pOne)
 		{
 			m_pOne->setGeometry(0,0,m_pTabWidget->width(), m_pTabWidget->height());
 		}
		if (m_pTwo)
		{
			m_pTwo->setGeometry(0,0,m_pTabWidget->width(), m_pTabWidget->height());
		}
 		if (m_pThree)
 		{
 			m_pThree->setGeometry(0,0,m_pTabWidget->width(), m_pTabWidget->height());
 		}
	}
	QWidget::resizeEvent(e);
}

void TabWidget::OnTabButtonClicked()
{

	QToolButton* pTBtn = static_cast<QToolButton*>(sender());
	if(!pTBtn) return;
	if (pTBtn->objectName() == "pBtn1")
	{
		if (!pTBtn->property("ShowTabs_1").toBool())
		{
			pTBtn->setProperty("ShowTabs_1", true);
			m_pBtn2->setProperty("ShowTabs_2", false);
			m_pBtn3->setProperty("ShowTabs_3", false);
			m_pTabWidget->setCurrentIndex(0);
		}
		else
		{
			return;
		}

	}
	else if (pTBtn->objectName() == "pBtn2")
	{
		if (!pTBtn->property("ShowTabs_2").toBool())
		{
			pTBtn->setProperty("ShowTabs_2", true);
			m_pBtn1->setProperty("ShowTabs_1", false);
			m_pBtn3->setProperty("ShowTabs_3", false);
			m_pTabWidget->setCurrentIndex(1);
		}
		else
		{
			return;
		}
	}
	else
	{
		if (!pTBtn->property("ShowTabs_3").toBool())
		{
			pTBtn->setProperty("ShowTabs_3", true);
			m_pBtn1->setProperty("ShowTabs_1", false);
			m_pBtn2->setProperty("ShowTabs_2", false);
			m_pTabWidget->setCurrentIndex(2);
		}
		else
		{
			return;
		}
	}

	QFile file(":/intelayerstab.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	file.close();

	m_pBtn1->setStyleSheet(style);
	m_pBtn2->setStyleSheet(style);
	m_pBtn3->setStyleSheet(style);
}
