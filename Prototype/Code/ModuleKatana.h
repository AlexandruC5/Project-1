#ifndef __ModuleKatana_H__
#define __ModuleKatana_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
//#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct Collider;


enum player_state {

	SPAWN_PLAYER,
	IDLE,
	BACKWARD,
	GO_BACKWARD,
	BACK_IDLE,
	
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

	int aux = 0;
	int aux1 = 0;
	int alpha_player = 255;
	

	SDL_Texture* graphics = nullptr;
	

	Animation* current_animation = nullptr;


	Animation idle;
	Animation backward;
	Animation intermediate;
	Animation intermediate_return;
	

	fPoint position;
	
	
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	player_state state = IDLE;
	
	bool time = true;
	bool blink = true;

	int time_on_entry = 0;
	int current_time = 0;

	int blink_on_entry = 0;
	int blink_time = 0;
	float speed;
	bool input = true;
	bool spin_pos = false;
	bool death_pos = false;
	bool explosion = false;

	int current_bullet_time = 0;
	int bullet_on_entry = 0;

};
#endif 