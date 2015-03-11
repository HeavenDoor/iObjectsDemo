#ifndef SCENETAB_H
#define SCENETAB_H

#include "scenebase_global.h"
#include "..\\..\\interface\scenebaseinterface.h"

#include "Stream/ugdefs.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

#include <QDesktopWidget>
#include <QApplication>
#include <QtGui>

#include "Workspace/UGWorkspace.h"
#include "Engine/UGDataSources.h"
#include "Scene/UGRoot3D.h"
#include "Scene/UGScene3D.h"
#include "SceneEditor/UGSceneEditorWnd.h"
#include "Graphics3D/UGRenderTarget.h"
namespace UGC
{
	class UGWorkspace;
	class UGSceneEditorWnd;
	class UGRoot3D;
	class UGModel;
	class UGKmlContainer3D;
}

using namespace UGC;

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


	virtual void* getUGSceneEditorWnd();
	virtual QWidget* getWidget();
	virtual QWidget* getSceneLayers();
	virtual QWidget* getSceneController();
	virtual QString getStyleSheet();
	virtual void setUGMapEditorWnd(void* wnd);

public:
	void SetWorkspace(/*UGWorkspace* pW*/void* workspace);
	virtual void paintEvent(QPaintEvent *event);
	void InitScene3D();
	virtual void destroy(bool destroyWindow /* = true */, bool destroySubWindows /* = true */);
	virtual void mouseMoveEvent(QMouseEvent * event);
	virtual void wheelEvent(QWheelEvent *event);
	virtual void mousePressEvent(QMouseEvent * event);
	virtual void mouseReleaseEvent(QMouseEvent * event);
	virtual void leaveEvent(QEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);
	void Open();

public slots:
	void render();
signals:
	void renderTick();
public:
	UGSceneEditorWnd* GetUGSecneWnd();
private:
	void ReviseCursor();

	UGWorkspace* m_pWorkspace;

	UGSceneEditorWnd* m_pSceneWnd;

	UGRoot3D* m_root3D;

	QTimer* m_timer;

	QVBoxLayout* verticalLayout;

	UGScene3D *pScene;
private:

};

#endif // SCENETAB_H
