#include "Application.h"
#include "DEMONWHEEL.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"



DEMONWHEEL::DEMONWHEEL(int x, int y) : Enemy(x, y)
{


	backward.PushBack({ 278,  8, 30, 31 });
	backward.PushBack({ 310,  8, 30, 31 });
	backward.PushBack({ 342,  8, 30, 30 });
	backward.PushBack({ 374,  8, 30, 31 });//FALTA ACABAR LANIMACIO :(
	



	path.PushBack({ -0.5f, 0 }, 250, &backward);
	//path.PushBack({ -0.5f, 0.5f }, 200, &backward);




	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}


void DEMONWHEEL::Move()
{

	position = original_pos + path.GetCurrentPosition(&animation);


}