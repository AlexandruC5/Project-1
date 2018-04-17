#ifndef _FISH_
#define _FISH_


#include "Enemy.h"
#include "Path.h"
class Enemy_Fish : public Enemy {
private:

	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;

public:

	Enemy_Fish(int x, int y);

	void Move();
};
#endif