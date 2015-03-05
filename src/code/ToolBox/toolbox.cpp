#include "stdafx.h"
#include "toolbox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent)
{
	this->setObjectName("ToolBox");
	this->setWindowOpacity(1);
	m_pOutLayout = NULL;
	m_pLeftLayout = NULL;
	m_pRightLayout = NULL;
	m_size.setWidth(50);
	m_size.setHeight(50);


	m_pOutLayout = new QHBoxLayout(this);
 	m_pOutLayout->setContentsMargins(0, 0, 0, 0);
 	m_pOutLayout->setSpacing(width());
	m_pOutLayout->setAlignment(Qt::AlignHorizontal_Mask);

	m_pLeftLayout = new QHBoxLayout(this);
	m_pLeftLayout->setContentsMargins(0, 0, 0, 0);
	m_pLeftLayout->setSpacing(10);
	m_pLeftLayout->setAlignment(Qt::AlignLeft);

	m_pRightLayout = new QHBoxLayout(this);
	m_pRightLayout->setContentsMargins(0, 0, 0, 0);
	m_pRightLayout->setSpacing(10);
	m_pRightLayout->setAlignment(Qt::AlignRight);

	m_pOutLayout->addLayout(m_pLeftLayout);
	m_pOutLayout->addStretch(0);
	m_pOutLayout->addLayout(m_pRightLayout);

	this->setLayout(m_pOutLayout);	
}

ToolBox::~ToolBox()
{

}

void ToolBox::paintEvent( QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void ToolBox::resizeEvent( QResizeEvent * )
{
// 	if (m_pSet)
// 	{
// 		m_pSet->setGeometry(width() - m_pSet->width() - 5, 3, m_pSet->width(), m_pSet->height());
// 	}

}



QObject* ToolBox::createToolButton( const QString& objectName, Qt::Alignment align /*= Qt::AlignLeft*/ )
{
	QPushButton* pBtn = new QPushButton(this);	
	pBtn->setObjectName(objectName);
	pBtn->setFixedSize(m_size);
	if (align != Qt::AlignRight)
	{
		m_pLeftLayout->addWidget(pBtn);
	}
	else
	{
		m_pRightLayout->addWidget(pBtn);

	}
	return pBtn;
}

void ToolBox::setToolButtonSize( QSize size )
{
	m_size = size;
}

void ToolBox::addWidget( QWidget* w )
{
	m_pLeftLayout->addWidget(w);
}

void ToolBox::removeWidget( QWidget* w )
{
	m_pLeftLayout->removeWidget(w);
}

void ToolBox::addLine( Qt::Alignment align /*= Qt::AlignLeft*/ )
{
	if (!m_pLeftLayout || !m_pOutLayout || !m_pRightLayout) return;

	QFrame* p = new QFrame(this);
	p->setObjectName("ToolBoxLine");
	p->setFixedHeight(height() -  8);
	p->setFixedWidth(4);

	if (align == Qt::AlignLeft)
	{
		m_pLeftLayout->addWidget(p);
	}

	else
	{
		m_pRightLayout->addWidget(p);
	}
}
