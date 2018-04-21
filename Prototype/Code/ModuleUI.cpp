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
#include <string>


ModuleUI::ModuleUI()
{
	player1.x = 8;
	player1.y = 6;
	player1.w = 15;
	player1.h = 9;

	player2.x = 26;
	player2.y = 6;
	player2.w = 16;
	player2.h = 9;

	life_sho.x = 24;
	life_sho.y = 174;
	life_sho.w = 15;
	life_sho.h = 13;
}

ModuleUI::~ModuleUI()
{}

// Load assets
bool ModuleUI::Start()
{
	LOG("Loading UI");
	time = 9;
	graphics = App->textures->Load("assets/sprites/UI/UI.png");
	black = App->textures->Load("assets/sprites/UI/black.png");
	font_score = App->fonts->Load("assets/sprites/UI/score_fonts.png", "0123456789", 1);
	font_time = App->fonts->Load("assets/sprites/UI/fonts/time_fonts.png", "0123456789", 1);
	return true;
}

// UnLoad assets
bool ModuleUI::CleanUp()
{
	LOG("Unloading UI");
	App->fonts->UnLoad(font_time);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(black);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleUI::Update()
{
	//Draw UI Score
	sprintf_s(player1_score, 10, "%7d", score_koyori);
	sprintf_s(player2_score, 10, "%7d", score_sho);

	sprintf_s(time_text, 2, "%1d", time);

	//Draw Top UI Interface
	current_animation = &start;
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Player1
	if (!game_over_koyori) {
		App->render->Blit(graphics, 10, 6, &player1, 0.00);
		App->fonts->BlitText(18, 5, font_score, player1_score);

		//Life Koyori
		for (int i = 1; i <= num_life_koyori - 1; i++) {
			App->render->Blit(graphics, 76 + life_koyori.w*i, 1, &life_koyori, 0.00f);
		}
	}
	else {
		App->render->Blit(graphics, 35, 10, &r, 0.00f);
	}

	//Player2
	if (!game_over_sho && App->player2->IsEnabled()) {
		App->render->Blit(graphics, 170, 5, &player2, 0.00);
		App->fonts->BlitText(180, 5, font_score, player2_score);

		//Life Sho
		for (int i = 1; i <= num_life_sho - 1; i++) {
			App->render->Blit(graphics, 236 + life_sho.w*i, 1, &life_sho, 0.00f);
		}
	}
	else {
		App->render->Blit(graphics, 210, 10, &r, 0.00f);
	}

	//Game over
	SDL_SetTextureAlphaMod(black, alpha);

	if (game_over_koyori && game_over_sho) {
		//Time countdown

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
		App->render->Blit(black, 0, 0, &screen, 0.00f);
		App->render->Blit(graphics, 100, 90, &game_over, 0.00f);
		App->fonts->BlitText(180, 115, font_time, time_text);
		App->render->Blit(black, 0, 0, &screen, 0.00f);
		if (time == 0) {
			App->fade->FadeToBlack(App->scene_water, App->scene_start);
		}
	}

	return UPDATE_CONTINUE;
}