#include "GlobalVariables.h"
#include "Snake.h"

Snake::Snake()
{

}

Snake::Snake(dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3)
{
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
	
	game_module_p->map[10][10]=NULL;

	switch(direction)
	{
	case Up:
		{
			temp=snake_list.front();
			break;
		}
	case Down:
		{

			break;
		}
	case Left:
		{

			break;
		}
	case Right:
		{

			break;
		}

	}
}

void Snake::SetDirection(dir_type new_direction)
{
	direction=new_direction;
}

dir_type Snake::GetDirection()
{
	return direction;
}
