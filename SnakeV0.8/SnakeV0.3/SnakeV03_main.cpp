
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "ModuleMgr.h"
#include "HelloScreen.h"
#include "ModuleName.h"
#include "StartMenu.h"
#include "Settings.h"
#include "SelectGameMode.h"

#include "GameWithLevels.h"
#include "GameTwoPlayers.h"
#include "GameClassic.h"
#include "GameThroneMode.h"

#include <fstream>
#include <iostream>

//GLOBAL VARIABLES
SDL_Surface *screen;
bool full_screen_mode=false;
int RESX=910;
int RESY=523;
int musicVolume=128;
int soundVolume=128;
SDL_Surface *cell_pic[9];//0-Snake1//1-Snake2//2-CellEmpty//3-CellWall//4-CellWallDestructible//5CellWallUnDestructible//6-CellReverse//7-CellTeleport//8-CellEatGenerator
CellTypeConverter Converter;
Cell *global_map[65][35];
ModuleMgr mgr;
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
	//SettingsFile.read((char*)&musicVolume,sizeof(int));
	//SettingsFile.read((char*)&soundVolume,sizeof(int));
	SettingsFile.close();
}
int main(int argc, char *argv[])
{
	InitSettings();

	SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO);
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
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
		RESY=523;
		screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	}
	
	HelloScreen hello;
	StartMenu menu;
	Settings settings;
	SelectGameMode select_game_mode;
	GameWithLevels game_with_levels;
	GameTwoPlayers game_two_players;
	GameClassic	   game_classic;
	GameThroneMode throne_mode;

	mgr.AddModule(HELLOSCREEN, &hello);
	mgr.AddModule(MAINMENU, &menu);
	mgr.AddModule(SETTINGS,&settings);
	mgr.AddModule(SELECTGAMEMODE,&select_game_mode);
	mgr.AddModule(GAMEWITHLEVELS,&game_with_levels);
	mgr.AddModule(TWOPLAYERS,&game_two_players);
	mgr.AddModule(CLASSIC,&game_classic);
	mgr.AddModule(THRONEMODE,&throne_mode);

	mgr.SetActiveModule(HELLOSCREEN);

	while(mgr.Frame());
	
	mgr.Close();

	TTF_Quit();
	SDL_Quit();
	return 0;
}
