#pragma once
#include "Cell.h"


class CellSnake :public Cell
{

public:
	CellSnake();
	void Interaction(Snake &snake,int x,int y);
};

