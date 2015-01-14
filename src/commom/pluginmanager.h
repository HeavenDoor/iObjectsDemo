#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>

class PluginManager : public QObject
{
	Q_OBJECT

public:
	~PluginManager();
	static PluginManager* instance();
	
	bool getPluginValueByName(const QString& name);
	void setPluginValueByName(const QString& name, const bool& value);
	QVariantMap getPluginMap();
	void insertPluginItem(const QString& name, const bool& value);
private:
	PluginManager(QObject *parent = NULL);

	bool getInfoPanel();
	void setInfoPanel(bool value);
	bool getInteLayers();
	void setInteLayers(bool value);
	bool getMapTab();
	void setMapTab(bool value);
	bool getToolBox();
	void setToolBox(bool value);
private:
	static PluginManager* m_pManager;
	QVariantMap m_pluginMap;
};

#endif // PLUGINMANAGER_H
