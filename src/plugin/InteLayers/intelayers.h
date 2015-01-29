#ifndef INTELAYERS_H
#define INTELAYERS_H

#include "intelayers_global.h"
#include "..\\..\\interface\\intelayersinterface.h"
#include "tabwidget.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QPropertyAnimation>

class InteLayers : public QWidget, InteLayersInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{FAC5AA17-0400-4FFC-8949-208D1E1392CE}" FILE "intelayers.json")
	Q_INTERFACES(InteLayersInterface)
public:
	InteLayers(QWidget* parent = NULL);
	~InteLayers();
	virtual void test();
	//virtual QWidget* getWidget();
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

	virtual void addTabPage(QVector<QString> vec);
signals:
	void refeshWindow();
private slots:
	void OnInteLayersCollapse();
	void OnInteLayersExpand();
	void OnAnimationFinished();
	bool eventFilter(QObject*, QEvent*);
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void	moveEvent(QMoveEvent*);
private:
	QVBoxLayout* m_pVLayout;
	QWidget* m_pHead;
	//QWidget* m_pTab;
	QPushButton* m_pCloseBtn;
	TabWidget* m_pTabWidget;
	QPushButton* m_pCollapseBtn;
	static const int timespan = 250;
	QPropertyAnimation *m_pProAnima;
	int m_width;
	int m_height;
};

#endif // INTELAYERS_H
