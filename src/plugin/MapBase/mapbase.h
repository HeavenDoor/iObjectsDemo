#ifndef MAPBASE_H
#define MAPBASE_H

#include "mapbase_global.h"
#include "..\\..\\interface\mapbaseinterface.h"

#include "mapcontrol.h"
#include "mapcontroller.h"
#include "maplayers.h"
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QVariantMap>

class MapBase : public QWidget, MapBaseInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{B0585DCB-DB60-49AA-9993-053203B1F53A}" FILE "mapbase.json")
	Q_INTERFACES(MapBaseInterface)
public:
	MapBase(QWidget *parent = NULL);
	~MapBase();

	virtual void test();

	virtual QObject* getObject();
	virtual void setPluginGeometry(const QRect& rect);
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah);
	virtual void setPluginParent(QWidget* parentWidget);
	virtual void showPlugin();
	virtual void raisePlugin();
	virtual void lowerPlugin();
	virtual void resizePlugin(int ax, int ay, int aw, int ah);
	virtual void setPluginWidth(int width);
	virtual void setPluginHeight(int height);
	virtual int pluginWidth();
	virtual int pluginHeight();

	//virtual void loadSkin();
	virtual void* getUGMapEditorWnd();
	virtual QWidget* getWidget();
	virtual QWidget* getMapLayers();
	virtual QWidget* getMapController();
	virtual QString getStyleSheet();
public:

	QString getMapUrl() const;
	/*QVector<QString>*/QVector<QVariantList> getLayers() const;
protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
signals:
	//void showLayers(QVector<QString> s);
	void showTips();
private slots:
 	void OnSelectClicked();
 	void OnPanClicked();
 	void OnEntireClicked();
 	void OnZoomInClicked();
 	void OnZoomOutClicked();
	void OnChangeLayers(const QString& text, int index);
private slots:
private:

	QString m_MapUrl;
	/*QVector<QString>*/QVector<QVariantList> m_Layers;
	QHBoxLayout* m_pMap2DLayout;
	MapControl* m_pMapControl;
	MapController* m_pMapController;
	MapLayers* m_pMapLayers;
	static const int tabrwidth = 81;
	

};

#endif // MAPBASE_H
