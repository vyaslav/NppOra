#include "V_GridRenderer.h"

V_GridRenderer::V_GridRenderer(V_GridData* data, V_GridMetrics* metrics)
{
	this->data = data;
	this->metrics = metrics;
}

V_GridRenderer::~V_GridRenderer(void)
{
}

//EVENT PROCs
//---------------------------------------------------------------------------------------
V_EVENT_HENDLER_DEC(V_GridRenderer, Paint)
{

	HDC m_hdc =			v_event.m_hdc;
	PAINTSTRUCT* ps =   v_event.ps; 
	RECT* r=			v_event.r;
	HWND hwnd =			v_event.hwnd;

	HDC hdcMem = CreateCompatibleDC(m_hdc); 
	HBITMAP bitmap = CreateCompatibleBitmap(m_hdc, r->right - r->left, r->bottom - r->top); 
	HBITMAP oldBitmap = ((HBITMAP) SelectObject(hdcMem, bitmap)); 
	FillRect(hdcMem, r, CreateSolidBrush(GetBkColor(m_hdc))); 

if(data->isCommited()){

    // Get vertical scroll bar position
	SCROLLINFO si; 
    si.cbSize = sizeof (si);
    si.fMask  = SIF_POS;
    GetScrollInfo (hwnd, SB_VERT, &si);
    int yPos = si.nPos;
	int yChar = metrics->getRowSize()+metrics->getBorderSize();

	int startRow = metrics->getRowNumByY(yPos*yChar);
	int endRow = min(metrics->rows->getCount(), metrics->getRowNumByY(yPos*yChar+r->bottom - r->top)+1);

	int vScrollVal = yChar * (0 - yPos);
    // Get vertical scroll bar position
	SCROLLINFO siH; 
    siH.cbSize = sizeof (siH);
    siH.fMask  = SIF_POS;
	GetScrollInfo (hwnd, SB_HORZ, &siH);
    int xPos = siH.nPos;
	
	int xChar = 1;

	int hScrollVal = xChar * (0 - xPos);

	if(metrics->rows->getCount()>startRow)
	{

		//paint
		//draw vertical border
		for(int i=0;i<=metrics->columns->getCount();i++){
			RECT rect = metrics->getBorderRectV(i);
			MoveToEx(hdcMem, rect.left+hScrollVal, rect.top+vScrollVal, NULL);
			LineTo(hdcMem, rect.right+hScrollVal, rect.bottom+vScrollVal);
		}
		
		//draw horizontal border
		for(int i=startRow//v_event.scrollVPos
			;i<=endRow//metrics->rows->getCount()
			;i++){
			RECT rect = metrics->getBorderRectH(i);
			MoveToEx(hdcMem, rect.left+hScrollVal, rect.top+vScrollVal, NULL);
			LineTo(hdcMem, rect.right+hScrollVal, rect.bottom+vScrollVal);
		}
		
		for(int col=0;col<metrics->columns->getCount();col++)
			for(int row=startRow//v_event.scrollVPos
				;row<endRow//metrics->rows->getCount()
				;row++){
				std::string str = data->getCellValue(col, row);
				TCHAR *txt = new TCHAR[str.size()+1];
				txt[str.size()] = 0;
				std::copy(str.begin(),str.end(),txt);
				RECT rect = metrics->getCellRect(col, row);
				int x = rect.left+2+hScrollVal;
				int y = rect.top+2+vScrollVal;
				TextOut(hdcMem, x, y, txt, _tcslen(txt));
				delete txt;
			}
		
	}
}
	//DB
	BitBlt(m_hdc, r->left, r->top, r->right - r->left, r->bottom - r->top, hdcMem, 0, 0, SRCCOPY); 
	SelectObject(hdcMem, oldBitmap); 
	DeleteObject(bitmap); 
	DeleteDC(hdcMem); 

    v_event.result = 0;
}

V_EVENT_HENDLER_DEC(V_GridRenderer, Resized)
{
	HWND hwnd = v_event.hwnd;
	int x = v_event.x;
	int y = v_event.y;

	SetWindowPos(hwnd, HWND_TOP, 0, 0, x, y, SWP_NOMOVE | SWP_NOZORDER);



}
/*
V_EVENT_HENDLER_DEC(V_GridRenderer, GridDataAvailable)
{
	if(InterlockedCompareExchange((volatile LONG *)&(data->sync),(LONG)data->sync, (LONG) 1)){
		//PostMessage (v_event.hwnd, WM_PAINT, NULL, NULL);
		RedrawWindow(
		  v_event.hwnd,
		 NULL,
		 NULL,
		 RDW_INVALIDATE | RDW_UPDATENOW
		);
	}
	v_event.result = 0;
}*/
