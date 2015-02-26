#include "stdafx.h"
#include "tabitem.h"

TabItem::TabItem(QWidget *parent) : QToolButton(parent)
{

}

TabItem::~TabItem()
{

}


QPixmap TabItem::getTabItemPixmap()
{
	QPixmap pix = QPixmap::grabWidget(this, this->geometry());
	return pix;
}


void TabItem::dragEnterEvent( QDragEnterEvent * event ) 
{
	QWidget::dragEnterEvent(event);
}

void TabItem::dragLeaveEvent( QDragLeaveEvent * event ) 
{
	QWidget::dragLeaveEvent(event);
}

void TabItem::mousePressEvent( QMouseEvent * event )
{
	//event->accept();
	//
	click();
	//event->ignore();
	//QToolButton::mousePressEvent(event);

	QWidget::mousePressEvent(event);
}


void TabItem::mouseReleaseEvent(QMouseEvent *event)
{

	//event->ignore();
	//QToolButton::mouseReleaseEvent(event);
	QWidget::mouseReleaseEvent(event);
}

void TabItem::dragMoveEvent( QDragMoveEvent *event ) 
{
	QWidget::dragMoveEvent(event);
}

void TabItem::dropEvent( QDropEvent *event ) 
{
	QWidget::dropEvent(event);
}
