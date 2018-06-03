#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleWelcomeScreen.h"
#include "WinScreen.h"
#include "ModuleSceneLoose.h"
#include"ModulePowerUPS.h"
#include "CharSelec.h"
ModuleSceneIntro::ModuleSceneIntro()
{
	// Psikyo
	s1 = {1730,0,323,227 };
	s2 = {462,0,323,227 };
	s3 = {827,0,323,227 };
	s4 = {1183,0,323,227 };
	s5 = {0,326,323,224 };
	s6 = {450,347,323,227 };
	s7 = {806,347,323,227 };
	s8 = {1162,347,323,227 };
	s9 = {57,665,323,227 };
	s10 = {451,665,323,227 };
	s11 = {807,665,323,227 };
	s12 = {1163,665,323,227 };
	s13= { 47,963,323,227 };
	s14= { 441,963,323,227 };
	s15 = { 797,963 ,323,227 };
	s16= {1153,963,323,227 };
	s17 = {47,1247,323,227 };
	s18 = {441,1247,323,227 };
	s19 = {797,1247,323,227 };
	s20 = {1165,1247,323,227 };
	
	

}

ModuleSceneIntro::~ModuleSceneIntro()
{}
bool ModuleSceneIntro::Init() {
	App->scene_start->Disable();
	App->scene_win->Disable();
	App->scene_loose->Disable();
	App->powerup->Disable();
	App->charmenu->Disable();
	return true;
}
// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro");

	graphics = App->textures->Load("assets/sprites/Scenes/Scene_Intro/Psikyo.png");


	//Mix_PlayMusic(mus, -1);

	time_on_entry = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro");

	App->textures->Unload(graphics);
	graphics = nullptr;
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//Timer
	current_time = SDL_GetTicks() - time_on_entry;
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &Psikyo, 0.00f);
	if (current_time <= 100) App->render->Blit(graphics, 0, 0, &s1);
	else if (current_time > 100 &&current_time <= 200) App->render->Blit(graphics, 0, 0, &s2);
	else if (current_time > 200 && current_time <= 300) App->render->Blit(graphics, 0, 0, &s3);
	else if (current_time > 300 && current_time <= 400) App->render->Blit(graphics, 0, 0, &s4);
	else if (current_time > 400 && current_time <= 500) App->render->Blit(graphics, 0, 0, &s5);
	else if (current_time > 500 && current_time <= 600) App->render->Blit(graphics, 0, 0, &s6);
	else if (current_time > 600 && current_time <= 700) App->render->Blit(graphics, 0, 0, &s7);
	else if (current_time > 700 && current_time <= 800) App->render->Blit(graphics, 0, 0, &s8);
	else if (current_time > 800 && current_time <= 900) App->render->Blit(graphics, 0, 0, &s9);
	else if (current_time > 900 && current_time <= 1000) App->render->Blit(graphics, 0, 0, &s10);
	else if (current_time > 1000 && current_time <= 1100) App->render->Blit(graphics, 0, 0, &s11);
	else if (current_time > 1100 && current_time <= 1200) App->render->Blit(graphics, 0, 0, &s12);
	else if (current_time > 1200 && current_time <= 1300) App->render->Blit(graphics, 0, 0, &s13);
	else if (current_time > 1300 && current_time <= 1400) App->render->Blit(graphics, 0, 0, &s14);
	else if (current_time > 1400 && current_time <= 1500) App->render->Blit(graphics, 0, 0, &s15);
	else if (current_time > 1500 && current_time <= 1600) App->render->Blit(graphics, 0, 0, &s16);
	else if (current_time > 1600 && current_time <= 1700) App->render->Blit(graphics, 0, 0, &s17);
	else if (current_time > 1700 && current_time <= 1800) App->render->Blit(graphics, 0, 0, &s18);
	else if (current_time > 1800 && current_time <= 1900) App->render->Blit(graphics, 0, 0, &s19);
	else if (current_time > 1900 && current_time <= 3500) App->render->Blit(graphics, 0, 0, &s20);







	// If pressed, change scene
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN || current_time>3499 || App->input->controller_START_button == KEY_STATE::KEY_DOWN) {
		//Mix_PlayChannel(-1, start, 0);
		App->fade->FadeToBlack(App->scene_intro, App->scene_start, 0.50f);
	}


	return UPDATE_CONTINUE;
}