#include "Enemy_BlueDragon.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BlueDragon::Enemy_BlueDragon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,45,91,100 });
	fly.PushBack({ 107,45,92,100 });
	fly.PushBack({ 211,45,88,100 });
	fly.PushBack({ 314,45,87,100 });
	
	fly.speed = 0.09f;


	currentAnim = &fly;

	/*path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);*/

	collider = App->collisions->AddCollider({ 0, 0, 88, 90 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BlueDragon::Update()
{
	path.Update();
	position.y = +1;

	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
