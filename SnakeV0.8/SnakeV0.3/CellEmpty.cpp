#include "GlobalVariables.h"

#include "ModuleName.h"

#include "CellEmpty.h"
#include "CellSnake.h"

CellEmpty::CellEmpty()
{
	SetActivity(true);
	SetPicture(cell_pic[2]);
}

bool CellEmpty::Interaction(Snake &snake,int x,int y)
{
	if(mgr.getCurrentModuleName()==THRONEMODE)
	{
		snake.snake_list.push_front(CellStruct(x,y));
		Converter.CreateConvert <CellSnake> (x,y);
		Converter.Convert();
		global_map[x][y]->SetPicture(snake.GetPicture());
		return true;
	}
	if(mgr.getCurrentModuleName()==TWOPLAYERS)
	{
		snake.snake_list.push_front(CellStruct(x,y));
		Converter.CreateConvert <CellSnake> (x,y);
		Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
		snake.snake_list.pop_back();
		Converter.Convert();
		global_map[x][y]->SetPicture(snake.GetPicture());
		return true;
	}
	if(mgr.getCurrentModuleName()==GAMEWITHLEVELS || mgr.getCurrentModuleName()==CLASSIC)
	{
		snake.snake_list.push_front(CellStruct(x,y));
		Converter.CreateConvert <CellSnake> (x,y);
		Converter.CreateConvert <CellEmpty> (snake.snake_list.back().CellX,snake.snake_list.back().CellY);
		snake.snake_list.pop_back();
		Converter.Convert();
		return true;
	}	
}



