#include "stdafx.h"
#include "fileutils.h"

FileUtils::FileUtils(QObject *parent)
	: QObject(parent)
{

}

FileUtils::~FileUtils()
{

}

QStringList FileUtils::getAllFileByExtensionsName( const QString & extensions, const QString& path )
{
	QStringList list;

 	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo kk(exeFileName);
	QString apppath = kk.canonicalPath(); 
	QString ss = QDir::currentPath();
 	QDir::setCurrent(apppath);

	QDir dir(path);
	
	QFileInfoList fileInfoList = dir.entryInfoList();
	foreach( QFileInfo fileInfo, fileInfoList)
	{
		if (fileInfo.fileName() == "." || fileInfo.fileName() == ".." || fileInfo.isDir())
			continue;

		if (fileInfo.suffix() == extensions)
		{
			QString yy = fileInfo.suffix();
			list.push_back(fileInfo.baseName());
		}
		

	}
	QDir::setCurrent(ss);
	return list;
}


// QString ss = fileInfo.fileName();

//QString yy = fileInfo.suffix();
//
//QString pp = fileInfo.fileName();
//QString gh = fileInfo.baseName();