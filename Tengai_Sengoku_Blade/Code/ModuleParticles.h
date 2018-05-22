#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE
{
	PARTICLE_NONE,
	PARTICLE_SHOT,
	PARTICLE_SHOT_KATANA,
	PARTICLE_SHOT_AYIN,
	PLAYER_ENEMY,
	PARTICLE_ENEMY_SHOT

};
struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, PARTICLE_TYPE particle_type = PARTICLE_NONE, Uint32 delay = 0);
	

private:

	//SDL_Texture * graphics = nullptr;
	//SDL_Texture * graphics1 = nullptr;
	//SDL_Texture * graphics2 = nullptr;
	//SDL_Texture * graphics3 = nullptr;
	SDL_Texture * graphics4 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	int time;
	Particle explosion;
	Particle card1, card2, card3, card4, card5;
	Particle BigC1, BigC2, BigC3, BigC4, BigC5;
	Particle waterExplosion;
	Particle sword1, sword2;
	Particle enemyattack;
	//Katana
	Particle shoot1, shoot2, shoot3;
	Particle ayin_shoot1, ayin_shoot2, ayin_shoot3;
	Particle ayin_wave;
	Particle arrow_shoot, charged_arrow_shoot;
	Particle enemy_bullet;
	Particle wave1, wave2, wave3, wave4, wave5, wave6, wave7;
	bool timer = false;
	int current_time = 1200, time_on_entry = 0;

};

#endif // __MODULEPARTICLES_H__