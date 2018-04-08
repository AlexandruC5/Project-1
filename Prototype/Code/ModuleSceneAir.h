#ifndef __ModuleSceneAir_H__
#define __ModuleSceneAir_H__

#include "Module.h"
#include "Globals.h"

#define NUM_LAYERS 4

struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;


class ModuleSceneAir : public Module {

private:

	//Background variables
	int x = 0;
	int y = 0;

	//Layers
	int xLayer = 0;
	int yLayer = 0;

	//timers
	//Uint32 start_time;
	//Uint32 total_time;

	SDL_Rect* textrect[NUM_LAYERS];
	SDL_Texture* textures[NUM_LAYERS];

	_Mix_Music* music = nullptr;
	Mix_Chunk* shipSpawn = nullptr;

public:
	int timer = 0;
	bool right, left, up, down;
	bool Init();
	bool loadMapTextures();
	update_status Update();
	bool CleanUp();
	bool Start();
	ModuleSceneAir();
	~ModuleSceneAir();

};


#endif