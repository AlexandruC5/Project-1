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
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	//SDL_Rect screen;
	
	SDL_Rect title;
	SDL_Rect background;
	SDL_Rect company1;
	SDL_Rect company2;
	SDL_Rect start_button;
	

	_Mix_Music* music = nullptr;

public:
	update_status Update();
	bool CleanUp();
	bool Start();

	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();
};





#endif
