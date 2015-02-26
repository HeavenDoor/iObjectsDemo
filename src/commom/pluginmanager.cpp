#include "stdafx.h"
#include "pluginmanager.h"
#include "sysconfig.h"
#include "fileutils.h"

PluginManager* PluginManager::m_pManager = NULL;

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{

}

PluginManager::~PluginManager()
{

}

PluginManager* PluginManager::instance()
{
	if (!m_pManager)
	{
		m_pManager = new PluginManager();
	}
	return m_pManager;
}


bool PluginManager::getInfoPanel()
{
	return SysConfig::getValue("InfoPanel").toBool();
}

void PluginManager::setInfoPanel(bool value)
{
	SysConfig::setValue("InfoPanel", value);
}

bool PluginManager::getInteLayers()
{
	return SysConfig::getValue("InteLayers").toBool();
}

void PluginManager::setInteLayers(bool value)
{
	SysConfig::setValue("InteLayers", value);
}

bool PluginManager::getMapTab()
{
	return SysConfig::getValue("MapTab").toBool();
}

void PluginManager::setMapTab(bool value)
{
	SysConfig::setValue("MapTab", value);
}

bool PluginManager::getToolBox()
{
	return SysConfig::getValue("ToolBox").toBool();
}

void PluginManager::setToolBox(bool value)
{
	SysConfig::setValue("ToolBox", value);
}

void PluginManager::setPluginValueByName( const QString& name, const bool& value )
{
	m_pluginMap.insert(name, value);
	SysConfig::setValue(name, value);
}

bool PluginManager::getPluginValueByName( const QString& name )
{
	return SysConfig::getValue(name).toBool();
}

QVariantMap PluginManager::getPluginMap()
{
	return m_pluginMap;
}

void PluginManager::insertPluginItem( const QString& name, const bool& value )
{
	m_pluginMap.remove(name);
	m_pluginMap.insert(name, value);
}

QVariantMap PluginManager::getDefaultPluginMap()
{
	QStringList pluginList = FileUtils::getAllFileByExtensionsName("pluginspec", "../plugins");
	for(int i = 0; i < pluginList.length(); i++)
	{
		QString plugiName = pluginList.at(i);
		bool m = SysConfig::getValue(plugiName).toBool();
		insertPluginItem(plugiName, SysConfig::getValue(plugiName).toBool());
	}

	return m_pluginMap;
}
