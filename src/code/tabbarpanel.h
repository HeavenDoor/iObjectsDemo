#ifndef TABBARPANEL_H
#define TABBARPANEL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

class TabBarPanel : public QWidget
{
	Q_OBJECT

public:
	TabBarPanel(QWidget *parent = NULL);
	~TabBarPanel();
	void addTabBarWidget(QWidget* w);
	void addTrigerWidget(QWidget* w);
private:
	QVBoxLayout* m_pMainLayout;
	QVBoxLayout* m_pTabLayout;
	QVBoxLayout* m_pTigerLayout;
};

#endif // TABBARPANEL_H
