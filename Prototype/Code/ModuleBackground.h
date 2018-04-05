#ifndef __MODULEBACKGROUND_H__
#define __MODULEBACKGROUND_H__

#include "Module.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* background = nullptr;
	SDL_Texture* stuff = nullptr;
};

#endif // __MODULEBACKGROUND_H__