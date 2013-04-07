#pragma once

#include "V_G_Events.h"

class V_Columns{
public:
	V_Columns(int count, int defColSize = 0){
		this->count = count;
		this->sizes = new int[count];
		for(int i=0;i<count;i++){
			this->sizes[i] = defColSize;
		}
	}

	~V_Columns(){
		delete[] sizes;
	}

	int count;
	int* sizes;

	int getCount(){
		return count;
	}

	int getSize(int x){
		return sizes[x];
	}
};

class V_Rows{
public:
	V_Rows(int count, int defRowSize = 0){
		this->count = count;
		this->size = defRowSize;
	}

	~V_Rows(){
	}

	int count;
	int size;

	int getCount(){
		return count;
	}

	int getSize(){
		return size;
	}
};

class V_Border{
public:
	V_Border(int size){
		this->size = size;
	}

	~V_Border(){
	}

	int size;

	int getSize(){
		return size;
	}
};

class V_GridMetrics{
public:
	V_GridMetrics();

	int getColX(int colNum);
	int getRowY(int rowNum);

	int getRowNumByY(int y);

	RECT getCellRect(int x, int y = 0);
	RECT getBorderRectH(int num); 
	RECT getBorderRectV(int num); 

	V_EVENT_HENDLER_DEF(DataSizeChanged)

	V_Columns* columns;
	V_Rows* rows;
	V_Border* border;

	int getRowSize(){
		return defRowSize;
	}
	int getBorderSize(){
		return defBorderSize;
	}

	int getAllColsSize(){
		int result = 0;
		for(int i=0; i< columns->count; i++)
			result += columns->sizes[i] + getBorderSize();
		return result;
	};

private:
	void setupColumns(int x);
	void setupRows(int y);
	void setupBorder(int sz);
	

	int defColSize;
	int defRowSize;
	int defBorderSize;
};