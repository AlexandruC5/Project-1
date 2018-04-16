#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleSceneWater.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 100;

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



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("assets/sprites/miko.png");
	player_collider = App->collision->AddCollider({position.x, position.y, 32, 28}, COLLIDER_PLAYER, this);
	bool isShooting = false;
	return true;
}


bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);
	graphics = nullptr;
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
		}
	
		
		position.x -= speed;
		if ((position.x * SCREEN_SIZE) < -App->render->camera.x) {
			position.x += speed;
		}
		
		
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.x += speed;
		if (((position.x + 32) * SCREEN_SIZE) > (-App->render->camera.x + SCREEN_WIDTH + 320)) {
			position.x -= speed;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.y += speed;
		if (((position.y + 28) * SCREEN_SIZE) > (-App->render->camera.y + SCREEN_HEIGHT + 224)) {
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
		if ((position.y * SCREEN_SIZE) < -App->render->camera.y)
		{
			position.y += speed;
		}
			
	}

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN) {
		switch (aux) {
		case 0:
			App->particles->AddParticle(App->particles->card1, position.x, position.y, COLLIDER_PLAYER_SHOT);

			//firerate = 10;
			//isShooting = true;
			break;
		case 1:
			App->particles->AddParticle(App->particles->card2, position.x, position.y, COLLIDER_PLAYER_SHOT);

		
			break;
		case 2:
			App->particles->AddParticle(App->particles->card3, position.x, position.y, COLLIDER_PLAYER_SHOT);
			//App->particles->AddParticle(App->particles->card1, position.x, position.y, COLLIDER_PLAYER_SHOT);

			break;
		case 3:
			App->particles->AddParticle(App->particles->card4, position.x, position.y, COLLIDER_PLAYER_SHOT);
			break;
		case 4:
			
			App->particles->AddParticle(App->particles->card5, position.x, position.y, COLLIDER_PLAYER_SHOT);

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
	
	player_collider->SetPos(position.x, position.y);
	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}