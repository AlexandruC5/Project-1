#ifndef _red_H
#define _red_H


#include "Enemy.h"
#include "Path.h"

class red : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
	Animation shoot;
	Animation death;

public:

	red(int x, int y);
	
	void Move();
};
#endif