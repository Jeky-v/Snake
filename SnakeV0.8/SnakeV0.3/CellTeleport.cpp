#include "CellTeleport.h"
#include "CellConnectionTeleport.h"
#include "GlobalVariables.h"
#include "CellSnake.h"
#include "CellEmpty.h"
CellTeleport::CellTeleport(void)
{
	SetActivity(true);
	SetPicture(cell_pic[7]);
}



bool CellTeleport::Interaction(Snake &snake, int x, int y)
{
	std::pair<int,int> nextCell=static_cast<CellConnectionTeleport*>(connection)->returnCellToTeleport(this);
	
	Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
	snake.snake_list.pop_back();
	
	Converter.CreateConvert <CellSnake> (x,y);
	snake.snake_list.push_front(CellStruct(x,y));
	
	snake.snake_list.push_front(CellStruct(nextCell.first,nextCell.second));
	Converter.CreateConvert <CellSnake> (nextCell.first,nextCell.second);

	return true;
}
