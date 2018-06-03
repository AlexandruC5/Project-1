#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	int spoty;
	int wheel_x, wheel_y;
	int w1x, w1y;
protected:
	Animation * animation = nullptr;
	Animation * animation_chariot = nullptr;
	Animation * animation_chariot_wheels = nullptr;
	Animation * animation_chariot_wheels2 = nullptr;
	Animation * animation_ball = nullptr;
	Animation * furniture = nullptr;
	Animation * chariot_robot = nullptr;
	Animation * chariot_wolf = nullptr;
	Animation * chariot_face_wolf = nullptr;
	Collider* collider = nullptr;

	//Final Boss
	Animation* demon_wheel = nullptr;
	Animation* demon_up = nullptr;
	Animation* demon_down = nullptr;

	Animation* demon_wheel1 = nullptr;

public:
	fPoint position;

public:
	Enemy(int x, int y, int type);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__