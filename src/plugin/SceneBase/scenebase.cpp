#include "scenebase.h"



using namespace UGC;


UGC::UGuint GetMasks(QInputEvent * event)
{
	UGC::UGuint flag=0;
	if (event->modifiers()&Qt::ShiftModifier)
	{
		flag=flag|UG_VK_SHIFT;
	} 
	if ((event->modifiers()&Qt::ControlModifier))
	{
		flag=flag|UG_VK_CONTROL;
	}
	if (event->modifiers()&Qt::MetaModifier)
	{
		flag=flag|UG_VK_MENU;
	}
	return flag;
}



SceneBase::SceneBase( QWidget *parent /*= NULL*/ ) : QWidget(parent)
{
	m_pSceneWnd = NULL;
	m_pWorkspace = NULL;
	m_root3D = NULL;
	m_timer = NULL;
	verticalLayout = NULL;
	pScene = NULL;

	verticalLayout = new QVBoxLayout();
	verticalLayout->setSpacing(0);
	verticalLayout->setMargin(0);
	setLayout(verticalLayout);
}


SceneBase::~SceneBase()
{
	destroy(TRUE,TRUE);
}



QObject* SceneBase::getObject()
{
	return this;
}

void SceneBase::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void SceneBase::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void SceneBase::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void SceneBase::showPlugin()
{
	this->show();
}

void SceneBase::raisePlugin()
{
	this->raise();
}

void SceneBase::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}

void SceneBase::lowerPlugin()
{
	lower();
}

void SceneBase::setPluginWidth( int width )
{
	setFixedWidth(width);
}

void SceneBase::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int SceneBase::pluginWidth()
{
	return width();
}

int SceneBase::pluginHeight()
{
	return height();
}

void SceneBase::test()
{

}

void* SceneBase::getUGSceneEditorWnd()
{
	return NULL;
}

QWidget* SceneBase::getWidget()
{
	return this;
}

QWidget* SceneBase::getSceneLayers()
{
	return NULL;
}

QWidget* SceneBase::getSceneController()
{
	return NULL;
}

QString SceneBase::getStyleSheet()
{
	return this->styleSheet();
}


void SceneBase::SetWorkspace( /*UGWorkspace* pW*/void* workspace )
{
	m_pWorkspace = (UGWorkspace*)workspace;	
	UGC::Window3D hWnd= (Window3D)this->winId();
	InitScene3D();
// 	if(m_pSceneWnd != NULL)
// 	{
// 		m_pSceneWnd->OnSize(width(), height());
// 	}
}

void SceneBase::setUGMapEditorWnd( void* wnd )
{
	SetWorkspace(wnd);
}


void SceneBase::render()
{
	m_root3D->Render();
	ReviseCursor();

	emit renderTick();
}


void SceneBase::paintEvent( QPaintEvent *event )
{
	InitScene3D();

	QWidget::paintEvent(event);
}
void SceneBase::keyPressEvent(QKeyEvent *event)
{

}
void SceneBase::destroy( bool destroyWindow /* = true */, bool destroySubWindows /* = true */ )
{
	if(m_timer != NULL)
	{
		m_timer->stop();
	}
	delete m_timer;
	m_timer = NULL;


	if(m_pSceneWnd != NULL)
	{
		delete m_pSceneWnd;
		m_pSceneWnd = NULL;
		m_pWorkspace= NULL;

		m_root3D->DestoryScene((Window3D)this->winId());

		delete m_root3D;
		m_root3D = NULL;
	}
}

void SceneBase::mouseMoveEvent( QMouseEvent * event )
{
	Qt::MouseButtons button = event->buttons();
	if(button != Qt::NoButton)
	{
		UGuint nflag= GetMasks(event);
		UGC::UGPoint pntTmp(event->x(), event->y());

		m_pSceneWnd->OnMouseMove(nflag, pntTmp);
	}



	QWidget::mouseMoveEvent(event);
}

void SceneBase::ReviseCursor()
{
	switch (m_pSceneWnd->m_SceneWindow.GetUserAction())
	{
	case UGC::suaNull :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaPan :
		{
			setCursor(QCursor(QPixmap("Resources/pan.png")));
		}
		break;
	case UGC::suaZoomIn :
		{
			setCursor(QCursor(QPixmap("Resources/ZoomIn.png"),2,2));
		}
		break;
	case UGC::suaZoomOut :
		{
			setCursor(QCursor(QPixmap("Resources/ZoomOut.png"),2,2));
		}
		break;
	case UGC::suaZoomFree :
		{
			setCursor(QCursor(QPixmap("Resources/ZoomFree.png")));
		}
		break;
	case UGC::suaPointSelect :
	case UGC::suaRectSelect :
	case UGC::suaLineSelect :
		{
			setCursor(QCursor(QPixmap("Resources/select.png"),4,4));
		}
		break;
	case UGC::suaCircleSelect :
		{
			setCursor(QCursor(QPixmap("Resources/select_circle.png"),64,64));
		}
		break;
	case UGC::suaRegionSelect :
		{
			setCursor(QCursor(QPixmap("Resources/select_region.png"),64,64));
		}
		break;
	case UGC::suaEdit :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaTrack :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMeasureDistance :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMeasureArea :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMeasureHeight :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMoveThemeLabel :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMoveThemeGraph :
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	case UGC::suaMoveThemeGraduatedSymbol :
	default:
		{
			setCursor(QCursor(Qt::ArrowCursor));
		}
		break;
	}
}

void SceneBase::wheelEvent( QWheelEvent *event )
{
	UGuint nflag= ::GetMasks(event);

	UGC::UGPoint pntTmp(event->x(), event->y());
	m_pSceneWnd->OnMouseWheel(nflag, event->delta(), pntTmp);
	QWidget::wheelEvent(event);
	event->accept();
}

void SceneBase::mousePressEvent( QMouseEvent * event )
{
	UGuint nflag=GetMasks(event);
	if(event->button ()==Qt::LeftButton)
	{
		UGC::UGPoint pntTmp(event->x(), event->y());
		m_pSceneWnd->OnLButtonDown(nflag, pntTmp);
	}
	else if(event->button ()==Qt::RightButton)
	{
		UGC::UGPoint pntTmp(event->x(), event->y());
		m_pSceneWnd->OnRButtonDown(nflag, pntTmp);
	}
	else if (event->button()==Qt::MidButton)
	{
		UGC::UGPoint pntTem(event->x(),event->y());
		m_pSceneWnd->OnMButtonDown(nflag,pntTem);
	}
	QWidget::mousePressEvent(event);
	event->accept();
}

void SceneBase::mouseReleaseEvent( QMouseEvent * event )
{
	UGPoint pt(event->x(),event->y());
	UGuint flags = ::GetMasks(event);

	if (event->button() == Qt::LeftButton)
	{
		m_pSceneWnd->OnLButtonUp(flags,pt);
	} 
	else if(event->button() == Qt::MiddleButton)
	{
		m_pSceneWnd->OnMButtonUp(flags,pt);
	}
	else if(event->button() == Qt::RightButton)
	{
		m_pSceneWnd->OnRButtonUp(flags,pt);
	}

	QWidget::mouseReleaseEvent(event);
}

void SceneBase::leaveEvent( QEvent *event )
{
	UGC::UGPoint pntTmp(0, 0);
	int nflag=0;

	m_pSceneWnd->OnMouseLeave(nflag,pntTmp);
	QWidget::leaveEvent(event);
}

void SceneBase::mouseDoubleClickEvent( QMouseEvent *event )
{
	UGuint nflag= GetMasks(event);
	UGC::UGPoint pntTmp(event->x(), event->y());

	if (event->button ()==Qt::LeftButton)
	{

		m_pSceneWnd->OnLButtonDblClk(nflag, pntTmp);
	} 
	if(event->button ()==Qt::RightButton)
	{
		m_pSceneWnd->OnRButtonDblClk(nflag, pntTmp);
	}
	QWidget::mouseDoubleClickEvent(event);
}

void SceneBase::resizeEvent( QResizeEvent *event )
{
	
	if(m_pSceneWnd != NULL)
	{
		int m = event->size().width();
		int n = event->size().height();
		m_pSceneWnd->OnSize(event->size().width(), event->size().height());
		if (pScene)
		{
			pScene->SetViewHeight(n);
			pScene->SetViewWidth(m);
		}
	}
	//setGeometry(0,0,width(),height() - 50);
	QWidget::resizeEvent(event);
}

UGSceneEditorWnd* SceneBase::GetUGSecneWnd()
{
	return m_pSceneWnd;
}

void SceneBase::Open()
{
	// 打开场景
	int count = m_pWorkspace->m_SceneStorages.GetCount();
	if(count > 0)
	{
		const UGSceneStorage* pSceneStorage = m_pWorkspace->m_SceneStorages.GetSceneAt(0);
		UGString sceneXML = pSceneStorage->GetXML();
		UGString workspaceFile = m_pWorkspace->GetName();
		workspaceFile = UGFile::GetDir(workspaceFile);
		m_pSceneWnd->GetScene3D()->FromXML(sceneXML,FALSE,0,workspaceFile);
	}

}

void SceneBase::InitScene3D()
{
	if (m_pWorkspace != NULL && m_root3D == NULL)
	{
		m_root3D =new UGC::UGRoot3D();
		m_root3D->SetGraphics3DType(UGC::RST_OGRE);
		m_root3D->Initialize(NULL);
		
		//UGScene3D *pScene = NULL;
		UGC::Window3D hWnd= (Window3D)this->winId();
#if defined _WIN32
		pScene =m_root3D->CreateScene(hWnd);
#else
		Display* hDisplay = this->x11Info().display();
		pScene= m_root3D->CreateScene(hWnd, hDisplay);
#endif

		if(pScene != NULL)
		{	

			UGCameraWorld *pCamera = pScene->CreateCamera(_U("Camera"));
			pScene->GetRenderTarget()->AddViewport(pCamera, 0);
			m_root3D->SetActiveScene(pScene);

			m_pSceneWnd=new UGC::UGSceneEditorWnd(pScene);
			m_pSceneWnd->SetUserAction(UGC::suaPanSelect);
			m_pSceneWnd->SetOpenEditMode(TRUE);

			
			QDesktopWidget *mydesk = QApplication::desktop();
			pScene->InitializeScene(_U(""),mydesk->physicalDpiX(),mydesk->physicalDpiY());

			pScene->SetDrawMode(REAL_TIME_RASTER);
			pScene->GetStatusBar()->SetFPSVisible(TRUE);

			//设置关联数据源集合
			pScene->m_Layers.SetDataSources(&m_pWorkspace->m_DataSources);
			pScene->m_TerrainLayer3Ds.SetDataSources(&m_pWorkspace->m_DataSources);
			pScene->m_Layers.SetWorkspace(m_pWorkspace);


		}

		m_timer = new QTimer(this);
		m_timer->connect(m_timer, SIGNAL(timeout()), this, SLOT(render()));
		m_timer->start(20);
		if(m_pSceneWnd != NULL)
		{
			m_pSceneWnd->OnSize(width(), height());
		}

		//m_pSceneWnd->Refresh();
	}
}


