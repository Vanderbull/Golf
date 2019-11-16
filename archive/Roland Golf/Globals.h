#include <iostream>
//#include "funktioner.h"
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include "SDL_mixer.h"
#include "SDL.h"


#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
#pragma comment(lib,"SDL_mixer.lib")

using namespace std;

class Sound
{
public:
	Sound();
	~Sound();
	void Three();
	void Water();
	void Hole();
	void Putter();
	void Driver();

private:
	Mix_Chunk *three;
	Mix_Chunk *water;
	Mix_Chunk *hole;
	Mix_Chunk *putter;
	Mix_Chunk *driver;
	
};

struct Surf
{
	Surf();
	~Surf();
	SDL_Surface* screen;
	SDL_Surface* image;
	SDL_Surface* golfimage;
	SDL_Surface* initPlayer;
	SDL_Surface* matare;
	SDL_Surface *bird;
	SDL_Surface *golfer;
	SDL_Surface* varde;
	SDL_Surface* vind;
	SDL_Surface *gFont;
};

struct Bools
{
	bool mousedown;
	bool mouseRdown;
	bool skjut;
	float value;
	bool setvalue;
	bool done; 	

	bool firstshot;
	bool pickClub;
	bool ground;
	bool power;
	//bool done; 
	bool Rmove;
	Bools();
};


extern float hojd1;
extern float bredd1;
extern int bredd;
extern int hojd;

extern Surf surf;
extern Sound snd;
extern int **yta;
extern int ***tyta;
