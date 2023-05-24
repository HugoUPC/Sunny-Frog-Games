#include "SceneStory5.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib")
#pragma comment( lib, "SDL/libx86/SDL2main.lib")

SceneStory5::SceneStory5(bool startEnabled) : Module(startEnabled)
{

	letras.PushBack({ 0, 483, 240, 340 });
	man.PushBack({ 0, 35, 240, 175 });

	explosion.PushBack({ 280,16,95,101 });
	explosion.PushBack({ 620, 22, 96, 101 });
	explosion.PushBack({ 412, 7, 137, 140 });
	explosion.PushBack({ 620, 22, 96, 101 });
	explosion.PushBack({ 280,16,95,101 });
	explosion.PushBack({ 412, 7, 137, 140 });
	explosion.PushBack({ 620, 22, 96, 101 });
	explosion.PushBack({ 0, 0, 0, 0 });
	explosion.speed = 0.13f;
	explosion.loop = false;

	ship1.PushBack({ 512, 405, 22, 42 });

	pathscroll.PushBack({ 0.0f, -1.0f }, 200);

	pathship1.PushBack({ 0.0f, -2.0f }, 200);
	
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

	letras.Update(); 
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) explosion.Update();
	man.Update();
	ship1.Update();
	pathscroll.Update();
	pathship1.Update();

//	App->collisions->Enable();

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

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2100)) {
		SDL_Rect rect = man.GetCurrentFrame();
		App->render->Blit(texture, 0, 60 + pathscroll.GetRelativePosition().y, &rect);
	}

	//EXPLOSIONS
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000) && !(SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3001))) explosion.Reset();
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 70, 205 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, -20, 140 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 140, 113 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 50, 10 + pathscroll.GetRelativePosition().y, &rect);
	}
	//END EXPLOSIONS (unload letras, man and explosions. Load ships)
	
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = ship1.GetCurrentFrame();
		App->render->Blit(texture, 15, 400 + pathship1.GetRelativePosition().y + pathscroll.GetRelativePosition().y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory5::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}