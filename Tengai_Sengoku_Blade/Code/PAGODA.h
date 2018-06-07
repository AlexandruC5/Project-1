#ifndef _PAGODA_H
#define _PAGODA_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"



enum pagoda_state {
	PAGODA_IDLE,
	PAGODA_SHOT_HEAD,
	PAGODA_OPEN_TOLDO,
	PAGODA_FIRST_SHOT,
	PAGODA_LAST_SHOT,
	PAGODA_CLOSE_TOLDO,
	PAGODA_FAREWELL

};

class PAGODA : public Enemy {
private:
	iPoint original_pos;
	Path path;

	void CheckState();
	void PerformActions();
	void Shoot();
	Animation idle;
	Animation head_shot;
	Animation open_toldo;
    Animation close_toldo;
	Animation go_to_last_shot;
	Animation go_to_first_shot;
	

public:

	PAGODA(int x, int y, int type);

	void Move();
	//void VerticalMove();
	
	bool movement = true;
	int timer = 0;
	int ammo = 6;
	
	pagoda_state state = PAGODA_IDLE;

	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;

	bool time_delay2 = true;
	int time_current2 = 0;
	int time_entry2 = 0;

	bool time_delay3 = true;
	int time_current3 = 0;
	int time_entry3 = 0;

	bool time_delay4 = true;
	int time_current4 = 0;
	int time_entry4 = 0;


};
#endif

