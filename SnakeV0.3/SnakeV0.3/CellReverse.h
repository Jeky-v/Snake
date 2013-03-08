#pragma once
#include "cell.h"
class CellReverse :public Cell
{
public:
	CellReverse(void);
	void Interaction(Snake &snake, int x, int y);
};

