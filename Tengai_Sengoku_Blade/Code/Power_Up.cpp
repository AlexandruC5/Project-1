#include "Application.h"
#include "Power_Up.h"
#include "ModuleEnemies.h"
#include "ModuleInterface.h"
#include "ModuleCollision.h"
#include "ModuleSceneTemple.h"


Power_Up::Power_Up(int x, int y) :Enemy(x, y)
{
	iddle.PushBack({34, 425, 32, 22 });
	iddle.PushBack({ 66, 425, 31, 22 });
	iddle.PushBack({97, 425, 31, 21 });
	iddle.PushBack({ 128, 425, 31, 20 });
	iddle.PushBack({ 159, 425, 31, 20 });

	iddle.PushBack({ 34, 447, 32, 20 });
	iddle.PushBack({66, 447, 31, 20 });
	iddle.PushBack({ 97, 447, 31, 20 });
	iddle.PushBack({128, 447, 31, 20 });
	iddle.PushBack({ 159, 447, 31, 20 });

	iddle.PushBack({ 34, 467, 32, 21 });
	iddle.PushBack({ 66, 467, 31, 21 });
	iddle.PushBack({97, 467, 31, 21 });
	iddle.PushBack({ 128, 467, 31, 21 });
	iddle.PushBack({159, 467, 31, 20 });

	iddle.PushBack({ 35, 488, 31, 21 });

	iddle.speed = 0.20f;

	movement.PushBack({ -0.1f, 0.0f }, 80, &iddle);
	//movement.PushBack({ 1.0f, 0.0f }, 160, &iddle);

	animation = &iddle;
	collider = App->collision->AddCollider({ 0, 0, 24, 20 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void Power_Up::Move()
{
	if (App->inter->enemies_movement) {
		position = originalposition + movement.GetCurrentPosition();
	}
}