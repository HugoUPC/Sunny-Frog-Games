#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

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

	//App->collisions->AddCollider({ 0, -3000, 240, 3000 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 8000, 8000, 10, 3000 }, Collider::Type::WALL);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 110, 0);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 125, -100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 150, 50);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 165, 50);

	App->player->Enable(); 
	App->enemies->Enable();

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 00, -510 + 250, NULL);
	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 5: Remove all memory leaks
	App->player->Disable();
	App->enemies->Disable();

	//App->textures->Unload(bgTexture);

	return true;
}