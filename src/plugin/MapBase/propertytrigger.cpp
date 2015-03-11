#include "stdafx.h"
#include "propertytrigger.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QPushButton>

PropertyTrigger::PropertyTrigger(QWidget *parent) : QWidget(parent)
{
	
}

PropertyTrigger::~PropertyTrigger()
{

}

void PropertyTrigger::setText(QString t)
{
	m_text = t;
}

void PropertyTrigger::init()
{
	QGraphicsScene* pScene = new QGraphicsScene(this); 
	QGraphicsView* pView = new QGraphicsView(pScene, this); 
	pView->horizontalScrollBar()->hide();
	pView->verticalScrollBar()->hide();
	pView->setGeometry(300, 20, 100, 100);


	QLabel*label = new QLabel();
	label->setWordWrap(true);
	label->setAlignment(Qt::AlignTop);
	QString s = m_text;

	//label->setStyleSheet("background-color: red");


	pScene->addWidget(label); 
	pView->rotate(90); 

	QFont ft;
	ft.setPointSize(8);
	ft.setWeight(13);
	ft.setBold(true);
	label->setFont(ft);

	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::black);
	label->setPalette(pa);

	label->setText(s);
	label->adjustSize();

	int m = label->width();
	int h = label->height();

	pView->setGeometry(0,0,label->height() + 6, label->width() + 6);
	pView->setAttribute(Qt::WA_TransparentForMouseEvents);
	this->setGeometry(100,100,label->height() + 6, label->width() + 6);
	m_width = pView->width();
	setFixedHeight(pView->height());
	setFixedWidth(pView->width());
}



void PropertyTrigger::mousePressEvent( QMouseEvent *e )
{
	emit tirggered();
}

int PropertyTrigger::getWidth()
{
	return m_width;
}
