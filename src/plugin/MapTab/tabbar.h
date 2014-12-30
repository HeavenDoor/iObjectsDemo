#ifndef TABBAR_H
#define TABBAR_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>

class TabBar : public QWidget
{
	Q_OBJECT

public:
	TabBar(QWidget *parent);
	~TabBar();

protected:
	void paintEvent(QPaintEvent*);
signals:
	void changeDimension(bool isTwoDimension);
	//void changeToThreeDimension();
private slots:
	void OnTabButtonClicked();
private:
	QHBoxLayout* m_pHlayout;
	QToolButton* m_pTwoBtn;
	QToolButton* m_pThreeBtn;
};

#endif // TABBAR_H
