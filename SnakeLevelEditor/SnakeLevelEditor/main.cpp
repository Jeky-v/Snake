#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
using namespace std;
SDL_Surface* screen;
const int RESX=910,RESY=540;
const short N=65,M=35;
int map[N][M];
int currentCellType=5;
const short numberOfPictures=9;

SDL_Surface* pictures[numberOfPictures];
SDL_Surface* bottomPicture;
SDL_Surface* menuPicture;

int loadResources();
void freeResources();
int drawMap();
int drawBottom();
int writeToFile();
void drawText(int x, int y, char* inputText, int size, int R, int G, int B);
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen=SDL_SetVideoMode(RESX,RESY,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	loadResources();

	SDL_Event event;
	
	bool exit=false;
	bool isRightMBPressed=false;
	bool isLeftMBPressed=false;

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
			SDL_Flip(screen);
		}
	}
	freeResources();
	writeToFile();
	SDL_Quit();
	return 0;
}
int loadResources()
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
	return 0;
}
void freeResources()
{
	for(int i=0;i<9;i++)
	{
		SDL_FreeSurface(pictures[i]);
	}
	SDL_FreeSurface(bottomPicture);
	SDL_FreeSurface(menuPicture);
}
int drawMap()
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
	return 0;
}
int drawBottom()
{
	int y=M*pictures[0]->h+5;
	const short spaceBetween=80;
	const short leftSpace=RESX / 2 - (numberOfPictures / 2)*(pictures[0]->w+spaceBetween) ;
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
	for (int i=0;i<numberOfPictures;i++)
	{
			source.x=0;
			source.y=0;
			source.h=pictures[i]->h;
			source.w=pictures[i]->w;
			destination.h=pictures[i]->h;
			destination.w=pictures[i]->w;
			destination.x=leftSpace+i*(pictures[i]->w+spaceBetween);
			destination.y=y;
			SDL_BlitSurface(pictures[i],&source,screen,&destination);
	}
	return 0;
}
void drawText(int x, int y, char* inputText, int size, int R, int G, int B)
{
	TTF_Font* font=0;
	font=TTF_OpenFont("SnakeLevelEditor/Fonts/komika.ttf",size);
	if(font==NULL)
	{
		printf("Error: Font not loaded!\n");
	}
	SDL_Color text_color = {R,G,B};
    char* text = inputText; 
    SDL_Surface* blended_m = TTF_RenderUTF8_Blended(font, text, text_color);
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
	TTF_CloseFont(font);
}

int writeToFile()
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
			 cout << map[i][j];
		}
	}
	int zero=0;
	out.write((char*)&zero,sizeof(zero));
	cin >> zero;
	out.close(); 
	return 0;
}	
