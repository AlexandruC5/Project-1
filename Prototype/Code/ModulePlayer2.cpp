#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleSceneWater.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUPS.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 60;

	// idle-forward-downwards animation 
	forward.PushBack({ 38 ,9 ,29 ,27 });
	forward.PushBack({ 75 ,10 ,29 ,26 });
	forward.PushBack({ 112, 10, 29, 27 });


	forward.speed = 0.1f;

	// move upwards-backwards animation
	mid.PushBack({ 187, 95, 26, 29 });
	mid.PushBack({ 230, 95, 24, 28 });
	mid.PushBack({ 270, 95, 26, 28 });
	mid.loop = false;
	mid.speed = 0.1f;

	mid2.PushBack({ 270, 95, 26, 28 });
	mid2.PushBack({ 230, 95, 24, 28 });
	mid2.PushBack({ 187, 95, 26, 29 });
	mid2.loop = false;
	mid2.speed = 0.1f;

	// move upwards-backwards animation
	backward.PushBack({ 193, 53, 26, 29 });
	backward.PushBack({ 233, 54, 27, 28 });
	backward.PushBack({ 272, 54, 27, 28 });
	//backward.loop = false;
	backward.speed = 0.1f;



}