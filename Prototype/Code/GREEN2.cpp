#include "Application.h"
#include "GREEN2.h"
#include "ModuleCollision.h"



GREEN2::GREEN2(int x, int y) : Enemy(x, y)
{


	backward.PushBack({ 39,  34, 30, 30 });
	backward.PushBack({ 86, 34, 30, 30 });
	backward.PushBack({ 132, 34, 30, 30 });
	backward.PushBack({ 177,34,30,30 });



	path.PushBack({ -0.5f, 0 }, 250, &backward);





	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}

void GREEN2::Move()
{
	position = original_pos + path.GetCurrentPosition(&animation);


}