#include "Enemy_RedBall.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_RedBall::Enemy_RedBall(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,24,35 });
	fly.PushBack({ 34,0,26,35 });
	fly.speed = 0.3f;
	

	currentAnim = &fly;

	path.PushBack({0.9f, 0.5f}, 200);
	path.PushBack({0.0f, 0.0f}, 10);
	path.PushBack({-0.9f, 0.5f}, 200);
	path.loop;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBall::Update()
{
	path.Update();
	
	
	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
