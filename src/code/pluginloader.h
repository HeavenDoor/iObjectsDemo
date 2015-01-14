#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

class Pluginloader : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(bool InfoPanel READ getInfoPanel WRITE setInfoPanel)
	Q_PROPERTY(bool MapTab READ getMapTab WRITE setMapTab)
	Q_PROPERTY(bool InteLayers READ getInteLayers WRITE setInteLayers)
	Q_PROPERTY(bool ToolBox READ getToolBox WRITE setToolBox)
public:
	Pluginloader(QWidget *parent);
	~Pluginloader();
	void showModel();

	bool getInfoPanel();
	void setInfoPanel(bool value);
	bool getInteLayers();
	void setInteLayers(bool value);
	bool getMapTab();
	void setMapTab(bool value);
	bool getToolBox();
	void setToolBox(bool value);

protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void closeEvent(QCloseEvent *);
signals:
	void reload();
private slots:
	void OnBtnOKClicked();

private:
	void applyChange();
private:
	QEventLoop m_eventloop;
	QTableWidget* m_pTableWidget;
	QStringList pluginList;
};

#endif // PLUGINLOADER_H
