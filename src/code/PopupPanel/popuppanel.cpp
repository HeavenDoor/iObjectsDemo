#include "stdafx.h"
#include "popuppanel.h"
#include "..\\..\\commom\widgetrect.h"

#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebFrame>

PopupPanel::PopupPanel(QWidget *parent, int xPos)	: QWidget(parent),m_Xpos(xPos)
{
	m_pPopupBody = NULL;
	m_pPopupTail = NULL;
	m_pWebView = NULL;
	setObjectName("PopupPanel");
// 	setFixedWidth(347);
// 	setFixedHeight(300);
	setAttribute(Qt::WA_AlwaysStackOnTop);


	m_pPopupBody = new QWidget(this);
	m_pPopupBody->setObjectName("PopupBody");

	m_pPopupTail = new QWidget(this);
	m_pPopupTail->setObjectName("PopupTail");
	m_pPopupTail->setFixedHeight(31);
	m_pPopupTail->setFixedWidth(42);


	m_pWebView = new QWebView(m_pPopupBody);
	m_pWebView->setObjectName("PopupWebView");
	m_pWebView->setUrl(QUrl("http://www.baidu.com"));
	m_pWebView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
	m_pWebView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
	m_pWebView->page()->setViewportSize(m_pWebView->size());
	m_pWebView->setZoomFactor(0.5);
	qApp->installEventFilter(this);
	
}

PopupPanel::~PopupPanel()
{
	if (m_pWebView)
	{
		delete m_pWebView;
		m_pWebView = NULL;
	}

	if (m_pPopupBody)
	{
		delete m_pPopupBody;
		m_pPopupBody = NULL;
	}

	if (m_pPopupTail)
	{
		delete m_pPopupTail;
		m_pPopupTail = NULL;
	}
}

void PopupPanel::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

void PopupPanel::resizeEvent( QResizeEvent * )
{

	if (m_pPopupBody && m_pPopupTail)
	{
		m_pPopupBody->setGeometry(0,0, width(), height() - m_pPopupTail-> height() + 1);
		m_pPopupTail->setGeometry(width()/2, height() - m_pPopupTail->height(), m_pPopupTail->width(), m_pPopupTail->height());
		m_pPopupTail->raise();
	}

	if (m_pWebView)
	{
		m_pWebView->setGeometry(10, 10, m_pPopupBody->width() - 20, m_pPopupBody->height() - 20);
		m_pWebView->page()->setViewportSize(m_pWebView->size());
	}

	
}

bool PopupPanel::eventFilter(QObject* obj, QEvent* e)
{
	QMouseEvent* en = dynamic_cast<QMouseEvent*>(e);
	if(!en) return false;
	QPoint point = en->globalPos();
	QRect rect = WidgetRect::widgetGlobalRect(this);
	if (en->buttons() && Qt::LeftButton)
	{
		if (obj->objectName() != "PopupPanel" && !rect.contains(point))
		{
			emit closePopupPanel();
		}
	}
	return false;
}