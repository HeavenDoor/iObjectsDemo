#include "stdafx.h"
#include "iobjectsdemo.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "Map2D/map2dcontainer.h"
void initStyle();

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);


	QString b = QApplication::applicationDirPath();

	QString s1 = "汉语";
	QString s2("漢語");
	//QString s3 = tr("中文");
	QString s4 = QStringLiteral("中文");//只要字符串不需要翻译，请关注这个
	//QString s5 = QString::fromWCharArray(L"中文");
	//QString s6 = u8"中文";//C++11
	//QString s7 = tr(u8"中文");

	initStyle();
	iObjectsDemo w;
	w.show();

// 	Map2DContainer c;
// 	c.show();
	return a.exec();
}

void initStyle()  // 加载qss 
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