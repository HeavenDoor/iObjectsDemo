#ifndef IOBJECTSDEMO_H
#define IOBJECTSDEMO_H

#include <QtWidgets/QWidget>
#include <QApplication>

class iObjectsDemo : public QWidget
{
	Q_OBJECT

public:
	iObjectsDemo(QWidget *parent = 0);
	~iObjectsDemo();
	void test(){}
protected:
	void paintEvent(QPaintEvent*);

private slots:
	void OnCloseBtnClicked();
private:
	QPushButton* m_pCloseBtn;
};

#endif // IOBJECTSDEMO_H
