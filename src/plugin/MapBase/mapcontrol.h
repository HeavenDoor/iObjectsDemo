#ifndef SHENGHAI_H_
#define SHENGHAI_H_

#include <QtWidgets/QWidget>
#include<QtWidgets/QLabel>
//#include <QGLWidget>

#include <vector>
#include <QPointF>


#include "Base/OgdcPoint2D.h"

#include "Engine/UGQueryDef.h"
#include "Engine/UGRecordset.h"
#include "Engine/UGDatasetVector.h"

#include "Graphics/UGGraphics.h"
#include "Graphics/UGImage.h"
#include "Graphics/UGGraphicsManager.h"

#include "Geometry/UGGeoLine.h"
#include "Geometry/UGGeoPoint.h"

#include "Projection/UGPrjCoordSys.h"

#include "MapEditor/UGMapEditorWnd.h"
#include "Map/UGLayer.h"

#include "Workspace/UGWorkspace.h"

#include "FileParser/UGExchangeParamsManager.h"
#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGFileParseToolkit.h"

using namespace OGDC;
namespace UGC
{
	class UGGraphics;
	class UGImage;
	class UGWorkspace;
	class UGMapEditorWnd;
	class UGMap;
	class UGGeoLine;
}
using namespace UGC;

//绘图控件类
class MapControl : public QWidget
{
	Q_OBJECT

public:
	MapControl(QWidget* parent = 0);
	~MapControl();
    
	//重写绘制函数
	virtual void paintEvent( QPaintEvent* event );

	//重写鼠标滚轮函数
	virtual void wheelEvent( QWheelEvent* event );
	
	//重写鼠标按下函数
	virtual void mousePressEvent ( QMouseEvent* event );
	
	// 重写鼠标弹起函数
	virtual void mouseReleaseEvent ( QMouseEvent* event );
	
	//重写鼠标移动函数	
	virtual void mouseMoveEvent ( QMouseEvent* event );
	
	//重写当窗口大小发生改变时函数
	virtual void resizeEvent ( QResizeEvent* event );

public:
	//打开地图方法
	int OpenMap(const QString& mapPath);
	//显示距离
	void ShowMessureResult(QString mType);

	//量测距离
	void CalcuLength();
	// 刷新地图
	virtual void Refresh();

	//地图漫游拖动
	virtual void Pan();

	//地图放大
	virtual void ZoomIn();

	//地图缩小
	virtual void ZoomOut();

	//鼠标指针状态，恢复当前鼠标操作
	virtual void Select();

    //全幅
	void ViewEntire();

	//释放占用资源
	virtual void Release();

	//初始化接口
	virtual void Init();

	void OnMapDrawn(UGGraphics* pGraphics);

    UGString  QStringToUGString(QString qstring );

	void openLayers(const QString& text);
public:
	QVector<QString> getLayersList();
public:

	int m_MessureType;
	QLabel* m_MessageLabel;

signals:
	//绘制地图信号
	void UGMapDrawnEvent(MapControl* pQMap, UGGraphics* pGraphics);


private:	
	UGMap& GetMap();

	//改变光标方法
	void ReviseCursor();

	//设置等待光标
	void SetWaitCursor();

	void CreateUGGrpaphics(UGGraphics* &pGraphics);

	void ReleaseUGGraphics(UGGraphics* &pGraphics);

	void PaintToQPainter();

	void Invalidate();

	//屏幕坐标转成地图坐标
	UGPoint2D PixelToMap(const QPoint &point);

	//地图坐标转成屏幕坐标
	QPointF MapToPixel(const UGPoint2D &point2D);

	//获取当前工作空间
	UGWorkspace* GetWorkspace(); 

	//获取当前
	UGMapEditorWnd* GetUGMapWnd();

private:
	UGC::UGMapEditorWnd* m_pMapEditorWnd;   

	UGC::UGWorkspace* m_pWorkspace;

	UGImage* m_pMapImage;
	UGImage* m_pOldImage;

	int m_width;
	int m_height;

	QPoint m_pressPoint;
	QPoint m_dragPoint;

	double m_defaultScale;
	UGPoint2D m_defaultCenter;

	bool m_invalidate;
	bool m_initialized;
	
	QImage* m_pQimage;
};


#endif
