#ifndef PLUGINSPEC_H
#define PLUGINSPEC_H

#include <QObject>
#include <QtCore>
//#include "ExtensionSystem_global.h"

namespace ExtensionSystem {
//struct PluginSpecInnerData;/// Plugin Spec Inner Data. Plugin�ĳ�Ա����
/**
 * ��ʾPlugin ������ϵ��Data
 *       �������ڵ�Name����Ӧ��Version
 *
 */

struct SpecDependencyData {
    QString Name;
    QString Version;
};

/**
 * Plugin Spec
 *       Plugin�����ļ��ĳ���ͨ�������ļ���������Plugin
 *
 */

class PluginSpec { //: public QObject
//Q_OBJECT

public:
    enum State {
        NotLoad = 0,
        Loaded = 1,
        BeforeInit = 2,
        Inited = 4,
        Completed = 8,
        Error = -1
    };

    explicit PluginSpec(const QString& fn);
    virtual ~PluginSpec();
    QString name() const;
    QString version() const;
	QString compatVersion() const;
	QString vendor() const;
    QString author() const;
    QString bugReportEmail() const;
    QList<SpecDependencyData> dependencyList() const;
	QString url() const;
    QString description() const;
    QString category() const;
    QString copyRight() const;
    QString license() const;
    int getState() const;
    void setState(int st);
//    signals:
    bool operator == (const QString& name);
    bool operator == (const PluginSpec& other);
private:
    QString Version;
    QString Name;
	QString CompatVersion;
	QString Vendor;
    QString Author;
    QString CopyRight;
    QString License;
    QString Url;
    QString BugReportEMail;
    QString Description;
    QString Category;
    QList<SpecDependencyData > DependencyList;
    int m_state;
};

}

#endif                                            // PLUGINSPEC_H
