#include "stdafx.h"
#include "xmlutils.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

QList<QHash<QString,QString>> XmlUtils::readXml(QString fileName)
{
	QFile xmlFile(fileName);
	QDomDocument doc;
	QList<QHash<QString,QString>> list;
	QHash<QString,QString> hash;

	if (!xmlFile.open(QIODevice::ReadOnly))
	{
		return list;
	}
	if (!doc.setContent(&xmlFile))
	{
		xmlFile.close();
		return list;
	}
	QDomElement root = doc.documentElement();
	QDomNodeList item = root.childNodes();
	list.clear();
	hash.clear();
	for (int i = 0; i < item.size(); ++i)
	{
		QDomNodeList node = item.at(i).childNodes();
		for (int j = 0; j < node.size(); ++j)
		{
			hash.insert(node.at(j).nodeName(), node.at(j).toElement().text());
		}
		list.append(hash);
		hash.clear();
	}
	return list;
}

QVariantList XmlUtils::ReadXml(QString fileName)
{
	QVariantList mapList;
	QList<QHash<QString, QString>> hashList = readXml(fileName);
	if (hashList.length()<1)
	{
		return mapList;
	}
	QStringList keys;
	for (int i = 0; i < hashList.size(); ++i)
	{
		QHash<QString, QString> hashtemp;
		QMap<QString, QVariant> maptemp;
		hashtemp = hashList.at(i);
		keys = hashtemp.keys();
		for (int j = 0; j < hashtemp.size(); ++j)
		{
			maptemp.insert(keys[j], hashtemp.value(keys[j]));
		}
		mapList.append(maptemp);
	}

	return mapList;
}