#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	int aux;
	//int firerate;
	bool isShooting;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	
	Animation forward;
	Animation backward;
	Animation mid;
	Animation mid2;
	iPoint position;
	Collider* player_collider;
};

#endif