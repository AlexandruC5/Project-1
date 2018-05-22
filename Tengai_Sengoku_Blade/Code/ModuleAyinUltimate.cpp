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
#include "ModuleAyinUltimate.h"

#include "SDL\include\SDL_timer.h"

ModuleAyinUltimate::ModuleAyinUltimate()
{
	graphics = nullptr;
	current_animation = nullptr;

	//PHASE 1
	phase1.PushBack({222, 287, 32, 39});

	//PHASE 2
	phase2.PushBack({256, 277, 49, 57});

	//PHASE 3
	phase3.PushBack({306, 267, 63, 65});

	

}

ModuleAyinUltimate::~ModuleAyinUltimate()
{
	//destroyer
}

bool ModuleAyinUltimate::Start()
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

bool ModuleAyinUltimate::CleanUp()
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

update_status ModuleAyinUltimate::Update()
{
	CheckState();

	PerformActions();

	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN) {
		App->ayin->ulti++;
	}
	if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN) {
		App->ayin->ulti--;
	}

	//Draw partner
	SDL_Rect r = current_animation->GetCurrentFrame();
	/*SDL_Rect r1 = current_animation_2->GetCurrentFrame();
	SDL_Rect r2 = current_animation_3->GetCurrentFrame();
	SDL_Rect r3 = current_animation_4->GetCurrentFrame();*/

	//Set position

	position.x = App->ayin->position.x - 20;
	position.y = App->ayin->position.y - 20;

	//ULTI 1
	if (exist) {

		if (state == FIRST_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);
		else if (state == SECOND_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30  - r.h, &r);
		else if (state == THIRD_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);
		//else if (state == SHOT_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);


		/*else if (state == LEVEL_ONE_CHARGE_2) App->render->Blit(graphics, position.x + 12, position.y + 4 - r.h, &r);
		else if (state == WAVE_SHOT_2) App->render->Blit(graphics, position.x + 25, position.y + 9 - r.h, &r);
		else if (state == SWORD_WAVE) App->render->Blit(graphics, position.x + 40, position.y + 2 - r.h, &r);
		else if (state == AYIN_COMEBACK) App->render->Blit(graphics, position.x + 40, position.y + 2 - r.h, &r);
		else if (state == LAST_SWORD_ANIM) App->render->Blit(graphics, position.x + 25, position.y + 2 - r.h, &r);*/


		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) {

			App->ayin->state = ULTI_AYIN;
			state = FIRST_PHASE;

		}

	}

	return UPDATE_CONTINUE;
}



void ModuleAyinUltimate::CheckState() {

	switch (state)
	{
	case NO_ULTI:
		if (App->ayin->ulti > 0) {
			exist = true;
			spot1 = 0;
			
		}
		break;

	case FIRST_PHASE:
		spot1 = spot1 + 2;
		if (spot1 >= 30) {
		state =SECOND_PHASE;
		}

	case SECOND_PHASE:

		spot1 = spot1 + 2;
		if (spot1 >= 60) {
			state = THIRD_PHASE;
		}
		
		break;

	case THIRD_PHASE:

		spot1 = spot1 + 2;
		if (spot1 >= 90) {
			state = SHOT_PHASE;
			ulti = true;
		}

		break;

	case SHOT_PHASE:
		/*if (App->particles->ulti_ayin.position.x > App->particles->ulti_ayin.position.x + SCREEN_WIDTH) {*/
			state = NO_ULTI;
		/*}*/
		break;

	}
}



void ModuleAyinUltimate::PerformActions()
{
	switch (state) {
	case NO_ULTI:
		current_animation = &phase1;
		break;

	case FIRST_PHASE:
		current_animation = &phase1;
		break;

	case SECOND_PHASE:
		current_animation = &phase2;

		break;

	case THIRD_PHASE:
		current_animation = &phase3;
		break;

	case SHOT_PHASE:

		if (ulti) {
			App->particles->AddParticle(App->particles->ulti_ayin, position.x + spot1, position.y - 30, COLLIDER_PLAYER_AYIN_ULTI);
			ulti = false;
		}
		
		break;

	
	}
}