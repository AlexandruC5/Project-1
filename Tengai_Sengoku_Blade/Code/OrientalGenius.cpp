#include "Application.h"
#include "OrientalGenius.h"
#include "ModuleCollision.h"



OrientalGenius::OrientalGenius(int x, int y, int type) : Enemy(x, y,type)
{


	

	up1.PushBack({ 9, 181,42, 35 });
	up2.PushBack({ 60,151, 42, 81 });
	up3.PushBack({ 113,181, 42, 62 });
	
	stay.PushBack({ 170,181, 41, 58 });
	stay.PushBack({226, 183, 38, 55});
	
	back.PushBack({ 226, 183, 38, 55 });

	shoot.PushBack({ 402, 181, 35, 52 });//1
	shoot.PushBack({ 345, 181, 35, 48 });//2
	shoot.PushBack({ 9, 258, 36, 44 });//3
	shoot.PushBack({ 60, 258, 36, 45 });//3
	shoot.PushBack({ 122, 258, 46, 45 });//4
	shoot.PushBack({280, 176, 44, 56});//5
	
	path.PushBack({ -0.5, -0.5 }, 10, &up1);
	path.PushBack({ -0.5, -0.5 }, 15, &up2);
	path.PushBack({ -0.5, -0.5 }, 50, &up3);

	path.PushBack({ 0.75f, 0 }, 50, &stay);
	path.PushBack({ 0.75f, 0 }, 200, &shoot);
	path.PushBack({ 2, -0.2f }, 99, &back);
	path.PushBack({ 1.5f, -2 }, 300, &shoot);

	//path.PushBack({ 0.5f,-1 }, 500, &shoot);
	
	stay.speed = 0.01f;
	shoot.speed = 0.02f;
	
	animation = &up1;
	animation = &up3;
	animation = &up2;
	animation = &stay;
	animation = &shoot;
	animation = &back;
	collider = App->collision->AddCollider({ 0, 0, 44, 56 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos = { x,y };


}

void OrientalGenius::Move()
{
	
	iPoint path_pos = path.GetCurrentPosition(&animation);
	position.x = float(original_pos.x + path_pos.x);
	position.y = float(original_pos.y + path_pos.y);

}