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

//#include "ModuleKatanaArrow.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include "ModuleAyin.h"
#include "ModuleSceneTemple.h"



ModuleAyin::ModuleAyin()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 20;

	// idle animation (ayin sprite sheet)
	idle.PushBack({ 29, 1, 33, 33 });
	idle.PushBack({ 63, 1, 33, 33 });
	idle.PushBack({ 101, 1, 33, 33 });
	idle.speed = 0.20f;

	// walk backward animation (ayin sprite sheet)
	backward.PushBack({ 88, 37, 21, 33 });
	backward.PushBack({ 114, 37, 20, 33 });
	backward.PushBack({ 139, 37, 20, 33 });
	backward.speed = 0.15f;

	//On recive one hit INTERMEDIATE
	intermediate.PushBack({ 145, 2, 23, 32 });
	intermediate.PushBack({ 171, 2, 14, 32 });
	intermediate.PushBack({ 189, 2, 21, 32 });
	intermediate.PushBack({ 212, 2, 15, 32 });
	intermediate.speed = 0.15f;

	//INTERMEDIATE RETURN
	intermediate.PushBack({ 212, 2, 15, 32 });
	intermediate.PushBack({ 189, 2, 21, 32 });
	intermediate.PushBack({ 171, 2, 14, 32 });
	intermediate.PushBack({ 145, 2, 23, 32 });
	intermediate.speed = 0.15f;

	// from idle to backward
	idle_to_backward.PushBack({ 4, 39, 31, 33 });
	idle_to_backward.PushBack({ 38, 39, 24, 32 });
	idle_to_backward.PushBack({ 64, 37, 19, 32 });
	idle_to_backward.speed = 0.15f;

	// falling
	falling.PushBack({ 4, 39, 31, 33 });
	falling.speed = 0.15f;

	// starting sword attack
	starting_sword_attack.PushBack({ 3, 108, 21, 32 });
	starting_sword_attack.PushBack({ 27, 110, 17, 32 });
	starting_sword_attack.PushBack({ 47, 110, 21, 32 });
	starting_sword_attack.speed = 0.15f;

	// catching sword attack
	catching_sword_attack.PushBack({ 79, 108, 20, 32 });
	catching_sword_attack.PushBack({ 100, 108, 21, 32 });
	catching_sword_attack.PushBack({ 124, 108, 21, 32 });
	catching_sword_attack.PushBack({ 147, 108, 22, 32 });
	catching_sword_attack.speed = 0.15f;

	// hitting sword attack
	hitting_sword_attack.PushBack({ 171, 107, 29, 32 });
	hitting_sword_attack.PushBack({ 204, 108, 17, 32 });
	hitting_sword_attack.PushBack({ 225, 109, 34, 31 });
	hitting_sword_attack.speed = 0.15f;

	// final attack
	final_attack.PushBack({ 3, 148, 33, 30 });
	final_attack.PushBack({ 39, 149, 33, 30 });
	final_attack.PushBack({ 76, 148, 31, 31 });
	final_attack.PushBack({ 109, 149, 28, 30 });
	final_attack.PushBack({ 141, 149, 26, 30 });
	final_attack.PushBack({ 170, 149, 28, 30 });
	final_attack.PushBack({ 202, 148, 27, 30 });
	final_attack.PushBack({ 233, 148, 26, 30 });
	final_attack.speed = 0.15f;


	/*   //Intermediate
	intermediate.PushBack({ 389,7,30,33 });
	intermediate.PushBack({ 365,6,24,33 });
	intermediate.PushBack({ 260,7,22,33 });
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 260,7,22,33 });
	intermediate_return.PushBack({ 365,6,24,33 });
	intermediate_return.PushBack({ 389,7,30,33 });
	intermediate_return.speed = 0.10f;               */

}


ModuleAyin::~ModuleAyin()
{}

// Load assets
bool ModuleAyin::Start()
{
	LOG("Loading player textures");

	graphics = App->textures->Load("assets/sprites/characters/ayin/Ayin_Spritesheet2.png");


	position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 100;

	state = SPAWN_PLAYER;
	//App->katana_arrow->Enable();
	time = true;
	destroyed = false;

	return true;
}

// Unload assets
bool ModuleAyin::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	//App->katana_arrow->Disable();

	return true;
}

update_status ModuleAyin::Update()
{

	//Create bool variables
	bool pressed_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT;
	bool pressed_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT;
	bool pressed_S = App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT;
	bool pressed_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT;
	bool gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	bool gamepad_DOWN = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEAD_ZONE;
	bool gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	bool gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;


	bool shot_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN;

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
		if (pressed_A || gamepad_LEFT) {
			position.x -= speed;
		}
		if (pressed_W || gamepad_UP) {
			position.y -= speed;
		}
		if (pressed_D || gamepad_RIGHT) {
			position.x += speed;
		}
		if (pressed_S || gamepad_DOWN) {
			position.y += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN /*|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT*/ || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1) {
			LOG("Shooting bullets");

			/*current_bullet_time = SDL_GetTicks() - bullet_on_entry;

			if (current_bullet_time > 100) {

			bullet_on_entry = SDL_GetTicks();*/
			aux1++;
			switch (aux1) {
			case 0:
				App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				LOG("Shoot 1");
				break;
			case 1:
				App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				break;
			case 2:
				App->particles->AddParticle(App->particles->shoot3, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
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


	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (!check_death) {
		if (check_spawn) {
			position.x++;

		}

		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}


	return UPDATE_CONTINUE;
}

void ModuleAyin::CheckState()
{
	//Create Input Bools
	bool press_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN;
	bool press_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN;
	bool press_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN;
	bool gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	bool gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	bool gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;
	/* NUEVOS NOMBRES DE LAS ANIMACIONES EN EL ENUM:
	
		SPAWN_PLAYER,
		IDLE,
		//BACKWARD,
		//GO_BACKWARD,
		//BACK_IDLE,
		IDLE_TO_BACKWARD,
		FALLING,
		STARTING_SWORD_ATTACK,
		CATCHING_SWORD_ATTACK,
		HITTING_SWORD_ATTACK,
		FINAL_ATTACK   
		
		*/
	switch (state)
	{
	case SPAWN_PLAYER:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE;
		}
		power_up = 0;

		break;

	case IDLE:
		if (press_W || press_A || gamepad_UP || gamepad_LEFT) {
			state = GO_BACKWARD;
		}

		break;

	case GO_BACKWARD:

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || gamepad_UP) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP || gamepad_LEFT) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD;
		}
		break;

	case BACKWARD:
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || gamepad_UP) {
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE || gamepad_LEFT) {
				state = BACK_IDLE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP || gamepad_LEFT) {
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || gamepad_UP) {
				state = BACK_IDLE;
			}
		}
		break;

	case BACK_IDLE:
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || gamepad_UP) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || gamepad_LEFT) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE;
		}
		break;

	}
}

void ModuleAyin::PerformActions()
{
	switch (state) {
	case SPAWN_PLAYER:

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

	case IDLE:
		if (App->render->camera.x > 4000) {
			input = false;
		}
		if (App->render->camera.x < 4000) {
			input = true;
		}
		death_pos = true;
		check_spawn = false;
		alpha_player = 255;

		current_animation = &idle;
		break;

	case GO_BACKWARD:

		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD:

		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE:

		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	}

}
