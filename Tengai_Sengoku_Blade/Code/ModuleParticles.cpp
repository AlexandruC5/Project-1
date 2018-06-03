#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleEnemies.h"
#include "ModuleInterface.h"
#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	//graphics = App->textures->Load("assets/sprites/miko.png");
	//graphics1 = App->textures->Load("assets/sprites/explosions/fish_explosions2.png");
	//graphics2 = App->textures->Load("assets/sprites/sho.png");
	//graphics3 = App->textures->Load("assets/enemies2.png");
	    graphics4 = App->textures->Load("assets/sprites/characters/katana/Katana_Spritesheet.png");

	card1.anim.PushBack({ 26, 136, 11, 13 });
	card2.anim.PushBack({ 49, 136, 12, 12 });
	card3.anim.PushBack({ 73, 137, 12, 11 });
	card4.anim.PushBack({ 97, 137, 13, 11 });
	
	card5.anim.PushBack({ 121, 139, 12, 7 });

	card1.anim.loop = false;
	card1.anim.speed = 1;
	card1.speed = { 10,0 };
	card1.life = 5 *500;
	
	card2.anim.loop = false;
	card2.anim.speed = 1;
	card2.speed = { 10,0 };
	card2.life = 5 * 500;
	
	card3.anim.loop = false;
	card3.anim.speed = 1;
	card3.speed = { 10,0 };
	card3.life = 5 * 500;
	
	card4.anim.loop = false;
	card4.anim.speed = 1;
	card4.speed = { 10,0 };
	card4.life = 5 * 500;

	card5.anim.loop = false;
	card5.anim.speed = 1;
	card5.speed = { 10,0 };
	card5.life = 5 * 500;

	BigC1.anim.PushBack({ 144,135,13 ,15 });
	BigC1.anim.loop = false;
	BigC1.speed = { 15,0 };
	BigC1.life = 5 * 500;

	BigC2.anim.PushBack({ 168,135,15 ,15 });
	BigC2.anim.loop = false;
	BigC2.speed = { 15,0 };
	BigC2.life = 5 * 500;

	BigC3.anim.PushBack({ 192,135, 15 ,14 });
	BigC3.anim.loop = false;
	BigC3.speed = { 15,0 };
	BigC3.life = 5 * 500;

	BigC4.anim.PushBack({ 216,136,15 ,13 });
	BigC4.anim.loop = false;
	BigC4.speed = { 15,0 };
	BigC4.life = 5 * 500;

	BigC5.anim.PushBack({ 240,138,14 ,8 });
	BigC5.anim.loop = false;
	BigC5.speed = { 15,0 };
	BigC5.life = 5 * 500;
	//Sho shots
	sword1.anim.PushBack({ 108, 151, 32, 4 });
	sword1.anim.loop = false;
	sword1.speed = { 10,0 };
	sword1.life = 5 * 500;

	sword2.anim.PushBack({ 149, 151, 32, 3 });
	sword2.anim.loop = false;
	sword2.speed = { 10,0 };
	sword2.life = 5 * 500;

	//Katana shoots
	shoot1.anim.PushBack({444, 165, 15, 8});
	shoot1.anim.loop = true;
    shoot1.life = 1400;
	shoot1.speed.x = 12;

	shoot2.anim.PushBack({396, 164, 15, 10});
	shoot2.anim.loop = true;
	shoot2.life = 1400;
	shoot2.speed.x = 12;

	shoot3.anim.PushBack({348, 164, 15, 10});
	shoot3.anim.loop = true;
	shoot3.life = 1400;
	shoot3.speed.x = 12;

	//Arrow Katana shoot
	arrow_shoot.anim.PushBack({462, 453, 16, 3});
	arrow_shoot.anim.loop = true;
	arrow_shoot.life = 1400;
	arrow_shoot.speed.x = 12;

	//Charged Katana shoot
	charged_arrow_shoot.anim.PushBack({308, 427, 35, 18});
	charged_arrow_shoot.anim.loop = false;
	charged_arrow_shoot.life = 800;
	charged_arrow_shoot.speed.x = App->scene_temple->speed;
	//charged_arrow_shoot.speed.y = 2;

	//Ayin shoots  (pu 0 - 4)

	//Power up 0 & 1
	ayin_shoot1.anim.PushBack({6, 516, 21, 5});
	ayin_shoot1.anim.loop = true;
	ayin_shoot1.life = 1400;
	ayin_shoot1.speed.x = 12;

	ayin_shoot2.anim.PushBack({31, 516, 21, 5});
	ayin_shoot2.anim.loop = true;
	ayin_shoot2.life = 1400;
	ayin_shoot2.speed.x = 12;

	ayin_shoot3.anim.PushBack({58, 516, 21, 5});
	ayin_shoot3.anim.loop = true;
	ayin_shoot3.life = 1400;
	ayin_shoot3.speed.x = 12;

	//Power up 2
	ayin_shoot1_2.anim.PushBack({ 88, 516, 27, 7 });
	ayin_shoot1_2.anim.loop = true;
	ayin_shoot1_2.life = 1400;
	ayin_shoot1_2.speed.x = 12;

	ayin_shoot2_2.anim.PushBack({ 121, 515, 27, 7 });
	ayin_shoot2_2.anim.loop = true;
	ayin_shoot2_2.life = 1400;
	ayin_shoot2_2.speed.x = 12;

	ayin_shoot3_2.anim.PushBack({ 154, 515, 27, 7 });
	ayin_shoot3_2.anim.loop = true;
	ayin_shoot3_2.life = 1400;
	ayin_shoot3_2.speed.x = 12;

	//Power up 3 & 4
	ayin_shoot1_3.anim.PushBack({ 187, 514, 33, 7 });
	ayin_shoot1_3.anim.loop = true;
	ayin_shoot1_3.life = 1400;
	ayin_shoot1_3.speed.x = 12;

	ayin_shoot2_3.anim.PushBack({ 222, 515, 33, 7 });
	ayin_shoot2_3.anim.loop = true;
	ayin_shoot2_3.life = 1400;
	ayin_shoot2_3.speed.x = 12;

	ayin_shoot3_3.anim.PushBack({ 259, 515, 33, 7 });
	ayin_shoot3_3.anim.loop = true;
	ayin_shoot3_3.life = 1400;
	ayin_shoot3_3.speed.x = 12;

	//Ayin wave (pu 1-4)

	//Power up 1
	ayin_wave.anim.PushBack({11, 529, 16, 23});
	ayin_wave.anim.loop = true;
	ayin_wave.life = 1400;
	ayin_wave.speed.x = 12;

	//Power up 2
	ayin_wave_2.anim.PushBack({ 315, 505, 17, 32 });
	ayin_wave_2.anim.loop = true;
	ayin_wave_2.life = 1400;
	ayin_wave_2.speed.x = 12;

	//Power up 3
	ayin_wave_3.anim.PushBack({ 337, 499, 17, 40 });
	ayin_wave_3.anim.loop = true;
	ayin_wave_3.life = 1400;
	ayin_wave_3.speed.x = 12;

	//Power up 4
	ayin_wave_4.anim.PushBack({ 363, 496, 27, 48 });
	ayin_wave_4.anim.loop = true;
	ayin_wave_4.life = 1400;
	ayin_wave_4.speed.x = 12;



	//Ayin charged shot wave (w1)
	wave1.anim.PushBack({14, 568, 139, 24});
	wave1.anim.loop = true;
	wave1.life = 150;
	wave1.speed.x = App->scene_temple->speed;

	//Ayin charged shot wave (w2)
	wave2.anim.PushBack({ 174, 572, 147, 15 });
	wave2.anim.loop = true;
	wave2.life = 150;
	wave2.speed.x = App->scene_temple->speed;

	//Ayin charged shot wave (w3)
	wave3.anim.PushBack({ 332, 560, 127, 26 });
	wave3.anim.loop = true;
	wave3.life = 150;
	wave3.speed.x = App->scene_temple->speed;

	//Ayin charged shot wave (w4)
	wave4.anim.PushBack({ 11, 603, 112, 26 });
	wave4.anim.loop = true;
	wave4.life = 150;
	wave4.speed.x = App->scene_temple->speed;

	//Ayin charged shot wave (w5)
	wave5.anim.PushBack({ 139, 602, 104, 27 });
	wave5.anim.loop = true;
	wave5.life = 150;
	wave5.speed.x = App->scene_temple->speed;

	//Ayin charged shot wave (w6)
	wave6.anim.PushBack({ 269, 605, 98, 17 });
	wave6.anim.loop = true;
	wave6.life = 150;
	wave6.speed.x = App->scene_temple->speed;


	//Ayin charged shot wave (w7)
	wave7.anim.PushBack({ 376, 608, 88, 12 });
	wave7.anim.loop = true;
	wave7.life = 30;
	wave7.speed.x = App->scene_temple->speed;


	//Ayin ultimate
	ulti_ayin.anim.PushBack({17, 737, 33, 41 });
	ulti_ayin.anim.PushBack({ 52, 727, 47, 59 });
	ulti_ayin.anim.PushBack({ 110, 718, 57, 67 });
	ulti_ayin.anim.PushBack({ 15, 644, 117, 66 });
	ulti_ayin.anim.loop = false;
	ulti_ayin.life = 1400;
	ulti_ayin.anim.speed = 0.15f;
	ulti_ayin.speed.x = App->scene_temple->speed + 1.5;

	//Enemy explosions on Water Stage
	/*
	waterExplosion.anim.PushBack({15, 9, 47, 44});
	waterExplosion.anim.PushBack({70, 5, 48, 45});
	waterExplosion.anim.PushBack({127, 4, 55, 62});
	waterExplosion.anim.PushBack({193, 6, 50, 58});
	waterExplosion.anim.PushBack({10, 71, 55, 60});
	waterExplosion.anim.PushBack({75, 72, 53, 63});
	waterExplosion.anim.PushBack({131, 76, 54, 65});
	waterExplosion.anim.PushBack({191, 78, 56, 63});
	waterExplosion.anim.PushBack({9, 155, 58, 65});
	waterExplosion.anim.PushBack({80, 158, 55, 60});
	waterExplosion.anim.PushBack({155, 160, 53, 59});
	waterExplosion.anim.loop = false;
	waterExplosion.anim.speed = 0.5;
	waterExplosion.life = 200;
	waterExplosion.speed = {0,0};
	*/
	waterExplosion.anim.PushBack({ 26, 522, 47, 44 });
	waterExplosion.anim.PushBack({ 81, 518, 48, 54 });
	waterExplosion.anim.PushBack({ 138, 518, 55, 61 });
	waterExplosion.anim.PushBack({ 203, 520, 51, 57 });
	waterExplosion.anim.PushBack({ 23, 583, 53, 61 });
	waterExplosion.anim.PushBack({ 85, 585, 53, 63 });
	waterExplosion.anim.PushBack({ 143,590, 53, 64 });
	waterExplosion.anim.PushBack({ 200, 591, 58, 63 });
	waterExplosion.anim.PushBack({ 21, 688,57, 64 });
	waterExplosion.anim.PushBack({ 91, 671, 55, 60 });
	waterExplosion.anim.PushBack({ 166, 673, 52, 59 });
	waterExplosion.anim.loop = false;
	waterExplosion.anim.speed = 0.3;
	waterExplosion.life = 360;
	waterExplosion.speed = { 0,0 };

	enemyattack.anim.PushBack({ 288,107,6,6 });
	enemyattack.anim.PushBack({ 299, 107, 6,6 });
	enemyattack.anim.PushBack({ 311, 107, 6,6 });
	enemyattack.anim.loop = true;
	enemyattack.anim.speed = 0.5f;
	enemyattack.life = 1200;
	enemyattack.speed.x = -3;

	enemy_bullet.anim.PushBack({40, 489, 6, 6});
	enemy_bullet.anim.PushBack({ 51, 489, 6, 6 });
	enemy_bullet.anim.PushBack({ 63, 489, 6, 6 });
	enemy_bullet.anim.PushBack({ 75, 489, 6, 6 });
	enemy_bullet.anim.PushBack({ 75, 489, 6, 6 });
	enemy_bullet.anim.PushBack({ 88, 489, 6, 6 });
	enemy_bullet.anim.PushBack({ 101, 489, 6, 6 });
	//enemy_bullet.speed.x = 
	//enemy_bullet.speed.y = 
	enemy_bullet.anim.loop = true;
	enemy_bullet.life = 1400;


	//Sharpener bullet
	sharpener_bullet.anim.PushBack({ 208, 677, 10, 8 });
	sharpener_bullet.speed.x = -7;
	sharpener_bullet.anim.loop = true;
	sharpener_bullet.life = 1400;

	//Sharpener shuriken
	sharpener_shuriken.anim.PushBack({ 167, 650, 10, 10 });
	sharpener_shuriken.anim.PushBack({ 180, 650, 10, 10 });
	sharpener_shuriken.anim.PushBack({ 193, 651, 8, 8 });
	sharpener_shuriken.anim.PushBack({ 204, 651, 8, 8 });
	sharpener_shuriken.anim.PushBack({ 215, 650, 10, 10 });
	sharpener_shuriken.anim.PushBack({ 228, 650, 10, 10 });
	//sharpener_shuriken.speed.x = -7;
	sharpener_shuriken.anim.loop = true;
	sharpener_shuriken.life = 1400;

	//Power Up & Power down
	power_up.anim.PushBack({436, 657, 30, 17 });
	power_up.anim.PushBack({ 436, 675, 29, 17 });
	power_up.anim.PushBack({436, 693, 29, 18 });
	power_up.anim.loop = true;
	power_up.anim.speed = 0.20f;
	power_up.life = 800;

	power_down.anim.PushBack({ 467, 675, 31, 17 });
	power_down.anim.PushBack({ 466, 694, 31, 17 });
	power_down.anim.loop = true;
	power_down.anim.speed = 0.10f;
	power_down.life = 800;

	//Coin
	coin_100.anim.PushBack({ 406, 724, 9, 7 });
	coin_100.anim.PushBack({ 406, 733, 9, 7 });
	coin_100.anim.PushBack({ 406, 742, 9, 7 });
	coin_100.anim.loop = true;
	coin_100.anim.speed = 0.20f;
	coin_100.life = 1000;

	coin_200.anim.PushBack({ 418, 724, 11, 7 });
	coin_200.anim.PushBack({ 418, 733, 11, 7 });
	coin_200.anim.PushBack({ 418, 742, 11, 7 });
	coin_200.anim.loop = true;
	coin_200.anim.speed = 0.20f;
	coin_200.life = 1000;

	coin_500.anim.PushBack({ 432, 724, 11, 7 });
	coin_500.anim.PushBack({ 432, 733, 11, 7 });
	coin_500.anim.PushBack({ 432, 742, 11, 7 });
	coin_500.anim.loop = true;
	coin_500.anim.speed = 0.20f;
	coin_500.life = 1000;

	coin_1000.anim.PushBack({ 446, 724, 13, 7 });
	coin_1000.anim.PushBack({ 446, 733, 13, 7 });
	coin_1000.anim.PushBack({ 446, 742, 13, 7 });
	coin_1000.anim.loop = true;
	coin_1000.anim.speed = 0.20f;
	coin_1000.life = 1000;

	coin_2000.anim.PushBack({ 462, 724, 15, 7 });
	coin_2000.anim.PushBack({ 462, 733, 15, 7 });
	coin_2000.anim.PushBack({ 462, 742, 15, 7 });
	coin_2000.anim.loop = true;
	coin_2000.anim.speed = 0.20f;
	coin_2000.life = 1000;

	coin_4000.anim.PushBack({ 480, 724, 15, 7 });
	coin_4000.anim.PushBack({ 480, 733, 15, 7 });
	coin_4000.anim.PushBack({ 480, 742, 15, 7 });
	coin_4000.anim.loop = true;
	coin_4000.anim.speed = 0.20f;
	coin_4000.life = 1000;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	//App->textures->Unload(graphics);
	//App->textures->Unload(graphics1);
	//App->textures->Unload(graphics2);
	//App->textures->Unload(graphics3);
	App->textures->Unload(graphics4);


	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	// Update Particle Emmiters
	ParticleEmmiter* p_emmiter = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_EMMITERS; ++i)
	{
		p_emmiter = emitters_active[i];

		if (p_emmiter != nullptr)
		{
			if (p_emmiter->Kill())
			{
				delete p_emmiter;
				emitters_active[i] = nullptr;
			}
			else
			{
				p_emmiter->Update();
			}
		}
	}

	// Update Particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			active[i]->Update(graphics4);

			if (!active[i]->Valid())
			{
				Particle* p = active[i];
				delete p;
				active[i] = nullptr;
			}
		}
	}

	//HandleParticleArray();

	return UPDATE_CONTINUE;
}


void ModuleParticles::AddParticle(const Particle& particle, int x, int y, /*int speedx, int speedy,*/ COLLIDER_TYPE collider_type, PARTICLE_TYPE particle_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			/*p->speed.x = speedx;
			p->speed.y = speedy;*/
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);

			active[i] = p;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------

bool ModuleParticles::AddParticle(Particle* p)
{
	bool ret = false;

	if (p != nullptr)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES && !ret; ++i)
		{
			if (this->active[i] == nullptr)
			{
				this->active[i] = p;
				ret = true;
			}
		}
	}

	return ret;
}


bool ModuleParticles::AddEmmiter(EmmiterType type, fPoint* pos)
{
	if (pos != nullptr)
	{
		for (uint i = 0; i < MAX_ACTIVE_EMMITERS; ++i)
		{
			ParticleEmmiter* p_emmiter = emitters_active[i];

			if (p_emmiter == nullptr)
			{
				switch (type)
				{
				case AJIN_ULT:
					emitters_active[i] = new AjinUlt(&ulti_ayin, pos);
					break;
				case SHARPENER_BURST:
					emitters_active[i] = new SharpenerBurst(&sharpener_shuriken, pos);
					break;
				}

				return (emitters_active[i] != nullptr && !emitters_active[i]->Kill());
			}
		}
	}
}

void ModuleParticles::HandleParticleArray()
{
	for (uint i2 = 0; i2 < MAX_ACTIVE_PARTICLES; ++i2)
	{
		if (active[i2] != nullptr)
		{
			if (i2 > 0 && active[i2 - 1] == nullptr)
			{
				active[i2 - 1] = active[i2];
				active[i2] = nullptr;
				i2--;
			}
		}
	}
}

int ModuleParticles::GetAvailableStorage(uint wanted) const
{
	int ret = 0;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
			ret++;
	}

	ret = MIN(wanted, ret);

	return ret;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{

			if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHOT)
			{
				if (c2 == App->katana->coll) {

					if (timer) {
						time_on_entry = SDL_GetTicks();
						timer = false;
					}
					current_time = SDL_GetTicks() - time_on_entry;

					if (current_time > 1000) {
						App->katana->explosion = true;
						//App->audio->PlaySoundEffects(App->enemies->fx_death);
						//App->particles->AddParticle(App->particles->explosion, active[i]->position.x, active[i]->position.y);
						//App->audio->PlaySoundEffects(koyori_death);
						App->inter->num_life_katana--;
						timer = true;
					}
					App->katana->state = DEATH;
				}
				
			}



			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
 {
	if (collider != nullptr)
		 collider->to_delete = true;
	}


void Particle::Update(SDL_Texture* tex)
{
	actual_life = SDL_GetTicks() - born;

	//LOG("Updating Particle - actual_life: %d", actual_life);

	position.x += speed.x + App->scene_temple->speed;
	position.y += speed.y;

	if (tex != nullptr)
	{
		App->render->Blit(
			tex,
			int(position.x),
			int(position.y),
			&(anim.GetCurrentFrame()));
	}

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

bool Particle::Valid()
{
	bool ret = true;

	if (life > 0)
	{
		if (actual_life > life)
		{
			LOG("Particle dies after %d", actual_life);
			ret = false;
		}
	}
	else if (anim.Finished())
	{
		ret = false;
	}

	return ret;
}


ParticleEmmiter::ParticleEmmiter(Particle* p, fPoint* pos)
	: particle_emited(p), position(pos), life_time(0), repetitions_current(0)
{
	trigger_time = SDL_GetTicks();
	valid = (pos != nullptr);
	offset.SetToZero();
}

AjinUlt::AjinUlt(Particle* p, fPoint* pos) : ParticleEmmiter(p, pos)
{
	interval = 180;
	repetitions_total = 4;
	offset.x = 5;
	offset.y = -35;
	speed.x = 5.f;
	speed.y = 0.f;
	total_particles = 1;
}


void AjinUlt::Update()
{
	life_time = SDL_GetTicks() - trigger_time;

	if (repetitions_current == repetitions_total)
	{
		valid = false;
	}
	else if (life_time > interval * repetitions_current)
	{
		Particle* p = nullptr;
		p = new Particle(*particle_emited);
		p->born = SDL_GetTicks();
		p->position.x = int(position->x) + offset.x;
		p->position.y = int(position->y) + offset.y;
		p->speed.x = speed.x;
		p->speed.y = speed.y;
		//p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_PLAYER_AYIN_ULTI, App->particles);
		App->particles->AddParticle(p);

		repetitions_current++;
	}
}

SharpenerBurst::SharpenerBurst(Particle* p, fPoint* pos) : ParticleEmmiter(p, pos)
{
	interval = 250;
	repetitions_total = 4;
	total_particles = 32;
	speed_multiplier = 6.0f;
	offset.x = 50;
	offset.y = 40;
}


void SharpenerBurst::Update()
{
	life_time = SDL_GetTicks() - trigger_time;

	if (repetitions_current == repetitions_total)
	{
		valid = false;
	}
	else if (life_time > interval * repetitions_current)
	{
		double angle_interval = 360.f / total_particles;

		// Radius casting using the angle to change speeds
		for (double angle = 0; angle < 360; angle += angle_interval)
		{
			Particle* p = new Particle(*particle_emited);
			p->born = SDL_GetTicks();
			p->position.x = int(position->x) + offset.x;
			p->position.y = int(position->y) + offset.y;

			// Each has different direction
			p->speed.x = SDL_sin(angle) * speed_multiplier;
			p->speed.y = SDL_cos(angle) * speed_multiplier;

			//p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_ENEMY_SHARPENER_KNIFE, App->particles);

			App->particles->AddParticle(p);
		}

		repetitions_current++;
	}
}

