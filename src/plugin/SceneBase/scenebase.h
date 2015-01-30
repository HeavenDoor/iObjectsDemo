#ifndef SCENETAB_H
#define SCENETAB_H

#include "scenebase_global.h"
#include "..\\..\\interface\scenebaseinterface.h"

#include <QtWidgets/QWidget>

class SceneBase : public QWidget, SceneBaseInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{2E23E146-CD7C-4D00-9335-E0DB52AE9087}" FILE "scenebase.json")
	Q_INTERFACES(SceneBaseInterface)
public:
	SceneBase(QWidget *parent = NULL);
	~SceneBase();

	virtual void test();
	virtual QObject* getObject();
	virtual void setPluginGeometry(const QRect& rect);
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah);
	virtual void setPluginParent(QWidget* parentWidget);
	virtual void showPlugin();
	virtual void raisePlugin();
	virtual void lowerPlugin();
	virtual void resizePlugin(int ax, int ay, int aw, int ah);
	virtual void setPluginWidth(int width);
	virtual void setPluginHeight(int height);
	virtual int pluginWidth();
	virtual int pluginHeight();
private:

};
#endif // SCENETAB_H
