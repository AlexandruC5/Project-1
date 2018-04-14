#include "Globals.h"
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

#include "ModuleSceneWater.h"
#include "ModuleWelcomeScreen.h"


ModuleSceneWater::ModuleSceneWater()
{
	//Mountain
	BG_Mountain.x = 0;
	BG_Mountain.y = 0;
	BG_Mountain.w = 756;
	BG_Mountain.h = 128;

	//Layer ocean 1
	layer_ocean_1.x = 801;
	layer_ocean_1.y = 88;
	layer_ocean_1.w = 960;
	layer_ocean_1.h = 16;

	//Layer ocean 2
	layer_ocean_2.x = 801;
	layer_ocean_2.y = 115;
	layer_ocean_2.w = 960;
	layer_ocean_2.h = 16;

	//Layer ocean 3
	layer_ocean_3.x = 800;
	layer_ocean_3.y = 145;
	layer_ocean_3.w = 960;
	layer_ocean_3.h = 20;

	//Layer ocean 4
	layer_ocean_4.x = 801;
	layer_ocean_4.y = 176;
	layer_ocean_4.w = 960;
	layer_ocean_4.h = 20;

	//Layer ocean 5
	layer_ocean_5.x = 801;
	layer_ocean_5.y = 206;
	layer_ocean_5.w = 960;
	layer_ocean_5.h = 41;

	//Waterfall rocks
	Waterfall_rocks.x = 436;
	Waterfall_rocks.y = 128;
	Waterfall_rocks.w = 320;
	Waterfall_rocks.h = 282;
	
	//Small waterfall animation
	waterfall1.PushBack({20, 155, 6, 68});
	waterfall1.PushBack({ 32, 155, 6, 68 });
	waterfall1.PushBack({ 44, 155, 6, 68 });
	waterfall1.PushBack({ 56, 155, 6, 68 });
	waterfall1.speed = 0.05f;

	//Mid waterfall animation
	waterfall2.PushBack({ 13, 243, 36, 82 });
	waterfall2.PushBack({ 62, 243, 41, 83 });
	waterfall2.PushBack({ 113, 244, 41, 83 });
	waterfall2.PushBack({ 163, 244, 41, 83 });
	waterfall2.speed = 0.05f;

	//Last waterfall animation
	waterfall3.PushBack({ 15, 344, 7, 66 });
	waterfall3.PushBack({ 40, 345, 7, 66 });
	waterfall3.PushBack({ 91, 344, 7, 66 });
	waterfall3.PushBack({ 116, 344, 7, 66 });
	waterfall3.speed = 0.05f;

	//Under waterfall animation
	under_waterfall.PushBack({166,176,32,16});
	under_waterfall.PushBack({ 125,176,32,16 });
	waterfall3.speed = 0.07f;

}

ModuleSceneWater::~ModuleSceneWater()
{
}

bool ModuleSceneWater::Start()
{
	LOG("Loading Water Scene");

	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Water/mountain&waterfall.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Water/waterfall.png");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Water/background_waterfall.png");
	graphics4 = App->textures->Load("assets/sprites/Scenes/Scene_Water/lateral_scroll&waterfall.png");

	App->player->Enable();
	
	return true;
}

update_status ModuleSceneWater::Update()
{

	// Move camera forward -----------------------------
	int scroll_speed = 1;

	//Player auto scroll
	App->player->position.x += 1;

	App->render->camera.x -= 2;

	// Draw everything --------------------------------------

	App->render->Blit(graphics1, 0, 0, &BG_Mountain, 0.55f);

	App->render->Blit(graphics1, 156, 44, &(waterfall1.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics1, 510, 44, &(waterfall2.GetCurrentFrame()), 0.55F);
	//App->render->Blit(graphics1, 509, 106, &(under_waterfall.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics1, 710, 45, &(waterfall3.GetCurrentFrame()), 0.55F);
	
	//App->render->Blit(graphics1, 697, 107, &(under_waterfall.GetCurrentFrame()), 0.55F);

	App->render->Blit(graphics1, 0, 128, &layer_ocean_1, 0.60f);
	App->render->Blit(graphics1, 0, 144, &layer_ocean_2, 0.65f);
	App->render->Blit(graphics1, 0, 160, &layer_ocean_3, 0.65f);
	App->render->Blit(graphics1, 0, 180, &layer_ocean_4, 0.70f);
	App->render->Blit(graphics1, 0, 200, &layer_ocean_5, 0.70f);

	return UPDATE_CONTINUE;
}


bool ModuleSceneWater::CleanUp()
{
	App->player->Disable();

	
		App->textures->Unload(graphics1);
		graphics1 = nullptr;

		App->textures->Unload(graphics2);
		graphics2 = nullptr;

		App->textures->Unload(graphics3);
		graphics3 = nullptr;

		App->textures->Unload(graphics4);
		graphics4 = nullptr;
	

	return true;
}