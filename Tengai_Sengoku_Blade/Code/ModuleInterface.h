#ifndef __MODULEINTERFACE_H__
#define __MODULEINTERFACE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "Application.h"

struct SDL_Texture;

enum UI {
	P1AYIN,
	P1KATANA,
	P2KATANAAYIN,
	P2AYINKATANA,
};
class ModuleInterface : public Module
{
public:
	ModuleInterface();
	~ModuleInterface();

	bool Start();
	update_status Update();
	bool CleanUp();
	UI  UIstate;
public:
	int font_score = -1, font_time = 0;
	int alpha = 0;

	int pos_score = 0;

	bool update_score = false;

	int time_on_entry = 0;
	int current_time = 0;

	int num_life_katana, num_life_ayin;
	bool aux = true, enemies_movement = true, game_over_katana = false, game_over_ayin = false;
	uint score_katana = 0, score_ayin = 0, time = 9;
	char player1_score[10], player2_score[10], time_text[2];

	SDL_Texture* graphics = nullptr;
	SDL_Texture* black = nullptr;
	Animation* current_animation;
	Animation start;
	SDL_Rect player1, player2, game_over, screen;
	SDL_Rect life_katana, life_ayin;
};

#endif // __MODULESCENESTART_H__
