#ifndef TITLE_H
#define TITLE_H

#include <QObject>

class Title : public QWidget
{
	Q_OBJECT

public:
	Title(QWidget *parent);
	~Title();
	
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent *);
	void moveEvent(QMoveEvent *);
signals:
	void collapse();
public slots:
	void expandTitle(); // 展开
	void packupTitle(); // 收起
private slots:
	void tt();
	void OnAnimationFinished();
private:
	static const int timespan = 400;
	QPushButton* m_pCollapseBtn;
	QPropertyAnimation *m_pProAnima;
};

#endif // TITLE_H
