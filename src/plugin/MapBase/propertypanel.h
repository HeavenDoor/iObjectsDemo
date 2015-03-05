#ifndef PROPERTYPANEL_H
#define PROPERTYPANEL_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
class PropertyPanel : public QWidget
{
	Q_OBJECT

public:
	PropertyPanel(QWidget *parent = NULL);
	~PropertyPanel();
	void setCentralWidget(QWidget* p);
	void setPropertyPanelTitle( const QString& title );
protected:
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
signals:
	void pinBtnClicked();
private:
	QVBoxLayout* m_pVLayout;
	QWidget* m_pHead;
	QWidget* m_pCentral;

	QLabel* m_pTitle;

	QVBoxLayout* m_pBodyLayout;
	QPushButton* m_pPinBtn;
};

#endif // PROPERTYPANEL_H
