#ifndef __MODULE_AYIN__ARROW__H
#define __MODULE_AYIN__ARROW__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleAyin.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum arrow_state_2 {
	NOT_EXISTING_2,
	LEVEL_ONE_2,
	LEVEL_ONE_CHARGE_2,
	LEVEL_ONE_CHARGING_2,
	LEVEL_FOUR_2,
	LEVEL_FOUR_CHARGE_2,
	SPAWN_2,
	WAVE_SHOT_2,
	SWORD_WAVE,
	AYIN_KEEP_DECHARGING,
	AYIN_COMEBACK,
	LAST_ARROW_SHOT_2,
	CAT_SHOT_2,
};

class ModuleAyinArrow : public Module
{
public:
	ModuleAyinArrow();
	~ModuleAyinArrow();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	void CheckState();
	void PerformActions();
	//void ArrowBehaviour();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;

	Animation spawn;
	Animation iddle;
	Animation charging;
	Animation charged;
	Animation decharging;
	Animation return_sword;

	
	Animation arrow_shot;

	SDL_Rect decharging_arrow;


	fPoint position;
	arrow_state_2 state = NOT_EXISTING_2;
	Path shot_movement;

	int arrow_position = 0;
	int aux, aux1;
	bool time_shoot = true, exist = false, time_cat = true;
	bool time_shoot2 = false, time_shoot3 = false;
	bool arrow_behaviour = false;
	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	int time_on_entry = 0;
	int current_time = 0;

	int time_on_entry2 = 0;
	int current_time2 = 0;

	int time_on_entry3 = 0;
	int current_time3 = 0;

	int charging_time = 0;
	int charge_on_entry = 0;

	bool create_bullet = true, update_bullet = false;
};

#endif

