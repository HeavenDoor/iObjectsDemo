#include "stdafx.h"
#include "tabbarpanel.h"

TabBarPanel::TabBarPanel(QWidget *parent) : QWidget(parent)
{
	m_pMainLayout = NULL;
	m_pTabLayout = NULL;
	m_pTigerLayout = NULL;


	m_pMainLayout = new QVBoxLayout();
	m_pMainLayout->setAlignment(Qt::AlignTop);
	m_pMainLayout->setContentsMargins(0, 0, 0, 0);
	m_pMainLayout->setSpacing(0);

	m_pTabLayout = new QVBoxLayout();
	m_pTabLayout->setAlignment(Qt::AlignTop);
	m_pTabLayout->setContentsMargins(0, 0, 0, 0);
	m_pTabLayout->setSpacing(0);


	m_pTigerLayout = new QVBoxLayout();
	m_pTigerLayout->setAlignment(Qt::AlignTop);
	m_pTigerLayout->setContentsMargins(0, 0, 0, 0);
	m_pTigerLayout->setSpacing(0);

	m_pMainLayout->addLayout(m_pTabLayout);
	m_pMainLayout->addSpacing(6);
	m_pMainLayout->addLayout(m_pTigerLayout);

	setLayout(m_pMainLayout);
}

TabBarPanel::~TabBarPanel()
{
	if (!m_pTabLayout)
	{
		delete m_pTabLayout;
		m_pTabLayout = NULL;
	}
	if (!m_pTigerLayout)
	{
		delete m_pTigerLayout;
		m_pTigerLayout = NULL;
	}
	if (!m_pMainLayout)
	{
		delete m_pMainLayout;
		m_pMainLayout = NULL;
	}
}

void TabBarPanel::addTabBarWidget(QWidget* w)
{
	if(!m_pMainLayout || !m_pTabLayout) return;
	m_pTabLayout->addWidget(w);
}

void TabBarPanel::addTrigerWidget(QWidget* w)
{
	if(!m_pMainLayout || !m_pTigerLayout) return;
	m_pTigerLayout->addWidget(w);
}