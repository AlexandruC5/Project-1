#include "Globals.h"
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneWater.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleEnemies.h"
#include "ModulePowerUPS.h"
#include "ModulePlayer2.h"
#include "WinScreen.h"
#include "ModuleSceneLoose.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleKatanaArrow.h"
#include "ModuleSceneTemple.h"
#include "ModuleCollision.h"
#include "CharSelec.h"

#include "ModuleInterface.h"


ModuleSceneTemple::ModuleSceneTemple()
{

	//Mountains
	Mountains.x = 1208;
	Mountains.y = 65;
	Mountains.w = 320;
	Mountains.h = 224;

	//Gateway
	Gateway.x = 313;
	Gateway.y = 794;
	Gateway.w = 1198;
	Gateway.h = 448;

	//Statue
	Statue.x = 306;
	Statue.y = 18;
	Statue.w = 473;
	Statue.h = 444;

	//Scroll bg
	scroll_bg.x = 15;
	scroll_bg.y = 17;
	scroll_bg.w = 256;
	scroll_bg.h = 224;

	//Scroll down
	scroll_down.x = 843;
	scroll_down.y = 39;
	scroll_down.w = 320;
	scroll_down.h = 581;

	//Scroll bg 2
	scroll_final.x = 1230;
	scroll_final.y = 360;
	scroll_final.w = 256;
	scroll_final.h = 224;

}

ModuleSceneTemple::~ModuleSceneTemple()
{
}

bool ModuleSceneTemple::Start()
{
	LOG("Loading Temple Scene");
	player2 = false;
	//App->player->Enable();
	//App->powerup->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->inter->Enable();

	App->inter->score_katana = 0;
	App->inter->score_ayin = 0;


	//App->ayin->Enable();
	//if (App->charmenu->player1) {


	


	if (App->charmenu->P1katana) {
		App->katana->Enable();
	}
	if (App->charmenu->P2katana) {
		App->katana->Enable();
	}
	if (App->charmenu->P1ayin) {
		App->ayin->Enable();
	}
	if (App->charmenu->P2ayin) {
		App->ayin->Enable();
	}

	graphics = App->textures->Load("assets/sprites/Scenes/Scene_Temple/templemap.png");

	
	//App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop,400,50);

	//App->enemies->AddEnemy(ENEMY_TYPES::SharpenerKnife, 500, 50);
	/*App->enemies->AddEnemy(ENEMY_TYPES::Power_up, 400, 150,1);
	App->enemies->AddEnemy(ENEMY_TYPES::Ulti_parchment, 400, 50,1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 380, 80, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 810, 30, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 850, 160, 2);

	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 600, 15, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 610, 45, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 620, 75, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::RED, 630, 105, 1);*/

	//App->enemies->AddEnemy(ENEMY_TYPES::Ball, 430, 50, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Chariot, 430, 50, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Pagoda, 430, 50, 1);

	//App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 630, 105, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 430, -40, 2);

	//App->enemies->AddEnemy(ENEMY_TYPES::Ball2, 430, 90, 2);

	//App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 580, 80, 1);

	coll_up = App->collision->AddCollider({ 0, 0, 99000, SCREEN_HEIGHT - 220 }, COLLIDER_WALL);
	coll_down = App->collision->AddCollider({ 0, SCREEN_HEIGHT - 4, 990000, 16 }, COLLIDER_WALL);
	coll_left = App->collision->AddCollider({ 0,0,0,SCREEN_HEIGHT }, COLLIDER_WALL);
	coll_right = App->collision->AddCollider({ SCREEN_WIDTH,0, 0,SCREEN_HEIGHT }, COLLIDER_WALL);

	return true;

}

update_status ModuleSceneTemple::Update()
{
	//Update Collision
	coll_left->SetPos(App->render->camera.x / SCREEN_SIZE, 0);
	coll_right->SetPos(SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE, 0);
	
	int aux = 1171;

	App->render->Blit(graphics, 0, 0, &Mountains,bg_speed*3/* 0.30f*/);
	App->render->Blit(graphics, posx2, posy2, &Statue, bg_speed*3.5/*0.35F*/);
	App->render->Blit(graphics, posx, posy, &Gateway, bg_speed*4.5/*0.45f*/);
	

	for (int i = 0; i < 15; i++) {
		App->render->Blit(graphics, aux, posy3, &scroll_bg, bg_speed*4.5/*0.45f*/);
		App->render->Blit(graphics, aux, pos4, &scroll_down, bg_speed*4.5/*0.45f*/);

		aux += scroll_bg.w;

		if (transition) {

			if (aux_time2 < 1860) {
				posy3 -= 0.3;
				pos4 -= 0.3;
				aux_time2++;
				
			}

			else {
				transition = false;
				if (aux_time3 < 300) {
					aux_time3++;
				}
				else speed = 1.5;
			}
			
			
		}
	}

	
	//Camera Events

	if (App->render->camera.x > 1090 && App->render->camera.x < 1591) {

		
		
		posx -= 0.0020*speed;
		posy -= 0.3*speed;

		posx2 -= 0.0020*speed;
		posy2 -= 0.3*speed;

		speed = 1.5;





		/*posx -= 0.0025*speed;
		posy -= 0.22*speed;

		posx2 -= 0.0025*speed;
		posy2 -= 0.22*speed;

		speed = 2;*/
	}

	if (App->render->camera.x > 1750 && App->render->camera.x <= 9500) {
		//App->katana->speed = 10;
		speed = 6;
		speed_activation = true;
		//katana_speed = 10.0;
		
	
	}
	
	if (App->render->camera.x > 9500) {

		if (aux_time < 120)
		{
			speed = 0;
			aux_time++;
		}
		else
		{
			transition = true;

			if (change) {
				pos4 = 205;
				change = false;
			}
			
		}

	}
	
	//Camera movement
	if (!speed_activation) {
		App->katana->position.x += speed / 1.5;
		App->ayin->position.x += speed / 1.5;
	}
	else {
		App->katana->position.x += speed;
		App->ayin->position.x += speed;
	}
		App->render->camera.x += speed;

		//Enable Players
		//if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN) {
		//	if (!App->ayin->IsEnabled()) {
		//		//App->audio->PlaySoundEffects(select_sho);
		//		App->ayin->Enable();
		//	}
		//}

     if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {

			App->fade->FadeToBlack(this, App->scene_win, 2);

		}

	 if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		 App->collision->GodMode();
	 }

		/*if (App->input->keyboard[SDL_SCANCODE_R] == KEY_STATE::KEY_DOWN) {
			App->inter->num_life_katana--;
		}*/
	return UPDATE_CONTINUE;
}


bool ModuleSceneTemple::CleanUp()
{
	//App->player->Disable();
	//App->player2->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();
	//App->katana->Disable();
	App->textures->Unload(graphics);
	App->inter->Disable();

	if (App->katana->IsEnabled()) {
		App->katana->Disable();
	}

	if (App->ayin->IsEnabled()) {
		App->ayin->Disable();
	}
	return true;
}


