#ifndef TABITEM_H
#define TABITEM_H

#include <QToolButton>
#include <QPixmap>

class TabItem : public QToolButton
{
	Q_OBJECT

public:
	TabItem(QWidget *parent = NULL);
	~TabItem();
	QPixmap getTabItemPixmap();
protected:
	void dragEnterEvent(QDragEnterEvent * event) Q_DECL_OVERRIDE;
	void dragLeaveEvent(QDragLeaveEvent * event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	
};

#endif // TABITEM_H
