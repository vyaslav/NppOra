#include "V_GridData.h"

V_GridData::V_GridData(void):data(NULL),X(0),Y(0)
{
	createTable();
	this->OnDataSizeChanged = NULL;
	//sync = 1;
}

V_GridData::~V_GridData(void)
{
	destroyTable();
}

void V_GridData::createTable(int x, int y){
	commited=false;
	if(data) destroyTable();
	data = new V_GridRows(y);
	for(V_GridRow iter = data->begin();iter != data->end();iter++)
		(*iter) = new std::string[x];
	X = x;
	Y= y;
	dataSizeChanged(x, y);
}

void V_GridData::appendRow(){
	data->push_back(new std::string[X]);
	Y++;
	dataSizeChanged(X, Y);
}

void V_GridData::destroyTable(){
	if (data != NULL){
		for(V_GridRow iter = data->begin();iter != data->end();iter++){
			delete[] (*iter);
		}
	delete data;
	data = NULL;
	}
}

void V_GridData::setCellValue(int x, int y, const std::string& value){
	std::string* row = data->at(y);
	row[x].assign(value);
}

std::string V_GridData::getCellValue(int x, int y){
	std::string* row = data->at(y);
	return row[x];
}

void V_GridData::dataSizeChanged(int x, int y){
	if(OnDataSizeChanged){
		V_EventOnDataSizeChanged eventOnDataSizeChanged;
		eventOnDataSizeChanged.x = x;
		eventOnDataSizeChanged.y= y;

		OnDataSizeChanged(eventOnDataSizeChanged);
	}
}