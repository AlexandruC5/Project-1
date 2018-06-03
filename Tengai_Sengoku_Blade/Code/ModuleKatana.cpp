#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

#include "ModuleKatanaArrow.h"
#include "ModuleEnemies.h"
#include "ModuleInterface.h"
#include "SDL\include\SDL_timer.h"
#include "SDL\include\SDL_render.h"
#include "ModuleKatana.h"
#include "ModuleSceneTemple.h"
#include "CharSelec.h"


ModuleKatana::ModuleKatana()
{
	graphics = NULL;
	current_animation = NULL;

	position.x = 10;
	position.y = 20;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 87, 4, 32, 33 });
	idle.PushBack({ 152, 5, 32, 33 });
	idle.PushBack({ 188, 5, 32, 33 });
	idle.speed = 0.20f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 286, 6, 22, 33 });
	backward.PushBack({ 311, 6, 21, 33 });
	backward.PushBack({ 335, 6, 22, 33 });
	backward.speed = 0.15f;

	//Intermediate
	intermediate.PushBack({ 389,7,30,33 });
	intermediate.PushBack({ 365,6,24,33 });
	intermediate.PushBack({ 260,7,22,33 });
	intermediate.speed = 0.10f;

	//Intermediate return
	intermediate_return.PushBack({ 260,7,22,33 });
	intermediate_return.PushBack({ 365,6,24,33 });
	intermediate_return.PushBack({ 389,7,30,33 });
	intermediate_return.speed = 0.10f;

	//Spin
	spin.PushBack({ 123, 4, 25, 33 });
    spin.PushBack({ 38, 4, 28, 33 });
	spin.PushBack({ 7, 5, 24, 33 });
	spin.PushBack({ 470, 49, 27, 32 });
	
	spin.PushBack({ 123, 4, 25, 33 });
	spin.PushBack({ 38, 4, 28, 33 });
	spin.PushBack({ 7, 5, 24, 33 });
	spin.PushBack({ 470, 49, 27, 32 });
	
	spin.PushBack({ 123, 4, 25, 33 });
	spin.PushBack({ 38, 4, 28, 33 });
	spin.PushBack({ 7, 5, 24, 33 });
	spin.PushBack({ 470, 49, 27, 32 });
	
	spin.PushBack({ 123, 4, 25, 33 });
	spin.PushBack({ 38, 4, 28, 33 });
	spin.PushBack({ 7, 5, 24, 33 });
	
	spin.speed = 0.15f;

	//Spin Circle
	spin_circle.PushBack({ 7,334,24,23 });
	spin_circle.PushBack({ 31,330,30,31 });
	spin_circle.PushBack({ 62,330,32,33 });
	spin_circle.PushBack({ 95,329,32,33 });
	spin_circle.PushBack({ 128,330,32,32 });
	spin_circle.PushBack({ 162,330,32,32 });
	spin_circle.PushBack({ 196,329,32,33 });
	spin_circle.PushBack({ 230,330,33,32 });
    //spin_circle.PushBack({ 214,192,32,32 });
	spin_circle.speed = 0.3f;

	//Death Circle
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 298,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 1,0, 130, 130 });
	death_circle.PushBack({ 153,0, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 143,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 300,153, 130, 130 });
	death_circle.PushBack({});
	death_circle.PushBack({ 2,292, 130, 130 });
	death_circle.speed = 0.8f;

	//Death Player
	death.x = 224;
	death.y = 5;
	death.w = 32;
	death.h = 32;
	


}


ModuleKatana::~ModuleKatana()
{}

// Load assets
bool ModuleKatana::Start()
{
	LOG("Loading player textures");

	graphics = App->textures->Load("assets/sprites/characters/katana/Katana_Spritesheet.png"); 
	player_death = App->textures->Load("assets/sprites/characters/death_player/Death_Player.png");
	if (App->charmenu->P1katana) {
		position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
		position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
	}
	else if (App->charmenu->P2katana) {
		position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
		position.y = (App->render->camera.y) / SCREEN_SIZE + 155;
	}
	coll = App->collision->AddCollider({ (int)position.x, (int)position.y, 32, 32 }, COLLIDER_PLAYER);
	hitbox = App->collision->AddCollider({ (int)position.x, (int)position.y,16,16 }, COLLIDER_HITBOX_KATANA);

	state = SPAWN_PLAYER;
	App->katana_arrow->Enable();

	App->inter->num_life_katana = 3;
	App->inter->num_ult_katana = 2;

	time = true;
	destroyed = false;

	return true;
}

// Unload assets
bool ModuleKatana::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->katana_arrow->Disable();
	App->textures->Unload(player_death);

	if (coll != nullptr)
		 coll->to_delete = true;
	
	if (hitbox != nullptr)
		 hitbox->to_delete = true;

	App->inter->game_over_katana = true;

	return true;
}

update_status ModuleKatana::Update()
{

	//Create bool variables
	bool pressed_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT ;
	bool pressed_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT ;
	bool pressed_S = App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT ;
	bool pressed_D = App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT ;


	Uint8 gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	Uint8 gamepad_DOWN = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) > CONTROLLER_DEAD_ZONE;
	Uint8 gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	Uint8 gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;


	bool shot_space = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN;
	bool shot_button_A = SDL_GameControllerGetButton(App->input->gamepad, SDL_CONTROLLER_BUTTON_A) ;
	 speed = 1.25;

	 //Power Up Limits
	 if (power_up < 0) {
		 power_up = 0;
	 }
	 if (power_up > 2) {
		 power_up = 2;
	 }

	//check state
	CheckState();

	//state actions
	PerformActions();

	//Inputs
	if (input) {

		if (shot_space /*|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT*/ || App->input->controller_A_button == KEY_STATE::KEY_DOWN) {
			LOG("Shooting bullets");



			/*current_bullet_time = SDL_GetTicks() - bullet_on_entry;

			if (current_bullet_time > 100) {

			bullet_on_entry = SDL_GetTicks();*/
			aux1++;
			switch (aux1) {
			case 0:
				App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				LOG("Shoot 1");
				break;
			case 1:
				App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				break;
			case 2:
				App->particles->AddParticle(App->particles->shoot3, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				aux1 = 0;
				break;

			}

		}

		if (pressed_A || App->input->controller_Dpad_LEFT== KEY_STATE::KEY_REPEAT) {
			position.x -= speed;
		}
		if (pressed_W || App->input->controller_Dpad_UP == KEY_STATE::KEY_REPEAT) {
			position.y -= speed;
		}
		if (pressed_D || App->input->controller_Dpad_RIGHT == KEY_STATE::KEY_REPEAT) {
			position.x += speed;
		}
		if (pressed_S || App->input->controller_Dpad_DOWN == KEY_STATE::KEY_REPEAT) {
			position.y += speed;
		}
		if (shot_space /*|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT*/ || App->input->controller_A_button ==BUTTON_DOWN) {
			LOG("Shooting bullets");



			/*current_bullet_time = SDL_GetTicks() - bullet_on_entry;

			if (current_bullet_time > 100) {

			bullet_on_entry = SDL_GetTicks();*/
			aux1++;
			switch (aux1) {
			case 0:
				App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				LOG("Shoot 1");
				break;
			case 1:
				App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				break;
			case 2:
				App->particles->AddParticle(App->particles->shoot3, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
				aux1 = 0;
				break;

			}

		}
		

		

	}

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {

		App->particles->AddParticle(App->particles->shoot1, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);

		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			App->particles->AddParticle(App->particles->shoot2, position.x, position.y - 20, COLLIDER_PLAYER_KATANA_SHOT, PARTICLE_SHOT_KATANA);
			time = true;
		}

	}*/






	//Fade
	SDL_SetTextureAlphaMod(graphics, alpha_player);

	//Set spin position
	if (spin_pos) {
		aux_spin.x = position.x ;
		aux_spin.y = position.y - 32;
		//spin_pos = false;
		
	}
	
		if (death_pos) {
		aux_death.x = position.x - 40;
		aux_death.y = position.y - 70;
		death_pos = false;
		
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	if (!check_death) {
		if (check_spawn) {
			position.x++;
			coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		}
		else {
			coll->SetPos(position.x, position.y - 32);
			hitbox->SetPos(position.x + 8, position.y - 25);
		}
	
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	else {
		App->render->Blit(graphics, position.x, position.y - 32, &death);
		coll->SetPos(App->render->camera.x, App->render->camera.y - 32);
		
		position.x -= 1;
		position.y += 3;
		
	}

	if (coll->CheckCollision(App->scene_temple->coll_left->rect)) {
		position.x = (App->render->camera.x / SCREEN_SIZE);
		
	}
	if (coll->CheckCollision(App->scene_temple->coll_right->rect)) {
		position.x = (SCREEN_WIDTH + App->render->camera.x / SCREEN_SIZE) - 33;
		
	}
	if (coll->CheckCollision(App->scene_temple->coll_up->rect)) {
		position.y = 35;
		
	}
	if (coll->CheckCollision(App->scene_temple->coll_down->rect)) {
		position.y = SCREEN_HEIGHT - 4;
		
	}

	return UPDATE_CONTINUE;
}

void ModuleKatana::CheckState()
{
	//Create Input Bools

	bool pressed_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT;
	bool pressed_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT;
	
	bool press_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_DOWN;
	bool press_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN;
	
	bool release_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP;
    bool release_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP;
	
	bool released_W = App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE;
	bool released_A = App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE;


	bool gamepad_UP = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTY) < -CONTROLLER_DEAD_ZONE;
	bool gamepad_RIGHT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) > CONTROLLER_DEAD_ZONE;
	bool gamepad_LEFT = SDL_GameControllerGetAxis(App->input->gamepad, SDL_CONTROLLER_AXIS_LEFTX) < -CONTROLLER_DEAD_ZONE;

	switch (state)
	{
	case SPAWN_PLAYER:
		if (time) {
			time_on_entry = SDL_GetTicks();
			time = false;
		}
		current_time = SDL_GetTicks() - time_on_entry;
		if (current_time > 1500) {
			state = IDLE;
		}
		power_up = 0;
		
		break;

	case IDLE:
		if (press_W || press_A ||App->input->controller_Dpad_UP || App->input->controller_Dpad_LEFT) {
			state = GO_BACKWARD;
		}

		break;

	case GO_BACKWARD:

		if (release_W || App->input->controller_Dpad_UP==BUTTON_UP) {
			state = BACK_IDLE;
		}
		if (release_A || App->input->controller_Dpad_LEFT==BUTTON_UP) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = BACKWARD;
		}
		break;

	case BACKWARD:

		if (release_W || release_A || App->input->controller_Dpad_UP == BUTTON_UP || App->input->controller_Dpad_LEFT == BUTTON_UP) {
			if (released_W || released_A || App->input->controller_Dpad_UP == BUTTON_UP || App->input->controller_Dpad_LEFT == BUTTON_UP) {

				state = BACK_IDLE;


		/*if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_UP || gamepad_UP) {
			if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE || gamepad_LEFT) {
				state = BACK_IDLE;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_UP || gamepad_LEFT) {
			if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE || gamepad_UP) {
				state = BACK_IDLE;*/
			}
		}
		break;

	case BACK_IDLE:
		if (pressed_W || App->input->controller_Dpad_UP == BUTTON_REPEAT) {
			state = BACK_IDLE;
		}
		if (pressed_A || App->input->controller_Dpad_LEFT == BUTTON_REPEAT) {
			state = BACK_IDLE;
		}
		if (current_animation->Finished()) {
			intermediate.Reset();
			state = IDLE;
		}
		break;

	case SPIN:
		if (spin.Finished()) {
			spin.Reset();
			spin_circle.Reset();
			spin_pos = false;
			state = IDLE;
			
		}
		break;
		
	case DEATH:
		if (position.y > SCREEN_HEIGHT + 130) {
			state = POST_DEATH;
					
		}
		break;
				
	case POST_DEATH:
		if (App->inter->num_life_katana > 0) {
			position.x = (App->render->camera.x) / SCREEN_SIZE - 20;
			position.y = (App->render->camera.y) / SCREEN_SIZE + 100;
			time = true;
		    state = SPAWN_PLAYER;
		}
	break;
	}
}

void ModuleKatana::PerformActions()
{
	switch (state) {
	case SPAWN_PLAYER:
		App->inter->game_over_katana = false;
		check_spawn = true;
		current_animation = &idle;
		blink_time = SDL_GetTicks() - blink_on_entry;
		if (blink_time > 10) {
			blink_on_entry = SDL_GetTicks();
			if (blink) {
				alpha_player = 0;
				blink = false;
			}
			else {
				alpha_player = 255;
				blink = true;
			}
		}
		input = false;
		check_death = false;
		break;

	case IDLE:
		if (App->render->camera.x > 40000) {
			input = false;
		}
		if (App->render->camera.x < 40000) {
			input = true;
		}
		death_pos = true;
		check_spawn = false;
		alpha_player = 255;
		spin.Reset();
		current_animation = &idle;
		break;

	case GO_BACKWARD:

		if (intermediate.Finished())
		{
			intermediate.Reset();
		}
		current_animation = &intermediate;
		break;

	case BACKWARD:

		if (backward.Finished())
			backward.Reset();
		current_animation = &backward;
		break;

	case BACK_IDLE:

		if (intermediate_return.Finished())
			intermediate_return.Reset();
		current_animation = &intermediate_return;
		break;

	case SPIN:
		SDL_Rect spin_rect = spin_circle.GetCurrentFrame();
		App->render->Blit(graphics, aux_spin.x, aux_spin.y, &spin_rect);
		current_animation = &spin;
		break;
		
	case DEATH:
	    SDL_Rect death_rect = death_circle.GetCurrentFrame();
		power_up = 0;
		check_death = true;
		input = false;
		App->render->Blit(player_death, aux_death.x, aux_death.y, &death_rect, 1.0f);
		/*if (explosion) {
			App->particles->AddParticle(App->particles->explosion, position.x - 8, position.y - 8);
			explosion = false;*/
		//}
		alpha_player = 255;
		break;
				
     case POST_DEATH:
		 if (App->inter->num_life_katana == 0) {

			 if (App->inter->score_katana > 1000) {
				 App->inter->score_katana -= 1000;

			 }
			 App->katana->Disable();
		 }

		 else {
			 check_death = false;
			 
		 }
		break;
	}
	
}
