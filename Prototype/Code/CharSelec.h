#ifndef _ModuleCharSelec_H
#define _ModuleCharSelec_H

#include"Module.h"
#include"Animation.h"
#include"Path.h"
struct SDL_Rect;
struct SDL_Texture;
struct _Mix_Music;
struct Mix_Chunk;

enum menu_state {

	
	KATANAP1,
	AYINP1,
	RANDOMP1,
	KATANAAYIN,
	AYINKATANA,
	RANDOMKATANA,
	RANDOMAYIN,
	AYINRANDOM,
	KATANARANDOM,
	OUTOFTIME,
};
enum players_state{
	ONEPLAYER,
	TWOPLAYERS,
};

class ModuleCharSelec  : public Module
{
private:
	float left, right, bgmove;
	int rand, clock,frames,s;
	SDL_Rect blueline;
	SDL_Rect sky;
	SDL_Rect background;
	SDL_Rect background2;
	SDL_Rect square1;
	SDL_Rect square2;
	SDL_Rect n0;
	SDL_Rect n1;
	SDL_Rect n2;
	SDL_Rect n3;
	SDL_Rect n4;
	SDL_Rect n5;
	SDL_Rect n6;
	SDL_Rect n7;
	SDL_Rect n8;
	SDL_Rect n9;
	SDL_Rect katana;
	SDL_Rect headkatana;
	SDL_Rect lettersK;
	SDL_Rect ayin;
	SDL_Rect headayin;
	SDL_Rect lettersA;
	SDL_Rect time;
	SDL_Rect random;
	
	SDL_Texture* graphics1 = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* graphics3 = nullptr;
	SDL_Texture* graphics4 = nullptr;
	SDL_Texture* graphics5 = nullptr;
	SDL_Texture* graphics6 = nullptr;
	SDL_Texture* graphics7 = nullptr;
	Animation Kidle;
	Animation Aidle;

	void CheckState();
public:
	ModuleCharSelec();
	~ModuleCharSelec();
	update_status Update();
	menu_state state = KATANAP1;
	players_state players = ONEPLAYER;
	bool Init();
	bool CleanUp();
	bool Start();
};


#endif // !_CharSelec_H
