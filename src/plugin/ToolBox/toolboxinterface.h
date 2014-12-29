#ifndef TOOLBOXINTERFACE_H
#define TOOLBOXINTERFACE_H

#include <QObject>
#include <QtWidgets/QWidget>
class ToolBoxInterface
{
public:
	virtual void test() = 0;
	virtual QWidget* getWidget() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(ToolBoxInterface, "{269649A4-5E60-4B63-BA70-665DF7BF2917}")
QT_END_NAMESPACE

#endif
