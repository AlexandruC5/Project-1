#include "Application.h"
#include "BALL.h"

#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include  "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"



BALL::BALL(int x, int y, int type) : Enemy(x, y, type)
{


	idle.PushBack({ 286, 149, 85, 104 });

	fly.PushBack({ 241, 473, 90, 115 });
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



	animation = &idle;
	ball_states state = IDLE_BALL;


	collider = App->collision->AddCollider({ 0, 0, 85, 105 }, COLLIDER_TYPE::COLLIDER_ENEMY_BALL, (Module*)App->enemies);

	//original_pos = { x,y };


}


void BALL::Move()
{

	
	if (App->inter->enemies_movement) {

		CheckState();
		PerformActions();


	}

}

void BALL::CheckState() {

  switch (state) {

	case IDLE_BALL:
		//position.x -= 2;
		if (position.x <= App->render->camera.x + (App->render->camera.w) - 180) {
			state = FLY_BALL;
		}
		break;

	case FLY_BALL:

		position.x += App->scene_temple->speed;

		//if (time_delay) {
		//	time_entry = SDL_GetTicks();
		//	time_delay = false;
		//}

		//time_current = SDL_GetTicks() - time_entry;

		//if (time_current > 500) {
		////	state = diagonal_ball;

		//}
		break;

//	case diagonal_ball:
//		position.x += 2;
//		position.y -= 2;
//
//		if (position.x < App->render->camera.x + App->render->camera.w - 90) {
//			state = open_ball;
//		}
//
//		break;
//
//	case open_ball:
//		position.x += App->scene_temple->speed;
//
//		if (open.Finished()) {
//			//Addparticle
//			if (time_delay2) {
//				time_entry2 = SDL_GetTicks();
//				time_delay2 = false;
//			}
//
//			time_current2 = SDL_GetTicks() - time_entry2;
//
//			if (time_current2 > 500) {
//				state = close_ball;
//			}
//		}
//		break;
//
//	case close_ball:
//		position.x += App->scene_temple->speed;
//
//		if (close.Finished()) {
//			//Addparticle
//			if (time_delay3) {
//				time_entry3 = SDL_GetTicks();
//				time_delay3 = false;
//			}
//
//			time_current3 = SDL_GetTicks() - time_entry3;
//
//			if (time_current3 > 500) {
//				state = move_ball;
//			}
//		}
//		break;
//
//	case move_ball:
//
//		if (movement) {
//
//			position.y += 2;
//
//			if (position.y >= 140) {
//				movement = false;
//				state = open_ball;
//			}
//		}
//		else if (!movement) {
//
//			position.y -= 2;
//			if (position.y <= 30) {
//				movement = true;
//				state = open_ball;
//			}
//		}
	}

}

void BALL::PerformActions() {

	switch (state) {

	case IDLE_BALL:
		animation = &fly;
		break;

	case FLY_BALL:
		animation = &idle;
		break;

	/*case diagonal_ball:
		animation = &fly;
		break;

	case open_ball:
		animation = &open;
		break;

	case close_ball:
		animation = &close;
		break;
		*/
	}

}

