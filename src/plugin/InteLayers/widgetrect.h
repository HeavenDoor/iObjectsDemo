#ifndef WIDGETRECT_H
#define WIDGETRECT_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QRect>

class WidgetRect : public QObject
{
	Q_OBJECT

public:
	WidgetRect();
	~WidgetRect();
public:
	static QRect widgetGlobalRect(const QWidget* widget);

private:
	
};

#endif // WIDGETRECT_H
