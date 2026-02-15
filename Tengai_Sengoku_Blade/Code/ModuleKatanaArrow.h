#ifndef __MODULE_KATANA__ARROW__H
#define __MODULE_KATANA__ARROW__H

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"
#include "ModuleKatana.h"
#include "SDL_mixer\include\SDL_mixer.h"

#define ARROWS 4
struct SDL_Texture;
struct Mix_Chunk;
enum arrow_state {
	NOT_EXISTING,
	LEVEL_ONE,
	LEVEL_ONE_CHARGE,
	LEVEL_ONE_CHARGING,
	LEVEL_FOUR,
	LEVEL_FOUR_CHARGE,
	SPAWN,
	ARROW_SHOT,
	LAST_ARROW_SHOT,
	CAT_SHOT,
};

class ModuleKatanaArrow : public Module
{
public:
	ModuleKatanaArrow();
	~ModuleKatanaArrow();

	bool Start();
	update_status Update();
	bool CleanUp();
private:
	void CheckState();
	void PerformActions();
	void ArrowBehaviour();
	void Shoot(SDL_Rect* frame);
	void ShootCharged();

public:
	Mix_Chunk* arrowsound = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;

	Animation spawn;
	Animation iddle;
	Animation charging;
	Animation decharging;
	Animation last_descharging;
	Animation charged;
	Animation arrow_shot;

	SDL_Rect decharging_arrow;

	fPoint* katanaPos;
	fPoint position[ARROWS];
	//fPoint position;
	arrow_state state = NOT_EXISTING;
	Path shot_movement;

	//int arrow_position = 0;
	int aux;
	bool time_shoot = true, exist = false, time_cat = true;
	bool arrow_behaviour = false;
	bool shot_delay = true;
	int shot_current = 0;
	int shot_entry = 0;

	int time_on_entry = 0;
	int current_time = 0;

	int charging_time = 0;
	int charge_on_entry = 0;

	bool create_bullet = true, update_bullet = false;

	bool left, up = true;
	float speed = 1.0f;
	float max_x = 20.0f;
	float max_y = 20.0f;
	fPoint offset;
};

#endif
