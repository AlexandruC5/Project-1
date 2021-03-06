#ifndef _WIN_SCREEN_H_
#define _WIN_SCREEN_H_

#include "Module.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;
struct Path;

enum clear_stage {
	AYIN,
	KATANA,
	KATANA_AYIN,
	AYIN_KATANA,
};

class ModuleWinScreen : public Module
{
private:

	float goUP, goDown, MaxUp, MaxDown;
	float U, M, goright, maxr;
	float goleft1, maxleft1, goleft2, maxleft2;
	bool Welcome;
	bool fade;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;

	//SDL_Texture* graphics3 = nullptr;
	Path path;
	SDL_Rect katana;
	SDL_Rect Ayin;

	int i = 0;
	SDL_Rect up;
	SDL_Rect down;
	SDL_Rect sky;
	SDL_Rect sky2;
	SDL_Rect letters;

public:
	_Mix_Music* Winfade = nullptr;

    ModuleWinScreen();
	update_status Update();
	bool CleanUp();
	bool Start();
	clear_stage state;

};
#endif // !_WIN_SCREEN_H