#pragma once
#include "cell.h"
class CellEat :public Cell
{
private:
	static int cell_eat_counter;
public:
	CellEat();
	bool Interaction(Snake &snake, int x, int y);
};

