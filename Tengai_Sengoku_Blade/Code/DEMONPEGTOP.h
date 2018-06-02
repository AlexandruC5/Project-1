#ifndef _DEMONPEGTOP_H
#define _DEMONPEGTOP_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"

enum state_pegtop {
	IDLE_PEGTOP,
	SHOT_PEGTOP,
	RETURN_SHOT_PEGTOP,
	FAREWELL_PEGTOP,
};

class DEMONPEGTOP : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation idle;
	Animation shot;
	Animation return_shot;
	Animation forward;
	Animation backward;
	Animation shoot;
	Animation death;
	int shootTimer = 0;
	int type;
	state_pegtop state = IDLE_PEGTOP;
	void CheckState();
	void PerformActions();
	void Shoot();
public:

	DEMONPEGTOP(int x, int y, int type);
	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;
	int ammo = 3;
	int weapon_timer = 0;
	void Move();
};
#endif
