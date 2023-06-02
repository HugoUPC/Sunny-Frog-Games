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

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -200);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -250);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -320);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -450);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -900);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1480);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1560);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1680);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2080);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2160);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2200);

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

	if (mouseState == 1)
	{
		App->particles->AddParticle(App->particles->explosion, mousePos.x, mousePos.y);
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

	//debug mouse pos
	/*SDL_Rect testRect = { mousePos.x, mousePos.y, 15, 15 };
	App->render->DrawQuad(testRect, 255, 0, 0, 255, 0);*/

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