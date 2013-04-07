#include "V_GridWindow.h"

V_GridWindow::V_GridWindow(HINSTANCE hinstance, HWND hWndParent)
{
	RECT        r;
    // Draw bars
    GetClientRect(hWndParent, &r);

	init(hinstance, hWndParent, r.left, r.top, r.right- r.left, r.bottom- r.top);
}

V_GridWindow::V_GridWindow(HINSTANCE hinstance, HWND hWndParent, int x, int y, int width, int height)
{
	init(hinstance, hWndParent, x, y, width, height);
}

void V_GridWindow::init(HINSTANCE hinstance, HWND hWndParent, int x, int y, int width, int height){
	//init variables
	this->state = VALID;
	this->hinstance = hinstance; 
	this->hWndParent = hWndParent;
	this->x = x; 
	this->y = y;
	this->width = width; 
	this->height = height;

	//this->scrollVPos = 0;

	//init event handlers
	this->OnPaint = NULL;

	if(regWClass()){
		if(!createWND()) this->state = INVALID;
	}else this->state = INVALID;
}

V_GridWindow::~V_GridWindow(void)
{
	//destroy window
	DestroyWindow(hWnd);
}

bool V_GridWindow::regWClass(void){
	WNDCLASS wc; 

	//register class
	if(!GetClassInfo(hinstance, TEXT(WNDCLASSNAMESTR), &wc)){
		wc.style = 0; //CS_HREDRAW | 
			//CS_VREDRAW;                    // redraw if size changes 
		wc.lpfnWndProc = (WNDPROC) GRIDClassProc;     // points to window procedure 
		wc.cbClsExtra = 0;                // no extra class memory 
		wc.cbWndExtra = 0;                // no extra window memory 
		wc.hInstance = hinstance;         // handle to instance 
		wc.hIcon = LoadIcon(NULL, 
			IDI_APPLICATION);              // predefined app. icon 
		wc.hCursor = LoadCursor(NULL, 
			IDC_ARROW);                    // predefined arrow 
		wc.hbrBackground = (HBRUSH) GetStockObject( 
			WHITE_BRUSH);                  // white background brush 
		wc.lpszMenuName =  NULL;    // name of menu resource 
		wc.lpszClassName = TEXT(WNDCLASSNAMESTR);  // name of window class 
		
		return RegisterClass(&wc) != 0;

	}

	return true;

}

bool V_GridWindow::createWND(void){
	TCHAR wndname[255];

	hWnd = CreateWindow( 
        TEXT(WNDCLASSNAMESTR),        // name of window class 
		lstrcat(
			lstrcpy((LPTSTR)&wndname, 
					TEXT(WNDCLASSNAMESTR)
					), 
			TEXT("_#num")
				),            // title-bar string 
        WS_BORDER | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, // top-level window 
        x,       //  horizontal position 
        y,       //  vertical position 
        width,       //  width 
        height,       //  height 
        hWndParent,         // owner window 
        (HMENU) NULL,        // use class menu 
        hinstance,           // handle to application instance 
        this);      

    return hWnd != 0;
}

bool V_GridWindow::display(bool isShow){
	int res = ShowWindow(hWnd, (isShow)?SW_SHOW:SW_HIDE);
	if(isShow) UpdateWindow(hWnd);
	return res != 0;
}

//WND PROCs
//---------------------------------------------------------------------------------------

//CLASS PROC
LRESULT CALLBACK V_GridWindow::GRIDClassProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{ 
	switch (uMsg) 
	{
		case WM_NCCREATE:
		{
			CREATESTRUCT *pCrstruct = (CREATESTRUCT *)(lParam);
			V_GridWindow *p_gridWindow = (V_GridWindow *)(pCrstruct->lpCreateParams);
			p_gridWindow->hWnd = hwnd;
			::SetWindowLongPtr(hwnd, GWL_USERDATA, (long)pCrstruct->lpCreateParams);
			//::GetWindowRect(hwnd, &(pStaticDlg->_rc));
            p_gridWindow->GRIDWNDProc(hwnd, uMsg, wParam, lParam);
			
			return TRUE;
		}
		case WM_ERASEBKGND:
		{
            return TRUE;
		}

		default :
		{
			V_GridWindow *p_gridWindow = reinterpret_cast<V_GridWindow *>(::GetWindowLongPtr(hwnd, GWL_USERDATA));
			if (!p_gridWindow)
				return FALSE;
			return p_gridWindow->GRIDWNDProc(hwnd, uMsg, wParam, lParam);
		}
	}
}
//WND PROC
LRESULT CALLBACK V_GridWindow::GRIDWNDProc(
    HWND hwnd,        // handle to window
    UINT uMsg,        // message identifier
    WPARAM wParam,    // first message parameter
    LPARAM lParam)    // second message parameter
{ 
	switch (uMsg) 
	{
		case WM_CREATE:
		{
    		break;
		}

	    case WM_PAINT:
		{
			V_EventOnPaint eventOnPaint;
			//eventOnPaint.scrollVPos=scrollVPos;
			eventOnPaint.result = 0;
			paintWnd(eventOnPaint);
			return eventOnPaint.result;
		}

		case WM_SIZE:
		{
			break;	
		}

		case WM_NOTIFY:
		{
			break;
		}

		case WM_DESTROY:
		{
			break;
		}
		case WM_VSCROLL:
		{
			SCROLLINFO si; 
	        // Get all the vertial scroll bar information
		    si.cbSize = sizeof (si);
            si.fMask  = SIF_ALL;
            GetScrollInfo (hwnd, SB_VERT, &si);

			V_EventOnVScrolled eventOnVScrolled;
			eventOnVScrolled.hwnd =hwnd;
			eventOnVScrolled.si = si;
			eventOnVScrolled.scrollType = LOWORD (wParam);
			eventOnVScrolled.result = 0;
			
			if(OnVScrolled){				
				OnVScrolled(eventOnVScrolled);
			}

			return eventOnVScrolled.result;

		}
		case WM_HSCROLL:
		{
			SCROLLINFO si; 
	        // Get all the vertial scroll bar information
		    si.cbSize = sizeof (si);
            si.fMask  = SIF_ALL;
            GetScrollInfo (hwnd, SB_HORZ, &si);

			V_EventOnHScrolled eventOnHScrolled;
			eventOnHScrolled.hwnd =hwnd;
			eventOnHScrolled.si = si;
			eventOnHScrolled.scrollType = LOWORD (wParam);
			eventOnHScrolled.result = 0;
			
			if(OnHScrolled){				
				OnHScrolled(eventOnHScrolled);
			}

			return eventOnHScrolled.result;
		}

		/*case WM_GRID_DATA_AVAILABLE:
		{
			V_EventOnGridDataAvailable eventOnGridDataAvailable;
			eventOnGridDataAvailable.hwnd = hWnd;
			OnGridDataAvailable(eventOnGridDataAvailable);
			return eventOnGridDataAvailable.result;
		}*/
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return FALSE;
}

void V_GridWindow::setVScrollRawRange(int nmin, int nmax){
	SCROLLINFO si; 
	        // Get all the vertial scroll bar information
	si.cbSize = sizeof (si);
	si.fMask = SIF_RANGE;
	si.nMin = nmin;
	si.nMax = nmax;
	SetScrollInfo (hWnd, SB_VERT, &si, TRUE);
}

void V_GridWindow::setHScrollRawRange(int nmin, int nmax){
	SCROLLINFO si; 
	        // Get all the vertial scroll bar information
	si.cbSize = sizeof (si);
	si.fMask = SIF_RANGE;
	si.nMin = nmin;
	si.nMax = nmax;
	SetScrollInfo (hWnd, SB_HORZ, &si, TRUE);
}

void V_GridWindow::paintWnd(V_EventOnPaint &eventOnPaint){
	if(OnPaint){
		PAINTSTRUCT ps;
		RECT        r;
	
		HDC m_hdc = ::BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &r);
	
		eventOnPaint.m_hdc = m_hdc;
		eventOnPaint.ps= &ps;
		eventOnPaint.r =&r;
		eventOnPaint.hwnd =hWnd;
		OnPaint(eventOnPaint);
		::EndPaint(hWnd, &ps);
	}
}