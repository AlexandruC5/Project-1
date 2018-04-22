#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

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
<<<<<<< HEAD
class ModuleWinScreen;
=======
class ModuleUI;

>>>>>>> 54aa95bf156168005b3390bae710e2762880e5c4


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
<<<<<<< HEAD
	ModuleWinScreen* scene_win;
=======
	//ModuleUI* UI;

>>>>>>> 54aa95bf156168005b3390bae710e2762880e5c4
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