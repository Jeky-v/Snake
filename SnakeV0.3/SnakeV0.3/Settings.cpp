#include <fstream>

#include "Settings.h"
#include "ModuleName.h"
#include "ModuleMgr.h"


Settings::Settings():tick(80,80)
{
	
}

void Settings::ChangeScreenMode()
{
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
}

void Settings::SaveSettings()
{
	using namespace std;
	ofstream SettingsFile;
	SettingsFile.open("settings.ssf",ios_base::out|ios_base::binary);
	SettingsFile.write((char*)&full_screen_mode,sizeof(bool));
	SettingsFile.close();

}

void Settings::DrawText(int x,int y,char *inputtext,int size,int R,int G,int B)
{
	TTF_Font* font = 0;
    font = TTF_OpenFont("Fonts/Komika.ttf",size);
	SDL_Color text_color = {R,G,B};
   // SDL_Color bg_color = {0,0,0}; // чёрный цвет фона
    char* text = inputtext; // наше тестовое сообщение

    SDL_Surface* blended_m = TTF_RenderUTF8_Blended(font, text, text_color); // рендерим сглаженное сообщение
    //SDL_Surface* shaded_m = TTF_RenderUTF8_Shaded(font, text, text_color, bg_color);
	SDL_Rect dst;
    dst.x = x;
	dst.y = y;
	dst.w = blended_m->w;
	dst.h = blended_m->h;
    SDL_Rect src;
    src.x = 0;       
	src.y = 0;
	src.w=dst.w;
	src.h=dst.h;
	SDL_BlitSurface(blended_m,&src,screen,&dst);
	SDL_Flip(screen);
}

void Settings::doInit()
{
	
	if(full_screen_mode)
	{background=IMG_Load("Pictures/Menu/Backgrounds/background0.1366.png");}
	else
	{background=IMG_Load("Pictures/Menu/Backgrounds/background0.900.png");}
	
	tickbox=IMG_Load("Pictures/Menu/Buttons/tickbox1.png");
	box=IMG_Load("Pictures/Menu/Buttons/box.png");
	backpic=IMG_Load("Pictures/Menu/Buttons/back.png");

	back.SetButtonPic(backpic);

	
	SDL_Rect src,des;
	src.x=0;
	src.y=0;
	src.w=background->w;
	src.h=background->h;
	des.x=0;
	des.y=0;
	des.w=src.w;
	des.h=src.h;
	SDL_BlitSurface(background,&src,screen,&des);

	if(full_screen_mode)
	{
		back.SetDestination(483,618,80,400);
		tick.SetDestination(RESX-400,25,115,115);
		tick.SetButtonPic(tickbox);
		
		DrawText(297,13,"Fullscreen Mode",80,166,132,201);
		DrawText(300,15,"Fullscreen Mode",80,250,152,5);
	}
	else
	{
		back.SetDestination(250,416,100,400);
		tick.SetDestination(RESX-250,20,115,115);
		tick.SetButtonPic(box);
		
		DrawText(147,17,"Fullscreen Mode",60,166,132,201);
		DrawText(150,20,"Fullscreen Mode",60,250,152,5);
	}
	
	SDL_Flip(screen);
}

bool Settings::doRun()
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
		{
			return false;
			break;
		}	
		case SDL_KEYDOWN:
		{
			if ( event.key.keysym.sym == SDLK_ESCAPE ) 
			{return false;} 
			break;
		}
		case SDL_MOUSEMOTION:
		{
			back.CheckActivity(event.motion.x,event.motion.y);
			tick.CheckActivity(event.motion.x,event.motion.y);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				if(back.GetState())
				{
					SaveSettings();
					ChangeScreenMode();
					m_mgr->SetActiveModule(MAINMENU);
					return true;
				}
				if(tick.GetState())
				{
					if(full_screen_mode)
					{
						full_screen_mode=false;
						tick.SetButtonPic(box);
					}
					else
					{
						full_screen_mode=true;
						tick.SetButtonPic(tickbox);
					}
				}
			}
			break;
		}
	}
	for(int i=0;i<5;i++)
	{
		back.DrawButton();
		tick.DrawButton();
	}
	SDL_Delay(10);
	return true;
}

void Settings::doClose()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(tickbox);
	SDL_FreeSurface(box);
	SDL_FreeSurface(backpic);
}

