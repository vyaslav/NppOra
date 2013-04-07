#pragma once

#include <windows.h>
#include <tchar.h>
#include <boost/function.hpp>

#define WM_GRID_DATA_AVAILABLE (WM_USER + 0)

#define V_EVENT_PROVIDER(eve) boost::function<void (V_EventOn##eve &)> On##eve;
#define V_EVENT_BIND(src, destType, dest, eve) src->On##eve = boost::bind(&destType::Do##eve, dest, _1);
#define V_EVENT_HENDLER_DEF(eve) void Do##eve(V_EventOn##eve& v_event);
#define V_EVENT_HENDLER_DEC(hendlerType,eve) void hendlerType::Do##eve(V_EventOn##eve& v_event)
#define V_EVENT_DEC_STD(eve, content) class V_EventOn##eve : private V_Event{\
	public:\
		V_EventOn##eve():V_Event(EventOn##eve){};\
		content\
		};\

class V_EventHandler{

};

enum V_EventName{
	EventOnPaint,
	EventOnDataSizeChanged,
	EventOnGridDataAvailable,
	EventOnDataThread,
	EventOnResized,
	EventOnVScrolled,
	EventOnHScrolled
};

class V_Event{
	public:
		V_Event(V_EventName eventName){
			this->eventName = eventName;
		}

		V_EventName getEventName(){
			return eventName;
		}

	protected:
		V_EventName eventName;
};

V_EVENT_DEC_STD(Paint,
		HDC m_hdc;
		PAINTSTRUCT* ps;
		RECT* r;
		HWND hwnd;
		//int scrollVPos;

		LRESULT result;
		)

V_EVENT_DEC_STD(DataSizeChanged,
		int x;
		int y;
		)

V_EVENT_DEC_STD(GridDataAvailable,
		HWND hwnd;
		LRESULT result;
		)

V_EVENT_DEC_STD(DataThread,
		HWND hwnd;
		LRESULT result;
		)

V_EVENT_DEC_STD(Resized,
		HWND hwnd;
		int x;
		int y;
		)

V_EVENT_DEC_STD(VScrolled, 
		HWND hwnd;
		SCROLLINFO si;
		int scrollType;
		LRESULT result;
		)

V_EVENT_DEC_STD(HScrolled, 
		HWND hwnd;
		SCROLLINFO si;
		int scrollType;
		LRESULT result;
		)