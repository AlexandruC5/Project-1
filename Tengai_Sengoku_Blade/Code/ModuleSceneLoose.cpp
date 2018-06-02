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
#include "CharSelec.h"
#include<string>
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleKatana.h"

ModuleLooseScreen::ModuleLooseScreen() {
	//background = {0,0,320,224};
	background = { 162,183,323,227 };
	ranking = {13,16,323,227};
	letters1 = { 102,32,128,16 };
	letters2 = { 8,31,78,16 };

	katana = { 25,63,30,15 };
	ayin = { 27,94,30,13 };

	let3 = { 7,60,28,15 };
	let4 = { 9,82,31,15 };
	let5 = { 9,104,30,15 };

	name = { 86,73,39,2 };
	level = { 141,67,11,8 };

	firstN = {61,33,35,7};
	secondN = {63,47,32,11};
	thirdN = { 64,65,33,11 };
	forthN = { 64,80,32,11 };
	fifthN = { 64,97,32,11 };

}

ModuleLooseScreen::~ModuleLooseScreen(){}


bool ModuleLooseScreen::Start() {
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	speed = 1;
	count = 0;
	down = false;
	stay = false;
	goup1 = 65;
	goup2 = 144;
	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Loose/Background.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Loose/Ranking.png");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Loose/bgsprites.png");
	graphics4 = App->textures->Load("assets/sprites/Scenes/Scene_Loose/RankSprites.png");
	fontScore = App->fonts->Load("assets/sprites/Scenes/Scene_Loose/scorefonts.png", "0123456789", 1);
	
	return true;
}

update_status ModuleLooseScreen::Update() {

	//states logic
	if (App->charmenu->numberplayers == 1) numplayers = ONE;
	else if (App->charmenu->numberplayers == 2) numplayers = TWO;

	if (App->charmenu->P1katana && App->charmenu->P2ayin) mode = K1A2;
	else if (App->charmenu->P2katana && App->charmenu->P1ayin) mode = A1K2;
	else if (App->charmenu->P1katana) mode = KATANA1;
	else if (App->charmenu->P1ayin) mode = AYIN1;
	 

	//camera
	count++;
	if (count >= 250 && count <=475) down = true,goup1 -=1,goup2-=1,stay =true;
	else  down = false;
	if (down== true) {
		App->render->camera.y += speed;
	}

	if (count >= 1000|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN) {
		App->inter->score_ayin = 0;
		App->inter->score_katana = 0;
		App->fade->FadeToBlack(this, App->scene_start, 1.5f);
	}
	App->render->Blit(graphics1, 0, 0, &background);
	App->render->Blit(graphics2, 0, 224, &ranking);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		App->fade->FadeToBlack(this, App->scene_start, 2);

	}

	

	switch (numplayers) {
	case ONE:
		App->render->Blit(graphics3, 185, 68, &level);
		App->render->Blit(graphics3, 97, 74, &name);
		App->render->Blit(graphics3, 68, 92, &letters1);
		App->render->Blit(graphics3, 199, 92, &letters2);
		switch (mode) {
			
		case KATANA1:
			sprintf_s(player1Score, 10, "%1d", App->inter->score_katana);
			App->render->Blit(graphics3, 145, 65, &katana);
			if(stay == false)App->fonts->BlitText(240, 65, fontScore,player1Score );
			else App->fonts->BlitText(240, goup1, fontScore, player1Score);
			break;
		case AYIN1:
			App->render->Blit(graphics3, 145, 68, &ayin);
			sprintf_s(player1Score, 10, "%1d", App->inter->score_ayin);
			if (stay == false)App->fonts->BlitText(240, 65, fontScore, player1Score);
			else App->fonts->BlitText(240, goup1, fontScore, player1Score);

			break;
		}
		break;
	case TWO:

		//Player1
		App->render->Blit(graphics3, 185, 68, &level);
		App->render->Blit(graphics3, 97, 74, &name);
		App->render->Blit(graphics3, 68, 92, &letters1);
		App->render->Blit(graphics3, 199, 92, &letters2);

		//Player2
		App->render->Blit(graphics3, 185, 147, &level);
		App->render->Blit(graphics3, 97, 153, &name);
		App->render->Blit(graphics3, 68, 171, &letters1);
		App->render->Blit(graphics3, 199, 171, &letters2);

		switch (mode) {
		case K1A2:
			App->render->Blit(graphics3, 145, 65, &katana);
			App->render->Blit(graphics3, 145, 147, &ayin);

			sprintf_s(player1Score, 10, "%1d", App->inter->score_katana);
			if(stay == false)App->fonts->BlitText(240, 65, fontScore, player1Score);
			else App->fonts->BlitText(240, goup1, fontScore, player1Score);

			sprintf_s(player2Score, 10, "%1d", App->inter->score_ayin);
			if(stay ==false)App->fonts->BlitText(240, 144, fontScore, player2Score);
			else App->fonts->BlitText(240, goup2, fontScore, player2Score);
			break;
		case A1K2:
			App->render->Blit(graphics3, 145, 68, &ayin);
			App->render->Blit(graphics3, 145, 144, &katana);

			sprintf_s(player1Score, 10, "%1d", App->inter->score_ayin);
			if(stay ==false)App->fonts->BlitText(240, 65, fontScore, player1Score);
			else App->fonts->BlitText(240, goup1, fontScore, player1Score);

			sprintf_s(player2Score, 10, "%1d", App->inter->score_katana);
			if(stay ==false)App->fonts->BlitText(240, 144, fontScore, player2Score);
			else App->fonts->BlitText(240, goup2, fontScore, player2Score);
			break;
		}
		break;
	}

	//Ranking

	App->render->Blit(graphics3, 90, 317, &name);
	App->render->Blit(graphics3, 90, 337, &name);
	App->render->Blit(graphics3, 90, 357, &name);
	App->render->Blit(graphics3, 90, 377, &name);
	App->render->Blit(graphics3, 90, 397, &name);


	App->render->Blit(graphics3, 142, 310, &katana);
	App->render->Blit(graphics3, 142, 330, &ayin);
	App->render->Blit(graphics4, 142, 350, &let3);
	App->render->Blit(graphics4, 142, 370, &let4);
	App->render->Blit(graphics4, 142, 390, &let5);

	App->render->Blit(graphics3, 185, 313, &level);
	App->render->Blit(graphics3, 185, 333, &level);
	App->render->Blit(graphics3, 185, 353, &level);
	App->render->Blit(graphics3, 185, 373, &level);
	App->render->Blit(graphics3, 185, 393, &level);

	App->render->Blit(graphics4, 237, 315, &firstN);
	App->render->Blit(graphics4, 237, 333, &secondN);
	App->render->Blit(graphics4, 237, 353, &thirdN);
	App->render->Blit(graphics4, 237, 372, &forthN);
	App->render->Blit(graphics4, 237, 391, &fifthN);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleLooseScreen::CleanUp() {
	App->textures->Unload(graphics1);
	graphics1 = nullptr;

	App->textures->Unload(graphics2);
	graphics2 = nullptr;

	App->textures->Unload(graphics3);
	graphics3 = nullptr;

	App->textures->Unload(graphics4);
	graphics4 = nullptr;

	App->fonts->UnLoad(fontScore);
	return true;
}