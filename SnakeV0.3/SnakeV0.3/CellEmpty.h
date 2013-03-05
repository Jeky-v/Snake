#pragma once
#include "Cell.h"

class CellEmpty :public Cell
{

public:
	CellEmpty();
	void Interaction(Snake &snake,int x,int y);
};

