#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneTemple.h"
#include "ModuleAyin.h"
#include "ModuleAyinArrow.h"
#include "ModuleUI.h"
#include "ModuleEnemies.h"

#include "SDL\include\SDL_timer.h"

ModuleAyinArrow::ModuleAyinArrow()
{
	graphics = nullptr;
	current_animation = nullptr;

	//Spawn sword
	spawn.PushBack({ 5, 306, 3, 6 });
	spawn.PushBack({ 11, 304, 1, 12 });
	spawn.PushBack({ 14, 299, 3, 20 });
	spawn.PushBack({ 20, 296, 4, 26 });
	spawn.speed = 0.10f;

	//Iddle sword - can shoot
	iddle.PushBack({ 19, 419, 4, 30 });
	iddle.speed = 0.10f;

	
	//Charging Sword
	charging.PushBack({30, 419, 4, 30});
	

	//Charged sword
	charged.PushBack({ 40, 295, 4, 27 });
	charged.PushBack({ 48, 298, 14, 26 });
	charged.PushBack({ 43, 419, 15, 29 });
	charged.loop = false;
	charged.speed = 0.10f;

	////Decharging sword
	
	decharging.PushBack({73, 433, 32, 4});
	
	//Return sword
	return_sword.PushBack({12, 464, 22, 11});
	return_sword.PushBack({ 44, 458, 4, 21});
	//return_sword.PushBack({ 58, 465, 21, 11 });
	return_sword.loop = false;
	return_sword.speed = 0.20f;

	//Last return sword
	last_return_sword.PushBack({ 58, 465, 21, 11 });
	last_return_sword.speed = 0.20f;
	////Last decharging animation
	//last_descharging.PushBack({ 395, 387, 112, 41 });
	//last_descharging.speed = 0.10f;

	//// Arrow charged
	//charged.PushBack({ 344, 346, 24, 24 });
	//charged.PushBack({ 314, 346, 24, 24 });
	//charged.speed = 0.15f;



}

ModuleAyinArrow::~ModuleAyinArrow()
{
	//destroyer
}

bool ModuleAyinArrow::Start()
{
	LOG("Loading partner textures");
	graphics = App->textures->Load("assets/sprites/characters/ayin/Ayin_SpriteSheet2.png");

	if (graphics == nullptr)
	{
		LOG("Could not load arrow textures")
			return false;
	}

	exist = false;
	aux = 0;

	position.x = App->ayin->position.x - 20;
	position.y = App->ayin->position.y + 20;

	return true;
}

bool ModuleAyinArrow::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);

	graphics = nullptr;

	if (graphics != nullptr)
	{
		LOG("Could not unload partner textures")
			return false;
	}

	return true;
}

update_status ModuleAyinArrow::Update()
{
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_T] == KEY_STATE::KEY_DOWN) {
		App->ayin->power_up++;
	}
	if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN) {
		App->ayin->power_up--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Set position

	position.x = App->ayin->position.x - 20;
	position.y = App->ayin->position.y - 20;

	if (exist) {

		if (state == SPAWN_2) App->render->Blit(graphics, position.x + 16, position.y +5 - r.h, &r);
		else if (state == LEVEL_ONE_2) App->render->Blit(graphics, position.x + 16, position.y + 5 - r.h, &r);
		else if (state == LEVEL_ONE_CHARGING_2) App->render->Blit(graphics, position.x + 16, position.y +4- r.h, &r);
		else if (state == LEVEL_ONE_CHARGE_2) App->render->Blit(graphics, position.x + 12, position.y +4 - r.h, &r);
		//else if (state == WAVE_SHOT_2) App->render->Blit(graphics, position.x + 25, position.y + 9 - r.h, &r);
		else if (state == SWORD_WAVE) App->render->Blit(graphics, position.x + 40, position.y + 2 - r.h, &r);
		else if (state == AYIN_COMEBACK) App->render->Blit(graphics, position.x + 40, position.y + 2 - r.h, &r);
		else if (state == LAST_SWORD_ANIM) App->render->Blit(graphics, position.x + 25, position.y + 2 - r.h, &r);


		if (App->input->keyboard[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN) {
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
			}
			shot_current = SDL_GetTicks() - shot_entry;
			if (shot_current > 140) {
				/*if (App->ayin->power_up == 2) {
					App->particles->AddParticle(App->particles->arrow_shoot, position.x + 10, position.y - 13, COLLIDER_PLAYER_KATANA_SHOT_ARROW);
					App->particles->arrow_shoot.fx_played = 1;
				}*/

				
				switch (aux1) {
				case 0:
					if (App->ayin->power_up == 1) {
						App->particles->AddParticle(App->particles->ayin_wave, position.x, position.y - 7, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 2) {
						App->particles->AddParticle(App->particles->ayin_wave_2, position.x, position.y - 7, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 3) {
						App->particles->AddParticle(App->particles->ayin_wave_3, position.x, position.y - 7, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 4) {
						App->particles->AddParticle(App->particles->ayin_wave_4, position.x , position.y - 7, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					LOG("Shoot 1");
					aux1++;
					break;

				case 1:
					if (App->ayin->power_up == 1) {
						App->particles->AddParticle(App->particles->ayin_wave, position.x, position.y - 25, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 2) {
						App->particles->AddParticle(App->particles->ayin_wave_2, position.x, position.y - 25, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 3) {
						App->particles->AddParticle(App->particles->ayin_wave_3, position.x, position.y - 25, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					else if (App->ayin->power_up == 4) {
						App->particles->AddParticle(App->particles->ayin_wave_4, position.x , position.y - 25, COLLIDER_PLAYER_AYIN_SHOT);
						shot_delay = true;
					}
					aux1 = 0;
					break;
				}
				
			}
		}
	}

	return UPDATE_CONTINUE;
}



void ModuleAyinArrow::CheckState() {

	switch (state)
	{
	case NOT_EXISTING_2:
		if (App->ayin->power_up == 1) {
			exist = true;
			state = SPAWN_2;
		}
		break;

	case SPAWN_2:
		if (spawn.Finished()) {
			spawn.Reset();
			state = LEVEL_ONE_2;
		}
	case LEVEL_ONE_2:
		if (App->ayin->power_up == 0) {
			exist = false;
			state = NOT_EXISTING_2;
		}
		if (App->ayin->power_up == 2 || App->ayin->power_up == 3 || App->ayin->power_up == 4) {
			state = LEVEL_ONE_2;
		}
		if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT) {
			if (time_shoot) {
				time_on_entry = SDL_GetTicks();
				time_shoot = false;
			}
			current_time = SDL_GetTicks() - time_on_entry;
			if (current_time > 800) {
				time_shoot = true;
				state = LEVEL_ONE_CHARGING_2;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_UP) {
			time_shoot = true;
			
		}
		break;

	case LEVEL_ONE_CHARGING_2:
		if (charging.Finished() && App->ayin->charging.Finished()) {
			state = LEVEL_ONE_CHARGE_2;
		}
		break;

	case LEVEL_ONE_CHARGE_2:
		if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_UP) {
			state = WAVE_SHOT_2;
			create_wave = true;
		}
		break;

	case WAVE_SHOT_2:
		if (App->ayin->spin_decharging.Finished()) {
		
			//App->ayin->state = DECHARGING_AYIN;
			state = SWORD_WAVE;
		}
		break;

	case SWORD_WAVE:
		if (App->ayin->decharging.Finished()) {

			state = AYIN_COMEBACK;
		}
		break;
    

	case AYIN_COMEBACK:

		if (return_sword.Finished()) {
			state = LAST_SWORD_ANIM;
		}

		/*if (App->ayin->return_idle.Finished()) {
			App->ayin->state = IDLE_2;
			state = SPAWN_2;
		}*/
		break;

	case LAST_SWORD_ANIM:

		if (App->ayin->return_idle.Finished()) {
			App->ayin->state = IDLE_2;
			state = SPAWN_2;
		}
		break;


	//case LAST_ARROW_SHOT:
	//	if (last_descharging.Finished()) {

	//		charging_time = SDL_GetTicks() - charge_on_entry;
	//		if (charging_time > 300) {
	//			charge_on_entry = SDL_GetTicks();
	//			create_bullet = true;
	//			state = LEVEL_ONE;
	//		}
	//	}
	//	break;

	}
}



void ModuleAyinArrow::PerformActions()
{
	switch (state) {
	case NOT_EXISTING_2:
		current_animation = &iddle;
		break;

	case SPAWN_2:
		current_animation = &spawn;
		break;

	case LEVEL_ONE_2:
		//ArrowBehaviour();

		current_animation = &iddle;

		/*if (charging.Finished()) {
			charging.Reset();
		}

		if (App->ayin->charging.Finished()) {
			App->ayin->charging.Reset();
		}*/
		break;

	case LEVEL_ONE_CHARGING_2:

		current_animation = &charging;
		App->ayin->state = CHARGING_AYIN;
		
		
		break;

	case LEVEL_ONE_CHARGE_2:

		if (charging.Finished()) {
			current_animation = &charged;
		}

		if (App->ayin->charging.Finished()) {
			App->ayin->state = CHARGE_AYIN;
		}
		break;

	case WAVE_SHOT_2:
		
		App->ayin->state = SPIN_DECHARGING_AYIN;

		/*if (App->ayin->spin_decharging.Finished()) {
			current_animation = &decharging;
		}*/
		/*if (time_shoot3) {
			time_on_entry3 = SDL_GetTicks();
			time_shoot3 = false;
		}
		current_time3 = SDL_GetTicks() - time_on_entry3;
		if (current_time3 > 1000) {
			time_shoot3 = true;
			current_animation = &decharging;
		}*/
		
		break;
	case SWORD_WAVE:

	/*	if (App->ayin->spin_decharging.Finished()) {

			App->ayin->state = DECHARGING_AYIN;
			
		}*/
		App->ayin->state = DECHARGING_AYIN;

		current_animation = &decharging;

		if (return_sword.Finished()) {
			return_sword.Reset();
		}

		if (create_wave) {
			switch (state_wave) {
			case 0:
				App->particles->AddParticle(App->particles->wave1, position.x - 20, position.y + 2, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave++;
				break;
			case 1:
				App->particles->AddParticle(App->particles->wave2, position.x - 7, position.y + 2, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave++;
				break;
			case 2:
				App->particles->AddParticle(App->particles->wave3, position.x + 15 , position.y - 16, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave++;
				break;
			case 3:
				App->particles->AddParticle(App->particles->wave4, position.x + 16, position.y - 16, COLLIDER_PLAYER_AYIN_SHOT);
			
				state_wave++;
				break;
			case 4:
				App->particles->AddParticle(App->particles->wave5, position.x + 50, position.y - 16, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave++;
				break;
		    case 5:
				App->particles->AddParticle(App->particles->wave6, position.x + 50, position.y - 16, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave++;
				
				break;
			case 6:
				App->particles->AddParticle(App->particles->wave7, position.x + 50, position.y - 16, COLLIDER_PLAYER_AYIN_SHOT);
				state_wave = 0;
				create_wave = false;
				break;
			}

		}
		break;
		


	case  AYIN_COMEBACK:
	
		current_animation = &return_sword;
		
		App->ayin->state = RETURN_IDLE_AYIN;
		break;

	case LAST_SWORD_ANIM:
		current_animation = &last_return_sword;
		break;


	/*case LAST_ARROW_SHOT:
		current_animation = &last_descharging;
		if (create_bullet) {
			App->particles->AddParticle(App->particles->charged_arrow_shoot, position.x + 107, position.y - 3, COLLIDER_PLAYER_KATANA_CHARGED_SHOT_ARROW);
			create_bullet = false;
		}

		break;*/
	}
}


