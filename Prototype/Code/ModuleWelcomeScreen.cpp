#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneAir.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleWelcomeScreen.h"
#include "ModulePlayer.h"

ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	int time = 20;
	int aux = 0;
	bool print = true;
	title = { 10, 248, 252, 194 };
	background = { 8, 8, 326, 229 };
	company1 = { 22, 453, 158, 22 };
	company2 = { 184, 454, 116, 17 };
	start_button = { 24, 480, 147, 17 };
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{
}

bool ModuleWelcomeScreen::Start()
{
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->position.x = 0;
	App->player->position.y = 100;

	graphics = App->textures->Load("assets/sprites/UI/WelcomeScreen/WelcomeScreen4.png");
	

	music = App->audio->LoadMusic("assets/audio/music/01_Gem_of_hope.ogg");
	Mix_PlayMusic(music, -1);

	return true;
}

update_status ModuleWelcomeScreen::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->scene_air, 2);

	App->render->Blit(graphics, 0, 0, &background);
	App->render->Blit(graphics, 35, 3, &title);
	App->render->Blit(graphics, 15, 203, &company1);
	App->render->Blit(graphics, 180, 205, &company2);
	
	if(aux <= time && print)
	{
	 	App->render->Blit(graphics, 87, 110, &start_button);	
	 	aux++;
	}else{
		print = false;
		aux--;
		if(aux == 0)print=true;
	}
		
	return update_status::UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	App->textures->Unload(graphics);
	graphics = nullptr;

	App->audio->UnloadMusic(music);
	music = nullptr;

	return true;
}

