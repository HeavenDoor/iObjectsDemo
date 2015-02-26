//////////////////////////////////////////////////////////////////////////
// MapBase��������Խӿ�                   
//////////////////////////////////////////////////////////////////////////
#ifndef MAPBASEINTERFACE_H
#define MAPBASEINTERFACE_H


#include <QObject>
#include <QtWidgets/QWidget>
#include "widgetplugininterface.h"

class MapBaseInterface : public WidgetPluginInterface
{
public:
	virtual void test() = 0;
	// UGMapEditorWnd�����ָ��Ļ�ȡ
	virtual void* getUGMapEditorWnd() = 0;
	// ���MapBase����������ָ�룬��Ϊ������Tabҳ����ʾ
	virtual QWidget* getWidget() = 0;   
	// ���MapBase�����MapLayers�ؼ�ָ�룬�������������ִ���
	virtual QWidget* getMapLayers() = 0;
	// ���MapBase���MapController�ؼ�ָ��
	virtual QWidget* getMapController() = 0;
};


QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(MapBaseInterface, "{D1B7D4F8-A0E7-42B8-AE6A-DAF3122D6EB8}")
QT_END_NAMESPACE

#endif