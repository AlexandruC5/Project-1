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



	card1.anim.PushBack({ 26, 136, 11, 13 });
	card2.anim.PushBack({ 49, 136, 12, 12 });
	card3.anim.PushBack({ 73, 137, 12, 11 });
	card4.anim.PushBack({ 97, 137, 13, 11 });
	card5.anim.PushBack({ 121, 139, 12, 7 });
	/*laser.anim.PushBack({ 144, 135, 13, 15 });
	laser.anim.PushBack({ 168, 135, 15, 15 });
	laser.anim.PushBack({ 192, 135, 15, 14 });
	laser.anim.PushBack({ 216, 136, 15, 13 });
	laser.anim.PushBack({ 240, 138, 14, 8 });
	laser.anim.PushBack({ 264, 135, 13, 15 });
	laser.anim.PushBack({ 288, 135, 15, 15 });
	laser.anim.PushBack({ 312, 135, 15, 14 });
	laser.anim.PushBack({ 336, 136, 15, 13 });
	laser.anim.PushBack({ 360, 138, 14, 8 });
	*/
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
	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

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