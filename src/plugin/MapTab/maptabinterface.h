#ifndef MAPTABINTERFACE_H
#define MAPTABINTERFACE_H


#include <QObject>
#include <QtWidgets/QWidget>
class MapTabInterface
{
public:
	virtual void test() = 0;
	virtual QWidget* getWidget() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(MapTabInterface, "{6EDEBEEB-DFDE-461E-BAF2-2A5D0C90BF1D}")
QT_END_NAMESPACE

#endif

