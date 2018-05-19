#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 23

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleRender;

class ModuleWelcomeScreen;
class ModuleSceneAir;
class ModuleSceneWater;
//class ModuleBackground;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleParticles;
class Module;
class ModuleCollision;
class ModuleEnemies;
class ModulePowerUPS;
class ModuleFonts;
class ModulePlayer2;
class ModuleWinScreen;

class ModuleLooseScreen;
class ModuleSceneTemple;
class ModuleKatana;
class ModuleKatanaArrow;
class ModuleCharSelec;
class ModuleInterface;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleWelcomeScreen* scene_start;
	ModuleSceneAir* scene_air;
	ModuleSceneWater* scene_water;
	//ModuleBackground* scene_background;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleEnemies* enemies;
	ModulePowerUPS* powerup;
	ModuleFonts* fonts;
	ModulePlayer2* player2;
	ModuleWinScreen* scene_win;
	ModuleLooseScreen* scene_loose;
	ModuleSceneTemple* scene_temple;
	ModuleKatana* katana;
	ModuleKatanaArrow* katana_arrow;
	ModuleCharSelec* charmenu;
	
	ModuleInterface* inter;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__