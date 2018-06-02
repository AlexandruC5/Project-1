#ifndef _ModuleLooseScene_H
#define _ModuleLooseScene_H

#include "Module.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;

enum mode {
	KATANA1,
	AYIN1,
	K1A2,
	A1K2,
};

enum numplayers {
	ONE,TWO,
};
class ModuleLooseScreen : public Module
{
private:


	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;
	SDL_Texture* graphics4 = nullptr;

	SDL_Rect firstN;
	SDL_Rect secondN;
	SDL_Rect thirdN;
	SDL_Rect forthN;
	SDL_Rect fifthN;


	SDL_Rect background;
	SDL_Rect ranking;
	SDL_Rect letters2;
	SDL_Rect letters1;
	SDL_Rect name;

	SDL_Rect ayin;
	SDL_Rect katana;
	SDL_Rect let3;
	SDL_Rect let4;
	SDL_Rect let5;

	SDL_Rect level;
	_Mix_Music* music = nullptr;
	int speed = 1;
	int count;
	bool down;
	float goup1,goup2;
	bool stay;
	char op[10];
	uint scorek;
public:

	ModuleLooseScreen();
	~ModuleLooseScreen();
	update_status Update();
	mode mode;
	numplayers numplayers;
	char player1Score[10], player2Score[10];
	int fontScore = -1;
	bool CleanUp();
	bool Start();

};

#endif





