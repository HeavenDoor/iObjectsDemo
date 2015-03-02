#include "stdafx.h"
#include "tabitem.h"

TabItem::TabItem(QWidget *parent) : QToolButton(parent)
{
	setAcceptDrops(true);
	setObjectName("TabItem");
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
