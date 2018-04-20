#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleUI.h"
#include "ModuleSceneWater.h"
 //#include "ModuleSceneScore.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"
#include <string>


ModuleUI::ModuleUI() {
	player1.x = 8;
	player1.y = 6;
	player1.w = 15;
	player1.h = 9;

	start.PushBack({ 44, 150, 67, 15 });
	start.PushBack({ 5, 50, 67, 15 });
	start.PushBack({});
	start.speed = 0.04f;

	game_over.x = 116;
	game_over.y = 153;
	game_over.w = 123;
	game_over.h = 38;

	screen.x = 0;
	screen.y = 0;
	screen.w = SCREEN_WIDTH;
	screen.h = SCREEN_HEIGHT;

	life_miko.x = 4;
	life_miko.y = 173;
	life_miko.w = 16;
	life_miko.h = 14;
}

bool ModuleUI::Start()
{
	LOG("Loading UI");
	time = 9;
	graphics = App->textures->Load("assets/sprite/UI.png");
	black = App->textures->Load("assets/sprite/black.png");
	font_score = App->fonts->Load("assets/sprites/UI/score_fonts.png", "0123456789", 1);
	font_time = App->fonts->Load("assets/sprites/UI/çtime_fonts.png", "0123456789", 1);
	return true;
}