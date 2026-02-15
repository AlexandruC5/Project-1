#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro();
	~ModuleSceneIntro();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect Psikyo;

	int time_on_entry = 0;
	int current_time = 0;



private:
	SDL_Rect s1;
	SDL_Rect s2;
	SDL_Rect s3;
	SDL_Rect s4;
	SDL_Rect s5;
	SDL_Rect s6;
	SDL_Rect s7;
	SDL_Rect s8;
	SDL_Rect s9;
	SDL_Rect s10;
	SDL_Rect s11;
	SDL_Rect s12;
	SDL_Rect s13;
	SDL_Rect s14;
	SDL_Rect s15;
	SDL_Rect s16;
	SDL_Rect s17;
	SDL_Rect s18;
	SDL_Rect s19;
	SDL_Rect s20;
};

#endif // __MODULESCENEINTRO_H__