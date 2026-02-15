#ifndef _SHARPENER_KNIFE_H
#define _SHARPENER_KNIFE_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"


enum sharpener_state {
	SPAWN_SHARPENER ,
	GO_BACKWARD_SHARPENER,
	SHOOT_SHARPENER,
	RETURN_SHOOT_SHARPENER,
	IDLE_FORWARD,
	GO_SPIN_SHARPENER,
	IDLE_SHARPENER,
	FULL_SHOOT_SHARPENER,
	FAREWELL_SHARPENER
};


class SHARPENER_KNIFE : public Enemy {

private:
	void CheckState();
	void PerformActions();

	int original_pos_x;
	int original_pos_y;
	int spot = 0;;
	bool going_forward = true;
	bool active_shoot = false;
	int ammo = 6;
	Path path;

	Animation idle;
	Animation shoot;
	Animation return_shoot;
	Animation spin;
	Animation spin_forward;
	Animation spin_backward;

public:

	SHARPENER_KNIFE(int x, int y, int type);
	sharpener_state state = SPAWN_SHARPENER;
	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;
	void Move();
	void Shoot();
};
#endif


