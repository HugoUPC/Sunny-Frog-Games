#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene::ModuleScene()
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);

	//App->collisions->AddCollider({ 0, -3000, 240, 3000 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 110, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 125, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 150, 50);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 165, 50);

	return ret;
}

update_status ModuleScene::Update()
{
	App->render->camera.y -= 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 00, -510 + 250, NULL);
	return update_status::UPDATE_CONTINUE;
}