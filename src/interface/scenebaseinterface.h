//////////////////////////////////////////////////////////////////////////
// SceneBase插件功能性接口                   
//////////////////////////////////////////////////////////////////////////

#ifndef SCENEBASEINTERFACE_H
#define SCENEBASEINTERFACE_H

#include "widgetplugininterface.h"
#include <QtWidgets/QWidget>

class SceneBaseInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;

};

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(SceneBaseInterface, "{07860120-8AFA-4DBE-8AD5-4DA96A26CDEC}")
QT_END_NAMESPACE

#endif