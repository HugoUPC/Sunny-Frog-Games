#include "Enemy_RedBat.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_RedBat::Enemy_RedBat(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 570,2,34,40 });
	fly.PushBack({ 529,2,34,40 });
	fly.PushBack({ 481,2,34,40 });
	fly.PushBack({ 438,2,42,40 });
	
	
	
	fly.speed = 0.5f;
	fly.loop = false;


	currentAnim = &fly;

	path.PushBack({ 0.0f, -2.0f }, 20);
	path.PushBack({ 0.0f, 1.0f }, 200);
	path.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 34, 40 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBat::Update()
{
	if (position.y > App->render->camera.y - 24) {
		path.Update();
	}

	position = spawnPos + path.GetRelativePosition();





	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
