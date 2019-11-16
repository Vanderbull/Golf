//#include "skjut.h"
//#include "funktioner.h"
//#include "playerinput.h"
#include "FMain.h"

#define Screen_width 640
#define Screen_Height 480
Players players;
IsPlaying isplaying[4];
int br[9],ho[9];
Bollpos boll[9];
Bools bo;
int mapnow=0;

using namespace std;

int main(int, char**)
{
	string name;
	ofstream fil;
	
	string saving;
	srand((unsigned)time(0));	
	char ab[]="level1";
	
	tyta = new int **[9];
	for(int k=0; k<9; k++)
	{	
		ifstream infil;
		ab[5]='1'+k;
		infil.open(ab);
		infil >> br[k] >> ho[k] >> boll[k].x >> boll[k].y;				
	
		tyta[k]= new int *[br[k]];
		for(int i=0; i<br[k]; ++i)
		{
			tyta[k][i]= new int[ho[k]];
		}

		for(int i=0; i<br[k]; i++)
		{
			for(int j=0; j<ho[k]; j++)
			{
				infil >> tyta[k][i][j];
			}
		}

		infil.close();
	}


	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) <0 )
	{
	  printf("Unable to init SDL: %s\n", SDL_GetError());
	  return 1;
	}

	atexit(SDL_Quit);

	//SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	
	
		
	
	float value=0;	
	/*Bools bo;*/
	int x2=0,y2=0;
	int isp=0;
	
	
	Klubba klubb;
	Klubba klubbor[]={Klubba(6.0f,8.0f),Klubba(6.0f,7.0f),Klubba(9.0f,3.0f),Klubba(6.0f,9.0f),Klubba(11.0f,2.2f),Klubba(0.0f,13.0f)};
	
	float Rhojd,Rbredd;
	Pos windPos={0,0};
	Pos WPos;
	UseWind(bo.firstshot,windPos,WPos);	

	for(int i=0; i<4; i++)
		isplaying[i].boll=boll[mapnow];		
	
	
		while(!bo.done)
		{
			
			while(!players.picked)
			{
				SDL_ShowCursor(SDL_ENABLE);
				PickPlayers();
			}
			if(bo.done)
				break;	
			if(bo.pickClub)
				SDL_ShowCursor(SDL_ENABLE);
			else
				SDL_ShowCursor(SDL_ENABLE);
		
		int Starttime=SDL_GetTicks();

		LandSatt(isp);	
		
		MainEvents(bo,Rhojd,Rbredd,x2,y2,klubb,klubbor,isp,value);
			
		const int x=55;
		const int a=670;
		const int b=725;
		const int c=30;
		
		if(bo.skjut==false)
		{
			SDL_GetMouseState(&x2, &y2);
			if(x2>Screen_width-10)
			{
				bredd1 += 30;
			}
			if(x2 < 10)
			{
				bredd1 -= 30;
			}
			if(y2 >  Screen_Height-10)
			{
				hojd1 += 30;
			}
			if(y2 < 10)
			{
				hojd1 -= 30;
			}
		}

		static int button=1;
		static bool down=false;
		static bool set=true;		
		if(bo.skjut==true)
		{		
			MainSkjut(set,x2,y2,isp,klubb,bo,value,windPos,WPos);	
		}
		else
		{			
			set=true;			
		}
	
		//main map drawing
		for(int i=1; i<18; ++i)
			for(int j=1; j<17; ++j) //ritar ut allt
			{
				//if(bo.Rmove);
				//	DrawIMG(surf.image, i*50-50-(int)Rbredd%50, j*50-50-(int)Rhojd%50, 50, 50,(((50+yta[i-1+((int)Rbredd/50)][j-1+(int)Rhojd/50])/50)*50-50), (yta[i-1+(int)Rbredd/50][j-1+(int)Rhojd/50]%50)*50-50);
				//else
				/*	DrawIMG(surf.image, 
						i*50-50-(int)bredd1%50, 
						j*50-50-(int)hojd1%50, 
						50, 
						50,
						(((50+yta[i-1+((int)bredd1/50)][j-1+(int)hojd1/50])/50)*50-50), 
						(yta[i-1+(int)bredd1/50][j-1+(int)hojd1/50]%50)*50-50);*/

				// spann 50->(18x50)
				int toint = bredd1;
				int result = toint%50;
				if( bredd1 < 0)
				{
					bredd1 = 0;
				}
				if(hojd1 < 0)
				{
					hojd1 = 0;
				}
				DrawIMG(surf.image, 
						i*50-50-(int)bredd1%50, 
						j*50-50-(int)hojd1%50, 
						50, 
						50,
						(((50+yta[i-1+((int)bredd1/50)][j-1+(int)hojd1/50])/50)*50-50), 
						((yta[i-1+(int)bredd1/50][j-1+(int)hojd1/50]%50)*50-50));
			}		
		

		
		
		if(bo.mouseRdown)
		{
			if((x2 > 700 && ((Rbredd+20)/50) < (bredd-18)))		
				Rbredd+=20;

			if((x2 < 100) && Rbredd-20 > 0 )
				Rbredd-=20;

			if(y2 > 500 && ((Rhojd+20)/50)<(hojd-17))
				Rhojd+=20;

			if(y2 < 100 && (Rhojd-20) > 0)
				Rhojd-=20;	
		}
		else if(bo.Rmove==false)
		{
			
			drawcircle((int)isplaying[isp].boll.x-(int)bredd1,(int)isplaying[isp].boll.y-(int)hojd1,3+(int)(isplaying[isp].boll.hojdNu/200),3+(int)(isplaying[isp].boll.hojdNu/200)); //bollen
			if(bo.skjut==false && bo.pickClub==false);
			DrawLine(isplaying[isp].boll.x-bredd1,isplaying[isp].boll.y-hojd1,x2,y2);
		}

		if( bo.mouseRdown==false && bo.Rmove)
		{
			//float x,y;
			//x=30*(Rbredd-bredd1)/(sqrtf(powf(abs(Rbredd-bredd1),2)+powf(abs(Rhojd-hojd1),2)));
			//y=30*(Rhojd-hojd1)/(sqrtf(powf(abs(Rbredd-bredd1),2)+powf(abs(Rhojd-hojd1),2)));
			//if(abs(Rbredd-bredd1) < 30)
			//	if(abs(Rhojd-hojd1) < 30)
			//		bo.Rmove=false;
			//
			//
			//Rbredd-=x;
			//Rhojd-=y;
		}

		if(bo.skjut==false && bo.pickClub && bo.Rmove==false);
			DrawIMG( surf.golfimage, 640, 10, 153, 278, 1, 1);
		Matare(isplaying[isp].boll);
		if(bo.pickClub==false && bo.mousedown && bo.skjut==false)
					{
						value=Power(bo.power);
						
						if(bo.power)
						{
							bo.setvalue=false;
							bo.skjut=true;							

							float temp;
							value > 1.0f ? temp=2.0f-value : temp=value;
							if(temp<0.1f)
								temp=0.1f;
							isplaying[isp].boll.hojd*= temp;
							isplaying[isp].boll.langd*=temp;
						}
					}
		
		ViewPower(value);	
		//viewWind(WPos,isplaying[isp].boll);
		if(bo.Rmove==false)
			viewBird();
	
			
		SDL_Flip(surf.screen);	 
		
		//	cout << SDL_GetTicks()-Starttime << endl;

		
		if(SDL_GetTicks()-Starttime <20)
			SDL_Delay(20-(SDL_GetTicks()-Starttime));
		
	}	
	SDL_Quit();
	return 0;
	
}