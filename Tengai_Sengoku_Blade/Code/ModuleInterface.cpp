#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSceneWater.h"
#include "ModuleSceneScore.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleInterface.h"
#include <string>
#include "CharSelec.h"

ModuleInterface::ModuleInterface()
{
	player1.x = 8;
	player1.y = 6;
	player1.w = 15;
	player1.h = 9;

	player2.x = 26;
	player2.y = 6;
	player2.w = 16;
	player2.h = 9;

	//Start Animation
	start.PushBack({ 44,150,67,15 });
	start.PushBack({ 5,50,67,15 });
	start.PushBack({});
	start.speed = 0.03f;

	game_over.x = 116;
	game_over.y = 153;
	game_over.w = 123;
	game_over.h = 38;

	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;

	life_katana.x = 48;
	life_katana.y = 174;
	life_katana.w = 14;
	life_katana.h = 17;

	life_ayin.x = 71;
	life_ayin.y = 174;
	life_ayin.w = 16;
	life_ayin.h = 17;

	ulti.PushBack({7, 19, 15, 16});
	ulti.PushBack({23, 19, 15, 16});
	ulti.speed = 0.12f;

	//ulti.x = 7;
	//ulti.y = 19;
	//ulti.w = 15;
	//ulti.h = 16;


}

ModuleInterface::~ModuleInterface()
{}

// Load assets
bool ModuleInterface::Start()
{
	LOG("Loading UI");
	time = 9;
	graphics = App->textures->Load("assets/sprites/UI/UI.png");
	black = App->textures->Load("assets/sprites/UI/black.png");
	font_score = App->fonts->Load("assets/sprites/UI/score_fonts.png", "0123456789", 1);
	font_time = App->fonts->Load("assets/sprites/UI/time_fonts.png", "0123456789", 1);
	return true;
}

// UnLoad assets
bool ModuleInterface::CleanUp()
{
	LOG("Unloading UI");
	App->fonts->UnLoad(font_time);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(black);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleInterface::Update()
{
	//App->fonts->(0, 0, font_score, "godmode");
	if (App->charmenu->P1katana && App->charmenu->P2ayin) UIstate = P2KATANAAYIN;
	else if (App->charmenu->P1ayin && App->charmenu->P2katana) UIstate = P2AYINKATANA;
	else if (App->charmenu->P1katana) UIstate = P1KATANA;
	else if (App->charmenu->P1ayin) UIstate = P1AYIN;
	//Draw UI Score
	

	sprintf_s(time_text, 2, "%1d", time);

	//Draw Top UI Interface
	current_animation = &start;
	current_animation_2 = &ulti;
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect r1 = current_animation_2->GetCurrentFrame();

	switch (UIstate) {
	case P1KATANA:
		//Player1: katana
		sprintf_s(player1_score, 10, "%1d", score_katana);

		if (!game_over_katana && App->katana->IsEnabled()) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(30, 5, font_score, player1_score);

			//Life Katana
			for (int i = 1; i <= num_life_katana - 1; i++) {
				App->render->Blit(graphics, 76 + life_katana.w*i, 1, &life_katana, 0.00f, 0.00f);
			}
			//Ulti Katana
			for (int i = 1; i <= num_ult_katana; i++) {
				App->render->Blit(graphics, 15*i - 6, 15, &r1, 0.00f, 0.00f);
			}
		}
		
			App->render->Blit(graphics, 210, 10, &r, 0.00f, 0.00f); //Can't be possible (start where p1 is APPART!!!!!!! ENRECORDAT GERARD
		
		break;
	
	
	case P1AYIN:
		sprintf_s(player1_score, 10, "%1d", score_ayin);

		if (!game_over_ayin && App->ayin->IsEnabled()) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(30, 5, font_score, player1_score);

			for (int i = 1; i <= num_life_ayin - 1; i++) {
				App->render->Blit(graphics, 76 + life_ayin.w*i, 1, &life_ayin, 0.00f, 0.00f);
			}
			//Ulti Ayin
			for (int i = 1; i <= num_ult_ayin; i++) {
				App->render->Blit(graphics, 15 * i - 6, 15, &r1, 0.00f, 0.00f);
			}
		}

		App->render->Blit(graphics, 210, 10, &r, 0.00f, 0.00f);
		break;

		//Player2: ayin

	case P2KATANAAYIN:
		sprintf_s(player1_score, 10, "%1d", score_katana);
		sprintf_s(player2_score, 10, "%1d", score_ayin);
		if (!game_over_katana && App->katana->IsEnabled()) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(30, 5, font_score, player1_score);

			//Life Katana
			for (int i = 1; i <= num_life_katana - 1; i++) {
				App->render->Blit(graphics, 76 + life_katana.w*i, 1, &life_katana, 0.00f, 0.00f);
			}
		}
		if (!game_over_ayin && App->ayin->IsEnabled()) {
			App->render->Blit(graphics, 170, 5, &player2, 0.00f, 0.00f);
			App->fonts->BlitText(215, 5, font_score, player2_score);

			//Life ayin
			for (int i = 1; i <= num_life_ayin - 1; i++) {
				App->render->Blit(graphics, 236 + life_ayin.w*i, 1, &life_ayin, 0.00f, 0.00f);
			}
		}

	
			//App->render->Blit(graphics, 35, 10, &r, 0.00f, 0.00f); //start till p2 is enable
		

		break;

	case P2AYINKATANA:
		sprintf_s(player1_score, 10, "%1d", score_ayin);
		sprintf_s(player2_score, 10, "%1d", score_katana);
		if (!game_over_ayin && App->ayin->IsEnabled()) {
			App->render->Blit(graphics, 10, 6, &player1, 0.00f, 0.00f);
			App->fonts->BlitText(30, 5, font_score, player1_score);

			for (int i = 1; i <= num_life_ayin - 1; i++) {
				App->render->Blit(graphics, 76 + life_ayin.w*i, 1, &life_ayin, 0.00f, 0.00f);
			}
		}

		if (!game_over_katana && App->katana->IsEnabled()) {
			App->render->Blit(graphics, 170, 5, &player2, 0.00f, 0.00f);
			App->fonts->BlitText(215, 5, font_score, player2_score);

			//Life Katana
			for (int i = 1; i <= num_life_katana - 1; i++) {
				App->render->Blit(graphics, 236 + life_katana.w*i, 1, &life_katana, 0.00f, 0.00f);
			}
		}
		break;
	}

	
	//Game over
	SDL_SetTextureAlphaMod(black, alpha);

	if (game_over_katana && game_over_ayin || game_over_katana &&  !App->ayin->IsEnabled() || game_over_ayin &&  !App->katana->IsEnabled()) {
		//Time countdown
		App->scene_temple->speed = 0;

		if (aux) {
			time_on_entry = SDL_GetTicks();
			aux = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1000) {
			time--;
			aux = true;
		}

		//Disable
		enemies_movement = false;

		//Draw
		alpha = 100;
		App->render->Blit(black, 0, 0, &screen, 0.00f, 0.00f);
		App->render->Blit(graphics, 100, 90, &game_over, 0.00f, 0.00f);
		App->fonts->BlitText(180, 115, font_time, time_text);
		App->render->Blit(black, 0, 0, &screen, 0.00f, 0.00f);
		if (time == 0) {
			App->fade->FadeToBlack(App->scene_temple, App->scene_start);
		}
	}



	return UPDATE_CONTINUE;
}