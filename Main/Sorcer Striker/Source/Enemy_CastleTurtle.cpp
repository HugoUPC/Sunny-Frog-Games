#include "Enemy_CastleTurtle.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Enemy_CastleTurtle::Enemy_CastleTurtle(int x, int y) : Enemy(x, y)
{
	walk.PushBack({0,146,162,164 });

	walk.speed = 0.09f;

	path.PushBack({ 0.0f, -2.0f }, 100000);
	path.loop;

	currentAnim = &walk;

	/*path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);*/

	collider = App->collisions->AddCollider({ 0, 0, 162, 164 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_CastleTurtle::Update()
{
	path.Update();
	position.y = +1;

	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_CastleTurtle::OnCollision(Collider* collider) {

	if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives <= 0) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
	else if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives > 0) {
		App->particles->AddParticle(App->particles->explosion, position.x + 44, position.y + 90);
		App->audio->PlayFx(destroyedFx);
		lives--;
	}
}
