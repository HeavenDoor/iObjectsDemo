#ifndef SCENETAB_H
#define SCENETAB_H

#include "scenetab_global.h"
#include "..\\..\\interface\scenetabinterface.h"

#include <QtWidgets/QWidget>

class SceneTab : public QWidget ,SceneTabInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{2E23E146-CD7C-4D00-9335-E0DB52AE9087}" FILE "scenetab.json")
	Q_INTERFACES(SceneTabInterface)
public:
	SceneTab(QWidget *parent = NULL);
	~SceneTab();

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
