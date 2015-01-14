#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>

class FileUtils : public QObject
{
	Q_OBJECT

public:
	FileUtils(QObject *parent);
	~FileUtils();
	static QStringList getAllFileByExtensionsName(const QString & extensions, const QString& path );
private:
	
};

#endif // FILEUTILS_H
