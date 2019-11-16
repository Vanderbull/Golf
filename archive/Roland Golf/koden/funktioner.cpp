#include "funktioner.h"
//#include "skjut.h"
#include <math.h>
#include <iomanip>
//#define PITCH (screen->pitch/4)
//extern float bredd1;
//extern float hojd1;
//extern int bredd;
//extern int hojd;

void Windrandom(float &x,float &y,float &max)
{
	
	x = rand() % 3;
	y = rand() % 3;
	int power = rand() %17;
	x-=1;
	y-=1;
	float speed;

	if( x==0 || y==0)
		speed=1;	//ifall bara en har vinkel
	else
		speed=0.707;  // ifall både x och y har vinkel
	max=((power+5)/10.0)*speed; 


}

void UseWind(bool &startMove, Pos &boll, Pos &WPos)
{
	static float x,y,max;
	
	if(startMove)	//sätter vinden
	{
		Windrandom(x,y,max);
		boll.x=0;
		boll.y=0;
	}


	else if(max> abs((int)x) || max > abs((int)y))	//Gör så bollen ökar en bit åt gången
	{
		if(x!=0)
		boll.x +=x*(max/60.0f);
		if(y!=0)
		boll.y +=y*(max/60.0f);
	}
	WPos.x=x*max;
	WPos.y=y*max;
	startMove=false;
}
	

void DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2) // Ritar ut sprites
{	  
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;      
  SDL_BlitSurface(img, &dest2, surf.screen, &dest);  
}

void DrawIMGAlpha(SDL_Surface *img,int x, int y, int w, int h, int x2, int y2, int trans) //Ritar ut sprites med alhpa värde
{	  
 SDL_SetAlpha(img, SDL_SRCALPHA, trans); 

  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;  
    
  SDL_BlitSurface(img, &dest2, surf.screen, &dest);   
}

void DrawLine(float startX,float startY,float stopX,float stopY) // ritar linje

{
	float dx = stopX-startX;
	float dy = stopY-startY;

	float x1,y1;


	int length = 0;
	if( abs(dx) > abs(dy) ) 
	{
		x1 = dx / abs(dx);
		y1 = dy / abs(dx);
		length = (int)abs(dx);
	}
	else
	{
		x1 = dx / abs(dy);
		y1 = dy / abs(dy);
		length = (int)abs(dy);
	}
	float stX=startX;
	float stY=startY;

	for( int i = 0; sqrtf(pow(startX-stX,2)+pow(startY-stY,2)) < 50 && CheckXY(startX,startY) ; i++ )
	{	
	
		((unsigned int*)surf.screen->pixels)[(PITCH*(int)startY + (int)startX)] = 0xFFFFFF;
		startX += x1;
		startY += y1;
	}
	
}

void drawcircle(int x, int y, int r, int c)	 //Ritar bollen
{
  int i, j;
  for (i = 0; i < 2 *r; i++)
  {
    // vertical clipping: (top and bottom)
    if ((y - r + i) >= 0 && (y - r + i) < 600)
    {
      int len = (int)sqrt((float)(r * r - (r - i) * (r - i)))*2;
      int xofs = x - len/2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= 800)
      {
        len -= (xofs + len) - 800;
      }
      int ofs = (y - r + i) * PITCH + xofs;
      
      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)surf.screen->pixels)[ofs + j] = 0xFFFFFFFF;
    }
  }
}


void Matare(Bollpos &boll) 
{	
	

	SDL_SetColorKey( surf.matare , SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surf.matare->format, 255,0,0)); 
	
	if(boll.x-bredd1 < 120 && boll.y-hojd1 > 400)
		DrawIMGAlpha(surf.matare, 1, 495, 116, 102, 1, 1,150);
	else
		DrawIMGAlpha(surf.matare, 1, 495, 116, 102, 1, 1,255);
}


float Power(bool &first) //Sägger kraften på slaget
{
	static float power=0;
	


	if(first==true)
	{
		power=0;
		first=false;
	}

	power+=0.03;	

	if(power >= 2.0f)
		first=true;	

	if(power<1.0f)
		return power;

	return 2.0f-power;
}

void ViewPower(float power) //Ritar hur mycket kraft slaget kommer få
{
	if(power>1.0f)
		return ;

	int place=(int)(64.0f*power);
	DrawIMGAlpha(surf.varde, 47, 583-place, 23, place, 0, 64-place,255);
}


void viewWind(Pos &WindPos,Bollpos &boll) //Ritar vindpekare
{
	int trans=255;
	if(boll.x-bredd1 < 120 && boll.y-hojd1 < 200)
		trans=150;
	
	SDL_SetColorKey(surf.vind, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surf.vind->format, 255,0,0));
	
	DrawIMGAlpha(surf.vind, 1, 1, 110, 110, 0, 0,trans);
	int tempX=0;
	int tempY=136;
	int Tbredd=52;
	
	if(WindPos.x==0 && WindPos.y!=0)
	{		
		if(WindPos.y>0)
			tempX=2*Tbredd;
	}

	else if(WindPos.x!=0 && WindPos.y==0)
	{
		
		if(WindPos.y>0)
			tempX=Tbredd;
		else
			tempX=3*Tbredd;
	}

	else if(WindPos.x!=0 && WindPos.y!=0)
	{
		tempY=188;
		if(WindPos.y<0)
		{
			if(WindPos.x <0)
				tempX=3*Tbredd;
		}
		else
		{
			if(WindPos.x > 0)
				tempX=Tbredd;
			else
				tempX=2*Tbredd;
		}
	}

	else
	{
		tempY=0;
		tempX=160;
	}

	/*tempY=188;
	tempX=0;*/	
	DrawIMGAlpha(surf.vind, 35, 38, Tbredd, Tbredd, tempX, tempY,trans);

	float styrka=sqrtf(WindPos.x*WindPos.x + WindPos.y*WindPos.y);
		
			
	int j=0;
	for(int i=0; i<5; i++)
	{
		DrawIMGAlpha(surf.vind, 38+8*j, 85, 8, 22, 8*((int)(styrka*powf(10,i)) % 10), 115,trans);

		if(i==0)
		{	 
			j++;
			DrawIMGAlpha(surf.vind, 38+8*j, 85, 8, 22, 8*10, 115,trans);
			
		}
		j++;


	}
	
}

	

void viewBird() //Ritar fågel
{
	static int birdposY,hoger=false;
	static float birdposX;
	static bool flying=false;
	
	SDL_SetColorKey(surf.bird, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(surf.bird->format, 255,255,255));


	if(flying==false)
	{
		birdposY= rand()%(hojd*50);		
		hoger = rand()%2;		
		flying=true;
		hoger==0 ? birdposX=0 : birdposX = bredd*50;
	}
	hoger==0 ? birdposX+=2 : birdposX-=2;

	float bx=-(bredd1+400-birdposX); 
	float by=-(hojd1+300-birdposY);

	if(bx > -255 && bx<200 && by > -205 && by < 150)
	{
		int ani= abs( (int)birdposX % 200 - (int)birdposX % 100 - (int)birdposX % 100);
		DrawIMG(surf.bird,400+2*bx,300+2*by,80,100,105*(ani/26)+hoger*420,0);
	}

	if(hoger==0 && birdposX>bredd*50)
		flying=false;
	else if(hoger==1 && birdposX < 0)
		flying=false;
		

}

void animPlayer(float value) //Borttagen funktion som ritar en spelare som slår
{	
	bool done=false;
	float tempval,val= -value - 0.01f;
	tempval=0;
	bool vanster=true;
	while(!done)
	{
		
		DrawIMG(surf.golfer,360,530,62,69,190+(63*(int)(tempval*4)),1);

		if(vanster)
		{
			if(tempval-0.25f < val)
				vanster=false;
			else
				tempval-=0.25f;
		}
		else
		{
			if(tempval+0.25f > value)
				done=true;
			else
				tempval+=0.25f;
		}
		SDL_Delay(80);
		SDL_Flip(surf.screen);
	}
}
			
			

