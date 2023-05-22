#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	head.PushBack({ 691,164,44,58 });
	head.PushBack({ 583,164,44,58 });
	head.PushBack({ 476,164,44,58 });
	head.speed = 0.09f;

	currentHead = &head;

	headDamaged.PushBack({ 645,164,44,58 });
	headDamaged.PushBack({ 539,164,44,58 });
	headDamaged.PushBack({ 433,164,44,58 });
	headDamaged.speed = 0.09f;

	propeller.PushBack({ 490,233,37,29 });
	propeller.PushBack({ 453,233,37,29 });
	propeller.speed = 0.09f;

	fullBody = { 24,344,287,126 };

	

	//path.PushBack({ 0.0f, 1.0f }, 120);
	//path.PushBack({ 0.0f, -2.0f }, 120);
	//path.loop;

	//currentAnim = &walk;

	path.PushBack({0.0f, 0.5f}, 60);
	path.loop = false;

	//collider = App->collisions->AddCollider({ 0, 0, 281,124 }, Collider::Type::WALL, (Module*)App->enemies);

	head1 = App->collisions->AddCollider({ 60, 84, 44,58 }, Collider::Type::ENEMY, (Module*)App->enemies);
	head2 = App->collisions->AddCollider({ 127, 84, 44,58 }, Collider::Type::ENEMY, (Module*)App->enemies);
	head3 = App->collisions->AddCollider({ 198, 84, 44,58 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_Boss::Update()
{

	head.Update();
	headDamaged.Update();
	propeller.Update();


	head1->SetPos(position.x + 60, position.y + 84);
	head2->SetPos(position.x + 127, position.y + 84);
	head3->SetPos(position.x + 198, position.y + 84);

	//path.Update();
	position.y -= 1;

	//position.y = spawnPos.y + path.GetRelativePosition().y;

	position.x = spawnPos.x + sin(SDL_GetTicks() / 3) * 5;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Boss::Draw()
{
	App->render->Blit(texture, position.x, position.y, &fullBody);

	App->render->Blit(texture, position.x + 60, position.y + 84, &(currentHead->GetCurrentFrame()));
	App->render->Blit(texture, position.x + 127, position.y + 84, &(head.GetCurrentFrame()));
	App->render->Blit(texture, position.x + 198, position.y + 84, &(head.GetCurrentFrame()));

	App->render->Blit(texture, position.x + 17, position.y + 83, &(propeller.GetCurrentFrame()));
	App->render->Blit(texture, position.x + 96, position.y + 84, &(propeller.GetCurrentFrame()));
	App->render->Blit(texture, position.x + 156, position.y + 83, &(propeller.GetCurrentFrame()));
	App->render->Blit(texture, position.x + 240, position.y + 84, &(propeller.GetCurrentFrame()));


}

void Enemy_Boss::OnCollision(Collider* collider) {}

void Enemy_Boss::OnCollision(Collider* c1, Collider* c2) {

	//LOG("holi2");

	if (c1 == head1 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head1 HIT!");
		currentHead = &headDamaged;
	}
	if (c1 == head2 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head2 HIT!");
	}
	if (c1 == head3 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head3 HIT!");
	}


	/*if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives <= 0) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
	else if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives > 0) {
		App->particles->AddParticle(App->particles->explosion, position.x + 44, position.y + 90);
		App->audio->PlayFx(destroyedFx);
		lives--;
	}*/
}

bool Enemy_Boss::ContainsCollider(Collider* c1)
{
	bool ret = false;
	ret = Enemy::ContainsCollider(c1);

	if (head1 == c1)
	{
		c1 = head1;
		ret = true;
	}
	else if (head2 == c1)
	{
		c1 = head2;
		ret = true;
	}
	else if (head3 == c1)
	{
		c1 = head3;
		ret = true;
	}
	return ret;
}
