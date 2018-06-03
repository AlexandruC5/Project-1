#ifndef __MODULE_AYIN__ULTIMATE__H
#define __MODULE_AYIN__ULTIMATE__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleAyin.h"
#include "SDL_mixer\include\SDL_mixer.h"

struct SDL_Texture;

enum ulti_state {
	NO_ULTI,
	FIRST_PHASE,
	SECOND_PHASE,
	THIRD_PHASE,
	SHOT_PHASE,

};

class ModuleAyinUltimate : public Module
{
public:
	ModuleAyinUltimate();
	~ModuleAyinUltimate();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	void CheckState();
	void PerformActions();
	

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation* current_animation_2 = nullptr;
	Animation* current_animation_3 = nullptr;
	Animation* current_animation_4 = nullptr;

	Animation phase1;
	Animation phase2;
	Animation phase3;



	


	fPoint position;
	ulti_state state = NO_ULTI,  state2 = NO_ULTI,  state3 = NO_ULTI,  state4 = NO_ULTI;
	Path shot_movement;
	bool active = false, active2 = false;

	int spot1 = 0, spot2 = 0, spot3 = 0, spot4 = 0;
	bool ulti = true,  ulti2 = true;

	int aux, aux1;
	bool time_shoot = true, exist = false, time_cat = true, exist2 = false;
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

	bool create_wave = true, update_bullet = false;
	int state_wave = 0;
};

#endif


