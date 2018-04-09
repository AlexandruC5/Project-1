<<<<<<< HEAD


#ifndef __MODULEBACKGROUND_H__
#define __MODULEBACKGROUND_H__

#include "Module.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();
	int x=0, x1=511, x2=1022;
	int wh = 0;
	int timer = 0;
	bool Start();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	SDL_Texture* background = nullptr;
	SDL_Texture* stuff = nullptr;
	
	SDL_Rect* Back = nullptr;
};

#endif // __MODULEBACKGROUND_H__

=======
//
//
//#ifndef __MODULEBACKGROUND_H__
//#define __MODULEBACKGROUND_H__
//
//#include "Module.h"
//
//struct SDL_Texture;
//
//class ModuleBackground : public Module
//{
//public:
//	ModuleBackground();
//	~ModuleBackground();
//	int x=0, x1=511, x2=1022;
//	int wh = 0;
//	int timer = 0;
//	bool Start();
//	update_status Update();
//	update_status PreUpdate();
//	bool CleanUp();
//
//	SDL_Texture* background = nullptr;
//	SDL_Texture* stuff = nullptr;
//
//	SDL_Rect* Back = nullptr;
//};
//
//#endif // __MODULEBACKGROUND_H__
//
>>>>>>> bd4bc993eec117b2f579f055ed6fb8f3fab2c3c4
