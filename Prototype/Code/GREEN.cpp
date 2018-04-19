#include "Application.h"
#include "GREEN.h"
#include "ModuleCollision.h"



Green::Green(int x, int y) : Enemy(x, y)
{


	fly.PushBack({ 22,  12, 32, 31 });
	fly.PushBack({ 78, 10, 32, 32 });
	fly.PushBack({ 135, 10, 32, 20 });
	fly.PushBack({ 190, 10, 32, 32 });


	path.PushBack({ 0.05f, 1 }, 500, &fly);


	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}

void Green::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);


}