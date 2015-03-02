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
#include "PopupPanel/popuppanel.h"

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
	void mousePressEvent(QMouseEvent*);
	bool eventFilter(QObject* obj, QEvent* e);

	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
signals:

private slots:
	void reloadPlugins();
	void OnCloseBtnClicked();
	void OnTitleCollapsed();
	void OnToolBoxPlugin_SearchBtnClicked();
	void OnToolBoxPlugin_SettingBtnClicked();
	void OnInteLayersPlugin_RefeshWindow();
	void OnShowMapBaseTips();
	void OnClosePopupPanel();
	
private:
	// ���ؿؼ�
	bool initControls();
	// ��ͼ���������TabView ע��TabViewҪ�ȼ���
	bool initTabView(); 
	// �鱨ͼ����Ҫ���ڵ�ͼ�������
	bool initInteLayers(); 
	// ToolBox��Ҫ���ڵ�ͼ�������
	bool initToolBox();
	// ���ز�� path����������ļ���Ŀ¼
	bool loadPlugins(const QString& path, const QString& pluginName);
	// ж�ز�� 
	bool unLoadPlugins(const QString& pluginName);
private:
	QString pluginPath;
	QPushButton* m_pCloseBtn;
	QPushButton* m_pPopBtn;
	ToolBox * m_pToolBox;
	InfoPanel* m_pInfoPanel;
	TabView* m_pTabView;
	TabView* m_pFlowTabView;
	InteLayers* m_pInteLayers;
	PopupPanel* m_pPopupPanel;
	Title* m_pTitle;
	Pluginloader* m_pPluginloader;
	QVariantMap m_pluginMap;
	MapBaseInterface* m_pMapBase;

	QPoint m_PressPoint;
};

#endif // IOBJECTSDEMO_H
