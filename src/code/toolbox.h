#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QObject>

class ToolBox : public QWidget
{
	Q_OBJECT
public:
	ToolBox(QWidget *parent = NULL);
	~ToolBox();

	// ToolBox�����м���Button��objectName�� Button��objectName  align�� Button��Left����Right  Ĭ��Left
	QObject* createToolButton(const QString& objectName, Qt::Alignment align = Qt::AlignLeft);
	// ����ToolButton ��С
	void setToolButtonSize(QSize size);
signals:
public slots:

protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent *);
private:
	QHBoxLayout* m_pOutLayout;
	QHBoxLayout* m_pLeftLayout;
	QHBoxLayout* m_pRightLayout;

	QSize m_size;
};

#endif // TOOLBOX_H
