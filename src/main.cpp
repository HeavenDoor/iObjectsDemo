#include "stdafx.h"
#include "iobjectsdemo.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

void initStyle();

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
	initStyle();
	iObjectsDemo w;
	w.show();
	return a.exec();
}

void initStyle()  // ¼ÓÔØqss 
{
	QString path = QApplication::applicationDirPath();

	QString exeFileName = QApplication::applicationFilePath();
	QFileInfo f(exeFileName);
	QString appPath = f.canonicalPath();
	QFile file(":/skin.qss");
	file.open(QFile::ReadOnly);
	QString style = QString(file.readAll());
	qApp->setStyleSheet(style);
	file.close();
}