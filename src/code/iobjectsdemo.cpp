#include "stdafx.h"
#include "iobjectsdemo.h"

#include <QLabel>

iObjectsDemo::iObjectsDemo(QWidget *parent) : QWidget(parent)
{
	setObjectName("iObjectsDemo");



	QLabel *lable = new QLabel(this);
	lable->setText(QStringLiteral("我是中文"));
	setGeometry(200,200,1247,766);


	m_pCloseBtn = new QPushButton(this);
	m_pCloseBtn->setObjectName("CloseBtn");
	m_pCloseBtn->setFixedHeight(48);
	m_pCloseBtn->setFixedWidth(48);
	m_pCloseBtn->setGeometry(width() - 60, 20, m_pCloseBtn->width(), m_pCloseBtn->height());


	connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(OnCloseBtnClicked()));

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

void iObjectsDemo::OnCloseBtnClicked()
{
	this->close();
}
