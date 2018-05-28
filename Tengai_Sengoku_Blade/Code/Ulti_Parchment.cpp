#include "Application.h"
#include "Ulti_Parchment.h"
#include "ModuleEnemies.h"
#include "ModuleInterface.h"
#include "ModuleCollision.h"
#include "ModuleSceneTemple.h"


Ulti_Parchment::Ulti_Parchment(int x, int y, int type) :Enemy(x, y, type)
{
	iddle.PushBack({ 26, 812, 32, 22 });
	iddle.PushBack({ 65, 812, 32, 20 });
	iddle.PushBack({104, 813, 32, 21 });
	iddle.PushBack({ 144, 812, 32, 21 });
	iddle.PushBack({185, 814, 32, 22 });

	iddle.PushBack({ 223, 813, 32, 22 });
	iddle.PushBack({ 268, 813, 32, 21 });
	iddle.PushBack({ 309, 813, 32, 21 });
	iddle.PushBack({ 352, 813, 31, 20 });
	iddle.PushBack({ 391, 812, 32, 20 });

	iddle.PushBack({ 434, 813, 32, 20 });
	iddle.PushBack({ 475, 813, 31, 20 });

	iddle.speed = 0.20f;

	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	//movement.PushBack({ 1.0f, 0.0f }, 160, &iddle);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 24, 20 }, COLLIDER_TYPE::COLLIDER_ULTI_PARCHMENT, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Ulti_Parchment::Move()
{
	if (App->inter->enemies_movement) {
		position = originalposition + movement.GetCurrentPosition();
	}
}