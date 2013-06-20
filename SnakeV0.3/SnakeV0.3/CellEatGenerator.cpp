#include "CellEatGenerator.h"
#include "CellConnectionEatGenerator.h"
#include "CellSnake.h"
#include "CellEmpty.h"
CellEatGenerator::CellEatGenerator(void)
{
	SetPicture(cell_pic[8]);
}


CellEatGenerator::~CellEatGenerator(void)
{
}
bool CellEatGenerator::Interaction(Snake &snake, int x, int y)
{
	if (connection) static_cast<CellConnectionEatGenerator*>(connection)->generate(this);

	snake.snake_list.push_front(CellStruct(x,y));
	Converter.CreateConvert <CellSnake> (x,y);

	Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
	snake.snake_list.pop_back();
	return true;
}