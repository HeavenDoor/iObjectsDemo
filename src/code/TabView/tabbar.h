#ifndef TABBAR_H
#define TABBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QVector>

class TabBar : public QWidget
{
	Q_OBJECT

public:
	TabBar(QWidget *parent);
	~TabBar();
	void insertTabbar(int index, QString tabName);
	void setCurrentIndex(int index);
	int tabCount();
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
signals:
	void changeIndex(int index);
	//void changeToThreeDimension();
private slots:
	void OnTabButtonClicked();
private:
	QHBoxLayout* m_pHlayout;
	QToolButton* m_pPrevBtn;
	QVector<QToolButton*> m_pTabBarList;
};

#endif // TABBAR_H
