#pragma once
#include "Cell.h"
#include <map>
class Cell;
class CellConnection
{
public:
	CellConnection(void);
	~CellConnection(void);
	void addCell(Cell* cell,int x, int y);
protected:
	std::list <std::pair<Cell*,std::pair<int,int> > > cells;
};

