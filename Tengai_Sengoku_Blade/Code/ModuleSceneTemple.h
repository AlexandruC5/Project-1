#ifndef __ModuleSceneTemple_H__
#define __ModuleSceneTemple_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneTemple : public Module
{
public:

	ModuleSceneTemple();
	~ModuleSceneTemple();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	
	float speed = 1.5;

	float posx = 0, posy = 0;
	float posx2 = 390, posy2 = 2;
	float posy3 = 0;
	float pos4 = 224;
	float pos5 = 491;

	int aux_time = 0;
	int aux_time2 = 0;
	int aux_time3 = 0;

	bool transition = false;
	bool change = true;
	bool player2 = false;
	
	SDL_Texture* graphics = nullptr;

	SDL_Rect Mountains;
	SDL_Rect Gateway;
	SDL_Rect Statue;
	SDL_Rect scroll_bg;
	SDL_Rect scroll_down;
	SDL_Rect scroll_final;

	Collider* coll_left = nullptr;
	Collider* coll_right = nullptr;
	Collider* coll_up = nullptr;
	Collider* coll_down = nullptr;
	
	float bg_speed = 0.10;
	float katana_speed = speed / 1.5;
	bool speed_activation = false;
};

#endif // __ModuleSceneTemple_H__


