#include "stdafx.h"
#include "infopanel.h"



int TimeModel::instances=0;
MinuteTimer *TimeModel::timer=0;


InfoPanel::InfoPanel()
{

}

InfoPanel::~InfoPanel()
{

}

void InfoPanel::registerTypes( const char *uri )
{
	// Q_ASSERT(uri == QLatin1String("TimeExample"));
	qmlRegisterType<TimeModel>(uri, 1, 0, "Time");
}
