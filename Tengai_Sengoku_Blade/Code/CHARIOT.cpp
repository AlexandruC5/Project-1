#include "Application.h"
#include "CHARIOT.h"
#include "BALL.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include  "ModuleInterface.h"
#include "ModuleSceneTemple.h"
#include "SDL\include\SDL_timer.h"


CHARIOT::CHARIOT(int x, int y, int type) : Enemy(x, y, type)
{

	idle.PushBack({ 1321, 183, 217, 166 });

	/*idle.PushBack({ 2086, 30, 224, 202 });
	idle.PushBack({ 2362, 28, 242, 211 });
	idle.PushBack({ 2638, 41, 220, 193 });
	idle.PushBack({ 2079, 257, 217, 191 });
	idle.PushBack({ 2350, 250, 220, 200 });
	idle.PushBack({ 2631, 249, 218, 203 });
	idle.speed = 0.2f;*/
	wheel.PushBack({ 1589, 491, 114, 114 });
	wheel.PushBack({ 1723,497,102,102 });
	wheel.PushBack({ 1854, 500, 96, 96 });
	wheel.PushBack({ 1595, 625, 102, 102 });
	wheel.PushBack({ 1717, 619, 114, 114 });
	wheel.PushBack({ 1844, 617, 117, 118 });
	wheel.loop = true;
	wheel.speed = 0.20f;

	chariot_wheels.PushBack({ 1599, 348, 48, 48 });
	chariot_wheels.PushBack({ 1663, 348, 48, 48 });
	chariot_wheels.PushBack({ 1727, 348, 48, 48 });
	chariot_wheels.PushBack({ 1599, 412, 48, 48 });
	chariot_wheels.PushBack({ 1663, 412, 48, 48 });
	chariot_wheels.PushBack({ 1727, 412, 48, 48 });
	chariot_wheels.speed = 0.20f;


	chariot_wheels2.PushBack({ 1800, 349, 48, 48 });
	chariot_wheels2.PushBack({ 1864, 349, 48, 48 });
	chariot_wheels2.PushBack({ 1928, 349, 48, 48 });
	chariot_wheels2.PushBack({ 1800, 413, 48, 48 });
	chariot_wheels2.PushBack({ 1864, 413, 48, 48 });
	chariot_wheels2.PushBack({ 1928, 413, 48, 48 });
	chariot_wheels2.speed = 0.20f;

	furni.PushBack({ 2498, 799, 214, 156 });

	robot.PushBack({ 2128, 537, 95, 95 });
	robot.PushBack({ 2127, 634, 96, 94 });
	robot.PushBack({ 2223, 537, 96, 95 });
	robot.speed = 0.05f;

	wolf.PushBack({ 2146, 790, 36, 41 });
	wolf.PushBack({ 2271, 789, 35, 42 });
	wolf.PushBack({ 2147, 852, 38, 43 });
	wolf.speed = 0.05f;
	wolf.loop = false;

	face_wolf.PushBack({ 2146, 790, 36, 41 });

	animation = &idle;
	animation_chariot = &wheel;
	animation_chariot_wheels = &chariot_wheels;
	animation_chariot_wheels2 = &chariot_wheels2;

	





	furniture = nullptr;
	chariot_wolf = nullptr;
	chariot_robot = nullptr;
	chariot_face_wolf = nullptr;

	collider = App->collision->AddCollider({ 0, 0, 240, 200 }, COLLIDER_TYPE::COLLIDER_ENEMY_CHARIOT, (Module*)App->enemies);

	original_pos = { x,y };

	/*EnemyInfo ball;
	ball.type = ENEMY_TYPES::Ball;
	ball.x = x - 30;
	ball.y = y + 65;
	ball.path_type = type;

	App->enemies->SpawnEnemy(ball);

	bola = (BALL*)App->enemies->SpawnEnemy(ball);
	bola->SetCarroza(this);*/




}


void CHARIOT::Move()
{

	//position = original_pos + path.GetCurrentPosition(&animation);
	if (App->inter->enemies_movement) {

		CheckState();
		PerformActions();


	}


}



void CHARIOT::CheckState() {

	switch (state)
	{
	case start_move_in:
		position.x -= 1.5;

		if (position.x < App->render->camera.x + App->render->camera.w - 110) {
			state = start_move_out;
			//bola->Active();

		}
		break;

	case start_move_out:
		position.x += 3;
		if (position.x >= App->render->camera.x + App->render->camera.w) {
			state = start_move_with_cam;
		}
		break;

	case start_move_with_cam:
		position.x += int(App->scene_temple->speed);

		

		if (App->enemies->ball_life == 100) {
			state = active;
		}


		break;


	case active:
		position.x -= 1;

		if (position.x < App->render->camera.x + App->render->camera.w - 205) {

			position.x += int(App->scene_temple->speed);
			state = start_wheels;
		}
		break;

	case start_wheels:

		position.x += int(App->scene_temple->speed);

		if(wheel_y >= 65 && wheel_x >= 35){
			state = fight;
		}
		break;

	case fight:
		position.x += int(App->scene_temple->speed);
		state = start_phase2;
		break;

	case start_phase2:
		position.x += int(App->scene_temple->speed);

		if (App->enemies->chariot_life == 100) {
			state = phase2;
		}
		break;

	case phase2:
		position.x += int(App->scene_temple->speed);
		
		if (time_delay2) {
			time_entry2 = SDL_GetTicks();
			time_delay2 = false;
			
		}

		time_current2 = SDL_GetTicks() - time_entry2;

		if (time_current2 > 2000) {
			time_delay2 = true;
			state = face_shot;
			
		}

		break;

	case face_shot:
		position.x += int(App->scene_temple->speed);

		if (wolf.Finished()) {
			state = phase2;
			wolf.Reset();
			
		}

	}

}

void CHARIOT::PerformActions() {
	switch (state)
	{
	case start_move_in:
		animation = &idle;
		animation_chariot = &wheel;
		animation_chariot_wheels = nullptr;
		animation_chariot_wheels2 = nullptr;
		break;

	case start_move_out:
		animation = &idle;
		animation_chariot = &wheel;
		animation_chariot_wheels = nullptr;
		animation_chariot_wheels2 = nullptr;
		break;

	case start_move_with_cam:
		animation = &idle;
		animation_chariot_wheels = nullptr;
		animation_chariot_wheels2 = nullptr;
		animation_chariot = &wheel;
		break;

	case active:
		animation = &idle;
		animation_chariot = &wheel;
		animation_chariot_wheels = nullptr;
		animation_chariot_wheels2 = nullptr;
		break;

	case start_wheels:
		wheel_y += 1.5;
		wheel_x += 1;

		animation_chariot_wheels = &chariot_wheels;
		animation_chariot_wheels2 = &chariot_wheels2;

		animation = &idle;
		animation_chariot = &wheel;
		break;
		
	case fight:
		break;

	case start_phase2:
		break;

	case phase2:
		furniture = &furni;
		chariot_robot = &robot;
		chariot_wolf = nullptr;
		chariot_face_wolf = &face_wolf;
		animation = nullptr;
		animation_chariot = &wheel;
		animation_chariot_wheels = &chariot_wheels;
		animation_chariot_wheels2 = &chariot_wheels2;
		
		break;
	case face_shot:
		chariot_wolf = &wolf;
		//chariot_face_wolf = nullptr;
		break;
	}

}



//void CHARIOT::Active() {
//	state = active;
//	bola = nullptr;
//}