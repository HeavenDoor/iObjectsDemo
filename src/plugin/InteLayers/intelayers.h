#ifndef INTELAYERS_H
#define INTELAYERS_H

#include "intelayers_global.h"
#include "intelayersinterface.h"
#include "tabwidget.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
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
	virtual QWidget* getWidget();

private slots:
	void OnInteLayersCollapse();
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private:
	QVBoxLayout* m_pVLayout;
	QWidget* m_pHead;
	//QWidget* m_pTab;
	QPushButton* m_pCloseBtn;
	TabWidget* m_pTabWidget;



	static const int timespan = 400;
	QPropertyAnimation *m_pProAnima;
};

#endif // INTELAYERS_H
