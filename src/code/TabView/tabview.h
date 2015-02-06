//////////////////////////////////////////////////////////////////////////
// TabView控件
// 把插件界面作为Tab页面显示
//////////////////////////////////////////////////////////////////////////


#ifndef TABVIEW_H
#define TABVIEW_H

#include "tabbar.h"
#include "tabwidget.h"
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class TabView : public QWidget
{
	Q_OBJECT
public:
	TabView(QWidget *parent = NULL);
	~TabView();

	// 添加页面 map： 界面指针  tabIndex：页面顺序 从0开始（< 0 时在最前） tabName：显示在TabBar上的名称
	void addCentralWidget(QWidget* map, int tabIndex, QString tabName);
	// 删除页面
	void removeCentralWidget(QWidget* widget);
	// 设置当前选中页面
	void setCurrentIndex(int index); 
	// 加载皮肤
	void loadDefaultSkin();
	// 加载自定义皮肤  styleSheet：qss字符串
	void loadCustomStyleSheet(const QString& styleSheet);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private slots:
	void OnChangeIndex(int index);
private:
	static const int tabrwidth = 81;
	TabWidget* m_pTabWidget;
	TabBar* m_pTabBar;
	
};

#endif // TABVIEW_H
