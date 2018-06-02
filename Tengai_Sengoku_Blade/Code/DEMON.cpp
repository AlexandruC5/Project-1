#include "Application.h"
#include "DEMON.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleKatana.h"
#include "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

DEMON::DEMON(int x, int y, int type) : Enemy(x, y, type)
{

	idle.PushBack({ 828, 1224, 164, 73 });
	idle.PushBack({ 999, 1224, 163, 75 });
	idle.speed = 0.15f;

	circular_shot.PushBack({ 830, 1298, 165, 71 });
	circular_shot.PushBack({ 999, 1299, 163, 70 });
	circular_shot.speed = 0.15f;

	down.PushBack({1177, 1237, 44, 49});
	down.PushBack({1175, 1311, 48, 47});
	down.speed = 0.15f;

	up.PushBack({1230, 1238, 60, 45});
	up.PushBack({1230, 1309, 59, 44});
	up.speed = 0.15f;

	wheel.PushBack({39, 1235, 99, 97});
	wheel.PushBack({46, 1364, 105, 102});
	wheel.PushBack({154, 1354, 114, 114});
	wheel.PushBack({269, 1345, 121, 119});
	wheel.PushBack({139, 1231, 118, 114});
	wheel.PushBack({257, 1230, 102, 109});
	wheel.speed = 0.2f;
	wheel.loop = true;


	

	

	animation = &idle;
	
	if (collider_active) {
		collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY_DEMON, (Module*)App->enemies);
	}
	original_pos = { x,y };


}


void DEMON::Move()
{
	if (App->inter->enemies_movement) {

		CheckState();
		PerformActions();


	}
}

void DEMON::CheckState() {

	switch (state)
	{
	case IDLE_DEMON:
		
		if (active) {
			position.y -= 1;
		}
		//position.x += int(App->scene_temple->speed);
		
		if (position.y < App->render->camera.y + (App->render->camera.h) - 170) {
			active = false;
			position.x += int(App->scene_temple->speed);
			if (time_delay) {
				time_entry = SDL_GetTicks();
				time_delay = false;
			}

			time_current = SDL_GetTicks() - time_entry;

			if (time_current > 800) {
				collider_active = true;
				state = FIRE_WHEELS;

			}
		}

		break;

	case FIRE_WHEELS:
		position.x += int(App->scene_temple->speed);
			//Shoot();

		if (time_delay2) {
			time_entry2 = SDL_GetTicks();
			time_delay2 = false;
		}

		time_current2 = SDL_GetTicks() - time_entry2;

		if (time_current2 > 600) {

			state = CIRCULAR_ATTACK;
		}
		break;

	case CIRCULAR_ATTACK:
			//Addemiter
			
			position.x += 1.5;
			position.y += 1;
		
			if (position.y > App->render->camera.y + (App->render->camera.h) - 50) {
				state = SHOT_FIRE_WHEELS;
			}
		
		break;

	case  SHOT_FIRE_WHEELS:

		//Lanzando fire wheels
		position.x -= 1;
		position.y -= 0.5;

		if (position.x < App->render->camera.x + (App->render->camera.w) - 70) {

			position.x += 1;
			position.y -= 1;
		}

		if (position.x > App->render->camera.x + (App->render->camera.w) - 15) {

			state = CIRCULAR_ATTACK_2;
		}
		break;

	case CIRCULAR_ATTACK_2:
		position.x += 1;
		position.y -= 1;

		if (position.y > App->render->camera.y + (App->render->camera.h) - 120) {

			//addremiter
			position.x -= 1;
			position.y -= 1;
		}

		if (position.y > App->render->camera.y + (App->render->camera.h) - 20) {
			state = SHOT_FIRE_WHEELS;
		}



	}

}

void DEMON::PerformActions()
{

	switch (state) {

	case IDLE_DEMON:
		animation = &idle;
		demon_down = &down;
		demon_up = &up;
		demon_wheel = &wheel;
		break;

	case FIRE_WHEELS:
		animation = &idle;
		demon_down = &down;
		demon_up = &up;
		demon_wheel = &wheel;
		break;

	case CIRCULAR_ATTACK:
		animation = &circular_shot;
		demon_down = &down;
		demon_up = &up;
		demon_wheel = &wheel;

		break;

	case SHOT_FIRE_WHEELS:
		animation = &idle;
		demon_down = &down;
		demon_up = &up;
		demon_wheel = &wheel;

		break;

	case CIRCULAR_ATTACK_2:
		animation = &circular_shot;
		demon_down = &down;
		demon_up = &up;
		demon_wheel = &wheel;

	}

}







