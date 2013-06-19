#pragma once
#include "GlobalVariables.h"
#include "Snake.h"
class CellConnection;
class Snake;
class Cell
{
private:
	SDL_Rect dest;
	SDL_Surface *picture;
	bool activity;
protected:
	CellConnection* connection;
public:
	void SetDestination(int x,int y,int h, int w);
	void setConnection(CellConnection* someConnection,int x, int y);
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

