#ifndef MAP2DCONTAINER_H
#define MAP2DCONTAINER_H

#include "mapcontrol.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>


class Map2DContainer : public QWidget
{
	Q_OBJECT

public:
	Map2DContainer(QWidget *parent = NULL);
	~Map2DContainer();
protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
private slots:
	void onclicked();
private:
	QHBoxLayout* m_pMap2DLayout;
	MapControl* m_pMapControl;
};

#endif // MAP2DCONTAINER_H
