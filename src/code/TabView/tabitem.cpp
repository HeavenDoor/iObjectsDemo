#include "stdafx.h"
#include "tabitem.h"

TabItem::TabItem(QString tabName, QWidget *parent) : QToolButton(parent), m_text(tabName)
{
	setAcceptDrops(true);
	setObjectName("TabItem");


	m_pScene = new QGraphicsScene(this); 
	m_pView = new QGraphicsView(m_pScene, this); 
	m_pView->horizontalScrollBar()->hide();
	m_pView->verticalScrollBar()->hide();
	//pView->setGeometry(300, 20, 100, 100);
	

	m_pTextLabel = new QLabel();
	m_pTextLabel->setWordWrap(true);
	m_pTextLabel->setAlignment(Qt::AlignTop);

	
	//label->setStyleSheet("background-color: red");

	m_pScene->addWidget(m_pTextLabel); 
	m_pView->rotate(90); 

	m_pTextLabel->setText(tabName);
	m_pTextLabel->adjustSize();

	// 	int m = label->width();
	// 	int h = label->height();

	m_pView->setGeometry(0,0,m_pTextLabel->height() + 6, m_pTextLabel->width() + 6);
	m_pView->setAttribute(Qt::WA_TransparentForMouseEvents);
	//
	
	//pbtn->setGeometry(100,100,label->height() + 6, label->width() + 6);

	m_pFlowBtn = new QPushButton(this);
	connect(m_pFlowBtn, SIGNAL(clicked()), this, SIGNAL(flowUp()));
	m_pFlowBtn->setObjectName("pupupBtn");
	m_pFlowBtn->setFixedHeight(12);
	m_pFlowBtn->setFixedWidth(12);
}

TabItem::~TabItem()
{

}

QPixmap TabItem::getTabItemPixmap()
{
	QPixmap pix = QPixmap::grabWindow(this->winId());
	return pix;
}

void TabItem::dragEnterEvent( QDragEnterEvent * event ) 
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
	//QWidget::dragEnterEvent(event);
}

void TabItem::dragLeaveEvent( QDragLeaveEvent * event ) 
{
	QWidget::dragLeaveEvent(event);
}

void TabItem::mousePressEvent( QMouseEvent * event )
{
	//event->ignore();
	QToolButton::mousePressEvent(event);

	//QWidget::mousePressEvent(event);
}

void TabItem::mouseReleaseEvent(QMouseEvent *event)
{

	//event->ignore();
	QToolButton::mouseReleaseEvent(event);
	//QWidget::mouseReleaseEvent(event);
}

void TabItem::dragMoveEvent( QDragMoveEvent *event ) 
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
	//QWidget::dragMoveEvent(event);
}

void TabItem::dropEvent( QDropEvent *event ) 
{
	QWidget::dropEvent(event);
}

void TabItem::resizeEvent( QResizeEvent *e )
{
	m_pView->setFixedWidth(width());
	m_pView->setFixedHeight(height());


	m_pFlowBtn->setGeometry(width() - m_pFlowBtn->width() - 2, 2, m_pFlowBtn->width(), m_pFlowBtn->height());
}

void TabItem::setSelected()
{
	QFont ft;
	ft.setPointSize(10);
	ft.setWeight(10);
	ft.setBold(true);
	m_pTextLabel->setFont(ft);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::white);
	m_pTextLabel->setPalette(pa);
	m_pTextLabel->setAttribute(Qt::WA_TranslucentBackground);
	m_pTextLabel->adjustSize();
	m_pView->setStyleSheet("background-color: #7ba4db");
	m_pView->setGeometry(0,0,m_pTextLabel->height() + 6, m_pTextLabel->width() + 6);
}

void TabItem::setDeselected()
{
	QFont ft;
	ft.setPointSize(10);
	ft.setWeight(10);
	ft.setBold(false);
	m_pTextLabel->setFont(ft);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::black);
	m_pTextLabel->setPalette(pa);
	m_pTextLabel->setAttribute(Qt::WA_TranslucentBackground);
	m_pTextLabel->adjustSize();
	m_pView->setStyleSheet("background-color: #ffffff");
	m_pView->setGeometry(0,0,m_pTextLabel->height() + 6, m_pTextLabel->width() + 6);
}

QString TabItem::getLabelText()
{
	return m_text;
}
