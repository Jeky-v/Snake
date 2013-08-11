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
	bool cursorHere;
	SDL_Surface* buttonPicture;
public:
	MenuButton();
	MenuButton(int tlX, int tlY, int brX, int brY);
	MenuButton(int tlX, int tlY, SDL_Surface* newPicture);
	void setPicture(SDL_Surface* newPicture);
	void drawButton(SDL_Surface* destinationSurface);
	bool isCursorHere(int mouseX, int mouseY);
};
