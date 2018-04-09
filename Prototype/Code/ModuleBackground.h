<<<<<<< HEAD
=======

>>>>>>> 84d967ff8e25b98e519888e827ade17b5fb9a1ed

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

<<<<<<< HEAD

=======
>>>>>>> 84d967ff8e25b98e519888e827ade17b5fb9a1ed
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

