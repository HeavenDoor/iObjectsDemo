#ifndef MIRRORPANEL_H
#define MIRRORPANEL_H

#include <QtWidgets/QWidget>

#include "..\TabView\tabview.h"
#include "..\tabbarpanel.h"

class MirrorPanel : public QWidget
{
	Q_OBJECT

public:
	MirrorPanel(QWidget *parent = NULL);
	~MirrorPanel();
	TabView* getTabView();
	TabBarPanel* getTabBarPanel();
protected:
	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *e);
	void closeEvent(QCloseEvent *e);
private:
	TabView* m_pTabView;
	TabBarPanel* m_pTabBarPanel;
};

#endif // MIRRORPANEL_H
