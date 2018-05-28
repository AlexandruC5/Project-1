#ifndef _DEMONWHEEL_H
#define _DEMONWHEEL_H


#include "Enemy.h"
#include "Path.h"

class DEMONWHEEL : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
	Animation shoot;
	Animation death;

public:

	DEMONWHEEL(int x, int y, int type);

	void Move();
};
#endif
