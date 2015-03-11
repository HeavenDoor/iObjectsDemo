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

	// ToolBox容器中加入Button，objectName： Button的objectName  align： Button在Left还是Right  默认Left
	QObject* createToolButton(const QString& objectName, Qt::Alignment align = Qt::AlignLeft);
	void addWidget(QWidget* w);
	void removeWidget(QWidget* w);
	// 设置ToolButton 大小
	void setToolButtonSize(QSize size);
	// 添加分割线
	void addLine(Qt::Alignment align = Qt::AlignLeft);
	// 添加空白区域
	void addSpacing(int space, Qt::Alignment align = Qt::AlignLeft);
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
