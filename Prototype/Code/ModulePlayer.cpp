#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleSceneWater.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePowerUPS.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <string>

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 60;

	// idle-forward-downwards animation 
	forward.PushBack({ 68 ,53 ,32 ,28 });
	forward.PushBack({ 108 ,54 ,32 ,28 });
	forward.PushBack({ 148, 54, 32, 27 });


	forward.speed = 0.1f;

	// move upwards-backwards animation
	mid.PushBack({ 187, 95, 26, 29 });
	mid.PushBack({ 230, 95, 24, 28 });
	mid.PushBack({ 270, 95, 26, 28 });
	mid.loop = false;
	mid.speed = 0.1f;

	mid2.PushBack({ 270, 95, 26, 28 });	
	mid2.PushBack({ 230, 95, 24, 28 });
	mid2.PushBack({ 187, 95, 26, 29 });
	mid2.loop = false;
	mid2.speed = 0.1f;

	// move upwards-backwards animation
	backward.PushBack({ 193, 53, 26, 29 });
	backward.PushBack({ 233, 54, 27, 28 });
	backward.PushBack({ 272, 54, 27, 28 });
	//backward.loop = false;
	backward.speed = 0.1f;


	death.PushBack( { 308,54,30,25 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/sprites/miko.png");
	font_score = App->fonts->Load("assets/sprites/UI/score_fonts.png", "0123456789", 1);
	font_players = App->fonts->Load("assets/sprites/UI/players.png", "12", 1);

	position.x = 10;
	position.y = 60;
	destroyed = false;

	player_collider = App->collision->AddCollider({position.x, position.y, 32, 28}, COLLIDER_PLAYER, this);
	LOG("Loading Audio");
	basic = App->audio->LoadFx("assets/audio/effects/miko/mikoshot.wav");
	bool isShooting = false;
	return true;
}


bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);

	if (player_collider != nullptr) {
		player_collider->to_delete = true;
	}

	graphics = nullptr;
	App->audio->UnloadSFX(basic);
	basic = nullptr;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//Animation* current_animation = &forward;

	int speed = 2;

	if (current_animation != &mid && current_animation != &mid2) {
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
			current_animation = &forward;
	}

	/*if (firerate == 0 && isShooting) {

		App->particles->AddParticle(App->particles->card1, position.x, position.y);
		firerate = 15;
		isShooting = false;
	}
	else firerate--;
	*/
	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{

		if (current_animation != &mid && !mid.isDone()) {
			//mid.Reset();
			current_animation = &mid;
		}

		else if (current_animation->isDone()) {
			current_animation = &backward;
			//position.x -= speed;

		}

		
		position.x -= speed;

		if ((position.x * SCREEN_SIZE) < App->render->camera.x) {
			position.x += speed;
		}
		
		
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.x += speed;

		
		if (((position.x + 32)* SCREEN_SIZE) > (App->render->camera.x + SCREEN_WIDTH + 320)) {
			position.x -= speed;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.y += speed;
		if (((position.y + 28) * SCREEN_SIZE) > (App->render->camera.y + SCREEN_HEIGHT + 224)) {
			position.y -= speed;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		
		
		if (current_animation != &mid && !mid.isDone()) {
			//mid.Reset();
			current_animation = &mid;
		}

		else if (current_animation->isDone()) {
			current_animation = &backward;
		}
	

		position.y -= speed;
		if ((position.y * SCREEN_SIZE) < App->render->camera.y)
		{
			position.y += speed;
		}
			
	}

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		Mix_PlayChannel(-1, basic, 0);


		switch (aux) {
		case 0:

			if (activePU[Red] == false)App->particles->AddParticle(App->particles->card1, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->BigC1, position.x, position.y, COLLIDER_PLAYER_SHOT);
			//firerate = 10;
			//isShooting = true;
			break;

		case 1:

			if (activePU[Red] == false)App->particles->AddParticle(App->particles->card2, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->BigC2, position.x, position.y, COLLIDER_PLAYER_SHOT);
			break;

		case 2:

			if (activePU[Red] == false)App->particles->AddParticle(App->particles->card3, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->BigC3, position.x, position.y, COLLIDER_PLAYER_SHOT);
			break;

		case 3:

			if (activePU[Red] == false)App->particles->AddParticle(App->particles->card4, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->BigC4, position.x, position.y, COLLIDER_PLAYER_SHOT);
		
			break;
		case 4:

			if (activePU[Red] == false)App->particles->AddParticle(App->particles->card5, position.x, position.y, COLLIDER_PLAYER_SHOT);
			if (activePU[Red] == true)App->particles->AddParticle(App->particles->BigC5, position.x, position.y, COLLIDER_PLAYER_SHOT);
			aux = 0;
			break;
		

		}
		aux++;
	}
	

	
	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP) {
		mid.Reset();
		current_animation = &mid2;
	}
	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) {
		if (current_animation->isDone()) {
			mid2.Reset();
			current_animation = &forward;
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) {
		mid.Reset();
		current_animation = &mid2;
	}

	else if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) {
		if (current_animation->isDone()) {
			mid2.Reset();
			current_animation = &forward;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {

		App->collision->GodMode();

		}
	


	
	player_collider->SetPos(position.x, position.y);
	// Draw everything --------------------------------------
	if (destroyed == true) current_animation = &death;

if(destroyed == false)
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
<<<<<<< HEAD
=======

App->fonts->BlitText(score_x - 25, 5, font_players, "1");
sprintf_s(score_text, 10, "%1d",score);
App->fonts->BlitText(74, 6.5f, font_score, score_text);
>>>>>>> 230896446f25389403892c24cc30f805933e06c2
	
	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == player_collider && destroyed == false) //&& App->fade->IsFading() == false)
	{
		App->player->Disable();
		destroyed = true;
	}
	
}