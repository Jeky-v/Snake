#pragma once
#include "cell.h"
class CellReverse :public Cell
{
public:
	CellReverse(void);
	bool Interaction(Snake &snake, int x, int y);
};

