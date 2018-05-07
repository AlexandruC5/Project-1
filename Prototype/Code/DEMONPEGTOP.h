#ifndef _DEMONPEGTOP_H
#define _DEMONPEGTOP_H


#include "Enemy.h"
#include "Path.h"

class DEMONPEGTOP : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	Animation forward;
	Animation backward;
	Animation shoot;
	Animation death;

public:

	DEMONPEGTOP(int x, int y);

	void Move();
};
#endif
