#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	// idle animation - just one sprite
	idleAnim.PushBack({ 0, 0, 30, 38 });

	// move upwards
	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	powerUp1.PushBack({ 50, 0, 21, 13 });
	powerUp1.PushBack({ 50, 14, 21, 9 });
	powerUp1.PushBack({ 50, 24, 21, 12 });
	powerUp1.speed = 0.1f;

	shipleft.PushBack({ 2, 46, 31, 38});
	shipleft.PushBack({ 7, 93, 24, 38 });
	shipleft.loop = false;
	shipleft.speed = 0.05f;

	shipright.PushBack({ 43, 46, 31, 38 });
	shipright.PushBack({ 45, 93, 24, 38 });
	shipright.loop = false;
	shipright.speed = 0.05f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/ship.png"); // arcade version
	currentAnimation = &idleAnim;
	
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	position.x = 110;
	position.y = 150;

	backupPosition = position;

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;
	score = 000;
	lives = 3;
	kills = 0;
	PowerUpActivated = false;
	transitionTimer = 50;


	collider = App->collisions->AddCollider({ position.x, position.y, 29, 38 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01..........23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	return ret;
}

update_status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	position.y -= 1;
	backupPosition.y -= 1;

	shipleft.Update();
	shipright.Update();

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x >= 0) {
			position.x -= speed;
		}
		
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x <= 208) {
			position.x += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y <= (App->render->camera.y) + 300) {
			position.y += speed;
			backupPosition.y += speed;
		}

		/*if (position.y <= App->render->camera.y) {
			position.y += speed;
		}*/
		/*if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}*/
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y >= App->render->camera.y) {
			position.y -= speed;
			backupPosition.y -= speed;
		}
		
		/*if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}*/
	}


	if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || burst) && shootCooldown <= 0)
	{
		if (!burst && burstCounter == 2) {
			burst = true;
			Particle* laser = App->particles->AddParticle(App->particles->laser, position.x + 11, position.y - 20, Collider::Type::PLAYER_SHOT);
			if (laser != nullptr)
			{
				laser->collider->AddListener((Module*)App->enemies);
			}
			App->audio->PlayFx(laserFx);
		}

		if (burstCounter <= 0) {
			burst = false;
			burstCounter = 2;
			shootCooldown = 30;
		}
			
		if (burstCountdown <= 0) {
			Particle* laser = App->particles->AddParticle(App->particles->laser, position.x + 11, position.y - 20, Collider::Type::PLAYER_SHOT);
			if (laser != nullptr)
			{
				laser->collider->AddListener((Module*)App->enemies);
			}
			App->audio->PlayFx(laserFx);
			burstCountdown = 5;
			burstCounter--;
		}
		else {
			burstCountdown--;
		}

		
	}

	if(shootCooldown > 0) shootCooldown--;

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && PowerUpActivated && shootCooldown <= 0) {
		PowerUp();
	}

	if (App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN) {
		bombStarted = true;
	}
	bomb();

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	// TODO 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
		kills = 20;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
	if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
		lives = 0;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN && !godMode) {
		godMode = true;
	}
	else if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN && godMode){
		godMode = false;
	}


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	else
	{
		if (destroyedCountdown <= 0) {
			position.x = backupPosition.x;
			position.y = backupPosition.y;
			destroyedCountdown = 120;
			destroyed = false;
		}
		else {
			position.x = 50000;
			position.y = -50000;
			destroyedCountdown--;
		}
	}

	if (PowerUpActivated)
	{
		powerUp1.Update();
		App->render->Blit(texture, position.x - 25, position.y + 12, &(powerUp1.GetCurrentFrame()));
		App->render->Blit(texture, position.x + 33, position.y + 12, &(powerUp1.GetCurrentFrame()));
	}

	if (bombStarted)
	{
		if (bombStartedTimer < 120)
		{
			App->render->Blit(texture, position.x, position.y - bombStartedTimer, &(powerUp1.GetCurrentFrame())); //textura provisional, cambiar por la de la bomba
			bombStartedTimer++;
		}
		else
		{
			bombStarted = false;
			bombActivated = true;
			bombStartedTimer = 0;
		}
	}

	if (bombActivatedTimer < 240 && bombActivatedTimer != 0)
	{
		App->render->Blit(texture, position.x, position.y - 150, &(powerUp1.GetCurrentFrame()));
	}

	if (kills >= 100 && transitionTimer <= 0) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	else if (kills >= 100 && transitionTimer > 0) transitionTimer--;

	if (lives < 0 && transitionTimer <= 0) App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	else if (lives < 0 && transitionTimer > 0) transitionTimer--;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT) {
		SDL_Rect rect = shipleft.GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT) {
		SDL_Rect rect = shipright.GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT && lives <= 0)
	{
		lives--;
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
	else if(c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT && destroyed == false && !godMode){
		destroyed = true;
		PowerUpActivated = false;
		lives--;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		score += 23;
		kills++;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::POWERUP) {
		if (PowerUpActivated) {
			PowerUpActivated = false;
		}
		else {
			PowerUpActivated = true;
		}
	}
}

void ModulePlayer::PowerUp() {
	Particle* batShotL = App->particles->AddParticle(App->particles->bat_shotsR, position.x , position.y + 20, Collider::Type::PLAYER_SHOT);
	Particle* batShotR = App->particles->AddParticle(App->particles->bat_shotsL, position.x, position.y + 20, Collider::Type::PLAYER_SHOT);
	if (batShotL != nullptr)
	{
		batShotL->collider->AddListener(this);
	}
	if (batShotR != nullptr)
	{
		batShotR->collider->AddListener(this);
	}

	App->audio->PlayFx(laserFx);
}

void ModulePlayer::bomb() {
	//Primero tiene un delay inicial en el cual la bomba avanza, luego explota el radio del sprite, dura unos segundos y luego acaba.

	if (bombActivated == true)
	{
		if (bombActivatedTimer == 0)
		{
			bombCollider = App->collisions->AddCollider({ position.x - 35, position.y - 200, 100, 100 }, Collider::Type::PLAYER_SHOT, (Module*)App->enemies);
			App->render->Blit(texture, position.x - 35, position.y - 200, &(powerUp1.GetCurrentFrame()));
		}

		if (bombActivatedTimer < 240)
		{
			bombActivatedTimer++;
			bombCollider->SetPos(position.x - 35, position.y - 200);
			App->render->Blit(texture, position.x - 35, position.y - 200, &(powerUp1.GetCurrentFrame()));
		}
		else
		{
			bombActivatedTimer = 0;
			bombActivated = false;
			bombCollider->pendingToDelete = true;
		}
	}
}