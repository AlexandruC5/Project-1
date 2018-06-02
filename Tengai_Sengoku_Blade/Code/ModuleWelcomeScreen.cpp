#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneWater.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"
#include "ModuleWelcomeScreen.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include"ModulePowerUPS.h"
#include"WinScreen.h"
#include"ModuleSceneLoose.h"
#include "ModuleSceneTemple.h"
#include "CharSelec.h"

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
	bg2_rect = { 0, 415, 512, 29 };
	bg3_rect = { 31, 89, 448, 24 };
	bg4_rect = { 0, 133, 513, 10 };
	bg5_rect = { 0, 162, 511, 8 };
	bg6_rect = { 0, 190, 507, 8 };
	bg7_rect = { 0, 213, 502, 4 };
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{
}

bool ModuleWelcomeScreen::Init() {

	bool ret = true;
	
	int aux = 35;
	bool print = true;

	scroll = -18.0;
	scroll2 = -18.0;

	scroll3 = -15.0;
	scroll4 = -15.0;

	scroll5 = -12.0;
	scroll6 = -12.0;

	scroll7 = -9.0;
	scroll8 = -9.0;

	scroll9 = -6.0;
	scroll10 = -6.0;

	scroll11 = -3.0;
	scroll12 = -3.0;

	scroll13 = 0.0;
	scroll14 = 0.0;
	

	return ret;
}
bool ModuleWelcomeScreen::Start()
{
	App->player2->Disable();

	//Reseting camera positions
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	App->scene_win->Disable();
	App->scene_loose->Disable();
	App->powerup->Disable();
	App->charmenu->Disable();
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
	//if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) == 1 || SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_A) == 1) App->fade->FadeToBlack(this, App->scene_temple, 2);
	bool press_Button_start = SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_START);
	bool press_Button2_start = SDL_GameControllerGetButton(App->input->gamepad2, SDL_CONTROLLER_BUTTON_START);
	//if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) App->fade->FadeToBlack(this, App->scene_water, 2);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, App->charmenu, 1);
		App->scene_temple->ResetPosition();
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) App->fade->FadeToBlack(this, App->scene_win, 1);
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) App->fade->FadeToBlack(this, App->scene_loose, 1);

	if (press_Button_start || press_Button2_start) App->fade->FadeToBlack(this, App->charmenu, 1);

	//Draw Background
	App->render->Blit(graphics2, 0, 0, &background);
	
	
	// Background scrolls


	//Layer 7
	scroll13 -= 0.5f;
	if (scroll13 <= -bg7_rect.w) {
		scroll13 = 0;
	}
	scroll14 = scroll13;

	App->render->Blit(bg1, (int)scroll13, 127, &bg7_rect);


	scroll14 += bg7_rect.w;

	App->render->Blit(bg1, (int)scroll14, 127, &bg7_rect);

	//Layer 6
	scroll11 -= 0.75f;
	if (scroll11 <= -bg6_rect.w) {
		scroll11 = 0;
	}
	scroll12 = scroll11;

	App->render->Blit(bg1, (int)scroll11, 132, &bg6_rect);

	
	scroll12 += bg6_rect.w;

	App->render->Blit(bg1, (int)scroll12, 132, &bg6_rect);

	//Layer 5
	scroll9 -= 1.00f;
	if (scroll9 <= -bg5_rect.w) {
		scroll9 = 0;
	}
	scroll10 = scroll9;

	App->render->Blit(bg1, (int)scroll9, 138, &bg5_rect);

	
	scroll10 += bg5_rect.w;

	App->render->Blit(bg1, (int)scroll10, 138, &bg5_rect);


	//Layer 4
	scroll7 -= 1.25;
	if (scroll7 <= -bg4_rect.w) {
		scroll7 = 0;
	}
	scroll8 = scroll7;

	App->render->Blit(bg1, (int)scroll7, 146, &bg4_rect);

	
	scroll8 += bg4_rect.w;

	App->render->Blit(bg1, (int)scroll8, 146, &bg4_rect);



	//Layer 3
	scroll5 -= 1.5;
	if (scroll5 <= -bg3_rect.w) {
		scroll5 = 0;
	}
	scroll6 = scroll5;

	App->render->Blit(bg1, (int)scroll5, 156, &bg3_rect);

	scroll6 += bg3_rect.w;

	App->render->Blit(bg1, (int)scroll6, 156, &bg3_rect);


	//Layer 2
	scroll3 -= 1.75f;
	if (scroll3 <= -bg2_rect.w) {
		scroll3 = 0;
	}
	scroll4 = scroll3;

	App->render->Blit(bg1, (int)scroll3, 164, &bg2_rect);

	
	scroll4 += bg2_rect.w;

	App->render->Blit(bg1, (int)scroll4, 164, &bg2_rect);


	//Layer 1
	scroll -= 2.0f;
	if (scroll <= -bg1_rect.w) {
		scroll = 0;
	}
	scroll2 = scroll;

	App->render->Blit(bg1, (int)scroll, 180, &bg1_rect);

	//bg1_rect.x += bg1_rect.w;
	scroll2 += bg1_rect.w;

	App->render->Blit(bg1, (int)scroll2, 180, &bg1_rect);

	// Draw main components
	App->render->Blit(graphics3,35, 6, &title);
	App->render->Blit(graphics, 15, 200, &company1);
	App->render->Blit(graphics, 180, 202, &company2);
	

	// Draw blinker start button
	if (print)
	{
		App->render->Blit(graphics, 95, 110, &start_button);
		aux--;
		if (aux <= 0)print = false;
	}
	else {
		aux++;
		if (aux >= 35)print = true;
	}
	
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

