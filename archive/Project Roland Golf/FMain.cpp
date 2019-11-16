#include "FMain.h"
extern Players players;
extern IsPlaying isplaying[4];
extern int br[9];
extern int ho[9];	
extern Bollpos boll[9];
extern int mapnow;

void PickPlayers()
{
	DrawIMG(surf.initPlayer,0,0,800,600,0,0);
	players.picked=Events(surf.initPlayer,players);				
	SDL_Flip(surf.screen);	
	if(players.picked)
	{
		if(!players.tournament)
		{
			for(int i=0; i<4; i++)						
				isplaying[i].boll=boll[players.selectMap-1];
			mapnow=players.selectMap-1;
			

		}
		else
		{
			for(int i=0; i<4; i++)						
				isplaying[i].boll=boll[0];
			mapnow=0;
		}
		BreddHojd(isplaying[0].boll);				
		bredd=br[mapnow];
		hojd=ho[mapnow];
		yta=tyta[mapnow];
		BreddHojd(boll[mapnow]);

	}
}

void LandSatt(int &isp)
{
	if(isplaying[isp].landat==true || isplaying[isp].sattbollen )
		{	
		
			isplaying[isp].landat=false;
			isplaying[isp].score++;

			if(isplaying[isp].sattbollen)
				players.antalsomsattden++;
			if(players.antalsomsattden==players.players)
			{
				++mapnow;
				
				if(mapnow==9 || players.tournament==false)
				{
					
					if(players.tournament)
					{
						players.finished=true; //Gör det möjligt att komma in på highscore
						Highscore(surf.initPlayer,isplaying,players);						
					}
					
					for(int i=0; i<4; i++)
					{
					
						isplaying[i].sattbollen=false;
						
					}
					players= Players();
				}
				
				else
				{
					bredd=br[mapnow];
					hojd=ho[mapnow];

					yta=tyta[mapnow];
					players.antalsomsattden=0;
					

					for(int i=0; i<players.players; i++)
					{
						isplaying[i].sattbollen=false;					
						isplaying[i].boll=boll[mapnow];
					}
					

					isp=0;
					BreddHojd(isplaying[isp].boll); //Centrerar skärmen
				}

				// Byt bana
			}
			else
			{
				while(isplaying[(++isp)%players.players].sattbollen==true) //Stegar frammåt till nästa spelare som itne satt den
					;

				isp%=players.players;
				BreddHojd(isplaying[isp].boll);
			}
		}
}

void MainEvents(Bools &bo,float &Rhojd,float &Rbredd,int x2,int y2,Klubba &klubb,Klubba klubbor[],int &isp,float &value)
{
	SDL_Event event;

	bool pressed = false;

	while(SDL_PollEvent(&event))
		{
			  if (event.type == SDL_KEYUP)
			  {
				switch(event.key.keysym.sym){
				  case SDLK_LEFT:
					pressed = false;
					break;
				  case SDLK_RIGHT:
					break;
				  case SDLK_UP:
					break;
				  case SDLK_DOWN:
					break;
				  default:
					break;
				}
			  }

			switch(event.type)
			{
				case SDL_MOUSEMOTION:
					break;
 

			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT && bo.skjut==false)
				{					
					bo.mousedown=true;
				}

				else if(event.button.button == SDL_BUTTON_RIGHT)
				{
					bo.mouseRdown=true;
					if(bo.Rmove==false) //Koppiterar nuvarande positionerna så man kan röra sig fritt
					{
						bo.Rmove=true;
						Rhojd=hojd1;
						Rbredd=bredd1;
					}
				}


				break;

			case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT && bo.mousedown==true)
					{						
						bo.mousedown=false;
						if(bo.Rmove==false)
						{
							if(bo.pickClub)
							{
								if((x2>640 && x2<793 && y2>10 && y2 <288 )) // Kollar om den är över klubb bilden
								{
									int tx,ty;
									x2 < ((640+793)/2) ? tx=0 : tx=3;
									ty = (y2-10)/(279/3);									
									klubb=klubbor[tx+ty];
									hitBoll(klubb,isplaying[isp].boll);
									bo.pickClub=false;		
									isplaying[isp].boll.hojdNu=0;
								}
							}
														
									
							else if(bo.setvalue)							
							{					
								bo.setvalue=false;								
								bo.skjut=true;
					
								float temp;
								value > 1.0f ? temp=2.0f-value : temp=value;
								if(temp<0.1f)
								temp=0.1f;

								isplaying[isp].boll.langd*=temp;
								isplaying[isp].boll.hojd*=temp;
								//animPlayer(value); //Vill inte animera spelare
							}
						}
					}

					if( event.button.button == SDL_BUTTON_RIGHT && bo.mouseRdown==true)
						bo.mouseRdown=false;
					break;

			case SDL_KEYDOWN:
				
				switch(event.key.keysym.sym)
				{
				
				case SDLK_ESCAPE:
				
					EscMeny(surf.initPlayer, bo, players, isplaying);
					break;

				case SDLK_LEFT:
					//bredd1 -= event.motion.xrel;
					pressed = true;
					break;
				case SDLK_RIGHT:
				  bredd1 += 5;
				  break;
				case SDLK_UP:
				  hojd1 -= 5;
				  break;
				case SDLK_DOWN:
				  hojd1 += 5;
				  break;

				
			
				case SDL_QUIT:
					bo.done=true;					
				break;
			}
		}
		}
	//if(!pressed) bredd1 -= 5;
}



void MainSkjut(bool &set,int &x2,int &y2,int &isp,Klubba &klubb,Bools &bo, float &value,Pos &windPos,Pos &WPos)
{

static float tempX,tempY,atX,atY;
	if(set)
	{
		
	atX=  ((x2-(isplaying[isp].boll.x-bredd1))/(sqrtf(powf(abs(x2-(isplaying[isp].boll.x-bredd1)),2)+powf(abs(y2-(isplaying[isp].boll.y-hojd1)),2))));
	atY=  ((y2-(isplaying[isp].boll.y-hojd1))/(sqrtf(powf(abs(x2-(isplaying[isp].boll.x-bredd1)),2)+powf(abs(y2-(isplaying[isp].boll.y-hojd1)),2))));
		set=false;
		if(klubb.hojd == 0) // kollar om det är putter eller annan
			snd.Putter();
		else
			snd.Driver();
	}

		tempX= isplaying[isp].boll.langd*atX;
		tempY= isplaying[isp].boll.langd*atY;
		if(isplaying[isp].boll.hojd>0)
			UseWind(bo.firstshot,windPos,WPos);
	
	Riktning x=CompPosX(bredd1,isplaying[isp].boll.x+tempX+windPos.x);
	Riktning y=CompPosY(hojd1,isplaying[isp].boll.y+tempY+windPos.y);			
	

	if(bredd1+tempX+windPos.x < ((bredd-16)*50) && bredd1+tempX+windPos.x >0)
		if((tempX+windPos.x > 0 && x==Hoger) || (tempX+windPos.x < 0 && x==Vanster) )
			bredd1+= tempX+windPos.x;
	
	if(hojd1+tempY+windPos.y < ((hojd-12)*50) && hojd1+tempY+windPos.y > 0 )
		if((tempY+windPos.y > 0 && y==Ner) || (tempY+windPos.y < 0 && y==Upp))
			hojd1+= tempY+windPos.y;

	isplaying[isp].boll.x+=tempX;
	isplaying[isp].boll.x+=windPos.x;
	isplaying[isp].boll.y+=tempY;
	isplaying[isp].boll.y+=windPos.y;

	
	if(isplaying[isp].boll.x<bredd*50)
		bo.skjut=Skjut(isplaying[isp],isplaying[isp].boll,windPos,atX,atY,bo.ground);
	if(bo.skjut)
		bo.skjut=OutofBounds(isplaying[isp].boll,tempX+windPos.x,tempY+windPos.y);
	if(isplaying[isp].sattbollen)
		bo.skjut=false;
	
	if(bo.skjut==false)
		{
			bo.pickClub=true;
			bo.ground=true;
			bo.setvalue=true;
			bo.power=true;
			value=0;
			bo.firstshot=true;
			isplaying[isp].landat=true;
			UseWind(bo.firstshot,windPos,WPos);
			
		}
}