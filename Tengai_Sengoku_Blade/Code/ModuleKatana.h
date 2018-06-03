#ifndef __ModuleKatana_H__
#define __ModuleKatana_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
//#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct Collider;
struct Mix_Chunk;

enum player_state {

	SPAWN_PLAYER,
	IDLE,
	BACKWARD,
	GO_BACKWARD,
	BACK_IDLE,
	SPIN,
	DEATH,
	POST_DEATH
	
};


class ModuleKatana : public Module
{
public:
	ModuleKatana();
	~ModuleKatana();

	bool Start();
	update_status Update();
	bool CleanUp();
	//void OnCollision(Collider* c1, Collider* c2);
private:
	void CheckState();
	void PerformActions();

public:
	Mix_Chunk* basicsound = nullptr;

	int aux = 0;
	int aux1 = 0;
	int alpha_player = 255;
	
	Collider* coll = nullptr;
	Collider* hitbox = nullptr;

	SDL_Texture* graphics = nullptr;
	SDL_Texture* player_death = nullptr;

	Animation* current_animation = nullptr;


	Animation idle;
	Animation backward;
	Animation intermediate;
	Animation intermediate_return;
	Animation spin;
	Animation spin_circle;
	Animation death_circle;
	
    SDL_Rect death;

	fPoint position;
	fPoint aux_spin;
	fPoint aux_death;
	
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	bool fire_rate = false;
	player_state state = IDLE;
	
	bool time = true;
	bool blink = true;

	int time_on_entry = 0;
	int current_time = 0;

	int blink_on_entry = 0;
	int blink_time = 0;
	int fire_rate_timer = 0;
	float speed;
	bool input = true;
	bool spin_pos = false;
	bool death_pos = false;
	bool explosion = false;

	int current_bullet_time = 0;
	int bullet_on_entry = 0;

	int power_up = 0;

};
#endif 