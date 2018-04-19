#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePowerUPS.h"
#include "ModuleParticles.h"
#include "Path.h"


ModulePowerUPS::ModulePowerUPS()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerUps[i] = nullptr;

	RED.anim.PushBack({ 4, 32, 31, 20 });
	RED.anim.PushBack({ 42, 31, 31, 20 });
	RED.anim.PushBack({ 82, 32, 31, 20 });
	RED.anim.PushBack({ 126, 31, 31, 21 });
	RED.anim.PushBack({ 167, 31, 31, 21 });
	RED.anim.PushBack({ 205, 29, 31, 21 });
	RED.anim.PushBack({ 246, 30, 31, 22 });
	RED.anim.PushBack({ 289, 30, 31, 22 });
	RED.anim.PushBack({ 330, 30, 31, 21 });
	RED.anim.PushBack({ 370, 30, 31, 21 });
	RED.anim.PushBack({ 414, 29, 31, 20 });
	RED.anim.PushBack({ 452, 31, 31, 20 });
	RED.anim.speed = 0.1f;
	RED.type = Red;
	RED.enabled = false;

	BLUE.anim.PushBack({ 0, 0, 31, 22 });
	BLUE.anim.PushBack({ 39, 0, 31, 20 });
	BLUE.anim.PushBack({ 78, 2, 31, 20 });
	BLUE.anim.PushBack({ 118, 0, 31, 20 });
	BLUE.anim.PushBack({ 159, 2, 31, 22 });
	BLUE.anim.PushBack({ 197, 1, 31, 22 });
	BLUE.anim.PushBack({ 242, 1, 31, 21 });
	BLUE.anim.PushBack({ 283, 1, 31, 21 });
	BLUE.anim.PushBack({ 325, 1, 31, 20 });
	BLUE.anim.PushBack({ 365, 0, 31, 20 });
	BLUE.anim.PushBack({ 408, 1, 31, 20 });
	BLUE.anim.PushBack({ 448, 1, 31, 20 });
	BLUE.anim.speed = 0.1f;
	BLUE.type = Blue;
	BLUE.enabled = false;
	
	
}

ModulePowerUPS::~ModulePowerUPS()
{
}

bool ModulePowerUPS::Init()
{
	return true;
}

bool ModulePowerUPS::Start()
{
	LOG("Loading PowerUp particles");
	graphics = App->textures->Load("assets/powerups.png");

	if (!graphics)return false;

	return true;
}

update_status ModulePowerUPS::Update()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		PowerUP* pu = powerUps[i];

		if (pu == nullptr)
			continue;

		pu->Update();

		App->render->Blit(graphics, pu->position.x, pu->position.y, &(pu->anim.GetCurrentFrame()));
	}
	return UPDATE_CONTINUE;
}

bool ModulePowerUPS::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerUps[i] != nullptr)
		{
			delete powerUps[i];
			powerUps[i] = nullptr;
		}
	}

	return true;
}

void ModulePowerUPS::OnCollision(Collider * c1, Collider * c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		// Always destroy powerUps that collide
		if (powerUps[i] != nullptr && powerUps[i]->collider == c1)
		{
			powerUps[i]->Effect();
			delete powerUps[i];
			powerUps[i] = nullptr;
			break;
		}
	}
}

void ModulePowerUPS::AddPowerUp(const PowerUP & powerup, int x, int y, COLLIDER_TYPE collider_type)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerUps[i] == nullptr)
		{
			PowerUP* pu = new PowerUP(powerup);
			pu->position.x = x;
			pu->position.y = y;
			if (collider_type != COLLIDER_NONE)
				pu->collider = App->collision->AddCollider(pu->anim.GetCurrentFrame(), collider_type, this);
			powerUps[i] = pu;
			break;
		}
	}
}


PowerUP::PowerUP()
{
}

PowerUP::PowerUP(const PowerUP& pu) :
	anim(pu.anim), position(pu.position), type(pu.type), enabled(pu.enabled)
{}

PowerUP::~PowerUP()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

void PowerUP::Effect()
{
	switch (type)
	{
	case Red:
		App->player->activePU[Red] = true;
		break;
	case Blue:
		App->player->activePU[Blue] = true;
		break;
	
	}
}

bool PowerUP::Update()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return true;
}
