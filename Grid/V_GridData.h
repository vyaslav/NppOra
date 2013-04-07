#pragma once
#include <vector>
#include <string>
#include "V_G_Events.h"
class V_GridData
{
public:
	V_GridData(void);
	~V_GridData(void);
	
	typedef std::vector<std::string*> V_GridRows;
	typedef std::vector<std::string*>::iterator V_GridRow;

	void createTable(int x = 0, int y =0);
	void appendRow();
	void setCellValue(int x, int y, const std::string& value);
	std::string getCellValue(int x, int y);

	V_EVENT_PROVIDER(DataSizeChanged)
	//CPU and compiler memory barrier... hopefully
	//volatile short sync;

	//temp
	//long val;
	bool isCommited(){
		return commited;
	}

	void commit(){
		commited=true;
	}
private:
	void destroyTable();

	void V_GridData::dataSizeChanged(int x, int y);

	V_GridRows* data;
	int X;
	int Y;
	bool commited;
};
