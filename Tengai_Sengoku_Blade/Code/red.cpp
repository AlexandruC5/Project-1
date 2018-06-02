#include "Application.h"
#include "red.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"



red::red(int x, int y, int type) : Enemy(x, y,type)
{


	backward.PushBack({ 16,  60, 30, 30 });
	backward.PushBack({ 62, 60, 30, 30 });
	backward.PushBack({ 110, 60, 30, 30 });
	backward.PushBack({ 155, 60, 30, 30 });
	backward.speed = 0.15f;



	path.PushBack({ -1, 0 }, 100, &backward);
	path.PushBack({ 2.5, 0 }, 500, &backward);


	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_RED, (Module*)App->enemies);

	original_pos = { x,y };


}


void red::Move()
{
	iPoint path_pos = path.GetCurrentPosition(&animation);
	position.x = float(original_pos.x + path_pos.x);
	position.y = float(original_pos.y + path_pos.y);


}