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
signals:
	void changeIndex(int index);
private slots:
	void OnTabButtonClicked();
private:
	QHBoxLayout* m_pHlayout;
	TabItem* m_pPrevBtn;
	QVector<TabItem*> m_pTabBarList;
};

#endif // TABBAR_H
