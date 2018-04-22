#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePLayer2.h"
#include "ModuleFonts.h"
#include <string>
#include "ModuleSceneWater.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUPS.h"
#include "SDL_mixer/include/SDL_mixer.h"

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 60;

	// idle-forward-downwards animation 
	idle.PushBack({ 38 ,9 ,29 ,27 }); //not input
	idle.PushBack({ 75 ,10 ,29 ,26 });
	idle.PushBack({ 112, 10, 29, 27 });


	forward.speed = 0.1f;

	// move upwards-backwards animation
	mid.PushBack({ 214, 10, 24, 26 }); //back & up
	mid.PushBack({ 183, 9, 22, 27 });
	mid.PushBack({ 266, 55, 24, 27 });
	mid.loop = false;
	mid.speed = 0.1f;

	mid2.PushBack({ 266, 55, 24, 27 });
	mid2.PushBack({ 183, 9, 22, 27 });
	mid2.PushBack({ 214, 10, 24, 26 });
	mid2.loop = false;
	mid2.speed = 0.1f;

	stayback.PushBack({ 149,9,24,27 }); //keep goind up & back
	stayback.PushBack({ 281,10,24,27 });
	stayback.PushBack({ 266, 55, 24, 27 });
	stayback.speed = 0.1f;
	// move upwards-backwards animation
	/*backward.PushBack({ 193, 53, 26, 29 });
	backward.PushBack({ 233, 54, 27, 28 });
	backward.PushBack({ 272, 54, 27, 28 });
	//backward.loop = false;
	backward.speed = 0.1f;
	*/


}

ModulePlayer2::~ModulePlayer2() {}

bool ModulePlayer2::Start() {
	LOG("Loading player2");
	graphics = App->textures->Load("assets/sprites/sho.png");
	font_score = App->fonts->Load("assets/sprites/UI/score_fonts.png", "0123456789", 1);
	font_players = App->fonts->Load("assets/sprites/UI/players.png", "12", 1);

	position.x = App->player->position.x;
	position.y = 100;
	destroyed = false;
	player_collider = App->collision->AddCollider({ position.x, position.y, 32, 32 }, COLLIDER_PLAYER, this);
	LOG("Loading Audio p2");
	basic = App->audio->LoadFx("assets/audio/effects/sho/Shobasic.wav");
	bool isShooting = false;
	return true;
}

bool ModulePlayer2::CleanUp() {
	LOG("Unloading PLayer2");
	App->textures->Unload(graphics);
	if (player_collider != nullptr) {
		player_collider->to_delete = true;
	}
	graphics = nullptr;
	App->audio->UnloadSFX(basic);
	basic = nullptr;
	return true;
}

update_status ModulePlayer2::Update() {
	int speed = 2;
	if (current_animation != &mid && current_animation != &mid2) {
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE)
			current_animation = &idle;
	}


	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT) {
		if (current_animation != &mid && !mid.isDone()) {
			current_animation = &mid;
		}
		else if (current_animation->isDone()) {
			current_animation = &stayback;
		}
		position.x -= speed;

		if ((position.x * SCREEN_SIZE) < App->render->camera.x) {
			position.x += speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT) {
		current_animation = &idle;
		position.x += speed;
		if (((position.x + 32)* SCREEN_SIZE) > (App->render->camera.x + SCREEN_WIDTH + 320)) {
			position.x -= speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) {
		current_animation = &idle;
		position.y += speed;
		if (((position.y + 28)* SCREEN_SIZE) > (App->render->camera.y + SCREEN_HEIGHT + 224)) {
			position.y -= speed;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{


		if (current_animation != &mid && !mid.isDone()) {
			//mid.Reset();
			current_animation = &mid;
		}

		else if (current_animation->isDone()) {
			current_animation = &stayback;
		}


		position.y -= speed;
		if ((position.y * SCREEN_SIZE) < App->render->camera.y)
		{
			position.y += speed;
		}

	}//here
	if (App->input->keyboard[SDL_SCANCODE_RCTRL] == KEY_STATE::KEY_DOWN) {
		Mix_PlayChannel(-1, basic, 0);
		switch (aux) {
		case 0:
			App->particles->AddParticle(App->particles->sword1, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->sword1, position.x, position.y, COLLIDER_PLAYER_SHOT);
			//firerate = 10;
			//isShooting = true;
			aux = 1;
			break;

		case 1:
			App->particles->AddParticle(App->particles->sword2, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->sword2, position.x, position.y, COLLIDER_PLAYER_SHOT);
			aux = 0;

			break;
		}

	}
	else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_UP) {
		mid.Reset();
		current_animation = &mid2;
	}
	else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE) {
		if (current_animation->isDone()) {
			mid2.Reset();
			current_animation = &idle;
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_UP) {
		mid.Reset();
		current_animation = &mid2;
	}

	else if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE) {
		if (current_animation->isDone()) {
			mid2.Reset();
			current_animation = &idle;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {

		App->collision->GodMode();

	}

	
	player_collider->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	if (destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	//UI
	App->fonts->BlitText(200 , 5, font_players, "2");
	sprintf_s(score_text, 10, "%1d", score);
	App->fonts->BlitText(240, 6.5f, font_score, score_text);

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider*c2)
{
	if (c1 == player_collider && destroyed == false) //&& App->fade->IsFading() == false)
	{
		App->player2->Disable();
		destroyed = true;
	}

}