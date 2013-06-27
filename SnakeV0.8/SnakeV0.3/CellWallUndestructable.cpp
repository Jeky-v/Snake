#include "CellWallUndestructable.h"


CellWallUndestructable::CellWallUndestructable(void)
{
	SetActivity(true);
	SetPicture(cell_pic[5]);
}


bool CellWallUndestructable::Interaction(Snake &snake, int x, int y)
{
	snake.SetDead(true);
	return false;
}

