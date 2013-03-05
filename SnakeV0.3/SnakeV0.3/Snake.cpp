#include "GlobalVariables.h"
#include "Snake.h"

Snake::Snake()
{

}

Snake::Snake(Game *new_game_pointer,dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3)
{
	game_pointer=new_game_pointer;
	direction=start_direction;
	score=0;
	strncpy(name,text,19);
	snake_list.push_front(cell3);
	snake_list.push_front(cell2);
	snake_list.push_front(cell1);
}

Snake::~Snake(void)
{
	snake_list.clear();
}

void Snake::Move()
{
	CellStruct temp;
	switch(direction)
	{
	case Up:
		{
			temp.CellX=snake_list.front().CellX;
			if(snake_list.front().CellY==0)
			{
				temp.CellY=35;//это нужно чтобы змейка выезжала с противоположной стороны
			}
			else
			{
				temp.CellY=snake_list.front().CellY+1;
			}
			break;
		}
	case Down:
		{
			temp.CellX=snake_list.front().CellX;
			if(snake_list.front().CellY==35)
			{
				temp.CellY=0;
			}
			else
			{
				temp.CellY=snake_list.front().CellY-1;
			}
			break;
		}
	case Left:
		{
			if(snake_list.front().CellX==0)
			{
				temp.CellX=65;
			}
			else
			{
				temp.CellX=snake_list.front().CellX-1;
			}
			temp.CellY=snake_list.front().CellY;
			break;
		}
	case Right:
		{
			if(snake_list.front().CellX==65)
			{
				temp.CellX=0;
			}
			else
			{
				temp.CellX=snake_list.front().CellX+1;
			}
			temp.CellY=snake_list.front().CellY;
			break;
		}

	}
	game_pointer->map[temp.CellX][temp.CellY]->Interaction(*this,temp.CellX,temp.CellY);
}
void Snake::SetDirection(dir_type new_direction)
{
	direction=new_direction;
}

dir_type Snake::GetDirection()
{
	return direction;
}
