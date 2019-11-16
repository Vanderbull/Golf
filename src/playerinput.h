#include "funktioner.h"

struct Players
{
	bool tournament;
	int players,playeractivated;
	int antalsomsattden;
	bool picked;
	bool finished;
	
	char names[4][30];//={{'\0'},{'\0'},{'\0'},{'\0'}};
	int nameplace[4];
	int selectMap;
	Players();
};

bool Events(SDL_Surface *img,Players &pl);
void drawcharacter(int x, int y, int character);
void drawstring(int x, int y, char *s);
void InitGfont();
void BreddHojd(Bollpos boll);
void Highscore(SDL_Surface* start,IsPlaying isp[],Players &play);
void EscMeny(SDL_Surface *init, Bools &bo, Players &players, IsPlaying isplaying[]);