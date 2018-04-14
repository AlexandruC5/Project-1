#ifndef __ModuleSceneWater_H__
#define __ModuleSceneWater_H__

#include "Module.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneWater : public Module
{
public:

	ModuleSceneWater();
	~ModuleSceneWater();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics1 = nullptr;
	SDL_Texture * graphics2 = nullptr;
	SDL_Texture * graphics3 = nullptr;
	SDL_Texture * graphics4 = nullptr;

	Mix_Music* SceneWater = nullptr;

};

#endif // __ModuleSceneWater_H__
