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

	

	title = { 34, 4, 247, 187 };
	//title = { 1, 4, 211, 162 };
	background = { 0, 0, 320, 224 };

	company1 = { 13, 198, 163, 14 };
	//company1 = { 1, 181, 141, 13 };
	company2 = { 180, 200, 111, 12 };
	//company2 = { 3, 195, 94, 12 };

	start_button = { 89, 108, 140, 13};
	//start_button = { 1, 167, 124, 13 };

}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{
}

bool ModuleWelcomeScreen::Init() {

	bool ret = true;

	int time = 60;
	int aux = 0;
	bool print = true;

	return ret;
}
bool ModuleWelcomeScreen::Start()
{
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->position.x = 0;
	App->player->position.y = 100;

	graphics = App->textures->Load("assets/sprites/UI/WelcomeScreen/components/button_start.png");
	graphics2 = App->textures->Load("assets/sprites/UI/WelcomeScreen/components/background.png");
	graphics3 = App->textures->Load("assets/sprites/UI/WelcomeScreen/components/title&text.png");
	music = App->audio->LoadMusic("assets/audio/music/01_Gem_of_hope.ogg");
	Mix_PlayMusic(music, -1);

	return true;
}

update_status ModuleWelcomeScreen::Update()
{


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->scene_air, 2);

	App->render->Blit(graphics2, 0, 0, &background);
	App->render->Blit(graphics3,40, 6, &title);
	App->render->Blit(graphics, 15, 200, &company1);
	App->render->Blit(graphics, 180, 202, &company2);

	//App->render->Blit(graphics, 180, 210, &start_button);
	

	
	if(aux <= time && print)
	{
	 	//App->render->Blit(graphics, 87, 110, &start_button);	
	 	aux++;
	}else{

		App->render->Blit(graphics, 95, 110, &start_button);
		print = false;
		aux--;
		if(aux == 0) print=true;
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

