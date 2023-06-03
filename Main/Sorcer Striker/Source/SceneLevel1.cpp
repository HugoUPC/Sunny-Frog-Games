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
#include "ModuleParticles.h"
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

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -210);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -230);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -250);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -320);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -720);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -740);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -750);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -760);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -770);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -840);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -850);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -860);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -900);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1030);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1050);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -2000);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -2010);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -2020);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -2100);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 110, -400);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 110, -600);
	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 130, -600);
	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 150, -600);

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	screenBoundingBox = App->collisions->AddCollider({ 0, 0, 240, 10 }, Collider::Type::SCREENBOUNDINGBOX, this);

	bgSize = { 518, 1, 240, 340 };

	App->UI->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->collisions->Enable(); 

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 1;
	screenBoundingBox->SetPos(0, App->render->camera.y);

	//set mouseState and mouseCoords
	mouseState = App->input->GetMouse(&mousePos.x, &mousePos.y);

	if (spawnMode)
	{
		if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 1;
		}
		else if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 2;
		}
		else if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 3;
		}
		else if (App->input->keys[SDL_SCANCODE_4] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 4;
		}
		else if (App->input->keys[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 5;
		}
		else if (App->input->keys[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 6;
		}


		if (mouseState == 1)
		{
			switch (selectedSpawnItem)
			{
			case 1:
				App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 2:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 3:
				App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);				
				break;
			case 4:
				App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 5:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 6:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			default:
				break;
			}
		}
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN && !spawnMode)
	{
		spawnMode = true;
		LOG("Spawn Mode enabled");
	}
	else if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN && spawnMode)
	{
		spawnMode = false;
		LOG("Spawn Mode disabled");
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->render->camera.y = -9000;
		App->player->position.y = -8900;
	}

	if(App->render->camera.y == -9100) App->enemies->AddEnemy(ENEMY_TYPE::BOSS, -15, -9050);

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{	
	//LOG( "%d, %d", App->render->camera.y, App->player->position.y);

	if (App->render->camera.y < -5000 && App->render->camera.y > -7500){
		if (bgSize.x != 775) bgSize.x = 775;
	}

	else if (App->render->camera.y < -7500 && App->render->camera.y > -11000){
		if (bgSize.x != 1031) bgSize.x = 1031;
		bgSpeed = 2;
	}

	//Infinite Background (Hem penso que amb App->render->camera.y es pot fer)
	if (bgPos < 340) {
		App->render->Blit(bgTexture, 0, bgPos, &bgSize, 0);
		App->render->Blit(bgTexture, 0, bgPos - 340, &bgSize, 0);
		bgPos += bgSpeed;
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