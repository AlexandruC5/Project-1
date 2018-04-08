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

	//shipSpawn = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-026.wav");
	music = App->audio->LoadMusic("Game/assets/audio/music/03_Sky_dance.ogg");

	Mix_PlayMusic(music, -1);
	//Mix_PlayChannel(-1, shipSpawn, 0);
	return true;
}

update_status ModuleSceneAir::Update()
{

	App->render->Blit(textures[0], 0, -560, textrect[0]);
	App->render->Blit(textures[1], 10, -560, textrect[1]);
	App->render->Blit(textures[2], 45, -560, textrect[2]);
	App->render->Blit(textures[3], 29, -560, textrect[3]);

	//App->render->Blit(textures[1], xLayer, yLayer, textrect[1]);

	// Move camera forward -----------------------------
	int scroll_speed = 1;
	timer++;

	App->player->position.x += 2;
	App->render->camera.x -= 2;

	if (timer >= 50 && timer <= 200) {

		App->player->position.y -= 1;
		App->render->camera.y += 3;

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
	
	textures[0] = App->textures->Load("assets/sprites/Scenes/Scene_Air/Background2.png");
	textures[1] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");
	textures[2] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline2.png");
	textures[3] = App->textures->Load("assets/sprites/Scenes/Scene_Air/treeline1.png");

	//textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/BG01.png");

	if (textures[0] == nullptr) {
		return false;
	}
	else return true;
}

