#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
using namespace std;
SDL_Surface* screen;
const int RESX=910,RESY=540;
const short N=65,M=35;
int map[N][M];
int currentCellType=4;
//0-Snake1//1-Snake2//2-CellEmpty//3-CellWallDestructable//4-CellWallUnDestructable//5-CellReverse//6-CellTeleport//7-CellEatGenerator//8-CellEat
const short numberOfPictures=9;

SDL_Surface* pictures[numberOfPictures];
SDL_Surface* textPictures[numberOfPictures];
SDL_Surface* bottomPicture;
SDL_Surface* menuPicture;
SDL_Surface* framePicture;
TTF_Font* mainFont;

void loadResources();
void freeResources();
void drawMap();
void drawBottom();
void drawCellsMenu();
void writeToFile();
void drawText(int x, int y, char* inputText, int R, int G, int B);

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
					int i=event.motion.x/pictures[0]->w;
					int j=event.motion.y/pictures[0]->h;
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
					if ( event.key.keysym.sym == SDLK_ESCAPE ) 
					{
						exit=true;
						break;
					}
				}
			}
			drawMap();
			drawBottom();
			if(drawMenu)
			{
				drawCellsMenu();
			}
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
	pictures[3]=IMG_Load("Pictures/CellPic/cellwalldestructable.14.png");
	pictures[4]=IMG_Load("Pictures/CellPic/cellwallundestructable.14.png");
	pictures[5]=IMG_Load("Pictures/CellPic/cellreverse.14.png");	
	pictures[6]=IMG_Load("Pictures/CellPic/cellteleport.14.png");
	pictures[7]=IMG_Load("Pictures/CellPic/celleatgenerator.14.png");
	pictures[8]=IMG_Load("Pictures/CellPic/celleat.14.png");

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
void drawCellsMenu()
{
	int middleX=RESX/2;
	int menuY=80;

	SDL_Rect source, destination;
	source.x=0;
	source.y=0;
	source.h=menuPicture->h;
	source.w=menuPicture->w;
	destination.x=middleX-menuPicture->w/2;
	destination.y=menuY;
	destination.h=source.h;
	destination.w=source.w;
	SDL_BlitSurface(menuPicture,&source,screen,&destination);
	
	int leftTab=50; //Length between left edge menu picture and picture of cells
	int topTab=40; //Length between top edge menu picture and picture of first cell
	int betweenTab=20;
	source.h=pictures[0]->h;
	source.w=pictures[0]->w;
	destination.h=source.h;
	destination.w=source.w;
	destination.x=middleX-menuPicture->w/2+leftTab;
	for(int i=0;i<numberOfPictures;i++)
	{
		destination.y=menuY+topTab+i*(pictures[0]->h+betweenTab);
		SDL_BlitSurface(pictures[i],&source,screen,&destination);
	}

	source.h=textPictures[0]->h;
	destination.h=source.h;
	destination.x=middleX-menuPicture->w/2+leftTab+20;
	for(int i=0;i<numberOfPictures;i++)
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
	destination.x=middleX-menuPicture->w/2+20;
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
	ofstream out("level.txt",ios::binary|ios::out);

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
			 out.write((char*)&map[i][j],sizeof(map[i][j]));
			 //cout << map[i][j];
		}
	}
	int zero=0;
	out.write((char*)&zero,sizeof(zero));
	//cin >> zero;
	out.close(); 
}	
