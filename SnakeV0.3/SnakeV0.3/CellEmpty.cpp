#include "CellEmpty.h"
#include "CellSnake.h"
class CellSnake;
CellEmpty::CellEmpty()
{
	SetActivity(true);
	SetPicture(cell_pic[2]);
}


void CellEmpty::Interaction(Snake &snake,int x,int y)
{
	snake.snake_list.push_front(CellStruct(x,y));
	Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
	Converter.Convert();
	Converter.CreateConvert <CellSnake> (x,y);
	snake.snake_list.pop_back();
}



