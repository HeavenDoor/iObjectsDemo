#include "stdafx.h"
#include "mirrorpanel.h"

MirrorPanel::MirrorPanel(QWidget *parent) : QWidget(parent)
{
	m_pTabView = NULL;
	m_pTabBarPanel = NULL;

	m_pTabView = new TabView(this);
	m_pTabView->setProperty("Names", "FlowUp");

	m_pTabBarPanel = new TabBarPanel(this);
	m_pTabBarPanel->setFixedWidth(32);
	m_pTabBarPanel->addTabBarWidget(m_pTabView->getTabBar());
}

MirrorPanel::~MirrorPanel()
{
	if (m_pTabView)
	{
		delete m_pTabView;
		m_pTabView = NULL;
	}
	if (m_pTabBarPanel)
	{
		delete m_pTabBarPanel;
		m_pTabBarPanel = NULL;
	}
}

void MirrorPanel::resizeEvent( QResizeEvent *e )
{
	if (m_pTabView && m_pTabBarPanel)
	{
		m_pTabView->setGeometry(0, 0, width() - m_pTabBarPanel->width(), height());
		m_pTabBarPanel->setGeometry(width() - m_pTabBarPanel->width(), 0, m_pTabBarPanel->width(), height());
	}
}

void MirrorPanel::paintEvent( QPaintEvent *e )
{
// 	QStyleOption opt;
// 	opt.init(this);
// 	QPainter p(this);
// 	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
// 
 	QWidget::paintEvent(e);
}

void MirrorPanel::closeEvent( QCloseEvent *e )
{
	//this->hide();
}


TabView* MirrorPanel::getTabView()
{
	return m_pTabView;
}

TabBarPanel* MirrorPanel::getTabBarPanel()
{
	return m_pTabBarPanel;
}