#pragma once
#include <SDL.h>

struct Point
{
	int x;
	int y;
	void setPoint(int newX,int newY)
	{
		x=newX;
		y=newY;
	}
};
class MenuButton
{
private:
	Point topLeft;
	Point bottomRight;
	SDL_Surface* buttonPicture;
public:
	MenuButton();
	MenuButton(int tlX, int tlY, int brX, int brY);
	void setPicture(SDL_Surface* newPicture);
	void drawButton();
	bool isCursorHere(int mouseX, int mouseY);
};
