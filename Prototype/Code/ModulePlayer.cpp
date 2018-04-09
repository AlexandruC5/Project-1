#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"

#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 0;
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

	int speed = 1;

	if (current_animation != &mid && current_animation != &mid2) {
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
			current_animation = &forward;
	}

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)

		if (current_animation != &mid && !mid.isDone()) {
			//mid.Reset();
			current_animation = &mid;
		}

		else if (current_animation->isDone()) {
			current_animation = &backward;
		}
	{
		
		position.x -= speed;
	
		
		
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		
		current_animation = &forward;
		position.y += speed;
		
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
	
	
	}
	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN) {//Differents sprites for the same attack NOT ANIMATION
		int cont = 0;
		if (cont == 0) {
			App->particles->AddParticle(App->particles->card1, position.x + 30, position.y);
			cont++;
		}
		else if (cont == 1) {
			App->particles->AddParticle(App->particles->card2, position.x + 30, position.y);
			cont++;
		}
		else if (cont == 2) {
			App->particles->AddParticle(App->particles->card3, position.x + 30, position.y);
			cont++;
		}
		else if (cont == 3) {
			App->particles->AddParticle(App->particles->card4, position.x + 30, position.y);

			cont++;
		}
		else if(cont ==4){
			App->particles->AddParticle(App->particles->card5, position.x + 30, position.y);
			cont = 0;
		}
	}
	
	
	
	
	// Draw everything --------------------------------------

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}