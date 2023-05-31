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
	pathscroll.PushBack({ 0.0f, -1.0f }, 200);

	letras.PushBack({ 0, 483, 240, 340 });
	man.PushBack({ 0, 35, 240, 175 });

	explosion.PushBack({ 413, 9, 134, 137 });
	explosion.PushBack({ 552, 9, 134, 137 });
	explosion.PushBack({ 691, 9, 134, 137 });
	explosion.PushBack({ 413, 151, 134, 137 });
	explosion.PushBack({ 691, 151, 134, 137 });
	explosion.PushBack({ 413, 151, 134, 137 });
	explosion.PushBack({ 691, 9, 134, 137 });
	explosion.PushBack({ 691, 151, 134, 137 });
	explosion.PushBack({ 413, 151, 134, 137 });
	explosion.PushBack({ 830, 151, 134, 137 });
	explosion.PushBack({ 552, 151, 134, 137 });
	explosion.PushBack({ 0, 0, 0, 0 });
	explosion.speed = 0.1f;
	explosion.loop = false;

	ship1.PushBack({ 32, 33, 22, 32 });
	ship2.PushBack({ 119, 19, 21, 51-19 });
	ship3.PushBack({ 142, 63, 167-142, 98-63 });
	ship4.PushBack({ 59, 75, 22, 45 });

	pathship1.PushBack({ 0.0f, -1.0f }, 65);
	pathship1.PushBack({ 1.0f, 0.2f }, 20);
	pathship1.PushBack({ 1.0f, 0.2f }, 65);
	pathship1.PushBack({ -1.0f, 1.3f }, 20);
	pathship1.loop;
	
	pathship2.PushBack({ 0.0f, -1.0f }, 65);
	pathship2.PushBack({ 1.0f, 0.2f }, 20);
	pathship2.PushBack({ 1.0f, 0.2f }, 65);
	pathship2.PushBack({ -1.0f, 1.3f }, 20);
	pathship2.loop;

	pathship3.PushBack({ 0.0f, -1.0f }, 65);
	pathship3.PushBack({ 1.0f, 0.2f }, 20);
	pathship3.PushBack({ 1.0f, 0.2f }, 65);
	pathship3.PushBack({ -1.0f, 1.3f }, 20);
	pathship3.loop;

	pathship4.PushBack({ 0.0f, -1.0f }, 65); 
	pathship4.PushBack({ 1.0f, 0.2f }, 20);
	pathship4.PushBack({ 1.0f, 0.2f }, 65);
	pathship4.PushBack({ -1.0f, 1.3f }, 20);
	//pathship4.loop;
	
	//pathship1.PushBack({ 0.0f, -1.0f }, 200);
	//pathship1.PushBack({ -1.0f, 0.0f }, 200);
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
	shiptexture = App->textures->Load("Assets/Intro/ships.png");

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

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 9500)) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	App->render->camera.y -= 1;

	letras.Update(); 
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2200)) explosion.Update();
	man.Update();
	ship1.Update();
	pathscroll.Update();
	pathship1.Update();

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

	App->render->Blit(texture2, 0, pathscroll.GetRelativePosition().y, NULL);
	
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
		App->textures->Unload(texture2);
	}



	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout-1000)) {
		SDL_Rect rect = letras.GetCurrentFrame();
		App->render->Blit(texture, 2, pathscroll.GetRelativePosition().y, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
		SDL_Rect rect = man.GetCurrentFrame();
		App->render->Blit(texture, 0, 60 + pathscroll.GetRelativePosition().y, &rect);
	}

	//EXPLOSIONS
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2200)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, -30, 252 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2300)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 150, 235 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2400)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 70, 205 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2500)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 135, 112 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2600)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, -10, 140 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2700)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 54, 76 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, -60, 27 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2900)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 105, -5 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 165, 8 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3100)) {
		SDL_Rect rect = explosion.GetCurrentFrame();
		App->render->Blit(texture, 20, -40 + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3600)) {
		App->textures->Unload(texture);
	}
	//END EXPLOSIONS (unload letras, man and explosions. Load ships)

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 4000)) {
		SDL_Rect rect = ship1.GetCurrentFrame();
		App->render->Blit(shiptexture, 52, 194  + pathship1.GetRelativePosition().y + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 4000)) {
		SDL_Rect rect = ship2.GetCurrentFrame();
		App->render->Blit(shiptexture, 140, 179 + pathship1.GetRelativePosition().y + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 4000)) {
		SDL_Rect rect = ship3.GetCurrentFrame();
		App->render->Blit(shiptexture, 163, 226 + pathship1.GetRelativePosition().y + pathscroll.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 4000)) {
		SDL_Rect rect = ship4.GetCurrentFrame();
		App->render->Blit(shiptexture, 79, 236 + pathship1.GetRelativePosition().y + pathscroll.GetRelativePosition().y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory5::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}