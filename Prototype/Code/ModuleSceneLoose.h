#ifndef _ModuleLooseScene_H
#define _ModuleLooseScene_H

#include "Module.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;
class ModuleLooseScreen : public Module
{
private:


	SDL_Texture* graphics1 = nullptr;


	SDL_Rect background;
	_Mix_Music* music = nullptr;

public:

	ModuleLooseScreen();
	~ModuleLooseScreen();
	update_status Update();
	
	bool CleanUp();
	bool Start();

};

#endif





