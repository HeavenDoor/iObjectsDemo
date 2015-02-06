//////////////////////////////////////////////////////////////////////////
// Í¼²ãÁÐ±í¿Ø¼þ       
//////////////////////////////////////////////////////////////////////////

#ifndef INTELAYERS_H
#define INTELAYERS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QPropertyAnimation>

class InteLayers : public QWidget
{
	Q_OBJECT
public:
	InteLayers(QWidget* parent = NULL);
	~InteLayers();
	void setInteLayersHeight(int height);
	void setInteLayersWidth(int width);
	int InteLayersHeight();
	int InteLayersWidth();

	void addLayers(QWidget* layers);
	void removeLayers(QWidget* layers);
signals:
	void refeshWindow();
	private slots:
	void OnInteLayersCollapse();
	void OnInteLayersExpand();
	void OnAnimationFinished();
	bool eventFilter(QObject*, QEvent*);
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
	void	moveEvent(QMoveEvent*);
private:
	QVBoxLayout* m_pVLayout;
	QWidget* m_pHead;
	//QWidget* m_pTab;
	QPushButton* m_pCloseBtn;
	QWidget* m_pTabWidget;
	QWidget* m_pBody;
	QPushButton* m_pCollapseBtn;
	static const int timespan = 250;
	QPropertyAnimation *m_pProAnima;
	int m_width;
	int m_height;
};

#endif // INTELAYERS_H
