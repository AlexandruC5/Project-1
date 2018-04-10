#ifndef __ModuleWelcomeScreen_H__
#define __ModuleWelcomeScreen_H__

#include "Module.h"


#define NUM_TEXTURES 2

struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;

class ModuleWelcomeScreen : public Module
{
private:

	int aux;
	bool print;

    // Scrolling variables
	float scroll;
	float  scroll2;
	float  scroll3;
	float  scroll4;
	float  scroll5;
	float  scroll6;
	float  scroll7;
	float  scroll8;
	float  scroll9;
	float  scroll10;
	float  scroll11;
	float  scroll12;
	float  scroll13;
	float  scroll14;

	//Component Textures
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;

	//Layer Textures
	SDL_Texture* bg1 = nullptr;
	SDL_Texture* bg2 = nullptr;
	SDL_Texture* bg3 = nullptr;
	SDL_Texture* bg4 = nullptr;
	SDL_Texture* bg5 = nullptr;
	SDL_Texture* bg6 = nullptr;
	SDL_Texture* bg7 = nullptr;
	
	//Rect Main Textures
	SDL_Rect title;
	SDL_Rect background;
	SDL_Rect company1;
	SDL_Rect company2;
	SDL_Rect start_button;

	//Rect Layers
	SDL_Rect bg1_rect;
	SDL_Rect bg2_rect;
	SDL_Rect bg3_rect;
	SDL_Rect bg4_rect;
	SDL_Rect bg5_rect;
	SDL_Rect bg6_rect;
	SDL_Rect bg7_rect;
	
	// Music
	_Mix_Music* music = nullptr;

	/*
	int time;
	int aux;
	bool print;
	int timer;
	*/

public:

	//Functions
	update_status Update();
	bool Init();
	bool CleanUp();
	bool Start();
	
	//Constructor&Destructor
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();
};





#endif
