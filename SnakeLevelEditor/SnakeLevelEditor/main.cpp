#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "MenuButton.h"

using namespace std;
SDL_Surface* screen;
const int RESX=910,RESY=540;
const short N=65,M=35;
const short numberOfPictures=9;
const short numberOfButtons=3;

int map[N][M];
int currentCellType=4;
//0-Snake1//1-Snake2//2-CellEmpty//3-CellWallDestructable//4-CellWallUnDestructable//5-CellReverse//6-CellTeleport//7-CellEatGenerator//8-CellEat


SDL_Surface* pictures[numberOfPictures];
SDL_Surface* textPictures[numberOfPictures];
SDL_Surface* buttonPictures[numberOfButtons];
SDL_Surface* bottomPicture;
SDL_Surface* menuPicture;
SDL_Surface* framePicture;
TTF_Font* mainFont;

void loadResources();
void freeResources();
void drawMap();
void drawBottom();
void drawCellsMenu(int,int,int,int);
void writeToFile();
void drawText(int x, int y, char* inputText, int R, int G, int B);
void processMenuControls();
void saveLevel();

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	loadResources();

	SDL_Event event;
	
	bool exit=false;
	bool isRightMBPressed=false;
	bool isLeftMBPressed=false;
	bool drawMenu=true;

	MenuButton* prev = new MenuButton(RESX/2 - 200, RESY - 45, buttonPictures[0]);
	MenuButton* next = new MenuButton(RESX/2 + 120, RESY - 45, buttonPictures[1]);
	MenuButton* save = new MenuButton(RESX - 100, RESY - 45, buttonPictures[2]);

	for (int i=0;i<N;i++)
		for (int j=0;j<M;j++)
			map[i][j]=2;

	while(!exit)
	{
		if (SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					exit = true;
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					int motionX=event.motion.x;
					int motionY=event.motion.y;
					int middleX=RESX / 2;
					int leftEdge=middleX-(pictures[currentCellType]->w+textPictures[currentCellType]->w)/2-8;
					int rightEdge=middleX+(pictures[currentCellType]->w+textPictures[currentCellType]->w)/2-8;
					if (motionY>(RESY-50) && motionY<RESY && motionX>leftEdge && motionX<rightEdge)  processMenuControls();
					int i=motionX/pictures[0]->w;
					int j=motionY/pictures[0]->h;
					if(prev->isCursorHere(motionX, motionY))
					{
						currentCellType--;
						if(currentCellType<0)
						{
							currentCellType=0;
						}
					}
					if(next->isCursorHere(motionX, motionY))
					{
						currentCellType++;
						if(currentCellType>numberOfPictures-1)
						{
							currentCellType=numberOfPictures-1;
						}
					}
					if(save->isCursorHere(motionX, motionY))
					{
						saveLevel();
					}
					if (j>=M) break;				
					if (event.button.button==SDL_BUTTON_LEFT)  
					{
						isLeftMBPressed=true;
						map[i][j]=currentCellType;
					}
					if (event.button.button==SDL_BUTTON_RIGHT) 
					{
						isRightMBPressed=true;
						map[i][j]=2;//cell empty
					}
					break;
				}
				case SDL_MOUSEMOTION:
				{
					prev->isCursorHere(event.motion.x,event.motion.y);
					next->isCursorHere(event.motion.x,event.motion.y);
					save->isCursorHere(event.motion.x,event.motion.y);
					if (isRightMBPressed||isLeftMBPressed)
					{
						int i=event.motion.x/pictures[0]->w;
						int j=event.motion.y/pictures[0]->h;
						if (j>=M) break;
						if (isLeftMBPressed) 
						{
							map[i][j]=currentCellType;
						}
						if (isRightMBPressed)  
						{
							map[i][j]=2;
						}
					}
					break;
				}	
				case SDL_MOUSEBUTTONUP:
				{
					if(event.button.button==SDL_BUTTON_LEFT)
					{
						isLeftMBPressed=false;
					}
					if(event.button.button==SDL_BUTTON_RIGHT)
					{
						isRightMBPressed=false;
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						{
							exit = true;
							break;
						}
					case SDLK_1:
						{
							currentCellType=0;
							break;
						}
					case SDLK_2:
						{
							currentCellType=1;
							break;
						}
					case SDLK_3:
						{
							currentCellType=2;
							break;
						}
					case SDLK_4:
						{
							currentCellType=3;
							break;
						}
					case SDLK_5:
						{
							currentCellType=4;
							break;
						}
					case SDLK_6:
						{
							currentCellType=5;
							break;
						}
					case SDLK_7:
						{
							currentCellType=6;
							break;
						}
					case SDLK_8:
						{
							currentCellType=7;
							break;
						}
					case SDLK_9:
						{
							currentCellType=8;
							break;
						}
					case SDLK_RIGHT:
						{
							currentCellType++;
							if(currentCellType>numberOfPictures-1)
							{
								currentCellType=numberOfPictures-1;
							}
							break;
						}

					case SDLK_LEFT:
						{
							currentCellType--;
							if(currentCellType<0)
							{
								currentCellType=0;
							}
							break;
						}
					}
				}
			}
			drawMap();
			drawBottom();
			prev->drawButton(screen);
			next->drawButton(screen);
			save->drawButton(screen);
			SDL_Flip(screen);
		}
	}
	freeResources();
	writeToFile();
	TTF_Quit();
	SDL_Quit();
	return 0;
}
void loadResources()
{	
	pictures[0]=IMG_Load("Pictures/CellPic/cellsnake.1.14.png");
	pictures[1]=IMG_Load("Pictures/CellPic/cellsnake.2.14.png");
	pictures[2]=IMG_Load("Pictures/CellPic/cellempty.14.png");
	pictures[3]=IMG_Load("Pictures/CellPic/celleat.14.png");
	pictures[4]=IMG_Load("Pictures/CellPic/cellwalldestructable.14.png");
	pictures[5]=IMG_Load("Pictures/CellPic/cellwallundestructable.14.png");	
	pictures[6]=IMG_Load("Pictures/CellPic/cellreverse.14.png");
	pictures[7]=IMG_Load("Pictures/CellPic/cellteleport.14.png");
	pictures[8]=IMG_Load("Pictures/CellPic/celleatgenerator.14.png");

	bottomPicture=IMG_Load("Pictures/Interface/bottompicture.png");
	menuPicture=IMG_Load("Pictures/Interface/menuPicture.png");
	framePicture=IMG_Load("Pictures/Interface/framePicture.png");

	mainFont=TTF_OpenFont("Fonts/arial.ttf",20);
	SDL_Color textColor={255,255,255};
	textPictures[0]=TTF_RenderUTF8_Blended(mainFont,"Snake1",textColor);
	textPictures[1]=TTF_RenderUTF8_Blended(mainFont,"Snake2",textColor);
	textPictures[2]=TTF_RenderUTF8_Blended(mainFont,"Empty Cell",textColor);
	textPictures[3]=TTF_RenderUTF8_Blended(mainFont,"Eat",textColor);
	textPictures[4]=TTF_RenderUTF8_Blended(mainFont,"Destructable Wall",textColor);
	textPictures[5]=TTF_RenderUTF8_Blended(mainFont,"Undestructable Wall",textColor);
	textPictures[6]=TTF_RenderUTF8_Blended(mainFont,"Reverse Cell",textColor);
	textPictures[7]=TTF_RenderUTF8_Blended(mainFont,"Teleport",textColor);
	textPictures[8]=TTF_RenderUTF8_Blended(mainFont,"Eat Generator",textColor);

	buttonPictures[0]=IMG_Load("Pictures/Interface/prev.png");
	buttonPictures[1]=IMG_Load("Pictures/Interface/next.png");
	buttonPictures[2]=IMG_Load("Pictures/Interface/save.png");
}
void freeResources()
{
	for(int i=0;i<9;i++)
	{
		SDL_FreeSurface(pictures[i]);
		SDL_FreeSurface(textPictures[i]);
	}
	SDL_FreeSurface(bottomPicture);
	SDL_FreeSurface(menuPicture);
	SDL_FreeSurface(framePicture);
	for(int i=0;i<numberOfButtons;i++)
	{
		SDL_FreeSurface(buttonPictures[i]);
	}
	TTF_CloseFont(mainFont);
}
void drawMap()
{
	for (int i=0;i<N;i++)
		for (int j=0;j<M;j++)
		{
			SDL_Rect source,destination;
			source.x=0;
			source.y=0;
			source.h=pictures[map[i][j]]->h;
			source.w=pictures[map[i][j]]->w;

			destination.h=pictures[map[i][j]]->h;
			destination.w=pictures[map[i][j]]->w;
			
			destination.x=i*pictures[map[i][j]]->w;
			destination.y=j*pictures[map[i][j]]->h;
			SDL_BlitSurface(pictures[map[i][j]],&source,screen,&destination);
		}
}
void drawBottom()
{
	SDL_Rect source,destination;
	source.x=0;
	source.y=0;
	source.h=bottomPicture->h;
	source.w=bottomPicture->w;
	destination.x=0;
	destination.y=RESY-50;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(bottomPicture,&source,screen,&destination);

	int bottomTab=20;
	int middleX=RESX/2;

	source.h=pictures[currentCellType]->h;
	source.w=pictures[currentCellType]->w;
	destination.x=middleX-(pictures[currentCellType]->w+textPictures[currentCellType]->w)/2-8;
	destination.y=RESY-bottomTab-pictures[currentCellType]->h;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(pictures[currentCellType],&source,screen,&destination);

	source.h=textPictures[currentCellType]->h;
	source.w=textPictures[currentCellType]->w;
	destination.x=middleX-(textPictures[currentCellType]->w)/2+8;
	destination.y=RESY-bottomTab-textPictures[currentCellType]->h+5;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(textPictures[currentCellType],&source,screen,&destination);
}
void drawCellsMenu(int menuX, int menuY,int leftTab,int topTab,int betweenTab, int betweenPicTextTab)
{
	SDL_Rect source, destination;
	source.x=0;
	source.y=0;
	source.h=menuPicture->h;
	source.w=menuPicture->w;
	destination.x=menuX;
	destination.y=menuY;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(menuPicture,&source,screen,&destination);
	
	source.h=pictures[0]->h;
	source.w=pictures[0]->w;
	destination.h=source.h;
	destination.w=source.w;
	destination.x=menuX+leftTab;
	for(int i=0;i<numberOfPictures;i++)
	{
		destination.y=menuY+topTab+i*(pictures[0]->h+betweenTab);
		SDL_BlitSurface(pictures[i],&source,screen,&destination);
	}

	source.h=textPictures[0]->h;
	destination.h=source.h;
	destination.x=menuX+leftTab+pictures[0]->w+betweenPicTextTab;
	for (int i=0;i<numberOfPictures;i++)
	{
		source.w=textPictures[i]->w;
		destination.w=source.w;
		destination.y=menuY+topTab+i*(pictures[0]->h+betweenTab)+pictures[0]->h-textPictures[0]->h+5;
		SDL_BlitSurface(textPictures[i],&source,screen,&destination);
	}
	
	source.h=framePicture->h;
	source.w=framePicture->w;
	destination.h=source.h;
	destination.w=source.w;
	destination.x=menuX+20;
	destination.y=menuY+topTab+currentCellType*(pictures[0]->h+betweenTab)-10;
	SDL_BlitSurface(framePicture,&source,screen,&destination);
}
void drawText(int x, int y, char* inputText, int R, int G, int B)
{
	SDL_Color textColor = {R,G,B};
	if(mainFont==NULL)
	{
		printf("%s \n",TTF_GetError());
	}
    SDL_Surface* blended_m = TTF_RenderUTF8_Blended(mainFont, inputText, textColor);
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
	SDL_FreeSurface(blended_m);
}
void writeToFile()
{
	ofstream out("1.txt",ios::binary|ios::out);

	int snakeDirection=2;
	out.write((char*)&snakeDirection,sizeof(snakeDirection));
	int snakeCellX=45, snakeCellY=15;
	//=============================================
	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));
	snakeCellX=46;
	snakeCellY=15;
	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));
	snakeCellX=47;
	snakeCellY=15;
	out.write((char*)&snakeCellX,sizeof(snakeCellX));
	out.write((char*)&snakeCellY,sizeof(snakeCellY));
	//===========================temprorary========

	for (int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			 int cell=map[i][j];
			 out.write((char*)&cell,sizeof(cell));
			 cout << cell;
		}
	}
	int zero=0;
	out.write((char*)&zero,sizeof(zero));
	//cin >> zero;
	out.close(); 
}	
void processMenuControls()
{
	MenuButton* logicButtons[numberOfPictures];
	int leftTab, topTab, betweenTab;
	leftTab=50; //Length between left edge menu picture and picture of cells
	topTab=40; //Length between top edge menu picture and picture of first cell
	betweenTab=20; //Length between lines
	int betweenPicTextTab=10;
	int menuX=RESX/2-menuPicture->w/2;
	int menuY=80;
	
	SDL_Surface* underMenuBackground=SDL_CreateRGBSurface(SDL_SWSURFACE,menuPicture->w,menuPicture->h,32,0,0,0,0);
	
	SDL_Rect src,dst;
	src.x=menuX;
	src.y=menuY;
	src.h=menuPicture->h;
	src.w=menuPicture->w;
	dst.x=0;
	dst.y=0;
	dst.h=src.h;
	dst.w=src.w;
	SDL_BlitSurface(screen,&src,underMenuBackground,&dst);


	for(int i=0;i<numberOfPictures;i++)
	{
		logicButtons[i]=new MenuButton(menuX+leftTab,menuY+topTab+i*(pictures[0]->h+betweenTab)+pictures[0]->h-textPictures[0]->h+5,menuX+leftTab+pictures[i]->w+betweenPicTextTab+textPictures[i]->w,menuY+topTab+i*(pictures[0]->h+betweenTab)+pictures[0]->h-textPictures[0]->h+5+textPictures[i]->h);
	}

	drawCellsMenu(menuX, menuY, leftTab, topTab, betweenTab,betweenPicTextTab);	
	SDL_Flip(screen);

	SDL_Event event;
	bool run = true;
	while(run)
	{
		if (SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
				{
					exit(0);
					break;
				}
				case SDL_KEYDOWN:
				{
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						run = false;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					if ( event.motion.x < (RESX / 2 - menuPicture->w / 2) ||  event.motion.x > (RESX / 2 + menuPicture->w / 2) || 
						event.motion.y < menuY || event.motion.y > (menuY + menuPicture->h))
					{
						run=false;
					}
					else
					{
						for(int i=0;i<numberOfPictures;i++)
						{
							if(logicButtons[i]->isCursorHere(event.motion.x,event.motion.y))
							{
								currentCellType=i;
							}
						}
						SDL_BlitSurface(underMenuBackground,&dst,screen,&src);
						drawCellsMenu(menuX, menuY, leftTab, topTab, betweenTab,betweenPicTextTab);
						SDL_Flip(screen);
					}
					break;
				}				
			}
		}	
	}
	for(int i=0;i<numberOfPictures;i++)
	{
		delete logicButtons[i];
	}
}
void saveLevel()
{
	
}