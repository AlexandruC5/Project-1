#include "Application.h"
#include "SHARPENER_KNIFE.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleInterface.h"
#include "SDL\include\SDL_timer.h"


SHARPENER_KNIFE::SHARPENER_KNIFE(int x, int y) : Enemy(x, y)
{

	//IDLE
	idle.PushBack({ 1092, 534, 87, 72 });
	idle.PushBack({ 1016, 534, 76, 72 });
	idle.PushBack({ 931, 534, 85, 73 });
	idle.PushBack({ 851, 534, 80, 73 });
	idle.PushBack({ 767, 534, 83, 73 });
	idle.PushBack({ 685, 534, 81, 72 });
	idle.speed = 0.15f;

	//GO SHOOT
	shoot.PushBack({ 891, 610, 96, 71 });
	shoot.PushBack({ 793, 610, 98, 74 });
	shoot.PushBack({ 691, 610, 101, 71 });
	shoot.speed = 0.15f;
	//RETURN SHOOT
	return_shoot.PushBack({ 691, 610, 101, 71 });
	return_shoot.PushBack({ 793, 610, 98, 74 });
	return_shoot.PushBack({ 891, 610, 96, 71 });
	return_shoot.speed = 0.15f;
	//START SPIN
	spin.PushBack({ 1122, 705, 44, 85 });
	spin.PushBack({ 996, 610, 48, 87 });
	spin.PushBack({ 1047, 610, 76, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 688, 701, 106, 87 });
	spin.PushBack({ 798, 700, 107, 88 });
	spin.PushBack({ 1009, 702, 106, 89 });
	spin.PushBack({ 911, 700, 93, 88 });
	spin.PushBack({ 1047, 610, 76, 88 });
	spin.PushBack({ 996, 610, 48, 87 });
	spin.PushBack({ 1122, 705, 44, 85 });
	spin.speed = 0.30f;
	spin.loop = false;

	/*path.PushBack({ -0.2f, 0 }, 250, &idle);*/

	animation = &spin;
	//sharpener_state state = SPAWN_SHARPENER;

	collider = App->collision->AddCollider({ 0, 0, 80, 70 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHARPENER_KNIFE, (Module*)App->enemies);

	original_pos_x = x;
	original_pos_y = y;


}


void SHARPENER_KNIFE::Move()
{
	if (App->inter->enemies_movement) {


		 CheckState();
		 PerformActions();




		//position.x -= 1;
		/*if (spin.Finished()) {
			animation = &idle;
		}

		else if (animation == &idle) {
			position.x += 1;
		}*/


		/*position = original_pos + path.GetCurrentPosition(&animation);*/

		/*void CheckState();

		void PerformActions();
*/

		//shootTimer++;

		//if (shootTimer == 100) {
		//	if (App->katana->position.x < position.x && App->katana->position.y < position.y)
		//	{
		//		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT);
		//	}
		//	else if (App->katana->position.x < position.x && App->katana->position.y > position.y) {
		//		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT);
		//	}
		//	else if (App->katana->position.x > position.x && App->katana->position.y < position.y) {
		//		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT);
		//	}
		//	else if (App->katana->position.x > position.x && App->katana->position.y > position.y) {
		//		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y + 10, COLLIDER_ENEMY_SHOT);
		//	}
		//	//shootTimer = 0;
		//}


	}
}



void SHARPENER_KNIFE::CheckState() {
	
	switch (state)
	{
	case SPAWN_SHARPENER:
		if (spin.Finished()) {
			state = GO_BACKWARD_SHARPENER;
		}
		break;

	case GO_BACKWARD_SHARPENER:
		position.x += 2 /*original_pos_x += 1*/;
		if(position.x >= App->render->camera.x + (App->render->camera.w) - 80){
			state = SHOOT_SHARPENER;
		}
		break;

	case SHOOT_SHARPENER:
		
		if (shoot.Finished()) {
			App->particles->AddParticle(App->particles->sharpener_bullet, position.x , position.y - 30, COLLIDER_ENEMY_SHOT);
			state = RETURN_SHOOT_SHARPENER;
		}
		break;

	case RETURN_SHOOT_SHARPENER:
		
		if (return_shoot.Finished()) {
			state = GO_SPIN_SHARPENER;
		}
		break;
	case GO_SPIN_SHARPENER:

	if (going_forward) {
		if (spot < -20) {
				going_forward = false;
			}
			else {
				position.x = original_pos_x + (spot--);
			}
		}

		else {

			if (spot >= 0) {
				state = IDLE_SHARPENER;
			}
			else position.x = original_pos_x + (spot++);
		}


		break;

	case IDLE_SHARPENER:

		if (time_delay)
		{
			time_entry = SDL_GetTicks();
			time_delay = false;
		}
		time_current = SDL_GetTicks() - time_entry;
		if (time_current > 400) {
		state = FULL_SHOOT_SHARPENER;
			time_delay = true;
		}

		break;

	case FULL_SHOOT_SHARPENER:
		if (shoot.Finished()) {
			App->particles->AddParticle(App->particles->sharpener_bullet, position.x, position.y - 30, COLLIDER_ENEMY_SHOT);
			state = FAREWELL_SHARPENER;
		}
		
		break;

	case FAREWELL_SHARPENER:
		position.x -= 1;
		break;

	}


}

void SHARPENER_KNIFE::PerformActions()
{
	
	switch (state) {

	case SPAWN_SHARPENER:
		animation = &spin;
		break;

	case GO_BACKWARD_SHARPENER:
		animation = &idle;
		break;

	case SHOOT_SHARPENER:
		animation = &shoot;

		break;

	case RETURN_SHOOT_SHARPENER:
		animation = &return_shoot;

		break;

	case GO_SPIN_SHARPENER:
		animation = &spin;

		break;

	case IDLE_SHARPENER: 
		animation = &idle;

	break;

	case FULL_SHOOT_SHARPENER:
		animation = &shoot;

		break;

	case FAREWELL_SHARPENER:
		animation = &idle;
		break;
	}

}