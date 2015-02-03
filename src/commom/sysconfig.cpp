#include "stdafx.h"
#include "sysconfig.h"
#include <QtWidgets/QApplication>

QSettings* SysConfig::m_sysSetting = NULL;

SysConfig::SysConfig(QObject *parent) : QObject(parent)
{

}

SysConfig::~SysConfig()
{

}

QVariant SysConfig::getValue(const QString &key)
{
//	QString s = QApplication::applicationDirPath() + "/System.cfg";
	if(!m_sysSetting)
		m_sysSetting = new QSettings(QApplication::applicationDirPath() + "/System.cfg", QSettings::IniFormat);
// 	QVariant v = m_sysSetting->value(key);
// 	qDebug()<<v;
// 	int m = GetLastError();
	return m_sysSetting->value(key);
}

void SysConfig::setValue(const QString &key, const QVariant& value)
{	
	if(!m_sysSetting)
		m_sysSetting = new QSettings(QApplication::applicationDirPath() + "/System.cfg", QSettings::IniFormat);
	m_sysSetting->setValue(key, value);
}