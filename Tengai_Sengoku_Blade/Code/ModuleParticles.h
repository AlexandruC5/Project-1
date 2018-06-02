#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 400
#define MAX_ACTIVE_EMMITERS 30

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum PARTICLE_TYPE
{
	PARTICLE_NONE,
	PARTICLE_SHOT,
	PARTICLE_SHOT_KATANA,
	PARTICLE_SHOT_AYIN,
	PARTICLE_ULTI_AYIN,
	PLAYER_ENEMY,
	PARTICLE_ENEMY_SHOT,
	PARTICLE_POWER_UP_KATANA,
	PARTICLE_POWER_UP_AYIN,

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
	Uint32 actual_life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	void Update(SDL_Texture* tex = nullptr);
	bool Valid();
	//bool Update();
};

class ParticleEmmiter;

enum EmmiterType
{
	NONE = 0,
	AJIN_ULT,
	SHARPENER_BURST
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
	void AddParticle(const Particle& particle, int x, int y, /*int speedx, int speedy,*/ COLLIDER_TYPE collider_type = COLLIDER_NONE, PARTICLE_TYPE particle_type = PARTICLE_NONE, Uint32 delay = 0);
	bool AddParticle(Particle* p = nullptr);
	bool AddEmmiter(EmmiterType type, fPoint* pos = nullptr);
	void HandleParticleArray();
	int GetAvailableStorage(uint wanted) const;

private:

	
	SDL_Texture * graphics4 = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	ParticleEmmiter* emitters_active[MAX_ACTIVE_EMMITERS];

	
	uint last_particle = 0;

public:
	Particle* lista_shurikens[16];
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

	//Ayin
	Particle ayin_wave, ayin_wave_2, ayin_wave_3, ayin_wave_4;
	Particle arrow_shoot, charged_arrow_shoot;
	Particle ayin_shoot1_2, ayin_shoot2_2, ayin_shoot3_2;
	Particle ayin_shoot1_3, ayin_shoot2_3, ayin_shoot3_3;
	Particle enemy_bullet;
	Particle wave1, wave2, wave3, wave4, wave5, wave6, wave7;
	Particle ulti_ayin;

	//Sharpener enemy
	Particle sharpener_bullet, sharpener_shuriken;
	bool timer = false;
	int current_time = 1200, time_on_entry = 0;

	int lista_valores_speed_x[16];
	int lista_valores_speed_y[16];

	Particle power_up, power_down;

};

class ParticleEmmiter
{
public:

	ParticleEmmiter(Particle* p = nullptr, fPoint* pos = nullptr);

	bool Kill() { return !valid; }
	virtual void Update() {}

protected:

	bool valid = true;

public:

	Particle* particle_emited;
	fPoint* position = nullptr;
	int total_particles = 0;

	// position adjust
	iPoint offset;

	// timmings
	Uint32 trigger_time = 0;
	Uint32 life_time = 0;
	Uint32 interval = 0;
	float repetitions_total = 0;
	float repetitions_current = 0;
};

class AjinUlt : public ParticleEmmiter
{
public:

	AjinUlt(Particle* p = nullptr, fPoint* pos = nullptr);
	void Update();

	fPoint speed;
};

class SharpenerBurst : public ParticleEmmiter
{
public:

	SharpenerBurst(Particle* p = nullptr, fPoint* pos = nullptr);
	void Update();

	float speed_multiplier = 1.0f;
};


#endif // __MODULEPARTICLES_H__