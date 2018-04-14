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

	if (timer >= 1000 && timer <= 2400) {

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
	

	//textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/BG01.png");
	for (int i = 0; i <= NUM_LAYERS; i++) {
	if (textures[i] == nullptr) {

		return false;
	}
	else return true;
	};
}


