#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFadeToBlack.h"
#include "WinScreen.h"
#include "ModuleSceneWater.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#include "CharSelec.h"

ModuleWinScreen::ModuleWinScreen() {
	up = { 185,0,327,112 };
	down = { 185, 268, 327, 114 };
	sky = { 55, 132, 457, 98 };
	sky2 = { 55,402,457,98 };
	/*up = { 193,0,319,112 };
	down = { 187, 268, 325, 114 };
	sky = { 54, 132, 458, 98 };
	sky2 = { 54,402,458,98 };*/
	letters = { 196,228,81,16 };
	katana = { 31,18,278,161 };
	//katana =  { 381,18,286,161 };
	Ayin = { 52,99,202,154 };

	//path.PushBack{0,155}
}




bool ModuleWinScreen::Start() {

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	goUP = 0.0f;
	goDown = 100.0f;
	MaxDown = 155;
	MaxUp = -47;
	U = -2.0f;
	M = 0.0f;
	goright = -100;
	maxr = 10;
	goleft1 = 0;
	goleft2 = sky2.w;
	maxleft1 = -sky.w;

	maxleft2 = -sky2.w - sky2.w;
	Welcome = false;
	fade = false;

	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Background.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Katanawinsheet.png");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Win/ayinwinsheet.png");
	Winfade = App->audio->LoadMusic("assets/audio/music/Level_Completed.ogg");

	Mix_PlayMusic(Winfade, 1);

	return true;
}




update_status ModuleWinScreen::Update() {
	//fade = false;
	if (goleft1 >= maxleft1) {
		goleft1 -= 1;
		if (goleft1 <= maxleft1 / 1.8) Welcome = true;
	}

	else if (goleft1 <= maxleft1 / 5.0) {
		goleft1 = sky2.w;
		Welcome = true;
	}

	if (Welcome == true)   App->fade->FadeToBlack(this, App->scene_start, 0.5);

	//CASE SEKECTOR
	if (App->charmenu->P1katana && App->charmenu->P2ayin) state = KATANA_AYIN;
	else if (App->charmenu->P1ayin && App->charmenu->P2katana) state = AYIN_KATANA;
	else if (App->charmenu->P1ayin) state = AYIN;
	else if (App->charmenu->P1katana) state = KATANA;


	if (goleft2 >= maxleft2) goleft2 -= 1;
	/*else if (goleft2 <= maxleft2) {
	goleft2 = sky2.w;
	}*/

	App->render->Blit(graphics1, (int)goleft1, 60, &sky);
	App->render->Blit(graphics1, (int)goleft2, 60, &sky2);

	if (goUP >= MaxUp) {
		goUP -= 0.9f;
	}
	if (goDown <= MaxDown) {
		goDown += 0.9f;
	}
	if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
		if (M <= (up.h) / 5.0) { //katana down
			U += 0.35f;
			M += 0.35f;
		}

		else if (M >= (up.h) / 5.0) {//up
			U -= 0.4f;
			if (U < up.h / 5.0) { M = 0.0f; }
		}
	}
	App->render->Blit(graphics1, -5, goUP, &up); //0, -47

												 //CASE KATANA
	switch (state) {
	case KATANA:
		if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
			App->render->Blit(graphics2, 15, U, &katana, 0.45f);
		}
		break;
	case AYIN:
		if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
			App->render->Blit(graphics3, 15, U, &Ayin, 0.45f);
		}

		break;

	case AYIN_KATANA:
		if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
			App->render->Blit(graphics2, 100, U, &katana, 0.45f);
			App->render->Blit(graphics3, -50, -U + 50, &Ayin, 0.45f);

		}
		break;

	case KATANA_AYIN:
		if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
			App->render->Blit(graphics3, 130, U, &Ayin, 0.45f);
			App->render->Blit(graphics2, -70, -U + 50, &katana, 0.45f);

		}
		break;
	}


	if (goUP <= MaxUp / 1.1 && goDown >= MaxDown / 1.1) {
		if (goright <= maxr) { goright += 2.0; }
	}
	App->render->Blit(graphics1, -3, (int)goDown, &down); //0,155
	App->render->Blit(graphics2, (int)goright, 170, &letters);//10,170



															  
	return update_status::UPDATE_CONTINUE;
}

bool ModuleWinScreen::CleanUp() {
	App->textures->Unload(graphics1);
	graphics1 = nullptr;
	App->textures->Unload(graphics2);
	graphics2 = nullptr;
	App->textures->Unload(graphics3);
	graphics3 = nullptr;
	App->audio->UnloadMusic(Winfade);
	Winfade = nullptr;
	return true;
}