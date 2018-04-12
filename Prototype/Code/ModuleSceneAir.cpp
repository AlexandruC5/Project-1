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


	


textrect[0]->x = 0;	 	
textrect[0]->y = 0;	 	
textrect[0]->h = 897;	 	
textrect[0]->w = 5110;

textrect[1]->x = 0;
textrect[1]->y = 0;
textrect[1]->h = 16;
textrect[1]->w = 5510;

textrect[2]->x = 0;
textrect[2]->y = 0;
textrect[2]->h = 16;
textrect[2]->x = 5510;


	/*
	
	textrect[0]->x = 0;
	textrect[0]->y = 0;
	textrect[0]->h = 785;
	textrect[0]->w = 5110;

	textrect[1]->x = 237;
	textrect[1]->y = 192;
	textrect[1]->w = 128;
	textrect[1]->h = 16;

	textrect[2]->x = -21;
	textrect[2]->y = 192;
	textrect[2]->w = 128;
	textrect[2]->h = 16;
	
	textrect[3]->x = -56;
	textrect[3]->y = 192;
	textrect[3]->w = 128;
	textrect[3]->h = 16;
	*/
	//shipSpawn = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-026.wav");
	music = App->audio->LoadMusic("assets/audio/music/03_Sky_dance.ogg");

	Mix_PlayMusic(music, -1);
	//Mix_PlayChannel(-1, shipSpawn, 0);
	return true;
}

update_status ModuleSceneAir::Update()
{

<<<<<<< HEAD
<<<<<<< HEAD
	//Painting the background
	App->render->Blit(textures[0], 0, -670, textrect[0], 1);
	App->render->Blit(textures[1], 0, -700, textrect[1], 0.5f);
=======
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e
=======
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e

	App->render->Blit(textures[0], 0, -670, textrect[0], 1);
	

<<<<<<< HEAD
	App->render->Blit(textures[1], 0, -700, textrect[1], 0.5f);
=======
<<<<<<< HEAD
<<<<<<< HEAD

	
=======
=======
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e
	App->render->Blit(textures[1], 0, 30, textrect[1], 0.5f);
>>>>>>> 3175d113bc458900f60aff4f8d2ed3b1429d7be9

	App->render->Blit(textures[2], 0, 40, textrect[2], 0.5f);


	//App->render->Blit(textures[1], xLayer, yLayer, textrect[1]);
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e

	// Move camera forward -----------------------------
	int scroll_speed = 1;
	timer++;



	if (timer < 30) {
		App->player->position.x += 1;
	}

	App->player->position.x += 1;
	App->render->camera.x -= 2;

	if (timer >= 1000 && timer <= 1668) {

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
	textures[1] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");
<<<<<<< HEAD
<<<<<<< HEAD
	textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");

	if (textures[0] == nullptr) {
		return false;
	}
	else return true;
	if (textures[1] == nullptr) {
=======
=======
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e

	textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");

	//textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");
	/*
	textures[1] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");
	textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");
	textures[3] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");
	*/
	//textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/BG01.png");
	for (int i = 0; i <= NUM_LAYERS; i++) {
	if (textures[i] == nullptr) {
<<<<<<< HEAD
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e
=======
>>>>>>> 364d0c88ed31de0e2b146ea7cf8759c328ce0e0e
		return false;
	}
	else return true;
	};
}


