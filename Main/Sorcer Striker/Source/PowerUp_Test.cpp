#include "PowerUp_Test.h"

#include "Application.h"
#include "ModuleCollisions.h"

PowerUp_Test::PowerUp_Test(int x, int y) : PowerUp(x, y)
{
	flyAnim.PushBack({ 4,1,32,18 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::POWERUP, (Module*)App->powerups);
}

void PowerUp_Test::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));
	position.y += 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PowerUp::Update();
}
