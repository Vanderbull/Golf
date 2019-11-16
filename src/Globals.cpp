#include "Globals.h"


float hojd1=0;
float bredd1=0;
int bredd;
int hojd;

//SDL_Surface* screen;
//SDL_Surface* image;
//SDL_Surface* golfimage;
//SDL_Surface* initPlayer;
Surf surf;
Sound snd;

int **yta;
int ***tyta;

Sound::Sound()
{
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 512;


	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}

	three = Mix_LoadWAV("sounds\\three.wav");
	water = Mix_LoadWAV("sounds\\water.wav");
	hole = Mix_LoadWAV("sounds\\hole.wav");
	putter = Mix_LoadWAV("sounds\\putter.wav");
	driver = Mix_LoadWAV("sounds\\driver.wav");
}

Sound::~Sound()
{
	Mix_FreeChunk(three);
	Mix_FreeChunk(water); 
	Mix_FreeChunk(hole);
	Mix_FreeChunk(putter);
	Mix_FreeChunk(driver);
	Mix_CloseAudio();
}

void Sound::Three()
{
	int channel = Mix_PlayChannel(-1, three, 0);
	if(channel == -1) 
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
}
void Sound::Water()
{
	int channel = Mix_PlayChannel(-1, water, 0);
	if(channel == -1) 
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
}
void Sound::Hole()
{
	int channel = Mix_PlayChannel(-1, hole, 0);
	if(channel == -1) 
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
}
void Sound::Putter()
{
	int channel = Mix_PlayChannel(-1, putter, 0);
	if(channel == -1) 
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
}
void Sound::Driver()
{
	int channel = Mix_PlayChannel(-1, driver, 0);
	if(channel == -1) 
		fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
}



Surf::Surf()
{
	screen = SDL_SetVideoMode(800,600,32,SDL_SWSURFACE |SDL_DOUBLEBUF | SDL_FULLSCREEN );
	
	if(! screen)
	{
		cerr << "Error: SetVideoMode failed" << endl;		
		SDL_Quit();
		
	}	
	
	image = SDL_LoadBMP("allt.bmp");
	golfimage = SDL_LoadBMP("golfallt.bmp");
	initPlayer = SDL_LoadBMP("introbild.bmp");
	matare = SDL_LoadBMP("matare.bmp");	
	bird = SDL_LoadBMP("bird.bmp");
	golfer = SDL_LoadBMP("golfer.bmp");
	varde = SDL_LoadBMP("varde.bmp");
	vind = SDL_LoadBMP("vind.bmp");
	
	SDL_Surface *temp = SDL_LoadBMP("font.bmp");
	surf.gFont = SDL_ConvertSurface(temp, surf.screen->format, SDL_SWSURFACE);
	SDL_FreeSurface(temp);


	if(!image || !golfimage || !initPlayer || !matare || !bird || !golfer || !varde || !vind)
	{
		cerr << "Error";		
		SDL_Quit();
	}	
	
	
}

Surf::~Surf()
{
	SDL_FreeSurface(image);
	SDL_FreeSurface(golfimage);
	SDL_FreeSurface(initPlayer);
	SDL_FreeSurface(matare);
	SDL_FreeSurface(bird);
	SDL_FreeSurface(golfer);
	SDL_FreeSurface(varde);
	SDL_FreeSurface(vind);
	SDL_FreeSurface(gFont);

	for(int i=0; i<9; i++)
	{
		for(int j=0; j< bredd; j++)
		{			
			delete [] tyta[i][j];
		}
		delete [] tyta[i];
	}


}

Bools::Bools()
{
	mousedown=false;
	mouseRdown=false;
	skjut=false;
	value=0;
	setvalue=true;

	firstshot=true;
	pickClub=true;
	ground=true;
	power=true;	
	Rmove=false;
	done = false; 	
}