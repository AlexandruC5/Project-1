#include "Application.h"
#include "PAGODA.h"

#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include  "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleKatana.h"

PAGODA::PAGODA(int x, int y, int type) : Enemy(x, y, type)
{

	idle.PushBack({ 658, 12, 62, 80 });
	idle.PushBack({787, 12, 59, 80 });
	idle.PushBack({ 917, 12, 56, 80 });
	idle.PushBack({ 1043, 11, 60, 81 });
	idle.PushBack({ 1043, 11, 60, 81 });
	idle.PushBack({ 1170, 12, 63, 80 });
	idle.speed = 0.25f;

	head_shot.PushBack({658, 137, 62, 83});
	head_shot.PushBack({785, 136, 64, 84});
	head_shot.speed = 0.15f;
	head_shot.loop = false;


	open_toldo.PushBack({ 658, 137, 62, 83 });
	open_toldo.PushBack({ 914, 139, 62, 81 });
	open_toldo.PushBack({ 1041, 133, 63, 86 });
	open_toldo.PushBack({ 1169, 126, 64, 94 });
	open_toldo.PushBack({ 656, 253, 65, 95 });
	open_toldo.speed = 0.15f;

	close_toldo.PushBack({ 656, 253, 65, 95 });
	close_toldo.PushBack({ 1169, 126, 64, 94 });
	close_toldo.PushBack({ 1041, 133, 63, 86 });
	close_toldo.PushBack({ 914, 139, 62, 81 });
	close_toldo.PushBack({ 658, 137, 62, 83 });
	close_toldo.speed = 0.15f;
	close_toldo.loop = false;

	go_to_last_shot.PushBack({656, 253, 65, 95});
	go_to_last_shot.PushBack({ 785, 252, 63, 96 });
	go_to_last_shot.PushBack({ 913, 253, 63, 95 });
	go_to_last_shot.PushBack({ 1042, 252, 62, 96 });
	go_to_last_shot.PushBack({ 1169, 252, 64, 96 });
	go_to_last_shot.PushBack({ 657, 381, 64, 95 });
	go_to_last_shot.PushBack({ 786, 381, 62, 95 });
	go_to_last_shot.PushBack({ 914, 381, 63, 95 });
	go_to_last_shot.PushBack({ 1042, 380, 62, 96 });
	go_to_last_shot.PushBack({1169, 381, 64, 95 });
	go_to_last_shot.speed = 0.15f;



	go_to_first_shot.PushBack({ 1169, 381, 64, 95 });
	go_to_first_shot.PushBack({ 1042, 380, 62, 96 });
	go_to_first_shot.PushBack({ 914, 381, 63, 95 });
	go_to_first_shot.PushBack({ 786, 381, 62, 95 });
	go_to_first_shot.PushBack({ 657, 381, 64, 95 });
	go_to_first_shot.PushBack({ 1169, 252, 64, 96 });
	go_to_first_shot.PushBack({ 1042, 252, 62, 96 });
	go_to_first_shot.PushBack({ 913, 253, 63, 95 });
	go_to_first_shot.PushBack({ 785, 252, 63, 96 });
	go_to_first_shot.PushBack({ 656, 253, 65, 95 });
	go_to_first_shot.speed = 0.15f;
	

	animation = &idle;
	

	collider = App->collision->AddCollider({ 0, 0, 65, 80 }, COLLIDER_TYPE::COLLIDER_ENEMY_PAGODA, (Module*)App->enemies);

	original_pos = { x,y };



}


void PAGODA::Move()
{

	if (App->inter->enemies_movement) {

		CheckState();
		PerformActions();
	}
}



void PAGODA::CheckState() {

	switch (state)
	{
	case PAGODA_IDLE:
		//position.x -= 1.5;

		if (position.x < App->render->camera.x + App->render->camera.w - 100) {
			
			position.x += int(App->scene_temple->speed);


			if (time_delay) {
				time_entry = SDL_GetTicks();
				time_delay = false;
			}

			time_current = SDL_GetTicks() - time_entry;

			if (time_current > 800) {
				state = PAGODA_SHOT_HEAD;
			}
		}
		break;

	case PAGODA_SHOT_HEAD:
	
		position.x += int(App->scene_temple->speed);

		if (head_shot.Finished()) {
			close_toldo.Reset();
			
			

			if (time_delay2) {
				time_entry2 = SDL_GetTicks();
				time_delay2 = false;
			}

			time_current2 = SDL_GetTicks() - time_entry2;

			if (time_current2 > 800) {
				Shoot();
				state = PAGODA_OPEN_TOLDO;

			}

}

		break;

	case PAGODA_OPEN_TOLDO:
		
		position.x += int(App->scene_temple->speed);

		if (open_toldo.Finished()) {
			open_toldo.Reset();
			Shoot();
			state = PAGODA_LAST_SHOT;
		}
		break;


	case PAGODA_LAST_SHOT:

		position.x += int(App->scene_temple->speed);

		if (go_to_last_shot.Finished()) {
			go_to_last_shot.Reset();
			Shoot();
			state = PAGODA_FIRST_SHOT;
		}
		break;

	case PAGODA_FIRST_SHOT:
	
		position.x += int(App->scene_temple->speed);

		if (go_to_first_shot.Finished()) {
			go_to_first_shot.Reset();
			state = PAGODA_CLOSE_TOLDO;
		}
		break;

	case PAGODA_CLOSE_TOLDO:
	
		position.x += int(App->scene_temple->speed);

		if (close_toldo.Finished()) {
			

			if (time_delay3) {
				time_entry3 = SDL_GetTicks();
				time_delay3 = false;
			}

			time_current3 = SDL_GetTicks() - time_entry3;

			if (time_current3 > 800) {
				if (timer >= 3) {
					state = PAGODA_FAREWELL;
				}
				else {
					state = PAGODA_SHOT_HEAD;
					timer++;
				}
			}
		}
		break;

	case PAGODA_FAREWELL:
		position.x += 2;
		position.y -= 1.5;
		break;
	}

}

void PAGODA::PerformActions() {
	switch (state)
	{
	case PAGODA_IDLE:
		animation = &idle;
		
		break;

	case PAGODA_SHOT_HEAD:
		animation = &head_shot;
		
		break;

	case PAGODA_OPEN_TOLDO:
		animation = &open_toldo;
	
		break;

	case PAGODA_LAST_SHOT:
		animation = &go_to_last_shot;
		break;

	case PAGODA_FIRST_SHOT:
		animation = &go_to_first_shot;
		break;

	case PAGODA_CLOSE_TOLDO:
		animation = &close_toldo;
		break;

	case PAGODA_FAREWELL:
		animation = &close_toldo;
		break;
	}

}


void PAGODA::Shoot() {

	for (int i = 0; i < ammo; i++) {

		Particle* p = new Particle(App->particles->enemy_bullet);
		p->born = SDL_GetTicks();
		p->position.x = int(position.x) + i * 6;
		p->position.y = int(position.y) + i * 3;
		p->speed.x = (App->katana->position.x - p->position.x) / 60.f;
		p->speed.y = (App->katana->position.y - p->position.y) / 60.f;
		p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_ENEMY_SHOT, App->particles);
		App->particles->AddParticle(p);

	}


}