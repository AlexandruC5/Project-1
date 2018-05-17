#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleFadeToBlack.h"
#include "CharSelec.h"
#include "ModuleKatana.h"
#include "ModuleKatanaArrow.h"
#include "ModuleSceneTemple.h"

#include "SDL_mixer/include/SDL_mixer.h"
#include "SDL/include/SDL.h"


ModuleCharSelec:: ModuleCharSelec()
{
	sky = { 0,56,322,115 };

	background = { 0,0,322,226 };
	background2 = { 0,0,322,226 };
    headkatana = { 43,33,112,128 };
	katana = { 283,4,165,211 };
	lettersK = { 203,207,80,32 };
	ayin = { 16,238,130,199 };
	headayin = { 337,267,112,122 };
	lettersA = { 203,419,80,31 };
	blueline = { 0,464, 336,48 };

	square1 = { 4,94,46,53 };
	square2 = { 52,93,46,54 };
	random = { 9,149,26,22 };
	time = { 6,72,29,9 };
	n0 = { 45,19,8,11 };
	n1 = { 55,19,5,11 };
	n2 = { 55,19,5,11 };
	n3 = { 72,19,8,11 };
	n4 = { 82,19,8,11 };
	n5 = { 92,19,8,11 };
	n6 = { 102,19,8,11 };
	n7 = { 112,19,8,11 };
	n8 = { 122,19,8,11 };
	n9 = { 132,19,8,11 };

	Kidle.PushBack({ 87, 4, 32, 33 });
	Kidle.PushBack({ 152, 5, 32, 33 });
	Kidle.PushBack({ 188, 5, 32, 33 });
	Kidle.speed = 0.20f;

	Aidle.PushBack({ 29, 1, 33, 33 });
	Aidle.PushBack({ 63, 1, 33, 33 });
	Aidle.PushBack({ 101, 1, 33, 33 });
	Aidle.speed = 0.20f;
}
ModuleCharSelec::~ModuleCharSelec() {}
bool ModuleCharSelec::Init() {
	left = 0, right = 0, bgmove = 0;
	rand = 0, clock=9;

	return true;
}
bool ModuleCharSelec::Start() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	clock = 9;
	frames = 0;
	s = 0;
	reset = false;
	player1 = false;
	player2 = false;
	state = KATANAP1;
	players = ONEPLAYER;
	graphics1 = App->textures->Load("assets/sprites/Scenes/CharSelecScene/Background.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/CharSelecScene/Characters.png");
	graphics3 = App->textures->Load("assets/sprites/UI/UI.png");
	graphics4 = App->textures->Load("assets/sprites/characters/katana/Katana_Spritesheet.png");
	graphics5 = App->textures->Load("assets/sprites/characters/ayin/Ayin_Spritesheet2.png");
	graphics6 = App->textures->Load("assets/sprites/Scenes/CharSelecScene/Background2.png");
	graphics7 = App->textures->Load("assets/sprites/Scenes/CharSelecScene/sky.png");
	return true;

}



update_status ModuleCharSelec::Update() {
	bool press_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_DOWN;
	bool press_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN;
	bool press_L = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN;
	bool press_R = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN;
	App->render->Blit(graphics7, 0, 31, &sky);
	
	if (clock == 0) state = OUTOFTIME;
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN) {
		players = TWOPLAYERS;
		state = KATANAAYIN;
		reset = true;
	}

	switch (players && state) {
	case ONEPLAYER:

		if (press_D&& state == KATANAP1) state = AYINP1;
		else if (press_A && state == KATANAP1) state = RANDOMP1;
		else if (press_A && state == AYINP1) state = KATANAP1;
		else if (press_D && state == AYINP1) state = RANDOMP1;
		else if (press_D && state == RANDOMP1) state = KATANAP1;
		else if (press_A && state == RANDOMP1) state = AYINP1;

		if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
			player1 = true;
		}

		App->render->Blit(graphics1, 0, 0, &background);
		switch (state) {
		case KATANAP1:

			App->render->Blit(graphics2, 16, 17, &headkatana);
			App->render->Blit(graphics2, 135, -3, &katana);
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 23, 157, &square1);

			App->render->Blit(graphics2, 35, 127, &lettersK);
			if (player1) {
				App->katana->Enable();
				App->fade->FadeToBlack(this, App->scene_temple, 2);
			}
			break;

		case AYINP1:
			App->render->Blit(graphics2, 160, -4, &ayin);
			App->render->Blit(graphics2, 16, 23, &headayin);
			App->render->Blit(graphics2, 35, 127, &lettersA);
			App->render->Blit(graphics2, 0, 161, &blueline);

			App->render->Blit(graphics3, 83, 157, &square1);

			break;
		case RANDOMP1:
			if (rand <= 5) {
				App->render->Blit(graphics2, 160, -4, &ayin,55);
				App->render->Blit(graphics2, 16, 23, &headayin,55);
				App->render->Blit(graphics2, 35, 127, &lettersA);
				rand+=1.5f;
			}
			else if (rand >5 &&rand <= 11) {
				App->render->Blit(graphics2, 16, 17, &headkatana,55);
				App->render->Blit(graphics2, 135, -3, &katana,55);
				App->render->Blit(graphics2, 35, 127, &lettersK);
				rand+=1.5f;
			}
			if (rand > 11) rand = 0;
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 143, 157, &square1);
			break;

		case OUTOFTIME:
			App->fade->FadeToBlack(this, App->scene_start, 3);
			break;
		}
	
		break;

	case TWOPLAYERS:

		if (press_D && state == KATANAAYIN) state = RANDOMAYIN; //1 player 
		else if (press_A  && state == KATANAAYIN) state = RANDOMAYIN;
		else if (press_A  && state == AYINKATANA) state = RANDOMKATANA;
		else if (press_D  && state == AYINKATANA) state = RANDOMKATANA;
		else if (press_D && state == AYINRANDOM) state = KATANARANDOM;
		else if (press_A && state == AYINRANDOM) state = KATANARANDOM;
		else if (press_D && state == RANDOMKATANA) state = AYINKATANA;
		else if (press_A && state == RANDOMKATANA) state = AYINKATANA;
		else if (press_A && state == RANDOMAYIN) state = KATANAAYIN;
		else if (press_D && state == RANDOMAYIN) state = KATANAAYIN;
		else if (press_D&& state == KATANARANDOM) state = AYINRANDOM;
		else if (press_A&& state == KATANARANDOM) state = AYINRANDOM;

		if (press_R && state == KATANAAYIN) state = KATANARANDOM; //2 player
		else if (press_L && state == KATANAAYIN) state = KATANARANDOM;
		else if (press_L && state == AYINKATANA) state = AYINRANDOM;
		else if (press_R && state == AYINKATANA) state = AYINRANDOM;
		else if (press_R&& state == KATANARANDOM) state = KATANAAYIN;
		else if (press_L&& state == KATANARANDOM) state = KATANAAYIN;

		else if (press_R && state == AYINRANDOM) state = AYINKATANA;
		else if (press_L && state == AYINRANDOM) state = AYINKATANA;

		else if (press_R && state == RANDOMKATANA) state = RANDOMAYIN;
		else if (press_L && state == RANDOMKATANA) state = RANDOMAYIN;
		else if (press_R && state == RANDOMAYIN) state = RANDOMKATANA;
		else if (press_L && state == RANDOMAYIN) state = RANDOMKATANA;
		App->render->Blit(graphics6, 0, 0, &background2);

		switch (state) {
		case KATANAAYIN:
			App->render->Blit(graphics2, 145, -3, &katana);
			App->render->Blit(graphics2, 10, -4, &ayin);
			App->render->Blit(graphics2, 0, 161, &blueline);

			App->render->Blit(graphics3, 23, 157, &square1);
			App->render->Blit(graphics3, 83, 157, &square2);
			break;
		case KATANARANDOM:
			App->render->Blit(graphics2, 145, -3, &katana);

			if (rand <= 5) {
				App->render->Blit(graphics2, 10, -4, &ayin);
				rand += 1.5f;
			}
			else if (rand >5 && rand <= 11) {
				App->render->Blit(graphics2, -15, -3, &katana, 55);
				rand += 1.5f;
			}
			if (rand > 11) rand = 0;
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 23, 157, &square1);
			App->render->Blit(graphics3, 143, 157, &square2);
			break;
		case AYINKATANA:

			App->render->Blit(graphics2, 160, -4, &ayin);
			App->render->Blit(graphics2, -15, -3, &katana, 55);
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 83, 157, &square1);
			App->render->Blit(graphics3, 23, 157, &square2);
			break;
		case AYINRANDOM:
			App->render->Blit(graphics2, 160, -4, &ayin);
			
			if (rand <= 5) {
				App->render->Blit(graphics2, 10, -4, &ayin);
				rand += 1.5f;
			}
			else if (rand >5 && rand <= 11) {
				App->render->Blit(graphics2, -15, -3, &katana, 55);
				rand += 1.5f;
			}
			if (rand > 11) rand = 0;
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 83, 157, &square1);
			App->render->Blit(graphics3, 143, 157, &square2);


			break;
		case RANDOMKATANA:
			
			App->render->Blit(graphics2, -15, -3, &katana, 55);

			if (rand <= 5) {
				App->render->Blit(graphics2, 160, -4, &ayin, 55);
				rand += 1.5f;
			}
			else if (rand >5 && rand <= 11) {
				App->render->Blit(graphics2, 145, -3, &katana, 55);
				rand += 1.5f;
			}
			if (rand > 11) rand = 0;
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 143, 157, &square1);
			App->render->Blit(graphics3, 23, 157, &square2);
			break;
			
		case RANDOMAYIN:
			
			App->render->Blit(graphics2, 10, -4, &ayin);

			if (rand <= 5) {
				App->render->Blit(graphics2, 160, -4, &ayin, 55);
				rand += 1.5f;
			}
			else if (rand >5 && rand <= 11) {
				App->render->Blit(graphics2, 145, -3, &katana, 55);
				rand += 1.5f;
			}
			if (rand > 11) rand = 0;
			App->render->Blit(graphics2, 0, 161, &blueline);
			App->render->Blit(graphics3, 143, 157, &square1);
			App->render->Blit(graphics3, 83, 157, &square2);
			break;

		case OUTOFTIME:
			App->fade->FadeToBlack(this, App->scene_start, 3);
			break;
		}
		break;
	}
	App->render->Blit(graphics3, 135, 213, &time);
	App->render->Blit(graphics4, 30, 167, &(Kidle.GetCurrentFrame()));
	App->render->Blit(graphics5, 90, 167, &(Aidle.GetCurrentFrame()));
	App->render->Blit(graphics3, 153, 170, &random);
	frames++;
	if (state == TWOPLAYERS && reset ==true) { 
		s = 0; 
	}
	
	if (frames <= 50) App->render->Blit(graphics3, 166, 211, &n9), clock = 9;
	else if(frames>=57&&frames<=100)App->render->Blit(graphics3, 166, 211, &n8), clock = 8;
	else if (frames > 107 && frames <= 200)App->render->Blit(graphics3, 166, 211, &n7), clock = 7;
	else if (frames >= 207 && frames <= 300)App->render->Blit(graphics3, 166, 211, &n6), clock = 6;
	else if (frames >= 307 && frames <= 400)App->render->Blit(graphics3, 166, 211, &n5), clock = 5;
	else if (frames >= 407 && frames <= 500)App->render->Blit(graphics3, 166, 211, &n4), clock = 4;
	else if (frames >= 507 && frames <= 600)App->render->Blit(graphics3, 166, 211, &n3), clock = 3;
	else if (frames >= 607 && frames <= 710)App->render->Blit(graphics3, 166, 211, &n2), clock = 2;
	else if (frames >= 707 && frames <= 800)App->render->Blit(graphics3, 166, 211, &n1), clock = 1;
	else if (frames >= 807 && frames <= 900)App->render->Blit(graphics3, 166, 211, &n0), clock = 0;
	else if (players == TWOPLAYERS && s == 0) frames = 0, s = 1;
	
	reset = false;
	return update_status:: UPDATE_CONTINUE;
}



void ModuleCharSelec::CheckState() {
	

}


bool ModuleCharSelec::CleanUp() {
	App->textures->Unload(graphics1);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);
	App->textures->Unload(graphics4);
	App->textures->Unload(graphics5);
	App->textures->Unload(graphics6);
	App->textures->Unload(graphics7);

	graphics1 = nullptr;
	graphics2 = nullptr;
	graphics3 = nullptr;
	graphics4 = nullptr;
	graphics5 = nullptr;
	graphics6 = nullptr;
	graphics7 = nullptr;
	return true;
}