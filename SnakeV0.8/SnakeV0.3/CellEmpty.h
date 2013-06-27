#pragma once
#include "Cell.h"

class CellEmpty :public Cell
{

public:
	CellEmpty();
	bool Interaction(Snake &snake,int x,int y);
};

