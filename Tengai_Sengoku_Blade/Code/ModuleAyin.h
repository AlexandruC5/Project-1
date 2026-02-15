#ifndef __ModuleAyin_H__
#define __ModuleAyin_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"
//#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;
struct Collider;


enum player_state_2 {

	SPAWN_PLAYER_2,
	IDLE_2,
	BACKWARD_2,
	GO_BACKWARD_2,
	BACK_IDLE_2,
	WALK_2,
	SPIN_2,
	DEATH_2,
	POST_DEATH_2,

	CHARGING_AYIN,
	CHARGE_AYIN,
	SPIN_DECHARGING_AYIN,
	DECHARGING_AYIN,
	RETURN_IDLE_AYIN,

	ULTI_AYIN,


};

enum controller_state {


	AYN1,
	AYN2,

};


class ModuleAyin : public Module
{
public:
	ModuleAyin();
	~ModuleAyin();

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
	SDL_Texture* player_death = nullptr;

	Animation* current_animation = nullptr;

	Collider* coll = nullptr;
	Collider* hitbox = nullptr;

	Animation idle;
	Animation backward;
	Animation intermediate;
	Animation intermediate_return;

	Animation spin;
	Animation spin_circle;
	Animation death_circle;

	Animation charging;
	Animation charge;
	Animation spin_decharging;
	Animation decharging;

	Animation return_idle;
	Animation ulti_ayin;

	SDL_Rect death;
	
	fPoint position;
	fPoint aux_spin;
	fPoint aux_death;
	controller_state controller_state;
	bool destroyed = false;
	bool check_death = false, check_spawn = true;
	player_state_2 state = IDLE_2;

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

	/*int current_bullet_time = 0;
	int bullet_on_entry = 0;*/

	int power_up = 0;
	int ulti = 0;

};
#endif 
