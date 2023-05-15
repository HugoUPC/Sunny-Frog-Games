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
	algo.PushBack({ 0,0,0,0 });

	path.PushBack({ 0.0f, 0.0f }, 200);
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

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory5::Update()
{
	//App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	/*if (App->render->camera.y < 680) {
		App->render->camera.y += 1;
	}
	if (App->render->camera.y >= 680) {
		App->fade->FadeToBlack(this, (Module*)App->intro1, 90);
	}*/

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5000)) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	algo.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory5::PostUpdate()
{
	//App->render->Blit(texture, 0, 0, NULL);
	App->render->Blit(texture2, 0, 0, NULL);

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
		SDL_Rect rect = algo.GetCurrentFrame();
		App->render->Blit(texture, 15, 10, &rect);
	}


	return update_status::UPDATE_CONTINUE;
}

bool SceneStory5::CleanUp()
{
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 300)) {
		App->textures->Unload(texture2);
	}
	App->textures->Unload(texture);

	return true;
}