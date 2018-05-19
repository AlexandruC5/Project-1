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
	//SDL_Texture* graphics3 = nullptr;
	Path path;
	SDL_Rect katana;

	int i = 0;
	SDL_Rect up;
	SDL_Rect down;
	SDL_Rect sky;
	SDL_Rect sky2;
	SDL_Rect letters;
	_Mix_Music* Winfade = nullptr;

public:
ModuleWinScreen();
	~ModuleWinScreen();
	update_status Update();
	bool Init();
	bool CleanUp();
	bool Start();
	void move();
	
};
#endif // !_WIN_SCREEN_H