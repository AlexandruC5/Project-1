#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneAir.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#include "ModuleWelcomeScreen.h"
#include "ModulePlayer.h"


ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	//Main Components
	title = { 34, 4, 247, 187 };
	background = { 0, 0, 320, 224 };
	company1 = { 13, 198, 163, 14 };
	company2 = { 180, 200, 111, 12 };
	start_button = { 89, 108, 140, 13};
	
	//Layers
	bg1_rect = { 0, 331, 510, 43 };
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{
}

bool ModuleWelcomeScreen::Init() {

	bool ret = true;

	scroll = 0;
	scroll2 = 0;
	

	return ret;
}
bool ModuleWelcomeScreen::Start()
{


	//Reseting camera positions
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	//Loading main sprites
	graphics = App->textures->Load("assets/sprites/UI/WelcomeScreen/button_start.png");
	graphics2 = App->textures->Load("assets/sprites/UI/WelcomeScreen/background.png");
	graphics3 = App->textures->Load("assets/sprites/UI/WelcomeScreen/title&text.png");

	//Loading sprite layers
	bg1 = App->textures->Load("assets/sprites/UI/WelcomeScreen/components/waves.png");
	
	//Loading Music
	music = App->audio->LoadMusic("assets/audio/music/01_Gem_of_hope.ogg");
	Mix_PlayMusic(music, -1);

	return true;
}

update_status ModuleWelcomeScreen::Update()
{
	// Switching between scenes
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->scene_air, 2);

	//Draw main components respecting its order
	App->render->Blit(graphics2, 0, 0, &background);
	App->render->Blit(graphics3,40, 6, &title);
	App->render->Blit(graphics, 15, 200, &company1);
	App->render->Blit(graphics, 180, 202, &company2);
	App->render->Blit(graphics, 95, 110, &start_button);
	
	// Background scrolls

	//Layer1 scrolling (doesn't work)

	scroll -= 3;
	if (scroll <= -bg1_rect.w) {
		scroll = 0;
	}
	scroll2 = scroll;

	App->render->Blit(bg1, scroll, 202, &bg1_rect, 0.90f);
	App->render->Blit(bg1, scroll, 103, &bg1_rect, 0.10f);

	//bg1_rect.x += bg1_rect.w;
	scroll2 += bg1_rect.w;

	App->render->Blit(bg1, scroll2, 202, &bg1_rect, 0.90f);
	App->render->Blit(bg1, scroll2, 103, &bg1_rect, 0.10f);

	/*
	timer++;
	if (timer >= 10) {
		App->render->Blit(graphics, 95, 110, &start_button);
		SDL_Delay(3000);
		timer = 0;
	}
	*/
	/*
	
	if(aux <= time && print)
	{
		App->render->Blit(graphics, 95, 110, &start_button);
	 	aux++;
	}else{

		print = false;
		aux--;
		if(aux == 0) print=true;
	}
	*/
	return update_status::UPDATE_CONTINUE;
}

bool ModuleWelcomeScreen::CleanUp()
{
	//Unloading textures
	App->textures->Unload(graphics);
	graphics = nullptr;

	//Unloading Audio
	App->audio->UnloadMusic(music);
	music = nullptr;

	return true;
}

