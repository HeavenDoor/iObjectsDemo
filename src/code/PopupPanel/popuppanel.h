#ifndef POPUPPANEL_H
#define POPUPPANEL_H

#include <QtWidgets/QWidget>

class PopupPanel : public QWidget
{
	Q_OBJECT

public:
	PopupPanel(QWidget *parent = NULL);
	~PopupPanel();
protected:
	void paintEvent(QPaintEvent *);
private:
	
};

#endif // POPUPPANEL_H
