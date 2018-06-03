#include "Application.h"
#include "DEMONWHEEL.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleInterface.h"
#include "ModuleKatana.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleRender.h"

DEMONWHEEL::DEMONWHEEL(int x, int y, int type) : Enemy(x, y,type)
{


	backward.PushBack({ 278,  8, 30, 31 });
	backward.PushBack({ 310,  8, 30, 31 });
	backward.PushBack({ 342,  8, 30, 30 });
	backward.PushBack({ 374,  8, 30, 31 });

	backward.PushBack({ 277, 40, 32, 32 });
	backward.PushBack({ 309, 40, 32, 32 });
	backward.PushBack({ 341, 40, 32, 32 });
	backward.PushBack({ 373, 40, 32, 32 });

	backward.PushBack({ 277, 73, 32, 30 });
	backward.PushBack({ 309, 72, 32, 32 });
	backward.PushBack({ 341, 72, 32, 32 });
	backward.PushBack({ 373, 72, 32, 32 });
	
	

	if (type == 1) {
		path.PushBack({ -1.f, 0 }, 85, &backward);
		path.PushBack({ 2.5, 0 }, 500, &backward);
		path.PushBack({ 1.5, 2.5 }, 200, &backward);
		path.PushBack({ -1.5, 0 }, 200, &backward);
	}

	if (type == 2) {
		path.PushBack({ -1.5f, 0 }, 70, &backward);
		path.PushBack({ 0.75f, 1.5 }, 70, &backward);
		path.PushBack({ 2.5f, 0 }, 500, &backward);
	}

	if (type == 3) {
		path.PushBack({ -1.5, 0 }, 100, &backward);
		path.PushBack({ 0.75, 1.5 }, 80, &backward);
		path.PushBack({ 2.5, 0 }, 500, &backward);
	}

	if (type == 4) {
		path.PushBack({ -1.5, 0 }, 130, &backward);
		path.PushBack({ 0.75, 1.5 }, 90, &backward);
		path.PushBack({ 2.5, 0 }, 500, &backward);
	}

	
	//path.PushBack({ -0.5f, 0.5f }, 200, &backward);

	


	backward.speed = 0.1f;

	animation = &backward;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY_DEMONWHEEL, (Module*)App->enemies);

	original_pos = { x,y };


}


void DEMONWHEEL::Move()
{
	

	if (App->inter->enemies_movement) {

		iPoint path_pos = path.GetCurrentPosition(&animation);
		position.x = float(original_pos.x + path_pos.x);
		position.y = float(original_pos.y + path_pos.y);

		if (position.x < App->render->camera.x + App->render->camera.w) {

			if (timer > 50) {
				Shoot();
				timer = 0;

			}
			else timer++;
		}
	}

}


void DEMONWHEEL::Shoot() {

	Particle* p = new Particle(App->particles->enemy_bullet);
	p->born = SDL_GetTicks();
	p->position.x = int(position.x) + 10;
	p->position.y = int(position.y);
	p->speed.x = (App->katana->position.x - position.x) / 60.f;
	p->speed.y = (App->katana->position.y - position.y) / 60.f;
	p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_ENEMY_SHOT, App->particles);
	App->particles->AddParticle(p);


}