#ifndef __COIN_H__
#define __COIN_H__

#include "Enemy.h"
#include "Path.h"

class COIN : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation up;
	Animation parabola;
	Animation down;
	Path movement;
public:

	COIN(int x, int y, int type);

	void Move();
};

#endif // __COIN_H__

