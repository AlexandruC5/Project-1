#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleKatanaArrow.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"

ModuleKatanaArrow::ModuleKatanaArrow()
{
	graphics = nullptr;
	current_animation = nullptr;

	//Spawn arrow
	spawn.PushBack({ 359, 440, 31, 4 });
	spawn.PushBack({ 393, 438, 31, 8 });
	spawn.PushBack({ 426, 434, 31, 16 });
	spawn.PushBack({ 393, 438, 31, 8 });
	spawn.speed = 0.10f;

	//Iddle arrow - can shoot
	iddle.PushBack({ 359, 440, 31, 4 });
	iddle.PushBack({ 393, 438, 31, 8 });
	iddle.PushBack({ 426, 434, 31, 16 });
	iddle.PushBack({ 393, 438, 31, 8 });
	iddle.speed = 0.10f;

	//Charging arrow animation
	charging.PushBack({ 461, 359, 30, 3 });
	charging.PushBack({ 424, 359, 30, 3 });
	charging.PushBack({ 398, 360, 22, 1 });
	charging.PushBack({ 376, 358, 16, 4 });
	//charging.PushBack({ 344, 346, 24, 24 });
	charging.speed = 0.20f;

	//Decharging arrow animation
	decharging.PushBack({ 306, 386, 34, 28 });
	decharging.PushBack({ 347, 387, 46, 26 });
	//decharging.PushBack({ 395, 387, 112, 41 });
	decharging.speed = 0.20f;

	//Last decharging animation
	last_descharging.PushBack({ 395, 387, 112, 41 });
	last_descharging.speed = 0.10f;

	// Arrow charged
	charged.PushBack({ 344, 346, 24, 24 });
	charged.PushBack({ 314, 346, 24, 24 });
	charged.speed = 0.15f;

	

}

ModuleKatanaArrow::~ModuleKatanaArrow()
{
	//destroyer
}

bool ModuleKatanaArrow::Start()
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprites/characters/katana/Katana_SpriteSheet.png");
	arrowsound = App->audio->LoadFx("assets/audio/effects/Player Shoots/katanapowerUP.wav");
	if (graphics == nullptr)
	{
		LOG("Could not load arrow textures")
			return false;
	}

	exist = false;
	aux = 0;

	position.x = App->katana->position.x - 20;
	position.y = App->katana->position.y + 20;

	return true;
}

bool ModuleKatanaArrow::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);

	graphics = nullptr;

	if (graphics != nullptr)
	{
		LOG("Could not unload partner textures")
			return false;
	}
	App->audio->UnloadSFX(arrowsound);
	arrowsound = nullptr;
	return true;
}

update_status ModuleKatanaArrow::Update()
{
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) {
		App->katana->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {
		App->katana->power_up--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Set position
	
		position.x = App->katana->position.x - 20;
		position.y = App->katana->position.y - 20 + arrow_position;
	
	if (exist) {

		if(state == SPAWN /*|| state == LEVEL_ONE*/) App->render->Blit(graphics, position.x + 22 , position.y - 15 - r.h, &r);
		else if (state == LEVEL_ONE) {
			ArrowBehaviour();
			App->render->Blit(graphics, position.x + 22, position.y - 15 - r.h, &r);
		}
		else if (state == LEVEL_ONE_CHARGING) App->render->Blit(graphics, position.x + 22, position.y - 15 - r.h, &r);
		else if (state == LEVEL_ONE_CHARGE) App->render->Blit(graphics, position.x + 12, position.y - 7 - r.h, &r);
		else if (state == ARROW_SHOT) App->render->Blit(graphics, position.x + 15, position.y - 8 - r.h, &r);
		else if (state == LAST_ARROW_SHOT) App->render->Blit(graphics, position.x + 18, position.y + 9 - r.h, &r);
			

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || App->input->controller_A_button==BUTTON_DOWN) {
			Mix_PlayChannel(-1, arrowsound, 0);
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
			}
			shot_current = SDL_GetTicks() - shot_entry;
			if (shot_current > 140) {
				if (App->katana->power_up == 2) {
					App->particles->AddParticle(App->particles->arrow_shoot, position.x + 10, position.y - 13, COLLIDER_PLAYER_KATANA_SHOT_ARROW);
					App->particles->arrow_shoot.fx_played = 1;
				}
				App->particles->AddParticle(App->particles->arrow_shoot, position.x + 22, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT_ARROW);
				shot_delay = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}



void ModuleKatanaArrow::CheckState() {

	switch (state)
	{
	case NOT_EXISTING:
		if (App->katana->power_up == 1) {
			exist = true;
			state = SPAWN;
		}
		break;

	case SPAWN:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE;
		}
	case LEVEL_ONE:
		if (App->katana->power_up == 0) {
			exist = false;
			state = NOT_EXISTING;
		}
		if (App->katana->power_up == 2) {
			state = LEVEL_FOUR;
		}
		if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_REPEAT||App->input->controller_B_button==KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 800) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGING;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_UP || App->input->controller_B_button == KEY_STATE::KEY_UP) {
			time_shoot = true;
		}
		break;

	case LEVEL_ONE_CHARGING:
		if (charging.Finished()) {
			state = LEVEL_ONE_CHARGE;
		}
			break;

	case LEVEL_ONE_CHARGE:
		if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_UP | App->input->controller_B_button == KEY_STATE::KEY_UP) {
			state = ARROW_SHOT;
		}
		break;

	case ARROW_SHOT:
		if (decharging.Finished()) {
			decharging.Reset();
			state = LAST_ARROW_SHOT;
		}


	case LAST_ARROW_SHOT:
		if (last_descharging.Finished()) {
			
			charging_time = SDL_GetTicks() - charge_on_entry;
			if (charging_time > 300) {
				charge_on_entry = SDL_GetTicks();
				create_bullet = true;
				state = LEVEL_ONE;
			}
		}
		break;

	}
}



void ModuleKatanaArrow::PerformActions()
{
	switch (state) {
	case NOT_EXISTING:
		current_animation = &iddle;
		break;

	case SPAWN:
		current_animation = &spawn;
		break;

	case LEVEL_ONE:
		//ArrowBehaviour();
		
		current_animation = &iddle;
		
		if (charging.Finished()) {
			charging.Reset();
		}

		 if (last_descharging.Finished()) {
			last_descharging.Reset();
		}
		break;

	case LEVEL_ONE_CHARGING:
		
			current_animation = &charging;
			break;

	case LEVEL_ONE_CHARGE:
		
		if (charging.Finished()) {
			current_animation = &charged;
		}
		break;

	case ARROW_SHOT:
		current_animation = &decharging;
		break;

	case LAST_ARROW_SHOT:
		current_animation = &last_descharging;
		if (create_bullet) {
			App->particles->AddParticle(App->particles->charged_arrow_shoot, position.x + 107, position.y - 3 , COLLIDER_PLAYER_KATANA_CHARGED_SHOT_ARROW);
			create_bullet = false;
		}

		break;
	}
}


void ModuleKatanaArrow::ArrowBehaviour() {

	

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT||App->input->controller_Dpad_UP==BUTTON_REPEAT) {
		arrow_position++;
		//position.y += arrow_position;
		if (arrow_position >= 47) arrow_position = 47;


		//App->render->Blit(graphics, position.x + 22, position.y - 15 - m.h, &m);
	}
	
	
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->controller_Dpad_DOWN==BUTTON_REPEAT) {

		arrow_position--;
		//position.y += arrow_position;
		if (arrow_position <= 0) arrow_position = 0;


		//App->render->Blit(graphics, position.x + 22, position.y - 15 - m.h, &m);

	}

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_UP || App->input->controller_Dpad_DOWN == BUTTON_UP) {
		position.y += arrow_position;

	}
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || App->input->controller_Dpad_LEFT == BUTTON_REPEAT) {

	}
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || App->input->controller_Dpad_DOWN == BUTTON_REPEAT) {

	}




}