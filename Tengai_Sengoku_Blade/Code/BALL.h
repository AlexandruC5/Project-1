#ifndef _BALL_H
#define _BALL_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"


enum ball_states {
	IDLE_BALL,
	FLY_BALL,
	DIAGONAL_BALL,
	OPEN_BALL,
	CLOSE_BALL,
	MOVE_BALL,
};

class BALL : public Enemy {

private:
	iPoint original_pos;
	//Path path;
	Animation idle;
	Animation fly;
	Animation open;
	Animation close;
	iPoint speed;
	iPoint position;
	ball_states state = IDLE_BALL;
	void CheckState();
	void PerformActions();


	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;

	bool time_delay2 = true;
	int time_current2 = 0;
	int time_entry2 = 0;

	bool time_delay3 = true;
	int time_current3 = 0;
	int time_entry3 = 0;

	bool movement = true;

public:

	BALL(int x, int y, int type);

	void Move();
	//void shoot();
	//void ball_movement();
	



};
#endif



