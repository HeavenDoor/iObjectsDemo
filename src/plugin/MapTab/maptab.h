#ifndef MAPTAB_H
#define MAPTAB_H

#include "maptab_global.h"
#include "maptabinterface.h"
#include "tabbar.h"
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class MapTab : public QWidget , MapTabInterface
{
	Q_OBJECT
		Q_PLUGIN_METADATA(IID "{38E64368-2917-4426-8E1B-CC9D72250A25}" FILE "maptab.json")
		Q_INTERFACES(MapTabInterface)
public:
	MapTab(QWidget *parent = 0);
	~MapTab();

	virtual void test();
	//virtual QWidget* getWidget();

	virtual QObject* getObject();
	virtual void setPluginGeometry(const QRect& rect);
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah);
	virtual void setPluginParent(QWidget* parentWidget);
	virtual void showPlugin();
	virtual void raisePlugin();
	virtual void resizePlugin(int ax, int ay, int aw, int ah);


protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private slots:
	void OnChangeDimension(bool isTwoDimension);
	//void OnChangeToThreeDimension();
private:
	QTabWidget* m_pTabWidget;
	TabBar* m_pTabBar;
	QWidget* m_pTwoDimension;
	QWidget* m_pThreeDimension;
};

#endif // MAPTAB_H
