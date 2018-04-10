#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

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



	laser.anim.PushBack({ 26, 136, 11, 13 });
	laser.anim.PushBack({ 49, 136, 12, 12 });
	laser.anim.PushBack({ 73, 137, 12, 11 });
	laser.anim.PushBack({ 97, 137, 13, 11 });
	laser.anim.PushBack({ 121, 139, 12, 7 });
	laser.anim.PushBack({ 144, 135, 13, 15 });
	laser.anim.PushBack({ 168, 135, 15, 15 });
	laser.anim.PushBack({ 192, 135, 15, 14 });
	laser.anim.PushBack({ 216, 136, 15, 13 });
	laser.anim.PushBack({ 240, 138, 14, 8 });
	laser.anim.PushBack({ 264, 135, 13, 15 });
	laser.anim.PushBack({ 288, 135, 15, 15 });
	laser.anim.PushBack({ 312, 135, 15, 14 });
	laser.anim.PushBack({ 336, 136, 15, 13 });
	laser.anim.PushBack({ 360, 138, 14, 8 });
	laser.anim.loop = false;
	laser.anim.speed = 1;
	laser.speed = { 5,0 };
	laser.life = 5 * 500;
	
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

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

	return ret;
}