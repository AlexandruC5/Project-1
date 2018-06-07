#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
//#include "ModuleBackground.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleSceneAir.h"
#include "ModuleSceneWater.h"
#include "ModuleUI.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleFonts.h"
#include "ModulePowerUPS.h"
#include "ModulePlayer2.h"
#include "WinScreen.h"
#include "ModuleSceneLoose.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleKatanaArrow.h"
#include "ModuleAyinArrow.h"
#include "CharSelec.h"
#include "ModuleInterface.h"
#include "ModuleAyinUltimate.h"
#include "ModuleSceneIntro.h"
Application::Application()
{
	
	
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = audio = new ModuleAudio();
	//modules[5] = scene_background = new ModuleBackground();
	modules[5] = scene_start = new ModuleWelcomeScreen();
	modules[6] = charmenu = new ModuleCharSelec();
	modules[7] = scene_air = new ModuleSceneAir();
	//modules[7] = scene_temple = new ModuleSceneTemple();
	modules[8] = scene_water = new ModuleSceneWater();
	modules[9] = scene_temple = new ModuleSceneTemple();
	//modules[8] = katana = new ModuleKatana();
	modules[10] = enemies = new ModuleEnemies();
	modules[11] = player = new ModulePlayer();
	modules[12] = fade = new ModuleFadeToBlack();
	
	//modules[11] = collision = new ModuleCollision();
	modules[13] = powerup = new ModulePowerUPS();
	modules[14] = fonts = new ModuleFonts();
	modules[15] = player2 = new ModulePlayer2();

	modules[16] = scene_win = new ModuleWinScreen();
	modules[17] = scene_loose = new ModuleLooseScreen();
	//modules[16] = scene_temple = new ModuleSceneTemple();
	
	//modules[18] = katana_arrow = new ModuleKatanaArrow();
	modules[18] = katana_arrow = new ModuleKatanaArrow();
	modules[19] = katana = new ModuleKatana();
	//modules[19] = ayin = new ModuleAyin();
	
	modules[20] = ayin_arrow = new ModuleAyinArrow();
	modules[21] = ayin = new ModuleAyin();
	modules[22] = ulti_ayin = new ModuleAyinUltimate();
	//modules[19] = collision = new ModuleCollision();
	
	modules[23] = particles = new ModuleParticles();
	modules[24] = inter = new ModuleInterface();
	modules[25] = collision = new ModuleCollision();
	//modules[21] = charmenu = new ModuleCharSelec();
	modules[26] = scene_intro = new ModuleSceneIntro();
	
}
	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	App->inter->Disable();
	player->Disable();
	scene_air->Disable();
	scene_water->Disable();
	collision->Disable();
	enemies->Disable();
	scene_temple->Disable();
	katana->Disable();
	ayin->Disable();
	
	

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;
		

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;


	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
	
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}