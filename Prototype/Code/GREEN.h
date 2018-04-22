#ifndef _GREEN_H
#define _GREEN_H


#include "Enemy.h"
#include "Path.h"

class GREEN : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
public:

	GREEN(int x, int y);

	void Move();
};
#endif