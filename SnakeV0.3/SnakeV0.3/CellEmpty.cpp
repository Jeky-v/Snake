#include "CellEmpty.h"
#include "CellSnake.h"

CellEmpty::CellEmpty()
{
	SetActivity(true);
	SetPicture(cell_pic[2]);
}


bool CellEmpty::Interaction(Snake &snake,int x,int y)
{
	snake.snake_list.push_front(CellStruct(x,y));
	Converter.CreateConvert <CellSnake> (x,y);

	Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
	snake.snake_list.pop_back();
	Converter.Convert();
	return true;
}



