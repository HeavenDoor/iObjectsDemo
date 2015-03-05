#ifndef PROPERTYTRIGGER_H
#define PROPERTYTRIGGER_H

#include <QWidget>

class PropertyTrigger : public QWidget
{
	Q_OBJECT

public:
	PropertyTrigger(QWidget *parent = NULL);
	~PropertyTrigger();
	void setText(QString t);
	void init();
	int getWidth();
signals:
	void tirggered();
protected:
	void mousePressEvent(QMouseEvent *e);
private:
	QString m_text;
	int m_width;
};

#endif // PROPERTYTRIGGER_H
