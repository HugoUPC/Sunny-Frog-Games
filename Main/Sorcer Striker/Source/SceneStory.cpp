#include "SceneStory.h"

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

SceneStory::SceneStory(bool startEnabled) : Module(startEnabled)
{
	goblins.PushBack({ 877, 201, 431, 85 });
	goblins.PushBack({ 877, 290, 431, 85 });
	goblins.speed = 0.1f;

	path.PushBack({ 0.15f, 0.0f }, 200);

	letras.PushBack({ 1172, 513, 240, 104 });

	cielo.PushBack({ 877, 387, 240, 102 });

	dragones.PushBack({ 877, 499, 242, 102 });
	path1.PushBack({ 0.05f, 0.05f }, 200);

	dragon.PushBack({ 1131, 393, 1170 - 1131, 393 - 421 });
}

SceneStory::~SceneStory()
{

}

// Load assets
bool SceneStory::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/prueba.png");
	dragonstexture = App->textures->Load("Assets/Intro/dragons.png");
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;


	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5000)) {
		App->fade->FadeToBlack(this, (Module*)App->scenestory3, 90);
	}

	goblins.Update();
	path.Update();
	letras.Update();
	cielo.Update();
	dragones.Update();
	path1.Update();
	//dragon.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory::PostUpdate()
{
	App->render->Blit(texture, 0, 0, NULL);

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
		SDL_Rect rect = goblins.GetCurrentFrame();
		App->render->Blit(texture, -path.GetRelativePosition().x, 16, &rect);
	}
	
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2000)) {
		SDL_Rect rect = letras.GetCurrentFrame();
		App->render->Blit(texture, 0, 115, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = cielo.GetCurrentFrame();
		App->render->Blit(texture, 0, 219, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = dragones.GetCurrentFrame();
		App->render->Blit(texture, -path1.GetRelativePosition().x, 219, &rect);
	}

	//if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
	//	SDL_Rect rect = dragon.GetCurrentFrame();
	//	App->render->Blit(texture, -path.GetRelativePosition().x, -path.GetRelativePosition().y, &rect);
	//	//App->render->Blit(texture, 0, 219, &rect);
	//}

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory::CleanUp()
{
	//App->textures->Unload(bgTexture);
	App->textures->Unload(texture);

	return true;
}