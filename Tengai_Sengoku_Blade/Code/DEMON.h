#ifndef _DEMON_H
#define _DEMON_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"

enum state_demon {
	IDLE_DEMON,
	CIRCULAR_ATTACK,
	FIRE_WHEELS,
	SHOT_FIRE_WHEELS,
	CIRCULAR_ATTACK_2
	
};

class DEMON : public Enemy {
private:
	iPoint original_pos;
	Path path;

	
	Animation idle;
	Animation circular_shot;

	Animation up;
	Animation down;
	Animation wheel;

	Animation wheel1;
	
	int shootTimer = 0;
	int type;
	state_demon state = IDLE_DEMON;
	bool collider_active = false;
	void CheckState();
	void PerformActions();
	void Shoot();
public:

	DEMON(int x, int y, int type);
	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;

	bool time_delay2 = true;
	int time_current2 = 0;
	int time_entry2 = 0;

	bool active = true;
	int ammo = 3;
	int weapon_timer = 0;
	void Move();
	
};
#endif

