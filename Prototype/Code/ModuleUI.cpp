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
	font_time = App->fonts->Load("assets/sprites/UI/time_fonts.png", "0123456789", 1);
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
	App->fonts->(0, 0, font_score, "godmode");


	return UPDATE_CONTINUE;
}