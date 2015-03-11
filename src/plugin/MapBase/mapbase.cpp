UGbyte
UGbyte
UGbyte
#include "stdafx.h"
#include "mapbase.h"
#include "..\\..\\commom\\sysconfig.h"

#include <QDir>
#include <QStyleOption>
#include <QPainter>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>

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

MapBase::MapBase(QWidget *parent) : QWidget(parent)
{
	setObjectName("MapTab");
//	setStyleSheet("background-color: red");
	m_pMapControl = NULL;
	m_pMapController = NULL;
	m_pMapLayers = NULL;
	m_pPropertyPanel = NULL;
	m_pPropertyTrigger = NULL;

	m_pMap2DLayout = new QHBoxLayout();
	m_pMap2DLayout->setContentsMargins(0, 0, 0, 0);
	m_pMap2DLayout->setSpacing(0);
	m_pMap2DLayout->setAlignment(Qt::AlignHorizontal_Mask);

 	m_pMapController = new MapController(this);
 	m_pMapController->setFixedHeight(32);
 	m_pMapController->setFixedWidth(32*5);
 	connect(m_pMapController, SIGNAL(selectClicked()), this, SLOT(OnSelectClicked()));
 	connect(m_pMapController, SIGNAL(panClicked()), this, SLOT(OnPanClicked()));
 	connect(m_pMapController, SIGNAL(entireClicked()), this, SLOT(OnEntireClicked()));
 	connect(m_pMapController, SIGNAL(zoominClicked()), this, SLOT(OnZoomInClicked()));
 	connect(m_pMapController, SIGNAL(zoomoutClicked()), this, SLOT(OnZoomOutClicked()));
 
 	m_pMapLayers = new MapLayers(this);
 	connect(m_pMapLayers, SIGNAL(changeLayers(const QString&, int )), this, SLOT(OnChangeLayers(const QString&, int)));


	testwidget = new QWidget(this);
 	m_pMapControl = new MapControl(this);
 	connect(m_pMapControl, SIGNAL(showTips()), this, SIGNAL(showTips()));
 	connect(m_pMapControl, SIGNAL(UGStyleChanged(const UGStyle&)), this, SLOT(OnUGStyleChanged(const UGStyle&)));



	QWidget* map2D = dynamic_cast<QWidget*>(m_pMapControl);

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);

	QFileInfo info("../Map/China/China400.smwu");
	QString ssb = info.absoluteFilePath();
	QDir::setCurrent(ss);

 	m_MapUrl = SysConfig::getValue("DefaultMap/DefaultMapPath").toString();
 	int flag = m_pMapControl->OpenMap(m_MapUrl);


 	if (flag != 0)
 	{
 		QMessageBox::warning(NULL, "", QString::number(flag));
 		return;
 	}
 	m_pMapControl->show();
 	m_pMapController->show();
 	m_pMapController->raise();
 	m_Layers = m_pMapControl->getLayersList();
 
 	m_pMapLayers->setGeometry(300,100,220,360);
 	m_pMapLayers->setFixedWidth(220);
 	m_pMapLayers->setFixedHeight(360);
 
 	m_pMapLayers->initLayers(m_Layers);
 
 	m_pMapLayers->show();
 	m_pMapLayers->raise();



	//PropertyBrowser 实现 参见OnPinBtnClicked() 显示，初始化 树形控件 //valueChanged() 通过树形控件修改值 触发事件//////////////////////////////////////////////////////////////////////
	m_pPropertyPanel = new PropertyPanel(this);
	m_pPropertyPanel->setFixedWidth(216); 
	m_pPropertyPanel->setPropertyPanelTitle("UGStyle Property");
	connect(m_pPropertyPanel, SIGNAL(pinBtnClicked()), this, SLOT(OnPinBtnClicked()));

	variantManager = new QtVariantPropertyManager(this);
	connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(valueChanged(QtProperty *, const QVariant &)));
	QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);

	propertyEditor = new QtTreePropertyBrowser(this);
	propertyEditor->setFactoryForManager(variantManager, variantFactory);
	propertyEditor->setFixedWidth(216); 


	m_pPropertyPanel->setCentralWidget(propertyEditor);
	//////////////////////////////////////////////////////////////////////////

//	m_pMap2DLayout->addWidget(testwidget);
	m_pMap2DLayout->addWidget(map2D);
	m_pMap2DLayout->addWidget(m_pPropertyPanel);
	this->setLayout(m_pMap2DLayout);


	m_pPropertyTrigger = new PropertyTrigger(this);
	m_pPropertyTrigger->setText("UGStyle Property");

	m_pPropertyTrigger->setFixedHeight(400);
	m_pPropertyTrigger->setFixedWidth(320);

	m_pPropertyTrigger->init();
	connect(m_pPropertyTrigger, SIGNAL(tirggered()), this, SLOT(OnPropertyTriggered()));
	QFile file(":/mapbase.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	this->setStyleSheet(style);
	file.close();
}

MapBase::~MapBase()
{
 	m_Layers.clear();
 
	if (m_pMapLayers)
	{
		delete m_pMapLayers;
		m_pMapLayers = NULL;
	}
	if (m_pMapController)
	{
		delete m_pMapController;
		m_pMapController = NULL;
	}
	if (m_pMapControl)
	{
		m_pMapControl->Release();
		delete m_pMapControl;
		m_pMapControl = NULL;
	}

	if (m_pPropertyPanel)
	{
		delete m_pPropertyPanel;
		m_pPropertyPanel = NULL;
	}
}

void MapBase::paintEvent(QPaintEvent* e)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(e);
}

QWidget* MapBase::getWidget()
{
	return this;
}

void* MapBase::getUGMapEditorWnd()
{
	if (!m_pMapControl) return NULL;
	{
	}
}

QWidget* MapBase::getMapLayers()
{
	return m_pMapLayers;
}

void MapBase::test()
{

}

void MapBase::resizeEvent( QResizeEvent* e)
{
	

	if (m_pPropertyPanel)
	{
		m_pPropertyPanel->setGeometry(width() - m_pPropertyPanel->width(), 0, m_pPropertyPanel->width(), height());
	}

	if (m_pMapControl && m_pPropertyPanel)
	{
		int m = m_pPropertyPanel->width();
		m_pMapControl->setFixedWidth(width() - m_pPropertyPanel->width());
		m_pMapControl->setFixedHeight(height() -3);
		m_pMapControl->setGeometry(0, 0, width() - m_pPropertyPanel->width(), height() - 3);
		
	}
// 	if (testwidget)
// 	{
// 		testwidget->setGeometry(0, 0, width() - m_pPropertyPanel->width(), height() - 3);
// 	}

	

	if (m_pPropertyTrigger)
	{
		m_pPropertyTrigger->raise();
	}

	QWidget::resizeEvent(e);
}

QObject* MapBase::getObject()
{
	return this;
}

void MapBase::setPluginGeometry( const QRect& rect )
{
	this->setGeometry(rect);
}

void MapBase::setPluginGeometry( int ax, int ay, int aw, int ah )
{
	this->setGeometry(ax, ay, aw, ah);
}

void MapBase::setPluginParent( QWidget* parentWidget )
{
	this->setParent(parentWidget);
}

void MapBase::showPlugin()
{
	this->show();
}

void MapBase::raisePlugin()
{
	this->raise();
}

void MapBase::resizePlugin(int ax, int ay, int aw, int ah)
{
	setGeometry(ax, ay, aw, ah);
}

void MapBase::lowerPlugin()
{
	lower();
}

void MapBase::setPluginWidth( int width )
{
	setFixedWidth(width);
}

void MapBase::setPluginHeight( int height )
{
	setFixedHeight(height);
}

int MapBase::pluginWidth()
{
	return width();
}

int MapBase::pluginHeight()
{
	return height();
}

// void MapBase::loadSkin()
// {
// 	QFile file(":/maptab.qss");
// 	file.open(QFile::ReadOnly);
// 	QString style = QString(file.readAll());
// 	this->setStyleSheet(style);
// 	file.close();
// }

void MapBase::OnSelectClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Select();
	}
}

void MapBase::OnPanClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->Pan();
	}
}

void MapBase::OnEntireClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ViewEntire();
	}
}

void MapBase::OnZoomInClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomIn();
	}
}

void MapBase::OnZoomOutClicked()
{
	if (m_pMapControl)
	{
		m_pMapControl->ZoomOut();
	}
}

QString MapBase::getMapUrl() const
{
	return m_MapUrl;
}

/*QVector<QString>*/QVector<QVariantList> MapBase::getLayers() const
{
	return m_Layers;
}

QString MapBase::getStyleSheet()
{
	return this->styleSheet();
}

void MapBase::OnChangeLayers( const QString& text , int index)
{
	if (m_pMapControl)
	{
		m_pMapControl->openLayers(text, index);
	}
}

QWidget* MapBase::getMapController()
{
	return m_pMapController;
}

QWidget* MapBase::getPropertyTrigger()
{
	return m_pPropertyTrigger;
}

void MapBase::OnPinBtnClicked()
{
	if (m_pPropertyPanel&& m_pMapControl)
	{
		m_pPropertyPanel->setFixedWidth(0);
		m_pMapControl->setFixedWidth(width());
		if (m_pPropertyTrigger)
		{
			int m = m_pPropertyTrigger->getWidth();
			m_pPropertyTrigger->setFixedWidth(m_pPropertyTrigger->getWidth());
			//m_pPropertyTrigger->setGeometry(width() - m_pPropertyTrigger->width() - 3, 20, m_pPropertyTrigger->width(), m_pPropertyTrigger->height());
			m_pPropertyTrigger->show();
			m_pPropertyTrigger->raise();
		}
	}
	this->repaint();
}

void MapBase::OnPropertyTriggered()
{
	if (m_pPropertyPanel&& m_pMapControl)
	{
		m_pPropertyPanel->setFixedWidth(216);
		m_pMapControl->setFixedWidth(width() - m_pPropertyPanel->width());
		if (m_pPropertyTrigger)
		{
			int m = m_pPropertyTrigger->getWidth();
			//m_pPropertyTrigger->setFixedWidth(0);
			//m_pPropertyTrigger->setGeometry(width(), 20, 0, m_pPropertyTrigger->height());
			m_pPropertyTrigger->hide();
			m_pPropertyTrigger->raise();
		}
	}

	this->repaint();
}

int QColorToInt(const QColor &color)  
{  
	//将Color 从QColor 转换成 int  
	return   (int)(((unsigned int)color.blue()<< 16) | (unsigned short)(((unsigned short)color.green()<< 8) | color.red()));  
}  
QColor IntToQColor(const int &intColor)  
{  
	//将Color 从int 转换成 QColor  
	int red = intColor & 255;  
	int green = intColor >> 8 & 255;  
	int blue = intColor >> 16 & 255;  
	return QColor(red, green, blue);  
}  

void MapBase::updateExpandState()
{
	QList<QtBrowserItem *> list = propertyEditor->topLevelItems();
	QListIterator<QtBrowserItem *> it(list);
	while (it.hasNext()) 
	{
		QtBrowserItem *item = it.next();
		QtProperty *prop = item->property();
		idToExpanded[propertyToId[prop]] = propertyEditor->isExpanded(item);
	}
}

void MapBase::addProperty(QtVariantProperty *property, const QString &id)
{
	propertyToId[property] = id;
	idToProperty[id] = property;
	QtBrowserItem *item = propertyEditor->addProperty(property);
	if (idToExpanded.contains(id))
		propertyEditor->setExpanded(item, idToExpanded[id]);
}

void MapBase::OnUGStyleChanged( const UGStyle&s )
{
	currentItem = s;
	//s.SetFillStyle(5);
	updateExpandState();

	QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
	while (itProp != propertyToId.constEnd()) 
	{
		delete itProp.key();
		itProp++;
	}
	propertyToId.clear();
	idToProperty.clear();


	//deleteAction->setEnabled(true);

	QtVariantProperty *property;

	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerStyle"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 100);
	property->setValue(s.GetMarkerStyle());
	addProperty(property, QLatin1String("MarkerStyle"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerAngle"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetMarkerAngle());
	addProperty(property, QLatin1String("MarkerAngle"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerSize"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetMarkerSize());
	addProperty(property, QLatin1String("MarkerSize"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerWidth"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetMarkerWidth());
	addProperty(property, QLatin1String("MarkerWidth"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerHeight"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetMarkerHeight());
	addProperty(property, QLatin1String("MarkerHeight"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("LineStyle"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetLineStyle());
	addProperty(property, QLatin1String("LineStyle"));

	property = variantManager->addProperty(QVariant::Color, QLatin1String("LineColor"));
	property->setValue(IntToQColor(s.GetLineColor()));
	addProperty(property, QLatin1String("LineColor"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("LineWidth"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 256);
	property->setValue(s.GetLineWidth());
	addProperty(property, QLatin1String("LineWidth"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillStyle"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 100);
	property->setValue(s.GetFillStyle());
	addProperty(property, QLatin1String("FillStyle"));

	property = variantManager->addProperty(QVariant::Color, QLatin1String("FillBackColor"));
	property->setValue(IntToQColor(s.GetFillBackColor()));
	addProperty(property, QLatin1String("FillBackColor"));

	property = variantManager->addProperty(QVariant::Color, QLatin1String("FillForeColor"));
	property->setValue(IntToQColor(s.GetFillForeColor()));
	addProperty(property, QLatin1String("FillForeColor"));


	property = variantManager->addProperty(QVariant::Bool, QLatin1String("FillBackOpaque"));  // bool
	property->setValue(s.GetFillBackOpaque());
	addProperty(property, QLatin1String("FillBackOpaque"));

	property = variantManager->addProperty(QVariant::Char, QLatin1String("FillOpaqueRate"));
	property->setValue(s.GetFillOpaqueRate());
	addProperty(property, QStringLiteral("FillOpaqueRate"));

	property = variantManager->addProperty(QVariant::Char, QLatin1String("FillGradientType"));
	property->setValue(s.GetFillGradientType());
	addProperty(property, QStringLiteral("FillGradientType"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillAngle"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 360);
	property->setValue(s.GetFillAngle());
	addProperty(property, QLatin1String("FillAngle"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillCenterOffsetX"));
	property->setAttribute(QLatin1String("minimum"), 0);
	property->setAttribute(QLatin1String("maximum"), 360);
	property->setValue(s.GetFillCenterOffsetX());
	addProperty(property, QLatin1String("FillCenterOffsetX"));

	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillCenterOffsetY"));
	property->setAttribute(QLatin1String("minimum"), 0);
	//property->setAttribute(QLatin1String("maximum"), 360);
	property->setValue(s.GetFillCenterOffsetY());
	addProperty(property, QLatin1String("FillCenterOffsetY"));

	property = variantManager->addProperty(QVariant::Bool, QLatin1String("SymbolScale"));  // bool
	property->setValue(s.IsScaleBySymbol());
	addProperty(property, QLatin1String("SymbolScale"));

// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerSymbolLength"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	property->setValue(s.GetMarkerSymbolLength());
// 	addProperty(property, QStringLiteral("MarkerSymbolLength"));

// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("MarkerSymbolVersion"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	//property->setAttribute(QLatin1String("maximum"), 360);
// 	property->setValue(s.GetMarkerSymbolVersion());
// 	addProperty(property, QLatin1String("MarkerSymbolVersion"));

// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("LineSymbolLength"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	//property->setAttribute(QLatin1String("maximum"), 360);
// 	property->setValue(s.GetLineSymbolLength());
// 	addProperty(property, QLatin1String("LineSymbolLength"));
// 
// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("LineSymbolVersion"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	//property->setAttribute(QLatin1String("maximum"), 360);
// 	property->setValue(s.GetLineSymbolVersion());
// 	addProperty(property, QLatin1String("LineSymbolVersion"));

// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillSymbolLength"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	//property->setAttribute(QLatin1String("maximum"), 360);
// 	property->setValue(s.GetFillSymbolLength());
// 	addProperty(property, QLatin1String("FillSymbolLength"));
// 
// 	property = variantManager->addProperty(QVariant::Int, QLatin1String("FillSymbolVersion"));
// 	property->setAttribute(QLatin1String("minimum"), 0);
// 	//property->setAttribute(QLatin1String("maximum"), 360);
// 	property->setValue(s.GetFillSymbolVersion());
// 	addProperty(property, QLatin1String("FillSymbolVersion"));





	property = variantManager->addProperty(QVariant::Color, tr("FixedColor"));
	property->setValue(IntToQColor(s.GetFixedColor()));
	addProperty(property, QLatin1String("FixedColor"));

	
}

void MapBase::valueChanged( QtProperty *property, const QVariant &value )
{
	if (!propertyToId.contains(property))
		return;
	QString id = propertyToId[property];
	if (id == QLatin1String("MarkerStyle")) 
	{
		currentItem.SetMarkerStyle(value.toInt());
	} 
	else if (id == QLatin1String("MarkerAngle"))
	{
		currentItem.SetMarkerAngle(value.toInt());
	}
	else if (id == QLatin1String("MarkerSize"))
	{
		currentItem.SetMarkerSize(value.toInt());
	}
	else if (id == QLatin1String("MarkerWidth"))
	{
		currentItem.SetMarkerWidth(value.toInt());
	}
	else if (id == QLatin1String("MarkerHeight"))
	{
		currentItem.SetMarkerHeight(value.toInt());
	}

	else if (id == QLatin1String("LineStyle"))
	{
		currentItem.SetLineStyle(value.toInt());
	}
	else if (id == QLatin1String("LineColor"))
	{
		currentItem.SetLineColor(QColorToInt(value.value<QColor>()));
	}
	else if (id == QLatin1String("LineWidth"))
	{
		currentItem.SetLineWidth(value.toInt());
	}
	else if (id == QLatin1String("FillStyle"))
	{
		currentItem.SetFillStyle(value.toInt());
	}
	else if (id == QLatin1String("FillBackColor"))
	{
		currentItem.SetFillBackColor(QColorToInt(value.value<QColor>()));
	}
	else if (id == QLatin1String("FillForeColor"))
	{
		currentItem.SetFillForeColor(QColorToInt(value.value<QColor>()));
	}
	else if (id == QLatin1String("FillBackOpaque"))
	{
		currentItem.SetFillBackOpaque(value.toBool());
	}
	else if (id == QLatin1String("FillOpaqueRate"))
	{
		
		currentItem.SetFillOpaqueRate(value.toChar().toLatin1());
	}
	else if (id == QLatin1String("FillGradientType"))
	{
		currentItem.SetFillGradientType(value.toChar().toLatin1());
	}
	else if (id == QLatin1String("FillAngle"))
	{
		currentItem.SetFillAngle(value.toInt());
	}
	else if (id == QLatin1String("FillCenterOffsetX"))
	{
		currentItem.SetFillCenterOffsetX(value.toInt());
	}
	else if (id == QLatin1String("FillCenterOffsetY"))
	{
		currentItem.SetFillCenterOffsetY(value.toInt());
	}
	else if (id == QLatin1String("SymbolScale"))
	{
		currentItem.SetScaleBySymbol(value.toBool());
	}
	else if (id == QLatin1String("FixedColor"))
	{
		currentItem.SetFixedColor(QColorToInt(value.value<QColor>()));
	}

	if (m_pMapControl)
	{
		m_pMapControl->changeUGstyleValue(currentItem);
	}
	

// 	else if (id == QLatin1String(""))
// 	{
// 		currentItem.Set(value.toInt());
// 	}
// 	else if (id == QLatin1String(""))
// 	{
// 		currentItem.Set(value.toInt());
// 	}
// 	else if (id == QLatin1String(""))
// 	{
// 		currentItem.Set(value.toInt());
// 	}
// 
// 	else if (id == QLatin1String(""))
// 	{
// 		currentItem.Set(value.toInt());
// 	}
// 
// 
// 	else if (id == QLatin1String(""))
// 	{
// 		currentItem.Set(value.toInt());
// 	}
	
}






