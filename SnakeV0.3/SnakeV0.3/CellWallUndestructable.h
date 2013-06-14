#pragma once
#include "cell.h"
class CellWallUndestructable :public Cell
{
public:
	CellWallUndestructable(void);
	bool Interaction(Snake &snake, int x, int y);
};

