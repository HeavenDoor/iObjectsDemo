#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <QObject>
#include <QSettings>
#include <QVariant>

class SysConfig : public QObject
{
	Q_OBJECT

public:
	SysConfig(QObject *parent = NULL);
	~SysConfig();
	static QVariant getValue(const QString &key);
	static void setValue(const QString &key, const QVariant& value);
private:
	static QSettings* m_sysSetting;
	
};

#endif // SYSCONFIG_H
