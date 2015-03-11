#include "stdafx.h"
#include "tabbar.h"


TabBar::TabBar(QWidget *parent)	: QWidget(parent)
{
	setObjectName("Tabbar");
	setMouseTracking(true);
	//this->setAttribute(Qt::WA_PaintOutsidePaintEvent)
	setAttribute(Qt::WA_TranslucentBackground);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	
	m_pPrevBtn = NULL;
	m_pVlayout = new QVBoxLayout(this);
	m_pVlayout->setContentsMargins(0, 0, 0, 0);
	m_pVlayout->setSpacing(0);


	painter = new QPainter(this);
	setAcceptDrops(true);
	press = false;
	move = false;
// 	setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
// 	setMovable(true);
	qApp->installEventFilter(this);

	
}

TabBar::~TabBar()
{
	m_pTabBarList.clear();
}

void TabBar::insertTabbar( int index, QString tabName )
{
	TabItem* pBtn = new TabItem(tabName, this);
	pBtn->setAcceptDrops(true);
	//pBtn->setDragEnabled(true)
	pBtn->setFixedWidth(this->width());

	int m = this->width();
	pBtn->setFixedHeight(81);
	//pBtn->setText(tabName);

	connect(pBtn, SIGNAL(clicked()), this, SLOT(OnTabButtonClicked()));
	connect(pBtn, SIGNAL(flowUp()), this, SLOT(OnFlowUp()));
	pBtn->setSelected();
	foreach (TabItem* item, m_pTabBarList)
	{
		item->setDeselected();
	}
/*	int previndex = -10;
	if (m_pTabBarList.length() != 0)
	{
		previndex = m_pTabBarList.indexOf(m_pPrevBtn);
	}

	//pBtn->sele
	

	if (index > m_pTabBarList.length())
	{
		index = m_pTabBarList.length();
	}

	if (m_pTabBarList.length() == 0)
	{
		//setVisible(false);
		//pBtn->setObjectName("MapTabbarHead");
		//pBtn->setProperty("HeadSelectedTabBar", 1);
		pBtn->setProperty("SelectedTabBar", 1);
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
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("TailSelectedTabBar", 0);
		}
		else
		{
			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 5);
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 0);

			if (previndex == m_pTabBarList.length() - 1)
			{
				m_pPrevBtn->setProperty("TailSelectedTabBar", 0);
				m_pPrevBtn->setProperty("SelectedTabBar", 5);
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
			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 5);
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
	}*/
	m_pPrevBtn = pBtn;
	m_pTabBarList.insert(index, pBtn);
	m_pVlayout->insertWidget(index, pBtn);

// 	QFile file(":/tabbar.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 	this->setStyleSheet(style);
// 	file.close();
}

void TabBar::removeTabbar( int index )
{
	if (index < 0 || index >= m_pTabBarList.length()) return;
	int origlength = m_pTabBarList.length();

	TabItem* p = m_pTabBarList.at(index);
	m_pTabBarList.removeAt(index);
	m_pVlayout->removeWidget(p);

	if (m_pTabBarList.length() == 0)
	{
		m_pPrevBtn = NULL;
		return;
	}

	if (m_pTabBarList.length() == 1)
	{
		//setVisible(false);
		//m_pTabBarList.at(0)->setProperty("SelectedTabBar", 1);
		m_pPrevBtn = m_pTabBarList.at(0);
	}
	else
	{
		if (index == 0)
		{
			m_pPrevBtn = m_pTabBarList.at(0);
// 			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
// 			m_pTabBarList.at(0)->setProperty("SelectedTabBar", 5);
			
		}
		else if(index = origlength - 1)
		{
			m_pPrevBtn = m_pTabBarList.at(0);
// 			m_pTabBarList.last()->setProperty("TailSelectedTabBar", 0);
// 			m_pTabBarList.last()->setProperty("SelectedTabBar", 5);
// 			//m_pTabBarList.at(0)->setProperty("SelectedTabBar", "5");
// 			m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
		}
		else
		{
			m_pPrevBtn = m_pTabBarList.at(0);

			//m_pTabBarList.at(0)->setProperty("HeadSelectedTabBar", 1);
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

	
	for (int i = 0; i < m_pTabBarList.length(); i++)
	{
		if (i == index)
		{
			m_pTabBarList.at(index)->setSelected();
		}
		else
		{
			m_pTabBarList.at(i)->setDeselected();
		}
	}
/*	if (index <= 0)  // 头
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
	*/
	m_pPrevBtn = m_pTabBarList.at(index);

// 	QFile file(":/tabbar.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 	this->setStyleSheet(style);
// 	file.close();
}

void TabBar::paintEvent(QPaintEvent* e)
{
	//QPainter p(this);

// 	QDataStream dataStream(&itemData, QIODevice::ReadOnly);
// 
// 	QPixmap pixmap;
// 	QString offset;
// 	dataStream >> pixmap >> offset;
// 
// 
// 	//painter.setOpacity(0.5);
// 
// 
// 	p.drawPixmap(0, 0 ,pixmap);

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
		pbtn->setFixedHeight(height()/tabCount());
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
// 	if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
// 	{
// 		if (event->source() == this) 
// 		{
// 			event->setDropAction(Qt::MoveAction);
// 			event->accept();
// 		} 
// 		else 
// 		{
// 			event->acceptProposedAction();
// 		}
// 	} 
// 	else 
// 	{
// 		event->ignore();
// 	}
}

void TabBar::dragMoveEvent(QDragMoveEvent *event)
{
// 	if (event->mimeData()->hasFormat("application/x-dnditemdata")) 
// 	{
// 		if (event->source() == this) 
// 		{
// 			event->setDropAction(Qt::MoveAction);
// 			event->accept();
// 		} 
// 		else 
// 		{
// 			event->acceptProposedAction();
// 		}
// 	} 
// 	else 
// 	{
// 		event->ignore();
// 	}
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
 	/*TabItem *child = static_cast<TabItem*>(childAt(event->pos()));
 	if (!child)
 		return;
 	//QString ss = 
 	
 
  	QPixmap pixmap = child->getTabItemPixmap();
 // 
 	QByteArray itemData;
 	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
 	dataStream << pixmap <<child->text();//<< QPoint(event->pos() - child->pos());
 
 	QMimeData *mimeData = new QMimeData;
 	mimeData->setData("application/x-dnditemdata", itemData);
 
 	QDrag *drag = new QDrag(this);
 	connect(drag, SIGNAL(actionChanged(Qt::DropAction)), this, SLOT(OnactionChanged(Qt::DropAction)));
  	drag->setMimeData(mimeData);
  	drag->setPixmap(pixmap);
 	drag->setHotSpot(event->pos() - child->pos());
 
//  	QPixmap tempPixmap = pixmap;
//  	QPainter painter;
//  	painter.begin(&tempPixmap);
//  	painter.fillRect(pixmap.rect(), QColor(0,0,0,0));
//  	painter.end();	
 
 
 	if (drag->exec(Qt::MoveAction)) 
 	{
 		child->close();
 	} 
 	else 
 	{
 		child->show();
 	}*/
 	QWidget::mousePressEvent(event);
}

void TabBar::dragLeaveEvent( QDragLeaveEvent * event ) 
{
	qDebug()<<"dragLeaveEvent";
}

void TabBar::mouseReleaseEvent( QMouseEvent *event )
{
	int m = 0;
}

void TabBar::OnactionChanged( Qt::DropAction act )
{
	qDebug()<<act;
}

bool TabBar::eventFilter( QObject * obj, QEvent * event)
{
	if(event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* en = dynamic_cast<QMouseEvent*>(event);
		if (!en) return false;
		if (obj->parent() == this)
		{
			qDebug()<<obj->objectName();
			press = true;
			qDebug()<<"press ";
			TabItem* item = static_cast<TabItem*>(obj);
			if (!item) return false;

			int index = m_pTabBarList.indexOf(item);

			QScreen *QSCREEN = QGuiApplication::primaryScreen();
			QPixmap pixmap = QSCREEN->grabWindow(item->winId());
			// 
			
			QDataStream dataStream(&itemData, QIODevice::WriteOnly);
			dataStream << pixmap <<item->getLabelText() << index;    //<< QPoint(event->pos() - child->pos());

			QMimeData *mimeData = new QMimeData;
			mimeData->setData("application/x-dnditemdata", itemData);

// 			m_drag = new QDrag(this);
// 			//connect(m_drag, SIGNAL(actionChanged(Qt::DropAction)), this, SLOT(OnactionChanged(Qt::DropAction)));
// 			m_drag->setMimeData(mimeData);
// 			m_drag->setPixmap(pixmap);
// 			m_drag->setHotSpot(en->pos());// - item->pos()
// 
// 			QPixmap tempPixmap = pixmap;
// 			QPainter painter;
// 			painter.begin(&tempPixmap);
// 			painter.fillRect(pixmap.rect(), QColor(0,0,0,0));
// 			painter.end();	
// 
// 			m_drag->exec(Qt::MoveAction);
		}
		

	}

	if(event->type() == QEvent::MouseMove)
	{
		QMouseEvent* en = dynamic_cast<QMouseEvent*>(event);
		if (!en) return false;
		if (press && obj->parent() == this)
		{
			move = true;
			qDebug()<<"move ";

			QDataStream dataStream(&itemData, QIODevice::ReadOnly);

			QPixmap pixmap;
			QString offset;
			dataStream >> pixmap >> offset;

			
			//painter.setOpacity(0.5);
//			painter->drawPixmap(0, 0 ,QPixmap(":/s.png"));
			setCursor(QCursor(pixmap));
		//QPixmap::
// 			painter->begin(&pixmap);
// 			painter->fillRect(pixmap.rect(), QColor(0,0,0,255));
// 			painter->end();	

//			repaint();

		}
		

	}

	if(event->type() == QEvent::MouseButtonRelease)
	{

		if (obj->parent() == this)
		{
			if (press && move /*&& obj->parent() == this*/)
			{
				qDebug()<<"press "<< press;

				QDataStream dataStream(&itemData, QIODevice::ReadOnly);
				QPixmap pixmap;
				QString offset;
				int index;
				dataStream >> pixmap >> offset >> index;


				//emit moveTabPage(index, offset);

				press = false;
				move = false;
				setCursor(QCursor(Qt::ArrowCursor));
				return true;
			}

			press = false;
			move = false;
		}
		qDebug()<<"release ";
	}

	return false;
}



void TabBar::OnFlowUp()
{
	TabItem* item = qobject_cast<TabItem*>(sender());
	if (!item) return;
	emit moveTabPage(m_pTabBarList.indexOf(item), item->getLabelText());
}
