#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading Particles");
	graphics = App->textures->Load("assets/sprites/miko.png");
	//basic attack different sprite for the same attack but the attack isn't animated just differents sprites for the same attack
	card1.anim.PushBack({ -26, -136, 11, 13 });
	card1.anim.loop = false;
	card1.speed = { 5,0 };
	card1.life = 5 * 1000;

	card2.anim.PushBack({ -49, -136, 12, 12 });
	card2.anim.loop = false;
	card2.speed = { 5,0 };
	card2.life = 5 * 1000;

	card3.anim.PushBack({ -73, -137, 12, 11 });
	card3.anim.loop = false;
	card3.speed = { 5,0 };
	card3.life = 5 * 1000;

	card4.anim.PushBack({ -97, -137, 13, 11 });
	card4.anim.loop = false;
	card4.speed = { 5,0 };
	card4.life = 5 * 1000;

	card5.anim.PushBack({ -121, -139, 12, 7 });
	card5.anim.loop = false;
	card5.speed = { 5,0 };
	card5.life = 5 * 1000;

	return true;
}

//Unload

bool ModuleParticles::CleanUp() {
	LOG("Unloading prticles");
	App->textures->Unload(graphics);
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	return true;
}

update_status ModuleParticles::Update() {
	for (uint i = 0;  i < MAX_ACTIVE_PARTICLES; i++) {
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
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

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}