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
	down = {187, 268, 325, 114};
	sky = { 196, 132, 316, 98 };
	
	background = { 0,0,320,224 };

}

ModuleWinScreen::~ModuleWinScreen(){}


bool ModuleWinScreen::Init() {
	goUP = -0.5f;
	goDown = 0.5f;
	MaxUp -= goUP;
	MaxDown += goDown;
	return true;
}
bool ModuleWinScreen::Start() {
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Background2.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Win/mikospritesheet.png");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Win/Allin.png");
	Winfade = App->audio->LoadMusic("assets/audio/music/Level_Completed.ogg");
	Mix_PlayMusic(Winfade, 1);

	return true;
}

update_status ModuleWinScreen::Update() {
	App->render->Blit(graphics1, 1.5f, 60, &sky);
	App->render->Blit(graphics3, 0, 0, &background);
	
	//App->render->Blit(graphics1, 0, -47, &up);
	//App->render->Blit(graphics1, 0, 155, &down);
		//App->render->Blit(graphics1, 0, 0, &up);
		//App->render->Blit(graphics1, 0, 109, &down);
	
	/*if(MaxUp<=-10 && MaxDown >=10){
		 App->render->Blit(graphics1, 0, goUP, &up);
		 App->render->Blit(graphics1, 0,109+ goDown, &down);
	//}
	 else {
		 App->render->Blit(graphics1, 0, MaxUp, &up);
		 App->render->Blit(graphics1, 0, MaxDown, &down);
	 }*/
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		
		App->fade->FadeToBlack(this, App->scene_water, 2);

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
	App->textures->Unload(graphics3);
	return true;
}