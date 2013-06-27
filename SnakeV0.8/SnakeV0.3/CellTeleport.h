#pragma once
#include "cell.h"
class CellTeleport :
	public Cell
{
public:
	CellTeleport(void);
	bool Interaction(Snake &snake, int x, int y);
};

