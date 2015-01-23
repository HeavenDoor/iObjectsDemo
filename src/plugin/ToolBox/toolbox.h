#ifndef TOOLBOX_H
#define TOOLBOX_H

#include "toolbox_global.h"
#include "..\\..\\interface\\toolboxinterface.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QObject>

class ToolBox : public QWidget , ToolBoxInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "{E10C47F9-2D9E-4096-B08E-22CAA71B52BB}" FILE "toolbox.json")
	Q_INTERFACES(ToolBoxInterface)
public:
	ToolBox(QWidget *parent = 0);
	~ToolBox();
	virtual void test();
	//virtual QWidget* getWidget();
	virtual QObject* getObject();
	virtual void setPluginGeometry(const QRect& rect);
	virtual void setPluginGeometry(int ax, int ay, int aw, int ah);
	virtual void setPluginParent(QWidget* parentWidget);
	virtual void showPlugin();
	virtual void raisePlugin();
	virtual void lowerPlugin();
	virtual void resizePlugin(int ax, int ay, int aw, int ah);
	virtual void setPluginWidth(int width);
	virtual void setPluginHeight(int height);
	virtual int pluginWidth();
	virtual int pluginHeight();


	virtual QObject* createToolButton(const QString& objectName, Qt::Alignment align = Qt::AlignLeft);
	virtual void setToolButtonSize(QSize size);
signals:
	//void resize(const QRect&);
	void ToolBoxPlugin_SearchBtnClicked();
	void ToolBoxPlugin_SettingBtnClicked();
public slots:
	//void OnResizeEvent(const QRect& rect);
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent *);
private:
	QHBoxLayout* m_pOutLayout;
	QHBoxLayout* m_pLeftLayout;
	QHBoxLayout* m_pRightLayout;
// 	QPushButton* m_pSearch;
// 	QPushButton* m_pSet;
	QSize m_size;
};

#endif // TOOLBOX_H
