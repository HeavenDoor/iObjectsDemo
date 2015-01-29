#ifndef MAP2DCONTROLLER_H
#define MAP2DCONTROLLER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
class Map2DController : public QWidget
{
	Q_OBJECT

public:
	Map2DController(QWidget *parent);
	~Map2DController();
protected:
	void paintEvent( QPaintEvent * e);
signals:
	void selectClicked();
	void panClicked();
	void entireClicked();
	void zoominClicked();
	void zoomoutClicked();
private:
	QHBoxLayout* m_pHboxLayout;
	QToolButton* m_pSelect;
	QToolButton* m_pPan;
	QToolButton* m_pEntire;
	QToolButton* m_pZoomIn;
	QToolButton* m_pZoomOut;
};

#endif // MAP2DCONTROLLER_H
