#include "stdafx.h"
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include <QVector>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QApplication>
#include "mapcontrol.h"
		
using namespace UGC;

// 获取移动过程中的值
void UGSTDCALL TrackingCallBack(UGlong pWnd, UGdouble dx, UGdouble dy, UGint nButtonClicked, UGdouble dCurrentLength, UGdouble dCurrentAngle, UGdouble dAzimuth, UGdouble dTotalLength, UGdouble dTotalArea)
{
	MapControl* pControl = (MapControl*)pWnd;
	QString showString;
	switch(pControl->m_MessureType)
	{
		case 0:
		{
			showString.append(QString::fromUtf8("距离:"));
			showString.append(QString::number(dTotalLength/1000, 'g', 4));
			showString.append(QString::fromUtf8("公里"));

		}
		break;
		case 1:
		{
			showString.append(QString::fromUtf8("面积:"));
			showString.append(QString::number(dTotalArea/1000000, 'g', 4));
			showString.append(QString::fromUtf8("平方公里"));

		}
		break;
		case 2:
		{
			showString.append(QString::fromUtf8("方位角:"));
			showString.append(QString::number(dAzimuth, 'g', 4));
			showString.append(QString::fromUtf8("°"));
		}
		break;
		default:
		break;
	}

	pControl->m_MessageLabel->setText(showString);
}

void UGSTDCALL AfterTrackingLayerCallBack(UGlong pWnd, UGGraphics* pGraphics)
{
	MapControl* pQMap = (MapControl*)pWnd;
	pQMap->OnMapDrawn(pGraphics);
}

void UGSTDCALL TrackedCallBack(UGlong pWnd)
{
	MapControl* pControl = (MapControl*)pWnd;
	QString str = QString("距离:%1").arg(QString::number(0, 'g', 4));
}

UGC::UGuint GetUGKeyflagMasks(QInputEvent* event)
{
	UGC::UGuint flag = 0;

	if (event->modifiers() & Qt::ShiftModifier)
	{
		flag = flag | UG_MK_SHIFT;
	}
	if ((event->modifiers() & Qt::ControlModifier))
	{
		flag = flag | UG_MK_CONTROL;
	}
	return flag;
}

void UGSTDCALL MapDrawnCallBack_QMap(UGlong pWnd, UGGraphics* pGraphics)
{
	MapControl* pQMap = (MapControl*)pWnd;
	pQMap->OnMapDrawn(pGraphics);
}

void UGSTDCALL MapSingleGeometrySelectedCallBack(UGlong pWnd,UGLayer* pLayer,UGint nGeoID)
{
	MapControl* pQMap = (MapControl*)pWnd;
	//pQMap->OnMapDrawn(pGraphics);
}

void UGSTDCALL GeometrySelectedProcCallBack(UGlong pWnd,UGint nSelectedGeometryCount)
{
	MapControl* pQMap = (MapControl*)pWnd;
	if (pQMap && nSelectedGeometryCount == 1)
	{
		pQMap->popupTips();
	}

	const UGStyle&s = pQMap->getstyle(pQMap);
	pQMap->emitStyleChanged(s);
}

const UGStyle& MapControl::getstyle(MapControl* p)
{
	return p->GetUGMapWnd()->GetDefaultStyle();
}

void MapControl::emitStyleChanged(const UGStyle&s)
{
	emit UGStyleChanged(s);
}

MapControl::MapControl( QWidget* parent)
{

	m_width = this->width();
	m_height = this->height();
	m_pWorkspace = NULL;
	m_pMapEditorWnd = NULL;
	m_pMapImage = NULL; 
	m_invalidate = FALSE;
	m_initialized = FALSE;
	m_pQimage = NULL;
	m_MessageLabel = NULL;

	this->Init();
}

MapControl::~MapControl()
{
	this->Release();
}

void MapControl::ViewEntire()
{
	m_pMapEditorWnd->ViewEntire();

    this->Refresh();
}

void MapControl::Init()
{
	this->setMouseTracking(true);

	UGGraphicsManager::SetCurGraphicsType(UGGraphics::GT_Windows);

	m_pMapEditorWnd = new UGMapEditorWnd();

	m_pMapEditorWnd->Initialize();
	m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaPointModeSelect); //uaPointModeSelectTrue 
	m_pMapEditorWnd->m_mapWnd.SetAfterMapDrawFunc(MapDrawnCallBack_QMap, (UGlong)this);
	m_pMapEditorWnd->SetTrackingFunc(TrackingCallBack, (UGlong)this);
	m_pMapEditorWnd->SetTrackedFunc(TrackedCallBack, (UGlong)this);

	m_pMapEditorWnd->SetSingleGeometrySelectedFunc(MapSingleGeometrySelectedCallBack, (UGlong)this);
	m_pMapEditorWnd->SetGeometrySelectedFunc(GeometrySelectedProcCallBack, (UGlong)this);

	m_pWorkspace = new UGWorkspace;
}

void MapControl::paintEvent( QPaintEvent* event )
{
	if (m_invalidate)
	{
		m_invalidate = FALSE;
		SetWaitCursor();

		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);

		UGRect rcInvalid(0, 0, m_width, m_height);
		m_pMapEditorWnd->OnDraw(pGraphics, rcInvalid, rcInvalid, false, false);

		ReleaseUGGraphics(pGraphics);

		ReviseCursor();
	}

	PaintToQPainter();
}

void MapControl::SetWaitCursor()
{
	static QCursor wait(Qt::WaitCursor);
	this->setCursor(wait);
}

void MapControl::ReviseCursor()
{
	switch(m_pMapEditorWnd->m_mapWnd.GetCursorShape())
	{
	case UGC::UGMapWnd::ecBusy :
		{
			SetWaitCursor();
			break;
		}
	case UGC::UGMapWnd::ecArrow:
		{
			setCursor(QCursor(Qt::ArrowCursor));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanLeft:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_left.png"), 0, 15));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanRight:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_right.png"), 30, 10));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanTop:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_top.png"),10, 0));	
			break;
		}
	case UGC::UGMapWnd::ecMarginPanBottom:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_bottom.png"), 10, 30));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanTopLeft:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_topleft.png"), 0, 0));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanTopRight:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_topright.png"), 30, 0));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanBottomRight:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_bottomright.png"), 30, 30));
			break;
		}
	case UGC::UGMapWnd::ecMarginPanBottomLeft:
		{
			setCursor(QCursor(QPixmap(":/Resources/Pan_bottomleft.png"), 0, 30));
			break;
		}
	case UGC::UGMapWnd::ecZoomFree:
	case UGC::UGMapWnd::ecZoomFree2:
		{
			setCursor(QCursor(QPixmap(":/Resources/ZoomFree.png")));
			break;
		}
	case UGC::UGMapWnd::ecPan:
		{
			setCursor(QCursor(QPixmap(":/Pan.png")));
			break;
		}
	case UGC::UGMapWnd::ecPan2:
		{
			setCursor(QCursor(QPixmap(":/Pan.png")));
			break;
		}
	case UGC::UGMapWnd::ecZoomIn:
		{
			setCursor(QCursor(QPixmap(":/Zoomin.png"), 2, 2));
			break;
		}
	case UGC::UGMapWnd::ecZoomOut:
		{
			setCursor(QCursor(QPixmap(":/Zoomout.png"), 2, 2));
			break;
		}
	case UGC::UGMapWnd::ecPointModeSelect:
	case UGC::UGMapWnd::ecPointModeSelectTrue:
	case UGC::UGMapWnd::ecRectModeSelect:
	case UGC::UGMapWnd::ecLineModeSelect:
		{
			setCursor(QCursor(QPixmap(":/select.png"), 4, 4));
			break;
		}	
	case UGC::UGMapWnd::ecDrawPolyGon:
	case UGC::UGMapWnd::ecDrawPolyLine:

		{
			setCursor(QCursor(QPixmap(":/Resources/Length.png"), 8, 8));
			break;
		}
	case UGC::UGMapWnd::ecDrawText:
		{
			setCursor(QCursor(Qt::IBeamCursor));
			break;
		}
	default:
		break;
	}
}

QPointF MapControl::MapToPixel(const OgdcPoint2D &point2D)
{
	UGMap& map = this->GetMap();
	UGPoint pt(0, 0);

	map.GetDrawing()->m_DrawParam.MPtoLP(point2D, pt);

	UGDrawCache &drawing = map.GetDrawing()->m_DrawCache;	
	
	drawing.LPtoDP(&pt, 1);

	return QPointF(pt.x, pt.y);
}

OgdcPoint2D MapControl::PixelToMap(const QPoint &point)
{
	UGMap& map = this->GetMap();

	UGDrawCache &drawing = map.GetDrawing()->m_DrawCache;	
	UGPoint pt(point.x(), point.y());
	drawing.DPtoLP(&pt, 1);

	OgdcPoint2D pt2D(0, 0);

	map.GetDrawing()->m_DrawParam.LPtoMP(pt, pt2D);

	return pt2D;
}

void MapControl::wheelEvent( QWheelEvent* event )
{
	double dScale = 1;

	if (event->delta() < 0)
	{
		dScale = 0.7;
	}
	else
	{
		dScale = 1.3;
	}

	UGPoint2D preLoction = this->PixelToMap(event->pos());
	
	m_pMapEditorWnd->Zoom(dScale);

	UGPoint2D curLoction = this->PixelToMap(event->pos());

	this->GetMap().Pan(curLoction.x - preLoction.x, curLoction.y - preLoction.y);
	this->Invalidate();
}

void MapControl::mousePressEvent( QMouseEvent* event )
{
	QWidget::mousePressEvent(event);
	int nflag= GetUGKeyflagMasks(event);
	UGPoint location(event->x(), event->y());

	if (event->button () == Qt::LeftButton)
	{
		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnLButtonDown(pGraphics, nflag, location);
		ReleaseUGGraphics(pGraphics);

		m_pressPoint.setX(event->x());
		m_pressPoint.setY(event->y());
	}   
	else if  (event->button () == Qt::RightButton)
	{	
		UGGraphics* pGraphics= NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnRButtonDown(pGraphics, nflag, location);
		ReleaseUGGraphics(pGraphics);  
	}		
	
	this->Invalidate();
}

void MapControl::mouseReleaseEvent( QMouseEvent* event )
{
	QWidget::mousePressEvent(event);
	int nflag = GetUGKeyflagMasks(event);
	UGPoint location(event->x(), event->y());
	
	if (event->button () == Qt::LeftButton)
	{
		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnLButtonUp(pGraphics, nflag, location);
		ReleaseUGGraphics(pGraphics);
	}   
	else if (event->buttons()==Qt::RightButton)
	{	
		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnRButtonUp(pGraphics, nflag, location);  
		ReleaseUGGraphics(pGraphics);
	}		
	this->Invalidate();
}

void MapControl::mouseMoveEvent( QMouseEvent* event )
{
	Qt::MouseButtons button = event->buttons();
	m_dragPoint.setX(event->x());
	m_dragPoint.setY(event->y());

	if (button == Qt::LeftButton)
	{
		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnMouseMove(pGraphics, 0, UGPoint(event->x(), event->y()));
		ReleaseUGGraphics(pGraphics);

		this->repaint();
	}

	if (m_pMapEditorWnd->GetUserAction() == UGC::UGDrawParamaters::uaTrack)
	{
		UGGraphics* pGraphics = NULL;
		CreateUGGrpaphics(pGraphics);
		m_pMapEditorWnd->OnMouseMove(pGraphics, 0, UGPoint(event->x(), event->y()));
		ReleaseUGGraphics(pGraphics);

		this->Invalidate();
	}

	ReviseCursor();
}

void MapControl::resizeEvent( QResizeEvent* event )
{
	QWidget::resizeEvent(event);
	m_width = this->width();
	m_height = this->height();

	m_pMapEditorWnd->OnSize(NULL,UGRect(0, 0, m_width, m_height));

	delete m_pMapImage;
	m_pMapImage = UGGraphicsManager::NewImage();
	m_pMapImage->CreateCompatibleImage(NULL, m_width, m_height);
	this->Invalidate();
}

void MapControl::Refresh()
{   
	m_pMapEditorWnd->Refresh();
	this->Invalidate();
}

void MapControl::Invalidate()
{
	m_invalidate = TRUE;
	this->update();
}

void MapControl::Pan()
{
	m_pMapEditorWnd->SetUserAction(UGC::UGDrawParamaters::uaPan);
}

void MapControl::ZoomIn()
{
	m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaZoomIn);
}

void MapControl::ZoomOut()
{
	m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaZoomOut);
}

void MapControl::Select()
{
	m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaPointModeSelect); // uaPointModeSelectTrue
}

void MapControl::Release()
{
	if (m_pMapImage != NULL)
	{ 
		delete m_pMapImage;
		m_pMapImage = NULL;
	}

	if (m_pMapEditorWnd != NULL)
	{
		delete m_pMapEditorWnd;
		m_pMapEditorWnd = NULL;
	}

	if (m_pWorkspace != NULL)
	{
		m_pWorkspace->Close();
		
		delete m_pWorkspace;
		m_pWorkspace = NULL;
	}

	if (m_MessageLabel != NULL)
	{
		delete m_MessageLabel;
		m_MessageLabel = NULL;
	}
}

UGString MapControl::QStringToUGString(QString qstring )
{
	UGString ugstring;
	ugstring.Append(qstring.toStdWString().c_str(),qstring.length());
	return ugstring;
}


void MapControl::openLayers( const QString& text , int index)
{
	UGLayers& layers = m_pMapEditorWnd->m_mapWnd.m_Map.m_Layers;
	UGString name = layers.GetLayerAt(index)->GetCaption();
	UGMBString strMB;
	name.ToMBString(strMB);
	const OgdcAchar * ugchar = strMB.Cstr();
	OgdcWchar * ugWchar;
	name.AcharToWchar(ugchar, ugWchar, name.GetLength());
	std::string drawstring = ugchar;
	QString strText = QString::fromLocal8Bit(drawstring.c_str());


	if (strText != text) return;
	layers.GetLayerAt(index)->SetVisible(!layers.GetLayerAt(index)->IsVisible());

	m_pMapEditorWnd->Refresh();
	Invalidate();
	
// 	m_defaultCenter = GetMap().GetCenter();
// 	m_defaultScale = GetMap().GetScale();

	//this->ViewEntire();
}

int MapControl::OpenMap( const QString& mapPath )
{
	QApplication::applicationDirPath();
	UGString workspacePath = QStringToUGString(mapPath);

	UGbool isOpen = m_pWorkspace->Open(workspacePath);

	if (!isOpen)
	{
		return 2;
	}

	UGMap *pMap = (UGMap*)&(m_pMapEditorWnd->m_mapWnd.m_Map);
	
	pMap->SetWorkspace(m_pWorkspace);

	pMap->m_TrackingLayer.SetVisible(TRUE);
	pMap->m_TrackingLayer.SetEditable(TRUE);
	pMap->m_TrackingLayer.SetSelectable(TRUE);
	pMap->m_TrackingLayer.SetLineSmoothingMode(false);

	pMap->SetLineSmoothingMode(false);

	int nMapCount = m_pWorkspace->m_MapStorages.GetCount();

	if (nMapCount == 0)
	{
		return 3;
	}

	UGint num = m_pWorkspace->m_MapStorages.GetCount();
	UGString mapName = m_pWorkspace->m_MapStorages.GetNameAt(0);

	if (!pMap->Open(mapName))
	{
		return 4;
	}

	
	m_defaultCenter = pMap->GetCenter();
	m_defaultScale = pMap->GetScale();

	this->ViewEntire();

	m_initialized = true;

	return 0;
}



QVector<QVariantList> MapControl::getLayersList()
{
	QVector<QVariantList> sList;
	QVariantList layersMap;
	//GetEditableLayer()
	
	
		UGLayers& layers = m_pMapEditorWnd->m_mapWnd.m_Map.m_Layers;
		int count = layers.GetTopLevelCount();
// 		 QVector<ILayer2D*> m_layers;
		for(int i =0;i<count;i++)
		{
			UGString name = layers.GetLayerAt(i)->GetCaption();
			UGMBString strMB;
			name.ToMBString(strMB);
			const OgdcAchar * ugchar = strMB.Cstr();
			OgdcWchar * ugWchar;
			name.AcharToWchar(ugchar, ugWchar, name.GetLength());
			std::string drawstring = ugchar;
			QString strText = QString::fromLocal8Bit(drawstring.c_str());
			//sList.push_back(strText);
			layersMap.insert(0,strText);
			layersMap.insert(1,layers.GetLayerAt(i)->IsVisible());
			sList.push_back(layersMap);
			//layersMap.insert(strText, layers.GetLayerAt(i)->IsVisible());
			//layersMap.
		}
	

		
// 	UGLayers list = GetMap().m_Layers;
// 	
// 
// 
// 	UGString ss = m_pWorkspace->m_MapStorages.GetMapAt(0)->GetXML();
// 
// 	for (int i = 0; i < m_pWorkspace->m_MapStorages.GetCount(); i++)
// 	{
// 		UGString name = m_pWorkspace->m_MapStorages.GetNameAt(i);
// 
// 		UGMBString strMB;
// 		name.ToMBString(strMB);
// 		const OgdcAchar * ugchar = strMB.Cstr();
// 		OgdcWchar * ugWchar;
// 		name.AcharToWchar(ugchar, ugWchar, name.GetLength());
// 		std::string drawstring = ugchar;
// 		QString strText = QString::fromLocal8Bit(drawstring.c_str());
// 		sList.push_back(strText);
// 	} 
//	qDebug()<<layersMap;
	qDebug()<<sList;
	return sList;

}


void MapControl::CreateUGGrpaphics(UGGraphics* &pGraphics)
{
	pGraphics = UGC::UGGraphicsManager::NewGraphics();
	pGraphics->CreateCompatibleGraphics(NULL);
	
	m_pOldImage = pGraphics->SelectImage(m_pMapImage);
}

void MapControl::ReleaseUGGraphics(UGGraphics* &pGraphics)
{
	pGraphics->SelectImage(m_pOldImage);
	delete pGraphics;
	pGraphics = NULL;
}

void MapControl::PaintToQPainter()
{
	m_pQimage = new QImage((UGC::UGbyte*)m_pMapImage->GetColors(), m_width, m_height, QImage::Format_ARGB32);

	QPainter paint;
	paint.begin(this);
	QColor backGound(255, 255, 255);
	paint.fillRect(0, 0, m_width, m_height, backGound); 
	paint.drawImage(QRectF(0, 0, m_width, m_height), *m_pQimage);
	paint.end();

	if (m_pQimage != NULL)
	{
		delete m_pQimage;
		m_pQimage = NULL;
	}	

}

UGWorkspace* MapControl::GetWorkspace()
{
	return m_pWorkspace;
}

UGMapEditorWnd* MapControl::GetUGMapWnd() 
{
	return m_pMapEditorWnd;
}

void MapControl::OnMapDrawn(UGGraphics* pGraphics )
{
	emit UGMapDrawnEvent(this, pGraphics);
}

UGMap& MapControl::GetMap()
{
	return m_pMapEditorWnd->m_mapWnd.m_Map;
}

void MapControl::CalcuLength()
{
	m_pMapEditorWnd->SetUserAction(UGDrawParamaters::uaTrack, UGC::UGEditType::ET_PolyLine);

	m_MessureType = 0;
	ShowMessureResult("Length: ");
}

void MapControl::ShowMessureResult(QString messageResult)
{
	if (m_MessageLabel == NULL)
	{
		m_MessageLabel = new QLabel(this);
		QFont font;
		font.setPointSize(10);

		m_MessageLabel->setFont(font);
		m_MessageLabel->setAutoFillBackground(true);
		m_MessageLabel->setGeometry(0,0,200,20);
		m_MessageLabel->show();
	}
	m_MessageLabel->setText(messageResult);
}

void MapControl::popupTips()
{
	emit showTips();
}

void* MapControl::getUGMapEditorWnd()
{
	return (void*)m_pMapEditorWnd;
}
