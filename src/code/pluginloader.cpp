#include "stdafx.h"
#include "pluginloader.h"
#include "fileutils.h"
#include "pluginspec.h"
#include "pluginmanager.h"
#include "sysconfig.h"
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidgetItem>
#include <QDesktopWidget>
#include <QtWidgets/QAbstractItemView>
using namespace ExtensionSystem;

Pluginloader::Pluginloader(QWidget *parent) : QWidget(parent)
{
	setObjectName("Pluginloader");
	setWindowTitle("SuperMap iObjectsDemo Pulgin Manager");

	setFixedWidth(600);
	setFixedHeight(400);
	
	QRect rect = QApplication::desktop()->availableGeometry();
	setGeometry(rect.width()/2 - width()/2, rect.height()/2 - height()/2, 600, 400);
	//setWindowFlags(Qt::WindowFlags)

	pluginList = FileUtils::getAllFileByExtensionsName("pluginspec", "../plugins");
	

	m_pTableWidget = new QTableWidget(this);

	m_pTableWidget->setObjectName("PluginloaderableWidget");
	m_pTableWidget->setColumnCount(4);	
	m_pTableWidget->setRowCount(pluginList.length());

	QStringList  columnName;
	columnName.push_back(QString(QStringLiteral("名称")));
	columnName.push_back(QString(QStringLiteral("加载")));
	columnName.push_back(QString(QStringLiteral("版本号")));
	columnName.push_back(QString(QStringLiteral("作者")));
	m_pTableWidget->setHorizontalHeaderLabels(columnName);

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);
	
	for (int i = 0; i < pluginList.length(); i++)
	{
		QString plugiName = pluginList.at(i);
		QString s = "..\\plugins\\" + plugiName + ".pluginspec";
		PluginSpec spec("..\\plugins\\" + plugiName + ".pluginspec");

		m_pTableWidget->setItem(i, 0, new QTableWidgetItem(spec.name()));	
		m_pTableWidget->setItem(i, 2, new QTableWidgetItem(spec.version()));
		m_pTableWidget->setItem(i, 3, new QTableWidgetItem(spec.vendor()));

		QCheckBox *chBox = new QCheckBox(m_pTableWidget); 		
		chBox->setProperty("PluginloaderCheckBox", true);
		chBox->setObjectName(plugiName);
		bool value = PluginManager::instance()->getPluginValueByName(plugiName);
		chBox->setChecked(PluginManager::instance()->getPluginValueByName(plugiName));
		m_pTableWidget->setCellWidget(i,1,chBox);
	}
	QDir::setCurrent(ss);

	m_pTableWidget->verticalHeader()->setVisible(false);
	m_pTableWidget->horizontalHeader()->setFixedHeight(32);
	
	
	m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); 
	m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	m_pTableWidget->horizontalHeader()->setStretchLastSection(true);

	m_pTableWidget->resizeColumnsToContents();  
	m_pTableWidget->resizeRowsToContents(); 
	//viewport()->stackUnder(frozenTableView);
	m_pTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pTableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pTableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
}

Pluginloader::~Pluginloader()
{

}

 void Pluginloader::applyChange()
 {
  	for(int i = 0; i < pluginList.length(); i++)
  	{
  		QString plugiName = pluginList.at(i);
  		QCheckBox* chBox = qobject_cast<QCheckBox*>(m_pTableWidget->cellWidget(i,1));
  		PluginManager::instance()->insertPluginItem(plugiName, chBox->isChecked());
  		if (!chBox) continue;
  		if (PluginManager::instance()->getPluginValueByName(plugiName) == chBox->isChecked()) continue;
  		else
  		{
  			PluginManager::instance()->setPluginValueByName(plugiName, chBox->isChecked());
  		}
  	}
  	qDebug()<< PluginManager::instance()->getPluginMap();
 }

 void Pluginloader::OnBtnOKClicked()
 {
 	applyChange();
 	m_eventloop.exit(0);
 	close();
 }

 void Pluginloader::closeEvent( QCloseEvent * )
 {
 	applyChange();
 	
 	m_eventloop.exit(0);
 	emit reload();
	close();
 }


void Pluginloader::resizeEvent(QResizeEvent* e)
{
	if (m_pTableWidget)
	{
		m_pTableWidget->setGeometry(0, 0, width(), height());
	}
}

void Pluginloader::paintEvent(QPaintEvent* e)
{
 	QStyleOption opt;
 	opt.init(this);
 	QPainter p(this);
 	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 	QWidget::paintEvent(e);
}

 void Pluginloader::showModel()
 {
   	show();
   	m_eventloop.exec();
 }


bool Pluginloader::getInfoPanel()
{
	return SysConfig::getValue("InfoPanel").toBool();
}

void Pluginloader::setInfoPanel(bool value)
{
	SysConfig::setValue("InfoPanel", value);
}

bool Pluginloader::getInteLayers()
{
	return SysConfig::getValue("InteLayers").toBool();
}

void Pluginloader::setInteLayers(bool value)
{
	SysConfig::setValue("InteLayers", value);
}

bool Pluginloader::getMapTab()
{
	return SysConfig::getValue("MapTab").toBool();
}

void Pluginloader::setMapTab(bool value)
{
	SysConfig::setValue("MapTab", value);
}

bool Pluginloader::getToolBox()
{
	return SysConfig::getValue("ToolBox").toBool();
}

void Pluginloader::setToolBox(bool value)
{
	SysConfig::setValue("ToolBox", value);
}