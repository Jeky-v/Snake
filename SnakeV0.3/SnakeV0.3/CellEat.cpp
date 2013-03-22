#include "CellEat.h"
#include "CellSnake.h"

class CellSnake;
int CellEat::cell_eat_counter=0;
CellEat::CellEat()
{
	SetActivity(true);
	SetPicture(cell_pic[3]);
	cell_eat_counter++;
}
bool CellEat::Interaction(Snake &snake, int x, int y)
{
	snake.snake_list.push_front(CellStruct(x,y));
	snake.SetScore(snake.GetScore()+10);
	Converter.CreateConvert <CellSnake> (x,y);
	cell_eat_counter--;
	if(cell_eat_counter==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}