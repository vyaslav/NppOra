#include "V_GridController.h"

V_GridController::V_GridController(V_GridData* data, V_GridMetrics* metrics)
{
	this->data = data;
	this->metrics = metrics;
}

V_GridController::~V_GridController(void)
{
}

//EVENT PROCs
//---------------------------------------------------------------------------------------
V_EVENT_HENDLER_DEC(V_GridController, VScrolled)
{
	HWND hwnd = v_event.hwnd;
	SCROLLINFO si = v_event.si;
	int scrollType = v_event.scrollType;

	// Save the position for comparison later on
	int yPos = si.nPos;
	switch (scrollType)
	{
	// user clicked the HOME keyboard key
	case SB_TOP:
		si.nPos = si.nMin;
		break;
		
	// user clicked the END keyboard key
	case SB_BOTTOM:
		si.nPos = si.nMax;
		break;
		
	// user clicked the top arrow
	case SB_LINEUP:
		si.nPos -= 1;
		break;
		
	// user clicked the bottom arrow
	case SB_LINEDOWN:
		si.nPos += 1;
		break;
		
	// user clicked the scroll bar shaft above the scroll box
	case SB_PAGEUP:
		si.nPos -= si.nPage;
		break;
		
	// user clicked the scroll bar shaft below the scroll box
	case SB_PAGEDOWN:
		si.nPos += si.nPage;
		break;
		
	// user dragged the scroll box
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
		
	default:
		break; 
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo (hwnd, SB_VERT, &si, TRUE);
	GetScrollInfo (hwnd, SB_VERT, &si);
	// If the position has changed, scroll window and update it
	if (si.nPos != yPos)
	{                    
	int yChar = metrics->getRowSize()+metrics->getBorderSize();
	ScrollWindow(hwnd, 0, yChar * (yPos - si.nPos), NULL, NULL);
	//UpdateWindow (hwnd);
	InvalidateRect(hwnd, NULL, TRUE); 
	
	}


    v_event.result = 0;
}

V_EVENT_HENDLER_DEC(V_GridController, HScrolled)
{
	HWND hwnd = v_event.hwnd;
	SCROLLINFO si = v_event.si;
	int scrollType = v_event.scrollType;

	// Save the position for comparison later on
	int xPos = si.nPos;
	switch (scrollType)
	{
		
	// user clicked the top arrow
	case SB_LINELEFT:
		si.nPos -= 1;
		break;
		
	// user clicked the bottom arrow
	case SB_LINERIGHT:
		si.nPos += 1;
		break;
		
	// user clicked the scroll bar shaft above the scroll box
	case SB_PAGELEFT:
		si.nPos -= si.nPage;
		break;
		
	// user clicked the scroll bar shaft below the scroll box
	case SB_PAGERIGHT:
		si.nPos += si.nPage;
		break;
		
	// user dragged the scroll box
	case SB_THUMBTRACK:
		si.nPos = si.nTrackPos;
		break;
		
	default:
		break; 
	}
	// Set the position and then retrieve it.  Due to adjustments
	//   by Windows it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo (hwnd, SB_HORZ, &si, TRUE);
	GetScrollInfo (hwnd, SB_HORZ, &si);
	// If the position has changed, scroll window and update it
	if (si.nPos != xPos)
	{                    
	int xChar = 1;
	ScrollWindow(hwnd, xChar * (xPos - si.nPos), 0, NULL, NULL);
	//UpdateWindow (hwnd);
	InvalidateRect(hwnd, NULL, TRUE); 
	}


    v_event.result = 0;
}
