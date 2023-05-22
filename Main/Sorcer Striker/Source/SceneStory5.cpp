#include "SceneStory5.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "ModuleCollisions.h"

#include <stdio.h>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

SceneStory5::SceneStory5(bool startEnabled) : Module(startEnabled)
{

	letras.PushBack({ 0, 483, 240, 340 });
	man.PushBack({ 0, 35, 240, 175 });
	explosion.PushBack({ 280,16,95,101 });

	pathscroll.PushBack({ 0.0f, -1.0f }, 200);

	
}

SceneStory5::~SceneStory5()
{

}

// Load assets
bool SceneStory5::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/SceneStory5.png");
	texture2 = App->textures->Load("Assets/Intro/por probar.png");
	bgTexture = App->textures->Load("Assets/Intro/backgroundd.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	screenBoundingBox = App->collisions->AddCollider({ 0, 0, 240, 10 }, Collider::Type::SCREENBOUNDINGBOX, this);

	bgSize = { 0, 3, 240, 343 };

	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory5::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	/*if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5000)) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}*/

	App->render->camera.y -= 1;
	screenBoundingBox->SetPos(0, App->render->camera.y);

	letras.Update(); 
	explosion.Update();
	man.Update();
	pathscroll.Update();

	App->collisions->Enable();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory5::PostUpdate()
{
	if (App->render->camera.y < -5000 && App->render->camera.y > -7500) {
		if (bgSize.x != 775) bgSize.x = 775;
	}

	else if (App->render->camera.y < -7500 && App->render->camera.y > -11000) {
		if (bgSize.x != 1031) bgSize.x = 1031;
		bgSpeed = 2;
	}
	//Infinete background
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

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout - 1000)) {
		App->render->Blit(texture2, 0, pathscroll.GetRelativePosition().y, NULL);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2000)) {
		App->textures->Unload(texture2);
	}



	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1500)) {
		SDL_Rect rect = letras.GetCurrentFrame();
		App->render->Blit(texture, 2, pathscroll.GetRelativePosition().y, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2050)) {
		SDL_Rect rect = man.GetCurrentFrame();
		App->render->Blit(texture, 0, 60 + pathscroll.GetRelativePosition().y, &rect);
	}

	//EXPLOSIONS
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 15, 10 + pathscroll.GetRelativePosition().y, &rect); 
	}
	//END EXPLOSIONS (unload letras, man and explosions. Load ships)
	

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory5::CleanUp()
{
	App->textures->Unload(texture);
	App->collisions->Disable();
	return true;
}