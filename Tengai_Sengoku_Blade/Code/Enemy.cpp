#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y, int type) : position(x, y)
{}



Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;

	/*if (collider == nullptr)
		collider->to_delete = true;*/
}




const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (demon_wheel != nullptr)
		App->render->Blit(sprites, position.x + 27 , position.y - 18, &(demon_wheel->GetCurrentFrame()));

	if (demon_up != nullptr)
		App->render->Blit(sprites, position.x + 50, position.y - 40, &(demon_up->GetCurrentFrame()));
	
	if (demon_down != nullptr)
		App->render->Blit(sprites, position.x + 59, position.y + 72, &(demon_down->GetCurrentFrame()));

	if (demon_wheel1 != nullptr)
		App->render->Blit(sprites, position.x + w1x, position.y + w1y , &(demon_wheel1->GetCurrentFrame()));

	if (animation_chariot_wheels != nullptr)
		App->render->Blit(sprites, position.x - wheel_x + 80, position.y + 70 + wheel_y, &(animation_chariot_wheels->GetCurrentFrame()));

	if (animation_chariot_wheels2 != nullptr)
		App->render->Blit(sprites, position.x + 100 + wheel_x, position.y + 70 + wheel_y, &(animation_chariot_wheels2->GetCurrentFrame()));

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));


	if (chariot_robot != nullptr)
		App->render->Blit(sprites, position.x + 45, position.y + 5, &(chariot_robot->GetCurrentFrame()));

	if (furniture != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(furniture->GetCurrentFrame()));

	if (chariot_face_wolf != nullptr)
		App->render->Blit(sprites, position.x + 36, position.y + 7, &(chariot_face_wolf->GetCurrentFrame()));

	if (chariot_wolf != nullptr)
		App->render->Blit(sprites, position.x +36, position.y+7, &(chariot_wolf->GetCurrentFrame()));


	if (animation_chariot != nullptr)
		App->render->Blit(sprites, position.x + 65, position.y + 90 , &(animation_chariot->GetCurrentFrame()));


	if (animation_ball != nullptr)
		App->render->Blit(sprites, position.x + 18, position.y + 95 + spoty, &(animation_ball->GetCurrentFrame()));

	
}

void Enemy::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
}