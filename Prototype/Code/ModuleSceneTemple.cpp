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

#include "ModuleSceneTemple.h"

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

	//App->player->Enable();
	//App->powerup->Enable();
	App->enemies->Enable();
	//App->particles->Enable();
	//App->collision->Enable();

	graphics = App->textures->Load("assets/sprites/Scenes/Scene_Temple/templemap.png");

	App->enemies->AddEnemy(ENEMY_TYPES::RED, 450, 50);
	
	return true;

}

update_status ModuleSceneTemple::Update()
{
	
	int aux = 1168;

	App->render->Blit(graphics, 0, 0, &Mountains, 0.30f);
	App->render->Blit(graphics, posx2, posy2, &Statue, 0.35F);
	App->render->Blit(graphics, posx, posy, &Gateway, 0.45f);
	

	for (int i = 0; i < 8; i++) {
		App->render->Blit(graphics, aux, posy3, &scroll_bg, 0.45f);
		App->render->Blit(graphics, aux, pos4, &scroll_down, 0.45f);

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
				else speed = 2;
			}
			
			
		}
	}

	
	//Camera Events

	if (App->render->camera.x > 2180 && App->render->camera.x < 3202) {
		
		posx -= 0.0025*speed;
		posy -= 0.22*speed;

		posx2 -= 0.0025*speed;
		posy2 -= 0.22*speed;

		speed = 2;
	}

	if (App->render->camera.x > 3800 && App->render->camera.x <= 11500) {
		speed = 16.5;
	}
	
	if (App->render->camera.x > 11500) {

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
	App->render->camera.x += speed;


	
	return UPDATE_CONTINUE;
}


bool ModuleSceneTemple::CleanUp()
{
	//App->player->Disable();
	//App->player2->Disable();
	//App->collision->Disable();
	//App->particles->Disable();
	//App->enemies->Disable();

	App->textures->Unload(graphics);
	
	return true;
}


