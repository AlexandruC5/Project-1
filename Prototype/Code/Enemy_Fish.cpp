#include "Application.h"
#include "Enemy_Fish.h"
#include "ModuleCollision.h"



Enemy_Fish::Enemy_Fish(int x, int y) : Enemy(x, y)
{
	
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	original_pos = { x,y };

	//Animation

	backward.PushBack({ 34, 99, 30, 24 });
	backward.PushBack({ 85, 99, 31, 24 });
	backward.PushBack({ 133, 99, 31, 24 });
	backward.speed = 0.1f;

	animation = &backward;


}


void Enemy_Fish::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);
}