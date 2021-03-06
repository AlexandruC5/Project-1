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
		Ayin1 = true;
		Ayin2 = false;
	}
	if (App->charmenu->P2ayin) {
		App->ayin->Enable();
		Ayin1 = false;
		Ayin2 = true;
	}

	graphics = App->textures->Load("assets/sprites/Scenes/Scene_Temple/templemap.png");

	
	

	
	//App->enemies->AddEnemy(ENEMY_TYPES::Power_up, 400, 150,1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Ulti_parchment, 400, 50,1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 400, 80, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 810, 30, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 850, 160, 2);

	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 550, 15, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 560, 45, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 570, 75, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::RED, 580, 105, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 1080, 90, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 1070, 120, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 1060, 150, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::RED, 1050, 180, 1);

	//App->enemies->AddEnemy(ENEMY_TYPES::Ball, 430, 50, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Chariot, 430, 50, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Pagoda, 430, 50, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1200, 40, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1240, 140, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1300, -40, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1320, -40, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1340, -40, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1360, -40, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1380, -40, 3); 

	
	App->enemies->AddEnemy(ENEMY_TYPES::SharpenerKnife, 1300, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1900, 40, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1920, 40, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1950, 140, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 1970, 140, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2220, -40, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2230, -40, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2240, -40, 4);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2250, -40, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2260, -40, 3);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 2220, 90, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 2240, 20, 3);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 2260, 160, 2);

	/*App->enemies->AddEnemy(ENEMY_TYPES::Coin, 2300, 230, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::Coin, 2320, 230, 2);
	App->enemies->AddEnemy(ENEMY_TYPES::Coin, 2340, 230, 2);*/

	App->enemies->AddEnemy(ENEMY_TYPES::Pagoda, 2265, 60, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2650, 40, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2650, 140, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2820, 40, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::DemonWheel, 2820, 140, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::Ball2, 3560, 80, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Chariot, 3600, 50, 1);

	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 3620, 170, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::Green2, 3640, 185, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Ball2, 430, 90, 2);

	//App->enemies->AddEnemy(ENEMY_TYPES::DemonPegTop, 580, 80, 1);
	//App->enemies->AddEnemy(ENEMY_TYPES::Demon, 450, 300, 1);

	//App->enemies->AddEnemy(ENEMY_TYPES::Coin, 2350, 100, 1);


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
				//boss = true;
			
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
		//speed = 6;
		//speed_activation = true;
		//katana_speed = 10.0;
		
	
	}
	
	if (App->render->camera.x > 950000) {

		if (aux_time < 120)
		{
			//speed = 0;
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

	 if (App->input->keyboard[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN) App->fade->FadeToBlack(this, App->scene_loose, 1);
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

void ModuleSceneTemple::ResetPosition() {

	 posx = 0, 
	 posy = 0;
	 posx2 = 390, posy2 = 2;
	 posy3 = 0;
	 pos4 = 224;
	 pos5 = 491;
	 speed = 1.5;


}

void ModuleSceneTemple::StopCamera() {

	speed = 0;

}


