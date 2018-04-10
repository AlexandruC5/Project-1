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
    // Scrolling variables
	int scroll;
	int scroll2;
	int bg_width;


	//Component Textures
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;

	//Layer Textures
	SDL_Texture* bg1 = nullptr;
	
	//Rect Main Textures
	SDL_Rect title;
	SDL_Rect background;
	SDL_Rect company1;
	SDL_Rect company2;
	SDL_Rect start_button;

	//Rect Layers
	SDL_Rect bg1_rect;
	
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
