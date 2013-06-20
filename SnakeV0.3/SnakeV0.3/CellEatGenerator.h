#pragma once
#include "cell.h"
class CellEatGenerator :
	public Cell
{
public:
	CellEatGenerator(void);
	~CellEatGenerator(void);
	bool Interaction(Snake &snake, int x, int y);
};

