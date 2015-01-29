#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>
#include <QtQuickWidgets/QQuickWidget>
#include "title.h"
#include "toolbox.h"

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
	void OnShowLayers(QVector<QString> vec);
private:
	// ���ؿؼ�
	bool loadControls();
	// ���ز�� path����������ļ���Ŀ¼
	bool loadPlugins(const QString& path, const QString& pluginName);
	// ж�ز�� 
	bool unLoadPlugins(const QString& pluginName);
private:

	QString pluginPath;
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;

	//ToolBoxInterface* m_pToolBox;
	MapTabInterface* m_pMapTab;
	InteLayersInterface* m_pInteLayers;
	InfoPanelInterface* m_pInfoPanel;

	Title* m_pTitle;
	ToolBox * m_pToolBox;

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
