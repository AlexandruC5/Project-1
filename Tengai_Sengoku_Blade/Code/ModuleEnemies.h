#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#define MAX_ENEMIES 100

// TODO 2: Add a new enemy: Brown Cookies!

// TODO 3: Have the Brown Cookies describe a path in the screen

// TODO 4: Create a new enemy type: the Mech

enum ENEMY_TYPES
{
	NO_TYPE,
	FISH,
	Green,
	Green2,
	ORIENTAL_GENIUS,
	RED,
	DemonPegTop,
	DemonWheel,
	SharpenerKnife,
	Power_up,
	Ulti_parchment,
	Coin,
	Chariot,
	Ball,
	Ball2,
	Pagoda,
	Demon

};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y, path_type;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, int path_type = 0);
	
private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	bool timer = false;
	int current_time = 700, time_on_entry = 0;

	bool timer_2 = false;
	int current_time_2 = 700, time_on_entry_2 = 0;

	bool shoot = true;
	bool spritec;
	

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
	SDL_Texture* sprites2;

	int num_pegtop = 0;
	int pegtop_life = 0;
};

#endif // __ModuleEnemies_H__