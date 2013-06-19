#pragma once
#include "GlobalVariables.h"
#include "Snake.h"
class CellConection;
class Snake;
class Cell
{
private:
	SDL_Rect dest;
	SDL_Surface *picture;
	bool activity;
	CellConection* connection;
public:
	void SetDestination(int x,int y,int h, int w);
	void setConnection(CellConection* someConnection);
	int GetX();
	int GetY();
	int GetH();
	int GetW();
	void SetActivity(bool newact);
	bool GetActivity();
	void SetPicture(SDL_Surface *new_pic);
	SDL_Surface *GetPicture();
	void DrawCell();
	virtual bool Interaction(Snake &snake,int x,int y)=0;
};

