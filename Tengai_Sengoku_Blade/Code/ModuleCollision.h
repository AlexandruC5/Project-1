

#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#include "Module.h"


enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PARED,
	COLLIDER_PLAYER,

	COLLIDER_ENEMY,
	COLLIDER_ENEMY_PEGTOP,
	COLLIDER_ENEMY_WHEEL,
	COLLIDER_ENEMY_GREENOVNI,
	COLLIDER_ENEMY_REDNOVNI,
	COLLIDER_ENEMY_PAGODA,
	COLLIDER_ENEMY_CANNONTANK,
	COLLIDER_ENEMY_SHARPENER_KNIFE,

	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_POWER_UP,
	COLLIDER_ULTI_PARCHMENT,
	COLLIDER_SHOOT,
	COLLIDER_PLAYER_KATANA_SHOT,
	COLLIDER_PLAYER_AYIN_SHOT,
	COLLIDER_PLAYER_AYIN_ULTI,
	COLLIDER_PLAYER_KATANA_SHOT_ARROW,
	COLLIDER_PLAYER_KATANA_CHARGED_SHOT_ARROW,
	COLLIDER_MAX,
	COLLIDER_HITBOX_KATANA,
	COLLIDER_HITBOX_AYIN

};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

	
	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	void GodMode();
	void DebugDraw();

private:

	Collider * colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
	bool god_mode = false;
};

#endif // __ModuleCollision_H__


