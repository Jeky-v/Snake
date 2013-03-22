#include "CellSnake.h"


CellSnake::CellSnake()
{
	SetActivity(true);
	SetPicture(cell_pic[0]);
}

bool CellSnake::Interaction(Snake &snake,int x,int y)
{
	snake.SetDead(true);
	return false;
}