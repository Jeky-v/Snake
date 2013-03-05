
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "ModuleMgr.h"
#include "HelloScreen.h"
#include "ModuleName.h"
#include "StartMenu.h"
#include "Settings.h"
#include "Game.h"

#include <fstream>
#include <iostream>

//GLOBAL VARIABLES
SDL_Surface *screen;
bool full_screen_mode=false;
int RESX=910;
int RESY=516;
SDL_Surface *cell_pic[8];//0-Snake1//1-Snake2//2-CellEmpty//3-CellWall//
//================


void InitSettings()
{
	using namespace std;
	ifstream SettingsFile;
	
	SettingsFile.open("settings.ssf",ios_base::in|ios_base::binary);
	if(!SettingsFile.is_open())
	{
		cout<<"Cannot open file"<<endl;
	}
	SettingsFile.read((char*)&full_screen_mode,sizeof(bool));

	SettingsFile.close();
}
int main(int argc, char *argv[])
{
	InitSettings();

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	if(full_screen_mode)
	{
		RESX=1366;
		RESY=768;
		screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	}
	else
	{
		RESX=910;
		RESY=516;
		screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	}
	ModuleMgr mgr;
	HelloScreen hello;
	StartMenu menu;
	Settings settings;
	Game game;

	mgr.AddModule(HELLOSCREEN, &hello);
	mgr.AddModule(MAINMENU, &menu);
	mgr.AddModule(SETTINGS,&settings);
	mgr.AddModule(GAME,&game);
	mgr.SetActiveModule(HELLOSCREEN);

	while(mgr.Frame());
	
	mgr.Close();

	TTF_Quit();
	SDL_Quit();
	return 0;
}
