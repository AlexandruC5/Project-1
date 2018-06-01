#ifndef __ULTI_PARCHMENT_H__
#define __ULTI_PARCHMENT__

#include "Enemy.h"
#include "Path.h"

class Ulti_Parchment : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	iPoint originalposition;
	Animation iddle;
	Path movement;
public:

	Ulti_Parchment(int x, int y, int type);

	void Move();
};

#endif // __ULTI_PARCHMENT_H__
