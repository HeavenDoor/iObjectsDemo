#ifndef TABBAR_H
#define TABBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QVector>
#include "tabitem.h"

class TabBar : public QWidget
{
	Q_OBJECT

public:
	TabBar(QWidget *parent);
	~TabBar();
	void insertTabbar(int index, QString tabName);
	void removeTabbar(int index);
	void setCurrentIndex(int index);
	int tabCount();
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);

	void	dragEnterEvent(QDragEnterEvent * event) Q_DECL_OVERRIDE;
	void	dragLeaveEvent(QDragLeaveEvent * event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event);


	void mouseReleaseEvent(QMouseEvent *event);

	bool eventFilter(QObject *, QEvent *);
signals:
	void changeIndex(int index);
	void moveTabPage(int index, QString tabName);
private slots:
	void OnTabButtonClicked();
	void OnactionChanged(Qt::DropAction act);
private:
	QHBoxLayout* m_pHlayout;
	TabItem* m_pPrevBtn;
	QVector<TabItem*> m_pTabBarList;
	bool press;
	bool move;
	QDrag *m_drag;
	QByteArray itemData;
	QPainter *painter;
};

#endif // TABBAR_H
