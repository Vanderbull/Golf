#include "playerinput.h"
//#include <string>
//#include <iostream>
//using namespace std;


//extern SDL_Surface* screen;
//extern float bredd1,hojd1;


#define PITCH (surf.screen->pitch/4)

void drawcharacter(int x, int y, int character)
{	
  if (character == 32)
    return;
  
  character -= 33; // our font does not have the first 33 characters.

  // Lock surface if needed
  if (SDL_MUSTLOCK(surf.gFont))
    if (SDL_LockSurface(surf.gFont) < 0) 
      return;

  int i, j;
  for (i = 0; i < surf.gFont->w; i++)
  {
    int screenofs = x + (y + i) * PITCH;
    int charofs = (i + character * surf.gFont->w) * (surf.gFont->pitch / 4);
    for (j = 0; j < surf.gFont->w; j++)
    {
      ((unsigned int*)surf.screen->pixels)[screenofs] = 
        ((unsigned int*)surf.gFont->pixels)[charofs];
      screenofs++;
      charofs++;
    }
  }

  // Unlock if needed
   /* if (SDL_MUSTLOCK(gFont)) 
        SDL_UnlockSurface(gFont);*/
}


void drawstring(int x, int y, char *s)
{		
	
  while (*s != 0)
  {
    drawcharacter(x, y, *s);
    s++;
    x += surf.gFont->w;
  }
}

bool Events(SDL_Surface *img,Players &pl)
{
	int x,y;

	SDL_GetMouseState(&x,&y);
	//static bool tournament=false;
	bool start=false;
	//static int players=1,playeractivated=0;

	int tx=419,ty=448,plus=37;
	//static char names[4][30]={{'\0'},{'\0'},{'\0'},{'\0'}};
	//static int nameplace[4]={0,0,0,0};
	//static int selectMap=1;
	SDL_Event event;
	while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				

			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT)
				{					
					if(x>102 && x< 328 && y>25 && y<241)
						pl.tournament=false;
					else if(x>398 && x< 626 && y>25 && y<241)
						pl.tournament=true;

					else if(x>438 && y>492 && x<568 && y< 552)
					{
						for(int i=0; i< pl.players ; i++)
						{
							if(pl.names[i][0]=='\0')
							{
								start=false;
								break;
							}
							else
							{
								start=true;
							}
						}

						
					}

					else if(x>2 && x<68 && y>49 && y<115)
					{
						int temp=(68-2)/3;						
						pl.selectMap=(x-2)/temp+1+3*((y-49)/temp);
					}

					else if(x>54 && x<87)
					{	
						if(y>tx && y<ty)
							pl.players=1;
						else if(y>tx+plus && y<ty+plus)
							pl.players=2;
						else if(y>tx+plus*2 && y<ty+plus*2)
							pl.players=3;
						else if(y>tx+plus*3 && y<ty+plus*3)
							pl.players=4;

						pl.playeractivated=0;
					}
					else if(x>101 && x<435)
					{
						pl.playeractivated=0;

						if(y>tx && y<ty)
							pl.playeractivated=1;
						else if(y>tx+plus && y<ty+plus && pl.players>1)
							pl.playeractivated=2;
						else if(y>tx+plus*2 && y<ty+plus*2 && pl.players>2)
							pl.playeractivated=3;
						else if(y>tx+plus*3 && y<ty+plus*3 && pl.players>3)
							pl.playeractivated=4;
					}					
					else
						pl.playeractivated=0;					
				}
				break;

			case SDL_KEYUP:				
				if(pl.playeractivated>0)
				{
					int key=event.key.keysym.sym;
					if(key >= SDLK_a && key<=SDLK_z && pl.nameplace[pl.playeractivated-1]<12)
					{
						pl.names[pl.playeractivated-1][pl.nameplace[pl.playeractivated-1]]=key;
						pl.nameplace[pl.playeractivated-1]++;
						pl.names[pl.playeractivated-1][pl.nameplace[pl.playeractivated-1]]='\0';
					}
					else if(key==SDLK_BACKSPACE && pl.nameplace[pl.playeractivated-1]>0)
					{											
						pl.names[pl.playeractivated-1][pl.nameplace[pl.playeractivated-1]-1]='\0';
						pl.nameplace[pl.playeractivated-1]--;
					}
				}
				break;		
			case SDL_KEYDOWN:	
				switch(event.key.keysym.sym)
				{
				
				case SDLK_ESCAPE:
					extern Bools bo;
					bo.done=true;
					start=true;
					
				}
				break;

			
				

			}
			break;

	}
	drawstring(104,426,pl.names[0]);
	drawstring(104,426+plus,pl.names[1]);
	drawstring(104,426+plus*2,pl.names[2]);
	drawstring(104,426+plus*3,pl.names[3]);

	for(int i=4; i>pl.players; i--)
		DrawIMGAlpha(img,100,419+plus*(i-1),261,29,100,600,150);
	
	if(pl.tournament)
	{		
		for(int i=0; i<7; i++)
			DrawIMGAlpha(img,103,26+31*i,228,31,367,600,60);
	}
	else
	{
		for(int i=0; i<7; i++)
			DrawIMGAlpha(img,398,26+31*i,228,31,367,600,60);
	}
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
		{
			if(j+1+i*3 != pl.selectMap)
				DrawIMGAlpha(img,4+22*j,51+22*i,19,19,367,600,60);
		}
		

	return start;


	
}
	
Players::Players()
{
	selectMap=1;
	players=1;
	playeractivated=0;
	tournament=false;
	antalsomsattden=0;
	picked=false;
	finished=false;

	for(int i=0; i<4; i++)
	{
		names[i][0]='\0';
		nameplace[i]=0;
	}
}




void BreddHojd(Bollpos boll)
{
	bredd1=(float)boll.x-200.0f;
		hojd1=(float)boll.y-300.f;
		if(bredd1<0)
			bredd1=0;
		else if(bredd1>=(bredd-16)*50)
			bredd1=(bredd-16)*50-1;

		if(hojd1<0)
			hojd1=0;
		else if(hojd1>=(hojd-12)*50)
			hojd1=(hojd-12)*50-1;
}

void Highscore(SDL_Surface* start,IsPlaying isp[],Players &play)
{
	ifstream infil("highscore.txt");	
	char namn[11][20];
	int score[11];
	SDL_Surface *hscore = SDL_LoadBMP("highscore.bmp");
	
	for(int i=0; i<10; i++)
	{
		strcpy(namn[i],"unnamed");
		score[i]=999;
	}
	
	if(infil)
	{
		for(int i=0; i<10 && infil.peek() !=EOF; i++)
		{
			infil >> namn[i] >> score[i];
		}
		infil.close();
	}
	if(play.finished)
	{
		for(int i=0; i<play.players; ++i)
		{		
			strcpy(namn[10],play.names[i]);
			score[10]= isp[i].score;
			bool klar=false;

			for(int j=9; j>=0 && !klar ; --j)
			{
				if(score[j] > score[j+1])
				{
					char temp[20];
					strcpy(temp,namn[j]);
					strcpy(namn[j],namn[j+1]);
					strcpy(namn[j+1],temp);

					swap(score[j],score[j+1]);
				}
				else
					klar=true;
			}
		}
	}



	int x,y;
	bool klar=false;

	while(!klar)
	{
		SDL_GetMouseState(&x,&y);
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(x>338 && y>492 && x<468 && y< 552)
					klar=true;
			}
		}

		SDL_FillRect(surf.screen,0,0xFFFFFFFF);
		DrawIMGAlpha(start,337,491,133,64,437,491,255);
		DrawIMG(hscore,200,40,420,41,0,0);
		
		char chScore[20];
		for(int i=0; i < 10; ++i)
		{			
			itoa(score[i],chScore,10);
			drawstring(260,110+30*i,namn[i]);
			drawstring(460,110+30*i,chScore);
		}
		
		
						//start=true;
		SDL_Flip(surf.screen);
	}
	ofstream offil("highscore.txt");
	for(int i=0; i<10; i++)
	{
		offil << namn[i] << " " << score[i] << endl;
	}
	offil.close();
	SDL_FreeSurface(hscore);
}

void EscMeny(SDL_Surface *init, Bools &bo, Players &players, IsPlaying isplaying[])
{
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Surface *img = SDL_LoadBMP("escmeny.bmp");

	bool done=false;
	SDL_Event event;
	int y1=50;
	int x,y;
	while(!done)
	{
		DrawIMG(img,269,175,262,251,0,0);		
			SDL_GetMouseState(&x,&y);
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_MOUSEBUTTONUP)
			{
				if(x>331 && y>208 && x<457 && y< 243) // Continue
					done=true;
				
				else if(x>331 && y>208+y1 && x<457 && y< 243+y1) //New Game
				{
					done=true;
					for(int i=0; i<4; i++)
					{
						//players= Players();
						isplaying[i].sattbollen=false;
						
					}
					players= Players();
					
				}

				else if(x>331 && y>208+y1*2 && x<457 && y< 243+y1*2) //HighScore
				{
					done=true;
					Highscore(init,isplaying,players);
					
				}

				else if(x>331 && y+y1*3 >208 && x<457 && y< 243+y1*3) //Exit
				{
					done=true;
					bo.done=true;
					
				}
			}
			
		}
	
		SDL_Flip(surf.screen);		
	}
	SDL_FreeSurface(img);
	SDL_ShowCursor(SDL_DISABLE);
	
}
