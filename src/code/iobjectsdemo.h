#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>
#include <QtQuickWidgets/QQuickWidget>
#include "title.h"

#include "interface/widgetplugininterface.h"
#include "interface/toolboxinterface.h"
#include "interface/maptabinterface.h"
#include "interface/intelayersinterface.h"
#include "interface/infopanelinterface.h"
#include "pluginloader.h"
#include "Map2D/map2dcontainer.h"
class iObjectsDemo : public QWidget
{
	Q_OBJECT

public:
	iObjectsDemo(QWidget *parent = 0);
	~iObjectsDemo();
	void test(){}
	
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void moveEvent(QMoveEvent*);
signals:

private slots:
	void reloadPlugins();

	void OnCloseBtnClicked();
	void OnTitleCollapsed();

	void OnToolBoxPlugin_SearchBtnClicked();
	void OnToolBoxPlugin_SettingBtnClicked();
	void OnInteLayersPlugin_RefeshWindow();
private:
	bool loadControls();
	bool loadPlugins(const QString& path, const QString& pluginName);
	bool unLoadPlugins(const QString& pluginName);
private:

	QString pluginPath;
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;

	ToolBoxInterface* m_pToolBox;
	MapTabInterface* m_pMapTab;
	InteLayersInterface* m_pInteLayers;
	InfoPanelInterface* m_pInfoPanel;

	Title* m_pTitle;
	Pluginloader* m_pPluginloader;
	QVariantMap m_pluginMap;

	Map2DContainer* m_pMap2DContainer;

	QWidget* a;
	QWidget* b;
	QWidget* c;
	QWidget* d;
	QWidget* e;
};

#endif // IOBJECTSDEMO_H
