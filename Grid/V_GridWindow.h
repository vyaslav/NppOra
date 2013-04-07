#pragma once

#include <windows.h>
#include <tchar.h>
#include <boost/function.hpp>
#include "V_G_Events.h"
#define WNDCLASSNAMESTR "V_UIGRID"

enum V_GridWindow_STATE{
	VALID,
	INVALID,
};

class V_GridWindow
{
public:
	V_GridWindow(HINSTANCE hinstance, HWND hWndParent);
	V_GridWindow(HINSTANCE hinstance, HWND hWndParent, int x, int y, int width, int height);
	~V_GridWindow(void);

	bool display(bool isShow);
	HWND getHWND(void){
		return hWnd;
	}
	void setVScrollRawRange(int nmin, int nmax);
	void setHScrollRawRange(int nmin, int nmax);

	V_EVENT_PROVIDER(Paint);
	V_EVENT_PROVIDER(VScrolled);
	V_EVENT_PROVIDER(HScrolled);
	V_EVENT_HENDLER_DEF(Resized)
	//V_EVENT_PROVIDER(GridDataAvailable);
private:
	void init(HINSTANCE hinstance, HWND hWndParent, int x, int y, int width, int height);

	bool regWClass(void);
	bool createWND(void);
	//WNDCLASProc
	static LRESULT CALLBACK GRIDClassProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	LRESULT CALLBACK GRIDWNDProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	void paintWnd(V_EventOnPaint &eventOnPaint);
	//event procs
	//LRESULT OnPaint(void);	
	//LRESULT (* OnPaint)(HDC, PAINTSTRUCT*, RECT*);


	HINSTANCE hinstance;
	HWND hWndParent;
	HWND hWnd;
	V_GridWindow_STATE state;
	
	int x;
	int y;
	int width;
	int height;
	//int scrollVPos;
};
