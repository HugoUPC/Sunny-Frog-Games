#include "SceneStory4.h"

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

SceneStory4::SceneStory4(bool startEnabled) : Module(startEnabled)
{
	//1172 638 719 1252
	character1.PushBack({ 1172, 639, 80, 80 });
	character2.PushBack({ 1255, 639, 80, 80 });
	character3.PushBack({ 1338, 639, 80, 80 });
	character4.PushBack({ 1421, 639, 80, 80 });

	path1.PushBack({ -1.0f, -1.2f }, 200);
	path2.PushBack({ 1.0f, -1.2f }, 200);
	path3.PushBack({ -1.0f, 1.2f }, 200);
	path4.PushBack({ 1.0f, 1.2f }, 200);
}

SceneStory4::~SceneStory4()
{

}

// Load assets
bool SceneStory4::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/prueba.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory4::Update()
{
	//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	character1.Update();
	character2.Update();
	character3.Update();
	character4.Update();
	path1.Update();
	path2.Update();
	path3.Update();
	path4.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory4::PostUpdate()
{
	App->render->Blit(texture, 0, -694, NULL);
	
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
		SDL_Rect rect = character1.GetCurrentFrame();
			App->render->Blit(texture, 15, 10, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 900)) {
		SDL_Rect rect = character2.GetCurrentFrame();
		App->render->Blit(texture, 145, 10, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 600)) {
		SDL_Rect rect = character3.GetCurrentFrame();
		App->render->Blit(texture, 15, 241, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 300)) {
		SDL_Rect rect = character4.GetCurrentFrame();
		App->render->Blit(texture, 145, 241, &rect);
	}


	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1300)) {
		SDL_Rect rect = character1.GetCurrentFrame();
		App->render->Blit(texture, 15 - path1.GetRelativePosition().x, 10 - path1.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1300)) {
		SDL_Rect rect = character2.GetCurrentFrame();
		App->render->Blit(texture, 145 - path2.GetRelativePosition().x, 10 - path2.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1300)) {
		SDL_Rect rect = character3.GetCurrentFrame();
		App->render->Blit(texture, 15 - path3.GetRelativePosition().x, 241 - path3.GetRelativePosition().y, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1300)) {
		SDL_Rect rect = character4.GetCurrentFrame();
		App->render->Blit(texture, 145 - path4.GetRelativePosition().x, 241 - path4.GetRelativePosition().y, &rect);
	}
	

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory4::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}