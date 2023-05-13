#include "Enemy_RedBallStraight.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_RedBallStraight::Enemy_RedBallStraight(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,24,35 });
	fly.PushBack({ 34,0,26,35 });
	fly.speed = 0.3f;


	currentAnim = &fly;

	path.PushBack({ 0.0f, 4.0f }, 60);
	path.PushBack({ 0.0f, 0.0f }, 10);
	path.PushBack({ 3.0f, -5.0f }, 80);
	
	

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBallStraight::Update()
{
	if (position.y > App->render->camera.y / 2 - 24) {
		path.Update();
	}

	position = spawnPos + path.GetRelativePosition();





	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
