#pragma once
#include "skjut.h"
//extern int bredd;
//extern int hojd;

//struct Pos;
//struct Bollpos;
void Windrandom(float &x,float &y,float &max);
void UseWind(bool &startMove, Pos &boll,Pos &WPos);
void DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2);
void DrawIMGAlpha(SDL_Surface *img,int x, int y, int w, int h, int x2, int y2, int trans);

void DrawLine(float startX,float startY,float stopX,float stopY);
void drawcircle(int x, int y, int r, int c);
void Matare(Bollpos &boll);
float Power(bool &first);
void ViewPower(float power);
void viewWind(Pos &WindPos,Bollpos &boll);
void viewBird();
void animPlayer(float value);
