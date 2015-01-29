#ifndef SCENETABINTERFACE_H
#define SCENETABINTERFACE_H

#include "widgetplugininterface.h"
#include <QtWidgets/QWidget>
class SceneTabInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;

};

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(SceneTabInterface, "{07860120-8AFA-4DBE-8AD5-4DA96A26CDEC}")
QT_END_NAMESPACE

#endif