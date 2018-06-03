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
#include "DEMON.h"
#include "Power_Up.h"
#include "Ulti_Parchment.h"
#include "Coin.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "OrientalGenius.h"
#include "ModuleSceneTemple.h"
#include "ModuleKatana.h"
#include "ModuleAyin.h"
#include "ModuleInterface.h"
#include "time.h"
#include "stdlib.h"
#include "ModuleAudio.h"
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
	ayin_pdown = App->audio->LoadFx("assets/audio/voices/Loose power up/ayin_lvl_down.wav");
	katana_pdown = App->audio->LoadFx("assets/audio/voices/Loose power up/katana_lvl_down.wav");
	pegtop_die = App->audio->LoadFx("assets/audio/effects/Explotions/PegtopDie.wav");
	pagoda_die = App->audio->LoadFx("assets/audio/effects/Explotions/PagodaDie.wav");
	ball_die = App->audio->LoadFx("assets/audio/effects/Explotions/BallDie.wav");
	govni_demonwheel = App->audio->LoadFx("assets/audio/effects/Explotions/GOvni&DemonWheel.wav"); 
	pick_coin = App->audio->LoadFx("assets/audio/effects/ItemCollects/pickcoin.wav");//cambiar path
	pick_PowerUp = App->audio->LoadFx("assets/audio/effects/ItemCollects/getbluePU.wav");//cambiarpath
	katanavoice = App->audio->LoadFx("assets/audio/voices/Pick ower up/katanavoice.wav");
	ayinvoice = App->audio->LoadFx("assets/audio/voices/Pick ower up/ayinvoice.wav");
	yellingK = 0;
	yellingA = 0;
	waitkatana = false;
	waitayin = false;
	checkhitK = false;
	checkhitA = false;
	basicImpact = App->audio->LoadFx("assets/audio/effects/Impacts/BasicShotImpact.wav");
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

			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) - 150)
			{
				SpawnEnemy(queue[i]);

				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}

			if (queue[i].type == ENEMY_TYPES::Demon && queue[i].type != ENEMY_TYPES::NO_TYPE) {

				if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) - 210 && queue[i].y * SCREEN_SIZE > App->render->camera.y + (App->render->camera.h * SCREEN_SIZE))
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
	App->audio->UnloadSFX(ayin_pdown);
	ayin_pdown = nullptr;
	App->audio->UnloadSFX(katana_pdown);
	katana_pdown = nullptr;
	App->audio->UnloadSFX(pegtop_die);
	pegtop_die = nullptr;

	App->audio->UnloadSFX(pagoda_die);
	pagoda_die = nullptr;

	App->audio->UnloadSFX(ball_die);
	ball_die = nullptr;

	App->audio->UnloadSFX(govni_demonwheel);
	govni_demonwheel = nullptr;
	App->audio->UnloadSFX(pick_coin);
	pick_coin = nullptr;

	App->audio->UnloadSFX(pick_PowerUp);
	pick_PowerUp = nullptr;

	App->audio->UnloadSFX(katanavoice);
	katanavoice = nullptr;

	App->audio->UnloadSFX(ayinvoice);
	ayinvoice = nullptr;

	App->audio->UnloadSFX(basicImpact);
	basicImpact = nullptr;
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
			case ENEMY_TYPES::Coin:
				enemies[i] = new COIN(info.x, info.y, info.path_type);

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
			case ENEMY_TYPES::Demon:
				enemies[i] = new DEMON(info.x, info.y, info.path_type);

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
			if ((c2->type == COLLIDER_TYPE::COLLIDER_PLAYER) && c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHARPENER_KNIFE || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PAGODA || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_DEMONWHEEL || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_RED || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_BALL || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_CHARIOT) {
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

							App->particles->power_down.speed.x = int(App->scene_temple->speed);
							App->particles->power_down.speed.y = -1;
							App->particles->AddParticle(App->particles->power_down, App->katana->position.x, App->katana->position.y);

						}
						App->katana->power_up--;
						timer = true;
					}

					Mix_PlayChannel(-1, katana_pdown, 0);
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
							App->particles->power_down.speed.x = int(App->scene_temple->speed);
							App->particles->power_down.speed.y = -1;
							App->particles->AddParticle(App->particles->power_down, App->ayin->position.x, App->ayin->position.y);
						}
						App->ayin->power_up--;
						timer_2 = true;
					}
					Mix_PlayChannel(-1, ayin_pdown, 0);
					App->ayin->spin_pos = true;
					App->ayin->state = SPIN_2;
				}
			}
<<<<<<< HEAD
		}
	
			// shot sound impact
			if (checkhitK == true || checkhitA == true) Mix_PlayChannel(-1, basicImpact, 0), checkhitA = false, checkhitK = false;
=======


>>>>>>> d62133771d2d8cd062be0ecd58114a788bcf4896

			//Players kill pegtop

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PEGTOP && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				pegtop_life++;
<<<<<<< HEAD
				checkhitK = true;
				checkhitA = true;
=======


>>>>>>> d62133771d2d8cd062be0ecd58114a788bcf4896
				if (pegtop_life == 1) {
					App->particles->AddParticle(App->particles->bleeding, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->bleeding.speed.x = App->scene_temple->speed;
				}
				if (pegtop_life == 10) {
					Mix_PlayChannel(-1, pegtop_die, 0);
					AddEnemy(ENEMY_TYPES::Coin, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

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

			//Players kill pagoda

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_PAGODA && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				pagoda_life++;

				checkhitK = true;
				checkhitA = true;
				if (pagoda_life == 1 || pagoda_life == 15) {
					App->particles->AddParticle(App->particles->bleeding, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->bleeding.speed.x = App->scene_temple->speed;
				}
				if (pagoda_life == 25) {
					Mix_PlayChannel(-1, pagoda_die, 0);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

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
					pagoda_life = 0;
				}
			}

			//Players kill Sharpener

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_SHARPENER_KNIFE && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				sharpener_life++;
				checkhitK = true;
				checkhitA = true;

				if (sharpener_life == 1 || sharpener_life == 10 || sharpener_life == 20) {
					App->particles->AddParticle(App->particles->bleeding, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->bleeding.speed.x = App->scene_temple->speed;
				}
				if (sharpener_life == 35) {
					Mix_PlayChannel(-1, pagoda_die, 0);

					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

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
					sharpener_life = 0;
				}
			}


			//Players kill Ball

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_BALL && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				ball_life++;
				checkhitK = true;
				checkhitA = true;

				if (ball_life == 1 || ball_life == 10 || ball_life == 20 || ball_life == 30 || ball_life == 40 || ball_life == 50 || ball_life == 60 || ball_life == 70 || ball_life == 80) {
					App->particles->AddParticle(App->particles->bleeding, enemies[i]->position.x + 10, enemies[i]->position.y + 10);
					App->particles->bleeding.speed.x = App->scene_temple->speed;
				}

				if (ball_life == 100) {
					//App->audio->PlaySoundEffects(fx_death);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x + 20, enemies[i]->position.y + 20);
					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x + 20, enemies[i]->position.y - 20);
					App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;
					Mix_PlayChannel(-1, ball_die, 0);
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
					//ball_life = 0;
				}
			}

			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_CHARIOT && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				LOG("FIRE");
				chariot_life++;


<<<<<<< HEAD
				checkhitK = true;
				checkhitA = true;
				Mix_PlayChannel(-1, govni_demonwheel, 0);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
=======
				if (chariot_life == 1 || chariot_life == 10 || chariot_life == 20 || chariot_life == 30 || chariot_life == 40 || chariot_life == 50 || chariot_life == 60 || chariot_life == 80 || chariot_life == 120 || chariot_life == 140 || chariot_life == 160 || chariot_life == 180) {
					App->particles->AddParticle(App->particles->bleeding, enemies[i]->position.x + 20, enemies[i]->position.y + 40);
					App->particles->bleeding.speed.x = App->scene_temple->speed;
				}
>>>>>>> d62133771d2d8cd062be0ecd58114a788bcf4896

				if (chariot_life == 100) {
					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x + 30, enemies[i]->position.y - 30);
					App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;

					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x - 10, enemies[i]->position.y + 40);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x + 30, enemies[i]->position.y - 30);
					App->particles->explosion.speed.x = App->scene_temple->speed;
				}
				if (chariot_life == 200) {
					//App->audio->PlaySoundEffects(fx_death);

<<<<<<< HEAD
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;
=======
<<<<<<< HEAD
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x, enemies[i]->position.y);
					App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;
=======
<<<<<<< HEAD
			if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_RED && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {
				checkhitK = true;
				checkhitA = true;
				Mix_PlayChannel(-1, govni_demonwheel, 0);
				App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
=======
					
						

						App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
>>>>>>> d62133771d2d8cd062be0ecd58114a788bcf4896
>>>>>>> e05bc9d8c4a93450670eba418b37f69f4d07d973
>>>>>>> 78bd20c6ba60b306b2239e198e52e30a3d87d73d

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x + 10, enemies[i]->position.y + 30);
					//App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x - 10, enemies[i]->position.y + 5);

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x + 40, enemies[i]->position.y);

					App->particles->AddParticle(App->particles->chariot_big_explosion, enemies[i]->position.x, enemies[i]->position.y + 40);
					//App->particles->chariot_big_explosion.speed.x = App->scene_temple->speed;

					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);
					//App->particles->explosion.speed.x = App->scene_temple->speed;

					App->scene_temple->StopCamera();
					AddEnemy(ENEMY_TYPES::Power_up, enemies[i]->position.x, enemies[i]->position.y);

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
					chariot_life = 0;

				}
			}

				//Players kill green ovni & demonwheel

				if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY || c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_DEMONWHEEL && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {


					Mix_PlayChannel(-1, govni_demonwheel, 0);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);


					delete enemies[i];
					enemies[i] = nullptr;

					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT)
					{
						App->inter->score_katana += 200;
					}
					if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)
					{
						App->inter->score_ayin += 200;
					}

				}

				//Players kill red ovni & drop power up

				if (c1->type == COLLIDER_TYPE::COLLIDER_ENEMY_RED && (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_KATANA_SHOT || c2->type == COLLIDER_TYPE::COLLIDER_PLAYER_AYIN_SHOT)) {

					Mix_PlayChannel(-1, govni_demonwheel, 0);
					App->particles->AddParticle(App->particles->explosion, enemies[i]->position.x, enemies[i]->position.y);

					AddEnemy(ENEMY_TYPES::Power_up, enemies[i]->position.x, enemies[i]->position.y);

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
				}


				//Coin


				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_COIN) {
					Mix_PlayChannel(-1, pick_coin, 0);
					srand(time(NULL));
					typeofcoin = rand() % 6;

					switch (typeofcoin) {
					case 0:
						coin_type = App->particles->coin_100;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 100;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);

							App->inter->score_ayin += 100;
							coin_position = App->ayin->position;
						}

						break;

					case 1:
						coin_type = App->particles->coin_200;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 200;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_ayin += 200;
							coin_position = App->ayin->position;
						}

						break;

					case 2:
						coin_type = App->particles->coin_500;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 500;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_ayin += 500;
							coin_position = App->ayin->position;
						}

						break;

					case 3:
						coin_type = App->particles->coin_1000;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 1000;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_ayin += 1000;
							coin_position = App->ayin->position;
						}

						break;

					case 4:
						coin_type = App->particles->coin_2000;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 2000;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_ayin += 2000;
							coin_position = App->ayin->position;
						}

						break;

					case 5:
						coin_type = App->particles->coin_4000;

						if (c2 == App->katana->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_katana += 4000;
							coin_position = App->katana->position;
						}
						if (c2 == App->ayin->coll) {
							Mix_PlayChannel(-1, pick_coin, 0);
							App->inter->score_ayin += 4000;
							coin_position = App->ayin->position;
						}

						break;

					}

					//coin_type.speed.x = int(App->scene_temple->speed);
					coin_type.speed.y = -1.5;
					App->particles->AddParticle(coin_type, coin_position.x, coin_position.y, COLLIDER_NONE, PARTICLE_COIN);

					delete enemies[i];
					enemies[i] = nullptr;

				}



				//Power up

				if (c2->type == COLLIDER_TYPE::COLLIDER_PLAYER  && c1->type == COLLIDER_TYPE::COLLIDER_POWER_UP) {

					if (c2 == App->katana->coll) {
						Mix_PlayChannel(-1, pick_PowerUp, 0);
						Mix_PlayChannel(-1, katanavoice, 0);
						if (App->katana->power_up < 4) {
							//App->particles->power_up.speed.x = App->scene_temple->speed;
							App->particles->power_up.speed.y = -1;
							App->particles->AddParticle(App->particles->power_up, App->katana->position.x, App->katana->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_KATANA);
							App->katana->power_up++;
						}
						else {
							//App->particles->coin_2000.speed.x = int(App->scene_temple->speed);
							App->particles->coin_2000.speed.y = -1.5;
							App->particles->AddParticle(App->particles->coin_2000, App->player->position.x, App->player->position.y, COLLIDER_NONE, PARTICLE_COIN);
							App->inter->score_katana += 2000;
						}
					}
					if (c2 == App->ayin->coll) {
						Mix_PlayChannel(-1, pick_PowerUp, 0);
						Mix_PlayChannel(-1, ayinvoice, 0);
						if (App->ayin->power_up < 4) {
							//App->particles->power_up.speed.x = int(App->scene_temple->speed);;
							App->particles->power_up.speed.y = -1;
							App->particles->AddParticle(App->particles->power_up, App->ayin->position.x, App->ayin->position.y, COLLIDER_NONE, PARTICLE_POWER_UP_AYIN);
							App->ayin->power_up++;
						}
						else {
							//App->particles->coin_2000.speed.x = int(App->scene_temple->speed);
							App->particles->coin_2000.speed.y = -1.5;
							App->particles->AddParticle(App->particles->coin_2000, App->player2->position.x, App->player2->position.y, COLLIDER_NONE, PARTICLE_COIN);
							App->inter->score_ayin += 2000;
						}
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


			}


		}

	}
