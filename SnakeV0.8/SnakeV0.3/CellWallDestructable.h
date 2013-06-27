#pragma once
#include "cell.h"
class CellWallDestructable :public Cell
{
public:
	CellWallDestructable(void);
	bool Interaction(Snake &snake, int x, int y);
};

