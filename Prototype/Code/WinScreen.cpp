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


	//path.PushBack{0,155}
}

ModuleWinScreen::~ModuleWinScreen() {}


bool ModuleWinScreen::Init() {
	goUP = 0.0f;
	goDown = 100.0f;
	MaxDown = 155;
	MaxUp = -47;
	U = -2.0f;
	M = 0.0f;
	goright = -100;
	maxr = 10;
	goleft1 = 0;
	goleft2 = sky2.w;//distancia2
	maxleft1 = -sky.w;
	maxleft2 = -sky2.w - sky2.w;
	Welcome = false;
	fade = false;
	return true;
}
bool ModuleWinScreen::Start() {

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Background.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Katanawinsheet.png");
	Winfade = App->audio->LoadMusic("assets/audio/music/Level_Completed.ogg");
	Mix_PlayMusic(Winfade, 1);

	return true;
}

void ModuleWinScreen::move() {

}


update_status ModuleWinScreen::Update() {
	fade = false;
	if (goleft1 >= maxleft1) {
		goleft1 -= 1;
		if (goleft1 <= maxleft1/2.0) Welcome = true;
	}

	else if (goleft1 <= maxleft1/5.0) {
		goleft1 = sky2.w;
		Welcome = true;
	}

	if (Welcome == true) {
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
		Welcome = false; //no fa el fade pero es reinicia tot
		fade = true;
	}
	if (fade == true)  App->fade->FadeToBlack(this, App->scene_start, 0.1);

	if (goleft2 >= maxleft2) goleft2 -= 1;
	/*else if (goleft2 <= maxleft2) {
	goleft2 = sky2.w;
	}*/

	App->render->Blit(graphics1, (int)goleft1, 60, &sky);
	App->render->Blit(graphics1, (int)goleft2, 60, &sky2);

	if (goUP >= MaxUp) {
		goUP -= 0.4f;
	}
	if (goDown <= MaxDown) {
		goDown += 0.4f;
	}
	if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
		if (M <= (up.h) / 5.0) { //katana down
			U += 0.4f;
			M += 0.4f;
		}

		else if (M >= (up.h) / 5.0) {//up
			U -= 0.4f;
			if (U < up.h / 5.0) { M = 0.0f; }
		}
	}
	App->render->Blit(graphics1, -5, (int)goUP, &up); //0, -47



	if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
		App->render->Blit(graphics2, 15, (int)U, &katana, 0.45f);
	}
	if (goUP <= MaxUp / 1.1 && goDown >= MaxDown / 1.1) {
		if (goright <= maxr) { goright += 2.0; }
	}
	App->render->Blit(graphics1, -3, (int)goDown, &down); //0,155
	App->render->Blit(graphics2, (int)goright, 170, &letters);//10,170



	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {

		App->fade->FadeToBlack(this, App->scene_start, 2);

	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleWinScreen::CleanUp() {
	App->textures->Unload(graphics1);
	graphics1 = nullptr;
	App->textures->Unload(graphics2);
	graphics2 = nullptr;
	App->audio->UnloadMusic(Winfade);
	Winfade = nullptr;
	return true;
}