//////////////////////////////////////////////////////////////////////////
// TabView�ؼ�
// �Ѳ��������ΪTabҳ����ʾ
//////////////////////////////////////////////////////////////////////////


#ifndef TABVIEW_H
#define TABVIEW_H

#include "tabbar.h"
#include "tabwidget.h"
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

class TabView : public QWidget
{
	Q_OBJECT
public:
	TabView(QWidget *parent = NULL);
	~TabView();

	// ���ҳ�� map�� ����ָ��  tabIndex��ҳ��˳�� ��0��ʼ��< 0 ʱ����ǰ�� tabName����ʾ��TabBar�ϵ�����
	void addCentralWidget(QWidget* map, int tabIndex, QString tabName);
	// ɾ��ҳ��
	void removeCentralWidget(QWidget* widget);
	// ���õ�ǰѡ��ҳ��
	void setCurrentIndex(int index); 
	// ����Ƥ��
	void loadDefaultSkin();
	// �����Զ���Ƥ��  styleSheet��qss�ַ���
	void loadCustomStyleSheet(const QString& styleSheet);
	// ���TabBarָ��
	QWidget* getTabBar();
signals:
	void moveTabPage(QWidget* map, QString tabName);
	void removeTabPage(QWidget* map, QString tabName);
	void tabViewChange();
public slots:
	void OnMoveTabPage(QWidget* map, QString tabName);
	void OnReMoveTabPage(QWidget* map, QString tabName);
protected:
	void paintEvent(QPaintEvent*);
	void resizeEvent(QResizeEvent*);
private slots:
	void OnChangeIndex(int index);
	void OnMoveTabPage(int index, QString tabName);
private:
	//void removeCentralWidgetEx( QWidget* widget );
private:
	static const int tabrheight = 81;
	TabWidget* m_pTabWidget;
	TabBar* m_pTabBar;
	
};

#endif // TABVIEW_H
