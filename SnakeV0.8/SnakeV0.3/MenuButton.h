#pragma once
class MenuButton
{
private:
	SDL_Surface *button_pic;
	SDL_Rect source;
	SDL_Rect destination;
	bool state;
public:
	MenuButton();
	MenuButton(int h,int w);

	void SetButtonPic(SDL_Surface* new_surface);
	void SetDestination(int x,int y, int h, int w);
	void setState(bool _state){state=_state;}
	bool GetState();
	
	bool CheckCollision(int x,int y);
	void DrawButton();
	bool operator!=(MenuButton object);
};

