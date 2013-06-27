#pragma once
#include "Cell.h"


class CellSnake :public Cell
{

public:
	CellSnake();
	bool Interaction(Snake &snake,int x,int y);
};

