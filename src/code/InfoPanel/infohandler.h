#ifndef INFOHANDLER_H
#define INFOHANDLER_H

#include <QObject>
#include <QtWidgets/QWidget>
#include <QTimer>
#include "..\\..\\commom\xmlutils.h"

class InfoHandler : public QObject
{
	Q_OBJECT

public:
	InfoHandler(QWidget *parent = NULL);
	~InfoHandler();
	void run();
protected:
	void timerEvent(QTimerEvent *);

signals:
	void infoChanged(const QString& info);
private slots:
	void Ontimeout();
private:
	QTimer* m_pTimer;
	QVariantList list;
	int index;
};

#endif // INFOHANDLER_H
