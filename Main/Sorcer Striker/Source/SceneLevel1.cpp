#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "ModulePlayer.h"
#include <stdio.h>

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 110, -450);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 125, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 150, -650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 165, -700);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 110, -820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 125, -920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 150, -1020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 165, -1020);

	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 110, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 125, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 150, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 165, -650);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP, 110 / 2, -400 / 2);

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	screenBoundingBox = App->collisions->AddCollider({ 0, 0, 240, 10 }, Collider::Type::SCREENBOUNDINGBOX, this);

	App->UI->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->collisions->Enable(); 

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 2;
	screenBoundingBox->SetPos(0, App->render->camera.y / 2);

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{	
	SDL_Rect bgSize = { 518, 1, 240, 340 };

	LOG("(%d, %d", App->render->camera.y + App->render->camera.h, bgPos);

	//Infinite Background (Hem penso que amb App->render->camera.y / 2 es pot fer)
	if (bgPos < 340) {
		App->render->Blit(bgTexture, 0, bgPos, &bgSize, 0);
		App->render->Blit(bgTexture, 0, bgPos - 340, &bgSize, 0);
		bgPos += 2;
	}
	else {
		bgPos = 0;
		App->render->Blit(bgTexture, 0, bgPos, &bgSize, 0);
		App->render->Blit(bgTexture, 0, bgPos - 340, &bgSize, 0);
	}

	
	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 5: Remove all memory leaks
	App->UI->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	//App->textures->Unload(bgTexture);

	return true;
}