#ifndef __POWER_UP_H__
#define __POWER_UP_H__

#include "Enemy.h"
#include "Path.h"

class Power_Up : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation iddle;
	Path movement;
public:

	Power_Up(int x, int y);

	void Move();
};

#endif // __POWER_UP_H__