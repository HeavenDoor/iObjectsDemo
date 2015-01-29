#include "scenetab.h"


SceneTab::SceneTab( QWidget *parent /*= NULL*/ ) : QWidget(parent)
{

}


SceneTab::~SceneTab()
{

}



QObject* SceneTab::getObject()
{
	return this;
}

void SceneTab::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void SceneTab::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void SceneTab::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void SceneTab::showPlugin()
{
	this->show();
}

void SceneTab::raisePlugin()
{
	this->raise();
}

void SceneTab::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}

void SceneTab::lowerPlugin()
{
	lower();
}

void SceneTab::setPluginWidth( int width )
{
	setFixedWidth(width);
}


void SceneTab::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int SceneTab::pluginWidth()
{
	return width();
}

int SceneTab::pluginHeight()
{
	return height();
}

void SceneTab::test()
{

}
