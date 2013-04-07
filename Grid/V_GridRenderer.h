#pragma once
#include "V_G_Events.h"
#include "V_GridMetrics.h"
#include "V_GridData.h"

class V_GridRenderer : public V_EventHandler
{
public:
	V_GridRenderer(V_GridData* data, V_GridMetrics* metrics);
	~V_GridRenderer(void);

	V_EVENT_HENDLER_DEF(Paint)
	V_EVENT_HENDLER_DEF(Resized)
	//V_EVENT_HENDLER_DEF(GridDataAvailable)
private:
	V_GridData* data;
	V_GridMetrics* metrics;
};
