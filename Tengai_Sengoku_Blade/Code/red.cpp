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



	path.PushBack({ -0.5f, 0 }, 250, &backward);
	//path.PushBack({ -0.5f, 0.5f }, 200, &backward);




	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}


void red::Move()
{

	position = original_pos + path.GetCurrentPosition(&animation);


}