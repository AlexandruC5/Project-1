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

#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include "ModuleKatana.h"
#include "ModuleSceneTemple.h"



ModuleKatana::ModuleKatana()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 20;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 87, 4, 32, 33 });
	idle.PushBack({ 152, 5, 32, 33 });
	idle.PushBack({ 188, 5, 32, 33 });
	idle.speed = 0.20f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 286, 6, 22, 33 });
	backward.PushBack({ 311, 6, 21, 33 });
	backward.PushBack({ 335, 6, 22, 33 });
	backward.speed = 0.15f;

	//Intermediate
	intermediate.PushBack({ 389,7,30,33 });
	intermediate.PushBack({ 365,6,24,33 });
	intermediate.PushBack({ 260,7,22,33 });
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 260,7,22,33 });
	intermediate_return.PushBack({ 365,6,24,33 });
	intermediate_return.PushBack({ 389,7,30,33 });
	intermediate_return.speed = 0.10f;

	
}


ModuleKatana::~ModuleKatana()
{}

// Load assets
bool ModuleKatana::Start()
{
	LOG("Loading player textures");

	graphics = App->textures->Load("assets/sprites/characters/katana/Katana_Spritesheet.png"); 
	

	position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
	position.y = (App->render->camera.y) / SCREEN_SIZE + 100;

	state = SPAWN_PLAYER;

	time = true;
	destroyed = false;

	return true;
}

// Unload assets
bool ModuleKatana::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	
	return true;
}

update_status ModuleKatana::Update()
{

	//Create bool variables
	bool pressed_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT;
	bool pressed_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT;
	bool pressed_S = App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT;
	bool pressed_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT;

	bool shot_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN;

	 speed = 1.25;


	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (input) {
		if (pressed_A) {
			position.x -= speed;
		}
		if (pressed_W) {
			position.y -= speed;
		}
		if (pressed_D) {
			position.x += speed;
		}
		if (pressed_S) {
			position.y += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
			LOG("Shooting bullets");

			current_bullet_time = SDL_GetTicks() - bullet_on_entry;

			if (current_bullet_time > 100) {

				bullet_on_entry = SDL_GetTicks();
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

void ModuleKatana::CheckState()
{
	//Create Input Bools
	bool press_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN;
	bool press_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN;
	bool press_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN;

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
		
		break;

	case IDLE:
		if (press_W || press_A) {
			state = GO_BACKWARD;
		}

		break;

	case GO_BACKWARD:

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD;
		}
		break;

	case BACKWARD:
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
				state = BACK_IDLE;
			}
		}
		break;

	case BACK_IDLE:
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE;
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE;
		}
		break;

	}
}

void ModuleKatana::PerformActions()
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
