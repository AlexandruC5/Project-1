#include "Application.h"
#include "GREEN2.h"
#include "ModuleCollision.h"



GREEN2::GREEN2(int x, int y, int type) : Enemy(x, y, type)
{


	backward.PushBack({ 12, 16, 33, 30 });
	backward.PushBack({58, 16, 35, 30 });
	backward.PushBack({ 105, 16, 34, 30 });
	backward.PushBack({ 150, 16, 33, 30 });
	backward.speed = 0.15f;


	path.PushBack({ -1.f, 0 }, 100, &backward);
	path.PushBack({ 2.5f, 0 }, 300, &backward);
	path.PushBack({ 0, 2.f }, 300, &backward);
	path.PushBack({ -2.f, 0 }, 1000, &backward);






	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}

void GREEN2::Move()
{
	iPoint path_pos = path.GetCurrentPosition(&animation);
	position.x = float(original_pos.x + path_pos.x);
	position.y = float(original_pos.y + path_pos.y);
}