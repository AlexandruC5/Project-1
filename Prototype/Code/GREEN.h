#ifndef _GREEN_H
#define _GREEN_H


#include "Enemy.h"
#include "Path.h"

class Green : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation fly;
	
public:

	Green(int x, int y);

	void Move();
};
#endif//GREEN