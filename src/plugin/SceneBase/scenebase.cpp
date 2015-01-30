#include "scenebase.h"


SceneBase::SceneBase( QWidget *parent /*= NULL*/ ) : QWidget(parent)
{

}


SceneBase::~SceneBase()
{

}



QObject* SceneBase::getObject()
{
	return this;
}

void SceneBase::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void SceneBase::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void SceneBase::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void SceneBase::showPlugin()
{
	this->show();
}

void SceneBase::raisePlugin()
{
	this->raise();
}

void SceneBase::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}

void SceneBase::lowerPlugin()
{
	lower();
}

void SceneBase::setPluginWidth( int width )
{
	setFixedWidth(width);
}


void SceneBase::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int SceneBase::pluginWidth()
{
	return width();
}

int SceneBase::pluginHeight()
{
	return height();
}

void SceneBase::test()
{

}
