#include "ModuleAnim.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Anim.h"
#include "Anim_Goblins.h"

#define SPAWN_MARGIN 50


ModuleAnim::ModuleAnim(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ANIM; ++i)
		animation[i] = nullptr;
}

ModuleAnim::~ModuleAnim()
{

}

bool ModuleAnim::Start()
{
	texture = App->textures->Load("Assets/Intro/prueba.png");

	return true;
}


update_status ModuleAnim::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (animation[i] != nullptr && animation[i]->pendingToDelete)
		{
			delete animation[i];
			animation[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAnim::Update()
{

	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (animation[i] != nullptr)
			animation[i]->Update();
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleAnim::PostUpdate()
{
	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (animation[i] != nullptr)
			animation[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAnim::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (animation[i] != nullptr)
		{
			delete animation[i];
			animation[i] = nullptr;
		}
	}

	return true;
}

bool ModuleAnim::AddAnim(ANIM_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (spawnQueue[i].type == ANIM_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleAnim::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (spawnQueue[i].type != ANIM_TYPE::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnAnim(spawnQueue[i]);
				spawnQueue[i].type = ANIM_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}


void ModuleAnim::SpawnAnim(const AnimSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ANIM; ++i)
	{
		if (animation[i] == nullptr)
		{
			switch (info.type)
			{
			case ANIM_TYPE::GOBLINS:
				animation[i] = new Anim_Goblins(info.x, info.y);
				break;
			}
			animation[i]->texture = texture;

			break;
		}
	}
}
