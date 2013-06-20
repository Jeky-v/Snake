#include "CellConnection.h"


CellConnection::CellConnection(void)
{
}


CellConnection::~CellConnection(void)
{
	cells.clear();
}
void CellConnection::addCell(Cell* cell,int x, int y)
{
	auto _cell=std::pair<Cell*,std::pair<int,int> >(cell,std::pair<int,int>(x,y));
	cells.push_back(_cell);
	int k=4;
}
