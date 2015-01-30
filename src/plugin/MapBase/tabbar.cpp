#include "stdafx.h"
#include "tabbar.h"


TabBar::TabBar(QWidget *parent)	: QWidget(parent)
{
	setObjectName("Tabbar");
	setAttribute(Qt::WA_TranslucentBackground);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	
	m_pPrevBtn = NULL;
	m_pHlayout = new QHBoxLayout(this);
	m_pHlayout->setContentsMargins(0, 0, 0, 0);
	m_pHlayout->setSpacing(0);
}

TabBar::~TabBar()
{
	m_pTabBarList.clear();
}

void TabBar::insertTabbar( int index, QString tabName )
{
	QToolButton* pBtn = new QToolButton(this);
	pBtn->setFixedHeight(this->height());
	pBtn->setText(tabName);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));
	
	if (index > m_pTabBarList.length())
	{
		index = m_pTabBarList.length();
	}
	if (m_pTabBarList.length() == 0)
	{
		setVisible(false);
		pBtn->setObjectName("MapTabbarHead");
		pBtn->setProperty("HeadSelectedTabBar", 1);
	}
	if (m_pTabBarList.length() > 0)
	{
		setVisible(true);
	}

	if (index <= 0 && m_pTabBarList.length() >= 1)
	{
		pBtn->setObjectName("MapTabbarHead");		
		pBtn->setProperty("HeadSelectedTabBar", 1);
		if (m_pTabBarList.length() == 1 )
		{
			m_pTabBarList.at(0)->setObjectName("MapTabbarTail");
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("TailSelectedTabBar", 0);
		}
		else
		{
			m_pTabBarList.at(0)->setObjectName("empty");
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 0);
		}
		
	}
	if(index >= m_pTabBarList.length() && m_pTabBarList.length() >= 1)
	{
		m_pTabBarList.at(0)->setObjectName("MapTabbarTail");
		pBtn->setProperty("TailSelectedTabBar", 0);
		if (m_pTabBarList.length() == 1 )
		{
			m_pTabBarList.at(0)->setObjectName("MapTabbarHead");
			m_pTabBarList.at(0)->setProperty("TailSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
		}
		else
		{
			m_pTabBarList.at(m_pTabBarList.length() - 1)->setObjectName("empty");
			m_pTabBarList.at(m_pTabBarList.length() - 1)->setProperty("TailSelectedTabBar", 5);
			m_pTabBarList.at(m_pTabBarList.length() - 1)->setProperty("SelectedTabBar", 0);
		}
	}
	if (m_pTabBarList.length() > 1 && index != 0 && index < m_pTabBarList.length())
	{
		pBtn->setProperty("SelectedTabBar", 0);
	}
	
	m_pTabBarList.insert(index, pBtn);
	m_pHlayout->insertWidget(index, pBtn);


}


void TabBar::setCurrentIndex( int index )
{
	if (m_pTabBarList.length() > 1 && index > 0 && index < m_pTabBarList.length() - 1)
	{
		for each (QToolButton* pbtn in m_pTabBarList)
		{
			if (m_pTabBarList.indexOf(pbtn) == 0 || m_pTabBarList.indexOf(pbtn) == m_pTabBarList.length() - 1)
			{
				continue;
			}
			pbtn->setProperty("SelectedTabBar", "0");
		}
		m_pTabBarList.at(index)->setProperty("SelectedTabBar", "1");
	}

	if (index <= 0)
	{
		index = 0;
		m_pTabBarList.at(index)->setProperty("HeadSelectedTabBar", "1");
	}
	if (index >= m_pTabBarList.length() - 1)
	{
		index = m_pTabBarList.length() - 1;
		m_pTabBarList.at(index)->setProperty("TailSelectedTabBar", "1");
	}

	m_pPrevBtn = m_pTabBarList.at(index);

	QFile file(":/tabbar.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}


void TabBar::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}


void TabBar::resizeEvent( QResizeEvent* )
{
	for each (QToolButton* pbtn in m_pTabBarList)
	{
		pbtn->setFixedWidth(width()/tabCount());
	}
}


void TabBar::OnTabButtonClicked()
{
	QToolButton* pTBtn = static_cast<QToolButton*>(sender());
	if(!pTBtn) return;
	if (pTBtn == m_pPrevBtn) return;
	

	int index = m_pTabBarList.indexOf(pTBtn);
	int previndex = m_pTabBarList.indexOf(m_pPrevBtn);


	int a = m_pTabBarList.at(0)->property("HeadSelectedTabBar").toInt();
	int b = m_pTabBarList.at(1)->property("TailSelectedTabBar").toInt();
	if (index==0)
	{
		pTBtn->setProperty("HeadSelectedTabBar", "1");
	}
	else if (index == m_pTabBarList.length() - 1)
	{
		pTBtn->setProperty("TailSelectedTabBar", "1");
	}
	else
	{
		pTBtn->setProperty("SelectedTabBar", "1");
	}

	if (previndex <= 0)
	{
		m_pPrevBtn->setProperty("HeadSelectedTabBar", "0");
	}
	else if(previndex == m_pTabBarList.length() - 1)
	{
		m_pPrevBtn->setProperty("TailSelectedTabBar", "0");
	}
	else
	{
		m_pPrevBtn->setProperty("SelectedTabBar", "0");
	}
	m_pPrevBtn = pTBtn;

	emit changeDimension(index);

	QFile file(":/tabbar.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();

}

int TabBar::tabCount()
{
	return m_pTabBarList.length();
}

