#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "GREEN.h"
#include "Fish.h"
#include "Green2.h"
#include "red.h"
#include "DEMONPEGTOP.h"
#include "DEMONWHEEL.h"
#include "SHARPENER_KNIFE.h"
#include "BALL.h"
#include "BALL2.h"
#include "CHARIOT.h"
#include "PAGODA.h"
#include "Power_Up.h"
#include "Ulti_Parchment.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "OrientalGenius.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleInterface.h"
#include "time.h"
#include "stdlib.h"

#include "SDL\include\SDL_timer.h"


#define SPAWN_MARGIN 50
#define SCREEN_SIZE2 3

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	
	//sprites = App->textures->Load("assets/enemies2.png");
	sprites = App -> textures->Load("assets/enemiestemple.png");


	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::SharpenerKnife && queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}

		if (queue[i].type == ENEMY_TYPES::SharpenerKnife && queue[i].type != ENEMY_TYPES::NO_TYPE) {

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) - 150 )
			{
				SpawnEnemy(queue[i]);
				
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}

		/*if (queue[i].type == ENEMY_TYPES::DemonWheel && queue[i].type != ENEMY_TYPES::NO_TYPE) {

			if (queue[i].path_type == 2) {

				if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) - 250)
				{
					SpawnEnemy(queue[i]);

					queue[i].type = ENEMY_TYPES::NO_TYPE;
					LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
				}
			}*/
		//}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)
		{
			enemies[i]->Move();
			
		}
	}
	
	for (uint i = 0; i < MAX_ENEMIES; ++i) {
		if (enemies[i] != nullptr)  {
			enemies[i]->Draw(sprites);
			
			
		}
	}


	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, int path_type)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].path_type = path_type;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
			case ENEMY_TYPES::FISH:
			enemies[i] = new Fish(info.x, info.y, info.path_type);
			break;

			case ENEMY_TYPES::Green:
				enemies[i] = new GREEN(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::Green2:
				enemies[i] = new GREEN2(info.x, info.y, info.path_type);
				break;
			case ENEMY_TYPES::RED:
				enemies[i] = new red(info.x, info.y, info.path_type);

				break;

			case ENEMY_TYPES::ORIENTAL_GENIUS:
				enemies[i] = new OrientalGenius(info.x, info.y, info.path_type);

				break;

			case ENEMY_TYPES::DemonPegTop:
				enemies[i] = new DEMONPEGTOP(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::DemonWheel:
				enemies[i] = new DEMONWHEEL(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::SharpenerKnife:
				enemies[i] = new SHARPENER_KNIFE(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::Power_up:
				enemies[i] = new Power_Up(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::Ulti_parchment:
				enemies[i] = new Ulti_Parchment(info.x, info.y, info.path_type);

				break;

			case ENEMY_TYPES::Ball:
				enemies[i] = new BALL(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::Ball2:
				enemies[i] = new BALL2(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::Chariot:
				enemies[i] = new CHARIOT(info.x, info.y, info.path_type);

				break;
			case ENEMY_TYPES::Pagoda:
				enemies[i] = new PAGODA(info.x, info.y, info.path_type);

				break;
		}

	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{

			//Player collides w enemies
			if ((c2->type == COLLIDER_TYPE::COLLIDER_PLAYER /*|| c2->type == COLLIDER_TYPE::COLLIDER_HITBOX_AYIN*/) && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHARPENER_KNIFE) {
				LOG("collider on");
				//Katana colliders with enemy
				if (c2 == App->katana->coll) {
					if (timer) {
						time_on_entry = SDL_GetTicks();
						timer = false;
					}
					current_time = SDL_GetTicks() - time_on_entry;
					if (current_time > 600) {
						if (App->katana->power_up > 0) {
							
							App->particles->power_down.speed.x = App->scene_temple->speed;
							App->particles->power_down.speed.y = -1;
							App->particles->AddParticle(App->particles->power_down, App->katana->position.x, App->katana->position.y);
							
						}
						App->katana->power_up--;
						timer = true;
					}
					//App->audio->PlaySoundEffects(App->player->k_power_down);
					App->katana->spin_pos = true;
					App->katana->state = SPIN;
				}
			

			//Ayin colliders with enemy
			if (c2 == App->ayin->coll) {
				if (timer_2) {
					time_on_entry_2 = SDL_GetTicks();
					timer_2 = false;
				}
				current_time_2 = SDL_GetTicks() - time_on_entry_2;
				if (current_time_2 > 600) {
					if (App->ayin->power_up > 0) {
						App->particles->power_down.speed.x = App->scene_temple->speed;
						App->particles->power_down.speed.y = -1;
						App->particles->AddParticle(App->particles->power_down, App->ayin->position.x, App->ayin->position.y);
					}
					App->ayin->power_up--;
					timer_2 = true;
				}
				//App->audio->PlaySoundEffects(s_power_down);
				App->ayin->spin_pos = true;
				App->ayin->state = SPIN_2;
			}
		}
	


			//Kill enemy demon pegtop

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				pegtop_life++;


				if (pegtop_life == 1) {
					//App->particles->AddParticle(App->particles->spark, enemies[i]->position.x, enemies[i]->position.y);
					//App->particles->spark.speed.x = speed;
				}
				if (pegtop_life == 10) {
					//App->audio->PlaySoundEffects(fx_death);
					//App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT)
					{
						App->inter->score_katana += 200;
					}
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)
					{
						App->inter->score_ayin += 200;
					}
					
					delete enemies[i];
					enemies[i] = nullptr;
					pegtop_life = 0;
				}
			}


			if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_POWER_UP) {

				if (c2 == App->katana->coll) {
					if (App->katana->power_up < 4) {
						App->particles->power_up.speed.x = App->scene_temple->speed;
						App->particles->power_up.speed.y = -1;
						App->particles->AddParticle(App->particles->power_up, App->katana->position.x, App->katana->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_KATANA);
						App->katana->power_up++;
					}
					/*else {
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_koyori += 2000;
					}*/
				}
				if (c2 == App->ayin->coll) {
					if (App->ayin->power_up < 4) {
						App->particles->power_up.speed.x = App->scene_temple->speed;
						App->particles->power_up.speed.y = -1;
						App->particles->AddParticle(App->particles->power_up, App->ayin->position.x, App->ayin->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_AYIN);
						App->ayin->power_up++;
					}
					/*else {
						App->particles->coin_2000.speed.x = speed;
						App->particles->coin_2000.speed.y = -2;
						App->particles->AddParticle(App->particles->coin_2000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);
						App->ui->score_sho += 2000;
					}*/
				}

				delete enemies[i];
				enemies[i] = nullptr;
			}

			if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_ULTI_PARCHMENT) {

				if (c2 == App->katana->coll) {
					if (App->inter->num_ult_katana < 6) {

						App->inter->num_ult_katana++;
					}
				}

				if (c2 == App->ayin->coll) {
					if (App->inter->num_ult_ayin < 6) {
						App->inter->num_ult_ayin++;
					}
				}

				delete enemies[i];
				enemies[i] = nullptr;
			}



			//	//App->audio->PlaySoundEffects(fx_death);
			//	//App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

			//	if (num_pegtop >= 4) {
			//		//AddEnemy(ENEMY_TYPES::COIN, enemies[i]->position.x, enemies[i]->position.y);
			//		num_pegtop = 0;
			//	}
			//	delete enemies[i];
			//	enemies[i] = nullptr;

			//	if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT)
			//	{
			//		//App->ui->score_koyori += 200;
			//	}
			//	if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)
			//	{
			//		//App->ui->score_sho += 200;
			//	}


			//}




			//if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY && c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_SHOT) {


			//	App->particles->AddParticle(App->particles->waterExplosion, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_NONE);
			//	enemies[i]->OnCollision(c2);
			//	App->player->score += 200;
			//	App->player2->score += 200;

			//	delete enemies[i];
			//	enemies[i] = nullptr;
			//	break;
			//}
			//

			//if (c2->type == COLLIDER_TYPE::COLLIDER_SHOOT && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY) {
			//	//App->particles->AddParticle(App->particles->enemyattack, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_ENEMY_SHOT);
			//	if (shoot) {
			//		App->particles->AddParticle(App->particles->enemyattack, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_ENEMY_SHOT);
			//		shoot = false;
			//	}
			//}
			
		}
		

	}
	
}