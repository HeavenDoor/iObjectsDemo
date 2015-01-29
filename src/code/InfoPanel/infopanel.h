#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "infohandler.h"
#include "..\\..\\commom\widgetrect.h"

#include <QtWidgets/QWidget>
#include <QtQml/QQmlExtensionPlugin>
#include <QtQml/qqml.h>
#include <QtQml/QQmlContext>
#include <QtQuickWidgets/QQuickWidget>
#include <QPropertyAnimation>

class InfoPanel : public QQuickWidget
{
	Q_OBJECT

public:
	InfoPanel(QWidget* parent = NULL);
	~InfoPanel();
	
	void setPluginWidth(int width);
	void setPluginHeight(int height);
	int pluginWidth();
	int pluginHeight();
	// 设置动画时长
	void setAnimationTimespan(int timespan);
	bool IsExpandBtnVisible();
	int getExpandBtnWidth();
	int getExpandBtnHeight();
private:
	void registerTypes(const char *uri);
private slots:
	void collapseWnd();
	void expandWnd();	
	void OnAnimationFinished();
	bool eventFilter(QObject*, QEvent*);
private:
	int m_timespan;
	QPropertyAnimation *m_pProAnima;
	QObject * m_pExpandBtn;
	QObject * m_pRoot;
	int m_width;
	int m_height;
};

#endif // INFOPANEL_H
