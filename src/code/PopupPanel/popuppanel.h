#ifndef POPUPPANEL_H
#define POPUPPANEL_H

#include <QtWidgets/QWidget>
#include <QtWebKitWidgets/QWebView>

class PopupPanel : public QWidget
{
	Q_OBJECT

public:
	PopupPanel(QWidget *parent = NULL, int xPos = 147);
	~PopupPanel();
protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
	bool eventFilter(QObject* obj, QEvent* e);
signals:
	void closePopupPanel();
private slots:
	void OnBtnClose();
public:
	int m_Xpos;
private:
	QWidget* m_pPopupBody;
	QWidget* m_pPopupTail;
	QWebView* m_pWebView;
	QPushButton* m_pCloseBtn;
};

#endif // POPUPPANEL_H
