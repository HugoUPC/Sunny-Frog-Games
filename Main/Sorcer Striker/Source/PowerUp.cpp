#include "PowerUp.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

PowerUp::PowerUp(int x, int y) : position(x, y)
{
	spawnPos = position;
}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* PowerUp::GetCollider() const
{
	return collider;
}

void PowerUp::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void PowerUp::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void PowerUp::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
}

void PowerUp::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}