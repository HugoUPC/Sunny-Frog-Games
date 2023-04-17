#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	moveLeft.PushBack({ 6,104,28,33 });
	moveLeft.PushBack({ 39,104,28,33 });
	moveLeft.PushBack({ 72,104,28,33 });
	moveLeft.speed = 0.2f;
	moveLeft.pingpong = true;

	moveRight.PushBack({ 172,104,28,33 });
	moveRight.PushBack({ 139,104,28,33 });
	moveRight.PushBack({ 104,104,28,33 });
	moveRight.speed = 0.2f;
	moveRight.pingpong = true;
	currentAnim = &moveRight;

	// TODO 3: Have the Brown Cookies describe a path in the screen

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
	path.PushBack({ 1.0f, 0.0f }, 120, &moveRight);
	path.PushBack({ -1.0f, 0.0f }, 120, &moveLeft);
}

void Enemy_Mech::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
