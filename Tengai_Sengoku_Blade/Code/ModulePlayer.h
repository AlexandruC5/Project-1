#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;
struct SDL_Rect;
class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool activePU[2] = { false };

public:

	int aux;
	int score_x = 60;
	int font_score = -1;
	int font_players = -1;
	char score_text[10];
	uint score = 0;
	//int firerate;
	bool isShooting;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* basic = nullptr;
	Animation forward;
	Animation backward;
	Animation mid;
	Animation mid2;
	Animation death;
	iPoint position;
	Collider* player_collider;
	bool destroyed = false;
};

#endif