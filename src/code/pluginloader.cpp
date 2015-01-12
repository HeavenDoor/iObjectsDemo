#include "stdafx.h"
#include "pluginloader.h"

Pluginloader::Pluginloader(QWidget *parent) : QWidget(parent)
{
	setObjectName("Pluginloader");
	setWindowTitle("SuperMap iObjectsDemo Pulgin Manager");
// 	setWindowModality(Qt::ApplicationModal);
// 	setAttribute(Qt::WA_ShowModal, true);
	setFixedWidth(600);
	setFixedHeight(400);

	m_pBtnOK = new QPushButton(this);
	m_pBtnOK->setFixedHeight(35);
	m_pBtnOK->setFixedWidth(50);

	m_pBtnCancle = new QPushButton(this);
	m_pBtnCancle->setFixedHeight(35);
	m_pBtnCancle->setFixedWidth(50);

	connect(m_pBtnOK, SIGNAL(clicked()), this, SLOT(OnBtnOKClicked()));
	connect(m_pBtnCancle, SIGNAL(clicked()), this, SLOT(OnBtnCancleClicked()));
}

Pluginloader::~Pluginloader()
{

}

void Pluginloader::OnBtnOKClicked()
{
	m_eventloop.exit(0);
	close();
}

void Pluginloader::OnBtnCancleClicked()
{
	m_eventloop.exit(0);
	close();
}


void Pluginloader::closeEvent( QCloseEvent * )
{
	m_eventloop.exit(0);
	close();
}


void Pluginloader::resizeEvent(QResizeEvent* e)
{
	if (m_pBtnOK)
	{
		m_pBtnOK->setGeometry(width() - m_pBtnOK->width() - 20 - m_pBtnCancle->width(), height() - m_pBtnOK->height() - 10, m_pBtnOK->width(), m_pBtnOK->height());
	}
	if (m_pBtnCancle)
	{
		m_pBtnCancle->setGeometry(width() - m_pBtnCancle->width() - 10, height() - m_pBtnCancle->height() - 10, m_pBtnCancle->width(), m_pBtnCancle->height());
	}
}

void Pluginloader::paintEvent(QPaintEvent* e)
{

}

void Pluginloader::showModel()
{
	show();
	m_eventloop.exec();
}

