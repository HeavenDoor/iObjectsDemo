#ifndef TABITEM_H
#define TABITEM_H

#include <QToolButton>
#include <QPixmap>

class TabItem : public QToolButton
{
	Q_OBJECT

public:
	TabItem(QString tabName = "", QWidget *parent = NULL);
	~TabItem();
	QPixmap getTabItemPixmap();
	void setSelected();
	void setDeselected();
	QString getLabelText();
protected:
	void dragEnterEvent(QDragEnterEvent * event) Q_DECL_OVERRIDE;
	void dragLeaveEvent(QDragLeaveEvent * event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);

	void resizeEvent(QResizeEvent *e);

signals:
	void flowUp();
private:
	QString m_text;
	QGraphicsScene* m_pScene;
	QGraphicsView* m_pView;
	QPushButton* m_pFlowBtn;
	QLabel* m_pTextLabel;
};

#endif // TABITEM_H
