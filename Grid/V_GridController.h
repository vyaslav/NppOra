#pragma once
#include "V_G_Events.h"
#include "V_GridMetrics.h"
#include "V_GridData.h"

class V_GridController : public V_EventHandler
{
public:
	V_GridController(V_GridData* data, V_GridMetrics* metrics);
	~V_GridController(void);

	V_EVENT_HENDLER_DEF(VScrolled)
	V_EVENT_HENDLER_DEF(HScrolled)
	//V_EVENT_HENDLER_DEF(GridDataAvailable)
private:
	V_GridData* data;
	V_GridMetrics* metrics;
};
