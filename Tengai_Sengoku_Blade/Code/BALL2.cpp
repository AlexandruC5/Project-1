#include "Application.h"
#include "BALL2.h"

#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include  "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"



BALL2::BALL2(int x, int y, int type) : Enemy(x, y, type)
{


	idle.PushBack({ 286, 149, 85, 104 });

	open.PushBack({413, 143, 87, 110});
	open.PushBack({413, 257, 87, 124});
	open.PushBack({286, 257, 86, 124});
	open.speed = 0.15f;
	open.loop = false;


	close.PushBack({ 286, 257, 86, 124 });
	close.PushBack({ 413, 257, 87, 124 });
	close.PushBack({ 413, 143, 87, 110 });
	close.speed = 0.15f;
	close.loop = false;

	fire.PushBack({257, 600, 54, 20});
	fire.PushBack({337, 604, 46, 15});
	fire.PushBack({406, 606, 51, 16});
	fire.PushBack({480, 607, 50, 16});
	fire.speed = 0.15f;
	

	/*fly.PushBack({ 241, 473, 90, 115 });
	fly.PushBack({ 378, 473, 87, 109 });
	fly.PushBack({ 509, 473, 93, 114 });
	fly.PushBack({ 245, 660, 84, 113 });
	fly.speed = 0.25f;

	open.PushBack({ 35, 875, 87, 120 });
	open.PushBack({ 159, 875, 92, 117 });
	open.PushBack({ 295, 876, 93, 121 });
	open.PushBack({ 437, 875, 90, 121 });
	open.PushBack({ 34, 1011, 92, 137 });
	open.PushBack({ 153, 1011, 89, 132 });
	open.PushBack({ 287, 1011, 90, 135 });
	open.PushBack({ 426, 1009, 95, 137 });
	open.PushBack({ 631, 865, 88, 139 });
	open.PushBack({ 748, 865, 92, 131 });
	open.PushBack({ 630, 1017, 87, 135 });
	open.PushBack({ 744, 1017, 96, 138 });
	open.speed = 0.20f;
	open.loop = false;

	close.PushBack({ 744, 1017, 96, 138 });
	close.PushBack({ 630, 1017, 87, 135 });
	close.PushBack({ 748, 865, 92, 131 });
	close.PushBack({ 631, 865, 88, 139 });
	close.PushBack({ 426, 1009, 95, 137 });
	close.PushBack({ 287, 1011, 90, 135 });
	close.PushBack({ 153, 1011, 89, 132 });
	close.PushBack({ 34, 1011, 92, 137 });
	close.PushBack({ 437, 875, 90, 121 });
	close.PushBack({ 295, 876, 93, 121 });
	close.PushBack({ 159, 875, 92, 117 });
	close.PushBack({ 35, 875, 87, 120 });
	close.speed = 0.20f;
	close.loop = false;*/



	animation = &idle;
	ball_state state = IDLE_BALL2;


	collider = App->collision->AddCollider({ 0, 0, 85, 105 }, COLLIDER_TYPE::COLLIDER_ENEMY_BALL, (Module*)App->enemies);

	//original_pos = { x,y };


}


void BALL2::Move()
{


	if (App->inter->enemies_movement) {

		CheckState();
		PerformActions();


	}

}

void BALL2::CheckState() {

	switch (state) {

	case IDLE_BALL2:
		//position.x -= 2;
		if (position.x < App->render->camera.x + (App->render->camera.w) - 180) {
			state = FLY_BALL2;
		}
		break;

	case FLY_BALL2:

		position.x += App->scene_temple->speed;

		if (time_delay) {
			time_entry = SDL_GetTicks();
			time_delay = false;
		}

		time_current = SDL_GetTicks() - time_entry;

		if (time_current > 500) {
			state = DIAGONAL_BALL2;
		}
		break;

	case DIAGONAL_BALL2:
			position.x += 2;
			position.y -= 1;
	
				if (position.x > App->render->camera.x + App->render->camera.w - 90) {
					state = OPEN_BALL2;
				}
		
				break;
		
			case OPEN_BALL2:
				position.x += App->scene_temple->speed;
		
	             	if (open.Finished()) {
					//Addparticle
					if (time_delay2) {
						time_entry2 = SDL_GetTicks();
						time_delay2 = false;
					}
		
				time_current2 = SDL_GetTicks() - time_entry2;
		
					if (time_current2 > 1000) {
					state = CLOSE_BALL2;
					open.Reset();
					}
				}
				break;
		
			case CLOSE_BALL2:
				position.x += App->scene_temple->speed;
		
				if (close.Finished()) {
					//Addparticle
					if (time_delay3) {
						time_entry3 = SDL_GetTicks();
						time_delay3 = false;
					}
		
					time_current3 = SDL_GetTicks() - time_entry3;
		
					if (time_current3 > 1000) {
						state = MOVE_BALL2;
						close.Reset();
					}
				}
				break;
		
			case MOVE_BALL2:
				position.x += App->scene_temple->speed;

				if (movement) {
		
					position.y += 2;
		
					if (position.y >= 100) {
						movement = false;
						state = OPEN_BALL2;
				}
				}
				else if (!movement) {
		
					position.y -= 2;
					if (position.y <= 0) {
						movement = true;
						state = OPEN_BALL2;
			}
				}
	}

}

void BALL2::PerformActions() {

	switch (state) {

	case IDLE_BALL2:
		animation = &idle;
		break;

	case FLY_BALL2:
		animation = &idle;
		animation_ball = &fire;
		break;

		case DIAGONAL_BALL2:
		animation = &idle;
		animation_ball = &fire;
		break;

		case OPEN_BALL2:
		animation = &open;
		//animation_ball = &fire;
		spoty = 20;
		break;

		case CLOSE_BALL2:
		animation = &close;
		//animation_ball = &fire;
		spoty = 0;
		break;

		case MOVE_BALL2:
		animation = &idle;
		//animation_ball = &fire;
		break;
		
	}

}
