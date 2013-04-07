#include "V_UIGrid.h"
#include "V_OraDatabase.h"
#include <boost/lexical_cast.hpp>
//prototype

//TEMP THREAD FUNC
/*DWORD WINAPI MyThreadFunction( LPVOID lpParam ) 
{ 
    V_UIGrid* grid;
    // Cast the parameter to the correct data type.
    // The pointer is known to be valid because 
    // it was checked for NULL before the thread was created.
 
    grid = (V_UIGrid*)lpParam;

	V_EventOnDataThread eventOnDataThread;
	//eventOnDataSizeChanged.x = x;
	while(true){
	Sleep(1);
	grid->OnDataThread(eventOnDataThread);
	}

    return eventOnDataThread.result; 
}*/ 



V_UIGrid::V_UIGrid(HINSTANCE hinstance, HWND hWndParent)
{
	gridWindow = new V_GridWindow(hinstance, hWndParent);
	gridData = new V_GridData();
	gridMetrics = new V_GridMetrics();
	gridRenderer = new V_GridRenderer(gridData, gridMetrics);
	gridController = new V_GridController(gridData, gridMetrics);

	V_EVENT_BIND(gridData, V_GridMetrics, gridMetrics, DataSizeChanged)
	
	/*V_OraDatabase db;
	std::list<std::string*>* strList = db.getData();
	gridData->createTable(2,strList->size());
	int idx=0;
	for(std::list<std::string*>::iterator i=strList->begin();i!=strList->end();i++){
		for(int j=0;j<2;j++)
			gridData->setCellValue(j,idx, (*(const std::string*)new std::string((*i)[j])));
		idx++;
	}*/
		
	//set data
	int rows=40000;
	int cols=100;
	for(int r=0;r<3;r++){
	gridData->createTable(cols,rows);
	for(int i=0;i<cols;i++){
		std::string colNameStr="COL";
		std::string colstr="_";
		colstr+=boost::lexical_cast<string>( i );
		colNameStr += colstr;
		gridData->setCellValue(i,0,colNameStr);//+boost::lexical_cast<string>( i ));
		for(int j=1;j<rows;j++){
			std::string rawstr=boost::lexical_cast<string>( j );
			rawstr+=colstr;
			gridData->setCellValue(i,j,rawstr);//+boost::lexical_cast<string>( i )+boost::lexical_cast<string>( j )); 
		}
	}
	gridData->commit();
	}
	
	gridWindow->setVScrollRawRange(0,rows);
	gridWindow->setHScrollRawRange(0,gridMetrics->getAllColsSize());
	//gridData->setCellValue(0,2,"HEY1"); gridData->setCellValue(1,2,"HEY2");
	//--


	V_EVENT_BIND(gridWindow, V_GridRenderer, gridRenderer, Paint)
	V_EVENT_BIND(gridWindow, V_GridController, gridController, VScrolled)
	V_EVENT_BIND(gridWindow, V_GridController, gridController, HScrolled)
	//V_EVENT_BIND(gridWindow, V_GridRenderer, gridRenderer, GridDataAvailable)
	//V_EVENT_BIND(this, V_UIGrid, this, DataThread)

	/*HANDLE  tId = 0;
	//TEMP THREAD GOES HERE
	tId = CreateThread( 
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            this,          // argument to thread function 
            0,                      // use default creation flags 
            NULL);   // returns the thread identifier 
	if(!tId){
		MessageBox(
				NULL,
				(LPCWSTR)L"Thread wasn't created",
				(LPCWSTR)L"Information",
				MB_OK
			);
	}*/
}

V_UIGrid::~V_UIGrid(void)
{
	gridWindow->OnPaint = NULL;
	gridWindow->OnVScrolled = NULL;
	gridWindow->OnHScrolled = NULL;
	gridData->OnDataSizeChanged = NULL;

	delete gridRenderer;
	delete gridController;
	delete gridWindow;
	delete gridMetrics;
	delete gridData;
}

/*V_EVENT_HENDLER_DEC(V_UIGrid, DataThread)
{
	gridData->val++;
	if(gridData->val > 10 || gridData->val <0) gridData->val = 0;

	long val = gridData->val;
	
	gridData->createTable(2,2);
	gridData->setCellValue(0,0, "WTF" + boost::lexical_cast<string>( val ) );
	gridData->setCellValue(0,1, "WTF" + boost::lexical_cast<string>( val+1 ));
	gridData->setCellValue(1,0, "WTF1"+ boost::lexical_cast<string>( val ));
	gridData->setCellValue(1,1, "WTF1"+ boost::lexical_cast<string>( val+1 ));

	InterlockedExchange((volatile LONG *)&(gridData->sync), (LONG) 1);
	PostMessage (gridWindow->getHWND(), WM_GRID_DATA_AVAILABLE, NULL, NULL);
	v_event.result = 0;
}*/
