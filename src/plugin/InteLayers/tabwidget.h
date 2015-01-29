#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QScrollArea>

class TabWidget : public QWidget
{
	Q_OBJECT

public:
	TabWidget(QWidget *parent);
	~TabWidget();
	void addTabPage(QVector<QString> vec);
protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent*);

private slots:
	void OnTabButtonClicked();

private:
	
	QHBoxLayout* m_pHLayout;
	QWidget* m_pTabBar;
	QTabWidget* m_pTabWidget;
	

	QVBoxLayout* m_pVLayout;
	QVBoxLayout* m_pVLayout2;
	QVBoxLayout* m_pVLayout3;

	QWidget* m_pOne;
	QWidget* m_pTwo;
	QWidget* m_pThree;

	QToolButton* m_pBtn1;
	QToolButton* m_pBtn2;
	QToolButton* m_pBtn3;


	QWidget* m_a;
	QWidget* m_b; 
	QWidget*m_c;
	QWidget*m_d;
	QWidget*m_e;
	QWidget*m_f;

	QWidget* m_g;
	QWidget* m_h;
	QWidget* m_i;
	QWidget* m_j;

	QWidget* m_k;
	QWidget* m_l;


	QScrollArea* scroll;
	QWidget* a ;
};

#endif // TABWIDGET_H
