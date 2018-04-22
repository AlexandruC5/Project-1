#ifndef _GREEN2_H
#define _GREEN2_H


#include "Enemy.h"
#include "Path.h"

class GREEN2 : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
public:

	GREEN2(int x, int y);

	void Move();
};
#endif