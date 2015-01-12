#include "stdafx.h"
#include "pluginspec.h"
#include <QtXml>
#include <QtCore>

using namespace ExtensionSystem;

PluginSpec::~PluginSpec() 
{
//    delete this;
}


PluginSpec::PluginSpec(const QString& fn) 
{
    qDebug() << "Loading " << fn<<" Spec";
    QDomDocument document;
    QFile file(fn);
    file.open(QFile::ReadOnly);
    int errorColumn, errorLine;
    QString errorStr;

    if (!document.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) 
	{
        qDebug() << QObject::tr("Parse error at line %1, column %2:\n%3")
        .arg(errorLine)
        .arg(errorColumn)
        .arg(errorStr);
        return;
    }

    QDomNode n = document.firstChild();

    QDomElement root = n.toElement();
    n = root.firstChild();
	this->Name = root.attribute("name");
	this->Version = root.attribute("version");
	this->CompatVersion = root.attribute("compatVersion");
	
    while (!n.isNull()) 
	{
        QDomElement e = n.toElement();
        QString tn = e.tagName();

		if (tn == "vendor") 
		{
			this->Vendor = e.firstChild().toText().data();
		}

		else if (tn == "copyright") 
		{
			this->CopyRight = e.firstChild().toText().data();
		}

		else if (tn == "license") 
		{
			this->License = e.firstChild().toText().data();
		}

		else if (tn == "category")
		{
			this->Category = e.firstChild().toText().data();
		}
		else if (tn == "description") 
		{
			this->Description = e.firstChild().toText().data();
		}

		else if (tn == "url") 
		{
			this->Url = e.firstChild().toText().data();
		}

		else if (tn == "dependencyList") 
		{
			QDomNode de = e.firstChild();

			while (!de.isNull()) 
			{
				QDomElement el = de.toElement();
				SpecDependencyData temp;
				temp.Name = el.attribute("name");
				temp.Version = el.attribute("version");
				this->DependencyList.append(temp);
				de = de.nextSibling();
			}
		}

		n = n.nextSibling();
	}

    file.close();

    this->m_state = NotLoad;
}


QString PluginSpec::name() const 
{
    return this->Name;
}


QString PluginSpec::version() const 
{
    return this->Version;
}


QString PluginSpec::author() const 
{
    return this->Author;
}


QString PluginSpec::bugReportEmail() const 
{
    return this->BugReportEMail;
}


QList<SpecDependencyData> PluginSpec::dependencyList() const 
{
    return this->DependencyList;
}


QString PluginSpec::license() const 
{
    return this->License;
}


QString PluginSpec::category() const 
{
    return this->Category;
}


QString PluginSpec::copyRight() const 
{
    return this->CopyRight;
}


QString PluginSpec::description() const 
{
    return this->Description;
}


int PluginSpec::getState() const 
{
    return m_state;
}


void PluginSpec::setState(int st) 
{
    m_state = st;
}


bool PluginSpec::operator == (const QString& name) 
{
    return this->Name == name;
}


bool PluginSpec::operator == (const PluginSpec& other) 
{
    return this->Name == other.Name;
}

QString PluginSpec::url() const
{
	return Url;
}

QString PluginSpec::compatVersion() const
{
	return CompatVersion;
}

QString PluginSpec::vendor() const
{
	return Vendor;
}
