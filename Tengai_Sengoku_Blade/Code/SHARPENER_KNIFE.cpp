#include "Application.h"
#include "SHARPENER_KNIFE.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleSceneTemple.h"
#include "ModuleInterface.h"
#include "SDL\include\SDL_timer.h"


SHARPENER_KNIFE::SHARPENER_KNIFE(int x, int y, int type) : Enemy(x, y, type)
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
	shoot.speed = 0.1f;
	//RETURN SHOOT
	return_shoot.PushBack({ 691, 610, 101, 71 });
	return_shoot.PushBack({ 793, 610, 98, 74 });
	return_shoot.PushBack({ 891, 610, 96, 71 });
	return_shoot.speed = 0.1f;
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

	spin.speed = 0.2f;
	spin.loop = false;


	//SPIN FORWARD
	spin_forward.PushBack({ 1122, 705, 44, 85 });
	spin_forward.PushBack({ 996, 610, 48, 87 });
	spin_forward.PushBack({ 1047, 610, 76, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.PushBack({ 688, 701, 106, 87 });
	spin_forward.PushBack({ 798, 700, 107, 88 });
	spin_forward.PushBack({ 1009, 702, 106, 89 });
	spin_forward.PushBack({ 911, 700, 93, 88 });
	spin_forward.speed = 0.3f;
	//SPIN BACKWARD
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 688, 701, 106, 87 });
	spin_backward.PushBack({ 798, 700, 107, 88 });
	spin_backward.PushBack({ 1009, 702, 106, 89 });
	spin_backward.PushBack({ 911, 700, 93, 88 });
	spin_backward.PushBack({ 1047, 610, 76, 88 });
	spin_backward.PushBack({ 996, 610, 48, 87 });
	spin_backward.PushBack({ 1122, 705, 44, 85 });
	spin_backward.speed = 0.3f;
	
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
		position.x += App->scene_temple->speed;
		if (spin.Finished()) {
			spin.Reset();
			state = GO_BACKWARD_SHARPENER;
		}
		break;

	case GO_BACKWARD_SHARPENER:
		position.x += 2;
		if(position.x >= App->render->camera.x + (App->render->camera.w) - 101){
			state = SHOOT_SHARPENER;
		}
		break;

	case SHOOT_SHARPENER:
		position.x += App->scene_temple->speed;
		if (shoot.Finished()) {
			shoot.Reset();
			//App->particles->AddParticle(App->particles->sharpener_bullet, position.x , position.y - 30, COLLIDER_ENEMY_SHOT);
			state = RETURN_SHOOT_SHARPENER;
		}
		break;

	case RETURN_SHOOT_SHARPENER:

		position.x += App->scene_temple->speed;
		if (return_shoot.Finished()) {
			return_shoot.Reset();
			state = IDLE_FORWARD;
		}
		break;

	case IDLE_FORWARD:

		if (position.x < App->render->camera.x + (App->render->camera.w) - 200) {
			position.x += App->scene_temple->speed;
			state = GO_SPIN_SHARPENER;
		}
		break;

	case GO_SPIN_SHARPENER:

		for (int i = 0; i <= 15; i++) {

			//App->particles->AddParticle(App->particles->sharpener_shuriken, position.x, position.y - 30, lista_shurikens[i]->speed.x, lista_shurikens[i].speed.y, COLLIDER_ENEMY_SHOT);
		}
	if (going_forward) {
		if (position.x < App->render->camera.x +(App->render->camera.w)-200) {
				going_forward = false;
			}
			else {
				//position.x -= 1;
			}
		}

		else {

			if (position.x >= App->render->camera.x + (App->render->camera.w) - 101) {
				state = IDLE_SHARPENER;
			}
			
			else {
				position.x += 2;
			}
				
		}


		break;

	case IDLE_SHARPENER:

		position.x += App->scene_temple->speed;

		if (time_delay) {
			time_entry = SDL_GetTicks();
			time_delay = false;
		}
		
		time_current = SDL_GetTicks() - time_entry;

		if (time_current > 1500) {
			if (active_shoot) {
				state = FAREWELL_SHARPENER;
				time_entry = SDL_GetTicks();
			}
			else {
				state = FULL_SHOOT_SHARPENER;
				time_entry = SDL_GetTicks();
			}

		}

		break;

	case FULL_SHOOT_SHARPENER:
		position.x += App->scene_temple->speed;
		active_shoot = true;
		if (shoot.Finished()) {
			shoot.Reset();
			//App->particles->AddParticle(App->particles->sharpener_bullet, position.x, position.y - 30, COLLIDER_ENEMY_SHOT);
			state = IDLE_SHARPENER;
		}
		
		break;

	case FAREWELL_SHARPENER:
		position.x += 2;
		position.y -= 2;
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

	case IDLE_FORWARD:
		animation = &idle;

		break;

	case GO_SPIN_SHARPENER:
		animation = &spin;

		if (spin.Finished()) {

			//spin.Reset();
			animation = &idle;
		}


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