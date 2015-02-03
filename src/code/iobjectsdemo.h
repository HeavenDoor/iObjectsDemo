#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>
#include <QtQuickWidgets/QQuickWidget>
#include "title.h"
#include "pluginloader.h"
#include "ToolBox/toolbox.h"
#include "InfoPanel/infopanel.h"
#include "TabView/tabview.h"
#include "InteLayers/intelayers.h"

#include "interface/widgetplugininterface.h"
#include "interface/mapbaseinterface.h"
#include "interface/scenebaseinterface.h"

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
	void OnShowLayers(QVector<QString> vec);
private:
	// 加载控件
	bool initControls();
	bool initTabView(); // 地图插件依赖于TabView 注意TabView要先加载
	bool initInteLayers(); // 情报图层需要先于地图插件加载
	// 加载插件 path：插件所在文件夹目录
	bool loadPlugins(const QString& path, const QString& pluginName);
	// 卸载插件 
	bool unLoadPlugins(const QString& pluginName);
private:

	QString pluginPath;
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;

	ToolBox * m_pToolBox;
	InfoPanel* m_pInfoPanel;
	TabView* m_pTabView;
	InteLayers* m_pInteLayers;
	Title* m_pTitle;
	Pluginloader* m_pPluginloader;
	QVariantMap m_pluginMap;

	MapBaseInterface* m_pMapBase;

	
};

#endif // IOBJECTSDEMO_H
