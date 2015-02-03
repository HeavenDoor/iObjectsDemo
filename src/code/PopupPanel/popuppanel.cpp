#include "stdafx.h"
#include "popuppanel.h"

PopupPanel::PopupPanel(QWidget *parent)	: QWidget(parent)
{
	setObjectName("PopupPanel");
}

PopupPanel::~PopupPanel()
{

}

void PopupPanel::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}