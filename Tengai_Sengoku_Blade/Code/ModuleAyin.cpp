#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"
#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include "ModuleAyin.h"
#include "ModuleAyinArrow.h"
#include "ModuleAyinUltimate.h"
#include "ModuleSceneTemple.h"
#include "CharSelec.h"
#include "ModuleInterface.h"



ModuleAyin::ModuleAyin()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 20;

	// idle animation 
	idle.PushBack({ 63, 1, 33, 33 });
	idle.PushBack({ 101, 1, 33, 33 });
	idle.PushBack({ 29, 1, 33, 33 });
	idle.speed = 0.20f;

	// walk backward animation 
	backward.PushBack({ 88, 37, 21, 33 });
	backward.PushBack({ 114, 37, 20, 33 });
	backward.PushBack({ 139, 37, 20, 33 });
	backward.speed = 0.10f;

	//Intermediate
	intermediate.PushBack({ 4, 39, 31, 33 });
	intermediate.PushBack({ 38, 39, 24, 32 });
	intermediate.PushBack({ 64, 37, 19, 32 });
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 64, 37, 19, 32 });
	intermediate_return.PushBack({ 38, 39, 24, 32 });
	intermediate_return.PushBack({ 4, 39, 31, 33 });
	intermediate_return.speed = 0.10f;

	//Spin
	spin.PushBack({ 145,2,23,32 });
	spin.PushBack({ 172,2,15,32 });
	spin.PushBack({ 189,1,21,33 });
	spin.PushBack({ 212,2,15,32 });

	spin.PushBack({ 145,2,23,32 });
	spin.PushBack({ 172,2,15,32 });
	spin.PushBack({ 189,1,21,33 });
	spin.PushBack({ 212,2,15,32 });
	spin.speed = 0.15f;


	//Spin Circle
	spin_circle.PushBack({ 91,342,22,23 });
	spin_circle.PushBack({ 114,338,30,31 });
	spin_circle.PushBack({ 145,338,32,32 });
	spin_circle.PushBack({ 178,338,32,32 });
	spin_circle.PushBack({ 211,338,32,32 });
	spin_circle.PushBack({ 245,338,32,32 });
	spin_circle.PushBack({ 279,338,32,32 });
	spin_circle.PushBack({ 313,338,32,32 });
	spin_circle.speed = 0.3f;

	//Death
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 300,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,292, 130, 130 });
	death_circle.speed = 0.8f;


	//Death Player
	death.x = 323;
	death.y = 56;
	death.w = 27;
	death.h = 26;

	//Charging
	charging.PushBack({ 3, 108, 22, 32 });
	charging.PushBack({ 27, 110, 18, 32 });
	charging.PushBack({ 47, 110, 21, 32 });
	charging.speed = 0.10f;

	//Charge
	charge.PushBack({ 79, 108, 21, 32 });
	charge.PushBack({ 100, 108, 21, 32 });
	charge.PushBack({ 124, 108, 21, 32 });
	charge.PushBack({ 147, 108, 21, 32 });
	charge.speed = 0.10f;

	//Spin Decharging
	spin_decharging.PushBack({ 171, 107, 29, 32 });
	spin_decharging.PushBack({ 204, 108, 17, 32 });
	spin_decharging.speed = 0.15f;
	/*spin_decharging.loop = false;*/

	//Decharging
	decharging.PushBack({ 225, 110, 35, 30 });
	decharging.PushBack({ 3, 148, 34, 30 });
	decharging.PushBack({ 39, 149, 33, 30 });
	decharging.speed = 0.15f;

	return_idle.PushBack({ 76, 149, 31, 30 });
	return_idle.PushBack({ 109, 149, 28, 30 });
	return_idle.PushBack({ 141, 149, 27, 30 });
	return_idle.PushBack({ 170, 149, 28, 30 });
	return_idle.PushBack({ 202, 148, 28, 30 });
	return_idle.PushBack({ 233, 148, 26, 30 });
	return_idle.speed = 0.17f;

	//Ultimate Ayin
	ulti_ayin.PushBack({ 187, 444, 20, 33 });
	ulti_ayin.PushBack({ 213, 444, 16, 32 });
	ulti_ayin.PushBack({ 234, 445, 22, 32 });
	ulti_ayin.PushBack({ 259, 444, 30, 33 });
	ulti_ayin.PushBack({ 292, 445, 18, 33 });
	ulti_ayin.PushBack({ 313, 448, 35, 30 });
	ulti_ayin.loop = false;
	ulti_ayin.speed = 0.12f;
}


ModuleAyin::~ModuleAyin()
{}

// Load assets
bool ModuleAyin::Start()
{
	LOG("Loading player textures");

	graphics = App->textures->Load("assets/sprites/characters/ayin/Ayin_Spritesheet2.png");
	player_death = App->textures->Load("assets/sprites/characters/death_player/Death_Player.png");

	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_PLAYER);

	if (App->charmenu->P1ayin) {
		position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
		position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
	}
	else if (App->charmenu->P2ayin) {
	position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 155;
	}

	state = SPAWN_PLAYER_2;
	
	time = true;
	destroyed = false;

	App->ayin_arrow->Enable();
	App->ulti_ayin->Enable();

	App->inter->num_life_ayin = 3;
	return true;
}

// Unload assets
bool ModuleAyin::CleanUp()
{
	LOG("Unloading player");

	if (coll != nullptr)
		coll->to_delete = true;

	App->textures->Unload(graphics);
	App->textures->Unload(player_death);
	App->ayin_arrow->Disable();
	App->ulti_ayin->Disable();

	App->inter->game_over_ayin = true;
	return true;
}

update_status ModuleAyin::Update()
{

	//Create bool variables
	bool pressed_I = App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT;
	bool pressed_J = App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT;
	bool pressed_K = App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_REPEAT;
	bool pressed_L = App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_REPEAT;


	
	
	bool gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	bool gamepad_DOWN = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEAD_ZONE;
	bool gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	bool gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;


	bool shot_space = App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN;

	speed = 1.25;

	//Power Up Limits
	if (power_up < 0) {
		power_up = 0;
	}
	if (power_up > 2) {
		power_up = 2;
	}

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (input) {
		if (pressed_J || gamepad_LEFT) {
			position.x -= speed;
		}
		if (pressed_I || gamepad_UP) {
			position.y -= speed;
		}
		if (pressed_L || gamepad_RIGHT) {
			position.x += speed;
		}
		if (pressed_K || gamepad_DOWN) {
			position.y += speed;
		}

		if (shot_space /*|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT*/ /*|| SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1*/) {
			LOG("Shooting bullets");

			/*current_bullet_time = SDL_GetTicks() - bullet_on_entry;

			if (current_bullet_time > 100) {

			bullet_on_entry = SDL_GetTicks();*/
			aux1++;
			switch (aux1) {
			case 0:
				App->particles->AddParticle(App->particles->ayin_shoot1, position.x, position.y - 20, COLLIDER_PLAYER_AYIN_SHOT, PARTICLE_SHOT_AYIN);
				LOG("Shoot 1");
				break;
			case 1:
				App->particles->AddParticle(App->particles->ayin_shoot2, position.x, position.y - 20, COLLIDER_PLAYER_AYIN_SHOT, PARTICLE_SHOT_AYIN);
				break;
			case 2:
				App->particles->AddParticle(App->particles->ayin_shoot3, position.x, position.y - 20, COLLIDER_PLAYER_AYIN_SHOT, PARTICLE_SHOT_AYIN);
				aux1 = 0;
				break;

			}

		}

	}

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {

	App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);

	if (time) {
	time_on_entry = SDL_GetTicks();
	time = false;
	}
	current_time = SDL_GetTicks() - time_on_entry;
	if (current_time > 1500) {
	App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
	time = true;
	}

	}*/






	//Fade
	SDL_SetTextureAlphaMod(graphics, alpha_player);

	//Set spin posotion
	if (spin_pos) {
		aux_spin.x = position.x + 5;
		aux_spin.y = position.y - 32;
		spin_pos = false;
	}

	if (death_pos) {
		aux_death.x = position.x - 40;
		aux_death.y = position.y - 70;
		death_pos = false;
	}


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (!check_death) {
		if (check_spawn) {
			position.x++;
			coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		}
		else {
			coll->SetPos(position.x, position.y - 32);
		}

		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}

	else {
		App->render->Blit(graphics, position.x, position.y - 32, &death);
		coll->SetPos(App->render->camera.x, App->render->camera.y - 32);

		position.x -= 1;
		position.y += 3;
	}

	if (coll->CheckCollision(App->scene_temple->coll_left->rect)) {
		position.x = (App->render->camera.x / SCREEN_SIZE);

	}
	if (coll->CheckCollision(App->scene_temple->coll_right->rect)) {
		position.x = (SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE) - 33;

	}
	if (coll->CheckCollision(App->scene_temple->coll_up->rect)) {
		position.y = 35;

	}
	if (coll->CheckCollision(App->scene_temple->coll_down->rect)) {
		position.y = SCREEN_HEIGHT - 4;
	}

	return UPDATE_CONTINUE;
}

void ModuleAyin::CheckState()
{
	//Create Input Bools
	bool pressed_J = App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_REPEAT;
	bool pressed_I = App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_REPEAT;

	bool press_J = App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN;
	bool press_I = App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN;

	bool release_J = App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_UP;
	bool release_I = App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_UP;

	bool released_I = App->input->keyboard[SDL_SCANCODE_I] == KEY_STATE::KEY_IDLE;
	bool released_J = App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_IDLE;


	bool gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	bool gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	bool gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;
	

	switch (state)
	{
	case SPAWN_PLAYER_2:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE_2;
		}
		power_up = 0;

		break;

	case IDLE_2:
		if (press_I || press_J || gamepad_UP || gamepad_LEFT) {
			state = GO_BACKWARD_2;
		}

		break;

	case GO_BACKWARD_2:

		if (release_I || gamepad_UP) {
			state = BACK_IDLE_2;
		}
		if (release_J || gamepad_LEFT) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD_2;
		}
		break;

	case BACKWARD_2:

		if (release_I || release_J || gamepad_UP || gamepad_LEFT) {
			if (released_I || released_J || gamepad_UP || gamepad_LEFT) {

				state = BACK_IDLE_2;


				/*if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || gamepad_UP) {
				if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE || gamepad_LEFT) {
				state = BACK_IDLE;
				}
				}
				if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP || gamepad_LEFT) {
				if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || gamepad_UP) {
				state = BACK_IDLE;*/
			}
		}
		break;

	case BACK_IDLE_2:
		if (pressed_I || gamepad_UP) {
			state = BACK_IDLE_2;
		}
		if (pressed_J || gamepad_LEFT) {
			state = BACK_IDLE_2;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE_2;
		}
		break;

	case ULTI_AYIN:
		if (ulti_ayin.Finished()) {
			ulti_ayin.Reset();
			state = IDLE_2;
		}

	case SPIN_2:
		if (spin.Finished()) {
			spin.Reset();
			spin_circle.Reset();
			state = IDLE_2;
		}
		break;

	case DEATH_2:
		if (position.y > SCREEN_HEIGHT + 80) {
			state = POST_DEATH_2;
		}
		break;

	/*case SPIN_DECHARGING_AYIN:
		if (spin_decharging.Finished()) {
			state = DECHARGING_AYIN;
		}*/

	case POST_DEATH_2:
		if (App->inter->num_life_ayin > 0) {
			position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
			position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
			time = true;
			state = SPAWN_PLAYER_2;
		}
		
		break;
	}
}

void ModuleAyin::PerformActions()
{
	switch (state) {

	case SPAWN_PLAYER_2:
		App->inter->game_over_ayin = false;
		check_spawn = true;
		current_animation = &idle;
		blink_time = SDL_GetTicks() - blink_on_entry;
		if (blink_time > 10) {
			blink_on_entry = SDL_GetTicks();
			if (blink) {
				alpha_player = 0;
				blink = false;
			}
			else {
				alpha_player = 255;
				blink = true;
			}
		}
		input = false;
		check_death = false;
		break;

	case IDLE_2:
		if (App->render->camera.x > 40000) {
			input = false;
		}
		if (App->render->camera.x < 40000) {
			input = true;
		}
		death_pos = true;
		check_spawn = false;
		alpha_player = 255;
		spin.Reset();
		current_animation = &idle;
		break;

	case GO_BACKWARD_2:

		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD_2:

		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE_2:

		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	case CHARGING_AYIN:
		if (charging.Finished())
			charging.Reset();
		current_animation = &charging;
		break;

	case CHARGE_AYIN:
		current_animation = &charge;
		break;
		
	case SPIN_DECHARGING_AYIN:
		if (spin_decharging.Finished())
			spin_decharging.Reset();
		current_animation = &spin_decharging;
		break;

	case DECHARGING_AYIN:
		if (decharging.Finished())
			decharging.Reset();
		current_animation = &decharging;
		break;

	case RETURN_IDLE_AYIN:
		if (return_idle.Finished())
			return_idle.Reset();
		current_animation = &return_idle;
		break;

	case ULTI_AYIN:
		/*if (ulti_ayin.Finished())
			ulti_ayin.Reset();*/
		current_animation = &ulti_ayin;
		break;

	case SPIN_2:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;

	case DEATH_2:
		SDL_Rect death_rect = death_circle.GetCurrentFrame();
		power_up = 0;
		check_death = true;
		input = false;
		App->render->Blit(player_death, aux_death.x, aux_death.y, &death_rect, 1.0f);
		/*if (explosion) {
			App->particles->AddParticle(App->particles->explosion, position.x - 8, position.y - 8);
			explosion = false;*/
		//}
		alpha_player = 255;
		break;
	case POST_DEATH_2:
		if (App->inter->num_life_ayin == 0) {
			if (App->inter->score_ayin > 1000) {
				App->inter->score_ayin -= 1000;
			}
			App->ayin->Disable();
		}
		else {
			check_death = false;
		}
		break;
	}

}
