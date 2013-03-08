#pragma once
#include "cell.h"
class CellEat :public Cell
{
public:
	CellEat(void);
	void Interaction(Snake &snake, int x, int y);
};

