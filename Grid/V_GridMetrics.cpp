#include "V_GridMetrics.h"

V_GridMetrics::V_GridMetrics(){
	defColSize = 100;
	defRowSize = 30;
	defBorderSize = 1;
	columns = new V_Columns(0, defColSize);
	rows = new V_Rows(0, defRowSize);
	border = new V_Border(defBorderSize);
}

void V_GridMetrics::setupColumns(int x){
	V_Columns* newColumns = new V_Columns(x, defColSize);
	int copySz = (columns->count < newColumns->count)?columns->count:newColumns->count;
	for(int i=0; i< copySz; i++)
		newColumns->sizes[i] = columns->sizes[i];
	V_Columns* oldColumns = columns;
	columns = newColumns;
	delete oldColumns;
}

void V_GridMetrics::setupRows(int y){
	V_Rows* newRows = new V_Rows(y, defRowSize);
	V_Rows* oldRows = rows;
	rows = newRows;
	delete oldRows;
}

void V_GridMetrics::setupBorder(int sz){
	V_Border* newBorder = new V_Border(sz);
	V_Border* oldBorder = border;
	border = newBorder;
	delete oldBorder;
}

int V_GridMetrics::getColX(int colNum){
	int bordersColSz = border->getSize() * (colNum+1);
	int colsSz = 0;
	for(int i=0; i< colNum; i++){
		colsSz += columns->getSize(i);
	}

	return bordersColSz + colsSz;
}

int V_GridMetrics::getRowY(int rowNum){
	return border->getSize() * (rowNum+1) + rows->getSize() * rowNum;
}

int V_GridMetrics::getRowNumByY(int y){
	return y/(border->getSize() + rows->getSize());
}

RECT V_GridMetrics::getCellRect(int x, int y){
	RECT rect;
	rect.top = getRowY(y);
	rect.left = getColX(x);
	rect.bottom = rect.top + rows->getSize();
	rect.right = rect.left + columns->getSize(x);
	return rect;

}

RECT V_GridMetrics::getBorderRectH(int num){
	RECT rect;
	rect.top = getRowY(num) - border->getSize();
	rect.left = 0;
	rect.bottom = rect.top;
	rect.right = getColX(columns->getCount()) - border->getSize();
	return rect;
}

RECT V_GridMetrics::getBorderRectV(int num){
	RECT rect;
	rect.top = 0;
	rect.left = getColX(num) - border->getSize();
	rect.bottom = getRowY(rows->getCount()) - border->getSize();
	rect.right = rect.left;
	return rect;
}

V_EVENT_HENDLER_DEC(V_GridMetrics, DataSizeChanged)
{
	int x = v_event.x;
	int y = v_event.y;

	setupColumns(x);
	setupRows(y);

}