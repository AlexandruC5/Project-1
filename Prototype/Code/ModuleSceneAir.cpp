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

	textrect[0] = new SDL_Rect();

	textrect[0]->x = 0;
	textrect[0]->y = 0;
	textrect[0]->h = 785;
	textrect[0]->w = 5110;

	music = App->audio->LoadMusic("assets/audio/music/03_Sky_dance.ogg");
	//shipSpawn = App->audio->LoadFx("Assets/Audio/SFX/xmultipl-026.wav");
	Mix_PlayMusic(music, -1);
	//Mix_PlayChannel(-1, shipSpawn, 0);
	return true;
}

update_status ModuleSceneAir::Update()
{

	App->render->Blit(textures[0], 0, -560, textrect[0]);
	//App->render->Blit(textures[1], xLayer, yLayer, textrect[1]);

	// Move camera forward -----------------------------
	int scroll_speed = 1;
	timer++;

	//App->render->camera.x -= 2;
	//if (timer <= 100)
	//{
	//	App->player->position.x += 2;
	//}
	//App->player->position.x -= App->render->camera.x;
	//	

	App->player->position.x += 2;
	App->render->camera.x -= 2;

	if (timer >= 500 && timer <= 700) {

		App->player->position.y -= 1;
		App->render->camera.y += 2;

	}

	/*if (timer >= 500 && timer <= 700) {

		App->player->position.y -= 1;
		App->render->camera.y += 3;

	}*/

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

	for (int i = NUM_LAYERS; i < 1; --i)
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
	
	//textures[1] = App->textures->Load("Assets/Sprites/Stages/Stage1/Background/BG01.png");

	if (textures[0] == nullptr) {
		return false;
	}
	else return true;
}

