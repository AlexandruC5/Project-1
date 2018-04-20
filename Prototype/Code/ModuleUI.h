#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	int font_score = -1, font_time = 0;
	int alpha = 0;

	int time_on_entry = 0;
	int current_time = 0;

	int Mikolive = 4;
	bool aux = true, enemies_movement = true;
	uint score = 0, time = 9;
	char player1_score[10],  time_text[2];
	SDL_Texture* graphics = nullptr;
	SDL_Texture* black = nullptr;
	Animation* current_animation;
	Animation start;
	SDL_Rect player1, game_over, screen;
	SDL_Rect life_miko;
};

#endif