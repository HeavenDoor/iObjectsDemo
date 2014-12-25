#include "stdafx.h"
#include "iobjectsdemo.h"

#include <QLabel>

iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");



	QLabel *lable = new QLabel(this);
	lable->setText(QStringLiteral("我是中文"));
	setGeometry(200,200,1247,766);
}

iObjectsDemo::~iObjectsDemo()
{

}

void iObjectsDemo::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}
