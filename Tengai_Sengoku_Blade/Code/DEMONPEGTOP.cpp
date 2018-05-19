#include "Application.h"
#include "DEMONPEGTOP.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"



DEMONPEGTOP::DEMONPEGTOP(int x, int y) : Enemy(x, y)
{


	backward.PushBack({ 30,  160, 42, 48 });
	backward.PushBack({ 74,  160, 42, 48 });
	backward.PushBack({ 119,  160, 42, 48 });
	backward.PushBack({ 163,  160, 42, 48 });
	backward.PushBack({ 30,  215, 42, 48 });
	backward.PushBack({ 74,  215, 42, 48 });
	backward.PushBack({ 119,  215, 42, 48 });
	backward.PushBack({ 163,  215, 42, 48 });

	death.PushBack({ 30,  271, 42, 48 });
	death.PushBack({ 75,  271, 42, 48 });
	death.PushBack({ 118,  271, 43, 48 });
	death.PushBack({ 163,  271, 42, 48 });
	death.PushBack({ 29,  332, 42, 48 });
	death.PushBack({ 74,  332, 42, 49 });
	death.PushBack({ 119,  332, 42, 48 });
	death.PushBack({ 163,  332, 42, 49 });
	



	path.PushBack({ -0.5f, 0 }, 250, &backward);
	//path.PushBack({ -0.5f, 0.5f }, 200, &backward);




	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 48, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP, (Module*)App->enemies);

	original_pos = { x,y };


}


void DEMONPEGTOP::Move()
{

	position = original_pos + path.GetCurrentPosition(&animation);


}