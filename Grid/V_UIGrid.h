#pragma once
#include <windows.h>
#include "V_GridWindow.h"
#include "V_GridData.h"
#include "V_GridRenderer.h"
#include "V_GridMetrics.h"
#include "V_GridController.h"
#include <boost/bind.hpp>
class V_UIGrid
{
	friend class OutputDialog;
public:
	V_UIGrid(HINSTANCE hinstance, HWND hWndParent);
	V_UIGrid();
	~V_UIGrid(void);

	V_GridWindow* getGridWindow(){
		return gridWindow;
	};

	//V_EVENT_HENDLER_DEF(DataThread)
	//V_EVENT_PROVIDER(DataThread)

private:
	//Grid heart
	V_GridWindow	 *gridWindow;
	V_GridRenderer	 *gridRenderer;
	V_GridController *gridController;
	V_GridData		 *gridData;
	V_GridMetrics	 *gridMetrics;
	
};
