#ifndef __ModuleSceneWater_H__
#define __ModuleSceneWater_H__

#include "Module.h"
#include "Animation.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleSceneWater : public Module
{
public:

	ModuleSceneWater();
	~ModuleSceneWater();

	void CameraPosition();
	void CameraStates();
	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool right, left, up, down,down_right, waterfall, stop;
	int timer;
	float scroll,scroll2;
	SDL_Texture * graphics1 = nullptr;
	SDL_Texture * graphics2 = nullptr;
	SDL_Texture * graphics3 = nullptr;
	SDL_Texture * graphics4 = nullptr;

	SDL_Rect BG_Mountain;
	SDL_Rect layer_ocean_1;
	SDL_Rect layer_ocean_2;
	SDL_Rect layer_ocean_3;
	SDL_Rect layer_ocean_4;
	SDL_Rect layer_ocean_5;
	SDL_Rect static_layers;
	SDL_Rect Waterfall_bg;
	SDL_Rect scroll_bg;
	SDL_Rect sea_bg;
	SDL_Rect sea_scroll;
	SDL_Rect stone1;
	SDL_Rect stone2;
	SDL_Rect stone3;

	Animation waterfall1;
	Animation waterfall2;
	Animation waterfall3;
	Animation under_waterfall;
	Animation candle1;
	Animation candle2;
	Animation candle3;

	Mix_Music* SceneWater = nullptr;

};

#endif // __ModuleSceneWater_H__
