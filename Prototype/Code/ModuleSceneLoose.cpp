#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleSceneLoose.h"
#include "ModuleFadeToBlack.h"
#include"ModulePowerUPS.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"

ModuleLooseScreen::ModuleLooseScreen() {
	background = {0,0,320,224};


}

ModuleLooseScreen::~ModuleLooseScreen(){}


bool ModuleLooseScreen::Start() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	
	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Loose/score.png");
	return true;
}

update_status ModuleLooseScreen::Update() {
	App->render->Blit(graphics1, 0, 0, &background);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, App->scene_start, 2);

	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleLooseScreen::CleanUp() {
	App->textures->Unload(graphics1);
	graphics1 = nullptr;
	return true;
}