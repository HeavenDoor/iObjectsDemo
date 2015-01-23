#ifndef XMLUTILS_H
#define XMLUTILS_H
#include <QObject>
#include <QList>
#include <QHash>
#include <QVariant>
#include <QMap>
#include <QString>
#include <QStringList>

class XmlUtils : public QObject
{
	Q_OBJECT
public slots:
	static QList<QHash<QString,QString>> readXml(QString fileName);
	static QVariantList ReadXml(QString fileName);

public:
	virtual ~XmlUtils(){}
};

#endif