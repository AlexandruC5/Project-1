#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
//#include "ModuleSceneStage2.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleSceneAir.h"
#include "ModuleWelcomeScreen.h"



ModuleSceneAir::ModuleSceneAir()
{
	for (int i = 0; i < NUM_LAYERS; ++i)
	{
		textures[i] = nullptr;
	}

}

ModuleSceneAir::~ModuleSceneAir()
{
}

bool ModuleSceneAir::Init()
{

	return true;
}

bool ModuleSceneAir::Start() {

	App->player->Enable();

	right = true;
	up = false;
	down = false;
	left = false;

	if (!loadMapTextures()) {
		return false;
	}

	for (int i = 0; i < NUM_LAYERS; i++) {
		textrect[i] = new SDL_Rect();
	}

	for (int i = 0; i < NUM_LAYERS; i++) {
		textp[i] = new SDL_Rect();
	}

	for (int i = 0; i < NUM_LAYERS; i++) {
		textcl[i] = new SDL_Rect();
	}
	


textrect[0]->x = 0;	 	
textrect[0]->y = 0;	 	
textrect[0]->h = 897;	 	
textrect[0]->w = 5110;

textp[1]->x = 0;
textp[1]->y = 0;
textp[1]->h = 500;
textp[1]->w = 5510;

textp[2]->x = 0;
textp[2]->y = 0;
textp[2]->h = 24;
textp[2]->w = 5510;

textp[3]->x = 0;
textp[3]->y = 0;
textp[3]->h = 19;
textp[3]->w = 5510;

textcl[0]->x = 0;
textcl[0]->y = 0;
textcl[0]->w = 112;
textcl[0]->h = 79;

textcl[1]->x = 0;
textcl[1]->y = 0;
textcl[1]->w = 70;
textcl[1]->h = 42;

textcl[2]->x = 0;
textcl[2]->y = 0;
textcl[2]->w = 102;
textcl[2]->h = 71;

textcl[3]->x = 0;
textcl[3]->y = 0;
textcl[3]->w = 32;
textcl[3]->h = 42;

textcl[4]->x = 0;
textcl[4]->y = 0;
textcl[4]->w = 5510;
textcl[4]->h = 500;

textcl[5]->x = 0;
textcl[5]->y = 0;
textcl[5]->w = 5510;
textcl[5]->h = 500;

textcl[6]->x = 0;
textcl[6]->y = 0;
textcl[6]->w = 5510;
textcl[6]->h = 124;

textcl[7]->x = 0;
textcl[7]->y = 0;
textcl[7]->w = 38;
textcl[7]->h = 16;

textcl[8]->x = 0;
textcl[8]->y = 0;
textcl[8]->w = 42;
textcl[8]->h = 15;

textcl[9]->x = 0;
textcl[9]->y = 0;
textcl[9]->w = 42;
textcl[9]->h = 15;

textcl[12]->x = 0; //high cloud line
textcl[12]->y = 0; 
textcl[12]->w = 5510; 
textcl[12]->h = 29; 
	//shipSpawn = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-026.wav");
	music = App->audio->LoadMusic("assets/audio/music/03_Sky_dance.ogg");

	Mix_PlayMusic(music, -1);
	//Mix_PlayChannel(-1, shipSpawn, 0);
	return true;
}

update_status ModuleSceneAir::Update()
{


	//Painting the background



	//App->render->Blit(textures[1], xLayer, yLayer, textrect[1]);

	// Move camera forward -----------------------------
	int scroll_speed = 1;
	timer++;



	if (timer < 30) {
		App->player->position.x += 1;
	}

	App->player->position.x += 1;
	App->render->camera.x -= 2;

<<<<<<< HEAD
	if (timer >= 1000 && timer <= 2370) {
=======
	if (timer >= 1000 && timer <= 2400) {
>>>>>>> 04cbf0b64fd7a4751ddbf2d8aaac20245767ed5f

		App->player->position.y -= 1;
		App->render->camera.y += 2;

	}

	

	if (App->input->keyboard[SDL_SCANCODE_A]) {
		App->player->position.x -= 2;
		App->render->camera.x -= 0;


	}
	if (App->input->keyboard[SDL_SCANCODE_W]) {

		App->player->position.x -= 0;
		App->render->camera.x -= 0;
	}

	if (App->render->camera.x < -8000 && App->render->camera.x > -10400)
	{
		down = true;
	}
	else if (down) down = false;

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) App->fade->FadeToBlack(this, App->scene_start, 2);

	//Woods

	App->render->Blit(textures[0], 0, -700, textrect[0], 0.5f);
	App->render->Blit(textures[1], 10, -315, textp[1], 1.0f);
	App->render->Blit(textures[1], 10, -315, textp[1], 1.0f);
	App->render->Blit(textures[2], 0, -310, textp[1], 1.0f);
	App->render->Blit(textures[1], 0, -305, textp[1], 1.1f);
	App->render->Blit(textures[2], 0, -305, textp[1], 1.1f);
	App->render->Blit(textures[1], 0, -300, textp[1], 1.3f);
	App->render->Blit(textures[2], 0, -300, textp[1], 1.3f);
	App->render->Blit(textures[1], 0, -295, textp[1], 1.5f);
	App->render->Blit(textures[2], 0, -295, textp[1], 1.5f);
	App->render->Blit(textures[3], 0, 200, textp[2], 1.7f);
	App->render->Blit(textures[4], 0, 200, textp[3], 1.7f);
	App->render->Blit(textures[3], 15, 190, textp[2], 1.7f);
	App->render->Blit(textures[4], 15, 190, textp[3], 1.7f);

	//Clouds
	/*App->render->Blit(textures[5], 1330, -265, textcl[0], 1.0);
	App->render->Blit(textures[6], 1420, -300, textcl[1], 1.0);
	App->render->Blit(textures[7], 1497, -339, textcl[2], 1.0);
	App->render->Blit(textures[8], 1390, -325, textcl[3], 1.1);
	*/
	//cloudline
	App->render->Blit(textures[11], 1944, -1515, textcl[6], 1.1f);//slow

	App->render->Blit(textures[11], 1939, -1505, textcl[6], 1.1f);//slow
	App->render->Blit(textures[11], 1924, -1500, textcl[6], 1.1f);//slow
	App->render->Blit(textures[9], 1920, -2150, textcl[4], 1.3f);
    App->render->Blit(textures[10], 1940, -2145, textcl[5], 1.3f);
	App->render->Blit(textures[9], 1920, -2140, textcl[4], 1.3f);
	App->render->Blit(textures[10], 1900, -2135, textcl[5], 1.3f);
	App->render->Blit(textures[9], 1920, -2130, textcl[4], 1.3f);
	App->render->Blit(textures[9], 1960, -2125, textcl[4], 1.3f);
	App->render->Blit(textures[10], 1940, -2120, textcl[5], 1.3f);
	App->render->Blit(textures[9], 1920, -2115, textcl[4], 1.3f);
	App->render->Blit(textures[10], 1900, -2110, textcl[5], 1.3f);
	App->render->Blit(textures[9], 1920, -2103, textcl[4], 1.3f);
	App->render->Blit(textures[10], 1900, -2095, textcl[5], 1.3f);

	//App->render->Blit(textures[9], 15, -2250, textcl[4], 1.3f);

	//App->render->Blit(textures[9], 10, -2250, textcl[4], 1.5f);//mid

	/*App->render->Blit(textures[10], 0, -2280, textcl[5], 1.5f);//mid
	App->render->Blit(textures[10], 0, -2265, textcl[5], 1.3f);//mid
	App->render->Blit(textures[10], 0, -2200, textcl[5], 1.3f);//mid
	App->render->Blit(textures[11], 0, -100, textcl[6], 1.1f);//slow
	*/	
	App->render->Blit(textures[10], 1980, -2385, textcl[5], 1.5f);//mid
	App->render->Blit(textures[9], 1960, -2380, textcl[4], 1.5f);//mid
	App->render->Blit(textures[10], 1940, -2375, textcl[5], 1.5f);
	App->render->Blit(textures[9], 1920, -2370, textcl[4], 1.5f);
	App->render->Blit(textures[10], 1900, -2365, textcl[5], 1.5f);//mid
	App->render->Blit(textures[10], 1980, -2360, textcl[5], 1.5f);//mid
	App->render->Blit(textures[9], 1960, -2355, textcl[4], 1.5f);//mid
	App->render->Blit(textures[10], 1940, -2350, textcl[5], 1.5f);
	App->render->Blit(textures[9], 1920, -2345, textcl[4], 1.5f);
	App->render->Blit(textures[10], 1900, -2340, textcl[5], 1.5f);//mid
	

	App->render->Blit(textures[16], 1990, -2135, textcl[12], 1.7f);//quick
	App->render->Blit(textures[16], 1970, -2130, textcl[12], 1.7f);//quick
	App->render->Blit(textures[16], 1950, -2125, textcl[12], 1.7f);//quick
	App->render->Blit(textures[16], 1930, -2019, textcl[12], 1.6f);//quick


	//high clouds
	//App->render->Blit(textures[12], 0, -25, textcl[7], 1.0f);
	//App->render->Blit(textures[13], 0, -100, textcl[7], 1.5f);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleSceneAir::CleanUp()
{
	App->player->Disable();

	for ( int i = NUM_LAYERS; i < 1; --i)
	{
		App->textures->Unload(textures[i]);
		textures[i] = nullptr;
	}

	App->audio->UnloadMusic(music);
	music = nullptr;
	//App->audio->UnloadSFX(shipSpawn);
	//shipSpawn = nullptr;

	return true;
}





bool ModuleSceneAir::loadMapTextures()
{
	LOG("Loading background textures");

	//Load all background textures


	
	textures[0] = App->textures->Load("assets/sprites/Scenes/Scene_Air/background2.png");

	//Woods textures
	textures[1] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");
    textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");
	textures[3] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline3.png");
	textures[4] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline4.png");

	//Clouds textures
	textures[5] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud2.png");
	textures[6] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud1.png");
	textures[7] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud4.png");
	textures[8] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud3.png");
	//Highsky
	textures[9] = App->textures->Load("assets/sprites/Scenes/Scene_Air/BigCloudLine1.png");
	textures[10] = App->textures->Load("assets/sprites/Scenes/Scene_Air/BigCloudLine2.png");
	textures[11] = App->textures->Load("assets/sprites/Scenes/Scene_Air/BigCloudLine3.png");
	/*
	textures[12] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud5.png");
	textures[13] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud6.png");
	textures[14] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud7.png");
	textures[15] = App->textures->Load("assets/sprites/Scenes/Scene_Air/cloud8.png");
	*/
	textures[16] = App->textures->Load("assets/sprites/Scenes/Scene_Air/bigcloudline4.png");

	for (int i = 0; i <= NUM_LAYERS; i++) {
	if (textures[i] == nullptr) {

		return false;
	}
	else return true;
	};
}


