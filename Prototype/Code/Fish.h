#ifndef _FISH_H
#define _FISH_H


#include "Enemy.h"
#include "Path.h"

class Fish : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
	
public:

	Fish(int x, int y);

	void Move();
};
#endif