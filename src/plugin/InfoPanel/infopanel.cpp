#include "stdafx.h"
#include "infopanel.h"
#include <QQuickItem>

InfoPanel::InfoPanel()
{
	m_timespan = 500;
	registerTypes("SuperMap");

	setObjectName("QuickInfoPanel");
	setSource(QUrl("qrc:/InfoPanel.qml"));
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setClearColor(Qt::transparent);
	setAttribute(Qt::WA_AlwaysStackOnTop);
	setMouseTracking(true);

	m_pProAnima = new QPropertyAnimation(this, "geometry");
	connect(m_pProAnima, SIGNAL(finished()), this, SLOT(OnAnimationFinished()));


	QQuickItem * rootItem = rootObject();  
	m_pExpandBtn = rootItem->findChild<QObject*>("expandBtn");
	m_pRoot = rootItem->findChild<QObject*>("root");  
	QObject * collesAnimation = rootItem->findChild<QObject*>("animWidthDecrease");  
	if(m_pExpandBtn)  
	{  
		QObject::connect(m_pExpandBtn, SIGNAL(buttonClicked()), this, SLOT(expandWnd()));  
	}		
	if(collesAnimation)  
	{  
		QObject::connect(collesAnimation, SIGNAL(stopped()), this, SLOT(collapseWnd()));  
	}
	//qApp->installEventFilter(this);
}

InfoPanel::~InfoPanel()
{

}

void InfoPanel::registerTypes( const char *uri )
{
	qmlRegisterType<InfoHandler>(uri, 1, 0, "InfoHandler");
}

void InfoPanel::test()
{

}

QObject* InfoPanel::getObject()
{
	return this;
}

void InfoPanel::setPluginGeometry( const QRect& rect )
{
	setGeometry(rect);
}

void InfoPanel::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	setGeometry(ax, ay, aw, ah);
}

void InfoPanel::setPluginParent( QWidget* parentWidget )
{
	setParent(parentWidget);
}

void InfoPanel::showPlugin()
{
	show();
}

void InfoPanel::raisePlugin()
{
	raise();
}

void InfoPanel::lowerPlugin()
{
	lower();
}

void InfoPanel::resizePlugin( int ax, int ay, int aw, int ah )
{
	if (!m_pExpandBtn) return;
	if (!m_pExpandBtn->property("visible").toBool())
	{
		setGeometry(ax, ay, aw, ah);
	}
	else
	{
		this->setGeometry(ax + aw - m_pExpandBtn->property("imgWidth").toInt() , ay, m_pExpandBtn->property("imgWidth").toInt(), m_pExpandBtn->property("imgHeight").toInt() + 10);
	}
}

void InfoPanel::setPluginWidth( int width )
{
	m_width = width;
	if (!m_pRoot) return;
	m_pRoot->setProperty("width", width);
	//setFixedWidth(width);
}

void InfoPanel::setPluginHeight( int height )
{
	m_height = height;
	//setFixedHeight(height);
 	if (!m_pRoot) return;
 	m_pRoot->setProperty("height", height);
	//
}

int InfoPanel::pluginWidth()
{
	return m_width;
	return width();
}

int InfoPanel::pluginHeight()
{
	return m_height;
	return height();
}

bool InfoPanel::eventFilter(QObject* obj, QEvent* e)
{
// 	if(e->type() == QEvent::MouseButtonPress)
// 	{
// 		QMouseEvent* en = dynamic_cast<QMouseEvent*>(e);
// 		if(!en) return false;
// 		QPoint point = en->globalPos();
// 	}
	return false;
}

void InfoPanel::collapseWnd()
{

	if (!m_pExpandBtn) return;
	if (!m_pRoot) return;

	int m = m_pExpandBtn->property("imgWidth").toInt();
	int n = m_pExpandBtn->property("imgHeight").toInt();

	
	
  	m_pRoot->setProperty("width", m);
  	m_pRoot->setProperty("height", n);

	QRect rec = this->rect();
	QPoint e = mapToParent(rec.topRight());
	this->setGeometry(e.x() - m_pExpandBtn->property("imgWidth").toInt(), e.y(),m_pExpandBtn->property("imgWidth").toInt(), m_pExpandBtn->property("imgHeight").toInt() + 10);
	m_pRoot->setProperty("innerWidth", m_width);
}

void InfoPanel::expandWnd()
{
  	QRect rec = this->geometry();
  	this->setGeometry(rec.right() - m_width, rec.top(), m_width, m_height);
	
	if (!m_pRoot) return;
	m_pRoot->setProperty("width", m_width);
	m_pRoot->setProperty("height", m_height);
}

void InfoPanel::OnAnimationFinished()
{

}

void InfoPanel::setAnimationTimespan( int timespan )
{
	m_timespan = timespan;
	if (!m_pRoot) return;
	m_pRoot->setProperty("duration", timespan);
}
