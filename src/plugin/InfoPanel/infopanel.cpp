#include "stdafx.h"
#include "infopanel.h"

InfoPanel::InfoPanel()
{
	setObjectName("QuickInfoPanel");
	setSource(QUrl("qrc:/InfoPanel.qml"));
	setResizeMode(QQuickWidget::SizeRootObjectToView);
	setClearColor(Qt::transparent);
	setAttribute(Qt::WA_AlwaysStackOnTop);
	setMouseTracking(true);
}

InfoPanel::~InfoPanel()
{

}

void InfoPanel::registerTypes( const char *uri )
{
	// Q_ASSERT(uri == QLatin1String("TimeExample"));
	//qmlRegisterType<TimeModel>(uri, 1, 0, "Time");
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
	setGeometry(ax, ay, aw, ah);
}

void InfoPanel::setPluginWidth( int width )
{
	setFixedWidth(width);
}

void InfoPanel::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int InfoPanel::pluginWidth()
{
	return width();
}

int InfoPanel::pluginHeight()
{
	return height();
}