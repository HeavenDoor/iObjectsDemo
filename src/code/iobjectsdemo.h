#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>
#include <QQuickWidget>
#include "title.h"
#include <QQuickWidget>

#include "interface/widgetplugininterface.h"
#include "interface/toolboxinterface.h"
#include "interface/maptabinterface.h"
#include "interface/intelayersinterface.h"
#include "interface/infopanelinterface.h"
#include "pluginloader.h"

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
	//QQuickWidget* m_pInfoPanel;

	Pluginloader* m_pPluginloader;
	QVariantMap m_pluginMap;
};

#endif // IOBJECTSDEMO_H
