#ifndef _ORIENTAL_GENIUS_H
#define _ORIENTAL_GENIUS_H


#include "Enemy.h"
#include "Path.h"

class OrientalGenius : public Enemy {
private:
	iPoint original_pos;
	Path path;
	Animation back;
	Animation up1, up2, up3;
	Animation stay;
	Animation shoot;
public:

	OrientalGenius(int x, int y);

	void Move();
};
#endif
