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
	enemy_bullet.speed.x = -7;
	enemy_bullet.anim.loop = true;
	enemy_bullet.life = 1400;

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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			//App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			//App->render->Blit(graphics2, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			//App->render->Blit(graphics3, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			App->render->Blit(graphics4, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if(p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}
/*
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;



	active[last_particle++] = p;
}
*/
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, PARTICLE_TYPE particle_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);

			active[i] = p;
			break;
		}
	}
}
// -------------------------------------------------------------
// -------------------------------------------------------------
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
						//App->ui->num_life_koyori--;
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


bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}