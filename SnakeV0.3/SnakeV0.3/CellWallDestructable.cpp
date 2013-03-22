#include "CellWallDestructable.h"
#include "CellSnake.h"
#include "CellEmpty.h"

CellWallDestructable::CellWallDestructable(void)
{
	SetActivity(true);
	SetPicture(cell_pic[4]);
}

bool CellWallDestructable::Interaction(Snake &snake, int x, int y)
{
	if(snake.snake_list.size()<4)
	{
		return false;
	}
	else
	{
		snake.snake_list.push_front(CellStruct(x,y));
		Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
		Converter.Convert();
		snake.snake_list.pop_back();
		Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
		Converter.Convert();
		snake.snake_list.pop_back();
		Converter.CreateConvert <CellSnake> (x,y);
		return true;
	}
}

