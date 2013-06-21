#pragma once
#include <list>
#include "CellStruct.h"
#include "GameWithLevels.h"

#include "GlobalVariables.h"

class GameWithLevels;
enum dir_type {Up,Down,Left,Right};

class Snake
{
private:
	dir_type direction;
	SDL_Surface *picture;
	char name[20];
	int score;
	bool dead;
public:
		
	std::list <CellStruct> snake_list; 
	Snake();
	Snake(dir_type start_direction,char *text,CellStruct cell1,CellStruct cell2,CellStruct cell3);
	~Snake(void);

	void SetScore(int new_score);
	int GetScore();
	void SetDead(bool new_dead);
	bool GetDead();
	bool Move();
	void SetPicture(SDL_Surface* new_picture);
	SDL_Surface* GetPicture();
	void SetDirection(dir_type new_direction);
	dir_type GetDirection();
};

