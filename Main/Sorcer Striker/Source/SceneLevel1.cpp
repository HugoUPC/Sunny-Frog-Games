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

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1150);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1160);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1170);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1250);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1450);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1460);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1470);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1480);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1490);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1660);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1680);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1660);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1680);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1710);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1720);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -2000);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -2010);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -2020);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2350);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -2610);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -2620);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -2630);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2650);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -2700);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2950);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3150);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3210);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3230);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -3300);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3450);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3510);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3520);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -3500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3650);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3700);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3710);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3720);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3850);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -3900);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3900);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3910);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3920);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4030);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4050);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -4190);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -4200);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -4210);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -4200);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -4500);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -5100);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -5700);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -6300);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -6900);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -7500);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -8100);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -8700);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 110, -400);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 110, -600);

	

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
		else if (App->input->keys[SDL_SCANCODE_7] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 7;
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
				App->enemies->AddEnemy(ENEMY_TYPE::REDBAT, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 6:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 7:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			default:
				break;
			}
		}
	}

	if (App->DEBUG)
	{
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

		if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {

			if(App->speedMultiplier == 1)App->speedMultiplier = 2;
			else App->speedMultiplier = 1;
			
		}
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