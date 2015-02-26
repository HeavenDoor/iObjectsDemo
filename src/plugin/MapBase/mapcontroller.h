#ifndef MAP2DCONTROLLER_H
#define MAP2DCONTROLLER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
class MapController : public QWidget
{
	Q_OBJECT

public:
	MapController(QWidget *parent);
	~MapController();
protected:
	void paintEvent( QPaintEvent * e);
	void resizeEvent(QResizeEvent *);
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
