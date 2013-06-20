#pragma once
#include "cellconnection.h"
#include <list>
class Cell;
class CellConnectionEatGenerator :
	public CellConnection
{
public:
	CellConnectionEatGenerator(void);
	~CellConnectionEatGenerator(void);
	void generate(Cell* currentCell);
};

