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

	spot1 = 0;
	spot2 = 0;
	spot3 = 0;
	spot4 = 0;

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
	SDL_Rect r1 = current_animation_2->GetCurrentFrame();
	/*SDL_Rect r2 = current_animation_3->GetCurrentFrame();*/
	//SDL_Rect r3 = current_animation_4->GetCurrentFrame();

	//Set position

	position.x = App->ayin->position.x - 20;
	position.y = App->ayin->position.y - 20;

	
	
	if (exist) {
		//ULTI 1
		if (state == FIRST_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);
		else if (state == SECOND_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30  - r.h, &r);
		else if (state == THIRD_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);
		//else if (state == SHOT_PHASE) App->render->Blit(graphics, position.x + spot1, position.y + 30 - r.h, &r);


		if (state2 == FIRST_PHASE) App->render->Blit(graphics, position.x + spot2, position.y + 30 - r.h, &r1);
		else if (state2 == SECOND_PHASE) App->render->Blit(graphics,position.x + spot2 , position.y + 30 - r.h, &r1);
		else if (state2 == THIRD_PHASE) App->render->Blit(graphics, position.x + spot2 , position.y + 30 - r.h, &r1);

		//ULTI 3
		/*else if (state3 == FIRST_PHASE) App->render->Blit(graphics, position.x + spot3, position.y + 30 - r.h, &r2);
		else if (state3 == SECOND_PHASE) App->render->Blit(graphics, position.x + spot3, position.y + 30 - r.h, &r2);
		else if (state3 == THIRD_PHASE) App->render->Blit(graphics, position.x + spot3, position.y + 30 - r.h, &r2);*/

		////ULTI 4
		//else if (state4 == FIRST_PHASE) App->render->Blit(graphics, position.x + spot4, position.y + 30 - r.h, &r3);
		//else if (state4 == SECOND_PHASE) App->render->Blit(graphics, position.x + spot4, position.y + 30 - r.h, &r3);
		//else if (state4 == THIRD_PHASE) App->render->Blit(graphics, position.x + spot4, position.y + 30 - r.h, &r3);


		if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) {

			App->ayin->state = ULTI_AYIN;
			state = FIRST_PHASE;
			active = true;
			
		}


		if (active) {
			if (spot1 > 80) {
				state2 = FIRST_PHASE;
				active = false;
				//active2 = true;
			}

		}

		/*if (active2) {
			if (spot1 > 80) {
				state3 = FIRST_PHASE;
				
				active2 = false;
			}
		}*/


		/*if (active) {
			if (shot_delay)
			{
				shot_entry = SDL_GetTicks();
				shot_delay = false;
				active = false;
			}

			shot_current = SDL_GetTicks() - shot_entry;

			if (shot_current == 140) {
				state2 = FIRST_PHASE;

			}
			if (shot_current == 300) {
				state3 = FIRST_PHASE;
			}

			if (shot_current == 450) {
				state4 = FIRST_PHASE;
				shot_delay = true;

			}
		}*/

	}


	//if (exist2) {

	////ULTI 2
 //    if (state2 == FIRST_PHASE) App->render->Blit(graphics, position.x +spot2 , position.y + 30 - r.h, &r1);
	//else if (state2 == SECOND_PHASE) App->render->Blit(graphics,position.x + spot2 , position.y + 30 - r.h, &r1);
	//else if (state2 == THIRD_PHASE) App->render->Blit(graphics, position.x + spot2 , position.y + 30 - r.h, &r1);


	//state2 = FIRST_PHASE;
//	if (shot_delay)
//	{
//		shot_entry = SDL_GetTicks();
//		shot_delay = false;
//		
//		
//}
//
//	shot_current = SDL_GetTicks() - shot_entry;
//
//	if (shot_current >= 500) {
//        state2 = FIRST_PHASE;
//		//shot_delay = true;
//		//shot_entry = SDL_GetTicks();
//
//	}

	//if (App->input->keyboard[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) {

	//	state2 = FIRST_PHASE;
	//	//active = true;
	//}
	/*}*/

	return UPDATE_CONTINUE;
}



void ModuleAyinUltimate::CheckState() {
	//ULTI 1
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
		break;

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

	//ULTI 2
	switch (state2)
	{
	case NO_ULTI:
		if (App->ayin->ulti > 0) {
			
			spot2 = 0;


		}
		break;

	case FIRST_PHASE:
		spot2 = spot2 + 2;
		if (spot2 >= 30) {
			state2 = SECOND_PHASE;
			
		}
		break;

	case SECOND_PHASE:

		spot2 = spot2 + 2;

		if (spot2 >= 60) {
			state2 = THIRD_PHASE;
		}

		break;

	case THIRD_PHASE:

		spot2 = spot2 + 2;

		if (spot2 >=  90) {
			state2 = SHOT_PHASE;
			ulti2 = true;
		}

		break;

	case SHOT_PHASE:
		/*if (App->particles->ulti_ayin.position.x > App->particles->ulti_ayin.position.x + SCREEN_WIDTH) {*/
		state2 = NO_ULTI;
		
		/*}*/
		break;

	}

	//switch (state3)
	//{
	//case NO_ULTI:
	//	if (App->ayin->ulti > 0) {

	//		spot3 = 0;


	//	}
	//	break;

	//case FIRST_PHASE:
	//	spot3 = spot3 + 2;
	//	if (spot3 >= 30) {
	//		state3 = SECOND_PHASE;

	//	}
	//	break;

	//case SECOND_PHASE:

	//	spot3 = spot3 + 2;

	//	if (spot3 >= 60) {
	//		state3 = THIRD_PHASE;
	//	}

	//	break;

	//case THIRD_PHASE:

	//	spot3 = spot3 + 2;

	//	if (spot3 >= 90) {
	//		state3 = SHOT_PHASE;
	//		ulti = true;
	//	}

	//	break;

	//case SHOT_PHASE:
	//	/*if (App->particles->ulti_ayin.position.x > App->particles->ulti_ayin.position.x + SCREEN_WIDTH) {*/
	//	state3 = NO_ULTI;

	//	/*}*/
	//	break;

	//}

	////ULTI 4
	//switch (state4)
	//{
	//case NO_ULTI:
	//	if (App->ayin->ulti > 0) {
	//		exist = true;
	//		spot4 = 0;


	//	}
	//	break;

	//case FIRST_PHASE:
	//	spot4 = spot4 + 2;
	//	if (spot4 >= 30) {
	//		state4 = SECOND_PHASE;
	//	}
	//	break;

	//case SECOND_PHASE:

	//	spot4 = spot4 + 2;

	//	if (spot4 >= 60) {
	//		state4 = THIRD_PHASE;
	//	}

	//	break;

	//case THIRD_PHASE:

	//	spot4 = spot4 + 2;

	//	if (spot4 >= 90) {
	//		state4 = SHOT_PHASE;
	//		ulti = true;
	//	}

	//	break;

	//case SHOT_PHASE:
	//	/*if (App->particles->ulti_ayin.position.x > App->particles->ulti_ayin.position.x + SCREEN_WIDTH) {*/
	//	state4 = NO_ULTI;
	//	/*}*/
	//	break;

	//}
}



void ModuleAyinUltimate::PerformActions()
{
	//ULTI 1
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

	//ULTI 2
	switch (state2) {
	case NO_ULTI:
		current_animation_2 = &phase1;
		break;

	case FIRST_PHASE:
		current_animation_2 = &phase1;
		break;

	case SECOND_PHASE:
		current_animation_2 = &phase2;
	
		break;

	case THIRD_PHASE:
		current_animation_2 = &phase3;
		
		break;

	case SHOT_PHASE:
		
		if (ulti2) {
			App->particles->AddParticle(App->particles->ulti_ayin,  position.x + spot2 , position.y - 30, COLLIDER_PLAYER_AYIN_ULTI);
			ulti2 = false;
		}

		break;


	}

	//ULTI 3
	/*switch (state3) {
	case NO_ULTI:
		current_animation_3 = &phase1;
		break;

	case FIRST_PHASE:
		current_animation_3 = &phase1;
		break;

	case SECOND_PHASE:
		current_animation_3 = &phase2;

		break;

	case THIRD_PHASE:
		current_animation_3 = &phase3;

	break;

	case SHOT_PHASE:

		if (ulti) {
			App->particles->AddParticle(App->particles->ulti_ayin, position.x + spot3, position.y - 30, COLLIDER_PLAYER_AYIN_ULTI);
			ulti = false;
		}

		break;


	}*/

	////ULTI 4
	//switch (state4) {
	//case NO_ULTI:
	//	current_animation_4 = &phase1;
	//	break;

	//case FIRST_PHASE:
	//	current_animation_4 = &phase1;
	//	break;

	//case SECOND_PHASE:
	//	current_animation_4 = &phase2;

	//	break;

	//case THIRD_PHASE:
	//	current_animation_4 = &phase3;

	//	break;

	//case SHOT_PHASE:

	//	if (ulti) {
	//		App->particles->AddParticle(App->particles->ulti_ayin, position.x + spot4, position.y - 30, COLLIDER_PLAYER_AYIN_ULTI);
	//		ulti = false;
	//	}

	//	break;


	//}
}