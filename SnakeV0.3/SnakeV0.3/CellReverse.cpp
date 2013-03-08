#include "CellStruct.h"
#include "CellReverse.h"
#include "CellEmpty.h"

CellReverse::CellReverse(void)
{
	SetActivity(true);
	SetPicture(cell_pic[6]);
}

void CellReverse::Interaction(Snake &snake, int x, int y)
{
	snake.snake_list.reverse();

	CellStruct last;
	CellStruct beforelast;
	last=snake.snake_list.front();

	list<CellStruct>::iterator iter=snake.snake_list.begin();
	iter++;
	beforelast=*iter;

	if(beforelast.CellX-last.CellX==1)
	{
		snake.SetDirection(Left);
	}
	if(beforelast.CellX-last.CellX==-1)
	{
		snake.SetDirection(Right);
	}
	if(beforelast.CellY-last.CellY==1)
	{
		snake.SetDirection(Up);
	}
	if(beforelast.CellY-last.CellY==-1)
	{
		snake.SetDirection(Down);
	}

	Converter.CreateConvert <CellEmpty> (x,y);
}