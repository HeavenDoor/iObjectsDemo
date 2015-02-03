#ifndef MAPLAYERS_H
#define MAPLAYERS_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLabel>
class MapLayers : public QWidget
{
	Q_OBJECT

public:
	MapLayers(QWidget *parent = NULL);
	~MapLayers();
	void initLayers(const QVector<QString>& layers);
signals:
	void changeLayers(const QString& text);
protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
private:
	QVBoxLayout* m_pLayersVLayout;
	QScrollArea* m_pLayersScroll;
	QWidget* m_pLayersContainer;
};

class EmptyWidget : public QWidget
{
	Q_OBJECT
public:
	EmptyWidget(QWidget *parent = NULL);
	~EmptyWidget();
signals:
	void changeLayers(const QString& text);
protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);
public:
	QLabel* m_pLayerText;
};



#endif // MAPLAYERS_H
