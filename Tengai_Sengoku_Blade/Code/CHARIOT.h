#ifndef _CHARIOT_H
#define _CHARIOT_H


#include "Enemy.h"
#include "Path.h"
#include "Globals.h"

class BALL;

enum chariot_state {
	start_move_in,
	start_move_out,
	start_move_with_cam,
	active,
	start_wheels,
	fight,
	start_phase2,
	phase2,
	face_shot,
};

class CHARIOT : public Enemy {
private:
	iPoint original_pos;
	Path path;
	void CheckState();
	void PerformActions();
	Animation idle;
	Animation wheel;
	Animation chariot_wheels;
	Animation chariot_wheels2;
	Animation robot;
	Animation wolf;
	Animation furni;
	Animation face_wolf;

	

	

public:

	CHARIOT(int x, int y, int type);
	//void SetCarroza();
	void Move();
	void Active();
	chariot_state state = start_move_in;

	bool time_delay = true;
	int time_current = 0;
	int time_entry = 0;

	bool time_delay2 = true;
	int time_current2 = 0;
	int time_entry2 = 0;

private:
	BALL* bola = nullptr;
};
#endif

