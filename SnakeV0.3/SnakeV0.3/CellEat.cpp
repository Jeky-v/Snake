#include "CellEat.h"
#include "CellSnake.h"

class CellSnake;
CellEat::CellEat(void)
{
	SetActivity(true);
	SetPicture(cell_pic[3]);
}
void CellEat::Interaction(Snake &snake, int x, int y)
{
	snake.snake_list.push_front(CellStruct(x,y));
	snake.SetScore(snake.GetScore()+10);
	Converter.CreateConvert <CellSnake> (x,y);
}