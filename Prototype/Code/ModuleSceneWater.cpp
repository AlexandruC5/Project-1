#include "Globals.h"
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneWater.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleEnemies.h"
#include "ModulePowerUPS.h"

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

	//small stone
	stone1.x = 18;
	stone1.y = 705;
	stone1.w = 20;
	stone1.h = 10;

	// mid stone
	stone2.x = 18;
	stone2.y = 758;
	stone2.w = 29;
	stone2.h = 20;

	// big stone
	stone3.x = 13;
	stone3.y = 805;
	stone3.w = 42;
	stone3.h = 16;



	//Small green candle
	candle1.PushBack({78, 698, 14, 28});
	candle1.PushBack({103, 698, 14, 28});
	candle1.PushBack({129, 698, 14, 28});
	candle1.PushBack({155, 698, 14, 28});
	candle1.PushBack({179, 698, 14, 28});
	candle1.PushBack({204, 698, 14, 28});
	candle1.PushBack({230, 698, 14, 28});
	candle1.speed = 0.02f;

	//Mid green candle
	candle2.PushBack({74, 743, 23, 42});
	candle2.PushBack({101, 743, 23, 42});
	candle2.PushBack({126, 743, 23, 42});
	candle2.PushBack({151, 743, 23, 42});
	candle2.PushBack({176, 743, 24, 42});
	candle2.PushBack({206, 744, 23, 41});
	candle2.PushBack({231, 743, 23, 42});
	candle2.PushBack({255, 742, 23, 42});
	candle2.speed = 0.02f;

	//Big green candle
	candle3.PushBack({69, 805, 31, 59});
	candle3.PushBack({102, 803, 31, 62});
	candle3.PushBack({137, 801, 31, 65});
	candle3.PushBack({172, 801, 31, 66});
	candle3.PushBack({209, 802, 31, 65});
	candle3.PushBack({245, 801, 31, 66});
	candle3.PushBack({279, 801, 32, 65});
	candle3.speed = 0.02f;

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
	waterfall2.speed = 0.08f;

	//Last waterfall animation
	waterfall3.PushBack({ 15, 344, 7, 66 });
	waterfall3.PushBack({ 40, 345, 7, 66 });
	waterfall3.PushBack({ 91, 344, 7, 66 });
	waterfall3.PushBack({ 116, 344, 7, 66 });
	waterfall3.speed = 0.05f;

	//Under waterfall animation
	under_waterfall.PushBack({17, 444, 37, 16});
	under_waterfall.PushBack({ 71, 444, 37, 16 });
	under_waterfall.PushBack({ 124, 443, 37, 17 });
	under_waterfall.PushBack({ 180, 444, 37, 16 });
	under_waterfall.speed = 0.06f;

	//Wave animation
	wave.PushBack({632, 41, 764, 8});
	wave.PushBack({ 629, 77, 767, 7});
	wave.PushBack({628, 109, 768, 8});
	wave.PushBack({628, 144, 768, 8});
	wave.PushBack({ 626, 174, 768, 9});
	wave.PushBack({ 625, 207, 768, 8});
	wave.speed = 0.06;
	//Static Ocean
	static_layers.x = 436;
	static_layers.y = 128;
	static_layers.w = 320;
	static_layers.h = 96;

	//Waterfall background
	Waterfall_bg.x = 436;
	Waterfall_bg.y = 224;
	Waterfall_bg.w = 320;
	Waterfall_bg.h = 672;

	//Scroll background
	scroll_bg.x = 38;
	scroll_bg.y = 69;
	scroll_bg.w = 616;
	scroll_bg.h = 447;

	//Sea background
	sea_bg.x = 849;
	sea_bg.y = 330;
	sea_bg.w = 775;
	sea_bg.h = 224;

	//Scroll Sea
	sea_scroll.x = 849;
	sea_scroll.y = 587;
	sea_scroll.w = 3316;
	sea_scroll.h = 225;

	//background transition
	transition.x = 1234;
	transition.y = 627;
	transition.w = 320;
	transition.h = 224;

	//Big waterfall
	big_waterfall.PushBack({27, 65, 172, 599});
	big_waterfall.PushBack({ 683, 48, 183, 609 });
	big_waterfall.PushBack({ 1276, 46, 198, 609 });
	big_waterfall.speed = 0.02f;

	

}

ModuleSceneWater::~ModuleSceneWater()
{
}

bool ModuleSceneWater::Start()
{
	LOG("Loading Water Scene");

	

	App->player->Enable();
	App->enemies->Enable();
	App->particles->Enable();
	App->collision->Enable();

	scroll = 1417.0;
	scroll2 = 1417.0;

	right = false;
	up = false;
	down = false;
	left = false;
	down_right = false;
	waterfall = false;
	stop = false;

	graphics1 = App->textures->Load("assets/sprites/Scenes/Scene_Water/mountain&waterfall.png");
	graphics2 = App->textures->Load("assets/sprites/Scenes/Scene_Water/waterfall.png");
	graphics3 = App->textures->Load("assets/sprites/Scenes/Scene_Water/background_waterfall.png");
	graphics4 = App->textures->Load("assets/sprites/Scenes/Scene_Water/lateral_scroll&loop.png");

	SceneWater = App->audio->LoadMusic("assets/audio/music/06_Torn_silence.ogg");
	Mix_PlayMusic(SceneWater, -1);

	//Enemies

	//Fish


	
	
	App->enemies->AddEnemy(ENEMY_TYPES::FISH, 450, 138);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 1500, 528);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 1550, 538);
	

	//Green

	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 500, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 600, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 650, 300);
	App->enemies->AddEnemy(ENEMY_TYPES::GREEN, 700, 400);

	//PowerUps
	App->powerup->AddPowerUp(App->powerup->RED, 300, 60, COLLIDER_POWER_UP);
	App->powerup->AddPowerUp(App->powerup->BLUE, 500, 40, COLLIDER_POWER_UP);


	return true;

}

update_status ModuleSceneWater::Update()
{

	right = true;


	CameraPosition();
	CameraStates();

	
	// Move camera forward -----------------------------
	//int scroll_speed = 2;
	
	//Player auto scroll
	
	//App->player->position.x += 1;

	//App->render->camera.x -= scroll_speed;

	// Draw everything --------------------------------------

	App->render->Blit(graphics1, 0, 0, &BG_Mountain, 0.55f);
	App->render->Blit(graphics1, 437, 223, &Waterfall_bg, 0.55F);
	App->render->Blit(graphics4, 437, 673, &scroll_bg, 0.55F);
	App->render->Blit(graphics4, 662, 896, &sea_bg, 0.55F);
	App->render->Blit(graphics4, 1417, 896, &sea_scroll, 0.55F);

	App->render->Blit(graphics1, 156, 44, &(waterfall1.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics1, 510, 44, &(waterfall2.GetCurrentFrame()), 0.55F);
	//App->render->Blit(graphics1, 509, 106, &(under_waterfall.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics1, 710, 55, &(waterfall3.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics1, 693, 110, &(under_waterfall.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics4, 430, 875, &(wave.GetCurrentFrame()), 0.55F);
	
	
	//App->render->Blit(graphics1, 697, 107, &(under_waterfall.GetCurrentFrame()), 0.55F);

	if (!waterfall) {
		App->render->Blit(graphics1, 0, 128, &layer_ocean_1, 0.60f);
		App->render->Blit(graphics1, 0, 144, &layer_ocean_2, 0.65f);
		App->render->Blit(graphics1, 0, 160, &layer_ocean_3, 0.65f);
		App->render->Blit(graphics1, 0, 180, &layer_ocean_4, 0.70f);
		App->render->Blit(graphics1, 0, 200, &layer_ocean_5, 0.70f);
	}

	//Small candle
	App->render->Blit(graphics4, 100, 128, &(candle1.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics4, 240, 128, &(candle1.GetCurrentFrame()), 0.55F);
	App->render->Blit(graphics4, 355, 128, &(candle1.GetCurrentFrame()), 0.55F);

	//Mid candle
	App->render->Blit(graphics4, 75, 138, &(candle2.GetCurrentFrame()), 0.57F);
	App->render->Blit(graphics4, 265, 138, &(candle2.GetCurrentFrame()), 0.57F);
	App->render->Blit(graphics4, 395, 138, &(candle2.GetCurrentFrame()), 0.57F);

	//Big candle
	App->render->Blit(graphics4,33, 152, &(candle3.GetCurrentFrame()), 0.60F);
	App->render->Blit(graphics4, 300, 152, &(candle3.GetCurrentFrame()), 0.60F);
	App->render->Blit(graphics4, 470, 160, &(candle3.GetCurrentFrame()), 0.60F);

	//Small stone
	App->render->Blit(graphics4, 300, 143, &stone1, 0.55f);
	App->render->Blit(graphics4, 500, 143, &stone1, 0.55f);
	//Mid stone
	App->render->Blit(graphics4, 335, 155, &stone2, 0.57f);
	App->render->Blit(graphics4, 500, 152, &stone2, 0.57f);
	//Big stone
	App->render->Blit(graphics4, 390, 185, &stone3, 0.60f);
	App->render->Blit(graphics4, 570, 185, &stone3, 0.60f);

	
	if (App->render->camera.y >= 1310 && App->render->camera.y < 2000) {
		App->render->Blit(graphics1, 436, 407, &transition, 0.55f);
		App->render->Blit(graphics1, 436, 631, &transition, 0.55f);
		//App->render->Blit(graphics1, 436, 407, &transition, 0.55f);
	}

	
	App->render->Blit(graphics2, 580, 232, &(big_waterfall.GetCurrentFrame()), 0.55F);

	return UPDATE_CONTINUE;
}


bool ModuleSceneWater::CleanUp()
{
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();

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

void ModuleSceneWater::CameraPosition()
{
	if (App->render->camera.x >= 1590 && App->render->camera.y <= 2390)
	{
		waterfall = true;
		right = false;
		App->render->Blit(graphics1, 436, 127, &static_layers, 0.55f);
		down = true;
		
	}
	//else if (down) down = false;
	
	if (App->render->camera.y > 3257 && App->render->camera.x <= 3000) {

		down = false;
		//right = true;		
	}

	/*
	if (App->render->camera.x < -5000) {

		right = false;
		stop = true;

		scroll -= 2.0f;
		if (scroll <= 587.0) {
			scroll = 1417.0;
		}

		scroll2 = scroll;

		App->render->Blit(graphics4, (int)scroll, 896, &sea_scroll);

		//bg1_rect.x += bg1_rect.w;
		scroll2 += sea_scroll.w;
		App->render->Blit(graphics4, (int)scroll2, 896, &sea_scroll);

	}
	*/

	


	

	
}


void ModuleSceneWater::CameraStates()
{
	int speed = 2;

	if (right) {
		App->render->camera.x += speed;
		App->player->position.x += 1;
	}

	if (left) {
		App->render->camera.x -= speed;
	}
	if (up) {
		
			App->render->camera.y -= speed;
	}
	if (down) {
			App->render->camera.y += speed;
			App->player->position.y += 1;
	}
	
	if (stop) {
		speed = 0;
		//App->player->position.x += 0;
	}
	
	

}