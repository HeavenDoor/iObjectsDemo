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

	void addCentralWidget(QWidget* map, int tabIndex, QString tabName);
	void setCurrentIndex(int index);
	void loadDefaultSkin();
	void loadCustomStyleSheet(const QString& styleSheet);

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private slots:
	void OnChangeIndex(int index);
	//void OnChangeToThreeDimension();
private:
	static const int tabrwidth = 81;
	TabWidget* m_pTabWidget;
	TabBar* m_pTabBar;
	
};

#endif // TABVIEW_H
