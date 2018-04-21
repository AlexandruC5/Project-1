#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
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
	graphics = App->textures->Load("assets/sprites/miko.png");
	graphics1 = App->textures->Load("assets/sprites/explosions/fish_explosions2.png");
	graphics2 = App->textures->Load("assets/sprites/sho.png");

	card1.anim.PushBack({ 26, 136, 11, 13 });
	card2.anim.PushBack({ 49, 136, 12, 12 });
	card3.anim.PushBack({ 73, 137, 12, 11 });
	card4.anim.PushBack({ 97, 137, 13, 11 });
	card5.anim.PushBack({ 121, 139, 12, 7 });

	card1.anim.loop = false;
	card1.anim.speed = 1;
	card1.speed = { 5,0 };
	card1.life = 5 *500;
	
	card2.anim.loop = false;
	card2.anim.speed = 1;
	card2.speed = { 5,0 };
	card2.life = 5 * 500;
	
	card3.anim.loop = false;
	card3.anim.speed = 1;
	card3.speed = { 5,0 };
	card3.life = 5 * 500;
	
	card4.anim.loop = false;
	card4.anim.speed = 1;
	card4.speed = { 5,0 };
	card4.life = 5 * 500;

	card5.anim.loop = false;
	card5.anim.speed = 1;
	card5.speed = { 5,0 };
	card5.life = 5 * 500;

	//Sho shots
	sword1.anim.PushBack({ 108, 151, 32, 4 });
	sword1.anim.loop = false;
	sword1.speed = { 5,0 };
	sword1.life = 5 * 500;

	sword2.anim.PushBack({ 149, 151, 32, 3 });
	sword2.anim.loop = false;
	sword2.speed = { 5,0 };
	sword2.life = 5 * 500;



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

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(graphics1);

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
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			App->render->Blit(graphics2, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
 
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
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
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

			AddParticle(explosion, active[i]->position.x, active[i]->position.y);
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