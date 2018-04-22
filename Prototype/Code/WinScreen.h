#ifndef _WIN_SCREEN_H_
#define _WIN_SCREEN_H_

#include "Module.h"
#include "Animation.h"
#include "Path.h"
struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;
class ModuleWinScreen : public Module
{
private:

	float goUP, goDown, MaxUp, MaxDown;
	bool now;
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;

	
	SDL_Rect up;
	SDL_Rect down;
	SDL_Rect sky;

	_Mix_Music* music = nullptr;

public:

	ModuleWinScreen();
	~ModuleWinScreen();
	update_status Update();
	bool Init();
	bool CleanUp();
	bool Start();

};
#endif // !_WIN_SCREEN_H

