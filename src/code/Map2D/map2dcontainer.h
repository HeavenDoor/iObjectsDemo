#ifndef MAP2DCONTAINER_H
#define MAP2DCONTAINER_H

#include "mapcontrol.h"
#include "map2dcontroller.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>


class Map2DContainer : public QWidget
{
	Q_OBJECT

public:
	Map2DContainer(QWidget *parent = NULL);
	~Map2DContainer();
	QString getMapUrl() const;
	QVector<QString> getLayers() const;
protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
signals:
	void showLayers(QVector<QString> s);
private slots:
	void onclicked();
	void OnSelectClicked();
	void OnPanClicked();
	void OnEntireClicked();
	void OnZoomInClicked();
	void OnZoomOutClicked();
private:
	QString m_MapUrl;
	QVector<QString> m_Layers;
	QHBoxLayout* m_pMap2DLayout;
	MapControl* m_pMapControl;
	Map2DController* m_pMap2DController;
};

#endif // MAP2DCONTAINER_H
