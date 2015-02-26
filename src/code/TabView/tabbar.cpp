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

	setAcceptDrops(true);
}

TabBar::~TabBar()
{
	m_pTabBarList.clear();
}

void TabBar::insertTabbar( int index, QString tabName )
{
	TabItem* pBtn = new TabItem(this);
	pBtn->setAcceptDrops(true);
	//pBtn->setDragEnabled(true)
	pBtn->setFixedHeight(this->height());
	pBtn->setText(tabName);
	connect(pBtn, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));
	

	int previndex = -10;
	if (m_pTabBarList.length() != 0)
	{
		previndex = m_pTabBarList.indexOf(m_pPrevBtn);
	}
	

	if (index > m_pTabBarList.length())
	{
		index = m_pTabBarList.length();
	}

	if (m_pTabBarList.length() == 0)
	{
		setVisible(false);
		//pBtn->setObjectName("MapTabbarHead");
		pBtn->setProperty("HeadSelectedTabBar", 1);
	}

	if (m_pTabBarList.length() > 0)
	{
		setVisible(true);
	}

	if (index <= 0 && m_pTabBarList.length() >= 1)  // 在头部插入Tab
	{	
		pBtn->setProperty("HeadSelectedTabBar", 1);
		if (m_pTabBarList.length() == 1 )
		{
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("TailSelectedTabBar", 0);
		}
		else
		{
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 0);

			if (previndex == m_pTabBarList.length() - 1)
			{
				m_pPrevBtn->setProperty("TailSelectedTabBar", 0);
			}
			else
			{
				m_pPrevBtn->setProperty("SelectedTabBar", 0);
			}
		}
		
	}
	if(index >= m_pTabBarList.length() && m_pTabBarList.length() >= 1)  // 在尾部插入Tab
	{
		pBtn->setProperty("TailSelectedTabBar", 1);
		if (m_pTabBarList.length() == 1 )
		{
			m_pTabBarList.at(0)->setProperty("TailSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 0);
		}
		else
		{
			m_pTabBarList.at(m_pTabBarList.length() - 1)->setProperty("TailSelectedTabBar", 5);
			m_pTabBarList.at(m_pTabBarList.length() - 1)->setProperty("SelectedTabBar", 0);

			if (previndex == 0)
			{
				m_pPrevBtn->setProperty("HeadSelectedTabBar", 0);
			}
			else
			{
				m_pPrevBtn->setProperty("SelectedTabBar", 0);
			}
		}
	}
	if (m_pTabBarList.length() > 1 && index != 0 && index < m_pTabBarList.length())
	{
		pBtn->setProperty("SelectedTabBar", 1);
		if (previndex == 0)
		{
			m_pPrevBtn->setProperty("HeadSelectedTabBar", 0);
		}
		else if (previndex == m_pTabBarList.length() - 1)
		{
			m_pPrevBtn->setProperty("TailSelectedTabBar", 0);
		}
		else
		{
			m_pPrevBtn->setProperty("SelectedTabBar", 0);
		}
	}
	m_pPrevBtn = pBtn;
	m_pTabBarList.insert(index, pBtn);
	m_pHlayout->insertWidget(index, pBtn);


}


void TabBar::removeTabbar( int index )
{
	if (index < 0 || index >= m_pTabBarList.length()) return;
	int origlength = m_pTabBarList.length();

	QToolButton* p = m_pTabBarList.at(index);
	m_pTabBarList.removeAt(index);
	m_pHlayout->removeWidget(p);



	if (m_pTabBarList.length() == 1)
	{
		setVisible(false);
		m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
		m_pPrevBtn = m_pTabBarList.at(0);
	}
	else
	{
		if (index == 0)
		{
			m_pPrevBtn = m_pTabBarList.at(0);
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", "5");
			
		}
		else if(index = origlength - 1)
		{
			m_pPrevBtn = m_pTabBarList.at(0);
			m_pTabBarList.last()->setProperty("TailSelectedTabBar", 0);
			m_pTabBarList.last()->setProperty("SelectedTabBar", 0);
			//m_pTabBarList.at(0)->setProperty("SelectedTabBar", "5");
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", "1");
		}
		else
		{
			m_pPrevBtn = m_pTabBarList.at(0);

			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", "1");
		}

		emit changeIndex(0);
		
	}




	delete p;
	p = NULL;

	QFile file(":/tabbar.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}



void TabBar::setCurrentIndex( int index )
{
	if (!m_pPrevBtn)
	{
		QMessageBox::warning(NULL, "setCurrentIndex", "prevbtn enpty");
		return;
	}
	int previndex = m_pTabBarList.indexOf(m_pPrevBtn);
	if (previndex == index) return;



	if (index <= 0)  // 头
	{
		index = 0;
		m_pTabBarList.at(index)->setProperty("HeadSelectedTabBar", "1");

		if (previndex == m_pTabBarList.length() - 1)  // 尾巴
		{
			m_pPrevBtn->setProperty("TailSelectedTabBar", "0");
		}
		else // 中间
		{
			m_pPrevBtn->setProperty("SelectedTabBar", "0");
		}
	}

	if (index >= m_pTabBarList.length() - 1) // 尾巴
	{
		index = m_pTabBarList.length() - 1;
		m_pTabBarList.at(index)->setProperty("TailSelectedTabBar", "1");
		if (previndex == 0) // 头
		{
			m_pPrevBtn->setProperty("HeadSelectedTabBar", "0");
		}
		else  // 中间
		{
			m_pPrevBtn->setProperty("SelectedTabBar", "0");
		}
	}

	if (m_pTabBarList.length() > 1 && index > 0 && index < m_pTabBarList.length() - 1)
	{
// 		for each (QToolButton* pbtn in m_pTabBarList)
// 		{
// 			if (m_pTabBarList.indexOf(pbtn) == 0 || m_pTabBarList.indexOf(pbtn) == m_pTabBarList.length() - 1)
// 			{
// 				continue;
// 			}
// 			pbtn->setProperty("SelectedTabBar", "0");
// 		}
		m_pTabBarList.at(index)->setProperty("SelectedTabBar", "1");

		if (previndex == 0)
		{
			m_pPrevBtn->setProperty("HeadSelectedTabBar", "0");
		}
		else if (previndex == m_pTabBarList.length() - 1)
		{
			m_pPrevBtn->setProperty("TailSelectedTabBar", "0");
		}
		else
		{
			m_pPrevBtn->setProperty("SelectedTabBar", "0");
		}
	}

	m_pPrevBtn = m_pTabBarList.at(index);

// 	QFile file(":/tabbar.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 	this->setStyleSheet(style);
// 	file.close();
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
	TabItem* pTBtn = static_cast<TabItem*>(sender());
	if(!pTBtn) return;
	if (!m_pPrevBtn)
	{
		QMessageBox::warning(NULL, "OnTabButtonClicked", "prevbtn enpty");
		return;
	}
	if (pTBtn == m_pPrevBtn) return;
	

	int index = m_pTabBarList.indexOf(pTBtn);
	setCurrentIndex(index);
	/*int previndex = m_pTabBarList.indexOf(m_pPrevBtn);
	

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
		if(m_pPrevBtn) m_pPrevBtn->setProperty("HeadSelectedTabBar", "0");
	}
	else if(previndex == m_pTabBarList.length() - 1)
	{
		if(m_pPrevBtn) m_pPrevBtn->setProperty("TailSelectedTabBar", "0");
	}
	else
	{
		if(m_pPrevBtn) m_pPrevBtn->setProperty("SelectedTabBar", "0");
	}*/

	m_pPrevBtn = pTBtn;
	
	emit changeIndex(index);

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

void TabBar::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
	{
		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		} 
		else 
		{
			event->acceptProposedAction();
		}
	} 
	else 
	{
		event->ignore();
	}
}

void TabBar::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
	{
		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		} 
		else 
		{
			event->acceptProposedAction();
		}
	} 
	else 
	{
		event->ignore();
	}
}

void TabBar::dropEvent(QDropEvent *event)
{
	/*if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
	{
		QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
		QDataStream dataStream(&itemData, QIODevice::ReadOnly);

		QPixmap pixmap;
		QPoint offset;
		dataStream >> pixmap >> offset;

		QLabel *newIcon = new QLabel(this);
		newIcon->setPixmap(pixmap);
		newIcon->move(event->pos() - offset);
		newIcon->show();
		newIcon->setAttribute(Qt::WA_DeleteOnClose);

		if (event->source() == this) 
		{
			event->setDropAction(Qt::MoveAction);
			event->accept();
		} 
		else 
		{
			event->acceptProposedAction();
		}
	} 
	else 
	{
		event->ignore();
	}*/
}


void TabBar::mousePressEvent(QMouseEvent *event)
{
	TabItem *child = static_cast<TabItem*>(childAt(event->pos()));
	if (!child)
		return;
	QString ss = child->text();
	

 	QPixmap pixmap = child->getTabItemPixmap();
// 
	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	dataStream << pixmap << QPoint(event->pos() - child->pos());
// 	//! [1]
// 
// 	//! [2]
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("application/x-dnditemdata", itemData);
	//! [2]

	//! [3]
	QDrag *drag = new QDrag(this);
 	drag->setMimeData(mimeData);
 	drag->setPixmap(pixmap);
	drag->setHotSpot(event->pos() - child->pos());
	//! [3]

	QPixmap tempPixmap = pixmap;
	QPainter painter;
	painter.begin(&tempPixmap);
	painter.fillRect(pixmap.rect(), QColor(255,255,255,255));
	painter.end();
// 
 	//child->setPixmap(tempPixmap);

	if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) 
	{
		child->close();
	} 
	else 
	{
		child->show();
		//child->setPixmap(pixmap);
	}
	QWidget::mousePressEvent(event);
}

void TabBar::dragLeaveEvent( QDragLeaveEvent * event ) 
{

}
