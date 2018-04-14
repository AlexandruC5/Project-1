#include "Globals.h"
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"

#include "ModuleSceneWater.h"


ModuleSceneWater::ModuleSceneWater()
{

}

ModuleSceneWater::~ModuleSceneWater()
{
}

bool ModuleSceneWater::Start()
{
	LOG("Loading Water Scene");

	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Water/mountain&waterfall");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Water/waterfall");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Water/background_waterfall");
	graphics4 = App->textures->Load("assets/sprites/Scenes/Scene_Water/lateral_scroll&waterfall");

	App->player->Enable();
	
	return true;
}

update_status ModuleSceneWater::Update()
{

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