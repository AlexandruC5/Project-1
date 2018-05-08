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
	up = { 193,0,319,112 };
	down = { 187, 268, 325, 114 };
	sky = { 196, 132, 316, 98 };
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
	return true;
}
bool ModuleWinScreen::Start() {

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Background2.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Katanawinsheet.png");
	Winfade = App->audio->LoadMusic("assets/audio/music/Level_Completed.ogg");
	Mix_PlayMusic(Winfade, 1);

	return true;
}

void ModuleWinScreen::move() {

}


update_status ModuleWinScreen::Update() {


	App->render->Blit(graphics1, 1.5f, 60, &sky);

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
	App->render->Blit(graphics1, 0, (int)goUP, &up); //0, -47



	if (goUP <= MaxUp / 2 && goDown >= MaxDown / 2) {
		App->render->Blit(graphics2, 15, (int)U, &katana, 0.45f);
	}
	if (goUP <= MaxUp / 1.1 && goDown >= MaxDown / 1.1) {
		if (goright <= maxr) { goright += 2.0; }
	}
	App->render->Blit(graphics1, 0, (int)goDown, &down); //0,155
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