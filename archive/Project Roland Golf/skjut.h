#pragma once
#include "Globals.h"

#define PITCH (surf.screen->pitch/4)

template<class T> 
T Storst(T ett, T tva);

template<class T> 
T Minst(T ett, T tva);


enum Riktning{Upp,Ner,Hoger,Vanster,Inget};

struct Pos
{
	float x;
	float y;
};


struct Bollpos
{
	float x;
	float y;
	float hojd;
	float langd;
	float hojdNu;
	Bollpos(): hojdNu(0) {}
};

struct Klubba
{
	float hojd;
	float langd;
	
	Klubba(){}
	Klubba(float hojd,float langd){this->hojd= hojd, this->langd=langd;}	
};

struct IsPlaying
{
	int x;
	int y;
	bool sattbollen;
	bool landat;
	int score;
	IsPlaying(){sattbollen=false; landat=false; score=0;}
	Bollpos boll;
};


//void MoveR(float x,float y)




void hitBoll(Klubba klubba,Bollpos &boll);

bool Skjut(IsPlaying &play, Bollpos &boll,Pos &Windpos,float &atX,float &atY,bool &ground);
Riktning CompPosX(float bredd,float positiong);
Riktning CompPosY(float hojd,float positiong);
bool CheckXY(float X,float Y);
bool OutofBounds(Bollpos &boll,float tempX,float tempY);
bool InTerrain(IsPlaying &p);
void InGoal(IsPlaying & play);