#include "Application.h"
#include "DEMONPEGTOP.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleKatana.h"
#include "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

DEMONPEGTOP::DEMONPEGTOP(int x, int y, int type) : Enemy(x, y, type)
{


	idle.PushBack({ 30,  160, 42, 48 });
	idle.PushBack({ 74,  160, 42, 48 });
	idle.PushBack({ 119,  160, 42, 48 });
	idle.PushBack({ 163,  160, 42, 48 });
	idle.speed = 0.15f;

	shot.PushBack({ 30,  215, 42, 48 });
	shot.PushBack({ 74,  215, 42, 48 });
	shot.PushBack({ 119,  215, 42, 48 });
	shot.PushBack({ 163,  215, 42, 48 });
	shot.speed = 0.10f;

	return_shot.PushBack({ 163,  215, 42, 48 });
	return_shot.PushBack({ 119,  215, 42, 48 });
	return_shot.PushBack({ 74,  215, 42, 48 });
	return_shot.PushBack({ 30,  215, 42, 48 });
	return_shot.speed = 0.10f;

	death.PushBack({ 30,  271, 42, 48 });
	death.PushBack({ 75,  271, 42, 48 });
	death.PushBack({ 118,  271, 43, 48 });
	death.PushBack({ 163,  271, 42, 48 });

	death.PushBack({ 29,  332, 42, 48 });
	death.PushBack({ 74,  332, 42, 49 });
	death.PushBack({ 119,  332, 42, 48 });
	death.PushBack({ 163,  332, 42, 49 });
	



	/*path.PushBack({ -0.2f, 0 }, 75, &idle);
	path.PushBack({ 0, 0 }, 250, &shot);
	path.PushBack({ 0, 0 }, 250, &return_shot);
	path.PushBack({ 0.2f, -0.3f }, 500, &idle);*/

	this->type = type;

	//path.PushBack({ -0.5f, 0.5f }, 200, &backward);

	animation = &idle;
	//state_pegtop state = IDLE_PEGTOP;

	collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP, (Module*)App->enemies);

	original_pos = { x,y };


}


void DEMONPEGTOP::Move()
{
	if (App->inter->enemies_movement) {
		
		CheckState();
		PerformActions();
		

	}
}

void DEMONPEGTOP::CheckState() {

	switch (state)
	{
	case IDLE_PEGTOP:
		position.x -= 0.2;
		if(type == 1){
			if (position.x <= App->render->camera.x + (App->render->camera.w) - 170) 
				state = SHOT_PEGTOP;
			}
		if (type == 2) {
			if (position.x <= App->render->camera.x + (App->render->camera.w) - 80) 
				state = SHOT_PEGTOP;
			}
		if (type == 3) {
			if (position.x <= App->render->camera.x + (App->render->camera.w) - 125)
				state = SHOT_PEGTOP;
		}
		
		break;

	case SHOT_PEGTOP:
		position.x += int(App->scene_temple->speed);
		if (shot.Finished()) {
			Shoot();
			state = RETURN_SHOT_PEGTOP;
		}
		break;

	case RETURN_SHOT_PEGTOP:
		position.x += int(App->scene_temple->speed);
		if (return_shot.Finished()) {

			/*if (ammo < 5){
				state = SHOT_PEGTOP;
			}*/
			 state = FAREWELL_PEGTOP;
			//shoot.Reset();
			//App->particles->AddParticle(App->particles->sharpener_bullet, position.x , position.y - 30, COLLIDER_ENEMY_SHOT);
			
		}
		break;

	case FAREWELL_PEGTOP:

		position.x += int(App->scene_temple->speed);
		
		if (time_delay) {
			time_entry = SDL_GetTicks();
			time_delay = false;
		}

		time_current = SDL_GetTicks() - time_entry;

		if (time_current > 600) {
			  // position.x += App->scene_temple->speed;
			   position.y -= 1;

			   if (position.y < App->render->camera.y - 50) {
				   state = DESPAWNING_PEGTOP;
			   }
			
			}
		break;

	case DESPAWNING_PEGTOP:
     
		break;

	}

}

void DEMONPEGTOP::PerformActions()
{

	switch (state) {

	case IDLE_PEGTOP:
		animation = &idle;
		break;

	case SHOT_PEGTOP:
		animation = &shot;
		break;

	case RETURN_SHOT_PEGTOP:
		animation = &return_shot;

		break;

	case FAREWELL_PEGTOP:
		animation = &idle;

		break;

	case DESPAWNING_PEGTOP:
		animation = &idle;

		break;
	}

}




	void DEMONPEGTOP::Shoot() 
	
	{

		Particle* p = new Particle(App->particles->enemy_bullet);
		p->born = SDL_GetTicks();
		p->position.x = int(position.x) - 5;
		p->position.y = int(position.y);
		p->speed.x = (App->katana->position.x - position.x) / 60.f;
		p->speed.y = (App->katana->position.y - position.y) / 60.f;
		p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_ENEMY_SHOT, App->particles);
		App->particles->AddParticle(p);


		/*for (int i = 0; i < ammo; i++) {

			Particle* p = new Particle(App->particles->enemy_bullet);
			p->born = SDL_GetTicks();
			p->position.x = int(position.x) - i * 5;
			p->position.y = int(position.y) + i * 5;
			p->speed.x = (App->katana->position.x - p->position.x) / 60.f;
			p->speed.y = (App->katana->position.y - p->position.y) / 60.f;
			p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_ENEMY_SHOT, App->particles);
			App->particles->AddParticle(p);

		}
		ammo++;*/




	}