#include "Application.h"
#include "Fish.h"
#include "ModuleCollision.h"



Fish::Fish(int x, int y) : Enemy(x, y)
{


	backward.PushBack({ 34,  99, 30, 24 });
	backward.PushBack({ 85, 99, 31, 24 });
	backward.PushBack({ 133, 99, 31, 24 });
	



	path.PushBack({ -0.5f, 0 }, 500, &backward);


	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}

void Fish::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);


}