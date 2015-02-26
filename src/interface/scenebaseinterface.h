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
	// UGSceneEditorWnd对象的指针的获取
	virtual void* getUGSceneEditorWnd() = 0;
	// 获得SceneBase插件主界面的指针，作为主界面Tab页面显示
	virtual QWidget* getWidget() = 0;   
	// 获得SceneBase插件中SceneLayers控件指针，给主界面做布局处理
	virtual QWidget* getSceneLayers() = 0;
	// 获得SceneBase插件SceneController控件指针
	virtual QWidget* getSceneController() = 0;

};

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(SceneBaseInterface, "{07860120-8AFA-4DBE-8AD5-4DA96A26CDEC}")
QT_END_NAMESPACE

#endif