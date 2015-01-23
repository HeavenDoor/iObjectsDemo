#include "stdafx.h"
#include "infohandler.h"
#include <QDir>

InfoHandler::InfoHandler(QWidget *parent) : QObject(parent)
{
	m_pTimer = new QTimer(this);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(Ontimeout()));

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
	QDir::setCurrent(apppath);

	list = XmlUtils::ReadXml("vv.xml");
	index = 0;


	QList<QHash<QString,QString>> vd = XmlUtils::readXml("vv.xml");
// 
// 	foreach (QVariant v, list)
// 	{
// 		
// 		QString ss = v.toMap().value("info").toString();
// 		//qDebug()<<ss;
// 	}


	QDir::setCurrent(ss);
	run();
}

InfoHandler::~InfoHandler()
{

}

void InfoHandler::timerEvent( QTimerEvent * e)
{
	
}

void InfoHandler::run()
{
	m_pTimer->start(7000);
}

void InfoHandler::Ontimeout()
{
	if (list.length() < 1 || index >= list.length()) return;

	QString info;

	info = list.at(index).toMap().value("info").toString();
	emit infoChanged(info);

	if (index < list.length() - 1)
	{
		index ++;
	}
	else
	{
		index = 0;
	}
	
}
