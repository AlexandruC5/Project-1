#ifndef _BALL2_H
#define _BALL2_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"


enum ball_state {
	IDLE_BALL2,
	FLY_BALL2,
	DIAGONAL_BALL2,
	OPEN_BALL2,
	CLOSE_BALL2,
	MOVE_BALL2,
};

class BALL2 : public Enemy {

private:
	iPoint original_pos;
	Path path;
	Animation idle;
	Animation fly;
	Animation open;
	Animation close;
	Animation fire;
	
	ball_state state = IDLE_BALL2;
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

	BALL2(int x, int y, int type);

	void Move();
	




};
#endif


