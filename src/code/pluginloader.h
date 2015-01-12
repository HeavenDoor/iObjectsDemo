#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
class Pluginloader : public QWidget
{
	Q_OBJECT

public:
	Pluginloader(QWidget *parent);
	~Pluginloader();
	void showModel();
protected:
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);
	void closeEvent(QCloseEvent *);
private slots:
	void OnBtnCancleClicked();
	void OnBtnOKClicked();
private:
	QEventLoop m_eventloop;
	QPushButton* m_pBtnOK;
	QPushButton* m_pBtnCancle;
};

#endif // PLUGINLOADER_H
