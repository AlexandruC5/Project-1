#include "Application.h"
#include "Coin.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleInterface.h"

COIN::COIN(int x, int y, int type) :Enemy(x, y, type)
{
	up.PushBack({ 44, 1787, 14, 16 });
	up.PushBack({ 64, 1787, 14, 16 });
	up.PushBack({ 84, 1787, 12, 16 });
	up.PushBack({ 102, 1787, 12, 16 });
	up.PushBack({ 121, 1787, 8, 16 });
	up.PushBack({ 137, 1787, 8, 16 });
	up.PushBack({ 156, 1787, 4, 16 });
	up.PushBack({ 172, 1787, 4, 16 });
	up.PushBack({ 188, 1787, 8, 16 });
	up.PushBack({ 206, 1787, 8, 16 });
	up.PushBack({ 225, 1787, 12, 16 });
	up.PushBack({ 243, 1787, 12, 16 });
	up.PushBack({ 260, 1787, 14, 16});
	up.PushBack({ 279, 1787, 14, 16 });
	up.PushBack({ 298, 1787, 16, 16 });
	up.PushBack({ 319, 1787, 16, 16 });

	parabola.PushBack({ 44, 1787, 14, 16 });
	parabola.PushBack({ 64, 1787, 14, 16 });
	parabola.PushBack({ 84, 1787, 12, 16 });
	parabola.PushBack({ 102, 1787, 12, 16 });
	parabola.PushBack({ 121, 1787, 8, 16 });
	parabola.PushBack({ 137, 1787, 8, 16 });
	parabola.PushBack({ 156, 1787, 4, 16 });
	parabola.PushBack({ 172, 1787, 4, 16 });
	parabola.PushBack({ 188, 1787, 8, 16 });
	parabola.PushBack({ 206, 1787, 8, 16 });
	parabola.PushBack({ 225, 1787, 12, 16 });
	parabola.PushBack({ 243, 1787, 12, 16 });
	parabola.PushBack({ 260, 1787, 14, 16 });
	parabola.PushBack({ 279, 1787, 14, 16 });
	parabola.PushBack({ 298, 1787, 16, 16 });
	parabola.PushBack({ 319, 1787, 16, 16 });


	down.PushBack({ 44, 1787, 14, 16 });
	down.PushBack({ 64, 1787, 14, 16 });
	down.PushBack({ 84, 1787, 12, 16 });
	down.PushBack({ 102, 1787, 12, 16 });
	down.PushBack({ 121, 1787, 8, 16 });
	down.PushBack({ 137, 1787, 8, 16 });
	down.PushBack({ 156, 1787, 4, 16 });
	down.PushBack({ 172, 1787, 4, 16 });
	down.PushBack({ 188, 1787, 8, 16 });
	down.PushBack({ 206, 1787, 8, 16 });
	down.PushBack({ 225, 1787, 12, 16 });
	down.PushBack({ 243, 1787, 12, 16 });
	down.PushBack({ 260, 1787, 14, 16 });
	down.PushBack({ 279, 1787, 14, 16 });
	down.PushBack({ 298, 1787, 16, 16 });
	down.PushBack({ 319, 1787, 16, 16 });

	
	up.speed = 0.15f;
	parabola.speed = 0.15f;
	down.speed = 0.15f;

	
	if (type == 1) {
		movement.PushBack({ 1.f, -0.5f }, 50, &up);
		
		movement.PushBack({ 1.f, 0.5f }, 1008, &down);
	}

	if (type == 2) {
		movement.PushBack({ -1.5f, -0 }, 50, &up);
		movement.PushBack({ 1.f, -0.5f }, 70, &up);
		movement.PushBack({ 1.f, 0.5f }, 1008, &down);
	}
	animation = &up;

	collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_COIN, (Module*)App->enemies);

	originalposition.y = y;
	originalposition.x = x;
}

void COIN::Move()
{
	if (App->inter->enemies_movement) {
		
		iPoint path_pos = movement.GetCurrentPosition(&animation);
		position.x = float(originalposition.x + path_pos.x);
		position.y = float(originalposition.y + path_pos.y);

	}

}